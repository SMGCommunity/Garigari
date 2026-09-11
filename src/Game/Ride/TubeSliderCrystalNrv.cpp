#include "Ride/TubeSliderCrystalNrv.hpp"
#include "Ride/TubeSliderCrystal.hpp"
#include "Util/LiveActorUtil.hpp"

namespace NrvTubeSliderCrystal {
    TubeSliderCrystalNrvWait::TubeSliderCrystalNrvWait() {}
    TubeSliderCrystalNrvBreak::TubeSliderCrystalNrvBreak() {}

    void TubeSliderCrystalNrvBreak::execute(Spine* pSpine) const {
        static_cast<TubeSliderCrystal*>(pSpine->mExecutor)->exeBreak();
    }
    void TubeSliderCrystalNrvWait::execute(Spine* pSpine) const {
        MR::isFirstStep(static_cast<TubeSliderCrystal*>(pSpine->mExecutor));
    }
}
