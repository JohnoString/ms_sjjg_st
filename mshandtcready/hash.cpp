// 哈希
#if 0
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <malloc.h>
using namespace std;

constexpr auto MAXTABLESIZE = 10000; //允许开辟的最大散列表长度;
constexpr auto KEYLENGTH = 100;      //关键字的最大长度;

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
	int tablesize;  //表的最大长度
	LinkList heads; //存放散列单元数据的数组
};
typedef struct TblNode* HashTable;

/*返回大于n且不超过MAXTABLESIZE的最小素数*/
int NextPrime(int n)
{
	int p = (n % 2) ? n + 2 : n + 1; //从大于n的下一个奇数开始
	int i;
	while (p <= MAXTABLESIZE)
	{
		for (i = (int)sqrt(p); i > 2; i--)
		{
			if ((p % i) == 0)
				break;
		}
		if (i == 2)
			break; //说明是素数，结束
		else
			p += 2;
	}
	return p;
}

/*创建新的哈希表*/
HashTable CreateTable(int table_size)
{
	HashTable h = (HashTable)malloc(sizeof(TblNode));
	if (h != nullptr)
	{
		h->tablesize = NextPrime(table_size);
		h->heads = (LinkList)malloc(h->tablesize * sizeof(LNode));
		
		//初始化表头结点
		for (int i = 0; i < h->tablesize; i++)
		{
			h->heads[i].next = nullptr;
		}
	}
	
	return h;
}

/*查找数据的初始位置*/
int Hash(ElementType key, int n)
{
	//这里只针对大小写
	return key % 11;
}

/*查找元素位置*/
LinkList Find(HashTable h, ElementType key)
{
	int pos;

	pos = Hash(key, h->tablesize); //初始散列位置

	LinkList p = h->heads[pos].next; //从链表的第一个节点开始
	while (p && key != p->data)
	{
		p = p->next;
	}

	return p;
}

/*插入新的元素*/
bool Insert(HashTable h, ElementType key)
{
	LinkList p = Find(h, key); //先查找key是否存在
	if (!p)
	{
		//关键词未找到，可以插入
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

			// 尾插
			pNode->next = new_cell;
			new_cell->pri = pNode;
		}
		
		return true;
	}
	else
	{
		cout << "键值已存在！" << endl;
		return false;
	}
}

// 删除元素
void DeleteEle(HashTable h, ElementType key)
{
	LinkList p = Find(h, key); //先查找key是否存在
	if (!p)
	{
		cout << "键值不存在！" << endl;
	}
	else
	{
		int pos;
		pos = Hash(key, h->tablesize); //初始散列位置
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

/*销毁链表*/
void DestroyTable(HashTable h)
{
	int i;
	LinkList p, tmp;
	//释放每个节点
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
		Insert(h, a[i]); //插入元素
	}
	for (int i = 0; i < h->tablesize; i++)
	{
		LinkList p = h->heads[i].next;
		while (p)
		{
			cout << p->data << " "; //打印哈希表元素
			p = p->next;
		}
		cout << endl;
	}
	return 0;
}
#endif
