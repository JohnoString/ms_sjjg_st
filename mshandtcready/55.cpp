// ��Ծ��Ϸ ̰��
#if 0
#include <iostream>
#include <vector>
using namespace std;

// ˼·��ά��һ��ʵʱ���µ����ɵ��ﳤ��
bool IsArrive(vector<int> v)
{
	if (v.empty())
	{
		return false;
	}

	int max = -1;  // ��ǰ��Զ�ɵ���λ��
	for (int i = 0; i < v.size() - 1; ++i)
	{
		if (i + v[i] > max)
		{
			max = i + v[i];
		}
	}

	if (max >= v.size() - 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	vector<int> v = {3,2,1,0,4};
	bool b = IsArrive(v);
	cout << b << endl;
	return 0;
}
#endif