
#include <iostream>
#include "seq.h"
#include "seq_node.h"

int main() {
    auto *sp = new Seq<int>;
    *sp = Seq<int>(3, *sp);
    *sp = Seq<int>(4, *sp);
    *sp = Seq<int>(5, *sp);
    *sp = Cons(6, *sp);
    sp->InsertHead(7);

    auto t = *sp;
    while(t) {
        auto value = *t;
        std::cout << value << std::endl;
        ++t;
    }

    delete sp;
}