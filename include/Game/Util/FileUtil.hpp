#pragma once

#include <JKernel/JKRArchive.hpp>

namespace MR {
    JKRArchive* mountAsyncArchive(const char *);

    void makeScenarioArchiveFileName(char *, u32, const char *);

    bool isFileExist(const char *, bool);
};
