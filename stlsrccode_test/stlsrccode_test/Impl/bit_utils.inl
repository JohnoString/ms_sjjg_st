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
	Created:	2020/03/20 13:13:29
	Filename: 	bit_utils.inl
	File base:	bit_utils
	File ext:	inl
	Author:		Zhaokai
	
	Purpose:	比特相关帮助类
*********************************************************************/


#pragma once


template <typename int_type, typename mask_type >
__inline void Base::set_bit_value(int_type& v, const mask_type mask, bool bSet /*= true*/)
{
    if (bSet)
    {
        v |= mask;
    }
    else
    {
        v &= (~mask);
    }
}

template <typename int_type, typename mask_type >
__inline bool Base::test_bit_value(const int_type& v, const mask_type mask)
{
    return (v & mask) != 0;
}

