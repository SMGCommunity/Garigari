#ifndef DVD_H
#define DVD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <revolution/types.h>

typedef struct {
    u32 entryNum;
    u32 location;
    u32 next;
} DVDDir;

typedef struct {
    u32 entryNum;
    BOOL isDir;
    char* name;
} DVDDirEntry;

BOOL DVDOpenDir(const char *, DVDDir *);
BOOL DVDReadDir(DVDDir *, DVDDirEntry *);
BOOL DVDCloseDir(DVDDir *);

#ifdef __cplusplus
}
#endif

#endif // DVD_H
