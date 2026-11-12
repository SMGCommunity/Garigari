#pragma once

#include "Game/LiveActor/LiveActor.hpp"
#include <JSystem/JGeometry/TMatrix.hpp>

class BreakModel;
class ModelObj;
class BenefitItemOneUp;

/// @brief A wooden box that can be destroyed through most of the player and enemy attacks. It can spawn various different items when destroyed.
class WoodBox : public LiveActor {
public:
    /// @brief Creates a new `WoodBox`.
    /// @param pName A pointer to the null-terminated name of the box.
    WoodBox(const char* pName);

    /// @brief Sets up the `WoodBox` and its fields based on the given BCSV information.
    /// @param rIter Reference to the `JMapInfoIter` that supplies BCSV information.
    virtual void init(const JMapInfoIter& rIter);

    /// @brief Causes the `WoodBox` to appear.
    virtual void appear();

    /// @brief Causes the `WoodBox` to disappear. If the box contains a Power Star, this function attempts to make that appear.
    virtual void kill();

    virtual void control();

    /// @brief This function is called when the player attacks the `WoodBox`. If the player punches it, freezes it, runs into it while invincible, or
    /// attacks it with a fireball or Koopa shell, the box will be damaged. The box will also be damaged if the player ground-pounds it, but only if
    /// the box's "floor touch timer" is not 0. However, if the box doesn't have any hit points left, nothing will happen.
    /// @param msg A number representing the type of attack performed by the player.
    /// @param pSender Pointer to a `HitSensor` of the attacking object making contact with the box.
    /// @param pReceiver Pointer to whichever of the box's `HitSensor`s was hit.
    virtual bool receiveMsgPlayerAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver);

    /// @brief This function is called when an enemy attacks the `WoodBox`. Unless the box doesn't have any hit points left, this will cause the box
    /// to be damaged.
    /// @param msg A number representing the type of attack performed by an enemy.
    /// @param pSender Pointer to a `HitSensor` of the attacking object making contact with the box.
    /// @param pReceiver Pointer to whichever of the box's `HitSensor`s was hit.
    virtual bool receiveMsgEnemyAttack(u32 msg, HitSensor* pSender, HitSensor* pReceiver);

    /// @brief This function is called when something other than a player or enemy attack makes contact with the `WoodBox`. If the floor makes contact
    /// with the box, the box's "floor touch timer" will be set to 2.
    /// @param msg A number representing the type of physical contact being made with the box.
    /// @param pSender Pointer to a `HitSensor` of the object making contact with the box.
    /// @param pReceiver Pointer to whichever of the box's `HitSensor`s was touched.
    virtual bool receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver);

    /// @brief This function is called whenever damage is done to the `WoodBox`. If the box already has no hit points, nothing happens. Otherwise, it
    /// will lose a hit point, and if no hit points remain after this, the box will break. Different sounds and effects will play depending on whether
    /// the box is in water. Also, the `BreakModel` will appear.
    void doHit();

    /// @brief Causes the `WoodBox` to reappear. If the box was previously destroyed, this function makes its `BreakModel` disappear and plays the
    /// "Appear" sound and effect.
    void forceReappear();

    void registerBreakModelDemoCast();

    /// @brief Once the `WoodBox` has been destroyed but before it's been removed from the world entirely, this function is called every frame. On the
    /// first frame after being destroyed, the box will be made intangible, and if it contains a Power Star, the Power Star will be made to appear. On
    /// the 15th frame after being destroyed, the "SW_DEAD" switch will be activated, the "Riddle" SFX will be played if enabled for this box, and
    /// whatever coins, Star Bits, and/or 1-Ups contained in this box will be spawned. If the box's `BreakModel` is dead, the box will be removed from
    /// the world entirely.
    void exeHit();

    /// @brief While the `WoodBox` has not yet been destroyed, this function is called every frame.
    void exeWait();

    /// @brief After the `WoodBox` has been removed from the world entirely, this function is called every frame. It does nothing.
    void exeKilled();

    /* 0x90 */ u16 mFloorTouchTimer;
    /* 0x92 */ u16 _92;
    /* 0x94 */ u16 _94;

    /// @brief How many hit points the `WoodBox` has left. The box will only ever have 1 hit point at most, and a hit point will be subtracted each time it is damaged. The moment the box reaches 0 hit points, it will be destroyed.
    /* 0x96 */ u16 mHitPoint;

    /// @brief Whether the `WoodBox` contains a Power Star. Default is `false`.
    /* 0x98 */ bool mHasPowerStar;

    /// @brief Whether the broken remnants are shown when destroyed. Default is `true`.
    /* 0x99 */ bool mShowBrokenRemnants;

    /// @brief Whether the "Riddle" jingle is played when broken. Default is `false`.
    /* 0x9A */ bool mPlayRiddleSFX;

    /* 0x9C */ TPos3f mBaseMtx;

    /// @brief The number of coins to be spawned when destroyed. Default is 1.
    /* 0xCC */ s32 mCoinCount;

    /// @brief The number of Star Bits to be spawned when destroyed. Default is 0.
    /* 0xD0 */ s32 mStarPieceCount;

    /* 0xD4 */ BreakModel* mBreakModel;

    /// @brief Pointer to the Power Star model to be used in a cutscene that will play when destroyed. If the box doesn't contain a Power Star, this value is `nullptr`. Default is `nullptr`.
    /* 0xD8 */ ModelObj* mStarDemoModel;

    /// @brief Pointer to the 1-Up that will be spawned when destroyed. If the box doesn't contain a 1-Up, this value is `nullptr`. Default is `nullptr`.
    /* 0xDC */ BenefitItemOneUp* mOneUp;
};
