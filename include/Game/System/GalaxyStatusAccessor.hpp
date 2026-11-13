#pragma once

#include <revolution.h>

class ScenarioData;

class GalaxyStatusAccessor {
public:
    GalaxyStatusAccessor(const ScenarioData*);

    const char* getName() const;
    s32 getPowerStarNum() const;

	bool isCompletedNoGreen() const;
    bool isCompletedWithGreen() const;

    s32 getWorldNo() const;

    /* 0x00 */ const ScenarioData* mScenarioData;
};
