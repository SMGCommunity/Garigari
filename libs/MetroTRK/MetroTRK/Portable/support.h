#ifndef METROTRK_PORTABLE_SUPPORT_H
#define METROTRK_PORTABLE_SUPPORT_H

#include "trk.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TRKBuffer TRKBuffer;

DSError TRKRequestSend(TRKBuffer* msgBuf, int* bufferId);

#ifdef __cplusplus
}
#endif

#endif /* METROTRK_PORTABLE_SUPPORT_H */
