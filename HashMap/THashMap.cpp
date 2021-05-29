#include "THashMap.h"

template<class TK, class TV>
THashMap<TK, TV>::THashMap(int _size) {
    if (_size <= 0)
        throw std::invalid_argument("wrong map size");
    this->data = new TNode<TK, TV> *[_size];
    for (int i = 0; i < _size; ++i) {
        this->data[i] = nullptr;
    }
    this->size = _size;
    this->count = 0;
}

template<class TK, class TV>
THashMap<TK, TV>::THashMap(const THashMap& map) {
    if (this->size != 0) {
        for (int i = 0; i < this->size; ++i) {
            if (this->data[i])
                delete this->data[i];
        }
        delete[] this->data;
    }
    this->size = map.size;
    this->count = map.count;
    this->data = new TNode<TK, TV> *[map.size];
    for (int j = 0; j < this->size; ++j) {
        if (map.data[j] != nullptr) {
            this->data[j] = new TNode<TK, TV>(*(map.data[j]));
        }
        else {
            this->data[j] = nullptr;
        }
    }
}

template<class TK, class TV>
THashMap<TK, TV>::~THashMap() {
    if (this->size != 0) {
        for (int i = 0; i < this->size; ++i) {
            if (this->data[i])
                delete this->data[i];
        }
        delete[] this->data;
    }
}

template<class TK, class TV>
int THashMap<TK, TV>::Hash(TK key, int secret) {
    std::string s(key);
    int hash_result = 0;
    // обратный полиномиальный хеш h=(s0 + s1*k^n + s2*k^(n-1)+...+sN) mod size
    for (char i : s) {
        hash_result = (secret * hash_result + i) % this->size;
    }
    return hash_result;
}

template<class TK, class TV>
void THashMap<TK, TV>::Add(TK key, TV val) {
    if (this->count + 1 == this->size) {
        this->Resize();
    }

    int hash1 = this->Hash(key, this->size - 1);
    int hash2 = this->Hash(key, this->size + 1);

    int access_count = 0;
    while (this->data[hash1] != nullptr && access_count < this->size) {
        if (this->data[hash1]->deleted)
            break;
        hash1 = (hash1 + hash2) % this->size;
        access_count++;
    }

    if (this->data[hash1] == nullptr) {
        this->data[hash1] = new TNode<TK, TV>(key, val);
    }
    else {
        this->data[hash1]->SetKey(key);
        this->data[hash1]->SetVal(val);
        this->data[hash1]->deleted = false;
    }
    this->count++;
}

template<class TK, class TV>
TV THashMap<TK, TV>::Find(const TK& key) {
    int hash1 = this->Hash(key, this->size - 1);
    int hash2 = this->Hash(key, this->size + 1);

    int access_count = 0;
    bool deleted = false;
    while (this->data[hash1] != nullptr && access_count < this->size) {
        if (this->data[hash1]->GetKey() == key) {
            deleted = this->data[hash1]->deleted;
            break;
        }
        hash1 = (hash1 + hash2) % this->size;
        access_count++;
    }

    if (this->data[hash1] == nullptr || access_count == this->size || deleted) {
        throw std::invalid_argument("invalid key: no such record in the table");
    }
    else {
        return this->data[hash1]->GetVal();
    }
}

template<class TK, class TV>
void THashMap<TK, TV>::Delete(const TK& key) {
    int hash1 = this->Hash(key, this->size - 1);
    int hash2 = this->Hash(key, this->size + 1);

    int access_count = 0;
    while (this->data[hash1] != nullptr && access_count < this->size) {
        if (this->data[hash1]->GetKey() == key)
            break;
        hash1 = (hash1 + hash2) % this->size;
        access_count++;
    }

    if (this->data[hash1] != nullptr && access_count < this->size) {
        this->count--;
        this->data[hash1]->deleted = true;
    }
}

template<class TK, class TV>
TV THashMap<TK, TV>::operator[](const TK& key) {
    if (this->count + 1 == this->size) {
        this->Resize();
    }

    int hash1 = this->Hash(key, this->size - 1);
    int hash2 = this->Hash(key, this->size + 1);

    int access_count = 0;
    while (this->data[hash1] != nullptr && access_count < this->size) {
        if (this->data[hash1]->GetKey() == key)
            break;
        hash1 = (hash1 + hash2) % this->size;
        access_count++;
    }

    if (this->data[hash1] != nullptr && access_count < this->size) {
        return this->data[hash1]->GetVal();
    }
    else {
        this->data[hash1] = new TNode<TK, TV>(key, TV());
        this->count++;
        return TV();
    }
}

template<class TK, class TV>
void THashMap<TK, TV>::Resize() {
    const int new_size = this->size * 2;
    TNode<TK, TV>** new_data = new TNode<TK, TV>*[new_size];
    for (int i = 0; i < new_size; ++i) {
        new_data[i] = nullptr;
    }
    TNode<TK, TV>** tmp = this->data;
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
int THashMap<TK, TV>::GetCount() {
    return this->count;
}