#ifndef HASHMAPLIB_THASHMAP_H
#define HASHMAPLIB_THASHMAP_H

#include <stdexcept>
#include "TNode.cpp"

template<class TK, class TV>
class THashMap {
protected:
    TNode<TK, TV> **data;
    int size;
    int count;
    void Resize();

public:
    explicit THashMap(int _size = 1000);

    THashMap(const THashMap &map);

    ~THashMap();

    int Hash(TK key, int secret);

    void Add(TK key, TV val);

    TV Find(const TK &key);

    void Delete(const TK &key);

    TV operator[](const TK &key);


    int GetCount();
};
#endif 
