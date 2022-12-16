#include "protocol_translate.h"

// Translate can_frame to ipv6_data.
int can2ipv6_trans(const struct can_frame *frame, uint8_t *ipv6_data){
    uint8_t can_id_tmp[4];
    uint8_t can_dlc_tmp;
    uint8_t __pad_tmp;
    uint8_t __res0_tmp;
    uint8_t __res1_tmp;
    uint8_t data_tmp[CAN_MAX_DLEN];
    int len;
    
    // Save can id to can_dlc_tmp[].
    can_id_tmp[0] = frame->can_id; 
    can_id_tmp[1] = frame->can_id >> 8;
    can_id_tmp[2] = frame->can_id >> 16;
    can_id_tmp[3] = frame->can_id >> 24;

    // Save can_dlc,__pad,__res0,__res1.
    can_dlc_tmp = frame->can_dlc;
    __pad_tmp = frame->__pad;
    __res0_tmp = frame->__res0;
    __res1_tmp = frame->__res1;

    // Save data[CAN_MAX_DLEN] to data_tmp[CAN_MAX_DLEN].
    for(int i = 0; i < CAN_MAX_DLEN; i++){
        data_tmp[i] = frame->data[i];
    }

    // Copy all CAN info to ipv6_data.
    memcpy (ipv6_data, can_id_tmp, 4*sizeof (uint8_t));
    memcpy (ipv6_data + 4, &can_dlc_tmp, sizeof (uint8_t));
    memcpy (ipv6_data + 4 + 1, &__pad_tmp, sizeof (uint8_t));
    memcpy (ipv6_data + 4 + 1 + 1, &__res0_tmp, sizeof (uint8_t));
    memcpy (ipv6_data + 4 + 1 + 1 + 1, &__res1_tmp, sizeof (uint8_t));
    memcpy (ipv6_data + 4 + 1 + 1 + 1 + 1, data_tmp, CAN_MAX_DLEN*sizeof (uint8_t));
    
    //return lenth of the translated data;
    len = 4 + 1 + 1 + 1 + 1 + 8;
    return len;
}

// Translate ipv6_data to can_frame.
int ipv62can_trans(const uint8_t *ipv6_data, struct can_frame *frame){

    // Copy all CAN info to ipv6_data.
    memcpy (&frame->can_id, ipv6_data, 4*sizeof (uint8_t));
    memcpy (&frame->can_dlc, ipv6_data + 4, sizeof (uint8_t));
    memcpy (&frame->__pad, ipv6_data + 4 + 1, sizeof (uint8_t));
    memcpy (&frame->__res0, ipv6_data + 4 + 1 + 1, sizeof (uint8_t));
    memcpy (&frame->__res1, ipv6_data + 4 + 1 + 1 + 1, sizeof (uint8_t));
    memcpy (&frame->data, ipv6_data + 4 + 1 + 1 + 1 + 1, CAN_MAX_DLEN*sizeof (uint8_t));

    //return lenth of the translated data;
    return sizeof(*frame);
}