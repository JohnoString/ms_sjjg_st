/********************************************************************
	Created:	2019��8��23��
	Filename: 	noncopyable.h
	File base:	noncopyable
	File ext:	h
	Author:		Zhaokai
	
	Purpose:	nonecopyable
*********************************************************************/

#pragma once

namespace Base
{
	class noncopyable
	{
	protected:
		__inline noncopyable() {}
		__inline ~noncopyable() {}

	private:
		__inline noncopyable(const noncopyable& ) {}
		__inline noncopyable& operator = (const noncopyable& ) {}
	};
};
