#pragma once
#include "seq.h"

template <class T>
class SeqNode {
    friend class Seq<T>;
private:
    SeqNode(const T &v):
        value(v), next(nullptr), used(1) {};
    SeqNode(const T &, SeqNode *);

private:
    int used;
    SeqNode *next;
    const T value;
};

template <class T>
SeqNode<T>::SeqNode(const T &v, SeqNode<T> *s):
        value(v), next(s), used(1) {
    if (s) {
        ++s->used;
    }
}
