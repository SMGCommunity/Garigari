#pragma once

#include "LiveActor/LiveActor.hpp"

class BreakModel : public LiveActor {
public:
	BreakModel(LiveActor *pHost, const char *pName, const char *pModelName, MtxPtr pMtx, const char *pAnimName);

	virtual ~BreakModel();
	virtual void init(const JMapInfoIter &rIter);
	virtual void appear();
	virtual void calcAndSetBaseMtx();

	void exeBreak();

	LiveActor* mHost;      // _90
	const char* mAnimName; // _94
	MtxPtr mMtx;           // _98
};