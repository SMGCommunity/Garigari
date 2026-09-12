#pragma once

#include <revolution.h>

/* FINISHED */

class LiveActor;
class HitSensor;

namespace MR {
	void setSupportTicoAttachRangeGliBird();
	void resetSupportTicoAttachRangeGliBird();
	void setSupportTicoAttachRangeTubeSlider();
	void resetSupportTicoAttachRangeTubeSlider();
	void setSupportTicoFollowPlayerYDir();
	void resetSupportTicoFollowPlayerYDir();

	void offSupportTicoControl();
	void onSupportTicoControl();
	void requestSupportTicoMovementOn();
	void requestSupportTicoHide();
	void requestSupportTicoShow();
	bool isSupportTicoShow();

	bool attachSupportTicoToTarget(const LiveActor* pTarget);

	void joinSupportPlayGroup(LiveActor* pActor);
	bool isSupportPlayActive();
	bool isNeedExplainSupportTico();

	bool isMsgSupportPlayGroupStart(u32 msg);
	bool isMsgSupportPlayGroupStop(u32 msg);
	bool isMsgItemSupportTicoDemoShow(u32 msg);
	bool isMsgItemSupportTicoDemoHide(u32 msg);

	bool sendMsgSupportPlayGroupStart(LiveActor* pActor);
	bool sendMsgSupportPlayGroupStop(LiveActor* pActor);
	bool sendMsgSupportTicoSpin(HitSensor* pSender, HitSensor* pReceiver);
};
