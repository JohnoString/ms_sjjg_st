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
	Created:	2020年2月22日 11:14:55
	Filename: 	byte_utils.inl
	File base:	byte_utils
	File ext:	h
	Author:		Zhaokai
	
	Purpose:	字节相关的一些工具
*********************************************************************/

#pragma once

template < typename int_type >
__inline constexpr int_type Base::byte_alignment(const int_type v, uint32_t byte_number)
{
    // 值太离谱的不做处理
    QAXASSERT(byte_number > 0 &&byte_number <= 1024 *1024);

    // 0字节，1字节对齐的，直接返回原值
    // 传0字节对齐的人，就应该拖出去打一顿
    if (byte_number <= 1) return v;

    return ((v + byte_number - 1) / byte_number * byte_number);
}

template < typename int_type >
__inline constexpr int_type Base::byte_alignment_with_2_power(const int_type v, uint32_t power)
{
	// 值太离谱的不做处理
	QAXASSERT(power > 0 && power <= 10);

    // 2的0次方，就是1，直接返回就行
    if (power == 0) return v;
    
    // return ((v + (1 << power) - 1) >> power) << power;

    auto temp_v = 1 << power;

    return ((v + temp_v - 1) >> power) << power;
}

// 2字节对齐
template <typename int_type >
__inline constexpr int_type Base::byte_alignment_2(const int_type v)
{
	return byte_alignment_with_2_power(v, 1);
}

// 4字节对齐
template <typename int_type >
__inline constexpr int_type Base::byte_alignment_4(const int_type v) 
{
    return byte_alignment_with_2_power(v, 2);
}

// 8字节对齐
template <typename int_type >
__inline constexpr int_type Base::byte_alignment_8(const int_type v)
{
	return byte_alignment_with_2_power(v, 3);
}

// 16字节对齐
template <typename int_type >
__inline constexpr int_type Base::byte_alignment_16(const int_type v)
{
	return byte_alignment_with_2_power(v, 4);
}

// 3字节对齐
template <typename int_type >
__inline constexpr int_type Base::byte_alignment_32(const int_type v)
{
	return byte_alignment_with_2_power(v, 5);
}

// 64字节对齐
template <typename int_type >
__inline constexpr int_type Base::byte_alignment_64(const int_type v)
{
	return byte_alignment_with_2_power(v, 6);
}
