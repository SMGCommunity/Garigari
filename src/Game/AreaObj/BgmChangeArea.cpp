#include "Game/AreaObj/BgmChangeArea.hpp"
#include "Game/AudioLib/AudSoundId.hpp"
#include "Game/AudioLib/AudWrap.hpp"
#include "Game/GameAudio/AudStageBgmTable.hpp"
#include "Game/Util/DemoUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include "Game/Util/PlayerUtil.hpp"
#include "Game/Util/SoundUtil.hpp"
#include "Game/Util/SceneUtil.hpp"
#include <JSystem/JAudio2/JAISound.hpp>


BgmChangeArea::BgmChangeArea(const char* pName) : AreaObj(pName), _48(false) {

}

void BgmChangeArea::init(const JMapInfoIter& rIter) {
    AreaObj::init(rIter);

    // TODO: Useless call to MR::isTwisterTowerGalaxy

    switch (mObjArg0) {
    case 0:
        if (mObjArg1 >= 0) {
            JAISoundID bgmId = JAISoundID(AudStageBgmTable::getBgmId(MR::getCurrentStageName(), MR::getCurrentScenarioNo(), mObjArg1));
        }
        if (mObjArg2 >= 0) {
            AudStageBgmTable::getBgmState(MR::getCurrentStageName(), mObjArg2);
        }
        break;
    case 1:
        if (mObjArg2 >= 0) {
            JAISoundID bgmId = JAISoundID(AudStageBgmTable::getBgmId(MR::getCurrentStageName(), MR::getCurrentScenarioNo(), mObjArg2));
        }
        break;
    case 2: {
        if (mObjArg1 >= 0)
            JAISoundID bgmId = JAISoundID(AudStageBgmTable::getBgmState(MR::getCurrentStageName(), mObjArg1));
        }
        break;
    }
    MR::connectToSceneAreaObj(this);
}

void BgmChangeArea::movement() {
    if (!isValid())
        return;

    if (MR::isCubeBgmChangeInvalid())
        return;

    if (MR::isPowerStarGetDemoActive()) {
        invalidate();
        return;
    }

    if (MR::isPlayingStageBgmID(STM_STAR_CHANCE)) {
        invalidate();
        return;
    }

    if (MR::isPlayingStageBgmID(STM_STAR_CHANCE_2)) {
        invalidate();
        return;
    }

    if (MR::isPlayerDead()) {
        invalidate();
        return;
    }

    // TODO: figure out where this goes
    //if (MR::isStageStateScenarioOpeningCamera()) {
    //    return;
    //}

    if (isInVolume(*MR::getPlayerPos())) {
        if (_48) {
            return;
        }

        s32 objArg0 = mObjArg0;
        s32 objArg1 = mObjArg1;
        s32 objArg2 = mObjArg2;

        switch (objArg0) {
        case 0:
            if (objArg1 < 0) {
                MR::startCurrentStageBGM(true);
                break;
            }

            JAISoundID bgmId = JAISoundID(AudStageBgmTable::getBgmId(MR::getCurrentStageName(), MR::getCurrentScenarioNo(), objArg1));

            if (!bgmId.isAnonymous()) {
                // TODO: Missing AudBgmMgr
                //if (AudWrap::getBgmMgr()->mCurrentBGM[0] == bgmId) {
                //    if (MR::isPlayingStageBgm()) {
                //        break;
                //    }
                //}

                AudWrap::startStageBgm(bgmId, false, -1);
            }

            if (objArg2 >= 0) {
                s32 bgmState = AudStageBgmTable::getBgmState(MR::getCurrentStageName(), objArg2);

                if (bgmState >= 0) {
                    AudBgm* stageBgm = AudWrap::getStageBgm();

                    if (stageBgm != nullptr) {
                        // TODO: Missing AudBgm
                        //stageBgm->changeTrackMuteState(bgmState, 0);
                    }
                }
            }
            break;
        case 1:
            if (mObjArg3 != 1) {
                // TODO:    
                //if (MR::isGalaxyRedCometAppearInCurrentStage()) {
                //    break;
                //}

                //if (MR::isGalaxyBlackCometAppearInCurrentStage()) {
                //    break;
                //}
            }

            s32 arg1 = objArg1;

            if (arg1 < 0) {
                arg1 = 90;
            }

            if (objArg2 >= 0) {
                JAISoundID bgmId = JAISoundID(AudStageBgmTable::getBgmId(MR::getCurrentStageName(), MR::getCurrentScenarioNo(), objArg2));

                if (!bgmId.isAnonymous()) {
                    // TODO: Missing AudBgm
                    /*if (AudWrap::getBgmMgr()->mCurrentBGM[0] == bgmId) {
                        if (MR::isPlayingStageBgm()) {
                            break;
                        }
                    }*/

                    AudWrap::setNextIdStageBgm(bgmId);
                }
            }

            MR::stopStageBGM(arg1);
            break;
        case 2:
            if (objArg1 < 0) {
                AudBgm* stageBgm = AudWrap::getStageBgm();

                if (stageBgm != nullptr) {
                    s32 arg2 = getFadeTime();

                    // TODO: Missing AudBgm
                    //stageBgm->changeTrackMuteState(0, arg2);
                }
            } else {
                s32 bgmState = AudStageBgmTable::getBgmState(MR::getCurrentStageName(), objArg1);

                if (bgmState >= 0) {
                    AudBgm* stageBgm = AudWrap::getStageBgm();

                    if (stageBgm != nullptr) {
                        s32 arg2 = getFadeTime();

                        // TODO: Missing AudBgm
                        //stageBgm->changeTrackMuteState(bgmState, arg2);
                    }
                }
            }
            break;
        }

        _48 = true;
    } else {
        // TODO: This part is new to SMG2
        //s32 arg2 = getFadeTime();

        _48 = false;
    }
}


s32 BgmChangeArea::getFadeTime() const {
    return mObjArg2 >= 0 ? mObjArg2 : 30;
}