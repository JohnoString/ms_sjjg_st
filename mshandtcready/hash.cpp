// ��ϣ
#if 0
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <malloc.h>
using namespace std;

constexpr auto MAXTABLESIZE = 10000; //�����ٵ����ɢ�б���;
constexpr auto KEYLENGTH = 100;      //�ؼ��ֵ���󳤶�;

typedef int ElementType;
struct LNode
{
	ElementType data;
	LNode* next;
	LNode* pri;
};
typedef LNode* PtrToNode;
typedef PtrToNode LinkList;
struct TblNode
{
	int tablesize;  //�����󳤶�
	LinkList heads; //���ɢ�е�Ԫ���ݵ�����
};
typedef struct TblNode* HashTable;

/*���ش���n�Ҳ�����MAXTABLESIZE����С����*/
int NextPrime(int n)
{
	int p = (n % 2) ? n + 2 : n + 1; //�Ӵ���n����һ��������ʼ
	int i;
	while (p <= MAXTABLESIZE)
	{
		for (i = (int)sqrt(p); i > 2; i--)
		{
			if ((p % i) == 0)
				break;
		}
		if (i == 2)
			break; //˵��������������
		else
			p += 2;
	}
	return p;
}

/*�����µĹ�ϣ��*/
HashTable CreateTable(int table_size)
{
	HashTable h = (HashTable)malloc(sizeof(TblNode));
	if (h != nullptr)
	{
		h->tablesize = NextPrime(table_size);
		h->heads = (LinkList)malloc(h->tablesize * sizeof(LNode));
		
		//��ʼ����ͷ���
		for (int i = 0; i < h->tablesize; i++)
		{
			h->heads[i].next = nullptr;
		}
	}
	
	return h;
}

/*�������ݵĳ�ʼλ��*/
int Hash(ElementType key, int n)
{
	//����ֻ��Դ�Сд
	return key % 11;
}

/*����Ԫ��λ��*/
LinkList Find(HashTable h, ElementType key)
{
	int pos;

	pos = Hash(key, h->tablesize); //��ʼɢ��λ��

	LinkList p = h->heads[pos].next; //������ĵ�һ���ڵ㿪ʼ
	while (p && key != p->data)
	{
		p = p->next;
	}

	return p;
}

/*�����µ�Ԫ��*/
bool Insert(HashTable h, ElementType key)
{
	LinkList p = Find(h, key); //�Ȳ���key�Ƿ����
	if (!p)
	{
		//�ؼ���δ�ҵ������Բ���
		LinkList new_cell = (LinkList)malloc(sizeof(LNode));
		if (new_cell != nullptr)
		{
			new_cell->data = key;
			new_cell->next = nullptr;
			new_cell->pri = nullptr;
		}
		
		int pos = Hash(key, h->tablesize);

		LinkList pNode = h->heads[pos].next;
		if (pNode == nullptr)
		{
			h->heads[pos].next = new_cell;
			new_cell->pri = &h->heads[pos];
		}
		else
		{
			while (pNode->next)
			{
				pNode = pNode->next;
			}

			// β��
			pNode->next = new_cell;
			new_cell->pri = pNode;
		}
		
		return true;
	}
	else
	{
		cout << "��ֵ�Ѵ��ڣ�" << endl;
		return false;
	}
}

// ɾ��Ԫ��
void DeleteEle(HashTable h, ElementType key)
{
	LinkList p = Find(h, key); //�Ȳ���key�Ƿ����
	if (!p)
	{
		cout << "��ֵ�����ڣ�" << endl;
	}
	else
	{
		int pos;
		pos = Hash(key, h->tablesize); //��ʼɢ��λ��
		LinkList pNode = h->heads[pos].next;
		while (pNode)
		{
			if (key == pNode->data)
			{
				pNode->pri->next = pNode->next;
				pNode->next->pri = pNode->pri;

				pNode->pri = nullptr;
				pNode->next = nullptr;
				free(pNode);
				pNode = nullptr;
				break;
			}
			else
			{
				pNode = pNode->next;
			}
		}
	}
}

/*��������*/
void DestroyTable(HashTable h)
{
	int i;
	LinkList p, tmp;
	//�ͷ�ÿ���ڵ�
	for (i = 0; i < h->tablesize; i++)
	{
		p = h->heads[i].next;
		while (p)
		{
			tmp = p->next;
			free(p);
			p = tmp;
		}
	}
	free(h->heads);
	free(h);
}

int main(int argc, char const* argv[])
{
	int a[] = { 47, 7, 29, 29, 11, 16, 92, 22, 8, 3, 50, 37, 89, 94, 21 };
	int n = 15;
	HashTable h = CreateTable(n);
	for (int i = 0; i < n; i++)
	{
		Insert(h, a[i]); //����Ԫ��
	}
	for (int i = 0; i < h->tablesize; i++)
	{
		LinkList p = h->heads[i].next;
		while (p)
		{
			cout << p->data << " "; //��ӡ��ϣ��Ԫ��
			p = p->next;
		}
		cout << endl;
	}
	return 0;
}
#endif
