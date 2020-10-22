#if 0
#include <vector>
#include <iostream>
#include "2jjalloc.h"
using namespace std;

int main()
{
	int ia[5] = {1, 2, 3, 4, 5};

	vector<int, JJ::allocater<int> > iv(ia, ia + 5);
	for (int i = 0; i < iv.size(); ++i)
	{
		cout << iv[i] << ",";
	}

	cout << endl;
	return 0;
}
#endif

#if 1
#include <iostream>
using namespace std;

int main()
{
	return 0;
}
#endif