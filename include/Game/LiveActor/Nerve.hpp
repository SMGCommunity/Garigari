#pragma once

class Spine;

class Nerve {
public:
    inline Nerve() {}

    virtual void execute(Spine *) const = 0;
    virtual void executeOnEnd(Spine *) const;
};

#define NERVE(name, parent_class, executor_name)\
class name : public Nerve\
{\
public:\
    name() NO_INLINE {\
    };\
    virtual void execute(Spine *pSpine) const {\
        parent_class* actor = reinterpret_cast<parent_class*>(pSpine->mExecutor);\
        actor->exe##executor_name();\
    };\
    static name sInstance;\
};\
name name::sInstance;\

#define NERVE_ONEND(name, parent_class, func, onEndFunc)\
class name : public Nerve\
{\
public:\
    name() NO_INLINE {\
    };\
    virtual void execute(Spine *pSpine) const {\
        parent_class* actor = reinterpret_cast<parent_class*>(pSpine->mExecutor);\
        actor->func();\
    };\
    virtual void executeOnEnd(Spine *pSpine) const {\
        parent_class* actor = reinterpret_cast<parent_class*>(pSpine->mExecutor);\
        actor->onEndFunc();\
    };\
    static name sInstance;\
};\
name name::sInstance;\
