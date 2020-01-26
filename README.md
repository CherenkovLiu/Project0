# Project0

# 给睡觉的人看的

实现了一个bug满天飞的小栈虚拟机，可以基本的模拟一些东西了，接下来需要讨论一下指令集的事情，然后考虑要不要切换到c++的模式，毕竟没有OOP的生活真的是非常的难过，然后如果继续用C的话很多的东西都得自己弄，比如exception handling，然后我根本就没有想好怎么catch，以及stack的内存上的分配问题，肯定不能固定一个大小的stack，而是可以进行分配的，然后把API整的好看一点，以及stack里面的东西还有待商榷，比如其中PObject的实现应该怎么做这一类的

# PVar

这是Project0里面的基本数据类型，在pvm中是同样实现的，通过C/CPP中的Union来实现，包括了gc标签（bool），bool类型，int64_t类型和number类型，以及一个引用指针，可以引用到一个PObject，而PObject是Project0中的基类

# Keywords

```
# This is comment #

load {Package_name};

def foo() : nil {

}

class object {
    public def foo()
    private def foo()
    int a; # private for default #
    public int a;

}

def main(variable : type) : return_type {
    int a;
    double b;
    string c;
    if(a > b) {

    } else if() {

    } else {

    }

    {} == one sentence
    return;
}
```