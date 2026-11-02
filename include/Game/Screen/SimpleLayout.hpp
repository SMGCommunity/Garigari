#pragma once

#include "Game/Screen/LayoutActor.hpp"

class TalkTextFormer;

class SimpleLayout : public LayoutActor {
public:
    SimpleLayout(const char*, const char*, u32, int);
};

class SimpleEffectLayout : public SimpleLayout {
public:
    SimpleEffectLayout(const char*, const char*, u32, int);
};

class SimpleTalkTextLayout : public SimpleLayout {
public:
    SimpleTalkTextLayout(const char*, const char*, u32);

    void startTalk(const char* pMessageId);
    void endTalk();

    void exeStart();
    void exeUpdate();
    void exeEnd();

    /* 0x2C */ TalkTextFormer* mFormerText;
};
