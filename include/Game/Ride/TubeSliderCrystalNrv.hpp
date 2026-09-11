#pragma once

#include "LiveActor/Nerve.hpp"

namespace NrvTubeSliderCrystal {
    class TubeSliderCrystalNrvWait : public Nerve {
    public:
        TubeSliderCrystalNrvWait();
        virtual void execute(Spine*) const;
        static TubeSliderCrystalNrvWait sInstance;
    };
    class TubeSliderCrystalNrvBreak : public Nerve {
    public:
        TubeSliderCrystalNrvBreak();
        virtual void execute(Spine*) const;
        static TubeSliderCrystalNrvBreak sInstance;
    };
}
