#ifndef STDIO_API_H
#define STDIO_API_H

#include "size_t.h"
#include "wchar_t.h"

enum __ReadProcActions {
	__GetAChar,
	__UngetAChar,
	__TestForError
};

enum __WReadProcActions {
	__GetAwChar,
	__UngetAwChar,
	__TestForwcsError
};

typedef struct{
	char* NextChar;
	int NullCharDetected;
} __InStrCtrl;

typedef struct {
	wchar_t * wCharStr;
	size_t MaxCharCount;
	size_t CharsWritten;
} __wOutStrCtrl;

typedef struct {
	wchar_t * wNextChar;
	int    wNullCharDetected;
} __wInStrCtrl;

int __StringRead(void *, int, int);
wint_t __wStringRead(void *, wint_t, int);

#endif // STDIO_API_H