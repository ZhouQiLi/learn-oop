#pragma once

template <class T>
class SeqNode;

template <class T>
class Seq {
public:
    Seq():
        data(nullptr) {}
    Seq(const T &v, const Seq<T> &s):
        data(new SeqNode<T>(v, s.data)) {}
    Seq(const Seq<T> &s):
            data(s.data) {
        if (data) {
            ++data->used;
        }
    }

    ~Seq() {
        Destroy(data);
        data = nullptr;
    };

    explicit operator bool() const;
    Seq &operator=(const Seq &);
    Seq &operator++();
    Seq &operator++(int);
    T operator*();
    T Head() const;
    Seq Tail() const;
    Seq &InsertHead(const T &);

private:
    explicit Seq(SeqNode<T> *s):
            data(s) {
        if (data) {
            ++data->used;
        }
    }

    void Destroy(SeqNode<T> *);
private:
    SeqNode<T> *data;
};

template <class T>
Seq<T>::operator bool() const {
    return data != nullptr;
};

template <class T>
Seq<T> &Seq<T>::operator=(const Seq<T> &s) {
    if (&s != this) {
        if (s.data) {
            ++s.data->used;
        }
        Destroy(data);
        data = s.data;
    }
    return *this;
}

template <class T>
Seq<T> &Seq<T>::operator++() {
    if (data) {
        auto p = data->next;
        if (p) {
            ++p->used;
        }
        if (--data->used == 0) {
            delete data;
        }
        data = p;
    }

    return *this;
}

template <class T>
Seq<T> &Seq<T>::operator++(int) {
    auto result = *this;
    if (data) {
        --data->used;
        data = data->next;
        if (data) {
            ++data->used;
        }
    }
    return result;
}

template <class T>
T Seq<T>::operator*() {
    return Head();
}

template <class T>
T Seq<T>::Head() const {
    if (data) {
        return data->value;
    } else {
        throw "tail of an empty Seq";
    }
}

template <class T>
Seq<T> Seq<T>::Tail() const {
    if (data) {
        return Seq<T>(data->next);
    } else {
        throw "tail of an empty Seq";
    }
}

template <class T>
Seq<T> &Seq<T>::InsertHead(const T &t) {
    auto p = new SeqNode<T>(t, data);
    --data->used;
    data = p;
    return *this;
}

template <class T>
void Seq<T>::Destroy(SeqNode<T> *node) {
    while (node && --node->used == 0) {
        auto next = node->next;
        delete node;
        node = next;
    }
}

template <class T>
Seq<T> Cons(const T &t, const Seq<T> &s) {
    return Seq<T>(t, s);
}
