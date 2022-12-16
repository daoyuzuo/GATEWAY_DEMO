#pragma once

// Include some files.
#include "socket_can.h"
#include "raw_socket_ipv6.h"

// Define some constants.

// Function prototypes.

// Translate can_frame to ipv6_data.
int can2ipv6_trans(const struct can_frame *frame, uint8_t *ipv6_data);
int ipv62can_trans(const uint8_t *ipv6_data, struct can_frame *frame);