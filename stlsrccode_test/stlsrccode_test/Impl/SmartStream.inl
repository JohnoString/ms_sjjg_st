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
	Created:	2020年2月20日 14:43:51
	Filename: 	SmartStream.inl
	File base:	SmartStream
	File ext:	h
	Author:		Zhaokai
	
	Purpose:	智能流
*********************************************************************/

#pragma once


__inline Base::CSmartStream::CSmartStream() : std::wostream(&m_buffer)
{

}

__inline const std::wstring & Base::CSmartStream::CSmartStream::str(void)
{
	m_string = m_buffer.str().c_str();

    return m_string;
}

__inline const wchar_t* Base::CSmartStream::c_str(void)
{
    return str().c_str();
}

__inline Base::CSmartStream::operator const wchar_t* (void)
{
    return c_str();
}

__inline void Base::CSmartStream::clear()
{
    m_buffer.str(L"");
    m_string.clear();
    std::wostream::clear();
}

__inline bool Base::CSmartStream::empty(void) const
{
    return m_buffer.str().empty();
}

