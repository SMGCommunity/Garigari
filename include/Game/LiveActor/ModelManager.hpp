#pragma once

#include <JSystem/J3DGraphAnimator/J3DModel.hpp>

class ResourceHolder;
class J3DModel;
class J3DModelData;
class XanimePlayer;

class ModelManager {
public:
    void init(const char*, const char*, bool);
    void update();
    void calcAnim();
    void calcView();
    void entry();
    void newDifferedDLBuffer();
    void startBck(const char*, const char*);
    void startBckWithInterpole(const char*, long);
    void startBtk(const char*);
    void startBrk(const char*);
    void startBtp(const char*);
    void startBpk(const char*);
    void startBva(const char*);
    void stopBtk();
    void stopBrk();
    void stopBtp();
    void stopBpk();
    void stopBva();
    void fn_8023BBF0();
    void fn_8023BC60();
    void fn_8023BCB0();
    void fn_8023BD90();
    void fn_8023BE00();
    void getBckCtrl() const;
    void getBtkCtrl() const;
    void getBrkCtrl() const;
    void getBtpCtrl() const;
    void getBpkCtrl() const;
    void getBvaCtrl() const;
    bool isBckStopped() const;
    bool isBtkStopped() const;
    bool isBrkStopped() const;
    bool isBtpStopped() const;
    bool isBpkStopped() const;
    bool isBvaStopped() const;
    bool isBtkPlaying(const char*) const;
    bool isBrkPlaying(const char*) const;
    bool isBpkPlaying(const char*) const;
    bool isBtpPlaying(const char*) const;
    bool isBvaPlaying(const char*) const;
    void initJointTransform();
    void getJointTransform(const char*);
    ResourceHolder* getResourceHolder() const;
    void getModelResourceHolder() const;
    J3DModel getJ3DModel() const;
    J3DModelData getJ3DModelData() const;
    const char* getPlayingBckName() const;
    void initModelAndAnimation(ResourceHolder*, const char*, ResourceHolder*, J3DMdlFlag);
    void initMaterialAnm();
    void initVisibilityAnm();
    void calc();
    void changeBckSetting(const char*, const char*, XanimePlayer*);
};
