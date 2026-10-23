#pragma once

#include <JSystem/JGeometry/TVec.hpp>

class PlanetGravity;
class JMapInfoIter;
class BarrelGravity;
class CubeGravity;
class DiskGravity;
class DiskTorusGravity;
class ConeGravity;
class ParallelGravity;
class PointGravity;
class SegmentGravity;
class RailRider;
class WireGravity;

class GravityCreator {
public:
    GravityCreator();

    virtual PlanetGravity* getGravity() = 0;
    virtual PlanetGravity* createInstance() = 0;
    virtual void settingFromSRT(const TVec3f& rTrans, const TVec3f& rRotate, const TVec3f& rScale);
    virtual void settingFromJMapArgs(s32 arg0, s32 arg1, s32 arg2);
    virtual void settingFromJMapOtherParam(const JMapInfoIter& rIter);

    PlanetGravity* createFromJMap(const JMapInfoIter& rIter);
};

class BarrelGravityCreator : public GravityCreator {
public:
    BarrelGravityCreator() : GravityCreator(), mGravityInstance() {
    }

    virtual PlanetGravity* getGravity();
    virtual PlanetGravity* createInstance();
    virtual void settingFromSRT(const TVec3f& rTrans, const TVec3f& rRotate, const TVec3f& rScale);
    virtual void settingFromJMapArgs(s32, s32, s32);

    /* 0x4 */ BarrelGravity* mGravityInstance;
};

class CubeGravityCreator : public GravityCreator {
public:
    CubeGravityCreator() : GravityCreator(), mGravityInstance() {
    }

    virtual PlanetGravity* getGravity();
    virtual PlanetGravity* createInstance();
    virtual void settingFromSRT(const TVec3f& rTrans, const TVec3f& rRotate, const TVec3f& rScale);
    virtual void settingFromJMapArgs(s32 arg0, s32 arg1, s32 arg2);

    /* 0x4 */ CubeGravity* mGravityInstance;
};

class DiskGravityCreator : public GravityCreator {
public:
    DiskGravityCreator() : GravityCreator(), mGravityInstance() {
    }

    virtual PlanetGravity* getGravity();
    virtual PlanetGravity* createInstance();
    virtual void settingFromSRT(const TVec3f& rTrans, const TVec3f& rRotate, const TVec3f& rScale);
    virtual void settingFromJMapArgs(s32 arg0, s32 arg1, s32 arg2);

    /* 0x4 */ DiskGravity* mGravityInstance;
};

class DiskTorusGravityCreator : public GravityCreator {
public:
    DiskTorusGravityCreator() : GravityCreator(), mGravityInstance() {
    }

    virtual PlanetGravity* getGravity();
    virtual PlanetGravity* createInstance();
    virtual void settingFromSRT(const TVec3f& rTrans, const TVec3f& rRotate, const TVec3f& rScale);
    virtual void settingFromJMapArgs(s32 arg0, s32 arg1, s32 arg2);

    /* 0x4 */ DiskTorusGravity* mGravityInstance;
};

class ConeGravityCreator : public GravityCreator {
public:
    ConeGravityCreator() : GravityCreator(), mGravityInstance() {
    }

    virtual PlanetGravity* getGravity();
    virtual PlanetGravity* createInstance();
    virtual void settingFromSRT(const TVec3f& rTrans, const TVec3f& rRotate, const TVec3f& rScale);
    virtual void settingFromJMapArgs(s32 arg0, s32 arg1, s32 arg2);

    /* 0x4 */ ConeGravity* mGravityInstance;
};

class PlaneGravityCreator : public GravityCreator {
public:
    PlaneGravityCreator() : GravityCreator(), mGravityInstance() {
    }

    virtual PlanetGravity* getGravity();
    virtual PlanetGravity* createInstance();
    virtual void settingFromSRT(const TVec3f& rTrans, const TVec3f& rRotate, const TVec3f& rScale);

    /* 0x4 */ ParallelGravity* mGravityInstance;
};

class PlaneInBoxGravityCreator : public GravityCreator {
public:
    PlaneInBoxGravityCreator() : GravityCreator(), mGravityInstance() {
    }

    virtual PlanetGravity* getGravity();
    virtual PlanetGravity* createInstance();
    virtual void settingFromSRT(const TVec3f& rTrans, const TVec3f& rRotate, const TVec3f& rScale);
    virtual void settingFromJMapArgs(s32 arg0, s32 arg1, s32 arg2);

    /* 0x4 */ ParallelGravity* mGravityInstance;
};

class PlaneInCylinderGravityCreator : public GravityCreator {
public:
    PlaneInCylinderGravityCreator() : GravityCreator(), mGravityInstance() {
    }

    virtual PlanetGravity* getGravity();
    virtual PlanetGravity* createInstance();
    virtual void settingFromSRT(const TVec3f& rTrans, const TVec3f& rRotate, const TVec3f& rScale);
    virtual void settingFromJMapArgs(s32 arg0, s32 arg1, s32 arg2);

    /* 0x4 */ ParallelGravity* mGravityInstance;
};

class PlaneZeroGravityCreator : public PlaneGravityCreator {
public:
    PlaneZeroGravityCreator() : PlaneGravityCreator() {};

    virtual PlanetGravity* getGravity();
    virtual PlanetGravity* createInstance();
    virtual void settingFromSRT(const TVec3f& rTrans, const TVec3f& rRotate, const TVec3f& rScale);
};

class PlaneZeroInBoxGravityCreator : public PlaneInBoxGravityCreator {
public:
    PlaneZeroInBoxGravityCreator() : PlaneInBoxGravityCreator() {};

    virtual PlanetGravity* getGravity();
    virtual PlanetGravity* createInstance();
    virtual void settingFromSRT(const TVec3f& rTrans, const TVec3f& rRotate, const TVec3f& rScale);
    virtual void settingFromJMapArgs(s32 arg0, s32 arg1, s32 arg2);
};

class PlaneZeroInCylinderGravityCreator : public PlaneInCylinderGravityCreator {
public:
    PlaneZeroInCylinderGravityCreator() : PlaneInCylinderGravityCreator() {};

    virtual PlanetGravity* getGravity();
    virtual PlanetGravity* createInstance();
    virtual void settingFromSRT(const TVec3f& rTrans, const TVec3f& rRotate, const TVec3f& rScale);
    virtual void settingFromJMapArgs(s32 arg0, s32 arg1, s32 arg2);
};

class PointGravityCreator : public GravityCreator {
public:
    PointGravityCreator() : GravityCreator(), mGravityInstance() {
    }

    virtual PlanetGravity* getGravity();
    virtual PlanetGravity* createInstance();
    virtual void settingFromSRT(const TVec3f& rTrans, const TVec3f& rRotate, const TVec3f& rScale);

    /* 0x4 */ PointGravity* mGravityInstance;
};

class SegmentGravityCreator : public GravityCreator {
public:
    SegmentGravityCreator() : GravityCreator(), mGravityInstance() {
    }

    virtual PlanetGravity* getGravity();
    virtual PlanetGravity* createInstance();
    virtual void settingFromSRT(const TVec3f& rTrans, const TVec3f& rRotate, const TVec3f& rScale);
    virtual void settingFromJMapArgs(s32 arg0, s32 arg1, s32 arg2);

    /* 0x4 */ SegmentGravity* mGravityInstance;
};

class WireGravityCreator : public GravityCreator {
public:
    WireGravityCreator() : GravityCreator(), mRailRider(), mGravityInstance() {
    }

    virtual PlanetGravity* getGravity();
    virtual PlanetGravity* createInstance();
    virtual void settingFromJMapOtherParam(const JMapInfoIter& rIter);

    /* 0x4 */ RailRider* mRailRider;
    /* 0x8 */ WireGravity* mGravityInstance;
};
