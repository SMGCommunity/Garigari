#include "Game/Util/FootPrint.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/Scene/SceneFunction.hpp"
#include "Game/Util/ActorMovementUtil.hpp"
#include "Game/Util/Color.hpp"
#include "Game/Util/DirectDraw.hpp"
#include "Game/Util/JointUtil.hpp"
#include "Game/Util/LiveActorUtil.hpp"
#include "Game/Util/MathUtil.hpp"
#include "Game/Util/MemoryUtil.hpp"
#include "Game/Util/ObjUtil.hpp"
#include <JSystem/JUtility/JUTTexture.hpp>
#include <cstdio>

namespace {
    static const s32 sFadeBufferCount = 10;
    static const s32 sFadeOutTime = 60;
    static const char* sResourceName = "FootPrintCtrl";
    static const char* sObjectName = "の足跡";
    static const char* sTextureName = "FootPrint.bti";
};  // namespace

FootPrint::FootPrint(const char* pName, s32 amount, s32 drawType) : NameObj(pName) {
    initMember(amount, drawType);
}

FootPrint::FootPrint(const char* pName, s32 amount) : NameObj(pName) {
    initMember(amount, MR::DrawType_0x17);
}

void FootPrint::initMember(s32 amount, s32 drawType) {
    mTexture = nullptr;
    mPrints = nullptr;
    mPrintMaxNum = 0;
    mPrintNum = 0;
    mRotatingPrintIndex = 0;

    mSideOffset = 20.0f;
    mSideSize = 20.0f;
    mFrontSize = 20.0f;
    mMinDistance = 80.0f;

    mLastPrintPos.zero();

    mPrints = new FootPrintInfo[amount];
    mPrintMaxNum = amount;

    for (int i = 0; i < mPrintMaxNum; i++) {
        mPrints[i].mIsValid = false;
    }

    // FIXME: MovementType enum
    MR::connectToScene(this, MR::MovementType_MapObj, MR::CalcAnimType_None, MR::DrawBufferType_None, drawType);
}

FootPrintInfo::FootPrintInfo() {
}

void FootPrint::setTexture(ResTIMG* img) {
    MR::CurrentHeapRestorer heapRestorer = MR::CurrentHeapRestorer(reinterpret_cast< JKRHeap* >(MR::getSceneHeapGDDR3()));
    mTexture = new JUTTexture(img, 0);
}

void FootPrint::movement() {
    if (mIsCleared) {
        for (s32 i = 0; i < mPrintNum; i++) {
            if (!mPrints[i].mIsValid) {
                continue;
            }

            mPrints[i].mTimeLeft--;

            if (mPrints[i].mTimeLeft <= 0) {
                mPrints[i].mIsValid = false;
            }
        }

        return;
    }

    for (s32 i = mRotatingPrintIndex; i < mRotatingPrintIndex + ::sFadeBufferCount; i++) {
        s32 rotatedIndex = i;

        if (i >= mPrintMaxNum) {
            rotatedIndex -= mPrintMaxNum;
        }

        if (!mPrints[rotatedIndex].mIsValid) {
            continue;
        }

        mPrints[rotatedIndex].mTimeLeft--;

        if (mPrints[rotatedIndex].mTimeLeft <= 0) {
            mPrints[rotatedIndex].mIsValid = false;
        }
    }
}

bool FootPrint::addPrint(const TVec3f& rPos, const TVec3f& rArg2, const TVec3f& rArg3, bool arg4) {
    mIsCleared = false;

    if (mPrintNum > 0 && rPos.distance(mLastPrintPos) < mMinDistance) {
        return false;
    }

    mLastPrintPos = rPos;
    mPrints[mRotatingPrintIndex].mPos = rPos;
    mPrints[mRotatingPrintIndex]._C = rArg2;
    mPrints[mRotatingPrintIndex]._18 = rArg3;
    mPrints[mRotatingPrintIndex].mTimeLeft = ::sFadeOutTime;
    mPrints[mRotatingPrintIndex].mIsValid = true;
    mPrints[mRotatingPrintIndex]._29 = arg4;

    mRotatingPrintIndex++;
    mPrintNum++;

    if (mRotatingPrintIndex >= mPrintMaxNum) {
        mRotatingPrintIndex -= mPrintMaxNum;
    }

    if (mPrintNum > mPrintMaxNum) {
        mPrintNum = mPrintMaxNum;
    }

    return true;
}

void FootPrint::draw() const {
    if (mPrintNum <= 0) {
        return;
    }

    TDDraw::setup(2, 1, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    mTexture->load(GX_TEXMAP0);

    Color8 color(0, 0, 0, 255);

    for (int i = 0; i < mPrintNum; i++) {
        if (!mPrints[i].mIsValid) {
            continue;
        }

        color.a = 255.0f * MR::normalize(mPrints[i].mTimeLeft, 0.0f, ::sFadeOutTime);
        GXSetTevColor(GX_TEVREG0, color);

        TVec3f cross = mPrints[i]._C.cross(mPrints[i]._18);
        TVec3f center;
        if ((i & 1) != 0) {
            center = mPrints[i].mPos + cross * mSideOffset;
        } else {
            center = mPrints[i].mPos - cross * mSideOffset;
        }

        center += mPrints[i]._18 * 5.0f;

        TDDraw::drawTexture3D(center, mPrints[i]._18, mPrints[i]._C, mFrontSize, mSideSize, nullptr, mPrints[i]._29 != false, false);
    }

    TDDraw::close();
}

void FootPrint::clear() {
    mIsCleared = true;
}

void FootPrint::clearForce() {
    mPrintNum = 0;
    mRotatingPrintIndex = 0;
}

TVec3f* FootPrint::getPrintPos(u32 index) const {
    return &mPrints[index % mPrintMaxNum].mPos;
}

void FootPrint::invalidate(u32 index) {
    mPrints[index % mPrintMaxNum].mIsValid = false;
}

bool FootPrint::isValid(u32 index) const {
    return mPrints[index % mPrintMaxNum].mIsValid != false;
}

namespace MR {
    // FIXME: stack and regswap
    FootPrint* createFootPrintFromArc(const LiveActor* pActor) {
        ResTIMG* img = getTexFromArc(::sTextureName, pActor);

        const JMapInfo* pInfo = tryCreateCsvParser(pActor, "%s.bcsv", ::sResourceName);

        if (pInfo == nullptr) {
            FootPrint* pFootPrint = new FootPrint("ダミー足跡", 32);

            pFootPrint->setTexture(img);

            return pFootPrint;
        }

        s32 footNumMax = 32;
        f32 sideOffset = 0.0f;
        f32 sideSize = 100.0f;
        f32 frontSize = 100.0f;
        f32 distanceMin = 10.0f;

        getCsvDataS32(&footNumMax, pInfo, "FootNumMax", 0);
        getCsvDataF32(&sideOffset, pInfo, "SideOffset", 0);
        getCsvDataF32(&sideSize, pInfo, "SideSize", 0);
        getCsvDataF32(&frontSize, pInfo, "FrontSize", 0);
        getCsvDataF32(&distanceMin, pInfo, "DistanceMin", 0);

        s32 nameLen = strlen(pActor->mName) + strlen(::sObjectName) + 1;
        char* name = new char[nameLen];
        snprintf(name, nameLen, "%s%s", pActor->mName, ::sObjectName);

        FootPrint* pFootPrint = new FootPrint(name, footNumMax);

        pFootPrint->setTexture(img);

        pFootPrint->mSideOffset = sideOffset;
        pFootPrint->mSideSize = sideSize;
        pFootPrint->mFrontSize = frontSize;
        pFootPrint->mMinDistance = distanceMin;

        return pFootPrint;
    }

    // void addFootPrint(FootPrint*, const LiveActor*, const TVec3f&, const TVec3f&, bool, f32) {}

    // FIXME: TVec3f inlining
    void addFootPrint(FootPrint* pPrint, const LiveActor* pActor, const TVec3f& rVec, bool b1, f32 f1) {
        TVec3f front(0.0f, 0.0f, 1.0f);
        calcFrontVec(&front, pActor);

        addFootPrint(pPrint, pActor, rVec, front, b1, f1);
    }

    // FIXME: mtx inlining
    void addFootPrint(FootPrint* pPrint, const LiveActor* pActor, const char* pName, bool b1, f32 f1) {
        TPos3f jointMtx = getJointMtx(pActor, pName);

        TVec3f up, trans;
        jointMtx.getXDir(up);
        jointMtx.getTrans(trans);

        addFootPrint(pPrint, pActor, trans, up, b1, f1);
    }
};  // namespace MR
