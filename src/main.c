#include "raw_socket_ipv6.h"
#include "socket_can.h"
#include "protocol_convert.h"
#include "protocol_translate.h"
#include <pthread.h>
/*
int main (int argc, char **argv){

}
*/

struct can_frame can_recv_que;
uint8_t *ipv6_send_que;
struct can_frame can_send_que;
int can_que_flag;
int ipv6_que_flag;


int main (int argc, char **argv) {
    
    // Init global param.
    memset(&can_recv_que,0,sizeof(can_recv_que));
    memset(&can_send_que,0,sizeof(can_send_que));
    ipv6_send_que = allocate_ustrmem (IP_MAXPACKET);
    can_que_flag = 0;
    ipv6_que_flag = 0;
    
    // Init CAN interface.
    can_init();

    int res;

    // Create pthread_t for thread.
    pthread_t IPV6_SEND_THREAD, IPV6_RECV_THREAD, CAN_RECV_THREAD, CAN_SEND_THREAD;
    void* thread_result;

    // IPV6_SEND_THREAD :form the data from global buffer into ipv6 packet and execute sendto().
    res = pthread_create(&IPV6_SEND_THREAD, NULL, ipv6_send_thread, NULL);
    if (res != 0) {
        printf("Create IPV6_SEND_THREAD failed!");
        return 0;
    }

    // IPV6_RECV_THREAD :receive the ipv6 packet and unpack it into global buffer.
    res = pthread_create(&IPV6_RECV_THREAD, NULL, ipv6_recv_thread, NULL);
    if (res != 0) {
        printf("Create IPV6_RECV_THREAD failed!");
        return 0;
    }

    // CAN_RECV_THREAD :receive the CAN packet and unpack it into global buffer.
    res = pthread_create(&CAN_RECV_THREAD, NULL, can_recv_thread, NULL);
    if (res != 0) {
        printf("Create CAN_RECV_THREAD failed!");
        return 0;
    }

    // CAN_SEND_THREAD :form the data from global buffer into CAN message and execute write().
    res = pthread_create(&CAN_SEND_THREAD, NULL, can_send_thread, NULL);
    if (res != 0) {
        printf("Create CAN_SEND_THREAD failed!");
        return 0;
    }

    // Block main thread and print result of other thread.
    res = pthread_join(IPV6_SEND_THREAD, &thread_result);
    printf("%s\n", (char *)thread_result);
    res = pthread_join(IPV6_RECV_THREAD, &thread_result);
    printf("%s\n", (char *)thread_result);
    res = pthread_join(CAN_RECV_THREAD, &thread_result);
    printf("%s\n", (char *)thread_result);
    res = pthread_join(CAN_SEND_THREAD, &thread_result);
    printf("%s\n", (char *)thread_result);

    printf("process has all exited");
    return 0;
}



