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
	Created:	2020��2��25�� 14:18:49
	Filename: 	qaxallocator.inl
	File base:	qaxallocator
	File ext:	h
	Author:		Zhaokai
	
	Purpose:	������
*********************************************************************/

#pragma once



__inline void * Base::default_memory_allocator::alloc(size_t size)
{
    return ::malloc(size);
}

__inline void Base::default_memory_allocator::free(void * p)
{
    if (p == nullptr) return;

    ::free(p);
}
