// ɾ������ĵ�����N���ڵ�
// ˼·��˫ָ�뷨 ʱ��O(n) �ռ䣺O(1)
#if 0
#include <iostream>
#include <list>
using namespace std;

list<int> DelAnyNode(list<int> lst, int pos)
{
	if (pos <= 0)
		return lst;

	list<int>::iterator iterf = lst.begin();
	list<int>::iterator iterb = lst.begin();
	while (pos > 0)
	{
		if (iterb != lst.end())
		{
			iterb++;
			pos--;
		}
		else
		{
			return lst;
		}
	}

	while (iterb != lst.end())
	{
		iterf++;
		iterb++;
	}

	lst.erase(iterf);

	return lst;
}

int main()
{
	list<int> l = { 1,2,3,4,5,6,7 };
	list<int> lst = DelAnyNode(l, 3);
	for (int& a : lst)
	{
		cout << a << " ";
	}

	cout << endl;
	return 0;
}
#endif