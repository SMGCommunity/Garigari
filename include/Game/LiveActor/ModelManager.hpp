#pragma once

#include <JSystem/J3DGraphAnimator/J3DModel.hpp>
#include <revolution/types.h>

class DisplayListMaker;
class ResourceHolder;
class XjointTransform;

class ModelManager {
public:
    /// @brief Creates a new `ModelManager`.
    ModelManager();

    ResourceHolder* getResourceHolder() const;
    ResourceHolder* getModelResourceHolder() const;
    void updateDL(bool);
    void startBck(const char*, const char*);
    void startBckWithInterpole(const char*, s32);
    void newDifferedDLBuffer();
    void startBtp(const char*);
    const char* getPlayingBckName() const;
    bool isBckStopped() const;
    bool isBtkStopped() const;
    bool isBrkStopped() const;
    bool isBtpStopped() const;
    bool isBpkStopped() const;
    bool isBvaStopped() const;
    void startBtk(const char*);
    void startBrk(const char*);
    void startBpk(const char*);
    void startBva(const char*);
    bool isBtkPlaying(const char*) const;
    bool isBrkPlaying(const char*) const;
    bool isBpkPlaying(const char*) const;
    bool isBtpPlaying(const char*) const;
    bool isBvaPlaying(const char*) const;
    void stopBtk();
    void stopBrk();
    void stopBtp();
    void stopBpk();
    void stopBva();
    void initJointTransform();
    XjointTransform* getJointTransform(const char*);

    /* 0x00 */ u8 _0[0x28];
    /* 0x28 */ DisplayListMaker* mDisplayListMaker;
};
