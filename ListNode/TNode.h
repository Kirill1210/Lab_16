#ifndef MAPLIB_TNODE_H
#define MAPLIB_TNODE_H


template <class TK, class TV>
class TNode {
protected:
    TK key;
    TV val;
    bool deleted = false;
public:
    TNode();
    TNode(TK k , TV v);
    TNode(const TNode &p);

    TK GetKey();
    TV GetVal();

    void SetKey(TK k);
    void SetVal(TV v);

    TNode &operator=(const TNode &p);

    bool operator==(TNode &p);
    bool operator>(TNode &p);
    bool operator<(TNode &p);
    bool operator<=(TNode &p);
    bool operator>=(TNode &p);
    template <class TTK, class TTV> friend class THashMap;
};
#endif 
