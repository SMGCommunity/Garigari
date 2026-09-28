#include "stdio_api.h"

wint_t __wStringRead(void* isc, wint_t ch, int Action) {
    wchar_t ret;
    __wInStrCtrl* Iscp = (__wInStrCtrl*)isc;

    switch (Action) {
    case __GetAwChar:
        ret = *(Iscp->wNextChar);
        if (ret == 0) {
            Iscp->wNullCharDetected = 1;
            return 0xFFFF;
        } else {
            Iscp->wNextChar++;
            return ret;
        }
    case __UngetAwChar:
        if (!Iscp->wNullCharDetected) {
            Iscp->wNextChar--;
        } else {
            Iscp->wNullCharDetected = 0;
        }
        return ch;
    case __TestForwcsError:
        return Iscp->wNullCharDetected;
    }

    return 0;
}
