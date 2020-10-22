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
	Created:	2020/05/06 23:03:13
	Filename: 	SmartArchive.inl
	File base:	SmartArchive
	File ext:	inl
	Author:		Zhaokai
	
	Purpose:	Archive
*********************************************************************/

#pragma once


__inline Base::CStoreArchive::CStoreArchive(uint32_t size) :m_pos(0)
{
    m_size = size;
    m_buffer = std::make_unique<uint8_t[]>(size);
}

__inline uint32_t Base::CStoreArchive::buffer_size(void) const
{
    return m_size;
}

__inline uint32_t Base::CStoreArchive::pos(void) const
{
    return m_pos;
}

__inline uint32_t Base::CStoreArchive::data_length(void) const
{
	return m_pos;
}

__inline bool Base::CStoreArchive::AddData(const void* data, uint32_t length)
{
    // 缓冲区不够了，返回false
    if (m_pos + length > m_size) return false;

    auto p = m_buffer.get() + m_pos;
    
    *((uint32_t*)p) = length;

    m_pos += sizeof(uint32_t);
    p += sizeof(uint32_t);

    if (length > 0)
    {
        if (data != nullptr)
        {
            memcpy(p, data, length);
        }

        m_pos += length;
    }
    
    return true;
}

__inline bool Base::CStoreArchive::AddString(const wchar_t* str)
{
    if (str == nullptr)
    {
        str = L"";
    }

    uint32_t len = Base::String::GetByteLength(str, true);

    return AddData(str, len);
}

__inline bool Base::CStoreArchive::AddString(const char* str)
{
	if (str == nullptr)
	{
		str = "";
	}

	uint32_t len = Base::String::GetByteLength(str, true);

	return AddData(str, len);
}

__inline const uint8_t* Base::CStoreArchive::data(void) const
{
    return m_buffer.get();
}

