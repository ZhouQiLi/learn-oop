#pragma once
#include <iostream>
#include <memory>

class ExprNode {
public:
    virtual double Eval() const = 0;
    virtual void Print(std::ostream &) const = 0;
protected:
    virtual ~ExprNode() = default;;
};

class Expr {
public:
    // 只有数值的构造函数
    Expr(double value);
    // 一元 -
    Expr(std::string &&, const Expr &);
    // 二元：+-*/
    Expr(std::string &&, const Expr &, const Expr &);

    Expr(const Expr &) = default;
    Expr &operator=(const Expr &);

    void Print(std::ostream &out = std::cout) const;
    void PrintAll(std::ostream &out = std::cout) const;
    double Eval() const;
private:
    std::shared_ptr<ExprNode> p;
};

class NumberExpr: public ExprNode {
    friend class Expr;
private:
    NumberExpr(double target):
            value(target) {}
    ~NumberExpr() override = default;
    static std::shared_ptr<NumberExpr> Create(double);
    void Print(std::ostream &) const override;
    double Eval() const override;
private:
    double value;
};


class UnitExpr: public ExprNode {
    friend class Expr;
private:
    static std::shared_ptr<UnitExpr> Create(std::string, const Expr &);
    UnitExpr(std::string op, const Expr &v):
            op(std::move(op)), value(v) {}
    ~UnitExpr() override = default;

    void Print(std::ostream &) const override;
    double Eval() const override;
private:
    std::string op;
    Expr value;
};

class BinaryExpr: public ExprNode {
    friend class Expr;
private:
    static std::shared_ptr<BinaryExpr> Create(std::string, const Expr &, const Expr &);
    BinaryExpr(std::string o, const Expr &l, const Expr &r):
            op(std::move(o)), left(l), right(r) {}
    ~BinaryExpr() override = default;

    void Print(std::ostream &) const override;
    double Eval() const override;
private:
    std::string op;
    Expr left;
    Expr right;
};

Expr operator-(const Expr &);
Expr operator+(const Expr &, const Expr &);
Expr operator-(const Expr &, const Expr &);
Expr operator*(const Expr &, const Expr &);
Expr operator/(const Expr &, const Expr &);