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
	Created:	2020年2月17日 22:59:19
	Filename: 	ObjectLoader.inl
	File base:	ObjectLoader
	File ext:	h
	Author:		Zhaokai
	
	Purpose:	对象加载器的实现
*********************************************************************/

#pragma once

#include <Public/safeapi/safeapi.h>

__inline Base::CObjectLoaderBase::CObjectLoaderBase()
{

}

__inline Base::CObjectLoaderBase::~CObjectLoaderBase(void)
{
    QAXASSERT(IsValid());
}

#ifdef __I_KNOW_EXACTLY_WHAT_HAPPENS_WHEN_I_CALL_THIS_FUNCTION__
__inline void Base::CObjectLoaderBase::UnSafeFreeLibrary(void)
{
    if (IsValid() == false) return;

    _sysapi_::dll::FreeModuleByApi(m_handle);
    m_handle = nullptr;
}
#endif

__inline bool Base::CObjectLoaderBase::IsValid() const
{
    return  m_handle != nullptr && m_pfn_create_object != nullptr;
}

__inline Base::CObjectLoaderBase::operator bool(void) const
{
    return IsValid();
}

__inline qax_result Base::CObjectLoaderBase::CreateObject(const GUID& guid, void** ppInterface) const
{
    QAXASSERT(ppInterface);

    if (ppInterface == nullptr) return err_code::e_invalidarg;
    if (IsValid() == false) return err_code::e_nointerface;
    
    return m_pfn_create_object(guid, ppInterface);
}

template < typename _smart_ptr_type >
__inline qax_result Base::CObjectLoaderBase::CreateObject(_smart_ptr_type& ptr) const
{
    return CreateObject(_smart_ptr_type::GetIID(), (void**)&ptr);
}

template < typename _smart_ptr_type >
__inline _smart_ptr_type Base::CObjectLoaderBase::CreateObject(void) const
{
    _smart_ptr_type result;
    CreateObject(result);

    return result;
}

__inline QAX_HANDLE Base::CObjectLoaderBase::GetHandle(void) const
{
    return m_handle;
}

__inline Base::CObjectLoaderBase::operator QAX_HANDLE(void) const
{
    return GetHandle();
}

////////////////////////// CObjectLoader //////////////////////////

Base::CObjectLoader::CObjectLoader(const wchar_t* lpszId)
{
	QAXASSERT(lpszId);
	QAXASSERT(*lpszId);

	InternalLoadModule(lpszId);

#ifdef _DEBUG
    if (IsValid() == false)
    {
        wchar_t szMsg[1000];
        const wchar_t* MSG_FORMAT =
            L"加载模块失败 -- ID = %s\r\n\r\n"
            L"出现此问题的原因一般有以下几种：\r\n"
            L"1. 没有在EXE启动的时候初始化SafeBase，请在WinMain或main函数的的最开头部分加上初始化SafeBase的代码\r\n"
            L"2. 公共库的DLL没有放到正确位置，公共库一共有3个DLL，分别为SafeBase.dll、QAXBase.dll、QAXBase.win32.dll\r\n"
            L"3. 没有把配置文件一起拷贝进去，配置文件包括一个QAXBase.config.xml，和Config目录下的一系列文件\r\n"
            L"4. 没有在配置文件中把这个ID配置好\r\n";

        wsprintf(szMsg, MSG_FORMAT, lpszId);

		qax_internal_assert_w(szMsg, __FUNCTIONW__, __FILEW__, __LINE__);
		__debugbreak(); 
    }
#endif
	// QAXASSERT(IsValid());
}

__inline bool Base::CObjectLoader::InternalLoadModule(const wchar_t* lpszId)
{
	QAXASSERT(IsValid() == false);

	m_handle = safeapi::dll::LoadModuleById(lpszId);
	if (m_handle == nullptr) return false;

	return _sysapi_::dll::GetProcAddress(m_handle, CreateQAXObject_FunctionName, m_pfn_create_object);
}

#ifdef __MY_PROJECT_IS_EXE_AND_I_WANT_TO_INITIALIZE_SAFEBASE_DLL__

/////////////////////////////// CObjectLoaderEx ///////////////////////////////
Base::CObjectLoaderEx::CObjectLoaderEx(const wchar_t* lpszFilePath, bool bStaticCheckSign /*= true*/)
{
	QAXASSERT(lpszFilePath);
	QAXASSERT(*lpszFilePath);

	InternalLoadModule(lpszFilePath, bStaticCheckSign);

	QAXASSERT(IsValid());

}

#ifdef _WIN32
#include "Win32/internal_check_qax_sign.h"
#endif

bool Base::CObjectLoaderEx::InternalLoadModule(const wchar_t* lpszFilePath, bool bStaticCheckSign /*= true*/)
{
    QAX_UNREFERENCE_PARAMETER(bStaticCheckSign);

#ifdef _DEBUG
	// if (InternalHasValidQAXSign(lpszFilePath) == false) return false;
#else
	// 验证签名（如果是debug版本直接放过）
	if (InternalHasValidQAXSign(lpszFilePath) == false) return false;
#endif

	m_handle = _sysapi_::dll::LoadModuleByApi(lpszFilePath);
	if (m_handle == nullptr) return false;

	return _sysapi_::dll::GetProcAddress(m_handle, CreateQAXObject_FunctionName, m_pfn_create_object);
}

#endif  // #ifdef __MY_PROJECT_IS_EXE_AND_I_WANT_TO_INITIALIZE_SAFEBASE_DLL__
