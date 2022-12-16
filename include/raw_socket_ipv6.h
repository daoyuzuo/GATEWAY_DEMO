#pragma once

// Include some files.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>           // close()
#include <string.h>           // strcpy, memset(), and memcpy()
#include <netdb.h>            // struct addrinfo
#include <sys/types.h>        // needed for socket(), uint8_t, uint16_t
#include <sys/socket.h>       // needed for socket()
#include <netinet/in.h>       // IPPROTO_RAW, IPPROTO_UDP, INET6_ADDRSTRLEN
#include <netinet/ip.h>       // IP_MAXPACKET (which is 65535)
#include <netinet/ip6.h>      // struct ip6_hdr
#include <netinet/udp.h>      // struct udphdr
#include <arpa/inet.h>        // inet_pton() and inet_ntop()
#include <sys/ioctl.h>        // macro ioctl is defined
#include <bits/ioctls.h>      // defines values for argument "request" of ioctl.
#include <net/if.h>           // struct ifreq
#include <linux/if_ether.h>   // ETH_P_IP = 0x0800, ETH_P_IPV6 = 0x86DD
#include <linux/if_packet.h>  // struct sockaddr_ll (see man 7 packet)
#include <net/ethernet.h>
#include <errno.h>            // errno, perror()

// Define some constants.
#define IP6_HDRLEN 40         // IPv6 header length
#define UDP_HDRLEN  8         // UDP header length, excludes data
#define CAN_PORT   8888     // CAN to 5G or ethernet port

// Function prototypes
uint16_t checksum (uint16_t *addr, int len);                            // Computing the internet checksum
uint16_t udp6_checksum (struct ip6_hdr iphdr, struct udphdr udphdr, uint8_t *payload, int payloadlen); // Computing the UDPhdr checksum
char *allocate_strmem (int len);                                            // Allocate memory for an array of chars.
uint8_t *allocate_ustrmem (int len);                                        // Allocate memory for an array of unsigned chars.
int get_localip(const char * eth_name, char *local_ip_addr);            // Get localip by ioctrl()
int get_localmac(const char * interface,char *local_mac_addr);          // Get localmac by ioctrl()
int build_ipv6pkg(char *interface,uint8_t *dst_mac, char *src_ip, char *dst_ip,int src_port,int dst_port,uint8_t *payload, int payloadlen,uint8_t* ether_frame);  //Combines IP header, UDP header and payload into ipv6 frames.
int ipv6pkg_filter(int port, char *src_buf, char *dst_buf, int len);           // Copy the right ipv6 packet to dst_buf from src_buf.
void* ipv6_send_thread(void *arg);                                                    // Ipv6 uplink thread.
void* ipv6_recv_thread(void *arg);                                                  // Ipv6 downlink thread.