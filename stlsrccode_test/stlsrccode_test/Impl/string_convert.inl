/*
                   _ooOoo_
                  o8888888o
                  88" . "88
                  (| -_- |)
                  O\  =  /O
               ____/`---'\____
             .'  \\|     |//  `.
            /  \\|||  :  |||//  \
           /  _||||| -:- |||||-  \
           |   | \\\  -  /// |   |
           | \_|  ''\---/''  |   |
           \  .-\__  `-`  ___/-. /
         ___`. .'  /--.--\  `. . __
      ."" '<  `.___\_<|>_/___.'  >'"".
     | | :  `- \`.;`\ _ /`;.`/ - ` : | |
     \  \ `-.   \_ __\ /__ _/   .-` /  /
======`-.____`-.___\_____/___.-`____.-'======
                   `=---='
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
         佛祖保佑       永无BUG
*/

/********************************************************************
	Created:	2020/04/22 14:54:34
	Filename: 	string_convert.h
	File base:	string_convert
	File ext:	h
	Author:		Zhaokai
	
	Purpose:	字符串编码转换
                C++标准库里的转换速度太慢，而且在C++17以上不支持了
*********************************************************************/

#pragma once

#ifndef  _WIN32
#error  "本头文件只能用在Widows上，别的平台不要包含"
#endif

#include <Public/Helper/SmartBuffer.h>
#include <QAXBase/Helper/UtilsHelper.h>

typedef struct _ConvertErrorString
{
	std::string err;
	std::wstring werr;
}CONVERT_ERROR_STRING;

static const CONVERT_ERROR_STRING& get_error_string(void)
{
	static CONVERT_ERROR_STRING err;
	return err;
}

__inline std::string Base::String::utf16_to_utf8(const wchar_t* str)
{
	QAXASSERT(str);

    size_t len = Base::String::GetLength(str);

    if (len <= 0) return get_error_string().err;

    // utf16转换成utf8后，字节数会变化，但不会超过4倍
    Base::CSmartBuffer<char> buffer(len * 4);
    
#ifdef _DEBUG
	memset(buffer, 0xcc, buffer.size());
#endif

	auto spUtils = QAXBase::CUtilsHelper::instance().GetUtils();
	if(spUtils == nullptr) return get_error_string().err;

	// 大致能知道转换出来后的字符串最大长度是多少，因此没有必要再去测试一遍，浪费时间
    auto result = spUtils->WideCharToMultiByte(CP_UTF8, str, len, buffer, buffer.size());

	QAX_UNREFERENCE_PARAMETER(result);

	return buffer.buffer();
}

__inline std::wstring Base::String::utf8_to_utf16(const char* str)
{
	QAXASSERT(str);

	size_t len = Base::String::GetLength(str);

	if (len <= 0) return  get_error_string().werr;

	size_t size = len * 2 + 4;	// 正常肯定比这小，保险起见多弄点
	Base::CSmartBuffer<wchar_t> buffer(size);

#ifdef _DEBUG
		memset(buffer, 0xcc, buffer.size());
#endif

	auto spUtils = QAXBase::CUtilsHelper::instance().GetUtils();
	if (spUtils == nullptr) return get_error_string().werr;

	// 大致能知道转换出来后的字符串最大长度是多少，因此没有必要再去测试一遍，浪费时间
	auto result = spUtils->MultiByteToWideChar(CP_UTF8, str, len, buffer, buffer.size());

	QAX_UNREFERENCE_PARAMETER(result);

	return buffer.buffer();
}

__inline std::wstring  Base::String::gbk_to_utf16(const char* str)
{
	QAXASSERT(str);
	
	size_t len = Base::String::GetLength(str);

	if (len <= 0) return  get_error_string().werr;

	size_t size = len * 2 + 4;	// 正常肯定比这小，保险起见多弄点
	Base::CSmartBuffer<wchar_t> buffer(size);

#ifdef _DEBUG
		memset(buffer, 0xcc, buffer.size());
#endif

	auto spUtils = QAXBase::CUtilsHelper::instance().GetUtils();
	if (spUtils == nullptr) return get_error_string().werr;

	// 大致能知道转换出来后的字符串最大长度是多少，因此没有必要再去测试一遍，浪费时间
	auto result = spUtils->MultiByteToWideChar(936, str, len, buffer, buffer.size());

	QAX_UNREFERENCE_PARAMETER(result);

	return buffer.buffer();
}

__inline std::string Base::String::utf16_to_gbk(const wchar_t* str)
{
	QAXASSERT(str);

	size_t len = Base::String::GetLength(str);

	if (len <= 0) return  get_error_string().err;

	// utf16转换成utf8后，字节数会变化，但不会超过4倍
	Base::CSmartBuffer<char> buffer(len * 4);

#ifdef _DEBUG
		memset(buffer, 0xcc, buffer.size());
#endif

	auto spUtils = QAXBase::CUtilsHelper::instance().GetUtils();
	if (spUtils == nullptr) return get_error_string().err;

	// 大致能知道转换出来后的字符串最大长度是多少，因此没有必要再去测试一遍，浪费时间
	auto result = spUtils->WideCharToMultiByte(936, str, len, buffer, buffer.size());

	QAX_UNREFERENCE_PARAMETER(result);

	return buffer.buffer();
}
