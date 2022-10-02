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
 * Copyright (c) 1996
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

#ifndef __SGI_STL_INTERNAL_VECTOR_H
#define __SGI_STL_INTERNAL_VECTOR_H

#include <concept_checks.h>

__STL_BEGIN_NAMESPACE

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM!=_MIPS_SIM_ABI32)
#pragma set woff 1174
#pragma set woff 1375
#endif

// The vector base class serves two purposes.  First, its constructor
// and destructor allocate (but don't initialize) storage.  This makes
// exception safety easier.  Second, the base class encapsulates all of
// the differences between SGI-style allocators and standard-conforming
// allocators.

#ifdef __STL_USE_STD_ALLOCATORS

// Base class for ordinary allocators.
/* 普通分配器的基类 */
template <class _Tp, class _Allocator, bool _IsStatic>
class _Vector_alloc_base {
public:
  /* 通过 _Alloc_traits 获取 allocator 的类型 */
  typedef typename _Alloc_traits<_Tp, _Allocator>::allocator_type
		  allocator_type;
  allocator_type get_allocator() const { return _M_data_allocator; }

  _Vector_alloc_base(const allocator_type& __a)
	: _M_data_allocator(__a), _M_start(0), _M_finish(0), _M_end_of_storage(0)
  {}

protected:
  /* allocator 类型 */
  allocator_type _M_data_allocator;
  /* 目前使用空间的头 */
  _Tp* _M_start;
  /* 目前使用空间的尾 */
  _Tp* _M_finish;
  /* 目前可用空间的尾 */
  _Tp* _M_end_of_storage;

  _Tp* _M_allocate(size_t __n)
	{ return _M_data_allocator.allocate(__n); }
  void _M_deallocate(_Tp* __p, size_t __n)
	{ if (__p) _M_data_allocator.deallocate(__p, __n); }
};

// Specialization for allocators that have the property that we don't
// actually have to store an allocator object.
/* 偏特化，不用存储 allocator 对象 */
template <class _Tp, class _Allocator>
class _Vector_alloc_base<_Tp, _Allocator, true> {
public:
  typedef typename _Alloc_traits<_Tp, _Allocator>::allocator_type
		  allocator_type;
  allocator_type get_allocator() const { return allocator_type(); }

  _Vector_alloc_base(const allocator_type&)
	: _M_start(0), _M_finish(0), _M_end_of_storage(0)
  {}

protected:
  _Tp* _M_start;
  _Tp* _M_finish;
  _Tp* _M_end_of_storage;

  typedef typename _Alloc_traits<_Tp, _Allocator>::_Alloc_type _Alloc_type;
  _Tp* _M_allocate(size_t __n)
	{ return _Alloc_type::allocate(__n); }
  void _M_deallocate(_Tp* __p, size_t __n)
	{ _Alloc_type::deallocate(__p, __n);}
};

/* vector base 类，初始化参数 _M_start 等 */
template <class _Tp, class _Alloc>
struct _Vector_base
  : public _Vector_alloc_base<_Tp, _Alloc,
							  _Alloc_traits<_Tp, _Alloc>::_S_instanceless>
{
  typedef _Vector_alloc_base<_Tp, _Alloc,
							 _Alloc_traits<_Tp, _Alloc>::_S_instanceless>
		  _Base;
  typedef typename _Base::allocator_type allocator_type;

  _Vector_base(const allocator_type& __a) : _Base(__a) {}
  _Vector_base(size_t __n, const allocator_type& __a) : _Base(__a) {
	_M_start = _M_allocate(__n);
	_M_finish = _M_start;
	_M_end_of_storage = _M_start + __n;
  }

  ~_Vector_base() { _M_deallocate(_M_start, _M_end_of_storage - _M_start); }
};

#else /* __STL_USE_STD_ALLOCATORS */

/* 不存储 allocator 对象 */
template<class _Tp, class _Alloc>
class _Vector_base {
 public:
  typedef _Alloc allocator_type;
  allocator_type get_allocator() const { return allocator_type(); }

  _Vector_base(const _Alloc &)
	  : _M_start(0), _M_finish(0), _M_end_of_storage(0) {}
  _Vector_base(size_t __n, const _Alloc &)
	  : _M_start(0), _M_finish(0), _M_end_of_storage(0) {
	_M_start = _M_allocate(__n);
	_M_finish = _M_start;
	_M_end_of_storage = _M_start + __n;
  }

  ~_Vector_base() { _M_deallocate(_M_start, _M_end_of_storage - _M_start); }

 protected:
  _Tp *_M_start;
  _Tp *_M_finish;
  _Tp *_M_end_of_storage;

  typedef simple_alloc<_Tp, _Alloc> _M_data_allocator;
  _Tp *_M_allocate(size_t __n) { return _M_data_allocator::allocate(__n); }
  void _M_deallocate(_Tp *__p, size_t __n) { _M_data_allocator::deallocate(__p, __n); }
};

#endif /* __STL_USE_STD_ALLOCATORS */

/* vector */
template<class _Tp, class _Alloc = __STL_DEFAULT_ALLOCATOR(_Tp)>
class vector : protected _Vector_base<_Tp, _Alloc> {
  // requirements:

  __STL_CLASS_REQUIRES(_Tp, _Assignable
  );

 private:
  typedef _Vector_base<_Tp, _Alloc> _Base;
 public:
  /* 嵌套类型定义 */
  typedef _Tp value_type;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;
  typedef value_type *iterator;
  typedef const value_type *const_iterator;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  typedef typename _Base::allocator_type allocator_type;
  allocator_type get_allocator() const { return _Base::get_allocator(); }

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
  typedef reverse_iterator<const_iterator> const_reverse_iterator;
  typedef reverse_iterator<iterator> reverse_iterator;
#else /* __STL_CLASS_PARTIAL_SPECIALIZATION */
  typedef reverse_iterator<const_iterator, value_type, const_reference,
  difference_type> const_reverse_iterator;
  typedef reverse_iterator<iterator, value_type, reference, difference_type>
	  reverse_iterator;
#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

 protected:
#ifdef __STL_HAS_NAMESPACES
  using _Base::_M_allocate;
  using _Base::_M_deallocate;
  using _Base::_M_start;
  using _Base::_M_finish;
  using _Base::_M_end_of_storage;
#endif /* __STL_HAS_NAMESPACES */

 protected:
  void _M_insert_aux(iterator __position, const _Tp &__x);
  void _M_insert_aux(iterator __position);

 public:
  iterator begin() { return _M_start; }
  const_iterator begin() const { return _M_start; }
  iterator end() { return _M_finish; }
  const_iterator end() const { return _M_finish; }

  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

  size_type size() const { return size_type(end() - begin()); }
  size_type max_size() const { return size_type(-1)/sizeof(_Tp); }
  size_type capacity() const { return size_type(_M_end_of_storage - begin()); }
  bool empty() const { return begin()==end(); }

  // 操作符重载
  reference operator[](size_type __n) { return *(begin() + __n); }
  const_reference operator[](size_type __n) const { return *(begin() + __n); }

#ifdef __STL_THROW_RANGE_ERRORS
  void _M_range_check(size_type __n) const {
	if (__n >= this->size())
	  __stl_throw_range_error("vector");
  }

  reference at(size_type __n)
	{ _M_range_check(__n); return (*this)[__n]; }
  const_reference at(size_type __n) const
	{ _M_range_check(__n); return (*this)[__n]; }
#endif /* __STL_THROW_RANGE_ERRORS */

  // 构造函数
  // 空间初始化为 0
  explicit vector(const allocator_type &__a = allocator_type())
	  : _Base(__a) {}

  // 初始化 n 个值为 value 的元素
  vector(size_type __n, const _Tp &__value,
		 const allocator_type &__a = allocator_type())
	  : _Base(__n, __a) { _M_finish = uninitialized_fill_n(_M_start, __n, __value); }

  // 初始化 n 个值为 Tp() 的元素
  explicit vector(size_type __n)
	  : _Base(__n, allocator_type()) { _M_finish = uninitialized_fill_n(_M_start, __n, _Tp()); }

  // 拷贝构造函数
  vector(const vector<_Tp, _Alloc> &__x)
	  : _Base(__x.size(), __x.get_allocator()) { _M_finish = uninitialized_copy(__x.begin(), __x.end(), _M_start); }

#ifdef __STL_MEMBER_TEMPLATES
  // Check whether it's an integral type.  If so, it's not an iterator.
  // 区间拷贝
  template <class _InputIterator>
  vector(_InputIterator __first, _InputIterator __last,
		 const allocator_type& __a = allocator_type()) : _Base(__a) {
	typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
	_M_initialize_aux(__first, __last, _Integral());
  }

  // 如果是值是 integral，就直接调用 uninitialized_fill_n 函数
  template <class _Integer>
  void _M_initialize_aux(_Integer __n, _Integer __value, __true_type) {
	_M_start = _M_allocate(__n);
	_M_end_of_storage = _M_start + __n;
	_M_finish = uninitialized_fill_n(_M_start, __n, __value);
  }

  // 否则调用 _M_range_initialize 函数，调用的该函数版本实际上是再调用 push_back 函数
  template <class _InputIterator>
  void _M_initialize_aux(_InputIterator __first, _InputIterator __last,
						 __false_type) {
	_M_range_initialize(__first, __last, __ITERATOR_CATEGORY(__first));
  }

#else
  vector(const _Tp *__first, const _Tp *__last,
		 const allocator_type &__a = allocator_type())
	  : _Base(__last - __first, __a) { _M_finish = uninitialized_copy(__first, __last, _M_start); }
#endif /* __STL_MEMBER_TEMPLATES */

  ~vector() { destroy(_M_start, _M_finish); }
  // 赋值构造函数
  vector<_Tp, _Alloc> &operator=(const vector<_Tp, _Alloc> &__x);
  // 重新调整空间大小( n>capacity() 时起作用)，需使用 _M_allocate_and_copy、destroy、_M_deallocate 等函数
  void reserve(size_type __n) {
	if (capacity() < __n) {
	  const size_type __old_size = size();
	  iterator __tmp = _M_allocate_and_copy(__n, _M_start, _M_finish);
	  destroy(_M_start, _M_finish);
	  _M_deallocate(_M_start, _M_end_of_storage - _M_start);
	  _M_start = __tmp;
	  _M_finish = __tmp + __old_size;
	  _M_end_of_storage = _M_start + __n;
	}
  }

  // assign(), a generalized assignment member function.  Two
  // versions: one that takes a count, and one that takes a range.
  // The range version is a member template, so we dispatch on whether
  // or not the type is an integer.

  void assign(size_type __n, const _Tp &__val) { _M_fill_assign(__n, __val); }
  void _M_fill_assign(size_type __n, const _Tp &__val);

#ifdef __STL_MEMBER_TEMPLATES

  template <class _InputIterator>
  void assign(_InputIterator __first, _InputIterator __last) {
	typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
	_M_assign_dispatch(__first, __last, _Integral());
  }

  template <class _Integer>
  void _M_assign_dispatch(_Integer __n, _Integer __val, __true_type)
	{ _M_fill_assign((size_type) __n, (_Tp) __val); }

  template <class _InputIter>
  void _M_assign_dispatch(_InputIter __first, _InputIter __last, __false_type)
	{ _M_assign_aux(__first, __last, __ITERATOR_CATEGORY(__first)); }

  template <class _InputIterator>
  void _M_assign_aux(_InputIterator __first, _InputIterator __last,
					 input_iterator_tag);

  template <class _ForwardIterator>
  void _M_assign_aux(_ForwardIterator __first, _ForwardIterator __last,
					 forward_iterator_tag);

#endif /* __STL_MEMBER_TEMPLATES */

  // 首尾元素
  reference front() { return *begin(); }
  const_reference front() const { return *begin(); }
  reference back() { return *(end() - 1); }
  const_reference back() const { return *(end() - 1); }

  // 在尾部添加元素
  void push_back(const _Tp &__x) {
	if (_M_finish!=_M_end_of_storage) {
	  construct(_M_finish, __x);
	  ++_M_finish;
	} else
	  _M_insert_aux(end(), __x);
  }
  // 压入默认值
  void push_back() {
	if (_M_finish!=_M_end_of_storage) {
	  construct(_M_finish);
	  ++_M_finish;
	} else
	  _M_insert_aux(end());
  }
  // 交换
  void swap(vector<_Tp, _Alloc> &__x) {
	__STD::swap(_M_start, __x._M_start);
	__STD::swap(_M_finish, __x._M_finish);
	__STD::swap(_M_end_of_storage, __x._M_end_of_storage);
  }
  // 插入元素
  iterator insert(iterator __position, const _Tp &__x) {
	size_type __n = __position - begin();
	// 空间够且插入的位置在尾部
	if (_M_finish!=_M_end_of_storage && __position==end()) {
	  construct(_M_finish, __x);
	  ++_M_finish;
	} else
	  _M_insert_aux(__position, __x);
	return begin() + __n;
  }
  iterator insert(iterator __position) {
	size_type __n = __position - begin();
	if (_M_finish!=_M_end_of_storage && __position==end()) {
	  construct(_M_finish);
	  ++_M_finish;
	} else
	  _M_insert_aux(__position);
	return begin() + __n;
  }
#ifdef __STL_MEMBER_TEMPLATES
  // Check whether it's an integral type.  If so, it's not an iterator.
  // 范围插值
  template <class _InputIterator>
  void insert(iterator __pos, _InputIterator __first, _InputIterator __last) {
	typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
	_M_insert_dispatch(__pos, __first, __last, _Integral());
  }

  template <class _Integer>
  void _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __val,
						  __true_type)
	{ _M_fill_insert(__pos, (size_type) __n, (_Tp) __val); }

  template <class _InputIterator>
  void _M_insert_dispatch(iterator __pos,
						  _InputIterator __first, _InputIterator __last,
						  __false_type) {
	_M_range_insert(__pos, __first, __last, __ITERATOR_CATEGORY(__first));
  }
#else /* __STL_MEMBER_TEMPLATES */
  // 范围插入
  void insert(iterator __position,
			  const_iterator __first, const_iterator __last);
#endif /* __STL_MEMBER_TEMPLATES */

  void insert(iterator __pos, size_type __n, const _Tp &__x) { _M_fill_insert(__pos, __n, __x); }

  void _M_fill_insert(iterator __pos, size_type __n, const _Tp &__x);

  // 删除尾部元素
  void pop_back() {
	--_M_finish;
	destroy(_M_finish);
  }
  // 删除某一位置元素
  iterator erase(iterator __position) {
	if (__position + 1!=end())
	  copy(__position + 1, _M_finish, __position);
	--_M_finish;
	destroy(_M_finish);
	return __position;
  }
  iterator erase(iterator __first, iterator __last) {
	iterator __i = copy(__last, _M_finish, __first);
	destroy(__i, _M_finish);
	_M_finish = _M_finish - (__last - __first);
	return __first;
  }
  // 重新调整存储的元素个数
  void resize(size_type __new_size, const _Tp &__x) {
	if (__new_size < size())
	  erase(begin() + __new_size, end());
	else
	  insert(end(), __new_size - size(), __x);
  }
  void resize(size_type __new_size) { resize(__new_size, _Tp()); }
  // 清除所有元素
  void clear() { erase(begin(), end()); }

 protected:

#ifdef __STL_MEMBER_TEMPLATES
  template <class _ForwardIterator>
  iterator _M_allocate_and_copy(size_type __n, _ForwardIterator __first, 
											   _ForwardIterator __last)
{
	iterator __result = _M_allocate(__n);
	__STL_TRY {
	  uninitialized_copy(__first, __last, __result);
	  return __result;
	}
	__STL_UNWIND(_M_deallocate(__result, __n));
  }
#else /* __STL_MEMBER_TEMPLATES */
  // 分配空间并拷贝，调用 _M_allocate(__n) 分配空间，uninitialized_copy() 拷贝
  iterator _M_allocate_and_copy(size_type __n, const_iterator __first,
								const_iterator __last) {
	iterator __result = _M_allocate(__n);
	__STL_TRY{
		uninitialized_copy(__first, __last, __result);
		return __result;
	}
	__STL_UNWIND(_M_deallocate(__result, __n));
  }
#endif /* __STL_MEMBER_TEMPLATES */

#ifdef __STL_MEMBER_TEMPLATES
  template <class _InputIterator>
  void _M_range_initialize(_InputIterator __first,  
						   _InputIterator __last, input_iterator_tag)
  {
	for ( ; __first != __last; ++__first)
	  push_back(*__first);
  }

  // This function is only called by the constructor.
  template <class _ForwardIterator>
  void _M_range_initialize(_ForwardIterator __first,
						   _ForwardIterator __last, forward_iterator_tag)
  {
	size_type __n = 0;
	distance(__first, __last, __n);
	_M_start = _M_allocate(__n);
	_M_end_of_storage = _M_start + __n;
	_M_finish = uninitialized_copy(__first, __last, _M_start);
  }

  template <class _InputIterator>
  void _M_range_insert(iterator __pos,
					   _InputIterator __first, _InputIterator __last,
					   input_iterator_tag);

  template <class _ForwardIterator>
  void _M_range_insert(iterator __pos,
					   _ForwardIterator __first, _ForwardIterator __last,
					   forward_iterator_tag);

#endif /* __STL_MEMBER_TEMPLATES */
};

/* 操作符重载 */
// 等于操作符，比较两个 vector 中的所有元素是否一一相等，调用 equal 函数
template<class _Tp, class _Alloc>
inline bool
operator==(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y) {
  return __x.size()==__y.size() &&
	  equal(__x.begin(), __x.end(), __y.begin());
}

// 小于操作符，按字典序比较
template<class _Tp, class _Alloc>
inline bool
operator<(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y) {
  return lexicographical_compare(__x.begin(), __x.end(),
								 __y.begin(), __y.end());
}

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER

template <class _Tp, class _Alloc>
inline void swap(vector<_Tp, _Alloc>& __x, vector<_Tp, _Alloc>& __y)
{
  __x.swap(__y);
}

template <class _Tp, class _Alloc>
inline bool
operator!=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y) {
  return !(__x == __y);
}

template <class _Tp, class _Alloc>
inline bool
operator>(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y) {
  return __y < __x;
}

template <class _Tp, class _Alloc>
inline bool
operator<=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y) {
  return !(__y < __x);
}

template <class _Tp, class _Alloc>
inline bool
operator>=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y) {
  return !(__x < __y);
}

#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

// 赋值构造函数
template<class _Tp, class _Alloc>
vector<_Tp, _Alloc> &
vector<_Tp, _Alloc>::operator=(const vector<_Tp, _Alloc> &__x) {
  if (&__x!=this) {    // 判断是否是自我赋值
	const size_type __xlen = __x.size();
	if (__xlen > capacity()) {    // 如果容量不够，则需要重新分配空间
	  iterator __tmp = _M_allocate_and_copy(__xlen, __x.begin(), __x.end());
	  destroy(_M_start, _M_finish);
	  _M_deallocate(_M_start, _M_end_of_storage - _M_start);
	  _M_start = __tmp;
	  _M_end_of_storage = _M_start + __xlen;
	} else if (size() >= __xlen) {    // 如果空间大于所需的空间，则将其拷贝过来，并 destroy 剩下的
	  iterator __i = copy(__x.begin(), __x.end(), begin());
	  destroy(__i, _M_finish);
	} else {
	  copy(__x.begin(), __x.begin() + size(), _M_start);
	  uninitialized_copy(__x.begin() + size(), __x.end(), _M_finish);
	}
	_M_finish = _M_start + __xlen;
  }
  return *this;
}

template<class _Tp, class _Alloc>
void vector<_Tp, _Alloc>::_M_fill_assign(size_t __n, const value_type &__val) {
  if (__n > capacity()) {
	vector<_Tp, _Alloc> __tmp(__n, __val, get_allocator());
	__tmp.swap(*this);
  } else if (__n > size()) {
	fill(begin(), end(), __val);
	_M_finish = uninitialized_fill_n(_M_finish, __n - size(), __val);
  } else
	erase(fill_n(begin(), __n, __val), end());
}

#ifdef __STL_MEMBER_TEMPLATES

template <class _Tp, class _Alloc> template <class _InputIter>
void vector<_Tp, _Alloc>::_M_assign_aux(_InputIter __first, _InputIter __last,
										input_iterator_tag) {
  iterator __cur = begin();
  for ( ; __first != __last && __cur != end(); ++__cur, ++__first)
	*__cur = *__first;
  if (__first == __last)
	erase(__cur, end());
  else
	insert(end(), __first, __last);
}

template <class _Tp, class _Alloc> template <class _ForwardIter>
void
vector<_Tp, _Alloc>::_M_assign_aux(_ForwardIter __first, _ForwardIter __last,
								   forward_iterator_tag) {
  size_type __len = 0;
  distance(__first, __last, __len);

  if (__len > capacity()) {
	iterator __tmp = _M_allocate_and_copy(__len, __first, __last);
	destroy(_M_start, _M_finish);
	_M_deallocate(_M_start, _M_end_of_storage - _M_start);
	_M_start = __tmp;
	_M_end_of_storage = _M_finish = _M_start + __len;
  }
  else if (size() >= __len) {
	iterator __new_finish = copy(__first, __last, _M_start);
	destroy(__new_finish, _M_finish);
	_M_finish = __new_finish;
  }
  else {
	_ForwardIter __mid = __first;
	advance(__mid, size());
	copy(__first, __mid, _M_start);
	_M_finish = uninitialized_copy(__mid, __last, _M_finish);
  }
}

#endif /* __STL_MEMBER_TEMPLATES */

// insert 辅助函数
template<class _Tp, class _Alloc>
void
vector<_Tp, _Alloc>::_M_insert_aux(iterator __position, const _Tp &__x) {
  if (_M_finish!=_M_end_of_storage) {    // 如果还有剩余空间，则进行复制
	construct(_M_finish, *(_M_finish - 1));
	++_M_finish;
	_Tp __x_copy = __x;
	copy_backward(__position, _M_finish - 2, _M_finish - 1);
	*__position = __x_copy;
  } else {    // 否则申请新空间
	const size_type __old_size = size();
	const size_type __len = __old_size!=0 ? 2*__old_size : 1;    // 新空间为旧空间的两倍
	iterator __new_start = _M_allocate(__len);
	iterator __new_finish = __new_start;
	__STL_TRY{    // 将元素拷贝，并将值插入到相应位置
		__new_finish = uninitialized_copy(_M_start, __position, __new_start);
		construct(__new_finish, __x);
		++__new_finish;
		__new_finish = uninitialized_copy(__position, _M_finish, __new_finish);
	}
	__STL_UNWIND((destroy(__new_start, __new_finish),
		_M_deallocate(__new_start, __len)));
	destroy(begin(), end());    // destroy 旧元素
	_M_deallocate(_M_start, _M_end_of_storage - _M_start);    // 释放旧空间
	// 设置新的参数
	_M_start = __new_start;
	_M_finish = __new_finish;
	_M_end_of_storage = __new_start + __len;
  }
}

// 与前一个函数基本一致，只是插入的值默认为 Tp()
template<class _Tp, class _Alloc>
void
vector<_Tp, _Alloc>::_M_insert_aux(iterator __position) {
  if (_M_finish!=_M_end_of_storage) {
	construct(_M_finish, *(_M_finish - 1));
	++_M_finish;
	copy_backward(__position, _M_finish - 2, _M_finish - 1);
	*__position = _Tp();
  } else {
	const size_type __old_size = size();
	const size_type __len = __old_size!=0 ? 2*__old_size : 1;
	iterator __new_start = _M_allocate(__len);
	iterator __new_finish = __new_start;
	__STL_TRY{
		__new_finish = uninitialized_copy(_M_start, __position, __new_start);
		construct(__new_finish);
		++__new_finish;
		__new_finish = uninitialized_copy(__position, _M_finish, __new_finish);
	}
	__STL_UNWIND((destroy(__new_start, __new_finish),
		_M_deallocate(__new_start, __len)));
	destroy(begin(), end());
	_M_deallocate(_M_start, _M_end_of_storage - _M_start);
	_M_start = __new_start;
	_M_finish = __new_finish;
	_M_end_of_storage = __new_start + __len;
  }
}

template<class _Tp, class _Alloc>
void vector<_Tp, _Alloc>::_M_fill_insert(iterator __position, size_type __n,
										 const _Tp &__x) {
  if (__n!=0) {
	if (size_type(_M_end_of_storage - _M_finish) >= __n) {    // 若剩余的空间能够满足插入所需的空间
	  _Tp __x_copy = __x;
	  const size_type __elems_after = _M_finish - __position;
	  iterator __old_finish = _M_finish;
	  if (__elems_after > __n) {    // 若插入位置的后面元素的个数大于 n
		/* 为什么要考虑这两种情况呢，是因为这里要区分未初始化的空间和已经有元素的空间
		 * 针对未初始化的空间要使用 uninitialized_ 等函数，而已经有元素的空间 则需使用 copy fill 等函数
		 */
		uninitialized_copy(_M_finish - __n, _M_finish, _M_finish);    // 将位置空出来
		_M_finish += __n;
		copy_backward(__position, __old_finish - __n, __old_finish);    // 从后往前 copy
		fill(__position, __position + __n, __x_copy);    // 填充这 n 个元素
	  } else {
		uninitialized_fill_n(_M_finish, __n - __elems_after, __x_copy);    // 将新元素填充至超过 size() 的部分
		_M_finish += __n - __elems_after;
		uninitialized_copy(__position, __old_finish, _M_finish);    // copy 旧元素到新位置
		_M_finish += __elems_after;
		fill(__position, __old_finish, __x_copy);    // 将新元素填充到原本 size() 的部分
		/* 注意区别上述 uninitialized_fill_n 和 fill 函数，前一个由于空间没有初始化，因此需要调用构造函数来实现填充，
		 * 而 fill 函数则是因为填充的空间已经是初始化了的，其原本就存在着一个元素，其本质是 *first = val; 调用赋值函数
		 */
	  }
	} else {    // 若剩余空间不够
	  const size_type __old_size = size();
	  const size_type __len = __old_size + max(__old_size, __n);	// 新空间为旧空间与分配空间中的最大值加上旧空间
	  iterator __new_start = _M_allocate(__len);
	  iterator __new_finish = __new_start;
	  __STL_TRY{
		  __new_finish = uninitialized_copy(_M_start, __position, __new_start);
		  __new_finish = uninitialized_fill_n(__new_finish, __n, __x);
		  __new_finish
		  = uninitialized_copy(__position, _M_finish, __new_finish);
	  }
	  __STL_UNWIND((destroy(__new_start, __new_finish),
		  _M_deallocate(__new_start, __len)));
	  destroy(_M_start, _M_finish);		// destroy 旧空间元素
	  _M_deallocate(_M_start, _M_end_of_storage - _M_start);	// 释放旧空间
	  _M_start = __new_start;
	  _M_finish = __new_finish;
	  _M_end_of_storage = __new_start + __len;
	}
  }
}

#ifdef __STL_MEMBER_TEMPLATES

// 范围插入，就是调用 insert 函数
template <class _Tp, class _Alloc> template <class _InputIterator>
void 
vector<_Tp, _Alloc>::_M_range_insert(iterator __pos, 
									 _InputIterator __first,
									 _InputIterator __last,
									 input_iterator_tag)
{
  for ( ; __first != __last; ++__first) {
	__pos = insert(__pos, *__first);
	++__pos;
  }
}

template <class _Tp, class _Alloc> template <class _ForwardIterator>
void
vector<_Tp, _Alloc>::_M_range_insert(iterator __position,
									 _ForwardIterator __first,
									 _ForwardIterator __last,
									 forward_iterator_tag)
{
  if (__first != __last) {
	size_type __n = 0;
	distance(__first, __last, __n);
	if (size_type(_M_end_of_storage - _M_finish) >= __n) {
	  const size_type __elems_after = _M_finish - __position;
	  iterator __old_finish = _M_finish;
	  if (__elems_after > __n) {
		uninitialized_copy(_M_finish - __n, _M_finish, _M_finish);
		_M_finish += __n;
		copy_backward(__position, __old_finish - __n, __old_finish);
		copy(__first, __last, __position);
	  }
	  else {
		_ForwardIterator __mid = __first;
		advance(__mid, __elems_after);
		uninitialized_copy(__mid, __last, _M_finish);
		_M_finish += __n - __elems_after;
		uninitialized_copy(__position, __old_finish, _M_finish);
		_M_finish += __elems_after;
		copy(__first, __mid, __position);
	  }
	}
	else {
	  const size_type __old_size = size();
	  const size_type __len = __old_size + max(__old_size, __n);
	  iterator __new_start = _M_allocate(__len);
	  iterator __new_finish = __new_start;
	  __STL_TRY {
		__new_finish = uninitialized_copy(_M_start, __position, __new_start);
		__new_finish = uninitialized_copy(__first, __last, __new_finish);
		__new_finish
		  = uninitialized_copy(__position, _M_finish, __new_finish);
	  }
	  __STL_UNWIND((destroy(__new_start,__new_finish),
					_M_deallocate(__new_start,__len)));
	  destroy(_M_start, _M_finish);
	  _M_deallocate(_M_start, _M_end_of_storage - _M_start);
	  _M_start = __new_start;
	  _M_finish = __new_finish;
	  _M_end_of_storage = __new_start + __len;
	}
  }
}

#else /* __STL_MEMBER_TEMPLATES */

// 区间插入新元素，同上面函数分析差不多
template<class _Tp, class _Alloc>
void
vector<_Tp, _Alloc>::insert(iterator __position,
							const_iterator __first,
							const_iterator __last) {
  if (__first!=__last) {
	size_type __n = 0;
	distance(__first, __last, __n);
	if (size_type(_M_end_of_storage - _M_finish) >= __n) {	// 剩余空间足够插入新元素
	  const size_type __elems_after = _M_finish - __position;	// 插入位置的后面的元素个数
	  iterator __old_finish = _M_finish;
	  if (__elems_after > __n) {	// 后面的元素个数大于要插入的元素个数
		uninitialized_copy(_M_finish - __n, _M_finish, _M_finish);	// 初始化并拷贝
		_M_finish += __n;
		copy_backward(__position, __old_finish - __n, __old_finish); // 逆向拷贝旧元素
		copy(__first, __last, __position);	// 拷贝新元素
	  } else {
		uninitialized_copy(__first + __elems_after, __last, _M_finish);
		_M_finish += __n - __elems_after;
		uninitialized_copy(__position, __old_finish, _M_finish);
		_M_finish += __elems_after;
		copy(__first, __first + __elems_after, __position);
	  }
	} else {	// 剩余空间不够插入新元素，则重新分配空间
	  const size_type __old_size = size();
	  const size_type __len = __old_size + max(__old_size, __n);
	  iterator __new_start = _M_allocate(__len);
	  iterator __new_finish = __new_start;
	  __STL_TRY{
		  __new_finish = uninitialized_copy(_M_start, __position, __new_start);
		  __new_finish = uninitialized_copy(__first, __last, __new_finish);
		  __new_finish
		  = uninitialized_copy(__position, _M_finish, __new_finish);
	  }
	  __STL_UNWIND((destroy(__new_start, __new_finish),
		  _M_deallocate(__new_start, __len)));
	  destroy(_M_start, _M_finish);
	  _M_deallocate(_M_start, _M_end_of_storage - _M_start);
	  _M_start = __new_start;
	  _M_finish = __new_finish;
	  _M_end_of_storage = __new_start + __len;
	}
  }
}

#endif /* __STL_MEMBER_TEMPLATES */

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM!=_MIPS_SIM_ABI32)
#pragma reset woff 1174
#pragma reset woff 1375
#endif

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_VECTOR_H */

// Local Variables:
// mode:C++
// End:
