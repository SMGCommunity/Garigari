#include "Util/JMapUtil.hpp"
#include "Util/JMapInfo.hpp"
#include "Util/StringUtil.hpp"

namespace MR {
    
};

namespace {
    bool getJMapInfoArgNoInit(const JMapInfoIter &rIter, const char *pKey, s32 *pOut) {
        s32 val;
        if (!rIter.getValue<s32>(pKey, &val)) {
            return false;
        }

        if (val != -1) {
            *pOut = val;
            return true;
        }

        return false;
    }

    bool getJMapInfoArgNoInit(const JMapInfoIter &, const char *, f32 *);
    bool getJMapInfoArgNoInit(const JMapInfoIter &, const char *, bool *);
};

namespace MR {
    bool isConnectedWithRail(const JMapInfoIter &rIter) {
        if (!rIter.isValid()) {
            return false;
        }

        const char* key = "CommonPath_ID";
        s32 pathID = -1;
        return !::getJMapInfoArgNoInit(rIter, key, &pathID) ? false : pathID != -1;
    }

    bool isExistStageSwitchA(const JMapInfoIter &rIter) {
        if (!rIter.isValid()) {
            return false;
        }

        s32 id = -1;
        ::getJMapInfoArgNoInit(rIter, "SW_A", &id);
        return id != -1;
    }
    
    bool isExistStageSwitchB(const JMapInfoIter &rIter) {
        if (!rIter.isValid()) {
            return false;
        }

        s32 id = -1;
        ::getJMapInfoArgNoInit(rIter, "SW_B", &id);
        return id != -1;
    }

    bool isExistStageSwitchAppear(const JMapInfoIter &rIter) {
        if (!rIter.isValid()) {
            return false;
        }

        s32 id = -1;
        ::getJMapInfoArgNoInit(rIter, "SW_APPEAR", &id);
        return id != -1;
    }

    bool isExistStageSwitchDead(const JMapInfoIter &rIter) {
        if (!rIter.isValid()) {
            return false;
        }

        s32 id = -1;
        ::getJMapInfoArgNoInit(rIter, "SW_DEAD", &id);
        return id != -1;
    }

    bool isExistStageSwitchAwake(const JMapInfoIter &rIter) {
        if (!rIter.isValid()) {
            return false;
        }

        s32 id = -1;
        ::getJMapInfoArgNoInit(rIter, "SW_AWAKE", &id);
        return id != -1;
    }

    bool isExistStageSwitchParam(const JMapInfoIter &rIter) {
        if (!rIter.isValid()) {
            return false;
        }

        s32 id = -1;
        ::getJMapInfoArgNoInit(rIter, "SW_PARAM", &id);
        return id != -1;
    }

    bool isExistMessageId(const JMapInfoIter &rIter) {
        if (!rIter.isValid()) {
            return false;
        }

        s32 id = -1;
        ::getJMapInfoArgNoInit(rIter, "MessageId", &id);
        return id != -1;
    }

    bool isEqualObjectName(const JMapInfoIter  &rIter, const char *pName) {
        const char* name;
        MR::getObjectName(&name, rIter);
        return MR::isEqualStringCase(name, pName);
    }
};
