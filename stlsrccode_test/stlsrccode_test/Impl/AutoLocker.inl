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
	Created:	2020��2��9�� 21:16:58
	Filename: 	AutoLocker.inl
	File base:	AutoLocker
	File ext:	h
	Author:		Zhaokai
	
	Purpose:	AutoLocker��ص���������
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
