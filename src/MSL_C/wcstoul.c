#include "stdio_api.h"
#include "cctype"
#include "cwctype"
#include "cerrno"
#include "climits"

#define final_state(scan_state) (scan_state & (0x20 | 0x40))
#define success(scan_state) (scan_state & (0x4 | 0x10 | 0x20))
#define fetch() (count++, (*wReadProc)(wReadProcArg, 0, __GetAwChar))
#define unfetch(c) (*wReadProc)(wReadProcArg, c, __UngetAwChar)

unsigned long __wcstoul(int base, int max_width, wint_t (*wReadProc)(void*, wint_t, int), void* wReadProcArg, int* chars_scanned, int* negative, int* overflow) {
    int scan_state = 1;
    int count = 0;
    int spaces = 0;
    unsigned long value = 0;
    unsigned long value_max = 0;
    wchar_t c;

    *negative = *overflow = 0;

    if (base < 0 || base == 1 || base > 36 || max_width < 1) {
        scan_state = 0x40;
    } else {
        c = fetch();
    }

    if (base) {
        value_max = ULONG_MAX / base;
    }

    while (count <= max_width && c != -1 && !final_state(scan_state)) {
        switch (scan_state) {
        case 0x1:
            if (iswspace(c)) {
                c = fetch();
                count--;
                spaces++;
                break;
            }

            if (c == L'+') {
                c = fetch();
            } else if (c == L'-') {
                c = fetch();
                *negative = 1;
            }

            scan_state = 0x2;
            break;
        case 0x2:
            if (base == 0 || base == 16) {
                if (c == L'0') {
                    scan_state = 0x4;
                    c = fetch();
                    break;
                }
            }

            scan_state = 0x8;
            break;
        case 0x4:
            if (c == L'X' || c == L'x') {
                base = 16;
                scan_state = 0x8;
                c = fetch();
                break;
            }

            if (base == 0) {
                base = 8;
            }

            scan_state = 0x10;
            break;
        case 0x8:
        case 0x10:
            if (base == 0) {
                base = 10;
            }

            if (!value_max) {
                value_max = ULONG_MAX / base;
            }

            if (iswdigit(c)) {
                if ((c -= L'0') >= base) {
                    if (scan_state == 0x10) {
                        scan_state = 0x20;
                    } else {
                        scan_state = 0x40;
                    }

                    c += L'0';
                    break;
                }
            } else if (!iswalpha(c) || (toupper(c) - L'A' + 10) >= base) {
                if (scan_state == 0x10) {
                    scan_state = 0x20;
                } else {
                    scan_state = 0x40;
                }

                break;
            } else {
                c = towupper(c) - L'A' + 10;
            }

            if (value > value_max) {
                *overflow = 1;
            }

            value *= base;

            if (c > (ULONG_MAX - value)) {
                *overflow = 1;
            }

            value += c;
            scan_state = 0x10;
            c = fetch();
            break;
        }
    }

    if (!success(scan_state)) {
        count = 0;
        value = 0;
        *chars_scanned = 0;
    } else {
        count--;
        *chars_scanned = count + spaces;
    }

    unfetch(c);
    return value;
}

long wcstol(const wchar_t* str, wchar_t** end, int base) {
    unsigned long uvalue;
    long svalue;
    int count, negative, overflow;
    __wInStrCtrl wisc;

    wisc.wNextChar = (wchar_t*)str;
    wisc.wNullCharDetected = 0;

    uvalue = __wcstoul(base, INT_MAX, &__wStringRead, (void*)&wisc, &count, &negative, &overflow);

    if (end) {
        *end = (wchar_t*)str + count;
    }

    if (overflow || (!negative && uvalue > LONG_MAX) || (negative && uvalue > -LONG_MIN)) {
        svalue = (negative ? -LONG_MIN : LONG_MAX);
        errno = 0x22;
    } else {
        svalue = negative ? (long)-uvalue : (long)uvalue;
    }

    return svalue;
}
