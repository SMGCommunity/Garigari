#pragma once

#include <revolution.h>

class NameObj;
class NameObjHolder;

class NameObjRegister {
public:
    NameObjRegister();

    void setCurrentHolder(NameObjHolder *);
    void add(NameObj *);
};