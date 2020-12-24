// БЅКэПаіэ
#if 0
#include <iostream>
#include <cmath>
using namespace std;

int GetConsult(const int& a, const int& b)
{
	int c, d;
	c = abs(a);
	d = abs(b);

	int count = 0;

	if (c < d)
		return 0;
	else if (c == d)
		return 1;
	else
	{
		int e = c;
		while (e >= d)
		{
			e = c - d;
			c = c - d;
			count++;
		}
	}

	if ((a < 0 && b > 0) || (a > 0 && b < 0))
	{
		count = count - 2 * count;
	}

	if (count > INT_MAX || count < INT_MIN)
		return INT_MAX;

	return count;
}

int main()
{
	cout << GetConsult(-160, -3) << endl;
	return 0;
}
#endif