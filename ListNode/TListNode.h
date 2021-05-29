#ifndef HASHMAPLIB_TLISTNODE_H
#define HASHMAPLIB_TLISTNODE_H

template<class TK, class TV>
class TListNode {
protected:
    TK key;
    TV val;
    TListNode<TK, TV> *next;
public:
    TListNode();

    TListNode(TK k, TV v);

    TListNode(const TListNode &p);

    bool HasNext();
    void SetNext(TListNode* ptr);
    TListNode<TK, TV>* GetNext();
    TK GetKey();
    TV GetVal();
};
#endif 
