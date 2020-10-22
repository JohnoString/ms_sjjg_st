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
	Created:	2019��9��1�� 15:24:22
	Filename: 	ObjectType.inl
	File base:	ObjectType
	File ext:	h
	Author:		Zhaokai
	
	Purpose:	CObjectCreator���һЩ��������
*********************************************************************/

#pragma once

template < typename T >
__inline qax_result CObjectCreator<T>::CheckAndCreate(const GUID& base_id, const GUID& iid, void** ppInterface)
{
	if(is_equal_guid(base_id, iid) == false) return err_code::e_nointerface;

	ISmartUnknownPtr spUnknown;

	qax_result hr = T::CreateInstance(&spUnknown);
	if(qax_failed(hr)) return hr;

    // create��ʱ�����ü����Ѿ��ӹ���
    // *ppInterface = pUnknown;
    spUnknown->query_interface(iid, ppInterface);

	return hr;
}
