#ifndef METROTRK_PORTABLE_SERPOLL_H
#define METROTRK_PORTABLE_SERPOLL_H


#ifdef __cplusplus
extern "C" {
#endif

void TRKGetInput(void);
void TRKProcessInput(int bufferIdx);

extern void* gTRKInputPendingPtr;

#ifdef __cplusplus
}
#endif

#endif /* METROTRK_PORTABLE_SERPOLL_H */
