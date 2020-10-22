/********************************************************************
	Created:	2011/04/13
	Created:	13:4:2011   16:44
	Filename: 	AutoLocker.h
	File base:	AutoLocker
	File ext:	h
	Author:		赵凯
	
	Purpose:	自动锁
*********************************************************************/

#pragma once

#include "noncopyable.h"

namespace Base
{
	template < typename locker_t >
	class CAutoLockerT : public Base::noncopyable
	{
	public:
		CAutoLockerT(locker_t& locker);
		~CAutoLockerT();			// 注意，这里的析构函数不是虚函数，总不至于有人乱用吧

	private:
		locker_t& m_locker;
	};
};

