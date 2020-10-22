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
	Created:	2020年2月22日 13:29:40
	Filename: 	SmartBuffer.inl
	File base:	SmartBuffer
	File ext:	h
	Author:		Zhaokai
	
	Purpose:	智能缓冲区
*********************************************************************/

#pragma once

template < typename base_type, typename buffer_allocator /*= default_memory_allocator */>
__inline Base::CSmartBuffer<base_type, buffer_allocator>::CSmartBuffer(size_t nItemCount, bool bInit /*= false*/)
{
    m_nItemCount = nItemCount;
    m_nBufferSize = nItemCount * sizeof(base_type);

    if (UseStackBuffer())
    {
        m_pBuffer = m_stack_buffer;
    }
    else
    {
        const size_t size = sizeof(base_type) * nItemCount;
        m_pBuffer = (base_type *)buffer_allocator::alloc(size);
    }

    if (bInit)
    {
        clear();
    }
}

template < typename base_type, typename buffer_allocator /*= default_memory_allocator */>
__inline Base::CSmartBuffer<base_type, buffer_allocator>::~CSmartBuffer(void)
{
    release();
}

template < typename base_type, typename buffer_allocator /*= default_memory_allocator */>
constexpr size_t Base::CSmartBuffer<base_type, buffer_allocator>::memory_size() const
{
    return m_nBufferSize;
}

template < typename base_type, typename buffer_allocator /*= default_memory_allocator */>
bool Base::CSmartBuffer<base_type, buffer_allocator>::UseStackBuffer(void) const
{
    return m_nItemCount <= MAX_ITEM_COUNT;
}

template < typename base_type, typename buffer_allocator /*= default_memory_allocator */>
__inline void Base::CSmartBuffer<base_type, buffer_allocator>::clear(void)
{
    if (m_pBuffer == nullptr) return;

    memset(m_pBuffer, 0, m_nBufferSize);
}

template < typename base_type, typename buffer_allocator /*= default_memory_allocator */>
void Base::CSmartBuffer<base_type, buffer_allocator>::release()
{
	if (m_pBuffer == nullptr) return;

	// 如果是动态分配的内存，需要释放一下
	if (UseStackBuffer() == false)
	{
		buffer_allocator::free(m_pBuffer);
	}

	m_pBuffer = nullptr;
	m_nItemCount = 0;
	m_nBufferSize = 0;
}

template < typename base_type, typename buffer_allocator /*= default_memory_allocator */>
__inline size_t Base::CSmartBuffer<base_type, buffer_allocator>::size(void) const
{
    return m_nItemCount;
}

template < typename base_type, typename buffer_allocator /*= default_memory_allocator */>
__inline const base_type* Base::CSmartBuffer<base_type, buffer_allocator>::const_buffer(void) const
{
    return m_pBuffer;
}

template < typename base_type, typename buffer_allocator /*= default_memory_allocator */>
__inline base_type* Base::CSmartBuffer<base_type, buffer_allocator>::buffer(void)
{
    return m_pBuffer;
}

template < typename base_type, typename buffer_allocator /*= default_memory_allocator */>
__inline Base::CSmartBuffer<base_type, buffer_allocator>::operator const base_type* (void) const
{
    return m_pBuffer;
}

template < typename base_type, typename buffer_allocator /*= default_memory_allocator */>
__inline Base::CSmartBuffer<base_type, buffer_allocator>::operator base_type* (void)
{
    return m_pBuffer;
}
// 
// template < typename base_type, typename buffer_allocator /*= default_memory_allocator */>
// __inline base_type& Base::CSmartBuffer<base_type, buffer_allocator>::operator[](size_t index)
// {
// 	QAXASSERT(m_pBuffer != nullptr && index >= 0 && index < m_nItemCount);
// 
// 	return m_pBuffer[index];
// }

template < typename base_type, typename buffer_allocator /*= default_memory_allocator */>
__inline base_type& Base::CSmartBuffer<base_type, buffer_allocator>::at(const size_t index)
{
	QAXASSERT(m_pBuffer != nullptr && index >= 0 && index < m_nItemCount);

	return m_pBuffer[index];
}
