# Functor(Function object)

若我们想在一个函数内执行我们自定的一些操作，很容易想到的就是使用函数指针作为参数。但还有另外一种方法，就是写一个类，该类重载了操作符`()`，因此使用该类的对象就像使用普通的函数一样，这就叫做仿函数。既然有函数指针了，那为什么还要仿函数呢？这是因为函数指针并不满足 STL 对抽象性的要求（函数指针无法和 STL 其他组件如 adapter 等搭配）。一个例子是 sort 函数中的第三个参数：

```cpp
template <class RandomAccessIterator, class Compare> 
void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);
```

STL 仿函数若按照操作数 operand 个数划分，可分为一元和二元，若按功能划分，可分为算术运算 Arithmetic、关系运算 Rational、逻辑运算 Logical 三大类。

STL 的仿函数位于 \<functional> 中，实际位于 \<stl_function.h> 中。

STL 仿函数为了应该有能力被函数适配器（function adapter）修饰，每一个仿函数必须定义自己的相应型别（associative types），就像迭代器一样。这些型别是为了让适配器能够取出，获得仿函数的一些信息。相应型别都只是一些 typedef，所有必要操作都在编译期完成，对程序执行效率没太大的影响。

仿函数的型别主要是用来表现函数参数类型和返回类型。在 \<stl_function.h> 中定义了两个 classes，分别代表一元仿函数和二元仿函数。用户可以选择任意一个进行继承，便拥有了相应型别和适配能力。

```cpp
template <class _Arg, class _Result>
struct unary_function {
  typedef _Arg argument_type;
  typedef _Result result_type;
};

template <class _Arg1, class _Arg2, class _Result>
struct binary_function {
  typedef _Arg1 first_argument_type;
  typedef _Arg2 second_argument_type;
  typedef _Result result_type;
}; 

// 用户自定仿函数
template <class T>
struct plus: public binary_function<T,T,T>{
    T operator()(const T& x, const T& y){ return x+y; }
};

// 下面这个适配器将二元仿函数转化为一元仿函数
template <class Operation>
class binder1st{
    // ...
    protected:
        Operation op;
        typename Operation::first_argument_type value;
    public:
        typename Operation::result_type
            operator()(const typename Operation::second_argument_type& x) const{
                // ...
            }
    // ...
}
```

## 算术类（arithmetic）仿函数

加 plus、减 minus、乘 multiplies、除 divides、模 modulus、否定 negate

比如：

```cpp
template <class _Tp>
struct multiplies : public binary_function<_Tp,_Tp,_Tp> {
  _Tp operator()(const _Tp& __x, const _Tp& __y) const { return __x * __y; }
};

// 可以这样使用
// std::accumulate(a.begin(),a.end(),1,multiplies<int>());
```

证同元素（identity_element)：“运算 op 的证同元素”是指数值 A 若与该元素做 op 运算，得到的结果是他自己 A。加法的证同元素是 0，乘法的证同元素是 1。该函数并不是 STL 标准。

```cpp
template <class _Tp> inline _Tp identity_element(plus<_Tp>) {
  return _Tp(0);
}
template <class _Tp> inline _Tp identity_element(multiplies<_Tp>) {
  return _Tp(1);
}
```

## 关系运算类（relational）仿函数

等于 equal_to、不等于 not_equal、大于 greater、大于等于 greater_equal、小于 less、小于等于 less_equal

## 逻辑运算类（logical）仿函数

与 logical_and、或 logical_or、非 logical_not

## 证同（identity）、选择（select）、投影（project）（均不在 C++ 标准中）

这些仿函数均将参数原封不动地传回，只对传回的参数有刻意的选择或者忽略。

```cpp
// identity is an extensions: it is not part of the standard.
// identity 该函数将参数原封不动地传回
// 主要用于 rb-tree 所需的 KeyOfValue op
// 以及 set 元素键值
template <class _Tp>
struct _Identity : public unary_function<_Tp,_Tp> {
  const _Tp& operator()(const _Tp& __x) const { return __x; }
};

template <class _Tp> struct identity : public _Identity<_Tp> {};

// select1st and select2nd are extensions: they are not part of the standard.
// 接受一个 pair，返回 pair 的第一个元素
// 常用于 rb-tree 结构的 map 取出键
template <class _Pair>
struct _Select1st : public unary_function<_Pair, typename _Pair::first_type> {
  const typename _Pair::first_type& operator()(const _Pair& __x) const {
    return __x.first;
  }
};

// 接受一个 pair，返回 pair 的第二个元素
template <class _Pair>
struct _Select2nd : public unary_function<_Pair, typename _Pair::second_type>
{
  const typename _Pair::second_type& operator()(const _Pair& __x) const {
    return __x.second;
  }
};

// 传回第一个参数，忽略第二个参数
template <class _Arg1, class _Arg2>
struct _Project1st : public binary_function<_Arg1, _Arg2, _Arg1> {
  _Arg1 operator()(const _Arg1& __x, const _Arg2&) const { return __x; }
};
// 传回第二个参数，忽略第一个参数
template <class _Arg1, class _Arg2>
struct _Project2nd : public binary_function<_Arg1, _Arg2, _Arg2> {
  _Arg2 operator()(const _Arg1&, const _Arg2& __y) const { return __y; }
};
```
