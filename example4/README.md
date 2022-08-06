# Seq练习

只实现了书中前半部分，后半部分的merge、split、sort、merge2、flip函数更偏向算法，
书中写的很完善此处就不实现了。

## 几个注意的点

1. 模板函数的实现都放在头文件中。
2. 本例的insert实现与书中不一样:
```
template <class T>
Seq<T> &Seq<T>::InsertHead(const T &t) {
    auto p = new SeqNode<T>(t, data);
    --data->used;
    data = p;
    return *this;
}
```
在newSepNode时会将data的used值+1，所以下方直接--used一定大于0。执行了--used后再将new出来的指针赋值给data。
