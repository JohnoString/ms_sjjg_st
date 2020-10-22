#include "aa.h"

namespace static_test
{
	namespace A
	{
		void set_value(int val)
		{
			int& value = static_value();
			value = val;
		}

		void print_value()
		{
			std::cout << static_value() << '\n';
		}
	}
}