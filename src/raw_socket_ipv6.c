#include "raw_socket_ipv6.h"
#include <linux/can.h>
#include "protocol_translate.h"
#include "config.h"

extern struct can_frame can_recv_que;
extern uint8_t *ipv6_send_que;
extern struct can_frame can_send_que;
extern int can_que_flag,ipv6_que_flag;

// Computing the internet checksum (RFC 1071).
// Note that the internet checksum is not guaranteed to preclude collisions.
uint16_t
checksum (uint16_t *addr, int len) {

  int count = len;
  register uint32_t sum = 0;
  uint16_t answer = 0;

  // Sum up 2-byte values until none or only one byte left.
  while (count > 1) {
    sum += *(addr++);
    count -= 2;
  }

  // Add left-over byte, if any.
  if (count > 0) {
    sum += *(uint8_t *) addr;
  }

  // Fold 32-bit sum into 16 bits; we lose information by doing this,
  // increasing the chances of a collision.
  // sum = (lower 16 bits) + (upper 16 bits shifted right 16 bits)
  while (sum >> 16) {
    sum = (sum & 0xffff) + (sum >> 16);
  }

  // Checksum is one's compliment of sum.
  answer = ~sum;

  return (answer);
}

// Build IPv6 UDP pseudo-header and call checksum function (Section 8.1 of RFC 2460).
uint16_t
udp6_checksum (struct ip6_hdr iphdr, struct udphdr udphdr, uint8_t *payload, int payloadlen) {

  char buf[IP_MAXPACKET];
  char *ptr;
  int chksumlen = 0;
  int i;

  ptr = &buf[0];  // ptr points to beginning of buffer buf

  // Copy source IP address into buf (128 bits)
  memcpy (ptr, &iphdr.ip6_src.s6_addr, sizeof (iphdr.ip6_src.s6_addr));
  ptr += sizeof (iphdr.ip6_src.s6_addr);
  chksumlen += sizeof (iphdr.ip6_src.s6_addr);

  // Copy destination IP address into buf (128 bits)
  memcpy (ptr, &iphdr.ip6_dst.s6_addr, sizeof (iphdr.ip6_dst.s6_addr));
  ptr += sizeof (iphdr.ip6_dst.s6_addr);
  chksumlen += sizeof (iphdr.ip6_dst.s6_addr);

  // Copy UDP length into buf (32 bits)
  memcpy (ptr, &udphdr.len, sizeof (udphdr.len));
  ptr += sizeof (udphdr.len);
  chksumlen += sizeof (udphdr.len);

  // Copy zero field to buf (24 bits)
  *ptr = 0; ptr++;
  *ptr = 0; ptr++;
  *ptr = 0; ptr++;
  chksumlen += 3;

  // Copy next header field to buf (8 bits)
  memcpy (ptr, &iphdr.ip6_nxt, sizeof (iphdr.ip6_nxt));
  ptr += sizeof (iphdr.ip6_nxt);
  chksumlen += sizeof (iphdr.ip6_nxt);

  // Copy UDP source port to buf (16 bits)
  memcpy (ptr, &udphdr.source, sizeof (udphdr.source));
  ptr += sizeof (udphdr.source);
  chksumlen += sizeof (udphdr.source);

  // Copy UDP destination port to buf (16 bits)
  memcpy (ptr, &udphdr.dest, sizeof (udphdr.dest));
  ptr += sizeof (udphdr.dest);
  chksumlen += sizeof (udphdr.dest);

  // Copy UDP length again to buf (16 bits)
  memcpy (ptr, &udphdr.len, sizeof (udphdr.len));
  ptr += sizeof (udphdr.len);
  chksumlen += sizeof (udphdr.len);

  // Copy UDP checksum to buf (16 bits)
  // Zero, since we don't know it yet
  *ptr = 0; ptr++;
  *ptr = 0; ptr++;
  chksumlen += 2;

  // Copy payload to buf
  memcpy (ptr, payload, payloadlen * sizeof (uint8_t));
  ptr += payloadlen;
  chksumlen += payloadlen;

  // Pad to the next 16-bit boundary
  for (i=0; i<payloadlen%2; i++, ptr++) {
    *ptr = 0;
    ptr++;
    chksumlen++;
  }

  return checksum ((uint16_t *) buf, chksumlen);
}

// Allocate memory for an array of chars.
char *
allocate_strmem (int len) {

  void *tmp;

  if (len <= 0) {
    fprintf (stderr, "ERROR: Cannot allocate memory because len = %i in allocate_strmem().\n", len);
    exit (EXIT_FAILURE);
  }

  tmp = (char *) malloc (len * sizeof (char));
  if (tmp != NULL) {
    memset (tmp, 0, len * sizeof (char));
    return (tmp);
  } else {
    fprintf (stderr, "ERROR: Cannot allocate memory for array allocate_strmem().\n");
    exit (EXIT_FAILURE);
  }
}

// Allocate memory for an array of unsigned chars.
uint8_t *
allocate_ustrmem (int len) {

  void *tmp;

  if (len <= 0) {
    fprintf (stderr, "ERROR: Cannot allocate memory because len = %i in allocate_ustrmem().\n", len);
    exit (EXIT_FAILURE);
  }

  tmp = (uint8_t *) malloc (len * sizeof (uint8_t));
  if (tmp != NULL) {
    memset (tmp, 0, len * sizeof (uint8_t));
    return (tmp);
  } else {
    fprintf (stderr, "ERROR: Cannot allocate memory for array allocate_ustrmem().\n");
    exit (EXIT_FAILURE);
  }
}

// Get localip by ioctrl()
int get_localip(const char * eth_name, char *local_ip_addr)
{
	int ret = -1;
    register int fd;
    struct ifreq ifr;
 
	if (local_ip_addr == NULL || eth_name == NULL) {
		return ret;
	}
 
	if ((fd=socket(AF_INET, SOCK_DGRAM, 0)) > 0) {
		strcpy(ifr.ifr_name, eth_name);
		if (!(ioctl(fd, SIOCGIFADDR, &ifr))) {
			ret = 0;
			strcpy(local_ip_addr, inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
		}
	}
 
	if (fd > 0) {
		close(fd);
	}
    return ret;
}

// Get localmac by ioctrl() return 1 fail,0 success.
int get_localmac(const char * interface,char *local_mac_addr){
  register int fd;
  struct ifreq ifr;
  int ret = 0;
  // Submit request for a socket descriptor to look up interface.
  if ((fd = socket (PF_PACKET, SOCK_DGRAM, IPPROTO_RAW)) < 0) {
    perror ("socket() failed to get socket descriptor for using ioctl() ");
    exit (EXIT_FAILURE);
  }
  // Use ioctl() to look up interface name and get its MAC address.
  memset (&ifr, 0, sizeof (ifr));
  snprintf (ifr.ifr_name, sizeof (ifr.ifr_name), "%s", interface);
  if (ioctl (fd, SIOCGIFHWADDR, &ifr) < 0) {
    perror ("ioctl() failed to get source MAC address ");
    return (EXIT_FAILURE);
  }
  close (fd);

  // Copy source MAC address.
  memcpy (local_mac_addr, ifr.ifr_hwaddr.sa_data, 6 * sizeof (uint8_t));

  // Report source MAC address to stdout.
  printf ("MAC address for interface %s is ", interface);

  for (int i=0; i<5; i++) {
    printf ("%02x:", local_mac_addr[i]);
  }
  printf ("%02x\n", local_mac_addr[5]);

  return ret;
}

// Combines IP header, UDP header and payload into ipv6 frames.
int build_ipv6pkg(char *interface,uint8_t *dst_mac, char *src_ip, char *dst_ip,\
int src_port,int dst_port,uint8_t *payload, int payloadlen,uint8_t* ether_frame){
  
  uint8_t *src_mac;
  struct ip6_hdr iphdr;
  struct udphdr udphdr;
  struct addrinfo hints, *res;
  struct sockaddr_in6 *ipv6;
  void *tmp;

  // Record error
  int status,frame_length; 
  status = 0;
  src_mac = allocate_ustrmem (6);
  if(get_localmac(interface,(char*)src_mac)!=0){
    printf("can not get localmac");
  }
  free (src_mac);

  // Fill out hints for getaddrinfo().
  memset (&hints, 0, sizeof (hints));
  hints.ai_family = AF_INET6;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = hints.ai_flags | AI_CANONNAME;

  // Resolve target using getaddrinfo().
  if ((status = getaddrinfo (dst_ip, NULL, &hints, &res)) != 0) {
    fprintf (stderr, "getaddrinfo() failed for target: %s\n", gai_strerror (status));
    exit (EXIT_FAILURE);
  }
  ipv6 = (struct sockaddr_in6 *) res->ai_addr;
  tmp = &(ipv6->sin6_addr);
  if (inet_ntop (AF_INET6, tmp, dst_ip, INET6_ADDRSTRLEN) == NULL) {
    status = errno;
    fprintf (stderr, "inet_ntop() failed for target.\nError message: %s", strerror (status));
    exit (EXIT_FAILURE);
  }
  freeaddrinfo (res);
  
  // IPv6 header
  // IPv6 version (4 bits), Traffic class (8 bits), Flow label (20 bits)
  iphdr.ip6_flow = htonl ((6 << 28) | (0 << 20) | 0);

  // Payload length (16 bits): UDP header + UDP data
  iphdr.ip6_plen = htons (UDP_HDRLEN + payloadlen);

  // Next header (8 bits): 17 for UDP
  iphdr.ip6_nxt = IPPROTO_UDP;

  // Hop limit (8 bits): default to maximum value
  iphdr.ip6_hops = 255;

  // Source IPv6 address (128 bits)
  if ((status = inet_pton (AF_INET6, src_ip, &(iphdr.ip6_src))) != 1) {
    fprintf (stderr, "inet_pton() failed for source address.\nError message: %s", strerror (status));
    exit (EXIT_FAILURE);
  }

  // Destination IPv6 address (128 bits)
  if ((status = inet_pton (AF_INET6, dst_ip, &(iphdr.ip6_dst))) != 1) {
    fprintf (stderr, "inet_pton() failed for destination address.\nError message: %s", strerror (status));
    exit (EXIT_FAILURE);
  }
  
  // UDP header

  // Source port number (16 bits): pick a number
  udphdr.source = htons (src_port);

  // Destination port number (16 bits): pick a number
  udphdr.dest = htons (dst_port);

  // Length of UDP datagram (16 bits): UDP header + UDP data
  udphdr.len = htons (UDP_HDRLEN + payloadlen);

  // UDP checksum (16 bits)
  udphdr.check = udp6_checksum (iphdr, udphdr, payload, payloadlen);

  // Fill out ethernet frame header.

  // Ethernet frame length = ethernet data (IP header + UDP header + UDP data)
  frame_length = IP6_HDRLEN + UDP_HDRLEN + payloadlen;



  
  // IPv6 header
  memcpy (ether_frame, &iphdr, IP6_HDRLEN * sizeof (uint8_t));

  // UDP header
  memcpy (ether_frame + IP6_HDRLEN, &udphdr, UDP_HDRLEN * sizeof (uint8_t));

  // UDP data
  memcpy (ether_frame + IP6_HDRLEN + UDP_HDRLEN, payload, payloadlen * sizeof (uint8_t));

  frame_length = IP6_HDRLEN + UDP_HDRLEN + payloadlen;

  return frame_length;
}

// Copy the right ipv6 packet to dst_buf from src_buf.
int ipv6pkg_filter(int port, char *src_buf, char *dst_buf, int len){
  char *a = (char*)malloc(2); 
  a[0] = 0x22;
  a[1] = 0xb8;
  int status = 1;

  // Calculate Byte position of dst_port.
  if((src_buf[IP6_HDRLEN+2]==a[0])&&(src_buf[IP6_HDRLEN+3]==a[1]))
  memcpy (dst_buf, src_buf, len);
  else{
    status = 0;
  }
  free(a);
  return status;
}

//----------------------------------------------------------------------------------------------------//
// Follow code is about ipv6 thread.

// Ipv6 send thread.
void* ipv6_send_thread(void *arg){
  int datalen, bytes,src_port,dst_port,sd,frame_length;
  char *interface, *src_ip, *dst_ip;
  uint8_t *dst_mac, *ether_frame;
  struct sockaddr_ll device;

  // Allocate memory for various arrays.
  dst_mac = allocate_ustrmem (6);
  ether_frame = allocate_ustrmem (IP_MAXPACKET);
  interface = allocate_strmem (INET6_ADDRSTRLEN);
  src_ip = allocate_strmem (INET6_ADDRSTRLEN);
  dst_ip = allocate_strmem (INET6_ADDRSTRLEN);

  // Interface to send packet through.
  strcpy (interface, INTERFACE_ONE);

  // Set destination MAC address: you need to fill this out
  dst_mac[0] = 0xff;
  dst_mac[1] = 0xff;
  dst_mac[2] = 0xff;
  dst_mac[3] = 0xff;
  dst_mac[4] = 0xff;
  dst_mac[5] = 0xff;

  // Source IPv6 address: you need to fill this out
  strcpy (src_ip, LOCAL_IPV6ADDR);

  // Destination URL or IPv6 address: you need to fill this out
  strcpy (dst_ip, REMOTE_IPV6ADDR);

  // UDP data
//  datalen = 4;
//  data[0] = 'T';
//  data[1] = 'e';
//  data[2] = 's';
//  data[3] = 't';
  src_port = LOCAL_PORT;
  dst_port = REMOTE_PORT;

  // Find interface index from interface name and store index in
  // struct sockaddr_ll device, which will be used as an argument of sendto().
  memset (&device, 0, sizeof (device));
  if ((device.sll_ifindex = if_nametoindex (interface)) == 0) {
    perror ("if_nametoindex() failed to obtain interface index ");
    exit(EXIT_FAILURE);
  }
  printf ("Index for interface %s is %i\n", interface, device.sll_ifindex);

    // Fill out sockaddr_ll.
  device.sll_family = AF_PACKET;
  device.sll_protocol = htons (ETH_P_IPV6);
  memcpy (device.sll_addr, dst_mac, 6 * sizeof (uint8_t));
  device.sll_halen = 6;

  // Open raw socket descriptor.
  if ((sd = socket (PF_PACKET, SOCK_DGRAM, htons (ETH_P_ALL))) < 0) {
    perror ("socket() failed ");
    exit(EXIT_FAILURE);
  }
  
  while(1){
    
    if(can_que_flag == 0){
      continue;
    }
    // Translate CAN to IPV6 and insert to ipv6_send_que.
    datalen = can2ipv6_trans(&can_recv_que, ipv6_send_que);

    // Combines IP header, UDP header and payload into ipv6 frames.
    frame_length = build_ipv6pkg(interface, dst_mac, src_ip, dst_ip, src_port, dst_port, ipv6_send_que, datalen, ether_frame);

    // Send ethernet frame to socket.
    if ((bytes = sendto (sd, ether_frame, frame_length, 0, (struct sockaddr *) &device, sizeof (device))) <= 0) {
    perror ("sendto() failed");
    exit(EXIT_FAILURE);
    }
    printf("send\n");

    // Stop send() until next CAN message has arraived.
    can_que_flag = 0;
  }

  close (sd);

  // Free allocated memory.
  free (dst_mac);
  free (ether_frame);
  free (interface);
  free (src_ip);
  free (dst_ip);

  exit(EXIT_SUCCESS);
}




// Ipv6 receive thread.
void* ipv6_recv_thread(void *arg){

  int bytes, rd, len;
  uint8_t *recv_buf, *port1_buf;
  struct sockaddr_ll recv_device;

  // Allocate memory for various arrays.
  recv_buf = allocate_ustrmem(IP_MAXPACKET);
  port1_buf = allocate_ustrmem(IP_MAXPACKET);

  //set recv_device to 0
  memset(&recv_device, 0, sizeof(recv_device));
  len = sizeof(recv_device);

  //create socket
  if ((rd = socket (PF_PACKET, SOCK_DGRAM, htons (ETH_P_ALL))) < 0) {
    perror ("socket() failed ");
    exit(EXIT_FAILURE);
  }

  while (1)
  {
    if ((bytes = recvfrom(rd, recv_buf, IP_MAXPACKET, 0, (struct sockaddr *)&recv_device, &len)) <= 0)
    {
      perror("recvfrom() failed");
      exit(EXIT_FAILURE);
    }

    // If receive packet which has port 8888 ,save and work with it.
    if(ipv6pkg_filter(CAN_PORT, recv_buf, port1_buf, bytes*sizeof(char))){

      ipv62can_trans(recv_buf+IP6_HDRLEN + UDP_HDRLEN,&can_send_que);

#ifdef DEBUG 
      for (int i = 0; i < bytes; i++)
      printf("Receive ipv6 packet:\n","%02x ", recv_buf[i]);
      printf("                      \n");
#endif

      // CAN send thread will go on.
      ipv6_que_flag = 1;
    }
  }

  free (recv_buf);
  free (port1_buf);

  exit(EXIT_SUCCESS) ;
}
