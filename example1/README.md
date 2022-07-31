# 表达式

《c++沉思录》在第八章用了"算数表达式数"的程序来作为面向对象的范例，本用例根据书中的思路实现代码，与书中仅有两处差异：
1. 使用c++11标准的智能指针作为Expr类的成员。
2. 使用重载运算符的方式重载了+-*/四个二元操作。

在实现的途中遇到了构造函数被设置为私有，智能指针无法生成对象的问题，经在网上搜索，最终通过[此问答](https://stackoverflow.com/questions/8147027/how-do-i-call-stdmake-shared-on-a-class-with-only-protected-or-private-const)中的答案解决。