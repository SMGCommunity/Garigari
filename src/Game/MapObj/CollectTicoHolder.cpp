#include "Game/MapObj/CollectTicoHolder.hpp"
#include "Game/NPC/CollectTico.hpp"
#include "Game/Scene/SceneObjHolder.hpp"

CollectTicoHolder::CollectTicoHolder() : DeriveActorGroup< CollectTico >("チコ集め管理", 16) {

}

namespace MR {
    void registerCollectTico(CollectTico* ct) {
        MR::createSceneObj(SceneObj_CollectTicoHolder);
        MR::getSceneObj< CollectTicoHolder >(SceneObj_CollectTicoHolder)->registerActor(ct);
    }
    void launchRescuedStrayTico(const TPos3f& position) {
        if (!MR::isExistSceneObj(SceneObj_CollectTicoHolder))
            return;

        CollectTicoHolder* holder = MR::getSceneObj< CollectTicoHolder >(SceneObj_CollectTicoHolder);
        s32 count = holder->getObjectCount();
        for (s32 i = 0; i < count; i++) {
            holder->getMember(i)->launch(position);
        }
    }
}