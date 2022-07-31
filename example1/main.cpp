#include "expr.h"
int main() {
    auto a = (Expr(10) + Expr(20)) - Expr(3) * Expr(4);
    a.PrintAll();
    auto b = a / -Expr(2);
    b.PrintAll();
}