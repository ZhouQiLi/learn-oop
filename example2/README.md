

本用例为**字符图像**练习。



## 需求：

需求是通过一个字符串数组来构造一张字符图像，并实现以下接口：

1. **增加相框**

```
图像：
abc 
efgh
ijk  

加相框后：
+----+
|abc |
|efgh|
|ijk |
+----+
```

2. **删除相框**

```
图像：
+----+
|abc |
|efgh|
|ijk |
+----+

删除相框后：
abc 
efgh
ijk  
```

3. **左右拼接**

```
图像1：
abc 
efgh
ijk  

图像2：
+----+
|abc |
|efgh|
|ijk |
+----+


拼接后：
abc +----+
efgh|abc |
ijk |efgh|
    |ijk |
    +----+
```

4. **上下拼接**

```
图像1：
abc +----+
efgh|abc |
ijk |efgh|
    |ijk |
    +----+

图像2：
+----+
|abc |
|efgh|
|ijk |
+----+


拼接后：
abc +----+
efgh|abc |
ijk |efgh|
    |ijk |
    +----+
+----+
|abc |
|efgh|
|ijk |
+----+
```



用例中共有5个源码文件：

1. picture.h & .cpp
   
   给用户使用的handler。

2. picture_node.h & .cpp

       实现字符图片拼接与打印的基类及其继承类。

3. main.cpp
   
   用于测试。



## 一些笔记

### 多个头文件相互引用

存在以下情况：

```
// a.h
#include "b.h"
class A {
    B b;
};



// b.h
class A;
class B {
    A a;
};
```

如以上代码，a.h中include了b.h，加载完b.h后class B已经定义完毕，所以在class A中可以定义一个B成员。反观b.h文件中class B也想定义一个A成员，但因为加载到class B处时类型A还未定义，虽然在文件开头前置声明一个class A，但要创建一个A的实例必须是在A定义之后，所以此处会报错。所以只能将A成员改为指针：

```
class A;
class B {
    A *a;
}
```

因为指针的大小是固定的，所以此处定义class B成功。



### Picture类的拷贝构造函数和赋值操作符

因为Picture只有一个成员且该成员为智能指针，所以并不需要做特殊的资源获取与释放操作，对于拷贝构造函数和赋值操作符使用自动合成的就能满足需求。



### 虚基类的权限控制

```
class PictureNode {
    friend class Picture;
protected:
    virtual ~PictureNode()= default;

private:
    virtual std::size_t GetMaxWidth() const = 0;
    virtual std::size_t GetMaxHeight() const = 0;
    virtual void PrintLine(std::ostream &, std::size_t , std::size_t) const = 0;
    virtual bool HadFrame() {return false;};
};
```

将handler对象Picture设为友元类，对其开放所有权限。

PictureNode为字符图像的基类，作为虚基类不想被创建对象所以将析构函数设为protected。

将基类的虚函数设为private并不会影响类的多态，如果基类中的虚函数若不需要被继承类调用可以将函数设置为private。



### 匿名namespace

```
namespace {
    void PrintSpaces(std::ostream &out, std::size_t count) {
        if (count <= 0) {
            return;
        }
        while (count--) {
            out << ' ';
        }
        out << std::flush;
    }
}
```

如《c++primer》中讲的，在文件中设置匿名namespace可以让该 namespace 中的成员具有全局唯一的名称，避免重名。匿名namespace的作用域被限制在了本文件以内，也就是外部是不可见的且无法通过extern声明来进行链接。



### make_sheard 与 new

因为继承累中的构造函数都是private的，所以make_sheard并不能访问。在example1中我们为了使用std::make_sheard来构造继承类A，需要在每个继承类中添加一个static的Create函数，再通过函数内部添加一个local的类B来public继承A，这样make_sheard才可以构造出B，再因为public继承是has-a的结构，所以在return时可以隐式转换成类A。在本例中我就偷了个懒直接使用了std::shared_ptr< A >(new A())来生成智能指针，通过查阅资料，得知两者有以下区别：

> shared_ptr中共有两部分数据，1为指向原始数据的指针，2为指向计数器的指针。
> 当使用shared_ptr< A >(new A())时候，new A操作先分配了一次内存构造对象A，在shared_ptr中会再次分配内存来构造计数器对象，共执行了两次内存分配，
> 而make_shared只分配一块足够装下两部分数据的内存。我们都知道内存分配是会有异常的，当new A操作完后若在构造计数器对象时出错就很可能导致对象A无法释放。
> 虽然make_shared也有一些小问题，但在能用make_shared时候尽量都用make_shared。