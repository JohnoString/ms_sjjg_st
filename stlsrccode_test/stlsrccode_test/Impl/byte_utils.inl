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
	Created:	2020��2��22�� 11:14:55
	Filename: 	byte_utils.inl
	File base:	byte_utils
	File ext:	h
	Author:		Zhaokai
	
	Purpose:	�ֽ���ص�һЩ����
*********************************************************************/

#pragma once

template < typename int_type >
__inline constexpr int_type Base::byte_alignment(const int_type v, uint32_t byte_number)
{
    // ֵ̫���׵Ĳ�������
    QAXASSERT(byte_number > 0 &&byte_number <= 1024 *1024);

    // 0�ֽڣ�1�ֽڶ���ģ�ֱ�ӷ���ԭֵ
    // ��0�ֽڶ�����ˣ���Ӧ���ϳ�ȥ��һ��
    if (byte_number <= 1) return v;

    return ((v + byte_number - 1) / byte_number * byte_number);
}

template < typename int_type >
__inline constexpr int_type Base::byte_alignment_with_2_power(const int_type v, uint32_t power)
{
	// ֵ̫���׵Ĳ�������
	QAXASSERT(power > 0 && power <= 10);

    // 2��0�η�������1��ֱ�ӷ��ؾ���
    if (power == 0) return v;
    
    // return ((v + (1 << power) - 1) >> power) << power;

    auto temp_v = 1 << power;

    return ((v + temp_v - 1) >> power) << power;
}

// 2�ֽڶ���
template <typename int_type >
__inline constexpr int_type Base::byte_alignment_2(const int_type v)
{
	return byte_alignment_with_2_power(v, 1);
}

// 4�ֽڶ���
template <typename int_type >
__inline constexpr int_type Base::byte_alignment_4(const int_type v) 
{
    return byte_alignment_with_2_power(v, 2);
}

// 8�ֽڶ���
template <typename int_type >
__inline constexpr int_type Base::byte_alignment_8(const int_type v)
{
	return byte_alignment_with_2_power(v, 3);
}

// 16�ֽڶ���
template <typename int_type >
__inline constexpr int_type Base::byte_alignment_16(const int_type v)
{
	return byte_alignment_with_2_power(v, 4);
}

// 3�ֽڶ���
template <typename int_type >
__inline constexpr int_type Base::byte_alignment_32(const int_type v)
{
	return byte_alignment_with_2_power(v, 5);
}

// 64�ֽڶ���
template <typename int_type >
__inline constexpr int_type Base::byte_alignment_64(const int_type v)
{
	return byte_alignment_with_2_power(v, 6);
}
