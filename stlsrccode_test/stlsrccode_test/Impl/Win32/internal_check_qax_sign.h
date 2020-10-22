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
	Created:	2020/03/02 16:53:11
	Filename: 	internal_check_qax_sign.h
	File base:	internal_check_qax_sign
	File ext:	h
	Author:		Zhaokai
	
	Purpose:	�ڲ��ӿڣ��ⲿ��Ҫʹ��
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
#pragma message ("ע�⣬����ط�ֻ����ʱ����֤ǩ�����ܹر��ˣ���ʽ������ʱ��Ҫ����֤ǩ����")
#pragma message (__FILE__ "(71)")

		return true;

		QAXASSERT(Base::String::IsEmpty(lpszFilename) == false);

		// ����ļ���Ϊ�գ���������Ҫ��֤
		if (Base::String::IsEmpty(lpszFilename)) return false;

		// �ļ�Ӧ�ô���
		QAXASSERT(::PathFileExists(lpszFilename));

		QAXSIGNSTATE state = InternalGetQAXSignState(lpszFilename);

		// ֻ����һ������»ᱻ��Ϊ��valid��ǩ�������һ����ΪFALSE
		return state == Sign_Publish;
	}
};
