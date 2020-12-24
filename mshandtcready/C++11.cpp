// C++11.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#if 0
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <initializer_list>

class A
{
public:
    A(const std::initializer_list<int>& items) : m_items(items)
    {
    }

private:
    std::vector<int> m_items;
};

// 常量表达式 constexpr
//const int size() { return 1; }
constexpr int size() { return 1; }

// Lambda函数 注意最后的分号
auto add = [](int a, int b) { return a + b; };

int main()
{
    // 初始化列表
    std::vector<int> v = { 1, 2, 3 };
    std::map<int, std::string> m = { {1, "a"}, {2, "b"} };

    A a1 = { 1, 2, 3 };
    A a2{ 1, 2, 3 };

    // 类型推导 泛型编程方便
    auto i = 0;
    auto d = 1.1;
    auto a = { 1, 2 }; // std::initializer_list<int>

    // 遍历
    for (auto &i : v) // 对象类型&可避免多次拷贝
    {
        ;
    }

    // nullptr
    //void f(int i) {} // chose this one
   // void af(const char* s) { }

    //f(NULL);
   // af(nullptr);

    // 强类型枚举 enum class 以类的形式访问 注：enum 是全局的 
    // 静态断言 static assert
    // 构造函数的相互调用 delegating constructor
    // 禁止重写 final
    // 显式声明重写 override
    // 定义成员初始值
    // 默认构造函数 default
    // 删除构造函数 delete 以往，当我们需要隐藏构造函数时，可以把它声明为private成员
        class A1 {
        private:
            A1();
        };
    // 常量表达式 constexpr
    int arr[size()];

    // 字符串字面量
    // Lambda函数
    add(1, 2);  // 3

    int i1 = 1;
    auto f2 = [=]() { std::cout << i1 << std::endl; };
    i1 = 2;
    f2(); // 输出 1

    std::cout << "Hello World!\n";
}

#endif

#if 0 // 智能指针对比
#include <iostream>
using namespace std; 

class A
{
public:
    A(int a) { m_a = a; }

private:
    int m_a;
};

//二、循环引用

struct Node
{
    shared_ptr<Node> _pre;
    shared_ptr<Node> _next;

    ~Node()
    {
        cout << "~Node():" << this << endl;
    }
    int data;
};

void FunTest()
{
    shared_ptr<Node> Node1(new Node); //1
    shared_ptr<Node> Node2(new Node); //1 
    Node1->_next = Node2; //Node2.use_count()/Node1->_next.use_count()+1
    Node2->_pre = Node1;  //Node1.use_count()/Node2->_pre.use_count()+1

    cout << "Node1.use_count:" << Node1.use_count() << " Node1->_next.use_count:" << Node1->_next.use_count() << endl; //2
    cout << "Node2.use_count:" << Node2.use_count() << " Node2->_pre.use_count:" << Node2->_pre.use_count() << endl; //2
    // shared_ptr智能指针循环引用问题一句话概括就是：要释放的堆对象被该堆对象自己内部的智能指针成员变量增加引用计数阻止了。

    // week_ptr参考链接:https://blog.csdn.net/albertsh/article/details/82286999?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-1.control&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-1.control
    weak_ptr<Node> wk_ptr_a = Node2;
    weak_ptr<Node> wk_ptr_b = wk_ptr_a;
    cout << "wk_ptr_a use count : " << wk_ptr_a.use_count() << endl; // 输出：wk_ptr use count : 2
    cout << "wk_ptr_b use count : " << wk_ptr_b.use_count() << endl; // 输出：wk_ptr1 use count : 2

    if (!wk_ptr_a.expired())
    {
        wk_ptr_a.lock()->show();        // 输出：this is node class
    }

    if (!wk_ptr_b.expired())
    {
        wk_ptr_b.lock()->show();        // 输出：this is node class
    }

    // 编译错误
    // 编译必须作用于相同的指针类型之间
    // wk_ptr_a.swap(wk_ptr_b);         // 调用交换函数

    wk_ptr_b.reset();                   // 将wk_ptr_b的指向清空
    if (wk_ptr_b.expired())
    {
        cout << "wk_ptr_b is invalid" << endl;  // 输出：wk_ptr_b is invalid 说明改指针已经无效
    }

    if (!wk_ptr_b.expired())
    {
        wk_ptr_b.lock()->show();        // 输出：this is node class 调用赋值操作后，wk_ptr_b恢复有效
    }

    // 编译错误
    // 编译必须作用于相同的指针类型之间
    // wk_ptr_b = wk_ptr_a;


    // 最后输出的引用计数还是1，说明之前使用weak_ptr类型赋值，不会影响引用计数
    cout << "Node1 use count : " << Node1.use_count() << endl; // 输出：ptr_a use count : 2
    cout << "Node2 use count : " << Node2.use_count() << endl; // 输出：ptr_b use count : 2
}

int main()
{
    // auto_ptr
    //o 复制和赋值会改变资源的所有权，不符合人的直觉。
    //o 在 STL 容器中无法使用auto_ptr ，因为容器内的元素必需支持可复制（copy constructable）和可赋值（assignable）。
    /*
    1、auto_ptr不能共享所有权。
    2、auto_ptr不能指向数组
    3、auto_ptr不能作为容器的成员。
    4、不能通过赋值操作来初始化auto_ptr
    */
    auto_ptr<int> ap(new int(10));
    auto_ptr<int> one(ap);
    auto_ptr<int> two = one;
    //cout << *ap << endl; 转移所有权之后解引用会有未定义行为比如崩溃
    //cout << *one << endl; 转移所有权之后解引用会有未定义行为比如崩溃
    cout << *two << endl;

    //std::auto_ptr<int> p = new int(42);    //ERROR，本想通过new int(42)来产生临时对象temp（问题出在这里），再由temp拷贝构造产生p. 这是因为auto_ptr 的构造函数被定义为了explicit
    //std::auto_ptr<int> p = auto_ptr<int>(new int(42)); //Success   

    // unique_ptr特性
    //o 拥有它所指向的对象
    //o 无法进行复制构造，也无法进行复制赋值操作
    //o 保存指向某个对象的指针，当它本身离开作用域时会自动释放它指向的对象。
    
    //o 可作为函数返回值
    //实际上上面的的操作有点类似于如下操作
    //unique_ptr<int> up(new int(10);
    //unique_ptr<int> uPtr2 = std:move(up); //这里是显式的所有权转移. 把up所指的内存转给uPtr2了,而up不再拥有该内存
    
    //o 可作为容器元素 move语义实现

    unique_ptr<int> apu(new int(10));
    //unique_ptr<int> oneu(apu); // 会出错不允许操作
    //unique_ptr<int> twou = oneu; //会出错不允许操作

    // shared_ptr——循环引用（内存泄漏）
    
    //一、基础
    //注意，不能用下面的方式使得两个 shared_ptr 对象托管同一个指针：
    A* p = new A(10);
    //shared_ptr <A> sp1(p) , sp2(p);
    //sp1 和 sp2 并不会共享同一个对 p 的托管计数，而是各自将对 p 的托管计数都记为 1（sp2 无法知道 p 已经被 sp1 托管过。这样，当sp1消亡时要析构p，sp2 消亡时要再次析构 p，这会导致程序崩溃。
    
    shared_ptr <A> sp1(p), sp2(sp1), sp3(sp2);  // 没问题
    //每个shared_ptr所指向的对象都有一个引用计数，它记录了有多少个shared_ptr指向自己; 注：sp.use_count()函数返回sp所指对象的引用计数
    // count作为堆内存的原因是为了所有智能指针共享同一个引用计数
    cout << sp1.use_count() << endl; // 3
    cout << sp2.use_count() << endl; // 3
    cout << sp3.use_count() << endl; // 3
    shared_ptr <A> sp4;
    cout << sp4.use_count() << endl; // 0
    sp4 = sp3;
    cout << sp4.use_count() << endl; // 4
    cout << sp1.use_count() << endl; // 4
    cout << sp2.use_count() << endl; // 4
    cout << sp3.use_count() << endl; // 4
    //关注源码实现：只有拷贝构造函数、赋值运算符重载函数被调用时引用计数才会加1, 构造只是开辟引用计数的堆内存，并初始化为1

    //template<class T>
    //class SharpedPtr
    //{
    //public:
    //    SharpedPtr(T* ptr = 0)//构造函数
    //        :_ptr(ptr)
    //        , _pCount(NULL)
    //    {
    //        if (ptr)
    //        {
    //            _pCount = new int(1);
    //        }
    //    }
    //    SharpedPtr(const SharpedPtr<T>& ap)//拷贝构造
    //        :_ptr(ap._ptr)
    //        , _pCount(ap._pCount)
    //    {
    //        if (_ptr)
    //        {
    //            ++UseCount();
    //        }
    //    }
    //    //ap1 = ap2;赋值运算符重载
    //    //①ap1内部封装的指针为空
    //    //②ap1独占一块空间
    //    //③ap1与其他对象共享一块空间
    //    SharpedPtr& operator=(const SharpedPtr<int>& ap)
    //    {
    //        if (this != &ap)
    //        {
    //            if (_ptr)
    //            {
    //                Release();
    //            }
    //            //ap1与其他对象共享一块空间
    //            _ptr = ap._ptr;
    //            _pCount = ap._pCount;
    //            ++UseCount();
    //        }
    //        return *this;
    //    }
    //    //析构函数
    //    ~SharpedPtr()
    //    {
    //        Release();
    //    }
    //    //检查引用计数并释放空间
    //    void Release()
    //    {
    //        if (0 == --UseCount())
    //        {
    //            delete _pCount;
    //            _pCount = NULL;
    //            delete _ptr;
    //            _ptr = NULL;
    //        }
    //    }
    //    //获取引用计数
    //    int& UseCount()
    //    {
    //        return *_pCount;
    //    }
    //    //为了使其更像一个指针，所完成的基本操作
    //    T* operator->()
    //    {
    //        return _ptr;
    //    }

    //    T& operator*()
    //    {
    //        return *_ptr;
    //    }
    //private:
    //    T* _ptr;
    //    int* _pCount;
    //};
    //void TestSharpedPtr()
    //{
    //    SharpedPtr<int> ap1(new int(10));
    //    SharpedPtr<int> ap2(new int(20));
    //    SharpedPtr<int> ap3(ap1);
    //    SharpedPtr<int> ap4;
    //    ap4 = ap1;
    //    *ap1 = 1;
    //    *ap2 = 2;
    //    *ap3 = 3;
    //    *ap4 = 4;
    //}
    //int main()
    //{
    //    TestSharpedPtr();
    //    return 0;
    //}


    //shared_ptr智能指针循环引用问题一句话概括就是：要释放的堆对象被该堆对象自己内部的智能指针成员变量增加引用计数阻止了。
   
    /*总结：
        在以下情况时使用 shared_ptr ：
        当有多个使用者使用同一个对象，而没有一个明显的拥有者时
        当要把指针存入标准库容器时
        当要传送对象到库或从库获取对象，而没有明确的所有权时
        当管理一些需要特殊清除方式的资源时
        通过定制删除器的帮助。
    */

   // int main()
    {
        FunTest();
        system("pause");
        return 0;
    }

    // weak_ptr：weak_ptr是为配合shared_ptr而引入的一种智能指针来协助shared_ptr工作，它可以从一个shared_ptr或另一个weak_ptr对象构造，它的构造和析构不会引起引用记数的增加或减少。没有重载* 和->但可以使用lock获得一个可用的shared_ptr对象。
    return 0;
}

#endif

#if 0
#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <memory>
using namespace std;

struct A
{
    A(int&& n)
    {
        cout << "rvalue overload, n=" << n << endl;
    }
    A(int& n)
    {
        cout << "lvalue overload, n=" << n << endl;
    }
};

class B
{
public:
    template<class T1, class T2, class T3>
    B(T1&& t1, T2&& t2, T3&& t3) :
        a1_(std::forward<T1>(t1)),
        a2_(std::forward<T2>(t2)),
        a3_(std::forward<T3>(t3))
    {

    }
private:
    A a1_, a2_, a3_;
};

template <class T, class U>
std::unique_ptr<T> make_unique1(U&& u)
{
    //return std::unique_ptr<T>(new T(std::forward<U>(u)));
    return std::unique_ptr<T>(new T(std::move(u)));
}

template <class T, class... U>
std::unique_ptr<T> make_unique(U&&... u)
{
    //return std::unique_ptr<T>(new T(std::forward<U>(u)...));
    return std::unique_ptr<T>(new T(std::move(u)...));
}

int main()
{
    auto p1 = make_unique1<A>(2);

    int i = 10;
    auto p2 = make_unique1<A>(i);

    int j = 100;
    //auto p3 = make_unique<B>(i, 2, j);
    return 0;
}
#endif

#if 0
#include <iostream>
#include<string>

template<class T>
void MutiArg(const T& t)
{
    std::cout << "t=" << t << std::endl;
    std::cout << "end" << std::endl;
}

template<class T1, class... Args>
void MutiArg(const T1& t1, Args... args)
{
    std::cout << t1 << std::endl;
   //MutiArg(std::forward<Args>(args)...);
    MutiArg(args...);
}

void main()
{
    MutiArg(1, 1.2, 3, "string", 'c', 1, 3435);

    int a;
    std::weak_ptr<int> a = std::shared_ptr<int>(new int(10));
}
#endif