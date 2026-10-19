#pragma once

#include "Game/LiveActor/LiveActor.hpp"

class JUTTexture;
class OceanSpherePoint;
class WaterInfo;

class OceanSpherePlane {
public:
    OceanSpherePlane(s32 pointCount, const TVec3f* pCenter, const TVec3f& rAxis1, const TVec3f& rAxis2, const TVec2f& rTex1, const TVec2f& rTex2,
                     const TVec2f& rTex3);

    void update(f32 radius, f32 wave1Time, f32 wave2Time);
    OceanSpherePoint* getPoint(int col, int row) const {
        return mPoints[(mAxisPointCount * row) + col];
    }

    /* 0x00 */ s32 mGridPointCount;
    /* 0x04 */ s32 mAxisPointCount;
    /* 0x08 */ OceanSpherePoint** mPoints;
};

class OceanSpherePlaneEdge {
public:
    OceanSpherePlaneEdge(s32 pointCount, const TVec3f* pCenter, const TVec3f& rAxis1, const TVec3f& rAxis2, const TVec2f& rTex1, const TVec2f& rTex2);

    void update(f32 radius, f32 wave1Time, f32 wave2Time);

    /* 0x00 */ s32 mPointCount;
    /* 0x04 */ OceanSpherePoint** mPoints;
};

class OceanSphere : public LiveActor {
public:
    OceanSphere(const char* pName);

    virtual void init(const JMapInfoIter& rIter);
    virtual void appear();
    virtual void control();
    virtual void draw() const;

    bool isInWater(const TVec3f& rPos) const;
    bool calcWaterInfo(const TVec3f& rPos, const TVec3f& rGravity, WaterInfo* pInfo) const;
    void exeWait();
    void exeRiseUp();
    void initPoints();
    void initDisplayList();
    void updatePoints();
    OceanSpherePoint* getPlanePointLeftUpper(int row, int col) const;
    OceanSpherePoint* getPlanePointRightUpper(int row, int col) const;
    OceanSpherePoint* getPlanePointLeftLower(int row, int col) const;
    OceanSpherePoint* getPlanePointRightLower(int row, int col) const;
    void loadMaterialFace() const;
    void loadMaterialBack() const;
    void drawSphere(bool useEnvMap, bool useGD) const;
    void sendVertex(const OceanSpherePoint* pPoint, bool useEnvMap, bool useGD) const;

    f32 mRadius;
    f32 mRadiusTarget;
    s32 mPointCount;
    OceanSpherePoint* mAxisPointPX;
    OceanSpherePoint* mAxisPointNX;
    OceanSpherePoint* mAxisPointPY;
    OceanSpherePoint* mAxisPointNY;
    OceanSpherePoint* mAxisPointPZ;
    OceanSpherePoint* mAxisPointNZ;
    OceanSpherePlane* mPlaneLeftUpper;
    OceanSpherePlane* mPlaneRightUpper;
    OceanSpherePlane* mPlaneLeftLower;
    OceanSpherePlane* mPlaneRightLower;
    OceanSpherePlaneEdge* mEdge0;
    OceanSpherePlaneEdge* mEdge1;
    OceanSpherePlaneEdge* mEdge2;
    OceanSpherePlaneEdge* mEdge3;
    OceanSpherePlaneEdge* mEdge4;
    OceanSpherePlaneEdge* mEdge5;
    OceanSpherePlaneEdge* mEdge6;
    OceanSpherePlaneEdge* mEdge7;
    f32 mWaveTime1;
    f32 mWaveTime2;
    f32 mTexOffs0X;
    f32 mTexOffs0Y;
    f32 mTexOffs1X;
    f32 mTexOffs1Y;
    JUTTexture* mWaterTex;
    JUTTexture* mWaterEnvTex;
    GXColor mTevReg1Front;
    GXColor mTevReg1Back;
    bool mUseDisplayList;
    u8 _109;
    u8 _10A;
    u8 _10B;
    u32 mDispListFaceLen;
    u8* mDispListFace;
    u32 mDispListBackLen;
    u8* mDispListBack;
    bool mAlwaysUseRealDrawing;
    bool mIsCameraInside;
    bool mIsStartPosCamera;
    bool mIsTearDrop;
    bool mEnableStartPosCameraSwitch;
};
