#pragma once

#include <revolution.h>
#include "Util/Functor.hpp"

class JMapInfoIter;
class LiveActor;

namespace MR {
	bool useStageSwitchReadA(LiveActor* pActor, const JMapInfoIter& rIter);
	bool useStageSwitchReadB(LiveActor* pActor, const JMapInfoIter& rIter);
	bool useStageSwitchReadAppear(LiveActor* pActor, const JMapInfoIter& rIter);
	bool useStageSwitchWriteA(LiveActor* pActor, const JMapInfoIter& rIter);
	bool useStageSwitchWriteB(LiveActor* pActor, const JMapInfoIter& rIter);
	bool initUseStageSwitchReadA(LiveActor* pActor, const JMapInfoIter& rIter);
	bool initUseStageSwitchReadB(LiveActor* pActor, const JMapInfoIter& rIter);
	bool initUseStageSwitchReadAppear(LiveActor* pActor, const JMapInfoIter& rIter);
	bool useStageSwitchAwake(LiveActor* pActor, const JMapInfoIter& rIter);

	bool initUseStageSwitchWriteA(LiveActor* pActor, const JMapInfoIter& rIter);
	bool initUseStageSwitchWriteB(LiveActor* pActor, const JMapInfoIter& rIter);
	bool useStageSwitchWriteDead(LiveActor* pActor, const JMapInfoIter& rIter);
	bool initUseStageSwitchWriteDead(LiveActor* pActor, const JMapInfoIter& rIter);
	bool useStageSwitchWriteAutoDead(LiveActor* pActor, const JMapInfoIter& rIter);

	bool needStageSwitchReadA(LiveActor* pActor, const JMapInfoIter& rIter);
	bool needStageSwitchReadB(LiveActor* pActor, const JMapInfoIter& rIter);
	bool needStageSwitchReadAppear(LiveActor* pActor, const JMapInfoIter& rIter);
	bool needStageSwitchWriteA(LiveActor* pActor, const JMapInfoIter& rIter);
	bool needStageSwitchWriteB(LiveActor* pActor, const JMapInfoIter& rIter);
	bool needStageSwitchWriteDead(LiveActor* pActor, const JMapInfoIter& rIter);
	bool needStageSwitchWriteAutoDead(LiveActor* pActor, const JMapInfoIter& rIter);

	bool isValidSwitchA(const LiveActor* pActor);
	bool isValidSwitchB(const LiveActor* pActor);
	bool isValidSwitchAppear(const LiveActor* pActor);
	bool isValidSwitchDead(const LiveActor* pActor);

	bool isOnSwitchA(const LiveActor* pActor);
	bool isOnSwitchB(const LiveActor* pActor);
	bool isOnSwitchAppear(const LiveActor* pActor);

	bool onSwitchA(LiveActor* pActor);
	bool onSwitchB(LiveActor* pActor);
	bool onSwitchDead(LiveActor* pActor);
	bool offSwitchA(LiveActor* pActor);
	bool offSwitchB(LiveActor* pActor);
	bool offSwitchDead(LiveActor* pActor);

	void syncStageSwitchAppear(LiveActor* pActor);
	bool useStageSwitchSyncAppear(LiveActor* pActor, const JMapInfoIter& rIter);
	void syncStageSwitchAppearAndSync(LiveActor* pActor, const JMapInfoIter& rIter);

	void listenStageSwitchOnAppear(LiveActor* pActor, const MR::FunctorBase& rFunctor);
	void listenStageSwitchOnOffAppear(LiveActor* pActor, const MR::FunctorBase& rFunctorOn, const MR::FunctorBase& rFunctorOff);
	void listenStageSwitchOnA(LiveActor* pActor, const MR::FunctorBase& rFunctor);
	void listenStageSwitchOnOffA(LiveActor* pActor, const MR::FunctorBase& rFunctorOn, const MR::FunctorBase& rFunctorOff);
	void listenStageSwitchOnB(LiveActor* pActor, const MR::FunctorBase& rFunctor);
	void listenStageSwitchOffB(LiveActor* pActor, const MR::FunctorBase& rFunctor);
	void listenStageSwitchOnOffB(LiveActor* pActor, const MR::FunctorBase& rFunctorOn, const MR::FunctorBase& rFunctorOff);

	bool useStageSwitchReadParam(LiveActor* pActor, const JMapInfoIter& rIter);
	bool isValidSwitchParam(const LiveActor* pActor);
	bool isOnSwitchParam(const LiveActor* pActor);
};
