#pragma once

#include "Game/LiveActor/LiveActorGroup.hpp"
#include <JSystem/JGeometry/TMatrix.hpp>

class CollectTico;

class CollectTicoHolder : public DeriveActorGroup< CollectTico > {
public:
    CollectTicoHolder();
};

namespace MR {
    void registerCollectTico(CollectTico*);
    void launchRescuedStrayTico(const TPos3f&);
}