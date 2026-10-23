#pragma once

#include "Inline.hpp"

class NameObj;

enum SceneObj {
    SceneObj_SensorHitChecker = 0x00,
    SceneObj_CollisionDirector = 0x01,
    SceneObj_ClippingDirector = 0x02,
    SceneObj_DemoDirector = 0x03,
    SceneObj_EventDirector = 0x04,
    SceneObj_EffectSystem = 0x05,
    SceneObj_LightDirector = 0x06,
    SceneObj_SceneDataInitializer = 0x07,
    SceneObj_StageDataHolder = 0x08,
    SceneObj_MessageSensorHolder = 0x09,
    SceneObj_StageSwitchContainer = 0x0A,
    SceneObj_SwitchWatcherHolder = 0x0B,
    SceneObj_AwakeControllerHolder = 0x0C,
    SceneObj_AreaObjContainer = 0x0D,
    SceneObj_LiveActorGroupArray = 0x0E,
    SceneObj_MovementOnOffGroupHolder = 0x0F,
    SceneObj_CaptureScreenActor = 0x10,
    SceneObj_AudCameraWatcher = 0x11,
    SceneObj_AudEffectDirector = 0x12,
    SceneObj_AudBgmConductor = 0x13,
    SceneObj_ActionSoundSystem = 0x14, // NEW to SMG2
    SceneObj_MarioHolder = 0x15,
    SceneObj_16,
    SceneObj_MirrorCamera = 0x17,
    SceneObj_CameraContext = 0x18,
    SceneObj_NameObjGroup = 0x19, // TODO: Rename in both Petari and here to be IgnorePauseNameObjGroup or something
    SceneObj_TalkDirector = 0x1A,
    SceneObj_EventSequencer,
    SceneObj_StopSceneController,
    SceneObj_SceneNameObjMovementController,
    SceneObj_ImageEffectSystemHolder,
    SceneObj_BloomEffect,
    SceneObj_BloomEffectSimple,
    SceneObj_ScreenBlurEffect,
    SceneObj_DepthOfFieldBlur,
    SceneObj_PostFog, // NEW to SMG2
    SceneObj_PostOutline, // NEW to SMG2
    SceneObj_SceneWipeHolder,
    SceneObj_PlayerActionGuidance,
    SceneObj_LensFlareDirector,
    SceneObj_FurDrawManager,
    SceneObj_PlacementStateChecker,
    SceneObj_NamePosHolder,
    SceneObj_NPCDirector,
    SceneObj_ResourceShare,
    SceneObj_WarpPodMgr,
    SceneObj_CenterScreenBlur,
    SceneObj_SwitchingScreenEffect, // NEW to SMG2
    SceneObj_TimeStopScreenCaptureTexture, // NEW to SMG2
    SceneObj_TimeStopScreenCaptureEffect, // NEW to SMG2
    SceneObj_SwingActionWatcher, // NEW to SMG2
    SceneObj_WorldMap, // NEW to SMG2
    SceneObj_34, // NEW to SMG2
    SceneObj_35, // NEW to SMG2
    SceneObj_ScoreResultKeeper, // NEW to SMG2
    SceneObj_37, // NEW to SMG2
    SceneObj_SupportPlayDirector, // NEW to SMG2
    SceneObj_AllLiveActorGroup,
    SceneObj_CameraDirector,
    SceneObj_PlanetGravityManager,
    SceneObj_BaseMatrixFollowTargetHolder,
    SceneObj_GameSceneLayoutHolder,
    SceneObj_3E,
    SceneObj_CoinHolder,
    SceneObj_PurpleCoinHolder,
    SceneObj_CoinRotater,
    SceneObj_AirBubbleHolder,
    SceneObj_KarikariDirector,
    SceneObj_StarPieceDirector,
    SceneObj_BegomanAttackPermitter,
    SceneObj_BigFanHolder,
    SceneObj_KameckBeamHolder, // Not used in SMG2
    SceneObj_KameckFireBallHolder, // Not used in SMG2
    SceneObj_KameckBeamTurtleHolder, // Not used in SMG2
    SceneObj_KabokuriFireHolder,
    SceneObj_TakoHeiInkHolder,
    SceneObj_ShadowControllerHolder,
    SceneObj_4D, // NEW to SMG2
    SceneObj_ShadowVolumeDrawInit,
    SceneObj_ShadowSurfaceDrawInit,
    SceneObj_SwingRopeGroup,
    SceneObj_PlantStalkDrawInit,
    SceneObj_PlantLeafDrawInit,
    SceneObj_TrapezeRopeDrawInit,
    SceneObj_54,
    SceneObj_SpinDriverPathDrawInit,
    SceneObj_NoteGroup,
    SceneObj_ClipAreaDropHolder,
    SceneObj_FallOutFieldDraw,
    SceneObj_ClipFieldFillDraw,
    SceneObj_5A,
    SceneObj_ClipAreaHolder,
    SceneObj_SnowStepHolder, // NEW to SMG2
    SceneObj_ClipAreaLightFruit, // NEW to SMG2
    SceneObj_ScreenAlphaCapture,
    SceneObj_MapPartsRailGuideHolder,
    SceneObj_SpinCloudBlockGroup, // NEW to SMG2
    SceneObj_GCapture,
    SceneObj_SupportTico, // NEW to SMG2
    SceneObj_NameObjExecuteHolder,
    SceneObj_ElectricRailHolder,
    SceneObj_SpiderThread,
    SceneObj_QuakeEffectGenerator,
    SceneObj_KoopaBattleAccessor, // NEW to SMG2
    SceneObj_68,  // NEW to SMG2
    SceneObj_69,  // NEW to SMG2
    SceneObj_HeatHazeDirector,
    SceneObj_YellowChipHolder,
    SceneObj_EarthenPipeMediator,
    SceneObj_PetitPorterMediator, // NEW to SMG2
    SceneObj_6E, // NEW to SMG2
    SceneObj_WaterAreaHolder,
    SceneObj_WaterPlantDrawInit,
    SceneObj_RaceManager,
    SceneObj_GroupCheckManager,
    SceneObj_WaterPressureBulletHolder,
    SceneObj_FirePressureBulletHolder,
    SceneObj_SunshadeMapHolder,
    SceneObj_MiiFacePartsHolder,
    SceneObj_MiiFaceIconHolder,
    SceneObj_FluffWindHolder,
    SceneObj_GalaxyNamePlateDrawer,
    SceneObj_CinemaFrame,
    SceneObj_7B, // NEW to SMG2
    SceneObj_PlayerFollowPath, // NEW to SMG2
    SceneObj_InfernoMarioManager, // NEW to SMG2
    SceneObj_PlanetMapCreator,
    SceneObj_ProductMapCreator, // NEW to SMG2
    SceneObj_PriorDrawAirHolder,
    SceneObj_InformationObserver,
    SceneObj_StaffRoll,
    SceneObj_MapPartsHolder, // NEW to SMG2
    SceneObj_StarLightAreaHolder, // NEW to SMG2
    SceneObj_ChangeObjHolder, // NEW to SMG2
    SceneObj_DrillHoleHolder, // NEW to SMG2
    SceneObj_CollectTicoHolder, // NEW to SMG2
    SceneObj_IceMeteorHolder, // NEW to SMG2
    SceneObj_StoryBookWarpDemo, // NEW to SMG2
    SceneObj_PopoStickingManager, // NEW to SMG2
    SceneObj_KoopaJrCastleAccessor, // NEW to SMG2
    SceneObj_KoopaJrCastleWindHolder, // NEW to SMG2
    SceneObj_GliderShooterBulletHolder, // NEW to SMG2
    SceneObj_GhostAttackAccessor, // NEW to SMG2
    SceneObj_GliBirdTutorial, // NEW to SMG2
    SceneObj_PauseBlur, // NEW to SMG2
    SceneObj_StarPieceFlowerController, // NEW to SMG2
    SceneObj_WoodBoxExterminationFlagHolder, // NEW to SMG2
    SceneObj_MarioFaceShipSwitch, // NEW to SMG2
    SceneObj_94, // NEW to SMG2
    SceneObj_95, // NEW to SMG2
    SceneObj_96, // NEW to SMG2
    SceneObj_MarioFaceShipEventDataHolder, // NEW to SMG2
    SceneObj_WiiMessageBoardMailSender, // NEW to SMG2. Maybe needs to be renamed to use WC24 in the name?

    SceneObj_NumMax,
};

/// @brief The container for global scene objects.
class SceneObjHolder {
public:
    /// @brief Creates a new `SceneObjHolder`.
    SceneObjHolder();

    /// @brief Creates the requested object, returning the existing instance if it has already been created.
    /// @param id The index of the object.
    /// @return A pointer to the object.
    NameObj* create(int id);

    /// @brief Returns the requested object.
    /// @param id The index of the object.
    /// @return A pointer to the object.
    NameObj* getObj(int id) const;

    /// @brief Determines if the requested object has been created.
    /// @param id The index of the object.
    /// @return `true` if the object has been created, `false` otherwise.
    bool isExist(int id) const NO_INLINE;

    /// @brief Creates the requested object.
    /// @param id The index of the object.
    /// @return A pointer to the object.
    NameObj* newEachObj(int id);

    /// @brief The array of objects.
    /* 0x0 */ NameObj* mObj[0x99];
};

namespace MR {
    /// @brief Creates the requested global scene object, returning the existing instance if it has already been created.
    /// @param id The index of the object.
    /// @return A pointer to the object.
    NameObj* createSceneObj(int id);

    /// @brief Returns the container for global scene objects.
    /// @return A pointer to the container for global scene objects.
    SceneObjHolder* getSceneObjHolder() NO_INLINE;

    /// @brief Determines if the requested global scene object has been created.
    /// @param id The index of the object.
    /// @return `true` if the object has been created, `false` otherwise.
    bool isExistSceneObj(int id);

    /// @brief Returns the requested global scene object.
    /// @param id The index of the object.
    /// @return A pointer to the object.
    template < class T >
    T* getSceneObj(int id) {
        return static_cast< T* >(getSceneObjHolder()->getObj(id));
    }
};  // namespace MR