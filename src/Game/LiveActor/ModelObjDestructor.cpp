// This retail destructor is located separately from the main ModelObj methods.
// novtable suppresses duplicate data emission, without changing the class layout.
#define MODELOBJ_NO_VTABLE
#include "LiveActor/ModelObj.hpp"

ModelObj::~ModelObj() {}
