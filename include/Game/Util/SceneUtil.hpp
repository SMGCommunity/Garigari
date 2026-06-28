#pragma once

#include <JGeometry.hpp>
#include "Util/JMapInfo.hpp"

class NameObj;
class GameSystemSceneController;

namespace MR {
	s32 getCurrentScenarioNo();
	s32 getCurrentSelectedScenarioNo();
	void setCurrentScenarioNo(s32, s32);
	bool isScenarioDecided();
	GameSystemSceneController* getSceneController();

	const char* getCurrentStageName();
	bool isEqualSceneName(const char*);
	bool isEqualStageName(const char*);
	bool isValidZoneName(const char*);

    bool isPlacementLocalStage();

    TPos3f& getZonePlacementMtx(const JMapInfoIter &);

    void getCameraRailInfo(JMapInfoIter *, const JMapInfo **, s32, s32);

    void getRailInfo(JMapInfoIter *, const JMapInfo **, const JMapInfoIter &);

	s32 getChildObjNum(const JMapInfoIter&);
	void getChildObjName(const char**, const JMapInfoIter&, int);
	void initChildObj(NameObj*, const JMapInfoIter&, int);
};
