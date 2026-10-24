#pragma once

class NameObj;
class NameObjArchiveListCollector;
class JMapInfoIter;

typedef NameObj* (*CreatorFuncPtr)(const char*);
typedef void (*PostCreationFuncPtr)(const JMapInfoIter&);

namespace {
    template < typename T >
    NameObj* createNameObj(const char* pName) {
        return new T(pName);
    }
};  // namespace

/// @brief A namespace for creating `NameObj` instances.
namespace NameObjFactory {
    struct Name2CreateFunc {
        /* 0x0 */ const char* mName;
        /* 0x4 */ CreatorFuncPtr mCreateFunc;
    };

    struct Name2PostCreationFunc {
        /* 0x0 */ const char* mName;
        /* 0x4 */ PostCreationFuncPtr mCreateFunc;
    };

    const Name2CreateFunc* getName2CreateFunc(const char*);
    CreatorFuncPtr getCreator(const char*);
    void callPostCreation(const char*, const JMapInfoIter&);
    NameObj* initChildObj(const JMapInfoIter&, int);
};  // namespace NameObjFactory
