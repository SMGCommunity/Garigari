
#include <JSystem/JGeometry/TMatrix.hpp>
#include <JSystem/JGeometry/TVec.hpp>
#include <revolution/types.h>

class HitSensor;
class LiveActor;
class ProjmapEffectMtxSetter;

namespace AttackRockUtil {
    void initAttackRockBinder(LiveActor*);
    // TODO: find better name once usage is found
    f32 calcAngle(LiveActor*, const TQuat4f&);
    void startAttack(TVec3f*, const TQuat4f&, const HitSensor*, const HitSensor*, f32);
    void startAttack(TVec3f*, const TVec3f&, const HitSensor*, const HitSensor*, f32);
    void updateEffectMtx(TPos3f*, LiveActor*);
    void updateProjMapEffectMtx(ProjmapEffectMtxSetter*, const TQuat4f&, const TVec3f&);
    ProjmapEffectMtxSetter* createProjMapEffectMtxSetter(LiveActor*);
};  // namespace AttackRockUtil
