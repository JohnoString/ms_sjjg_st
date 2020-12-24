//2. 两数相加
#if 0
#include <iostream>
#include <list>
#include <cmath>
using namespace std;

uint64_t CalculatValue(list<int> res)
{
	if (res.front() == 0)
		return 0;

	uint64_t sum = 0;
	uint64_t i = 0;
	list<int>::iterator iBegin = res.begin();
	for (; iBegin != res.end(); ++iBegin, ++i)
	{
		sum += *iBegin * pow(10, i);
	}

	if (sum > pow(2, 64) - 1)
	{
		cout << "溢出" << endl;
		return -1;
	}

	return sum;
}

uint64_t GetReValue(list<int> ll, list<int> lr)
{
	if (ll.empty() || lr.empty())
	{
		return -1;
	}

	// 任意一条有0的情况
	if (ll.front() == 0)
	{
		return CalculatValue(lr);
	}
	else if (lr.front() == 0)
	{
		return CalculatValue(ll);
	}
	else  // 均不为0
	{
		int diffv = 0;
		if (ll.size() > lr.size())
		{
			diffv = ll.size() - lr.size();
			while (diffv >= 0)  // 多一个节点便于计算
			{
				lr.emplace_back(0);
				diffv--;
			}

			ll.emplace_back(0);
		}
		else if (ll.size() < lr.size())
		{
			diffv = lr.size() - ll.size();
			while (diffv >= 0)  // 多一个节点便于计算
			{
				ll.emplace_back(0);
				diffv--;
			}

			lr.emplace_back(0);
		}

		list<int> lres;
		bool IsAdd = false;
		list<int>::iterator pl = ll.begin();
		list<int>::iterator pr = lr.begin();
		for (; pl != ll.end(); ++pl, ++pr)
		{
			int tmp = *pl + *pr;
			
			if (IsAdd)
			{
				tmp += 1;
			}

			if (tmp <= 9)
			{
				lres.emplace_back(tmp);
				IsAdd = false;
			}
			else
			{
				lres.emplace_back((tmp) % 10);
				IsAdd = true;
			}
		}

		if (lres.back() == 0)
		{
			lres.pop_back();
		}

		return CalculatValue(lres);
	}
}

int main()
{
	list<int> ll = {1,2,3,4};
	list<int> lr = {7,8,9,1,2,3,4,5,6,7,7,8,8,8,8,8};
	uint64_t res = GetReValue(ll, lr);
	cout << res << endl;
	return 0;
}
#endif

// 思路：巧用进位变量 
#if 0
#include <iostream>
#include <list>

using namespace std;

list<int> GetReValue(list<int> ll, list<int> lr)
{
	list<int> lres;
	lres.clear();

	int carry = 0;
	list<int>::iterator iterll = ll.begin();
	list<int>::iterator iterlr = lr.begin();
	while (iterll != ll.end() || iterlr != lr.end())
	{
		// 优化前 时间：O(m > n ? m : n + k) 空间：O((m > n ? m : n + k) 说明：k为size差值
		/*if (iterll == ll.end())
		{
			ll.emplace_back(0);
			iterll--;
			continue;
		}

		if (iterlr == lr.end())
		{
			lr.emplace_back(0);
			iterlr--;
			continue;
		}

		int sum = (*iterll + *iterlr + carry) % 10;
		lres.emplace_back(sum);*/

		// 优化后 时间：O((m > n ? m : n) 空间：O((m > n ? m : n)
		int sum = 0;
		int all = 0;
		if (iterll == ll.end())
		{
			all = (0 + *iterlr + carry);
		}
		else if (iterlr == lr.end())
		{
			all = (*iterll + 0 + carry) % 10;
		}
		else
		{
			all = (*iterll + *iterlr + carry) % 10;
		}

		sum = all % 10;
		lres.emplace_back(sum);
		carry = all / 10;

		if (iterll != ll.end())
		{
			iterll++;
		}
		
		if (iterlr != lr.end())
		{
			iterlr++;
		}	
	}

	if (carry > 0)
	{
		lres.emplace_back(carry);
	}

	return lres;
}

int main()
{
	list<int> ll = { 1,2,3,4,6,7,8,9,0 };
	list<int> lr = { 7,8,9,1,2,3,4,5,6,7,7,8,8,8,8,8 };
	list<int> lres = GetReValue(ll, lr);
	list<int>::iterator iter = lres.begin();
	for (; iter != lres.end(); ++iter)
	{
		cout << *iter << " ";
	}
	
	cout << endl;
	return 0;
}
#endif