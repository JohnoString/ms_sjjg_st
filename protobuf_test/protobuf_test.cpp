// protobuf_test.cpp: 定义应用程序的入口点。
//
#include "protobuf_test.h"
#include <stdio.h>
#include <string.h>
#include "hello.pb.h"

using namespace std;
using namespace hello;

int main()
{
	Hello a;
	a.set_id(101);
	a.set_name("xg");
	a.set_email("893277858");
	
	string tmp;

	bool ret = a.SerializeToString(&tmp);
	if (ret)
	{
		printf("encode success!\n");
	}
	else
	{
		printf("encode faild!\n");
	}

	Hello b;
	ret = b.ParseFromString(tmp);
	if (ret)
	{
		printf("decode success!\n id=%d\n name=%s\n email=%s\n", b.id(), b.name().c_str(), b.email().c_str());
	}
	else
	{
		printf("decode faild!\n");
	}

	return 0;
}