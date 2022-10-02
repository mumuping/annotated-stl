/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef __SGI_STL_INTERNAL_CONSTRUCT_H
#define __SGI_STL_INTERNAL_CONSTRUCT_H

#include <new.h>

__STL_BEGIN_NAMESPACE

// construct and destroy.  These functions are not part of the C++ standard,
// and are provided for backward compatibility with the HP STL.  We also
// provide internal names _Construct and _Destroy that can be used within
// the library, so that standard-conforming pieces don't have to rely on
// non-standard extensions.

// Internal names

template <class _T1, class _T2>
inline void _Construct(_T1* __p, const _T2& __value) {
	// 调用 placement new
  new ((void*) __p) _T1(__value);
}

template <class _T1>
inline void _Construct(_T1* __p) {
  new ((void*) __p) _T1();
}

template <class _Tp>
inline void _Destroy(_Tp* __pointer) {
	// 调用析构函数
  __pointer->~_Tp();
}

// **********************************************************************************
// 这个函数与后一个重载函数 __destroy_aux 均接受两个迭代器，其利用 __type_traits<> 来选择调用那个版本
// 第一个接受的是 __false_type，后一个接受的是 __true_type
// __false_type 代表 non-trivial destructor
// __true_type 代表 trivial destructor，其类型包括 bool, char, signed char, unsigned char,
// wchar_t, short, unsigned short, int, unsigned int, ... , char* 等
// 也就是会根据 type 的不同，选择不同的 destroy 函数，即若 type 是 __true_type（简单的类型），
// 则并不释放内存，而是将其放回 SGI 设计的内存池中；若是 __false_type（复杂的类型），则释放内存
//
template <class _ForwardIterator>
void
__destroy_aux(_ForwardIterator __first, _ForwardIterator __last, __false_type)
{
  for ( ; __first != __last; ++__first)
    destroy(&*__first);
}

template <class _ForwardIterator> 
inline void __destroy_aux(_ForwardIterator, _ForwardIterator, __true_type) {}

// **********************************************************************************
// 根据情况选择不同的 __destroy_aux()
template <class _ForwardIterator, class _Tp>
inline void 
__destroy(_ForwardIterator __first, _ForwardIterator __last, _Tp*)
{
  typedef typename __type_traits<_Tp>::has_trivial_destructor
          _Trivial_destructor;
  __destroy_aux(__first, __last, _Trivial_destructor());
}

// **********************************************************************************
// 不同版本的 _Destroy()
template <class _ForwardIterator>
inline void _Destroy(_ForwardIterator __first, _ForwardIterator __last) {
	// 要判断选用哪种 __destroy_aux，就必须首先通过迭代器来获取到它的值类型，
	// 也就是要通过 __VALUE_TYPE() 来获取，
	// 然后再根据 __type_trait<_Tp> 来判断是否为 trivial 类型
  __destroy(__first, __last, __VALUE_TYPE(__first));
}

// 这个是针对迭代器为 char* 等类型的特化版本
inline void _Destroy(char*, char*) {}
inline void _Destroy(int*, int*) {}
inline void _Destroy(long*, long*) {}
inline void _Destroy(float*, float*) {}
inline void _Destroy(double*, double*) {}
#ifdef __STL_HAS_WCHAR_T
inline void _Destroy(wchar_t*, wchar_t*) {}
#endif /* __STL_HAS_WCHAR_T */

// --------------------------------------------------
// Old names from the HP STL.

template <class _T1, class _T2>
inline void construct(_T1* __p, const _T2& __value) {
  _Construct(__p, __value);
}

template <class _T1>
inline void construct(_T1* __p) {
  _Construct(__p);
}

// destroy 接受两种版本的参数，一个是指针（直接调用析构函数），
// 一个是迭代器（根据情况选择不同的版本，执行不同的操作）
template <class _Tp>
inline void destroy(_Tp* __pointer) {
  _Destroy(__pointer);
}

template <class _ForwardIterator>
inline void destroy(_ForwardIterator __first, _ForwardIterator __last) {
  _Destroy(__first, __last);
}

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_CONSTRUCT_H */

// Local Variables:
// mode:C++
// End:
