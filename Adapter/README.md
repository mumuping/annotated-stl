# 适配器 Adapter

> Adapter：将一个 class 的接口转换为另一个 class 的接口，使原本因接口不兼容而不能合作的 classes 可以一起运作。

适配器根据改变接口所属的类型可以分为：仿函数适配器 functor adapter、容器适配器 container adapter、迭代器适配器 iterator adapter。

## 1. container adapter

包括 stack 和 queue，它们是对 deque 接口的封装。具体见 stack、queue 实现。

## 2. iterator adapter

包括 insert iterator、reverse iterator、iostream iterator 等。具体分析见 [\<stl_iterator.h>](Iterator-Adapter/stl_iterator.h)
  
### 2.1 insert iterator

可以将一般迭代器的赋值操作转变为插入操作，包括在尾部插入的 back_insert_iterator、在头部插入的 front_insert_iterator、以及可以从任意位置执行插入操作的 insert_iterator。注意该迭代器类型被定义为 output_iterator_tag，调用 ++ -- * 操作，只会返回它本身，它只会将 operator= 重载调用 insert、push_front、push_back 等操作。

```cpp
back_insert_iterator<Container>(x);  // 可以用函数 back_inserter(Container& x) 产生
front_insert_iterator<Container>(x); // 可以用函数 front_inserter(Container& x) 产生
insert_iterator<Container>(x, Container::iterator(i)); // 可以用函数 inserter(Container& x, Iterator i) 产生
```

### 2.2 reverse iterator

可以将一般迭代器前进的方向逆转，使原本应该前进的 operator++ 变成后退操作，使原本应该后退的 operator-- 变成前进操作。

### 2.3 iostream iterator

可以将迭代器绑定到某个 iostream 对象上，绑定到 istream 对象（如 std::cin），称为 istream_iterator；绑定到 ostream 对象（如 std::cout），称为 ostream_iterator。

对于 istream_iterator，其实就是在内部维护一个 istream member，对这个迭代器做 **operator++** 操作，会被引导调用迭代器内部的 istream member 的输入操作 operator>>。这个迭代器不允许做 operator-- 操作。

对于 ostream_iterator，其实就是在内部维护一个 ostream member，对这个迭代器做 **operator=** 操作，会被引导调用迭代器内部的 ostream member 的输出操作 operator<<。operator ++ 和 operator * 都将返回自身。

对于调用 isteam_iterator 带参构造函数时，一定要注意它会一直等待输入。

```cpp
  // 该构造函数会调用 read 操作，第一次从输入流读取值，若输入流没有值，则会等待输入
  // 因此，只要确实是要读取输入时，才定义该对象，否则会陷入等待
  // 比如： istream_iterator<int> a(cin); cout<<"please input: "; 在第一句时就会导致等待，根本不会待第二句执行才开始等待
  istream_iterator(istream_type& __s) : _M_stream(&__s) { _M_read(); }
```

```cpp
istream_iterator<int> inite(cin), eos;  // 默认构造函数产生的 eos 用于判断输入流是否结束
// 注意这里会一直等待输入流有元素
// 然后才会执行 copy
copy(inite, eos, inserter(id, id.begin())); // 将输入流中的元素插入到 id 的头部
```

```cpp
ostream_iterator<int> outite(cout, " ");
copy(id.begin(), id.end(), outite);
```

## 3. functor adapter

对仿函数进行适配操作，包括系结 bind、否定 negate、组合 compose、以及对一般函数或成员函数的修饰。定义于 \<stl_function.h> 中。
