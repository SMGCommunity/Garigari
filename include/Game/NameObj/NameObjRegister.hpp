#pragma once

class NameObj;
class NameObjHolder;

class NameObjRegister {
public:
    NameObjRegister();

    void setCurrentHolder(NameObjHolder *);
    void add(NameObj *);

    NameObjHolder* mHolder;         // 0x00
};
