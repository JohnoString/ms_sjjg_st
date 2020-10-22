/********************************************************************
	Created:	2011/04/13
	Created:	13:4:2011   16:44
	Filename: 	AutoLocker.h
	File base:	AutoLocker
	File ext:	h
	Author:		�Կ�
	
	Purpose:	�Զ���
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
		~CAutoLockerT();			// ע�⣬������������������麯�����ܲ������������ð�

	private:
		locker_t& m_locker;
	};
};

