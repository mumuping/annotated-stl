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


#ifndef __SGI_STL_INTERNAL_NUMERIC_H
#define __SGI_STL_INTERNAL_NUMERIC_H

__STL_BEGIN_NAMESPACE

// 将每个元素累加到 init 上
// 这里设置 init 是因为当 [first, last) 为空时，仍能返回一个有意义的值
template <class _InputIterator, class _Tp>
_Tp accumulate(_InputIterator __first, _InputIterator __last, _Tp __init)
{
  __STL_REQUIRES(_InputIterator, _InputIterator);
  for ( ; __first != __last; ++__first)
    __init = __init + *__first;
  return __init;
}

// 把 init 和迭代区间中的每个元素进行一个二元操作
template <class _InputIterator, class _Tp, class _BinaryOperation>
_Tp accumulate(_InputIterator __first, _InputIterator __last, _Tp __init,
               _BinaryOperation __binary_op)
{
  __STL_REQUIRES(_InputIterator, _InputIterator);
  for ( ; __first != __last; ++__first)
    __init = __binary_op(__init, *__first);
  return __init;
}

// 两个序列的内积
// __init = __init + (*__first1 * *__first2);
template <class _InputIterator1, class _InputIterator2, class _Tp>
_Tp inner_product(_InputIterator1 __first1, _InputIterator1 __last1,
                  _InputIterator2 __first2, _Tp __init)
{
  __STL_REQUIRES(_InputIterator2, _InputIterator);
  __STL_REQUIRES(_InputIterator2, _InputIterator);
  for ( ; __first1 != __last1; ++__first1, ++__first2)
    __init = __init + (*__first1 * *__first2);
  return __init;
}

// 二元操作版本
// __init = __binary_op1(__init, __binary_op2(*__first1, *__first2));
template <class _InputIterator1, class _InputIterator2, class _Tp,
          class _BinaryOperation1, class _BinaryOperation2>
_Tp inner_product(_InputIterator1 __first1, _InputIterator1 __last1,
                  _InputIterator2 __first2, _Tp __init, 
                  _BinaryOperation1 __binary_op1,
                  _BinaryOperation2 __binary_op2)
{
  __STL_REQUIRES(_InputIterator2, _InputIterator);
  __STL_REQUIRES(_InputIterator2, _InputIterator);
  for ( ; __first1 != __last1; ++__first1, ++__first2)
    __init = __binary_op1(__init, __binary_op2(*__first1, *__first2));
  return __init;
}

// 前 n 个元素和的辅助函数
template <class _InputIterator, class _OutputIterator, class _Tp>
_OutputIterator 
__partial_sum(_InputIterator __first, _InputIterator __last,
              _OutputIterator __result, _Tp*)
{
  _Tp __value = *__first;
  while (++__first != __last) {
    __value = __value + *__first;
    *++__result = __value;
  }
  return ++__result;
}

// 前 n 个元素和
template <class _InputIterator, class _OutputIterator>
_OutputIterator 
partial_sum(_InputIterator __first, _InputIterator __last,
            _OutputIterator __result)
{
  __STL_REQUIRES(_InputIterator, _InputIterator);
  __STL_REQUIRES(_OutputIterator, _OutputIterator);
  if (__first == __last) return __result;
  *__result = *__first;
  return __partial_sum(__first, __last, __result, __VALUE_TYPE(__first));
}

// 二元操作版本的前 n 个元素总计的辅助函数
template <class _InputIterator, class _OutputIterator, class _Tp,
          class _BinaryOperation>
_OutputIterator 
__partial_sum(_InputIterator __first, _InputIterator __last, 
              _OutputIterator __result, _Tp*, _BinaryOperation __binary_op)
{
  _Tp __value = *__first;
  while (++__first != __last) {
    __value = __binary_op(__value, *__first);
    *++__result = __value;
  }
  return ++__result;
}

// 二元操作版本的前 n 个元素总计
template <class _InputIterator, class _OutputIterator, class _BinaryOperation>
_OutputIterator 
partial_sum(_InputIterator __first, _InputIterator __last,
            _OutputIterator __result, _BinaryOperation __binary_op)
{
  __STL_REQUIRES(_InputIterator, _InputIterator);
  __STL_REQUIRES(_OutputIterator, _OutputIterator);
  if (__first == __last) return __result;
  *__result = *__first;
  return __partial_sum(__first, __last, __result, __VALUE_TYPE(__first), 
                       __binary_op);
}

// 辅助函数
// 相邻元素的差（后-前），赋值给目标
template <class _InputIterator, class _OutputIterator, class _Tp>
_OutputIterator 
__adjacent_difference(_InputIterator __first, _InputIterator __last,
                      _OutputIterator __result, _Tp*)
{
  _Tp __value = *__first;
  while (++__first != __last) {
    _Tp __tmp = *__first;
    *++__result = __tmp - __value;
    __value = __tmp;
  }
  return ++__result;
}

// 相邻元素的差（后-前），赋值给目标
template <class _InputIterator, class _OutputIterator>
_OutputIterator
adjacent_difference(_InputIterator __first,
                    _InputIterator __last, _OutputIterator __result)
{
  __STL_REQUIRES(_InputIterator, _InputIterator);
  __STL_REQUIRES(_OutputIterator, _OutputIterator);
  if (__first == __last) return __result;
  *__result = *__first;
  return __adjacent_difference(__first, __last, __result,
                               __VALUE_TYPE(__first));
}

// 二元版本的相邻元素差（后-前）
template <class _InputIterator, class _OutputIterator, class _Tp, 
          class _BinaryOperation>
_OutputIterator
__adjacent_difference(_InputIterator __first, _InputIterator __last, 
                      _OutputIterator __result, _Tp*,
                      _BinaryOperation __binary_op) {
  _Tp __value = *__first;
  while (++__first != __last) {
    _Tp __tmp = *__first;
    *++__result = __binary_op(__tmp, __value);
    __value = __tmp;
  }
  return ++__result;
}

// 二元版本的相邻元素差（后-前）
template <class _InputIterator, class _OutputIterator, class _BinaryOperation>
_OutputIterator 
adjacent_difference(_InputIterator __first, _InputIterator __last,
                    _OutputIterator __result, _BinaryOperation __binary_op)
{
  __STL_REQUIRES(_InputIterator, _InputIterator);
  __STL_REQUIRES(_OutputIterator, _OutputIterator);
  if (__first == __last) return __result;
  *__result = *__first;
  return __adjacent_difference(__first, __last, __result,
                               __VALUE_TYPE(__first),
                               __binary_op);
}

// Returns __x ** __n, where __n >= 0.  _Note that "multiplication"
// is required to be associative, but not necessarily commutative.

// 幂次方，如果 n>=0 时返回 x^n
// 注意 _MonoidOperation 必须满足结合律，但不需要满足交换律
template <class _Tp, class _Integer, class _MonoidOperation>
_Tp __power(_Tp __x, _Integer __n, _MonoidOperation __opr)
{
  // 如果 n 为 0，则取出证同元素
  if (__n == 0)
    return identity_element(__opr);
  else {
	// 如果 n 为偶数
    while ((__n & 1) == 0) {
      __n >>= 1;
      __x = __opr(__x, __x);
    }

    _Tp __result = __x;
	// 再往右移动一位
    __n >>= 1;
	// 如果 n 为 0，说明前面 n 为偶数已经计算完了
	// 否则表示 n 为奇数
    while (__n != 0) {
      __x = __opr(__x, __x);
      if ((__n & 1) != 0)
        __result = __opr(__result, __x);
      __n >>= 1;
    }
    return __result;
  }
}

// x 的 n 次幂
template <class _Tp, class _Integer>
inline _Tp __power(_Tp __x, _Integer __n)
{
  return __power(__x, __n, multiplies<_Tp>());	// 指定为乘法
}

// Alias for the internal name __power.  Note that power is an extension,
// not part of the C++ standard.

template <class _Tp, class _Integer, class _MonoidOperation>
inline _Tp power(_Tp __x, _Integer __n, _MonoidOperation __opr)
{
  return __power(__x, __n, __opr);
}

template <class _Tp, class _Integer>
inline _Tp power(_Tp __x, _Integer __n)
{
  return __power(__x, __n);
}

// iota is not part of the C++ standard.  It is an extension.
// 在 [first, last) 区间中填入 value, value+1, value+2 ...
template <class _ForwardIter, class _Tp>
void 
iota(_ForwardIter __first, _ForwardIter __last, _Tp __value)
{
  __STL_REQUIRES(_ForwardIter, _Mutable_ForwardIterator);
  __STL_CONVERTIBLE(_Tp, typename iterator_traits<_ForwardIter>::value_type);
  while (__first != __last)
    *__first++ = __value++;
}

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_NUMERIC_H */

// Local Variables:
// mode:C++
// End:
