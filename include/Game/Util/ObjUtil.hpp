#pragma once

#include <JGeometry.hpp>
#include "Util/JMapInfo.hpp"
#include "Util/Functor.hpp"

class NameObj;
class LiveActor;
class LayoutActor;
class ModelObj;
class ResourceHolder;
class NameObjAdaptor;
class BenefitItemOneUp;
class BenefitItemLifeUp;
class StageSwitchCtrl;
class Color8;
struct GXColor;

namespace MR {
    JMapInfo* createCsvParserFromFile(const char *, const char *, ...);
    bool isExistElement(const JMapInfo *, const char *, const char *);




    bool isJudgedToClipFrustum(const TVec3f& rPosition, f32 radius);
    bool isJudgedToClipFrustum50m(const TVec3f& rPosition, f32 radius);
    bool isJudgedToClipFrustum300m(const TVec3f& rPosition, f32 radius);
    bool isJudgedToNearClip(const TVec3f& rPosition, f32 radius);

    void initialize(NameObj* pObj, const JMapInfoIter& rIterrIter);

    bool isInWater(const TVec3f& rPosition);
    bool isInDeath(const TVec3f& rPosition);
    bool isInDarkMatter(const TVec3f& rPosition);

    void connectToScene(LiveActor* pActor, int movementType, int calcAnimType, int drawBufferType, int drawType);
    void connectToScene(NameObj* pObj, int movementType, int calcAnimType, int drawBufferType, int drawType);
    void connectToSceneCollisionMapObj(LiveActor* pActor);
    void connectToSceneCollisionMapObjWeakLight(LiveActor* pActor);
    void connectToSceneCollisionMapObjStrongLight(LiveActor* pActor);
    void connectToSceneCollisionEnemy(LiveActor* pActor);
    void connectToSceneCollisionEnemyStrongLight(LiveActor* pActor);
    void connectToSceneCollisionEnemyNoShadowedMapObjStrongLight(LiveActor* pActor);
    void connectToSceneNpc(LiveActor* pActor);
    void connectToSceneNpcMovement(LiveActor* pActor);
    void connectToSceneRide(LiveActor* pActor);
    void connectToSceneEnemy(LiveActor* pActor);
    void connectToSceneEnemyMovement(NameObj* pObj);
    void connectToSceneMapObj(LiveActor* pActor);
    void connectToSceneMapObjMovement(NameObj* pObj);
    void connectToSceneMapObjMovementCalcAnim(NameObj* pObj);
    void connectToSceneMapObjNoMovement(LiveActor* pActor);
    void connectToSceneMapObjNoCalcAnim(LiveActor* pActor);
    void connectToSceneMapObjNoCalcAnimStrongLight(LiveActor* pActor);
    void connectToSceneMapObjDecoration(LiveActor* pActor);
    void connectToSceneMapObjDecorationStrongLight(LiveActor* pActor);
    void connectToSceneMapObjDecorationMovement(NameObj* pObj);
    void connectToSceneMapObjStrongLight(LiveActor* pActor);
    void connectToScenePlanet(LiveActor* pActor);
    void connectToSceneEnvironment(LiveActor* pActor);
    void connectToSceneEnvironmentStrongLight(LiveActor* pActor);
    void connectToClippedMapParts(LiveActor* pActor);
    void connectToSceneEnemyDecoration(LiveActor* pActor);
    void connectToSceneEnemyDecorationMovement(NameObj* pObj);
    void connectToSceneEnemyDecorationMovementCalcAnim(NameObj* pObj);
    void connectToSceneItem(LiveActor* pActor);
    void connectToSceneItemStrongLight(LiveActor* pActor);
    void connectToSceneIndirectEnemy(LiveActor* pActor);
    void connectToSceneIndirectNpc(LiveActor* pActor);
    void connectToSceneIndirectMapObj(LiveActor* pActor);
    void connectToSceneIndirectMapObjStrongLight(LiveActor* pActor);
    void connectToSceneScreenEffectMovement(NameObj* pObj);
    void connectToSceneAreaObj(NameObj* pObj);
    void connectToScene3DModelFor2D(LiveActor* pActor);
    void connectToSceneLayout(NameObj* pObj);
    // one unknown function
    void connectToSceneLayoutMovementCalcAnim(NameObj* pObj);
    void connectToSceneLayoutDecoration(NameObj* pObj);
    void connectToSceneLayoutFileSelect(NameObj* pObj);
    void connectToSceneTalkLayout(NameObj* pObj);
    void connectToSceneWipeLayout(NameObj* pObj);
    void connectToSceneLayoutOnPause(NameObj* pObj);
    void connectToSceneLayoutMovement(NameObj* pObj);
    void connectToSceneMirrorMapObj(LiveActor* pActor);
    void connectToSceneMirrorMapObjDecoration(LiveActor* pActor);
    void connectToSceneCamera(NameObj* pObj);
    void connectToSceneNoShadowedMapObj(LiveActor* pActor);
    void connectToSceneNoShadowedMapObjStrongLight(LiveActor* pActor);
    void connectToSceneNoSilhouettedMapObj(LiveActor* pActor);
    void connectToSceneNoSilhouettedMapObjStrongLight(LiveActor* pActor);
    void connectToSceneNoSilhouettedMapObjStrongLightCalcAnim(LiveActor* pActor);
    void connectToSceneNoSilhouettedMapObjWeakLightCalcAnim(LiveActor* pActor);
    void connectToSceneSwitchingScreenEffect(LiveActor* pActor);
    void connectToSceneSky(LiveActor* pActor);
    void connectToSceneAir(LiveActor* pActor);
    void connectToSceneSun(LiveActor* pActor);
    void connectToSceneWorldMapMiniObj(LiveActor* pActor);
    void connectToSceneWorldMapIcon(LiveActor* pActor);
    void connectToSceneSuperDreamer(LiveActor* pActor);

    void requestMovementOn(NameObj* pObj);
    void requestMovementOn(LiveActor* pActor);
    void requestMovementOn(LayoutActor* pLayout);
    void requestMovementOff(NameObj* pObj);
    void requestMovementOff(LiveActor* pActor);
    void requestMovementOff(LayoutActor* pLayout);

    void joinToNameObjGroup(NameObj* pObj, const char* pGroupName);
    void registerPreDrawFunction(const MR::FunctorBase& rFunctor, int drawType);
    void registerPreDrawFunctionIfNotExist(const MR::FunctorBase& rFunctor, int drawType);

    NameObjAdaptor* createDrawAdapter(const char* pName, int drawType, const MR::FunctorBase& rFunctor);
    NameObjAdaptor* createAdaptorAndConnectToDrawBloomModel(const char* pName, const MR::FunctorBase& rFunctor);

    void listenNameObjStageSwitchOnAppear(const NameObj* pObj, const StageSwitchCtrl* pStageSwitchCtrl, const MR::FunctorBase& rFunctor);
    void listenNameObjStageSwitchOnOffAppear(const NameObj* pObj, const StageSwitchCtrl* pStageSwitchCtrl, const MR::FunctorBase& rFunctorOn, const MR::FunctorBase& rFunctorOff);
    void listenNameObjStageSwitchOnA(const NameObj* pObj, const StageSwitchCtrl* pStageSwitchCtrl, const MR::FunctorBase& rFunctor);
    void listenNameObjStageSwitchOnOffA(const NameObj* pObj, const StageSwitchCtrl* pStageSwitchCtrl, const MR::FunctorBase& rFunctorOn, const MR::FunctorBase& rFunctorOff);
    void listenNameObjStageSwitchOnB(const NameObj* pObj, const StageSwitchCtrl* pStageSwitchCtrl, const MR::FunctorBase& rFunctor);
    void listenNameObjStageSwitchOffB(const NameObj* pObj, const StageSwitchCtrl* pStageSwitchCtrl, const MR::FunctorBase& rFunctor);
    void listenNameObjStageSwitchOnOffB(const NameObj* pObj, const StageSwitchCtrl* pStageSwitchCtrl, const MR::FunctorBase& rFunctorOn, const MR::FunctorBase& rFunctorOff);

    ResourceHolder* createAndAddResourceHolder(const char* pObjName);
    // more ResourceHolder stuff...
    bool isExistFileInArc(const ResourceHolder* pResArc, const char* pPathFormat, ...);

    const JMapInfo* createCsvParser(const ResourceHolder* pResArc, const char* pPathFormat, ...);
    const JMapInfo* createCsvParser(const char* pArcName, const char* pPathFormat, ...);
    const JMapInfo* tryCreateCsvParser(const ResourceHolder* pResArc, const char* pPathFormat, ...);
    const JMapInfo* tryCreateCsvParser(const LiveActor* pActor, const char* pPathFormat, ...);
    const JMapInfo* tryCreateCsvParser(const char* pArcName, const char* pPathFormat, ...);

    const JMapInfo* tryCreateStageCsvParser(const char* pStageName, const char* pArcName, const char* pPathFormat, ...);
    const JMapInfo* tryCreateStageZoneInfoCsvParser(const char* pPathFormat, ...);
    const JMapInfo* tryCreateStageUseResourceCsvParser(const char* pStageName, const char* pPathFormat, ...);

    const JMapInfo* tryCreateWorldMapCsvParser(u32* pWorldId, const char* pCsvName); // first argument isn't actually a u32 pointer (it's most likely a pointer to something world map related), but treating it as one is totally valid 

    s32 getCsvDataElementNum(const JMapInfo* pCsvData);
    void getCsvDataStr(const char** pDest, const JMapInfo* pCsvData, const char* pItemName, s32 dataRow);
    void getCsvDataStrOrNULL(const char** pDest, const JMapInfo* pCsvData, const char* pItemName, s32 dataRow);
    void getCsvDataS32(s32* pDest, const JMapInfo* pCsvData, const char* pItemName, s32 dataRow);
    void getCsvDataU32(s32* pDest, const JMapInfo* pCsvData, const char* pItemName, s32 dataRow);
    void getCsvDataS16(s16* pDest, const JMapInfo* pCsvData, const char* pItemName, s32 dataRow);
    void getCsvDataU8(u8* pDest, const JMapInfo* pCsvData, const char* pItemName, s32 dataRow);
    void getCsvDataF32(f32* pDest, const JMapInfo* pCsvData, const char* pItemName, s32 dataRow);
    void getCsvDataBool(bool* pDest, const JMapInfo* pCsvData, const char* pItemName, s32 dataRow);
    void getCsvDataVec(Vec* pDest, const JMapInfo* pCsvData, const char* pItemName, s32 dataRow);
    void getCsvDataColor(GXColor* pDest, const JMapInfo* pCsvData, const char* pItemName, s32 dataRow);

    bool hasCsvItem(const JMapInfo*, const char* pItemName);
    bool hasCsvDataItem(const JMapInfo*, const char* pItemName, const char* pDataName);
    /// <summary>
    /// 
    /// </summary>
    /// <param name="pDest">The output</param>
    /// <param name="pCsvData">The BCSV to look through</param>
    /// <param name="pItemName">The BCSV Column to find pDataName in</param>
    /// <param name="pDataName">The value to find the first row of inside the pItemName Column</param>
    /// <param name="pElementName">The BCSV Column to get the data from using the index of the row found for pDataName</param>
    JMapInfoIter getCsvDataStrByElement(const char** pDest, const JMapInfo* pCsvData, const char* pItemName, const char* pDataName, const char* pElementName);
    // more csv functions...

    void declarePowerStar(const NameObj* pHost);
    void declarePowerStar(const NameObj* pHost, s32 powerStarId);
    void declarePowerStarCoin100();
    void appearPowerStarContinueCurrentDemo(const NameObj* pHost, const TVec3f& rPosition);
    void appearPowerStarWithoutDemo(const NameObj* pHost);
    void requestAppearPowerStar(const NameObj* pHost);
    void requestAppearPowerStar(const NameObj* pHost, const TVec3f& rPosition);
    void requestAppearPowerStar(const NameObj* pHost, s32 powerStarId, const TVec3f& rPosition);
    void requestAppearPowerStar(const NameObj* pHost, const LiveActor* pFromActor, f32);
    void requestAppearPowerStarFromBelow(const NameObj* pHost);
    void requestAppearPowerStarCoin100();
    bool isEndPowerStarAppearDemo(const NameObj* pHost);

    ModelObj* createPowerStarDemoModel(const NameObj* pHost, const char* pName, MtxPtr pMtx);

    void declareCoin(const NameObj* pHost, s32 numItems);
    s32 getDeclareRemnantCoinCount(const NameObj* pHost);
    s32 getUncollectedCoinCount(const NameObj* pHost);
    bool hopCoin(const NameObj* pHost, const TVec3f& rPosition, const TVec3f& rDirection);
    bool appearCoinPop(const NameObj* pHost, const TVec3f&, s32 numItems);
    bool appearCoinPopToDirection(const NameObj* pHost, const TVec3f& rPosition, const TVec3f& rDirection, s32 numItems);
    bool appearCoinAgainstGravity(const NameObj* pHost, const TVec3f& rPosition, s32 numItems);
    bool appearCoinToVelocity(const NameObj* pHost, const TVec3f& rPosition, const TVec3f& rVelocity, s32 numItems);
    bool appearCoinCircle(const NameObj* pHost, const TVec3f& rPosition, s32 numItems);

    void declareStarPiece(const NameObj* pHost, s32 numItems);
    s32 getDeclareRemnantStarPieceCount(const NameObj* pHost);
    s32 getDeclareRemnantStarPieceCountNotExist(const NameObj* pHost);
    void declareStarPieceReceiver(const NameObj* pHost, s32);
    void clearGotCountStarPieceReceiver(const NameObj* pHost);
    bool hopStarPiece(const NameObj* pHost, const TVec3f&, const TVec3f&);
    bool appearStarPiece(const NameObj* pHost, const TVec3f& rPosition, s32 numItems, f32 radius, f32 height, bool);
    bool appearStarPieceToDirection(const NameObj* pHost, const TVec3f& rPosition, const TVec3f& rDirection, s32 numItems, f32 radius, f32 height, bool);
    // one unknown StarPiece function
    void initStarPieceGetCSSound();

    BenefitItemOneUp* createKinokoOneUp();
    void appearKinokoOneUp(BenefitItemOneUp* pKinoko, MtxPtr pMtx);
    void appearKinokoOneUpPop(BenefitItemOneUp* pKinoko, MtxPtr pMtx);
    void appearKinokoOneUpHop(BenefitItemOneUp* pKinoko, MtxPtr pMtx);

    BenefitItemLifeUp* createKinokoSuper();
    void appearKinokoSuperPop(BenefitItemLifeUp* pKinoko, MtxPtr pMtx);

    void stopScene(s32 duration);
    void stopSceneForDefaultHit(s32 duration);

    bool tryRumblePad(const void* pHost, const char* pPatternName, s32 wiimote);
    bool tryRumblePadVeryStrong(const void* pHost, s32 wiimote);
    bool tryRumblePadStrong(const void* pHost, s32 wiimote);
    bool tryRumblePadMiddle(const void* pHost, s32 wiimote);
    bool tryRumblePadWeak(const void* pHost, s32 wiimote);
    bool tryRumblePadVeryWeak(const void* pHost, s32 wiimote);
    bool tryRumblePadWeakAndVeryWeak(const void* pHost, s32 wiimote);
    bool tryRumbleDefaultHit(const void* pHost, s32 wiimote);

    void shakeCameraVeryStrong();
    void shakeCameraStrong();
    void shakeCameraNormalStrong();
    void shakeCameraNormal();
    void shakeCameraNormalWeak();
    void shakeCameraWeak();
    void shakeCameraVeryWeak();
    void shakeCameraInfinity(NameObj* pHost, f32, f32);
    void stopShakingCamera(NameObj* pHost);

    bool isName(const NameObj* pObj, const char* pName);
    bool isSame(const NameObj* pObjA, const NameObj* pObjB);

    void suspendAllSceneNameObj();
    void resumeAllSceneNameObj();

    void requestPointLight(const LiveActor*, TVec3f, Color8, f32, s32);
    bool registerNamePosLinkObj(const NameObj* pLinkedObj, const JMapInfoIter& rIter, const char* pPosName);
    bool tryRegisterNamePosLinkObj(const NameObj* pLinkedObj, const JMapInfoIter& rIter, const char* pPosName);
    bool findNamePos(const char* pPosName, MtxPtr pMtx);
    bool findNamePos(const char* pPosName, TVec3f* pPosition, TVec3f* pRotation);
    bool findNamePosOnGround(const char* pPosName, MtxPtr pMtx);
    bool tryFindNamePos(const char* pPosName, MtxPtr pMtx);
    bool tryFindNamePos(const char* pPosName, TVec3f* pPosition, TVec3f* pRotation);
    bool findLinkNamePos(const NameObj* pLinkedObj, const char* pPosName, MtxPtr pMtx);
    bool tryFindLinkNamePos(const NameObj* pLinkedObj, const char* pPosName, TVec3f* pPosition, TVec3f* pRotation);
    bool tryFindLinkNamePos(const NameObj* pLinkedObj, const char* pPosName, MtxPtr pMtx);
};
