#include <unordered_map>
#include "expr.h"

Expr::Expr(double value) {
    p = NumberExpr::Create(value);
}

Expr::Expr(std::string &&op, const Expr &target) {
    p = UnitExpr::Create(std::forward<std::string>(op), target);
}

Expr::Expr(std::string &&op, const Expr &left, const Expr &right) {
    p = BinaryExpr::Create(std::forward<std::string>(op), left, right);
}

Expr &Expr::operator=(const Expr &target) {
    if (this != &target) {
        p = target.p;
    }
    return *this;
}

void Expr::Print(std::ostream &out) const {
    p->Print(out);
}

void Expr::PrintAll(std::ostream &out) const {
    Print(out);
    out << " = " << Eval() << std::endl;
}

double Expr::Eval() const {
    return p->Eval();
}

std::shared_ptr<NumberExpr> NumberExpr::Create(double value) {
    struct MakeNumberExprEnabler : public NumberExpr {
        MakeNumberExprEnabler(double value):
                NumberExpr(value) {};
    };
    return std::make_shared<MakeNumberExprEnabler>(value);
}

void NumberExpr::Print(std::ostream &out) const {
    out << value;
}

double NumberExpr::Eval() const {
    return value;
}


std::shared_ptr<UnitExpr> UnitExpr::Create(std::string op, const Expr &target) {
    struct MakeUnitExprEnabler : public UnitExpr {
        MakeUnitExprEnabler(std::string op, const Expr &target):
                UnitExpr(std::move(op), target) {};
    };
    return std::make_shared<MakeUnitExprEnabler>(std::move(op), target);
}

void UnitExpr::Print(std::ostream &out) const {
    out << op << value.Eval();
}

double UnitExpr::Eval() const {
    if (op == "-") {
        return -value.Eval();
    }
    return value.Eval();
}


std::shared_ptr<BinaryExpr> BinaryExpr::Create(std::string op, const Expr &left, const Expr &right) {
    struct MakeBinaryExprEnabler : public BinaryExpr {
        MakeBinaryExprEnabler(std::string op, const Expr &left, const Expr &right):
                BinaryExpr(std::move(op), left, right) {};
    };
    return std::make_shared<MakeBinaryExprEnabler>(std::move(op), left, right);
}

void BinaryExpr::Print(std::ostream &out) const {
    out << "(";
    left.Print(out);
    out << " " << op << " ";
    right.Print(out);
    out << ")";
}

double BinaryExpr::Eval() const {
    if (op == "+") {
        return left.Eval() + right.Eval();
    } else if (op == "-") {
        return left.Eval() - right.Eval();
    } else if (op == "*") {
        return left.Eval() * right.Eval();
    } else {
        return left.Eval() / right.Eval();
    }
}

Expr operator-(const Expr &target) {
    return Expr{"-", target};
}
Expr operator+(const Expr &left, const Expr &right) {
    return Expr{"+", left, right};
}
Expr operator-(const Expr &left, const Expr &right) {
        return Expr{"-", left, right};
}
Expr operator*(const Expr &left, const Expr &right) {
        return Expr{"*", left, right};
}
Expr operator/(const Expr &left, const Expr &right) {
    return Expr{"/", left, right};
}