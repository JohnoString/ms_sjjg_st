#if 0
#include <iostream>
using namespace std;

// �۲���
// ��������
/*
�۲���ģʽ�ͷ���-����ģʽ�������� ����-����ģʽ���¼��������ġ�
�۲���ģʽ�ɾ���Ŀ����ȣ�ÿ�������ĵ�Ŀ�����涼��Ҫ�жԹ۲��ߵĴ������ִ���ʽ���ܻ���ɴ�������ࡣ
����-����ģʽ�У�ͳһ�ɵ����н��д��������ߺͷ����߻������ţ������˷����ߺͶ�����֮�������������һ����ʵ���˽����һ�������ʵ�ָ���ϸ���ȵĿ��ơ����緢���߷����˺ܶ���Ϣ�����������еĶ����߶�ϣ�����յ����Ϳ����ڵ���������һЩ��������Ȩ�޿���֮��ġ���������һЩ����������

����Խṹ���ֱ�ģʽ������-����ģʽ�ȹ۲���ģʽ����һ���������ģ����Է���-����ģʽ��ͬ�ڹ۲���ģʽ��
�������ͼ���ֱ�ģʽ�����Ƕ�ʵ���˶����һ�Զ��������ϵ����һ�������״̬�����ı�ʱ�������������Ķ��󶼽��õ�֪ͨ�����Զ����£���ô���Ǿ���ͬһ��ģʽ������-����ģʽ���ڹ۲���ģʽ�Ļ����������Ż�������
�������������ǲ���ͬһ�����ģʽ�����ǵ�ʵ�ַ�ʽ��ȷ��������������ʹ��ʱӦ�ø���Ӧ�ó������ж�ѡ���ĸ���
*/

int main()
{
	return 0;
}
#endif

// ����ģʽ
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

Singleton* Singleton::m_Instance = new Singleton();  // ����ģʽ;

Singleton* Singleton::GetInstance()
{
	if (NULL == m_Instance)
	{
		m_Instance = new Singleton();  // ����ģʽ
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
		if (p == NULL)   //p != NULL,˵�������Ѿ����������ˣ�ֱ�ӷ��ض����ָ�룬û��Ҫ�ڼ��������˷�ʱ�䡣
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
	//delete p; // (���������ڲ�delete)��������ֹ������,��ѭ��
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

// װ��ģʽ
#if 0
#include <iostream>
#include <string>
using namespace std;

class Component { // �ӿ�
public:
	virtual void Operation() = 0;
	virtual ~Component() {}
};

class ConcreteComponent : public Component { // ����ʵ�ֶ�����Ҫ��װ�ε���
public:
	void Operation() { cout << "ConcreteComponent" << endl; }
};

class Decorator : public Component {
private:
	Component* component;
public:
	void SetComponent(Component* c) { component = c; }  // ����Component
	virtual void Operation() {
		if (component) component->Operation();
	}
};

class ConcreteDecoratorA : public Decorator {
private:
	string addedState;   // ������й���
public:
	void Operation() {
		Decorator::Operation();
		addedState = "New state";
		cout << "ConcreteDecoratorA: " << addedState << endl;
	}
};

class ConcreteDecoratorB : public Decorator {
private:
	void AddedBehavior() { cout << "ConcreteDecoratorB: AddedBehavior" << endl; }   // �������з���
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