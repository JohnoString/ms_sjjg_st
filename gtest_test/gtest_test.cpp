// gtest_test.cpp: 定义应用程序的入口点。
//

#include "gtest_test.h"
#include <gtest/gtest.h>

using namespace std;

TEST(test, add)
{
	EXPECT_EQ(3, add(1, 2));
}

int _tmain(int argc, _TCHAR *argv[])
{
	cout << "Hello gtest." << endl;
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	Sleep(-1);
	return 0;
}
