#include "TListNode.h"

template<class TK, class TV>
TListNode<TK, TV>::TListNode(const TListNode& p) {
    if (this != &p) {
        this->key = p.key;
        this->val = p.val;
        this->next = nullptr;
    }
}

template<class TK, class TV>
bool TListNode<TK, TV>::HasNext() {
    return this->next != nullptr;
}

template<class TK, class TV>
void TListNode<TK, TV>::SetNext(TListNode* ptr) {
    this->next = ptr;
}

template<class TK, class TV>
TListNode<TK, TV>::TListNode(TK k, TV v) {
    this->key = k;
    this->val = v;
    this->next = nullptr;
}

template<class TK, class TV>
TListNode<TK, TV>::TListNode() {
    this->key = TK();
    this->val = TV();
    this->next = nullptr;
}

template<class TK, class TV>
TListNode<TK, TV>* TListNode<TK, TV>::GetNext() {
    return this->next;
}

template<class TK, class TV>
TK TListNode<TK, TV>::GetKey() {
    return this->key;
}

template<class TK, class TV>
TV TListNode<TK, TV>::GetVal() {
    return this->val;
}
