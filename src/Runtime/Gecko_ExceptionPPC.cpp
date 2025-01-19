#include <NMWException.h>

#pragma schedule once
#pragma exceptions on

typedef struct ProcessInfo {
	__eti_init_info* exception_info;
	char* TOC;
	int active;
} ProcessInfo;

static ProcessInfo fragmentinfo[1];

int __register_fragment(struct __eti_init_info *info, char *TOC) {
	ProcessInfo* f = fragmentinfo;
	int i;

	for(i = 0; i < 0x20; ++i, ++f) if (f->active == 0)
	{
		f->exception_info = info;
		f->TOC = TOC;
		f->active = 1;
		return i;
	}

	return -1;
}

void __unregister_fragment(int id) {
    ProcessInfo* info;

    if (id <= 0x1Fu) {
        info = &fragmentinfo[id];
        info->exception_info = 0;
        info->TOC = 0;
        info->active = 0;
    }
}
