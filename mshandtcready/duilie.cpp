// 顺序队列存在假溢出情况
// 循环队列
#if 0
#include <iostream>
using namespace std;

typedef uint32_t DataType;

class Queue
{
public:
	Queue(uint32_t size): max_size_(size)
	{
		front_ = rear_ = 0;
		base_ = nullptr;
	}

	bool Init();
	bool IsEmpty();
	bool IsFull();

	bool Put(DataType data);
	bool Pop();
	DataType GetFront();
	uint32_t GetQueueLength();

	void Print();
private:
	uint32_t max_size_;
	uint32_t front_;
	uint32_t rear_;
	DataType* base_;
};

bool Queue::Init()
{
	if (base_ == nullptr)
	{
		base_ = new(std::nothrow) DataType[max_size_ + 1];
		if (base_ == nullptr)
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}

bool Queue::IsEmpty()
{
	return front_ == rear_ ? true : false;
}

bool Queue::IsFull()
{
	return rear_ + 1 % max_size_ == front_ ? true : false;
}

bool Queue::Put(DataType data)
{
	if (IsFull())
	{
		return false;
	}

	base_[rear_] = data;
	rear_ += 1;
}

bool Queue::Pop()
{
	if (IsEmpty())
	{
		return false;
	}

	front_ += 1;
}

DataType Queue::GetFront()
{
	if (IsEmpty())
	{
		return false;
	}

	return base_[front_];
}

void Queue::Print()
{
	if (IsEmpty())
	{
		return;
	}

	uint32_t frontTmp = front_;
	while (frontTmp < rear_)
	{
		cout << base_[frontTmp] << " ,";

		frontTmp++;
	}
	cout << endl;
}

uint32_t Queue::GetQueueLength()
{
	return (max_size_ + rear_ - front_) % max_size_;
}

int main()
{
	Queue q(7);
	q.Init();
	q.Put(1);
	q.Put(2);
	q.Put(3);
	q.Put(4);
	q.Put(5);
	q.Put(6);
	q.Put(7);
	q.Put(8);
	q.Pop();
	q.Print();

	return 0;
}
#endif