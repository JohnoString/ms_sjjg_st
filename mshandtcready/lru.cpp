//LRU的实现 LRU是Least Recently Used的缩写，即最近最少使用，是一种常用的页面置换算法，选择最近最久未使用的页面予以淘汰

// 利用双向链表实现

// 双向链表有一个特点就是它的链表是双路的，我们定义好头节点和尾节点，然后利用先进先出（FIFO），最近被放入的数据会最早被获取。
// 其中主要涉及到添加、访问、修改、删除操作。首先是添加，如果是新元素，直接放在链表头上面，其他的元素顺序往下移动；访问的话，
// 在头节点的可以不用管，如果是在中间位置或者尾巴，就要将数据移动到头节点；修改操作也一样，修改原值之后，再将数据移动到头部；
// 删除的话，直接删除，其他元素顺序移动；


// 标准的lru算法实现都是 hashmap+双向链表

// 维护多个lru缓存，将数据大致均匀的映射到这n个 lru缓存中，主要是为了缓解 吊销缓存数据、添加数据等写操作的竞争。
// 维护的lru缓存个数 = CPU的核心数。

// 双向链表实现LRU缓存更新删除平均时间复杂度为O(1)
/**
  * Double Linked List
  * 用了一个特别的双向的ListNode，有了head和tail，这样就大大加快了速度。
* 主要加快的就是那个‘更新排位’的过程，找到item hashmap O(1), 做减法换位也都是O(1)
* Overall O(1)
*##### 巧妙点
* 1. head和tail特别巧妙：除掉头和尾，和加上头和尾，就都特别快。
* 2. 用双向的pointer: pre和next, 当需要除掉任何一个node的时候，只要知道要除掉哪一个，
* 直接把node.pre和node.next耐心连起来就好了，node就自然而然的断开不要了。
* 一旦知道怎么解决了，就不是很特别，并不是难写的算法:
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
    bool Insert(DataType data); // 新数据插入到链表头部;
    bool Destory();
    bool Print();
private:
    uint32_t GetTableSize();
    bool IsFindEleUpdate(DataType data); // 更新或者访问数据，将该数据移动到链表头部
    uint32_t Hash(DataType data);
    bool DeleFromTail(uint32_t pos);

private:
    DeList head_;   // 存储双向链表头节点的数组
    uint32_t size_;  // 哈希表长度 暂时不考虑扩容
    uint32_t data_num_;  // 业务数据量
    uint32_t list_size_;  // 链表最大长度
};

uint32_t HashTable::GetTableSize()
{
    // 计算哈希表长度 取大于等于业务数据size的第一个素数
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

bool HashTable::Insert(DataType data) // 新数据插入到链表头部; 更新或者访问数据，将该数据移动到链表头部; 当链表满时，将链表尾部的数据丢弃
{
    if (head_ == nullptr)
    {
        return false;
    }

    // 头节点默认不存数据
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
        // 链表是否满了 满了尾部淘汰数据
        if (list_size_ >= MaxListSize)
        {
            if (!DeleFromTail(pos))
            {
                return false;
            }

            cout << "list is full" << endl;
            return true;
        }

         // 头插入
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
            // 对于Key-Value形式更新值, 此处象征性的赋值
            pNode->data = data;
            IsFind = true;
            break;
        }
        pNode = pNode->next;
    }

    if (IsFind)
    {
        // 移除当前节点
        if (pNode->next == nullptr)
        {
            pNode->pri->next = nullptr;
        }
        else
        {
            pNode->pri->next = pNode->next;
            pNode->next->pri = pNode->pri;
        }

        // 头插入
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

    // 初始化头节点
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