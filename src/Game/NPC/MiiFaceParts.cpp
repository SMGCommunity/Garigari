#include "Game/NPC/MiiFaceParts.hpp"
#include "Game/LiveActor/LiveActor.hpp"
#include "Game/NPC/MiiFaceRecipe.hpp"
#include "Game/Scene/SceneObjHolder.hpp"
#include "RFL_Model.h"

MiiFaceParts::MiiFaceParts(const char* pName, const MiiFaceRecipe& rRecipe) : LiveActor(pName), _90(), _94(), mRecipe(), _D0(), _D4() {
    // FIXME
    // decomp.me: https://decomp.me/scratch/cda1h
    // I know exactly how to fix this: change MiiFaceRecipe::mIndex from an s16 to a u16.
    // Problem is, I can't make changes to MiiFaceRecipe in a MiiFaceParts PR.
    // So, I have to wait for a new MiiFaceRecipe PR to be merged in order to get this function 100% matching.

    mRecipe = new MiiFaceRecipe(rRecipe);

    MR::createSceneObj(0x76);
}

MiiFaceParts::~MiiFaceParts() {}

void MiiFaceParts::init(const JMapInfoIter& rIter) {
    // FIXME
    // decomp.me: https://decomp.me/scratch/pkSj4
    // Need to figure out how to pass two parameters into new[]

    _94 = new u8[mRecipe->getModelBufferSize()]; // Can't figure out how to pass in 32 as the second parameter for new
    _90 = new RFLCharModel;
    _D5 = 1;
}

void MiiFaceParts::calcAnim() {
    /*
    r0: _D0
    r3: _D0
    r31: r3
    */
    if (_D0 != nullptr) {
        // Need FixedPosition.hpp to be created in order to continue this function.
    }
}
