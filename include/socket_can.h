#pragma once

// Include some files.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>

// Define some constants.
#define command "ip link set can0 type can bitrate 1000000"// Set CAN0 baud rate to 500K. 
#define up "ip link set can0 up"// Open CAN0.                  
#define down "ip link set can0 down"// Close CAN0.


// Function prototypes.
int can_init();                                            // Set and open CAN Interface
int can_send(struct can_frame frame);                      // Send CAN data from can_frame struct
int can_receive(struct can_frame * r_frame,unsigned int filter_id); // Receive data and save to can_frame
int send_cansta(void);                                     // Filling can_frame as sta frame and send.
int send_caneff(void);                                     // Filling can_frame as eff frame and send.
int send_canrtr(void);                                     // Filling can_frame as rtr frame and send.
int rev_can(void);                                         // Receive packet and filling can_frame
float can_get_vol(void);                                   // CAN get value.
void* can_recv_thread(void *arg);                          // CAN receive thread.
void* can_send_thread(void *arg);                           // CAN send thread.
