#pragma once

#include "Game/MapObj/MapPartsFunction.hpp"
#include "Game/Util/Array.hpp"

class MapPartsRailGuidePoint;

class MapPartsRailGuideDrawer : public MapPartsFunction {
public:
    MapPartsRailGuideDrawer(LiveActor* pHost, const char* pModelName);

    virtual void init(const JMapInfoIter& rIter);
    virtual bool isWorking() const;
    virtual void start();
    virtual void end();

    void initGuidePoints(const JMapInfoIter& rIter);

    void show();
    void hide();
    void exeHideAll();
    void exeDrawAll();
    void exeDrawForward();

    /* 0x028 */ MR::Vector< MR::FixedArray< MapPartsRailGuidePoint*, 256 > > mGuidePoints;
    /* 0x42C */ s32 mGuideType;
    /* 0x430 */ s32 mRailId;
    /* 0x434 */ const char* mModelName;
};
