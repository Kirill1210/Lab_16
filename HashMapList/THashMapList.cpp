#include "THashMapList.h"

template<class TK, class TV>
THashMapList<TK, TV>::THashMapList(int _size) {
    if (_size <= 0)
        throw std::invalid_argument("wrong map size");
    this->data = new TListNode<TK, TV> *[_size];
    for (int i = 0; i < _size; ++i) {
        this->data[i] = nullptr;
    }
    this->size = _size;
    this->count = 0;
}

template<class TK, class TV>
THashMapList<TK, TV>::THashMapList(const THashMapList& map) {
    if (this->size != 0) {
        for (int i = 0; i < this->size; ++i) {
            if (this->data[i]) {
                TListNode<TK, TV>* tmp;
                TListNode<TK, TV>* node = this->data[i];
                while (node->HasNext()) {
                    tmp = node->GetNext();
                    delete node;
                    node = tmp;
                }
                delete node;
            }
        }
        delete[] this->data;
    }
    this->size = map.size;
    this->count = map.count;
    this->data = new TListNode<TK, TV> *[map.size];
    for (int j = 0; j < this->size; ++j) {
        if (map.data[j] != nullptr) {
            TListNode<TK, TV>* ptr = map.data[j];
            this->data[j] = new TListNode<TK, TV>(*(ptr));
            TListNode<TK, TV>* inner = this->data[j];
            while (ptr->HasNext()) {
                ptr = ptr->GetNext();
                auto* tmp = new TListNode<TK, TV>(*(ptr));
                inner->SetNext(tmp);
                inner = tmp;
            }
        }
        else {
            this->data[j] = nullptr;
        }
    }
}

template<class TK, class TV>
THashMapList<TK, TV>::~THashMapList() {
    if (this->size != 0) {
        for (int i = 0; i < this->size; ++i) {
            if (this->data[i]) {
                TListNode<TK, TV>* tmp;
                TListNode<TK, TV>* node = this->data[i];
                while (node->HasNext()) {
                    tmp = node->GetNext();
                    delete node;
                    node = tmp;
                }
                delete node;
            }
        }
        delete[] this->data;
    }
}

template<class TK, class TV>
int THashMapList<TK, TV>::Hash(TK key, int secret) {
    std::string s(key);
    int hash_result = 0;
    for (char i : s) {
        hash_result = (secret * hash_result + i) % this->size;
    }
    return hash_result;
}

template<class TK, class TV>
void THashMapList<TK, TV>::Add(TK key, TV val) {
    if (this->count + 1 == this->size) {
        this->Resize();
    }

    int hash = this->Hash(key, this->size - 1);
    if (this->data[hash] == nullptr) {
        this->data[hash] = new TListNode<TK, TV>(key, val);
    }
    else {
        TListNode<TK, TV>* node = this->data[hash];
        while (node->HasNext()) {
            node = node->GetNext();
        }
        node->SetNext(new TListNode<TK, TV>(key, val));
    }
    this->count++;
}

template<class TK, class TV>
TV THashMapList<TK, TV>::Find(const TK& key) {
    int hash = this->Hash(key, this->size - 1);
    if (this->data[hash] != nullptr) {
        TListNode<TK, TV>* node = this->data[hash];
        if (node->GetKey() == key) {
            return node->GetVal();
        }
        while (node->HasNext()) {
            node = node->GetNext();
            if (node->GetKey() == key) {
                return node->GetVal();
            }
        }
    }
    throw std::invalid_argument("invalid key: no such record in the table");
}

template<class TK, class TV>
void THashMapList<TK, TV>::Delete(const TK& key) {
    int hash = this->Hash(key, this->size - 1);
    if (this->data[hash] != nullptr) {
        TListNode<TK, TV>* prev = this->data[hash];
        TListNode<TK, TV>* node = this->data[hash];
        if (node->GetKey() == key) {
            if (node->HasNext()) {
                prev = node->GetNext();
                delete node;
                this->count--;
                this->data[hash] = prev;
            }
        }
        else {
            while (node->HasNext()) {
                prev = node;
                node = node->GetNext();
                if (node->GetKey() == key) {
                    prev->SetNext(node->GetNext());
                    delete node;
                    this->count--;
                }
            }
        }
    }
}

template<class TK, class TV>
TV THashMapList<TK, TV>::operator[](const TK& key) {
    int hash = this->Hash(key, this->size - 1);
    if (this->data[hash] != nullptr) {
        TListNode<TK, TV>* node = this->data[hash];
        if (node->GetKey() == key) {
            return node->GetVal();
        }
        while (node->HasNext()) {
            node = node->GetNext();
            if (node->GetKey() == key) {
                return node->GetVal();
            }
        }
    }
    this->data[hash] = new TListNode<TK, TV>(key, TV());
    this->count++;
    return TV();
}

template<class TK, class TV>
void THashMapList<TK, TV>::Resize() {
    const int new_size = this->size * 2;
    TListNode<TK, TV>** new_data = new TListNode<TK, TV>*[new_size];
    for (int i = 0; i < new_size; ++i) {
        new_data[i] = nullptr;
    }
    TListNode<TK, TV>** tmp = this->data;
    const int old_size = this->size;
    this->data = new_data;
    this->size = new_size;
    for (int j = 0; j < old_size; ++j) {
        this->Add(tmp[j]->GetKey(), tmp[j]->GetVal());
    }

    for (int k = 0; k < old_size; ++k) {
        if (tmp[k] != nullptr)
            delete tmp[k];
    }
    delete[] tmp;
}

template<class TK, class TV>
int THashMapList<TK, TV>::GetCount() {
    return this->count;
}
