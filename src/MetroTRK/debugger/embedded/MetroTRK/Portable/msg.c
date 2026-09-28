/**
 * msg.c
 * Description:
 */

#include "MetroTRK/Portable/msg.h"
#include "trk.h"

static u16 gPacketSeq;

DSError TRKMessageSend(TRKBuffer* msg) {
    DSError write_err;
    u16 seq = gPacketSeq;

    if (seq == 0) {
        seq = 1;
    }

    *(u16*)(msg->data + 6) = seq;
    gPacketSeq = (seq & 0xFFFF) + 1;

    write_err = TRKWriteUARTN(msg->data, msg->length);
    if (write_err != DS_NoError) {
        OSReport("MetroTRK - TRK_WriteUARTN returned %ld\n", write_err);
    }

    return DS_NoError;
}
