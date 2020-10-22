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
	Created:	2020年2月25日 15:41:10
	Filename: 	stackbuffer.inl
	File base:	stackbuffer
	File ext:	h
	Author:		Zhaokai
	
	Purpose:	堆栈中的缓冲区
*********************************************************************/

#pragma once



template < typename base_type, size_t item_count /*= 1024 */>
__inline Base::CStackBuffer<base_type, item_count>::CStackBuffer(bool bInit /*= false*/)
{
	static_assert(BUFFER_SIZE * sizeof(base_type) <= Base::byte_alignment_8(4096 + sizeof(base_type)), "本类中的缓冲区是在堆栈中分配的，不宜太长");

	if (bInit)
	{
		clear();
	}
}

template < typename base_type, size_t item_count /*= 1024 */>
__inline size_t Base::CStackBuffer<base_type, item_count>::size(void) const
{
	return ITEM_COUNT;
}

template < typename base_type, size_t item_count /*= 1024 */>
__inline base_type* Base::CStackBuffer<base_type, item_count>::buffer(void)
{
	return m_buffer;
}

template < typename base_type, size_t item_count >
__inline const base_type* Base::CStackBuffer<base_type, item_count>::const_buffer(void) const
{
	return m_buffer;
}

template < typename base_type, size_t item_count /*= 1024 */>
__inline Base::CStackBuffer<base_type, item_count>::operator base_type* (void)
{
	return buffer();
}

template < typename base_type, size_t item_count /*= 1024 */>
__inline Base::CStackBuffer<base_type, item_count>::operator const base_type* (void) const
{
	return const_buffer();
}

// template < typename base_type, size_t item_count /*= 1024 */>
// __inline base_type& Base::CStackBuffer<base_type, item_count>::operator[](const size_t index)
// {
// 	QAXASSERT(index >= 0 && index < ITEM_COUNT);
// 
// 	return m_buffer[index];
// }

template < typename base_type, size_t item_count >
__inline base_type& Base::CStackBuffer<base_type, item_count>::at(const size_t index)
{
	QAXASSERT(index >= 0 && index < ITEM_COUNT);

	return m_buffer[index];
}

template < typename base_type, size_t item_count /*= 1024 */>
__inline void Base::CStackBuffer<base_type, item_count>::clear(void)
{
	memset(m_buffer, 0, sizeof(m_buffer));
}


template < typename base_type, size_t item_count >
__inline constexpr size_t Base::CStackBuffer<base_type, item_count>::memory_size(void) const
{
	return BUFFER_SIZE * sizeof(base_type);
}

