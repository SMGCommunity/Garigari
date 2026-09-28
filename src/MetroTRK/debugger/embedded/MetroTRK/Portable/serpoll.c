#include "MetroTRK/Portable/serpoll.h"
#include "MetroTRK/Portable/nubevent.h"
#include "trk.h"

void* gTRKInputPendingPtr;

MessageBufferID TRKTestForPacket() {
    u8 payloadBuf[0x880];
    u8 packetBuf[0x40];
    int bufID;
    TRKBuffer* msg;
    MessageBufferID result;

    if (TRKPollUART() <= 0) {
        return -1;
    }

    result = TRKGetFreeBuffer(&bufID, &msg);

    TRKSetBufferPosition(msg, 0);
    if (TRKReadUARTN(packetBuf, 0x40) == UART_NoError) {
        int readSize;

        TRKAppendBuffer_ui8(msg, packetBuf, 0x40);
        readSize = ((u32*)packetBuf)[0] - 0x40;
        result = bufID;
        if (readSize > 0) {
            if (TRKReadUARTN(payloadBuf, ((u32*)packetBuf)[0] - 0x40) == UART_NoError) {
                TRKAppendBuffer_ui8(msg, payloadBuf, ((u32*)packetBuf)[0]);
            } else {
                TRKReleaseBuffer(result);
                result = -1;
            }
        }
    } else {
        TRKReleaseBuffer(result);
        result = -1;
    }

    return result;
}

void TRKGetInput(void) {
    MessageBufferID id = TRKTestForPacket();
    if (id != -1) {
        TRKProcessInput(id);
    }
}

void TRKProcessInput(int bufferIdx) {
    TRKEvent event;

    TRKConstructEvent(&event, NUBEVENT_Request);
    event.msgBufID = bufferIdx;
    TRKPostEvent(&event);
}

DSError TRKInitializeSerialHandler() {
    return DS_NoError;
}

DSError TRKTerminateSerialHandler(void) {
    return DS_NoError;
}
