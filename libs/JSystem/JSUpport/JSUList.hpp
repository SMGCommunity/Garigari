#pragma once

#include <revolution.h>

class JSUPtrLink;

class JSUPtrList {
public:
    inline JSUPtrList() {
        initiate();
    }

    JSUPtrList(bool);
    ~JSUPtrList();

    void initiate();
    void setFirst(JSUPtrLink *);
    bool append(JSUPtrLink *);
    bool prepend(JSUPtrLink *);
    bool insert(JSUPtrLink *, JSUPtrLink *);
    bool remove(JSUPtrLink *);

    JSUPtrLink* getFirstLink() const { 
        return mHead; 
    }

    u32 getNumLinks() const { 
        return mNodeCount; 
    }

    JSUPtrLink *mHead;  // 0x0
    JSUPtrLink *mTail;  // 0x4
    u32 mNodeCount;     // 0x8
};

class JSUPtrLink {
public:
    JSUPtrLink(void *);
    ~JSUPtrLink();

    void* getObjectPtr() const { 
        return mData; 
    }

    JSUPtrList* getList() const { 
        return mPtrList; 
    }

    JSUPtrLink* getNext() const { 
        return mNext;
    }

    void *mData;            // 0x0
    JSUPtrList *mPtrList;   // 0x4
    JSUPtrLink *mPrev;      // 0x8
    JSUPtrLink *mNext;      // 0xC
};

template<class T>
class JSULink : public JSUPtrLink {
public:
    JSULink(void *pData) : JSUPtrLink(pData) {

    }

    ~JSULink() NO_INLINE {

    }

    T* getObject() const { 
        return (T*)getObjectPtr(); 
    }

    JSULink<T>* getNext() const { 
        return (JSULink<T>*)this->JSUPtrLink::getNext(); 
    }

    JSULink<T>* getPrev() const { 
        return (JSULink<T>*)this->JSUPtrLink::getPrev(); 
    }
};
