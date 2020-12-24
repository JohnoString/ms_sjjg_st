#if 0
#include<iostream>
using namespace std;

typedef int DataType;
#define Node ElemType
#define ERROR NULL

class Node
{
public:
	int data;
	Node* next;
};

class LinkList
{
public:
	LinkList();
	~LinkList();
	void TravalLinkList();
	int GetLength();
	bool IsEmpty();
	ElemType* Find(DataType data);
	void InsertElemAtEnd(DataType data);
	void InsertElemAtIndex(DataType data, int n);
	void InsertElemAtHead(DataType data);
	void DeleteElemAtEnd();
	void DeleteAll();
	void DeleteElemAtPoint(DataType data);
	void DeleteElemAtHead();
	void Reverse_Dir();
	ElemType* Reverse_Recursion(ElemType* pNode);
	void Reverse_Recursion_(ElemType* pNode);
	void Print();
	ElemType* GetHead();
private:
	ElemType* head;              //ͷ���
};

ElemType* LinkList::GetHead()
{
	return head;
}

LinkList::LinkList()
{
	head = new ElemType;
	head->data = -1;
	head->next = NULL;
}

LinkList::~LinkList()
{
	if (head)
	{
		delete head;
		head = NULL;
	}
}

void LinkList::InsertElemAtEnd(DataType data)
{
	ElemType* node = new ElemType;
	node->data = data;
	ElemType* pNode = head;
	if (!head)
	{
		head = node;
	}
	else
	{
		while (pNode->next)
		{
			pNode = pNode->next;
		}

		node->next = NULL;
		pNode->next = node;
	}
}

void LinkList::Print()
{
	ElemType* pNode = head;
	while (pNode)
	{
		cout << pNode->data << ", ";
		pNode = pNode->next;
	}
	cout << endl;
}

void LinkList::InsertElemAtHead(DataType data)
{
	ElemType* node = new ElemType;
	node->data = data;

	ElemType* pNode = head;
	if (!head)
	{
		head = node;
	}
	else
	{
		ElemType* pNode_ = head->next;
		pNode->next = node;
		node->next = pNode_;
	}
}

void LinkList::DeleteElemAtEnd()
{
	if (!head)
	{
		return;
	}
	else if (!head->next)
	{
		return;
	}
	ElemType* pNode = new ElemType;
	ElemType* pTmp = NULL;
	pNode = head->next;
	while (pNode->next)
	{
		pTmp = pNode;
		pNode = pNode->next;
	}

	delete pNode;
	pNode = NULL;
	pTmp->next = NULL;
}

void LinkList::DeleteElemAtHead()
{
	if (!head)
	{
		return;
	}
	else if (!head->next) //�����
	{
		return;
	}

	ElemType* pNode = head->next;
	head->next = pNode->next;
	delete pNode;
	pNode = NULL;

}

// �͵�ͷ��
void LinkList::Reverse_Dir()
{
	if (!head || !head->next)
	{
		return;
	}
	else
	{
		ElemType* p = head->next;
		ElemType* q = NULL;
		while (p->next)
		{  
			// ע�Ᵽ֤������ʵĽڵ�ָ�벻ʧЧ
			/*
			����ʾ����:q->next����ָ����q, ���´�ӡ��ѭ��
			q = p->next;
			head->next = q;
			p->next = q->next;
			q->next = head->next;
			����ʾ���ڵ������ڵڶ���ͷ���ʱ��pָ���Ѿ�������һ���ڵ�, ���մ�ӡֻʣͷ����������ڵ�
			q = p->next;
			p->next = q->next;
			q->next = p;
			head->next = q;
			*/
			q = p->next;
			p->next = q->next;
			q->next = head->next;
			head->next = q;
		}
	}
}

// ������ֵ
ElemType* LinkList::Reverse_Recursion(ElemType* pNode)
{
	if (NULL == pNode || NULL == pNode->next)
		return pNode;

	ElemType* newhead = Reverse_Recursion(pNode->next);
	if (pNode != head) {
		pNode->next->next = pNode;
		pNode->next = NULL;
		return newhead;
	}
	else {
		pNode->next = newhead;
		return pNode;
	}
}

// �޷���ֵ ������
//void LinkList::Reverse_Recursion_(ElemType* pNode)
//{
//	if (NULL == pNode || NULL == pNode->next)
//		return;
//
//	Reverse_Recursion_(pNode->next);
//	ElemType* newhead = pNode->next;
//	if (pNode != head) {
//		pNode->next->next = pNode;
//		pNode->next = NULL;
//		return;
//	}
//	else {
//		pNode->next = newhead;
//		return;
//	}
//}


// ��ͷ�ڵ�ݹ�����


int main()
{
	//��ͷ�ڵ�ĵ�����ͷ�ڵ�������Ϊ-1
	LinkList l;
	l.InsertElemAtEnd(1);
	l.InsertElemAtEnd(2);
	l.InsertElemAtHead(0);
	l.InsertElemAtEnd(3);
	l.InsertElemAtEnd(4);
	l.Print();
	//l.DeleteElemAtEnd();
	//l.Print();
	//l.DeleteElemAtHead();
	//l.Print();
	//l.Reverse_Dir();
	//l.Print();
	//l.Reverse_Recursion(l.GetHead());
	//l.Print();
	l.Reverse_Recursion_(l.GetHead());
	l.Print();
	return 0;
}
#endif
// ˫��ѭ������
// ˫������
#if 0
#include <iostream>
using namespace std;

typedef int DataType;

class Node
{
public:
	DataType data;
	Node* next;
	Node* pri;
};

typedef Node* ListHead;

class DoubleList
{
public:
	DoubleList()
	{
		m_pHead = nullptr;
		//m_nLength = 0;
	}

	ListHead GetHead();
	uint32_t GetListLength();
	bool CreateList();
	bool InsertToHead(DataType value);
	bool InsertToTail(DataType value);
	bool InsertToAny(DataType value, uint32_t pos);

	bool DelFromHead();
	bool DelFromTail();
	bool DelFromAny(uint32_t pos);

	bool ReversedList();
	ListHead RecuRevList(Node* pNode);
	void Print();

private:
	//uint32_t m_nLength;
	ListHead m_pHead;
};

ListHead DoubleList::GetHead()
{
	return m_pHead;
}

void DoubleList::Print()
{
	if (m_pHead == nullptr)
	{
		return;
	}

	Node* pHead = m_pHead->next;
	while (pHead)
	{
		cout << pHead->data << ", ";
		pHead = pHead->next;
	}
	cout << endl;
}

bool DoubleList::CreateList()
{
	if (m_pHead == nullptr)  // ����ͷ���
	{
		Node* pNode = new Node;
		if (pNode)
		{
			pNode->data = -1;
			pNode->next = nullptr;
			pNode->pri = nullptr;
			m_pHead = pNode;
			return true;
		}
	}
}

bool DoubleList::InsertToHead(DataType value)
{
	if (m_pHead == nullptr)
	{
		return false;
	}
	else if (m_pHead->next == nullptr)
	{
		Node* pNode = new Node;
		pNode->data = value;
		pNode->next = nullptr;
		pNode->pri = nullptr;

		m_pHead->next = pNode;
		pNode->pri = m_pHead;
	}
	else	
	{
		Node* pNode = new Node;
		pNode->data = value;
		pNode->next = nullptr;
		pNode->pri = nullptr;
		Node* pTmp = m_pHead->next;
		pNode->next = pTmp;
		pTmp->pri = pNode;
		m_pHead->next = pNode;
		pNode->pri = m_pHead;	
	}

	return true;
}

bool DoubleList::InsertToTail(DataType value)
{
	if (m_pHead == nullptr)
	{
		return false;
	}
	else if (m_pHead->next == nullptr)
	{
		Node* pNode = new Node;
		pNode->data = value;
		pNode->next = nullptr;
		pNode->pri = nullptr;

		m_pHead->next = pNode;
		pNode->pri = m_pHead;
	}
	else
	{
		Node* pHead = m_pHead->next;
		while (pHead->next)
		{
			pHead = pHead->next;
		}

		Node* pNode = new Node;
		pNode->data = value;
		pNode->next = nullptr;
		pNode->pri = nullptr;
		pHead->next = pNode;
		pNode->pri = pHead;
	}

	return true;
}

uint32_t DoubleList::GetListLength()
{
	if (m_pHead == nullptr)
	{
		return -1;
	}

	uint32_t uNum = 0;
	Node* pHead = m_pHead->next;
	while (pHead)
	{
		pHead = pHead->next;
		uNum++;
	}
	
	return uNum;
}

bool DoubleList::InsertToAny(DataType value, uint32_t pos) // posָ���ǵڼ����ڵ����, Ĭ�ϴ�1��ʼ
{
	if (m_pHead == nullptr || pos <= 0 || pos > GetListLength())
	{
		return false;
	}
	else if (m_pHead->next == nullptr && pos == 1)
	{
		if (!InsertToHead(value))
		{
			return false;
		}
	}
	else
	{
		if (m_pHead->next != nullptr)
		{
			Node* pHead = m_pHead->next;

			while (pos > 0)
			{
				pos--;
				pHead = pHead->next;
			}

			if (!pHead)
			{
				if (!InsertToTail(value))
				{
					return false;
				}
			}
			else
			{
				Node* pNode = new Node;
				pNode->data = value;
				pNode->next = nullptr;
				pNode->pri = nullptr;

				pNode->pri = pHead->pri;
				pNode->next = pHead;
				pHead->pri->next = pNode;
				pHead->pri = pNode;
			}
		}
	}
	return true;
}

bool DoubleList::DelFromHead()
{
	if (m_pHead == nullptr || m_pHead->next == nullptr)
	{
		return false;
	}
	else
	{
		Node* pHead = m_pHead->next;
		m_pHead->next = pHead->next;
		pHead->next->pri = m_pHead;

		pHead->next = nullptr;
		pHead->pri = nullptr;
		delete pHead;
		pHead = nullptr;
	}

	return true;
}

bool DoubleList::DelFromTail()
{
	if (m_pHead == nullptr || m_pHead->next == nullptr)
	{
		return false;
	}
	else
	{
		Node* pHead = m_pHead->next;
		while (pHead->next)
		{
			pHead = pHead->next;
		}

		pHead->pri->next = nullptr;
		pHead->next = nullptr;
		pHead->pri = nullptr;
		delete pHead;
		pHead = nullptr;
	}

	return true;
}

bool DoubleList::DelFromAny(uint32_t pos)
{
	if (m_pHead == nullptr || m_pHead->next == nullptr || pos <= 0 || pos >= GetListLength())
	{
		return false;
	}
	else if (pos = GetListLength() - 1)
	{
		if (!DelFromTail())
		{
			return false;
		}
	}
	else
	{
		if (m_pHead->next != nullptr)
		{
			Node* pHead = m_pHead->next;

			while (pos > 0)
			{
				pos--;
				pHead = pHead->next;
			}

			pHead->pri->next = pHead->next;
			pHead->next->pri = pHead->pri;

			pHead->next = nullptr;
			pHead->pri = nullptr;
			delete pHead;
			pHead = nullptr;
		}
	}
	return true;
}

bool DoubleList::ReversedList()
{
	if (m_pHead == nullptr)
	{
		return false;
	}
	else if (m_pHead->next == nullptr || m_pHead->next->next == nullptr)
	{
		return true;
	}
	else
	{
		Node* pNode = m_pHead->next;
		Node* p = pNode;
		Node* q = pNode->next;
		while (p->next)
		{
			q = p->next;
			p->next = q->next;
			q->next = m_pHead->next;
			m_pHead->next = q;
		}
	}

	return true;
}

ListHead DoubleList::RecuRevList(Node *pNode)
{
	if (pNode == nullptr || pNode->next == nullptr)
	{
		return m_pHead;
	}

	Node* newhead = RecuRevList(pNode->next);
	if (pNode != m_pHead) {
		pNode->next->next = pNode;
		pNode->next = NULL;
		return newhead;
	}
	else {
		pNode->next = newhead;
		return pNode;
	}
}

int main()
{
	DoubleList d;
	d.CreateList();
	d.InsertToHead(1);
	d.InsertToHead(2);
	d.InsertToHead(3);
	d.InsertToTail(4);
	d.InsertToTail(5);
	d.InsertToAny(6, 4);
	d.Print();
	//d.DelFromHead();
	//d.DelFromTail();
	d.DelFromAny(4);
	d.Print();
	//d.ReversedList();
	d.ReversedList();
	d.Print();
	return 0;
}
#endif