#if 0
#include <iostream>
using namespace std;

// 观察者
// 发布订阅
/*
观察者模式和发布-订阅模式最大的区别： 发布-订阅模式有事件调度中心。
观察者模式由具体目标调度，每个被订阅的目标里面都需要有对观察者的处理，这种处理方式可能会造成代码的冗余。
发布-订阅模式中，统一由调度中进行处理，订阅者和发布者互不干扰，消除了发布者和订阅者之间的依赖。这样一方面实现了解耦，另一方面可以实现更加细粒度的控制。比如发布者发布了很多消息，但不是所有的订阅者都希望接收到，就可以在调度中心做一些处理，类似权限控制之类的。还可以做一些节流操作。

如果以结构来分辨模式，发布-订阅模式比观察者模式多了一个调度中心，所以发布-订阅模式不同于观察者模式。
如果以意图来分辨模式，它们都实现了对象间一对多的依赖关系，当一个对象的状态发生改变时，所有依赖它的对象都将得到通知，并自动更新，那么它们就是同一种模式，发布-订阅模式是在观察者模式的基础上做了优化升级。
不过不管它们是不是同一个设计模式，它们的实现方式的确是有区别，我们在使用时应该根据应用场景来判断选择哪个。
*/

int main()
{
	return 0;
}
#endif

// 单例模式
#if 0
#include <iostream>
#include <mutex>
using namespace std;

class Singleton
{
private:
	Singleton() { cout << "construction" << endl; }
	Singleton(const Singleton& ref) {}
	Singleton& operator=(const Singleton& ref) {}
	static Singleton* m_Instance;
public:
	void Destory()
	{
		cout << "destory" << endl;
		if (m_Instance != NULL)
		{
			delete m_Instance;
		}
		m_Instance = NULL;
	}
	static Singleton* GetInstance();
};

Singleton* Singleton::m_Instance = new Singleton();  // 饿汉模式;

Singleton* Singleton::GetInstance()
{
	if (NULL == m_Instance)
	{
		m_Instance = new Singleton();  // 懒汉模式
	}
	return m_Instance;
}

class singleton
{
private:
	singleton()
	{
	}

	static singleton* p;
	static mutex mutex_;
public:
	static singleton* initance()
	{
		if (p == NULL)   //p != NULL,说明对象已经创建出来了，直接返回对象的指针，没必要在加锁解锁浪费时间。
		{
			mutex_.lock();
			if (p == NULL)
			{
				p = new singleton();
			}
			mutex_.unlock();
		}
		return p;
	}
};

mutex singleton::mutex_;
singleton* singleton::p = NULL;

int main()
{
	Singleton* p = Singleton::GetInstance();
	//delete p; // (若用析构内部delete)引起无休止调析构,死循环
	//p = NULL;
	Singleton* p1 = Singleton::GetInstance();
	if (p == p1)
	{
		cout << p << endl;
		cout << p1 << endl;
	}
	p->Destory();
	return 0;
}
#endif

// 装饰模式
#if 0
#include <iostream>
#include <string>
using namespace std;

class Component { // 接口
public:
	virtual void Operation() = 0;
	virtual ~Component() {}
};

class ConcreteComponent : public Component { // 具体实现对象，需要被装饰的类
public:
	void Operation() { cout << "ConcreteComponent" << endl; }
};

class Decorator : public Component {
private:
	Component* component;
public:
	void SetComponent(Component* c) { component = c; }  // 设置Component
	virtual void Operation() {
		if (component) component->Operation();
	}
};

class ConcreteDecoratorA : public Decorator {
private:
	string addedState;   // 本类独有功能
public:
	void Operation() {
		Decorator::Operation();
		addedState = "New state";
		cout << "ConcreteDecoratorA: " << addedState << endl;
	}
};

class ConcreteDecoratorB : public Decorator {
private:
	void AddedBehavior() { cout << "ConcreteDecoratorB: AddedBehavior" << endl; }   // 本类特有方法
public:
	void Operation() {
		Decorator::Operation();
		AddedBehavior();
	}
};

int main() {
	Component* c = new ConcreteComponent();

	Decorator* d1 = new ConcreteDecoratorA();
	d1->SetComponent(c);
	d1->Operation();  // ConcreteComponent
	// ConcreteDecoratorA: New state
	Decorator* d2 = new ConcreteDecoratorB();
	d2->SetComponent(c);
	d2->Operation();  // ConcreteComponent
	// ConcreteDecoratorB: AddedBehavior
	delete d1;
	delete d2;
	delete c;
	return 0;
}
#endif