#include "picture.h"

int main() {
    auto p = Picture({"abc", "efgh", "ijk"});
    auto p2 = p;
    p.FrameSplicing().Print();

    p2.HorizontalSplicing(p).Print();

    auto p3 = p2;
    p3.VerticalSplicing(p).Print();

    auto p4 = p3;
    p4.HorizontalSplicing(p3).Print();

    p4.FrameSplicing().Print();
    p4.RemoveFrame().Print();

    return 0;
}