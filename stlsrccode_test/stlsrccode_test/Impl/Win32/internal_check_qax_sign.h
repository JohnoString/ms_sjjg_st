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
	Created:	2020/03/02 16:53:11
	Filename: 	internal_check_qax_sign.h
	File base:	internal_check_qax_sign
	File ext:	h
	Author:		Zhaokai
	
	Purpose:	内部接口，外部不要使用
*********************************************************************/

#pragma once

#include <Public/Interface/sign/Win32/QAXSignC.h>
#include <Public/Interface/sign/Win32/PEInfo/QHBase.h>
#include <Public/Interface/sign/Win32/QHNewSignC.h>

// Lib
#	ifdef _WIN64

#		pragma comment(lib, "QAXBaseLib_md_64_2019.lib")

#	else

#		pragma comment(lib, "QAXBaseLib_md_32_2019.lib")

#	endif

namespace Base
{
	__inline QAXSIGNSTATE InternalGetQAXSignState(const wchar_t* lpszFilename)
	{
		QAXSIGNSTATE state = Sign_No;

		PQAXPESIGN_INFO pInfo = NULL;
		DWORD dwSize = 0;

		BOOL bResult = QAXCheckCertificate(lpszFilename, &state, &pInfo, &dwSize);
		QAX_UNREFERENCE_PARAMETER(bResult);

		QAXCertificateSignResRelease(pInfo);

		return state;
	}

	__inline bool InternalHasValidQAXSign(const wchar_t* lpszFilename)
	{
#pragma message ("注意，这个地方只是暂时把验证签名功能关闭了，正式发布的时候要把验证签名打开")
#pragma message (__FILE__ "(71)")

		return true;

		QAXASSERT(Base::String::IsEmpty(lpszFilename) == false);

		// 如果文件名为空，根本不需要验证
		if (Base::String::IsEmpty(lpszFilename)) return false;

		// 文件应该存在
		QAXASSERT(::PathFileExists(lpszFilename));

		QAXSIGNSTATE state = InternalGetQAXSignState(lpszFilename);

		// 只有这一种情况下会被人为有valid的签名，别的一律认为FALSE
		return state == Sign_Publish;
	}
};
