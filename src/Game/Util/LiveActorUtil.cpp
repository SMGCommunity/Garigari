#include "Util/LiveActorUtil.hpp"
#include "LiveActor/LodCtrl.hpp"

namespace MR {
    LodCtrl* createLodCtrlNPC(LiveActor *pActor, const JMapInfoIter &rIter) {
        LodCtrl* ctrl = new LodCtrl(pActor, rIter);
        ctrl->createLodModel(0x11, 0x27, -1);
        ctrl->syncMaterialAnimation();
        ctrl->syncJointAnimation();
        ctrl->initLightCtrl();
        ctrl->offSyncShadowHost();
        ctrl->mDistCameraCalc = true;
        return ctrl;
    }

    LodCtrl* createLodCtrlPlanet(LiveActor *pActor, const JMapInfoIter &rIter, f32 farClip, s32 calcAnim) {
        LodCtrl* ctrl = new LodCtrl(pActor, rIter);
        ctrl->createLodModel(6, calcAnim, 1);
        ctrl->setDistanceToMiddleAndLow(5000.0f, 10000.0f);
        ctrl->setFarClipping(farClip);
        return ctrl;
    }





    void setClippingTypeSphere(LiveActor* pActor, f32 clippingRadius);
    void setClippingTypeSphere(LiveActor* pActor, f32 clippingRadius, const TVec3f* pClippingPos);
    void setClippingTypeSphereContainsModelBoundingBox(LiveActor* pActor, f32 radiusExtension);
    void setClippingFar50m(LiveActor* pActor);
    void setClippingFar100m(LiveActor* pActor);
    void setClippingFar200m(LiveActor* pActor);
    void setClippingFar300m(LiveActor* pActor);
    void setClippingFarMax(LiveActor* pActor);
    void setClippingFar(LiveActor* pActor, f32 farDistance);
};
