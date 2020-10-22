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
	Created:	2020��2��5�� 18:05:27
	Filename: 	qaxobject.inl
	File base:	qaxobject
	File ext:	h
	Author:		Zhaokai
	
	Purpose:	qaxobject����������
*********************************************************************/

#pragma once

#ifdef	_WIN32

#	if defined(_MSC_VER) &&_MSC_VER < 1920

#		error "������ֻ֧��vs2019�����ϰ汾��vs2019���µİ汾���Լ���취ʵ��"

#	endif

#endif


// ʵ�ֲ���

__inline Base::CQAXObjectBase::CQAXObjectBase() : m_ref_count(0)
{

}

__inline uint32_t Base::CQAXObjectBase::internal_addref(void)
{
    uint32_t count = ++m_ref_count;
    return count;
}

__inline void Base::CQAXObjectBase::FinalRelease(void)
{

}

__inline uint32_t Base::CQAXObjectBase::internal_release(void)
{
    uint32_t count = --m_ref_count;

    if (count == 0)
    {
        FinalRelease();
        DestroyInstance();
    }

    return count;
}

__inline qax_result Base::CQAXObjectBase::internal_query_interface(const GUID& guid, void** ppInterface)
{
    QAX_UNREFERENCE_PARAMETER(guid);
    QAX_UNREFERENCE_PARAMETER(ppInterface);

    return err_code::e_notimpl;
}

///////////////////////////// auto_locker_t /////////////////////////////
template < typename locker >
Base::auto_locker_t<locker>::auto_locker_t(locker& l) : m_locker(l)
{
	m_locker.lock();
}

template < typename locker >
Base::auto_locker_t<locker>::auto_locker_t(locker* l) : m_locker(*l)
{
	m_locker.lock();
}

template < typename locker >
Base::auto_locker_t<locker>::~auto_locker_t()
{
	m_locker.unlock();
}


///////////////////////////// CQAXObjectImpl /////////////////////////////


// ������һЩ��


#ifndef is_equal_guid
#define is_equal_guid(rguid1, rguid2) (!memcmp(&rguid1, &rguid2, sizeof(GUID)))
#endif

template <typename T, typename object_creator_t = default_object_creator<T>, typename ... Args >
__inline qax_result internal_qax_create_instance(ISmartUnknown ** ppUnknown, Args ... args)
{
    if (ppUnknown == nullptr) return err_code::e_invalidarg;

    // T* pThis = new T;
    auto pThis = object_creator_t::create(std::forward<Args>(args)...);

    if(pThis == nullptr) return err_code::e_outofmemory;

    ISmartUnknownPtr spUnknown;
	auto hr = pThis->query_interface(__qax_uuidof(ISmartUnknown), (void **)&spUnknown);

    if (qax_failed(hr))
    {
        QAXASSERT(!L"�ӿ��б�����query�� ISmartUnknwon�������ڽӿ�����������\r\n QAX_OBJECT_INTERFACE(ISmartUnknown)����ĳЩ����¿�����Ҫ��QAX_OBJECT_INTERFACE2(ISmartUnknown, xxxxx)������");

        return hr;
    }

    *ppUnknown = spUnknown.Detach();

    // �������ü�����û������
    // * ppUnknown = pThis;
    // (*ppUnknown)->addref();
    
	return err_code::error_success;
}

template <typename T, typename object_creator_t = default_object_creator<T> >
__inline void internal_qax_destroy_instance(T* p)
{
    if (p == nullptr) return;
    object_creator_t::destroy(p);
}

template <typename T, typename ... Args>
__inline qax_result internal_qax_get_instance(ISmartUnknown** ppUnknown, Args ... args)
{
	if (ppUnknown == nullptr) return err_code::e_invalidarg;

	static T __instance(std::forward<Args>(args)...);

	* ppUnknown = &__instance;
	(*ppUnknown)->addref();

	return err_code::error_success;
}

// ������������ִ�ISmartUnknown�̳У���ֻ�������һ�µ���Щ��
#define DECLARE_VIRTUAL_QAX_OBJECT( __class )   \
    virtual uint32_t STDCALLTYPE addref(void) { return 2; } \
    virtual uint32_t STDCALLTYPE release(void) { return 1; } \
    virtual qax_result STDCALLTYPE query_interface(const GUID& guid, void** ppInterface) { return e_notimpl; }


// ʵ��һ�������Ķ���(���������ûɶ���ˣ�������Ҳ�޷���������ܻẦ�ĺö๤���б������
#define IMPLEMENT_QAX_OBJECT( __class ) ;

   
// object map����ͨ����
#define BEGIN_QAX_OBJECT_MAP( __class )	\
	public: \
        virtual uint32_t STDCALLTYPE addref(void) { return Base::CQAXObjectBase::internal_addref(); } \
	    virtual uint32_t STDCALLTYPE release(void) { return Base::CQAXObjectBase::internal_release(); } \
        template < typename ... Args > \
        static qax_result InternalCreateInstance( ISmartUnknown ** ppUnknown, Args ... args) \
        { \
            return internal_qax_create_instance< __class, __class::this_object_creator  >(ppUnknown, std::forward<Args>(args)...); \
        } \
        template < typename ... Args > \
        static qax_result CreateInstance( ISmartUnknown ** ppUnknown, Args ... args) { return InternalCreateInstance(ppUnknown, std::forward<Args>(args)... ); } \
	    virtual void DestroyInstance(void) \
        { \
            __class * pThis = static_cast<__class *>(this); \
            internal_qax_destroy_instance<__class, __class::this_object_creator>(pThis); \
        } \
	    virtual qax_result STDCALLTYPE query_interface(const GUID& guid, void** ppInterface) { 

#define BEGIN_QAX_OBJECT_MAP_EX BEGIN_QAX_OBJECT_MAP

// object map����������
#define BEGIN_QAX_SINGLETON_OBJECT_MAP( __class )	\
	public: \
        static __class & instance() \
        { \
            ISmartUnknownPtr spResult; \
            CreateInstanceEx(spResult); \
            return *smartptr_cast<__class>(spResult); \
        } \
        virtual uint32_t STDCALLTYPE addref(void) { return 2; } \
	    virtual uint32_t STDCALLTYPE release(void) { return 1; } \
        template < typename ... Args > \
        static qax_result InternalCreateInstance( ISmartUnknown ** ppUnknown, Args ... args) \
        { \
            return internal_qax_get_instance< __class >(ppUnknown, args...); \
        } \
        template < typename ... Args > \
        static qax_result CreateInstance( ISmartUnknown ** ppUnknown, Args ... args) { return InternalCreateInstance(ppUnknown, args... ); } \
	    virtual void DestroyInstance(void) \
        { \
            __class * pThis = static_cast<__class *>(this); \
            internal_qax_destroy_instance<__class, __class::this_object_creator>(pThis); \
        } \
	    virtual qax_result STDCALLTYPE query_interface(const GUID& guid, void** ppInterface) { 


#define END_QAX_OBJECT_MAP()	\
		return err_code::e_nointerface; \
	}

#define QAX_OBJECT_INTERFACE_0( __interface, __iid )	\
	if(is_equal_guid(guid, __iid)) \
	{ \
		__interface* p = this; \
			* ppInterface = p; \
			Base::CQAXObjectBase::internal_addref(); \
			return err_code::error_success; \
	}


#define QAX_OBJECT_INTERFACE( __interface )	\
	if(is_equal_guid(guid, IID_ ## __interface)) \
	{ \
		__interface* p = this; \
			* ppInterface = p; \
			Base::CQAXObjectBase::internal_addref(); \
			return err_code::error_success; \
	}

#define QAX_OBJECT_INTERFACE2( __interface, __interface_2 )	\
	if(is_equal_guid(guid, IID_ ## __interface)) \
	{ \
        __interface_2 * p2 = this; \
		__interface* p = p2; \
			* ppInterface = p; \
			Base::CQAXObjectBase::internal_addref(); \
			return err_code::error_success; \
	}

