#pragma once

#include <revolution/types.h>

class ActorStateBaseInterface;
class LiveActor;
class Nerve;
class NerveExecutor;

namespace MR {
    /// @brief Initializes and registers an actor state with a nerve executor.
    /// @param pExecutor The nerve executor that will manage this state.
    /// @param pActorState The state interface to initialize and register.
    /// @param pNerve The nerve associated with this state for state machine transitions.
    /// @param pStateName State name or identifier string for debugging/lookup purposes.
    /// @note The state interface's init() method will be called during this process.
    void initActorState(NerveExecutor* pExecutor, ActorStateBaseInterface* pActorState, const Nerve* pNerve, const char* pStateName);
    
    /// @brief Initializes and registers an actor state with a live actor.
    /// @param pExecutor The live actor that will manage this state.
    /// @param pActorState The state interface to initialize and register.
    /// @param pNerve The nerve associated with this state for state machine transitions.
    /// @param pStateName State name or identifier string for debugging/lookup purposes.
    /// @note The state interface's init() method will be called during this process.
    void initActorState(LiveActor* pExecutor, ActorStateBaseInterface* pActorState, const Nerve* pNerve, const char* pStateName);

        
    /// @brief Updates the current active state of a LiveActor.
    /// @param pActor The LiveActor whose current state should be updated.
    /// @return true if the current state was active and processed, false if no active state.
    /// @note Uses the executor's state keeper to update whichever state is currently active.
    bool updateActorState(LiveActor* pActor);
    
    /// @brief Updates an actor state and transitions to the next nerve if the state completed.
    /// @param pActor The live actor whose state should be updated.
    /// @param pNextNerve The nerve to transition to if the state update succeeds.
    /// @return True if the state was updated and nerve transition occurred, false otherwise.
    /// @note Only transitions to the next nerve if the state indicates it should update.
    bool updateActorStateAndNextNerve(LiveActor* pActor, const Nerve* pNextNerve);
    
    /// @brief Updates the current active state of a nerve executor.
    /// @param pExecutor The nerve executor whose current state should be updated.
    /// @return true if the current state was active and processed, false if no active state.
    /// @note Uses the executor's state keeper to update whichever state is currently active.
    bool updateActorState(NerveExecutor* pExecutor);
};  // namespace MR
