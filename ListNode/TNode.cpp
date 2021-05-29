#include "TNode.h"

template<class TK, class TV>
TNode<TK, TV>::TNode(TK k, TV v) {
    this->key = k;
    this->val = v;
}

template<class TK, class TV>
TNode<TK, TV>::TNode(const TNode& p) {
    this->key = p.key;
    this->val = p.val;
}

template<class TK, class TV>
TK TNode<TK, TV>::GetKey() {
    return this->key;
}

template<class TK, class TV>
TV TNode<TK, TV>::GetVal() {
    return this->val;
}

template<class TK, class TV>
void TNode<TK, TV>::SetKey(TK k) {
    this->key = k;
}

template<class TK, class TV>
void TNode<TK, TV>::SetVal(TV v) {
    this->val = v;
}

template<class TK, class TV>
TNode<TK, TV>& TNode<TK, TV>::operator=(const TNode& p) {
    this->key = p.key;
    this->val = p.val;
    return *this;
}

template<class TK, class TV>
bool TNode<TK, TV>::operator==(TNode& p) {
    return this->key == p.key;
}

template<class TK, class TV>
bool TNode<TK, TV>::operator>(TNode& p) {
    return this->key > p.key;
}

template<class TK, class TV>
bool TNode<TK, TV>::operator<(TNode& p) {
    return this->key < p.key;
}

template<class TK, class TV>
bool TNode<TK, TV>::operator<=(TNode& p) {
    return this->key <= p.key;
}

template<class TK, class TV>
bool TNode<TK, TV>::operator>=(TNode& p) {
    return this->key >= p.key;
}

template<class TK, class TV>
TNode<TK, TV>::TNode() {}
