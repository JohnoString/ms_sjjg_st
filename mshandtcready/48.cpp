// ��תͼ�� ԭ��
#if 0
#include <iostream>
#include <vector>
using namespace std;

void swap(int& a, int& b)
{
	int t = a;
	a = b;
	b = t;
}

// ˼·����ת�ú�ת  ע��:�����ν���
vector<vector<int> > GetMatrixRotation(vector<vector<int> > v)
{
	if (v.empty())
	{
		return v;
	}

	// ת��
	for (int i = 0; i < v.size(); ++i)
	{
		for (int j = i; j < v[i].size(); ++j)
		{
			if (i != j)
			{
				swap(v[i][j], v[j][i]);
			}
		}
	}

	// ��ת
	for (int i = 0; i < v.size(); ++i)
	{
		for (int j = 0; j < (v[i].size() + 1) / 2; ++j)
		{
			swap(v[i][j], v[i][v[i].size() - 1 - j]);
		}
	}

	return v;
}

int main()
{
	vector<vector<int> > v = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16} };
	vector<vector<int> > vv;
	vv = GetMatrixRotation(v);
	for (vector<int>& vx : vv)
	{
		for (int& a : vx)
		{
			cout << a << ", ";
		}
		cout << endl;
	}
	cout << endl;
	return 0;
	return 0;
}
#endif