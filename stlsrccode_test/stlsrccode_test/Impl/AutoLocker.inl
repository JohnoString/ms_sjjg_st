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
	Created:	2020年2月9日 21:16:58
	Filename: 	AutoLocker.inl
	File base:	AutoLocker
	File ext:	h
	Author:		Zhaokai
	
	Purpose:	AutoLocker相关的内联函数
*********************************************************************/

#pragma once

template <typename locker_t>
CAutoLockerT< locker_t>(locker_t& locker) : m_locker(locker)
{
	m_locker.lock();
}

template < typename locker_t >
CAutoLockerT<locker_t>::~CAutoLockerT()
{
	m_locker.unlock();
}
