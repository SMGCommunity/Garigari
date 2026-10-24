#include "Game/NameObj/NameObjFactory.hpp"
#include "Game/Map/PlanetMapCreator.hpp"
#include "Game/Util/SceneUtil.hpp"
#include "Game/Util/StringUtil.hpp"

namespace MR {
    bool hasProductMapCreator(const char*);
    CreatorFuncPtr getProductMapCreator(const char*);
};  // namespace MR

namespace NameObjFactory {
    const Name2CreateFunc cCreateTable[977] = {
        // ...
    };

    const Name2PostCreationFunc cPostCreationTable[27] = {
        // ...
    };

    inline const Name2CreateFunc* getName2CreateFunc(const char* pName) {
        for (const Name2CreateFunc* pName2CreateFunc = cCreateTable; pName2CreateFunc != cCreateTable + ARRAY_SIZE(cCreateTable);
             pName2CreateFunc++) {
            if (pName2CreateFunc->mName == nullptr) {
                continue;
            }

            if (!MR::isEqualStringCase(pName2CreateFunc->mName, pName)) {
                continue;
            }

            return pName2CreateFunc;
        }

        return nullptr;
    }

    CreatorFuncPtr getCreator(const char* pName) {
        if (PlanetMapCreatorFunction::isRegisteredObj(pName)) {
            return PlanetMapCreatorFunction::getPlanetMapCreator(pName);
        }

        if (MR::hasProductMapCreator(pName)) {
            return MR::getProductMapCreator(pName);
        }

        const Name2CreateFunc* pName2CreateFunc = getName2CreateFunc(pName);

        if (pName2CreateFunc == nullptr) {
            return nullptr;
        }

        return pName2CreateFunc->mCreateFunc;
    }

    void callPostCreation(const char* pName, const JMapInfoIter& rIter) {
        for (const Name2PostCreationFunc* pName2PostCreationFunc = cPostCreationTable;
             pName2PostCreationFunc != cPostCreationTable + ARRAY_SIZE(cPostCreationTable); pName2PostCreationFunc++) {
            if (!MR::isEqualString(pName2PostCreationFunc->mName, pName)) {
                continue;
            }

            pName2PostCreationFunc->mCreateFunc(rIter);
        }
    }

    NameObj* initChildObj(const JMapInfoIter& rIter, int idx) {
        const char* name = nullptr;
        MR::getChildObjName(&name, rIter, idx);

        CreatorFuncPtr creator = getCreator(name);
        NameObj* pObj = creator(MR::getJapaneseObjectName(name));
        MR::initChildObj(pObj, rIter, idx);

        return pObj;
    }
};  // namespace NameObjFactory
