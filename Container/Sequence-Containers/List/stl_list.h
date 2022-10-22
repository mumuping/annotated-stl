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

#ifndef __SGI_STL_INTERNAL_LIST_H
#define __SGI_STL_INTERNAL_LIST_H

#include <concept_checks.h>

__STL_BEGIN_NAMESPACE

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM!=_MIPS_SIM_ABI32)
#pragma set woff 1174
#pragma set woff 1375
#endif

/* list base 节点 */
struct _List_node_base {
  _List_node_base *_M_next;
  _List_node_base *_M_prev;
};

/* list 节点 */
template<class _Tp>
struct _List_node : public _List_node_base {
  _Tp _M_data;
};

/* list base 迭代器 */
struct _List_iterator_base {
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  // 注意这里 list 迭代器类型与 vector 迭代器类型不同
  typedef bidirectional_iterator_tag iterator_category;

  _List_node_base *_M_node;

  // 构造函数
  _List_iterator_base(_List_node_base *__x) : _M_node(__x) {}
  _List_iterator_base() {}

  // 下一个或上一个 node
  void _M_incr() { _M_node = _M_node->_M_next; }
  void _M_decr() { _M_node = _M_node->_M_prev; }

  // 操作符重载
  bool operator==(const _List_iterator_base &__x) const {
	return _M_node==__x._M_node;
  }
  bool operator!=(const _List_iterator_base &__x) const {
	return _M_node!=__x._M_node;
  }
};

/* list 迭代器 */
template<class _Tp, class _Ref, class _Ptr>
struct _List_iterator : public _List_iterator_base {
  typedef _List_iterator<_Tp, _Tp &, _Tp *> iterator;
  typedef _List_iterator<_Tp, const _Tp &, const _Tp *> const_iterator;
  typedef _List_iterator<_Tp, _Ref, _Ptr> _Self;

  typedef _Tp value_type;
  typedef _Ptr pointer;
  typedef _Ref reference;
  typedef _List_node<_Tp> _Node;

  // 构造函数
  _List_iterator(_Node *__x) : _List_iterator_base(__x) {}
  _List_iterator() {}
  _List_iterator(const iterator &__x) : _List_iterator_base(__x._M_node) {}

  // * 操作符重载
  reference operator*() const { return ((_Node *)_M_node)->_M_data; }

#ifndef __SGI_STL_NO_ARROW_OPERATOR
  pointer operator->() const { return &(operator*()); }
#endif /* __SGI_STL_NO_ARROW_OPERATOR */

  // 自增 和 自减
  _Self &operator++() {
	this->_M_incr();
	return *this;
  }
  _Self operator++(int) {
	_Self __tmp = *this;
	this->_M_incr();
	return __tmp;
  }
  _Self &operator--() {
	this->_M_decr();
	return *this;
  }
  _Self operator--(int) {
	_Self __tmp = *this;
	this->_M_decr();
	return __tmp;
  }
};

#ifndef __STL_CLASS_PARTIAL_SPECIALIZATION

// 一些偏特化
inline bidirectional_iterator_tag
iterator_category(const _List_iterator_base &) {
  return bidirectional_iterator_tag();
}

template<class _Tp, class _Ref, class _Ptr>
inline _Tp *
value_type(const _List_iterator<_Tp, _Ref, _Ptr> &) {
  return 0;
}

inline ptrdiff_t *
distance_type(const _List_iterator_base &) {
  return 0;
}

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */


// Base class that encapsulates details of allocators.  Three cases:
// an ordinary standard-conforming allocator, a standard-conforming
// allocator with no non-static data, and an SGI-style allocator.
// This complexity is necessary only because we're worrying about backward
// compatibility and because we want to avoid wasting storage on an 
// allocator instance if it isn't necessary.

#ifdef __STL_USE_STD_ALLOCATORS

// Base for general standard-conforming allocators.
/* 基本的满足标准的通用配置器 */
template <class _Tp, class _Allocator, bool _IsStatic>
class _List_alloc_base {
public:
  typedef typename _Alloc_traits<_Tp, _Allocator>::allocator_type
		  allocator_type;
  allocator_type get_allocator() const { return _Node_allocator; }

  _List_alloc_base(const allocator_type& __a) : _Node_allocator(__a) {}

protected:
  _List_node<_Tp>* _M_get_node()
   { return _Node_allocator.allocate(1); }
  void _M_put_node(_List_node<_Tp>* __p)
	{ _Node_allocator.deallocate(__p, 1); }

protected:
  typename _Alloc_traits<_List_node<_Tp>, _Allocator>::allocator_type
		   _Node_allocator;
  _List_node<_Tp>* _M_node;
};

// Specialization for instanceless allocators.
// 偏特化
template <class _Tp, class _Allocator>
class _List_alloc_base<_Tp, _Allocator, true> {
public:
  typedef typename _Alloc_traits<_Tp, _Allocator>::allocator_type
		  allocator_type;
  allocator_type get_allocator() const { return allocator_type(); }

  _List_alloc_base(const allocator_type&) {}

protected:
  typedef typename _Alloc_traits<_List_node<_Tp>, _Allocator>::_Alloc_type
		  _Alloc_type;
  _List_node<_Tp>* _M_get_node() { return _Alloc_type::allocate(1); }
  void _M_put_node(_List_node<_Tp>* __p) { _Alloc_type::deallocate(__p, 1); }

protected:
  _List_node<_Tp>* _M_node;
};

/* 配置器 */
template <class _Tp, class _Alloc>
class _List_base
  : public _List_alloc_base<_Tp, _Alloc,
							_Alloc_traits<_Tp, _Alloc>::_S_instanceless>
{
public:
  typedef _List_alloc_base<_Tp, _Alloc,
						   _Alloc_traits<_Tp, _Alloc>::_S_instanceless>
		  _Base;
  typedef typename _Base::allocator_type allocator_type;

  // 构造函数，初始化
  _List_base(const allocator_type& __a) : _Base(__a) {
	_M_node = _M_get_node();
	_M_node->_M_next = _M_node;
	_M_node->_M_prev = _M_node;
  }
  // 析构函数，释放所有空间
  ~_List_base() {
	clear(); // 释放除 m_node 外的所有空间
	_M_put_node(_M_node); // 释放 m_node 空间
  }

  void clear();
};

#else /* __STL_USE_STD_ALLOCATORS */
// 使用 simple_alloc 作为配置器
template<class _Tp, class _Alloc>
class _List_base {
 public:
  typedef _Alloc allocator_type;
  allocator_type get_allocator() const { return allocator_type(); }

  // 初始化一个空的 node，前后节点都指向自己，以此判断 list 是否为空
  _List_base(const allocator_type &) {
	_M_node = _M_get_node();
	_M_node->_M_next = _M_node;
	_M_node->_M_prev = _M_node;
  }
  // 析构函数，释放所有空间
  ~_List_base() {
	clear();
	_M_put_node(_M_node);
  }

  void clear();

 protected:
  typedef simple_alloc<_List_node<_Tp>, _Alloc> _Alloc_type;
  _List_node<_Tp> *_M_get_node() { return _Alloc_type::allocate(1); }
  void _M_put_node(_List_node<_Tp> *__p) { _Alloc_type::deallocate(__p, 1); }

 protected:
  _List_node<_Tp> *_M_node;
};

#endif /* __STL_USE_STD_ALLOCATORS */

// 释放除 m_node 外的所有空间
template<class _Tp, class _Alloc>
void
_List_base<_Tp, _Alloc>::clear() {
  _List_node<_Tp> *__cur = (_List_node<_Tp> *)_M_node->_M_next;
  while (__cur!=_M_node) {
	_List_node<_Tp> *__tmp = __cur;
	__cur = (_List_node<_Tp> *)__cur->_M_next;
	_Destroy(&__tmp->_M_data);
	_M_put_node(__tmp);
  }
  _M_node->_M_next = _M_node;
  _M_node->_M_prev = _M_node;
}

/* list */
template<class _Tp, class _Alloc = __STL_DEFAULT_ALLOCATOR(_Tp)>
class list : protected _List_base<_Tp, _Alloc> {
  // requirements:

  __STL_CLASS_REQUIRES(_Tp, _Assignable
  );

  // 一些 typedef
  typedef _List_base<_Tp, _Alloc> _Base;
 protected:
  typedef void *_Void_pointer;

 public:
  typedef _Tp value_type;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef _List_node<_Tp> _Node;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  typedef typename _Base::allocator_type allocator_type;
  allocator_type get_allocator() const { return _Base::get_allocator(); }

 public:
  typedef _List_iterator<_Tp, _Tp &, _Tp *> iterator;
  typedef _List_iterator<_Tp, const _Tp &, const _Tp *> const_iterator;

  // 反向迭代器
#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
  typedef reverse_iterator<const_iterator> const_reverse_iterator;
  typedef reverse_iterator<iterator>       reverse_iterator;
#else /* __STL_CLASS_PARTIAL_SPECIALIZATION */
  typedef reverse_bidirectional_iterator<const_iterator, value_type,
  const_reference, difference_type>
	  const_reverse_iterator;
  typedef reverse_bidirectional_iterator<iterator, value_type, reference,
  difference_type>
	  reverse_iterator;
#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

 protected:
#ifdef __STL_HAS_NAMESPACES
  using _Base::_M_node;
  using _Base::_M_put_node;
  using _Base::_M_get_node;
#endif /* __STL_HAS_NAMESPACES */

 protected:
  // 创建一个节点
  _Node *_M_create_node(const _Tp &__x) {
	_Node *__p = _M_get_node(); // 分配空间
	__STL_TRY{
		_Construct(&__p->_M_data, __x);    // 构造
	}
	__STL_UNWIND(_M_put_node(__p));
	return __p;
  }

  _Node *_M_create_node() {
	_Node *__p = _M_get_node();
	__STL_TRY{
		_Construct(&__p->_M_data);
	}
	__STL_UNWIND(_M_put_node(__p));
	return __p;
  }

 public:
  // 构造函数
  explicit list(const allocator_type &__a = allocator_type()) : _Base(__a) {}

  // 迭代器相关函数
  iterator begin() { return (_Node *)(_M_node->_M_next); }
  const_iterator begin() const { return (_Node *)(_M_node->_M_next); }

  iterator end() { return _M_node; }
  const_iterator end() const { return _M_node; }

  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

  // 数量相关函数
  // 是否为空
  bool empty() const { return _M_node->_M_next==_M_node; }
  size_type size() const {
	size_type __result = 0;
	// 在 distance 函数中，若 iterator 为 random-access 则调用 operator-，
	// 否则重复使用 operator++。显然这里是重复使用 operator++
	distance(begin(), end(), __result);
	return __result;
  }
  size_type max_size() const { return size_type(-1); }

  // 头元素和尾元素
  reference front() { return *begin(); }
  const_reference front() const { return *begin(); }
  reference back() { return *(--end()); }
  const_reference back() const { return *(--end()); }

  // 交换
  void swap(list<_Tp, _Alloc> &__x) { __STD::swap(_M_node, __x._M_node); }

  // 插入元素，即链表操作中的插入
  iterator insert(iterator __position, const _Tp &__x) {
	_Node *__tmp = _M_create_node(__x);
	__tmp->_M_next = __position._M_node;
	__tmp->_M_prev = __position._M_node->_M_prev;
	__position._M_node->_M_prev->_M_next = __tmp;
	__position._M_node->_M_prev = __tmp;
	return __tmp;
  }
  // 插入默认值
  iterator insert(iterator __position) { return insert(__position, _Tp()); }
#ifdef __STL_MEMBER_TEMPLATES
  // Check whether it's an integral type.  If so, it's not an iterator.
	// 区间插入
  template<class _Integer>
  void _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __x,
						  __true_type) {
	_M_fill_insert(__pos, (size_type) __n, (_Tp) __x);
  }

  template <class _InputIterator>
  void _M_insert_dispatch(iterator __pos,
						  _InputIterator __first, _InputIterator __last,
						  __false_type);

  template <class _InputIterator>
  void insert(iterator __pos, _InputIterator __first, _InputIterator __last) {
	typedef typename _Is_integer<_InputIterator>::_Integral _Integral;
	_M_insert_dispatch(__pos, __first, __last, _Integral());
  }

#else /* __STL_MEMBER_TEMPLATES */
  // 区间插入
  void insert(iterator __position, const _Tp *__first, const _Tp *__last);
  void insert(iterator __position,
			  const_iterator __first, const_iterator __last);
#endif /* __STL_MEMBER_TEMPLATES */
  void insert(iterator __pos, size_type __n, const _Tp &__x) { _M_fill_insert(__pos, __n, __x); }
  void _M_fill_insert(iterator __pos, size_type __n, const _Tp &__x);

  // 在链头或链尾插入元素
  void push_front(const _Tp &__x) { insert(begin(), __x); }
  void push_front() { insert(begin()); }
  void push_back(const _Tp &__x) { insert(end(), __x); }
  void push_back() { insert(end()); }

  // 删除某位置元素
  iterator erase(iterator __position) {
	_List_node_base *__next_node = __position._M_node->_M_next;
	_List_node_base *__prev_node = __position._M_node->_M_prev;
	_Node *__n = (_Node *)__position._M_node;
	__prev_node->_M_next = __next_node;
	__next_node->_M_prev = __prev_node;
	_Destroy(&__n->_M_data);
	_M_put_node(__n);
	return iterator((_Node *)__next_node);
  }
  // 区间删除
  iterator erase(iterator __first, iterator __last);
  // 删除所有元素
  void clear() { _Base::clear(); }

  // 调整空间大小
  void resize(size_type __new_size, const _Tp &__x);
  void resize(size_type __new_size) { this->resize(__new_size, _Tp()); }

  // 弹出头元素或尾元素
  void pop_front() { erase(begin()); }
  void pop_back() {
	iterator __tmp = end();
	erase(--__tmp);
  }

  // 构造函数
  list(size_type __n, const _Tp &__value,
	   const allocator_type &__a = allocator_type())
	  : _Base(__a) { insert(begin(), __n, __value); }
  explicit list(size_type __n)
	  : _Base(allocator_type()) { insert(begin(), __n, _Tp()); }

#ifdef __STL_MEMBER_TEMPLATES

  // We don't need any dispatching tricks here, because insert does all of
  // that anyway.
  // 区间构造
  template <class _InputIterator>
  list(_InputIterator __first, _InputIterator __last,
	   const allocator_type& __a = allocator_type())
	: _Base(__a)
	{ insert(begin(), __first, __last); }

#else /* __STL_MEMBER_TEMPLATES */

  list(const _Tp *__first, const _Tp *__last,
	   const allocator_type &__a = allocator_type())
	  : _Base(__a) { this->insert(begin(), __first, __last); }
  list(const_iterator __first, const_iterator __last,
	   const allocator_type &__a = allocator_type())
	  : _Base(__a) { this->insert(begin(), __first, __last); }

#endif /* __STL_MEMBER_TEMPLATES */
// 拷贝构造
  list(const list<_Tp, _Alloc> &__x) : _Base(__x.get_allocator()) { insert(begin(), __x.begin(), __x.end()); }

  ~list() {}

  // 赋值构造
  list<_Tp, _Alloc> &operator=(const list<_Tp, _Alloc> &__x);

 public:
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

  template <class _InputIterator>
  void _M_assign_dispatch(_InputIterator __first, _InputIterator __last,
						  __false_type);

#endif /* __STL_MEMBER_TEMPLATES */

 protected:
  // 移动元素，链表操作
  // 注意这里 [first, last) 区间不能包含 position，否则会出现内存泄漏问题
  void transfer(iterator __position, iterator __first, iterator __last) {
	if (__position!=__last) {
	  // Remove [first, last) from its old position.
	  __last._M_node->_M_prev->_M_next = __position._M_node;
	  __first._M_node->_M_prev->_M_next = __last._M_node;
	  __position._M_node->_M_prev->_M_next = __first._M_node;

	  // Splice [first, last) into its new position.
	  _List_node_base *__tmp = __position._M_node->_M_prev;
	  __position._M_node->_M_prev = __last._M_node->_M_prev;
	  __last._M_node->_M_prev = __first._M_node->_M_prev;
	  __first._M_node->_M_prev = __tmp;
	}
  }

 public:
  // 将 list x 中的元素移动到 position 的位置
  void splice(iterator __position, list &__x) {
	if (!__x.empty())
	  this->transfer(__position, __x.begin(), __x.end());
  }
  // 将位置 i 的元素移动到 position
  void splice(iterator __position, list &, iterator __i) {
	iterator __j = __i;
	++__j;
	if (__position==__i || __position==__j) return;
	this->transfer(__position, __i, __j);
  }
  // 范围移动
  void splice(iterator __position, list &, iterator __first, iterator __last) {
	if (__first!=__last)
	  this->transfer(__position, __first, __last);
  }

  // 删除所有值为 value 的元素
  void remove(const _Tp &__value);
  void unique();
  void merge(list &__x);
  void reverse();
  void sort();

#ifdef __STL_MEMBER_TEMPLATES
  template <class _Predicate> void remove_if(_Predicate);
  template <class _BinaryPredicate> void unique(_BinaryPredicate);
  template <class _StrictWeakOrdering> void merge(list&, _StrictWeakOrdering);
  template <class _StrictWeakOrdering> void sort(_StrictWeakOrdering);
#endif /* __STL_MEMBER_TEMPLATES */
};

// 操作符重载
// 依次比较两个 list 中的元素是否相同
template<class _Tp, class _Alloc>
inline bool
operator==(const list<_Tp, _Alloc> &__x, const list<_Tp, _Alloc> &__y) {
  typedef typename list<_Tp, _Alloc>::const_iterator const_iterator;
  const_iterator __end1 = __x.end();
  const_iterator __end2 = __y.end();

  const_iterator __i1 = __x.begin();
  const_iterator __i2 = __y.begin();
  while (__i1!=__end1 && __i2!=__end2 && *__i1==*__i2) {
	++__i1;
	++__i2;
  }
  return __i1==__end1 && __i2==__end2;
}

// 字典序比较
template<class _Tp, class _Alloc>
inline bool operator<(const list<_Tp, _Alloc> &__x,
					  const list<_Tp, _Alloc> &__y) {
  return lexicographical_compare(__x.begin(), __x.end(),
								 __y.begin(), __y.end());
}

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER

// 以下函数调用 == 或 < 重载函数实现
template <class _Tp, class _Alloc>
inline bool operator!=(const list<_Tp,_Alloc>& __x,
					   const list<_Tp,_Alloc>& __y) {
  return !(__x == __y);
}

template <class _Tp, class _Alloc>
inline bool operator>(const list<_Tp,_Alloc>& __x,
					  const list<_Tp,_Alloc>& __y) {
  return __y < __x;
}

template <class _Tp, class _Alloc>
inline bool operator<=(const list<_Tp,_Alloc>& __x,
					   const list<_Tp,_Alloc>& __y) {
  return !(__y < __x);
}

template <class _Tp, class _Alloc>
inline bool operator>=(const list<_Tp,_Alloc>& __x,
					   const list<_Tp,_Alloc>& __y) {
  return !(__x < __y);
}

template <class _Tp, class _Alloc>
inline void 
swap(list<_Tp, _Alloc>& __x, list<_Tp, _Alloc>& __y)
{
  __x.swap(__y);
}

#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

#ifdef __STL_MEMBER_TEMPLATES

// 插入元素
template <class _Tp, class _Alloc> template <class _InputIter>
void 
list<_Tp, _Alloc>::_M_insert_dispatch(iterator __position,
									  _InputIter __first, _InputIter __last,
									  __false_type)
{
  for ( ; __first != __last; ++__first)
	insert(__position, *__first);
}

#else /* __STL_MEMBER_TEMPLATES */
// 区间范围插入
template<class _Tp, class _Alloc>
void
list<_Tp, _Alloc>::insert(iterator __position,
						  const _Tp *__first, const _Tp *__last) {
  for (; __first!=__last; ++__first)
	insert(__position, *__first);
}

template<class _Tp, class _Alloc>
void
list<_Tp, _Alloc>::insert(iterator __position,
						  const_iterator __first, const_iterator __last) {
  for (; __first!=__last; ++__first)
	insert(__position, *__first);
}

#endif /* __STL_MEMBER_TEMPLATES */

template<class _Tp, class _Alloc>
void
list<_Tp, _Alloc>::_M_fill_insert(iterator __position,
								  size_type __n, const _Tp &__x) {
  for (; __n > 0; --__n)
	insert(__position, __x);
}

// 区间删除
template<class _Tp, class _Alloc>
typename list<_Tp, _Alloc>::iterator list<_Tp, _Alloc>::erase(iterator __first,
															  iterator __last) {
  while (__first!=__last)
	erase(__first++);
  return __last;
}

// 调整元素个数，如元素个数小于旧元素个数，则删除剩余元素，否则插入值为 x 的元素
template<class _Tp, class _Alloc>
void list<_Tp, _Alloc>::resize(size_type __new_size, const _Tp &__x) {
  iterator __i = begin();
  size_type __len = 0;
  for (; __i!=end() && __len < __new_size; ++__i, ++__len);
  if (__len==__new_size)
	erase(__i, end());
  else                          // __i == end()
	insert(end(), __new_size - __len, __x);
}

// 赋值构造函数
template<class _Tp, class _Alloc>
list<_Tp, _Alloc> &list<_Tp, _Alloc>::operator=(const list<_Tp, _Alloc> &__x) {
  if (this!=&__x) {
	iterator __first1 = begin();
	iterator __last1 = end();
	const_iterator __first2 = __x.begin();
	const_iterator __last2 = __x.end();
	while (__first1!=__last1 && __first2!=__last2)
	  *__first1++ = *__first2++;
	if (__first2==__last2)
	  erase(__first1, __last1);
	else
	  insert(__last1, __first2, __last2);
  }
  return *this;
}

// assign 函数，将 n 个值为 val 的元素分配给 list，即从 begin 到 end，多余的删除，不够的插入
template<class _Tp, class _Alloc>
void list<_Tp, _Alloc>::_M_fill_assign(size_type __n, const _Tp &__val) {
  iterator __i = begin();
  for (; __i!=end() && __n > 0; ++__i, --__n)
	*__i = __val;
  if (__n > 0)
	insert(end(), __n, __val);
  else
	erase(__i, end());
}

#ifdef __STL_MEMBER_TEMPLATES

template <class _Tp, class _Alloc> template <class _InputIter>
void
list<_Tp, _Alloc>::_M_assign_dispatch(_InputIter __first2, _InputIter __last2,
									  __false_type)
{
  iterator __first1 = begin();
  iterator __last1 = end();
  for ( ; __first1 != __last1 && __first2 != __last2; ++__first1, ++__first2)
	*__first1 = *__first2;
  if (__first2 == __last2)
	erase(__first1, __last1);
  else
	insert(__last1, __first2, __last2);
}

#endif /* __STL_MEMBER_TEMPLATES */

// 删除所有值为 value 的元素
template<class _Tp, class _Alloc>
void list<_Tp, _Alloc>::remove(const _Tp &__value) {
  iterator __first = begin();
  iterator __last = end();
  while (__first!=__last) {
	iterator __next = __first;
	++__next;
	if (*__first==__value) erase(__first);
	__first = __next;
  }
}

// 删除所有连续相同的元素，只留第一个元素
template<class _Tp, class _Alloc>
void list<_Tp, _Alloc>::unique() {
  iterator __first = begin();
  iterator __last = end();
  if (__first==__last) return;
  iterator __next = __first;
  while (++__next!=__last) {
	if (*__first==*__next)
	  erase(__next);
	else
	  __first = __next;
	__next = __first;
  }
}

// 将已经排好序的 x transfer 到同样排好序的 list 中
// 注意最后 x 是一个空的链表
template<class _Tp, class _Alloc>
void list<_Tp, _Alloc>::merge(list<_Tp, _Alloc> &__x) {
  iterator __first1 = begin();
  iterator __last1 = end();
  iterator __first2 = __x.begin();
  iterator __last2 = __x.end();
  while (__first1!=__last1 && __first2!=__last2)
	if (*__first2 < *__first1) {
	  iterator __next = __first2;
	  transfer(__first1, __first2, ++__next);
	  __first2 = __next;
	} else
	  ++__first1;
  if (__first2!=__last2) transfer(__last1, __first2, __last2);
}

// 交换节点内的前后指针指向
inline void __List_base_reverse(_List_node_base *__p) {
  _List_node_base *__tmp = __p;
  do {
	__STD::swap(__tmp->_M_next, __tmp->_M_prev);
	__tmp = __tmp->_M_prev;     // Old next node is now prev.
  } while (__tmp!=__p);
}

// 逆转所有元素
template<class _Tp, class _Alloc>
inline void list<_Tp, _Alloc>::reverse() {
  __List_base_reverse(this->_M_node);
}

// 排序，list 只能使用自带的 sort 函数进行排序，
// 因为 STL 算法中的 sort 只支持 RandomAccessIterator
// 这里采用了归并排序
template<class _Tp, class _Alloc>
void list<_Tp, _Alloc>::sort() {
  // Do nothing if the list has length 0 or 1.
  if (_M_node->_M_next!=_M_node && _M_node->_M_next->_M_next!=_M_node) {
	// 临时存储数据
	list<_Tp, _Alloc> __carry;
	list<_Tp, _Alloc> __counter[64];	// counter[i] 中存储的元素个数为 2^i 个，每个 counter 中都是排好序的
	int __fill = 0;	// fill 表示最高填充到了 counter[fill] 中
	while (!empty()) {
	  __carry.splice(__carry.begin(), *this, begin());
	  int __i = 0;
	  while (__i < __fill && !__counter[__i].empty()) {
		__counter[__i].merge(__carry); // 将 carry 中的元素和 counter[i] 合并
		__carry.swap(__counter[__i++]);	// 将元素放在 carry 中，并将 counter[i] 设置为空
	  }
	  __carry.swap(__counter[__i]);	// 将最后合并的值放在 counter[i+1]（i 为上面注释中的 i） 中
	  if (__i==__fill) ++__fill;
	}

	// 最后将所有 counter 中的元素合并
	for (int __i = 1; __i < __fill; ++__i)
	  __counter[__i].merge(__counter[__i - 1]);
	swap(__counter[__fill - 1]);
  }
}

#ifdef __STL_MEMBER_TEMPLATES

// 条件删除
template <class _Tp, class _Alloc> template <class _Predicate>
void list<_Tp, _Alloc>::remove_if(_Predicate __pred)
{
  iterator __first = begin();
  iterator __last = end();
  while (__first != __last) {
	iterator __next = __first;
	++__next;
	if (__pred(*__first)) erase(__first);
	__first = __next;
  }
}

// 条件去重
template <class _Tp, class _Alloc> template <class _BinaryPredicate>
void list<_Tp, _Alloc>::unique(_BinaryPredicate __binary_pred)
{
  iterator __first = begin();
  iterator __last = end();
  if (__first == __last) return;
  iterator __next = __first;
  while (++__next != __last) {
	if (__binary_pred(*__first, *__next))
	  erase(__next);
	else
	  __first = __next;
	__next = __first;
  }
}

// 条件合并
// Binary predicate that, taking two values of the same type than those contained in the list, returns true if
// the first argument is considered to go before the second in the strict weak ordering it defines, and false otherwise.
// This shall be a function pointer or a function object.template <class _Tp, class _Alloc> template <class
template <class _Tp, class _Alloc> template <class _StrictWeakOrdering>
void list<_Tp, _Alloc>::merge(list<_Tp, _Alloc>& __x,
							  _StrictWeakOrdering __comp)
{
  iterator __first1 = begin();
  iterator __last1 = end();
  iterator __first2 = __x.begin();
  iterator __last2 = __x.end();
  while (__first1 != __last1 && __first2 != __last2)
	if (__comp(*__first2, *__first1)) {
	  iterator __next = __first2;
	  transfer(__first1, __first2, ++__next);
	  __first2 = __next;
	}
	else
	  ++__first1;
  if (__first2 != __last2) transfer(__last1, __first2, __last2);
}

// 条件排序
template <class _Tp, class _Alloc> template <class _StrictWeakOrdering>
void list<_Tp, _Alloc>::sort(_StrictWeakOrdering __comp)
{
  // Do nothing if the list has length 0 or 1.
  if (_M_node->_M_next != _M_node && _M_node->_M_next->_M_next != _M_node) {
	list<_Tp, _Alloc> __carry;
	list<_Tp, _Alloc> __counter[64];
	int __fill = 0;
	while (!empty()) {
	  __carry.splice(__carry.begin(), *this, begin());
	  int __i = 0;
	  while(__i < __fill && !__counter[__i].empty()) {
		__counter[__i].merge(__carry, __comp);
		__carry.swap(__counter[__i++]);
	  }
	  __carry.swap(__counter[__i]);
	  if (__i == __fill) ++__fill;
	}

	for (int __i = 1; __i < __fill; ++__i)
	  __counter[__i].merge(__counter[__i-1], __comp);
	swap(__counter[__fill-1]);
  }
}

#endif /* __STL_MEMBER_TEMPLATES */

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM!=_MIPS_SIM_ABI32)
#pragma reset woff 1174
#pragma reset woff 1375
#endif

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_LIST_H */

// Local Variables:
// mode:C++
// End:
