#pragma once

#include "Game/LiveActor/ModelObj.hpp"

class MiniEarthenPipe : public ModelObj {
public:
    MiniEarthenPipe();

    virtual void control();

    bool fn_804E3420();  // TODO: better name

    bool isPointing() const;
};
