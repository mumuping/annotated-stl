# Iterator

iterator 主要用于将 container 和 algorithm 分开，彼此独立设计，最后再用 iterator 将它们结合起来。

实际上迭代器就是一种 smart pointer，其最重要的工作就是对 operator* 和 operator-> 进行重载，这一点可以参考 [\<memory>](../SGI-STL%20V3.3/memory) 中的 auto_ptr。

要设计出一个 container 的迭代器，就必须要对此 container 的内部实现细节有所了解（因为要实现 container 元素的迭代操作，只有它自己才知道），因此，每一种 STL container 都提供有其专属的迭代器。

### 迭代器 associated types 和 traits

associated types 指的是与迭代器相关联的一些类型，比如迭代器所指元素的类型、迭代器之间的距离、迭代器所属类型等。traits 指的是从迭代器中取出这些 associated types。下面通过几个问题来具体了解 associated types 和 traits。

最开始，如果在编程中我们想要得到迭代器所指元素的类型，该怎么做？解决办法是采用函数模板的参数推导，如下：
```c++
/* 3 */
template<class I, class T>
void func_impl(I iter, T t){
  T tmp;  // 这里就得到了迭代器所指元素的类型，本例中为 int
  
  // ...
};

/* 2 */
template<class I>
void func(I iter){
  // 为了得到所指元素的类型，需要将 *iter 作为参数继续向下再传递一层
  // 因此 func 的具体实现需要转移到 func_impl 中
  func_impl(iter, *iter); 
  
};

/* 1 */
int main(){
  int i;
  func(&i);
}
```

但是如果我们想在 func 函数处的返回类型也是迭代器所指元素的类型该怎么办呢？这时候参数推导就做不到了，但我们还可以使用内嵌类型，把类型直接嵌入到迭代器 class 中。
```c++
template<class T>
struct MyIter{
  // 直接把元素类型作为迭代器的内嵌类型
  typedef T value_type;
  // ...
};

// func 函数就可以改写为如下
template<class I>
typename I::value_type func(I iter){
  // ...
};

int main(){
  MyIter<int> iter(new int(8));
  cout<<func(iter);
}
```

但是上述办法只对 class type 的迭代器有用，而对一些原生指针（如 int* 等）没有用，且也无法为它们添加内嵌类型，但 STL 中规定，必须接受原生指针作为一种迭代器。因此还需要对上述方法进行改进。

既然原生指针无法实现内嵌，那我们就专门写一个结构体再对 associated types 封装一下，再利用结构体模板偏特化来为原生指针单独写个版本。而这个结构体就是 iterator_traits，它提取出迭代器（无论是 class type 还是原生指针）中的各种 associated types。
```c++
// 针对 class type 的迭代器，即使用该迭代器自身有的 value_type
template<class T>
struct iterator_traits{
  typedef typename T::value_type value_type;
};

// 针对原生指针，使用偏特化，使用值 T
template<class T>
struct iterator_traits<T*>{
  typedef T value_type;
};
```
 
这里需要注意的一点是，如果声明一个 `iterator_traits<const int*>::value_type` ，那么返回的就是一个 `const int`，即声明了一个无法赋值的暂时变量！因此对于 pointer-to-const 的迭代器，我们要将其改为 non-const 类型。
```c++
template<class T>
struct iterator_traits<const T*>{
  typedef T value_type;
};
```

最后，在 iterator_traits 中，定义了五种 associated types，因此，如果我们自己要写一个 iterator，为了保证 iterator_traits 有效，就必须定义这五个 associated types。
```c++
template<class T>
struct iterator_traits{
  typedef typename T::iterator_category      iterator_category;
  typedef typename T::value_type             value_type;
  typedef typename T::difference_type        difference_type;
  typedef typename T::pointer                pointer;
  typedef typename T::reference              reference;
};
```

### 五种 associated types

* value_type：迭代器所指对象的类型。
* difference_type：两个迭代器之间的距离。对于连续空间的容器，可以使用头尾之间的距离这个计算其最大容量。（原生指针偏特化版本是 ptrdiff_t）
* reference_type：引用类型，如返回 T&。
* pointer_type：指针类型，如返回 T*。
* iterator_category：迭代器类型。

其中迭代器类型一共有五种，分别是：

* Input Iterator：只读，支持 operator++
* Output Iterator：只写，支持 operator++
* Forward Iterator：允许“写入型”算法在此种迭代器所形成的区间上进行读写操作，支持 operator++
* Bidirectional Iterator：可以双向移动，支持 operator++ 和 operator--
* Random Access Iterator：随机访问，支持 operator++、operator--、p+n、p[n]、p1<p2 等操作

```c++
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};
```

注意原生指针的迭代器类型被定义为 `typedef random_access_iterator_tag iterator_category`。

下面见一个具体的例子，如 [stl_iterator_base.h](stl_iterator_base.h) 中的 advance 函数。

```c++
// 三个 __advance 重载版本，显然根据输入的迭代器不同，其执行的操作也不同，效率也可能不同
template <class _InputIter, class _Distance>
inline void __advance(_InputIter& __i, _Distance __n, input_iterator_tag) {
  while (__n--) ++__i;
};

template <class _BidirectionalIterator, class _Distance>
inline void __advance(_BidirectionalIterator& __i, _Distance __n, 
                      bidirectional_iterator_tag) {
  __STL_REQUIRES(_BidirectionalIterator, _BidirectionalIterator);
  if (__n >= 0)
    while (__n--) ++__i;
  else
    while (__n++) --__i;
};

template <class _RandomAccessIterator, class _Distance>
inline void __advance(_RandomAccessIterator& __i, _Distance __n, 
                      random_access_iterator_tag) {
  __STL_REQUIRES(_RandomAccessIterator, _RandomAccessIterator);
  __i += __n;
};

// 暴露接口
// 这里有一点需要注意的是函数模板参数是 _InputIterator，这并不代表一定要传递 input_iterator，
// 而是因为 STL 中的一个命名规则：以算法所能接受的最低阶迭代器来为其命名
template <class _InputIterator, class _Distance>
inline void advance(_InputIterator& __i, _Distance __n) {
  __STL_REQUIRES(_InputIterator, _InputIterator);
  __advance(__i, __n, iterator_category(__i));
  // 等价于调用 __advance(__i, __n, iterator_traits<_InputIterator>::iterator_category());
};

// 除了重载作用外，上述方式还可以实现如下效果：若我们没有写 BidirectionalIterator 版本的 __advance()，
// 那么当我们调用 __advance(i, n, bidirectional_iterator_tag) 时，由于继承关系，它会转向调用 InputIterator 版本，
// 因此若 bidirectional iterator 的行为与 input iterator 的行为一样的话，那我们就可以只写 input iterator 即可。
// 同样可以参考 [stl_iterator_base.h](stl_iterator_base.h) 中的 distance 函数。
```

最后一点需要强调的是，若我们自己写一个 iterator，为了实现符合 STL 规范，那我们就必须要包含这五种 associated types。当然，为了方便，在 STL 中，它也为了我们提供了一个基本的 iterator，我们只用继承于他并传递模板参数即可。

```c++
// stl 提供给我们的基本 iterator 模板
template <class _Category, class _Tp, class _Distance = ptrdiff_t,
          class _Pointer = _Tp*, class _Reference = _Tp&>
struct iterator {
  typedef _Category  iterator_category;
  typedef _Tp        value_type;
  typedef _Distance  difference_type;
  typedef _Pointer   pointer;
  typedef _Reference reference;
};

// 然后我们自己写一个 iterator 继承于它
template<class Item>
struct MyIter: public std::iterator<std::input_iterator_tag, Item>{
  // ...
};
```

