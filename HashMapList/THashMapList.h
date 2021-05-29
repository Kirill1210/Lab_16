#ifndef HASHMAPLIB_THASHMAPLIST_H
#define HASHMAPLIB_THASHMAPLIST_H

#include <stdexcept>
#include "TListNode.cpp"

template<class TK, class TV>
class THashMapList {
protected:
    TListNode<TK, TV> **data;
    int size;
    int count;
    void Resize();

public:
    explicit THashMapList(int _size = 1000);

    THashMapList(const THashMapList &map);
    ~THashMapList();

    int Hash(TK key, int secret);
    void Add(TK key, TV val);
    TV Find(const TK &key);
    void Delete(const TK &key);
    TV operator[](const TK &key);
    int GetCount();
};
#endif 
