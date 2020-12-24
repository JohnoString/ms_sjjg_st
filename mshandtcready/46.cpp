// 全排列 无重复数字
#if 0
#include <iostream>
#include <vector>
using namespace std;

// 回溯思想 需要一个bool数组进行剪枝 时间：O(n*n!)
void GetFullPermutation(vector<vector<int> >& v, const vector<int>& vdata/*, int index*/, vector<int>& out, vector<bool> used)
{
	if (out.size() == vdata.size())
	{
		v.emplace_back(out);
	}
	else
	{
		for (int i = 0; i < vdata.size(); ++ i)
		{
			if (used[i]) continue;
			out.emplace_back(vdata[i]);
			used[i] = true;
			GetFullPermutation(v, vdata/*, index + 1*/, out, used);
			out.pop_back();
			used[i] = false;
		}
	}
}

vector<vector<int> > GetAll(vector<int> v)
{
	vector<vector<int> > vv;
	if (v.empty())
	{
		return vv;
	}

	vector<int> vout;
	vector<bool> used(v.size(), false);
	GetFullPermutation(vv, v, /*0, */vout, used);

	return vv;
}

int main()
{
	vector<vector<int> > v;
	vector<int> vd = { 1, 2, 3 };
	v = GetAll(vd);
	for (vector<int>& vx : v)
	{
		for (int& a : vx)
		{
			cout << a << ", ";
		}
		cout << endl;
	}
	cout << endl;
	return 0;
}
#endif
