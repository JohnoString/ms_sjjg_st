#if 0
#include <iostream>
using namespace std;

#define __STL_FUNCTION_TMPL_PARTIAL_ORDER

template <class I, class O>
struct testClass
{
	testClass() {cout << "I, O" << endl;}
};

template <class T>
struct testClass<T*, T*>
{
	testClass() {cout << "T*, T*" << endl;}
};

template <class T>
struct testClass<const T*, T*>
{
	testClass() {cout << "cosnt T*, T*" << endl;}
};


class alloc
{

};

template <class T, class Alloc = alloc>
class vector
{
public:
	void swap(vector<T, Alloc>&) {cout << "swap()" << endl;}
};

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
template <class T, class Alloc>
inline void swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
{
	x.swap(y);
}
#endif

int main()
{

	//testClass<int, char> obj1;
	//testClass<int*, int*> obj2;
	//testClass<const int*, int*> obj3;
	
	vector<int> x, y;
	swap(x, y);

	return 0;
}
#endif