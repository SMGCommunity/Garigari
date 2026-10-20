#pragma once

class NameObj;

// There is a bunch of stuff to define here, but I am too lazy for most of it.

namespace MR {
    void connectToSceneTemporarily(NameObj*);
    void disconnectToSceneTemporarily(NameObj*);
    void connectToDrawTemporarily(NameObj*);
    void disconnectToDrawTemporarily(NameObj*);
}
