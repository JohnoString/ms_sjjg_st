//LRU��ʵ�� LRU��Least Recently Used����д�����������ʹ�ã���һ�ֳ��õ�ҳ���û��㷨��ѡ��������δʹ�õ�ҳ��������̭

// ����˫������ʵ��

// ˫��������һ���ص��������������˫·�ģ����Ƕ����ͷ�ڵ��β�ڵ㣬Ȼ�������Ƚ��ȳ���FIFO�����������������ݻ����类��ȡ��
// ������Ҫ�漰����ӡ����ʡ��޸ġ�ɾ����������������ӣ��������Ԫ�أ�ֱ�ӷ�������ͷ���棬������Ԫ��˳�������ƶ������ʵĻ���
// ��ͷ�ڵ�Ŀ��Բ��ùܣ���������м�λ�û���β�ͣ���Ҫ�������ƶ���ͷ�ڵ㣻�޸Ĳ���Ҳһ�����޸�ԭֵ֮���ٽ������ƶ���ͷ����
// ɾ���Ļ���ֱ��ɾ��������Ԫ��˳���ƶ���


// ��׼��lru�㷨ʵ�ֶ��� hashmap+˫������

// ά�����lru���棬�����ݴ��¾��ȵ�ӳ�䵽��n�� lru�����У���Ҫ��Ϊ�˻��� �����������ݡ�������ݵ�д�����ľ�����
// ά����lru������� = CPU�ĺ�������

// ˫������ʵ��LRU�������ɾ��ƽ��ʱ�临�Ӷ�ΪO(1)
/**
  * Double Linked List
  * ����һ���ر��˫���ListNode������head��tail�������ʹ��ӿ����ٶȡ�
* ��Ҫ�ӿ�ľ����Ǹ���������λ���Ĺ��̣��ҵ�item hashmap O(1), ��������λҲ����O(1)
* Overall O(1)
*##### �����
* 1. head��tail�ر��������ͷ��β���ͼ���ͷ��β���Ͷ��ر�졣
* 2. ��˫���pointer: pre��next, ����Ҫ�����κ�һ��node��ʱ��ֻҪ֪��Ҫ������һ����
* ֱ�Ӱ�node.pre��node.next�����������ͺ��ˣ�node����Ȼ��Ȼ�ĶϿ���Ҫ�ˡ�
* һ��֪����ô����ˣ��Ͳ��Ǻ��ر𣬲�������д���㷨:
* moveToHead()
* insertHead()
* remove()
*/

#if 0
#include <iostream>
using namespace std;

const uint32_t MaxSize = 10000;
const uint32_t MaxListSize = 10;
typedef int DataType;

struct DeListNode
{
    DataType data;
    DeListNode* next;
    DeListNode* pri;
};

typedef DeListNode* DeList;

class HashTable
{
public:
    HashTable(uint32_t datanum) : data_num_(datanum)
    {
        head_ = nullptr;
        size_ = 0;
        list_size_ = 0;
    }

    bool Init();
    bool Insert(DataType data); // �����ݲ��뵽����ͷ��;
    bool Destory();
    bool Print();
private:
    uint32_t GetTableSize();
    bool IsFindEleUpdate(DataType data); // ���»��߷������ݣ����������ƶ�������ͷ��
    uint32_t Hash(DataType data);
    bool DeleFromTail(uint32_t pos);

private:
    DeList head_;   // �洢˫������ͷ�ڵ������
    uint32_t size_;  // ��ϣ���� ��ʱ����������
    uint32_t data_num_;  // ҵ��������
    uint32_t list_size_;  // ������󳤶�
};

uint32_t HashTable::GetTableSize()
{
    // �����ϣ���� ȡ���ڵ���ҵ������size�ĵ�һ������
    uint32_t data_num_tmp = data_num_;
    while (data_num_tmp <= MaxSize)
    {
        bool IsPri = true;
        uint32_t i = 2;
        while (i < data_num_tmp)
        {
            if (data_num_tmp % i == 0)
            {
                IsPri = false;
            }

            i++;
        }

        if (IsPri)
        {
            break;
        }

        data_num_tmp++;
    }

    size_ = data_num_tmp;
    return data_num_tmp;
}

bool HashTable::Destory()
{
    if (head_)
    {
        delete[] head_;
        head_ = nullptr;
    }

    return true;
}

bool HashTable::Print()
{
    if (head_ == nullptr)
    {
        return false;
    }

    DeList pHead = head_;
    for (int i = 0; i < size_; ++i)
    {
        if (pHead[i].next == nullptr)
            continue;

        DeListNode* pNode = pHead[i].next;
        while (pNode)
        {
            cout << pNode->data << endl;
            pNode = pNode->next;
        }
    }
}

uint32_t HashTable::Hash(DataType data)
{
    return data % size_;
}

bool HashTable::DeleFromTail(uint32_t pos)
{
    if (pos < 0 || pos >= size_)
    {
        return false;
    }

    if (head_ == nullptr)
    {
        return false;
    }

    DeListNode* pNode = head_[pos].next;
  
    if (pNode == nullptr)
    {
        return false;
    }

    while (pNode->next)
    {
        pNode = pNode->next;
    }

    pNode->pri->next = pNode->next;
 
    pNode->next = nullptr;
    pNode->pri = nullptr;
    delete pNode;
    pNode = nullptr;
}

bool HashTable::Insert(DataType data) // �����ݲ��뵽����ͷ��; ���»��߷������ݣ����������ƶ�������ͷ��; ��������ʱ��������β�������ݶ���
{
    if (head_ == nullptr)
    {
        return false;
    }

    // ͷ�ڵ�Ĭ�ϲ�������
    DeListNode* pNode = new(std::nothrow) DeListNode;
    if (pNode == nullptr)
    {
        return false;
    }

    pNode->next = pNode->pri = nullptr;
    pNode->data = data;

    uint32_t pos = Hash(data);

    if (!IsFindEleUpdate(data))
    {
        // �����Ƿ����� ����β����̭����
        if (list_size_ >= MaxListSize)
        {
            if (!DeleFromTail(pos))
            {
                return false;
            }

            cout << "list is full" << endl;
            return true;
        }

         // ͷ����
         DeListNode* pTmp = head_[pos].next;
         if (pTmp == nullptr)
         {
             head_[pos].next = pNode;
             pNode->pri = &head_[pos];
         }
         else
         {
             head_[pos].next = pNode;
             pNode->pri = &head_[pos];
             pNode->next = pTmp;
         }

         list_size_++;
    }
}

bool HashTable::IsFindEleUpdate(DataType data)
{
    bool IsFind = false;
    uint32_t pos = Hash(data);
    
    DeListNode* pNode = head_[pos].next;
    if (pNode == nullptr)
    {
        return false;
    }

    while (pNode->next)
    {
        if (pNode->data == data)
        {
            // ����Key-Value��ʽ����ֵ, �˴������Եĸ�ֵ
            pNode->data = data;
            IsFind = true;
            break;
        }
        pNode = pNode->next;
    }

    if (IsFind)
    {
        // �Ƴ���ǰ�ڵ�
        if (pNode->next == nullptr)
        {
            pNode->pri->next = nullptr;
        }
        else
        {
            pNode->pri->next = pNode->next;
            pNode->next->pri = pNode->pri;
        }

        // ͷ����
        DeListNode* pTmp = head_[pos].next;

        pNode->pri = &head_[pos];
        pNode->next = pTmp;
        head_[pos].next = pNode;
    }

    return false;
}

bool HashTable::Init()
{
    uint32_t uTableSize = GetTableSize();
    if (uTableSize <= 0)
    {
        return false;
    }

    DeList pHead = new(std::nothrow) DeListNode[uTableSize];
    if (pHead == nullptr)
    {
        return false;
    }

    // ��ʼ��ͷ�ڵ�
    for (int i = 0; i < size_; ++i)
    {
        pHead[i].next = nullptr;
        pHead[i].pri = nullptr;
    }

    head_ = pHead;
    return true;
}

int main()
{
    uint32_t arr[10] = {11,23,45,67,89,12,34,4,5,78};
    HashTable h(sizeof(arr) / sizeof(uint32_t));
    h.Init();
    for (uint32_t i = 0; i < sizeof(arr) / sizeof(uint32_t); ++i)
    {
        h.Insert(arr[i]);
    }
 
    h.Print();
    h.Destory();
	return 0;
}
#endif