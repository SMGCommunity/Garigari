#pragma once

#include <revolution.h>

namespace MR {
    void copyString(char *, const char *, u32);

    const char* getBasename(const char *);
    void removeExtensionString(char *, u32, const char *);

    bool isEqualString(const char *, const char *);
    bool isEqualStringCase(const char *, const char *);
    bool isEqualSubString(const char *, const char *);
    bool hasStringSpace(const char *);

    bool isNullOrEmptyString(const char *);
};
