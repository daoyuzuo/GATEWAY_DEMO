#include "socket_can.h"
#include "raw_socket_ipv6.h"
#include "protocol_translate.h" 

extern struct can_frame can_recv_que;
extern uint8_t *ipv6_send_que;
extern struct can_frame can_send_que;
extern int can_que_flag,ipv6_que_flag;

int can_init()
{
    //reboot can0 interface
    system(down);
    system(command);
    system(up);
    return 0;
}

int can_send(struct can_frame frame)
{
    int s, nbytes = 0;
    struct sockaddr_can addr;
    struct ifreq ifr;

    //create socket
    s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    strcpy(ifr.ifr_name, "can0" );

    //get info about can0
    ioctl(s, SIOCGIFINDEX, &ifr); 
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    //bind addr with socket
    bind(s, (struct sockaddr *)&addr, sizeof(addr));
    nbytes = write(s, &frame, sizeof(frame));
    if(nbytes != sizeof(frame))
    {
        printf("Send Error frame[0]!\n");
    }
    close(s);
    return 0;
}

int can_receive(struct can_frame * r_frame,unsigned int filter_id)
{
    int s, nbytes = 0;
    struct sockaddr_can addr;
    struct ifreq ifr;
    struct can_frame frame;
    struct can_filter rfilter;

    // Initial frame
    memset(&frame,0,sizeof(frame));
    s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    strcpy(ifr.ifr_name, "can0" );
    ioctl(s, SIOCGIFINDEX, &ifr); 
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    // Bind addr to socket 
    bind(s, (struct sockaddr *)&addr, sizeof(addr));

    // Set filter and mask for can_receive().
/*    if (filter_id != 0)
    {
        rfilter.can_id   = 0x123;
        // CAN_EFF_MASK | CAN_SFF_MASK
        rfilter.can_mask = CAN_SFF_MASK;
        setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));//设置规则：rcan_id & can_mask == can_id & can_mask
    }
*/
    while (nbytes == 0)
    {
        nbytes = read(s, &frame, sizeof(frame));
    }
    *r_frame = frame;
    return 0;
}
/*  can_id 
 *  CAN_EFF_FLAG: extend 
 *  CAN_RTR_FLAG: remote
 *  CAN_ERR_FLAG: error
 *  exm:frame.can_id = CAN_EFF_FLAG | 0x123 ;
 * */
int send_cansta(void)
{   
    struct can_frame frame;
    memset(&frame, 0, sizeof(frame));
    
    frame.can_id = 0x301;
    frame.can_dlc = 8;
    frame.data[0] = 0x00;
    can_send(frame);
    return 0;
}

int rev_can(void)
{
    struct can_frame frame;
    memset(&frame, 0, sizeof(frame)); 
    can_receive(&frame,0);
    printf("length:%d ", sizeof(frame));
    printf("ID=0x%X DLC=%d\n", frame.can_id, frame.can_dlc);
    printf("data=0x ",frame.data);
    for(int i=0;i<8;i++)
    {
        printf("%02X ",frame.data[i]);
    }
    printf("\n");
    return 0;
}

int send_caneff(void)
{
    struct can_frame frame;
    memset(&frame, 0, sizeof(frame));
    frame.can_id = CAN_EFF_FLAG | 0xAA0301;
    frame.can_dlc = 8;
    frame.data[0] = 0X00;//十进制
    frame.data[1] = 0X00;
    can_send(frame);
    return 0;
}


int send_canrtr(void)
{
    struct can_frame frame;
    memset(&frame, 0, sizeof(frame));
    frame.can_id = CAN_RTR_FLAG | 0x30000;
    frame.can_dlc = 8;
    frame.data[0] = 33;//远程针相当于命令，要求相同ID的节点返回数据针，发送方只发送远程针的ID部分，不发送数据内容
    can_send(frame);
    return 0;
}

float can_get_vol(void)
{
    float vol_vle = 0;
    struct can_frame frame;
    memset(&frame, 0, sizeof(frame));
    // wait until can frame 100 received
    can_receive(&frame,0);
    printf("###############################\n");
    printf("length:%d ", sizeof(frame));
    printf("ID=0x%X DLC=%d\n", frame.can_id, frame.can_dlc);
    printf("data0=0x%02x\n",frame.data[0]);
    printf("data1=0x%02x\n",frame.data[1]);
    printf("data2=0x%02x\n",frame.data[2]);
    printf("data3=0x%02x\n",frame.data[3]);
    printf("data4=0x%02x\n",frame.data[4]);
    printf("data5=0x%02x\n",frame.data[5]);
    printf("data6=0x%02x\n",frame.data[6]);
    printf("data7=0x%02x\n",frame.data[7]);

    vol_vle = (float)frame.data[0]/50;
    return vol_vle;
}


//-------------------------------------------------------------------------------------------------------//
// Follow code is about CAN thread.

// CAN receive thread.
void* can_recv_thread(void *arg){

    int sd, nbytes = 0;
    unsigned int filter_id;
    struct sockaddr_can addr;
    struct ifreq ifr;
    struct can_frame frame;
    struct can_filter rfilter;

    // Initial frame and CAN socket.
    memset(&frame,0,sizeof(frame));
    sd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    strcpy(ifr.ifr_name, "can0" );
    ioctl(sd, SIOCGIFINDEX, &ifr); 
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    // Bind addr to socket.
    bind(sd, (struct sockaddr *)&addr, sizeof(addr));

    // Set filter and mask for can_receive().
/*    if (filter_id != 0)
    {
        rfilter.can_id   = 0x123;
        // CAN_EFF_MASK | CAN_SFF_MASK
        rfilter.can_mask = CAN_SFF_MASK;
        setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));//设置规则：rcan_id & can_mask == can_id & can_mask
    }
*/
    while (1){

        nbytes = read(sd, &frame, sizeof(frame));
        if(nbytes <=0){
            printf("CAN receive failed!");
            exit(EXIT_FAILURE);
        }

        memcpy (&can_recv_que, &frame, sizeof(frame));

        // Ipv6 send thread will go on.
        can_que_flag = 1;

    }
    return 0;
}

// CAN send thread.
void* can_send_thread(void *arg){
    int sd, nbytes = 0;
    struct sockaddr_can addr;
    struct ifreq ifr;

    // Create and init socket.
    sd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    strcpy(ifr.ifr_name, "can0" );
    ioctl(sd, SIOCGIFINDEX, &ifr); 
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    bind(sd, (struct sockaddr *)&addr, sizeof(addr));

    while(1){
        if(ipv6_que_flag == 0){
            continue;
        }
        nbytes = write(sd, &can_send_que, sizeof(can_send_que));
        if(nbytes <= 0)
        {
            printf("CAN send failed!\n");
            exit(EXIT_FAILURE);
        }

        // Stop send() until next ipv6 packet has arraived.
        ipv6_que_flag = 0;
    }

    close(sd);
    return 0;
}