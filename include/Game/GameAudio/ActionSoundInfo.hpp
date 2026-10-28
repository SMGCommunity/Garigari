#pragma once

#include <revolution.h>

class ActionSoundInfo {
public:
    void fn_8021F470(const char* pName, s32 pitch, s32 velocity, s32 volume) const;
    void fn_8021F490(s32, const char* pName, s32 pitch, s32 velocity, s32 volume) const; // TODO: rename and verify arguments
    void fn_8021F5A0(const char* pName, u32) const;
    void fn_8021F630(const char* pName) const;
};
