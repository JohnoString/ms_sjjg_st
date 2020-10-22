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
         ���汣��       ����BUG
*/

/********************************************************************
	Created:	2020/04/22 14:54:34
	Filename: 	string_convert.h
	File base:	string_convert
	File ext:	h
	Author:		Zhaokai
	
	Purpose:	�ַ�������ת��
                C++��׼�����ת���ٶ�̫����������C++17���ϲ�֧����
*********************************************************************/

#pragma once

#ifndef  _WIN32
#error  "��ͷ�ļ�ֻ������Widows�ϣ����ƽ̨��Ҫ����"
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

    // utf16ת����utf8���ֽ�����仯�������ᳬ��4��
    Base::CSmartBuffer<char> buffer(len * 4);
    
#ifdef _DEBUG
	memset(buffer, 0xcc, buffer.size());
#endif

	auto spUtils = QAXBase::CUtilsHelper::instance().GetUtils();
	if(spUtils == nullptr) return get_error_string().err;

	// ������֪��ת����������ַ�����󳤶��Ƕ��٣����û�б�Ҫ��ȥ����һ�飬�˷�ʱ��
    auto result = spUtils->WideCharToMultiByte(CP_UTF8, str, len, buffer, buffer.size());

	QAX_UNREFERENCE_PARAMETER(result);

	return buffer.buffer();
}

__inline std::wstring Base::String::utf8_to_utf16(const char* str)
{
	QAXASSERT(str);

	size_t len = Base::String::GetLength(str);

	if (len <= 0) return  get_error_string().werr;

	size_t size = len * 2 + 4;	// �����϶�����С�����������Ū��
	Base::CSmartBuffer<wchar_t> buffer(size);

#ifdef _DEBUG
		memset(buffer, 0xcc, buffer.size());
#endif

	auto spUtils = QAXBase::CUtilsHelper::instance().GetUtils();
	if (spUtils == nullptr) return get_error_string().werr;

	// ������֪��ת����������ַ�����󳤶��Ƕ��٣����û�б�Ҫ��ȥ����һ�飬�˷�ʱ��
	auto result = spUtils->MultiByteToWideChar(CP_UTF8, str, len, buffer, buffer.size());

	QAX_UNREFERENCE_PARAMETER(result);

	return buffer.buffer();
}

__inline std::wstring  Base::String::gbk_to_utf16(const char* str)
{
	QAXASSERT(str);
	
	size_t len = Base::String::GetLength(str);

	if (len <= 0) return  get_error_string().werr;

	size_t size = len * 2 + 4;	// �����϶�����С�����������Ū��
	Base::CSmartBuffer<wchar_t> buffer(size);

#ifdef _DEBUG
		memset(buffer, 0xcc, buffer.size());
#endif

	auto spUtils = QAXBase::CUtilsHelper::instance().GetUtils();
	if (spUtils == nullptr) return get_error_string().werr;

	// ������֪��ת����������ַ�����󳤶��Ƕ��٣����û�б�Ҫ��ȥ����һ�飬�˷�ʱ��
	auto result = spUtils->MultiByteToWideChar(936, str, len, buffer, buffer.size());

	QAX_UNREFERENCE_PARAMETER(result);

	return buffer.buffer();
}

__inline std::string Base::String::utf16_to_gbk(const wchar_t* str)
{
	QAXASSERT(str);

	size_t len = Base::String::GetLength(str);

	if (len <= 0) return  get_error_string().err;

	// utf16ת����utf8���ֽ�����仯�������ᳬ��4��
	Base::CSmartBuffer<char> buffer(len * 4);

#ifdef _DEBUG
		memset(buffer, 0xcc, buffer.size());
#endif

	auto spUtils = QAXBase::CUtilsHelper::instance().GetUtils();
	if (spUtils == nullptr) return get_error_string().err;

	// ������֪��ת����������ַ�����󳤶��Ƕ��٣����û�б�Ҫ��ȥ����һ�飬�˷�ʱ��
	auto result = spUtils->WideCharToMultiByte(936, str, len, buffer, buffer.size());

	QAX_UNREFERENCE_PARAMETER(result);

	return buffer.buffer();
}
