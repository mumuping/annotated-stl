# Sequence Containers

根据数据在容器中的排列，可以分为序列式容器（sequence containers）和关联式容器（associative containers）。

序列式容器包括：array、vector、list、deque、queue 等；关联式容器包括：set、map、multiset、multimap、hash_set、hash_table 等。

序列式容器中的元素都可序（ordered），但是未必有序（sorted）。

### vector

vector 与 array 最大的区别在于：array 是静态的，其空间大小一开始就必须决定，一旦配置了就不能改变；而 vector 是动态配置的，其空间大小能够随着新元素的加入自动扩充。

vector 的关键在于对空间大小的管理以及重新配置时数据的移动，简单来说即当空间不够时，vector 需要重新申请一块大的空间（oldsize*2 或者 oldsize+max(oldsize,n)），并将旧空间中的元素移动到新空间中，最后再释放旧空间。

具体分析见 [\<stl_vector.h>](Vector/stl_vector.h)

### list

与 vector 的连续空间不同，list 每插入或者删除一个元素，就配置或释放一个元素空间，且对于任何位置的元素插入或删除，其时间复杂度都是常数。list 本质上是一个**循环双向链表**。

具体分析见 [\<stl_list.h>](List/stl_list.h)

### deque
vector 是单向开口的连续线性空间，而 deque 是双向开口的连续线性空间，即能够在常数时间内对头部和尾部进行插入或删除操作。此外 deque 也没有容量 capacity 的概念，因此也就没有 reserve 功能。这是因为它是动态地以分段连续空间组合而成的，随时可以增加一段新的空间并链接起来。deque 虽然也提供 random-access iterator，但是它的迭代器并不是普通指针，而是更复杂的。因此应该尽可能地使用 vector，而不是 deque。当对 deque 进行排序时，为了最高效率，可以先将 deque 复制到一个 vector 中，然后在 vector 中使用 stl sort 进行排序，最后再复制到 deque 中。

deque 是由一段一段的定量连续空间构成，其最大的任务是在这些分段的定量连续空间上，维护一个整体的连续的假象，并提供随机存取的接口，避开了“重新配置、复制、释放”的结构。deque 中有一块连续的空间，其中每个元素都是一个指针，指向另一段连续的空间，此空间才是真正存放数据的位置。

具体分析见 [\<stl_deque.h>](Deque/stl_deque.h)

### stack

stack 是一种先进后出（first in last out）的数据结构。stack 只有一个出口，它允许在栈顶进行添加、删除、访问元素，但除栈顶元素外，没有任何其他方法可用存取 stack 中的其他元素。**也就是说 stack 不允许有遍历行为，因此也就没有迭代器**。

stack 被归类于容器适配器（container adaptor），也就是说 stack 本身并没有实现容器的功能，而是使用其他已有的容器作为底部结构，通过封装接口，使其符合“先进后出”的特点。在 SGI STL 中，在缺省的情况下，使用的是 deque 作为其底部结构。此外也可以使用其他如 list 等作为底部结构。

具体分析见 [\<stl_stack.h>](Stack/stl_stack.h)

### queue

queue 是一种先进先出（first in first out）的数据结构。除了在头部取出元素、尾部加入元素外，没有任何其他方法可以存取 queue 中的元素。**即 queue 不允许有遍历行为**。

同 stack 一样，queue 也被归类于容器适配器，即 queue 本身没有实现容器的功能，而是使用其他已有的容器作为底部结构，通过封装接口，使其符合“先进先出”的特点。在 SGI STL 中，在缺省情况下，使用的是 deque 作为底部结构。此外也可以使用其他如 list 等作为底部结构。

具体分析见 [\<stl_queue.h>](Queue/stl_queue.h)

### priority queue

priority queue 允许用户以任何次序将任何元素推入容器内，但取出时一定时从优先权最高（也就是数值最高）的元素开始取。这与 binary max heap 的特性一致，因此 binary max heap 也就作为 priority queue 的底层机制。

同 stack 一样，priority queue 也被归类于容器适配器，即 priority queue 本身没有实现容器的功能，而是使用其他已有的容器作为底部结构，通过封装接口，使其符合“优先权最高的元素先出”的特点。在 SGI STL 中，在缺省情况下，使用的是 vector 作为底部结构。但这里要求容器类型为 _RandomAccessContainer 才行，因此 list 是不允许的。

#### heap

首先如果要实现将元素以任意次序推入容器中，然后取出时的元素始终是优先权最高的，可以考虑 list，其插入和删除操作都是常数时间，但是为了正确地找到需要插入的位置，其复杂度是线性的，因此不可取。

binary heap 采用的是一棵**完全二叉树 complete binary tree**，整棵树除了最底层的叶子节点外，都是填满的，且最底层的叶节点从左到右是连续的，中间没有空隙。如果用 array 从上到下、从左到右存储节点（从 array[1] 开始存储，array[0] 用于存储无限大值或无限小值），则位于 array 的 i 的节点，其左子节点位于 2i 处，右子节点位于 2i+1，父节点位于 [i/2] 处。因此可以通过 array 来存储这么一颗完全二叉树。这种方法被成为隐式表述法（implicit representation）。

因此现在就只需要一个 array 和一组 heap 算法（删除、插入、取最大值）就可以实现。但考虑到元素个数是可变的，因此将 array 换为 vector 更合适。

根据元素的排序方式，heap 可以分为最大堆 max-heap 和最小堆 min-heap 。最大堆指每个节点的键值都大于等于其子节点的键值，最小堆相反。因此最大堆在根节点，最小堆在根节点。SGI STL 采用的是最大堆。heap 中所采用的算法细节见源代码，其包括四种操作：push_heap、pop_heap、make_heap、sort_heap。

具体分析见 [\<stl_heap.h>](Priority-Queue&Heap/Heap/stl_heap.h)

### slist

slist 是一个单向链表，与双向链表 list 的主要区别在于：slist 的迭代器属于单向的 forward iterator，后者的迭代器属于双向的 bidirectional iterator。

slist 和 list 都不会由于元素的插入 insert、移除 erase、接合 splice 等操作而导致迭代器（非移除元素）失效。

在 STL 中，对于元素插入的操作，习惯上会定义为将新元素插入到指定位置之前。而这对于 forward iterator 的迭代器容器来说，进行插入或删除操作就必须从头依次开始迭代，直到找到指定位置的前面。因此此类操作效率很低。同样，出于效率考虑，slist 不会提供 push_back() 操作，而只提供 push_front()。因此 slist 的元素次序会和元素插入操作次序相反。

具体分析见 [\<stl_slist.h>](Slist/stl_slist.h)
