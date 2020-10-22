#if 0
#include <iostream>
using namespace std;

class alloc
{
public:
protected:
private:
};

template <class T, class Alloc = alloc>
class vector{
public:
	typedef T vlaue_type;
	typedef vlaue_type* iterator;

	template <class I>
	void insert(iterator position, I first, I last)
	{
		cout << "insert()" << endl;
	}
};

int main()
{
	int ia[5] = {0, 1, 2, 3, 4};
	vector<int> x;
	vector<int>::iterator iter = ia;
	x.insert(iter, ia, ia + 5);
	return 0;
}
#endif

#if 0
#include <iostream>
#include <string>
#include <fstream>
using namespace std;



int main()
{
	//wstring result = L"Hell,World!";
	//wofstream f;
	//f.open(L"E:\\11.txt",wios::app);
	//f << result.c_str() << endl;
	//f.close();

	for (int i = 0; i < 19; i++)
	{
		if (i > 0 && i < 12)
		{
			continue;
		}
		cout << "i=" << i << endl;
	}
	return 0;
}
#endif