#if 0
#include <iostream>

# include "aa.h"
# include "bb.h"

using namespace std;

template <class T>
struct Plus
{
	T operator ()(const T& x, const T& y)const 
	{
		return x + y;
	}
};


int main()
{
	/*static_test::A::set_value(42);

	static_test::A::print_value();
	static_test::B::print_value();

	static_test::B::set_value(37);

	static_test::A::print_value();
	static_test::B::print_value();*/

	cout << Plus<int>()(3, 4) << endl;

	return 0;
}
#endif