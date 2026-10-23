#pragma once

#include "Game/NameObj/NameObjGroup.hpp"

class LiveActor;

class LiveActorGroup : public NameObjGroup {
public:
    LiveActorGroup(const char*, int);

    inline virtual ~LiveActorGroup() {
    }

    void registerActor(LiveActor*);
    LiveActor* getActor(int) const;
    LiveActor* getDeadActor() const;
    s32 getLivingActorNum() const;
    void killAll();
    void appearAll();
    void makeAllDead();
};

template < typename T >
class DeriveActorGroup : public LiveActorGroup {
public:
    /// @brief Creates a new `DeriveActorGroup`.
    /// @param pName A pointer to the null-terminated name of the object.
    /// @param numMax The maximum allowed number of derived `LiveActor` instances in the group.
    DeriveActorGroup(const char* pName, int numMax) : LiveActorGroup(pName, numMax) {
    }

    T* getMember(int index) const {
        return static_cast< T* >(getActor(index));
    }

    T* getDeadMember() const {
        if (getDeadActor() != nullptr) {
            T* pActor = static_cast< T* >(getDeadActor());
            return pActor;
        }

        return nullptr;
    }
};
