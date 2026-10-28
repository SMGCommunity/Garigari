#include "Game/Enemy/AttackRockUtil.hpp"
#include "Game/LiveActor/HitSensor.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/LiveActor/MaterialCtrl.hpp"
#include "Game/Util/ActorSensorUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/MtxUtil.hpp"
#include "Game/Util/PlayerUtil.hpp"
#include "math_types.hpp"

namespace AttackRockUtil {
    void initAttackRockBinder(LiveActor* pActor) {
        MR::setBinderIgnoreMovingCollision(pActor);
        // TODO: 0x3C probably a sensor type
        MR::setBinderExceptSensorType(pActor, 0x3C);
        MR::offBind(pActor);
    }

    f32 calcAngle(LiveActor* pActor, const TQuat4f& rQuat) {
        TVec3f velocityDir;
        MR::normalizeOrZero(&velocityDir, pActor->mVelocity);

        TVec3f zDir;
        rQuat.getZDir(zDir);

        // TODO: rounding of the conversion to degree constant
        return _180_PI * MR::diffAngleAbs(velocityDir, -zDir);
    }

    void startAttack(TVec3f* pOut, const TQuat4f& rQuat, const HitSensor* pSensor1, const HitSensor* pSensor2, f32 speed) {
        TVec3f zDir;
        rQuat.getZDir(zDir);
        startAttack(pOut, zDir, pSensor1, pSensor2, speed);
    }

    void startAttack(TVec3f* pOut, const TVec3f& rVec, const HitSensor* pSensor1, const HitSensor* pSensor2, f32 speed) {
        TVec3f sensorDir;
        MR::calcSensorDirectionNormalize(&sensorDir, pSensor1, pSensor2);
        MR::jumpPlayer(sensorDir * -10.0f);

        TVec3f attackDir;

        attackDir.set(sensorDir - rVec * 0.5f);

        if (MR::normalizeOrZero(&attackDir)) {
            attackDir.set(sensorDir);
        }

        pOut->set(attackDir * speed);
    }

    void updateEffectMtx(TPos3f* pEffectMtx, LiveActor* pActor) {
        TVec3f velocityDir;
        if (!MR::normalizeOrZero(&velocityDir, pActor->mVelocity)) {
            MR::turnMtxToYDirRate(pEffectMtx, pActor->mVelocity, 1.0f);
        }

        pEffectMtx->setTrans(pActor->mPosition);
    }

    void updateProjMapEffectMtx(ProjmapEffectMtxSetter* pEffectMtxSetter, const TQuat4f& rQuat, const TVec3f& rVec) {
        TPos3f pos;

        pos.setQT(rQuat, rVec);
        pos.invert(pos);

        pEffectMtxSetter->setEffectMtx(pos);
    }

    ProjmapEffectMtxSetter* createProjMapEffectMtxSetter(LiveActor* pActor) {
        ProjmapEffectMtxSetter* effectMtxSetter = MR::initDLMakerProjmapEffectMtxSetter(pActor);
        MR::newDifferedDLBuffer(pActor);
        effectMtxSetter->updateMtxUseBaseMtx();
        return effectMtxSetter;
    }

};  // namespace AttackRockUtil
