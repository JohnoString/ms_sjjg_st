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
	Created:	2017/02/03 23:32
	Filename: 	StringUtils.inl
	File base:	StringUtils
	File ext:	inl
	Author:		Zhaokai
	
	Purpose:	常用字符串工具类的实现
*********************************************************************/

#pragma once


#include <algorithm>

#include "string_convert.inl"


template < typename T >
__inline bool Base::String::IsEmptyString(const T * str)
{
	return (str == nullptr || * str == 0);
}

template < typename T >
__inline bool Base::String::IsEmpty(const T* str)
{
	return IsEmptyString(str);
}

template < typename T >
__inline bool Base::String::IsNotEmptyString(const T * str)
{
	return !IsEmptyString(str);
}

template <typename stl_string_t >
__inline stl_string_t& Base::String::trim_left(stl_string_t& s)
{
	s.erase(0, s.find_first_not_of(L' '));

	return s;
}

template <typename stl_string_t >
__inline stl_string_t& Base::String::trim_right(stl_string_t& s)
{
	s.erase(s.find_last_not_of(L' ') + 1); 
	
	return s;
}

template <typename stl_string_t >
__inline stl_string_t& Base::String::trim(stl_string_t& s)
{
	return trim_left(trim_right(s));
}

// 比较字符串是否相等
template < typename stl_string_t >
__inline bool Base::String::IsEqual(const stl_string_t& str1, const stl_string_t& str2)
{
    return str1 == str2;
}

__inline bool Base::String::IsEqualEx(const wchar_t* str1, const wchar_t* str2)
{
	QAXASSERT(str1);
	QAXASSERT(str2);

	return wcscmp(str1, str2) == 0;
}

// 比较字符串是否相等(不区分大小写）
template < typename stl_string_t >
__inline bool Base::String::IsEqualNoCase(const stl_string_t& str1, const stl_string_t& str2)
{
    if (str1.size() != str2.size()) return false;

	return std::equal(str1.begin(), str1.end(), str2.begin(), 
        [](auto c1, auto c2) 
        {
		return toupper(c1) == toupper(c2);
		}
    );
}

template <typename T>
T __inline string_utils_min(const T t1, const T t2)
{
	return t1 < t2 ? t1 : t2;
}

// 比较指定长度
template < typename stl_string_t >
__inline bool Base::String::IsEqualN(const stl_string_t& str1, const stl_string_t& str2, size_t n)
{
    n = string_utils_min(n, str1.size());
    n = string_utils_min(n, str2.size());

    auto end = str1.begin() + n;

	return std::equal(str1.begin(), end, str2.begin(),
		[](auto c1, auto c2)
		{
            return c1 == c2;
		}
	);
}

template < typename stl_string_t >
__inline void Base::String::ToUpper(stl_string_t& str)
{
	for (auto& c : str)
	{
		c = std::toupper(c);
	}
}

template < typename stl_string_t >
__inline void Base::String::ToLower(stl_string_t& str)
{
	for (auto& c : str)
	{
		c = std::tolower(c);
	}
}

// 比较指定长度
template < typename stl_string_t >
__inline bool Base::String::IsEqualNoCaseN(const stl_string_t& str1, const stl_string_t& str2, size_t n)
{
	n = string_utils_min(n, str1.size());
	n = string_utils_min(n, str2.size());

	auto end = str1.begin() + n;

	return std::equal(str1.begin(), end, str2.begin(),
		[](auto c1, auto c2)
		{
			return toupper(c1) == toupper(c2);
		}
	);
}

__inline size_t Base::String::GetLength(const char* str)
{
	return str ? strlen(str) : 0;
}

__inline size_t Base::String::GetLength(const wchar_t* str)
{
	return str ? wcslen(str) : 0;
}

__inline size_t Base::String::GetByteLength(const char* str, bool bIncludeLastZero)
{
	if (str == nullptr) return 0;

	auto result = strlen(str);

	if (bIncludeLastZero)
	{
		result++;
	}

	return result;
}

__inline size_t Base::String::GetByteLength(const wchar_t* str, bool bIncludeLastZero)
{
	if (str == nullptr) return 0;

	auto result = wcslen(str);
	
	if (bIncludeLastZero)
	{
		result++;
	}
	
	return result * 2;
}

__inline std::string Base::String::ws2utf8(const wchar_t* str)
{
	return utf16_to_utf8(str);
}

_inline std::wstring Base::String::utf82ws(const char* str)
{
	return utf8_to_utf16(str);
}

__inline std::string Base::String::gbk_to_utf8(const char* str)
{
	auto w = gbk_to_utf16(str);
	return utf16_to_utf8(w.c_str());
}

__inline std::string Base::String::utf8_to_gbk(const char* str)
{
	auto w = utf8_to_utf16(str);
	return utf16_to_gbk(w.c_str());
}

template < typename string_type, typename char_type /*= string_type::value_type */>
__inline void Base::String::assign_std_string(string_type& str , const char_type* p)
{
	if (p)
	{
		str = p;
	}
	else
	{
		str.clear();
	}
}

