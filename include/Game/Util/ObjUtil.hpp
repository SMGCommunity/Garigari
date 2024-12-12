#pragma once

class NameObj;

namespace MR {
    void requestMovementOn(NameObj *);
    void requestMovementOff(NameObj *);

    void connectToScene(NameObj *, int, int, int, int);
};
