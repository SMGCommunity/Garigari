#include "Game/Gravity/PlanetGravityManager.hpp"
#include "Game/Gravity/GravityInfo.hpp"
#include "Game/Gravity/PlanetGravity.hpp"
#include "Game/Util/MathUtil.hpp"

PlanetGravityManager::PlanetGravityManager(const char* pName) : NameObj(pName), mGravityCount() {
}

void PlanetGravityManager::init(const JMapInfoIter& rIter) {
}

bool PlanetGravityManager::calcTotalGravityVector(TVec3f* pTotalGravity, GravityInfo* pInfo, const TVec3f& rPos, u32 gravityType, u32 host,
                                                  const NameObj* pObj) const {
    TVec3f vec;
    vec.zero();

    PlanetGravity* const* gravityArr = mGravityArr;

    if (pInfo != nullptr) {
        pInfo->init();
    }

    f32 f1 = -1.0f;
    s32 maxPriority = -1;

    for (; gravityArr != &mGravityArr[mGravityCount]; gravityArr++) {
        PlanetGravity* pGravity = *gravityArr;

        if (!pGravity->isValid()) {
            continue;
        }

        if ((gravityType & pGravity->mGravityType) == 0) {
            continue;
        }

        if (host == (u32)pGravity->mHost) {
            continue;
        }

        s32 priority = pGravity->mPriority;
        if (priority < maxPriority) {
            break;
        }

        TVec3f gravityVec;
        if (!pGravity->calcGravity(&gravityVec, rPos)) {
            continue;
        }

        bool b1 = false;
        f32 magnitude = gravityVec.length();
        if (priority == maxPriority) {
            vec += gravityVec;

            if (f1 < magnitude) {
                b1 = true;
            }
        } else if (priority > maxPriority) {
            b1 = true;
            maxPriority = priority;
            vec = gravityVec;
        }

        if (pInfo != nullptr && b1) {
            f1 = magnitude;
            pInfo->mGravityVector = gravityVec;
            pInfo->mLargestPriority = maxPriority;
            pInfo->mGravityInstance = *gravityArr;
        }
    }

    bool ret = false;
    if (pTotalGravity != nullptr) {
        ret = MR::normalizeOrZero(&vec);
        *pTotalGravity = vec;
    }

    return !ret;
}

void PlanetGravityManager::registerGravity(PlanetGravity* pGravity) {
    pGravity->mIsRegistered = true;

    s32 index = mGravityCount++;
    mGravityArr[index] = pGravity;

    sortGravities();
}

inline void PlanetGravityManager::sortGravities() {
    for (s32 i = mGravityCount - 1; i >= 1; i--) {
        if (mGravityArr[i]->mPriority > mGravityArr[i - 1]->mPriority) {
            bubbleDown(i);
        } else {
            break;
        }
    }
}

inline void PlanetGravityManager::bubbleDown(int i) {
    PlanetGravity* temp = mGravityArr[i - 1];
    mGravityArr[i - 1] = mGravityArr[i];
    mGravityArr[i] = temp;
}
