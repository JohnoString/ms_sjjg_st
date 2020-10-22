#include "aa.h"
#include "bb.h"

namespace static_test
{
	namespace B
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