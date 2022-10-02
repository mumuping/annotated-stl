# Associative Containers

标准的关联式容器包括：set、map 两大类，以及相应的衍生体 multiset（多建集合）、multimap（多键映射表）。这些容器都是以**红黑树 RB-tree** 实现的。红黑树本身就是一个容器，但并不对外提供接口使用。

此外 SGI STL 还提供了一个不在标准规格中的关联式容器 **hash table（散列表）**，以及以此为底层容器的 hash_set、hash_map、hash_multiset、hash_multimap。

```
-----------------------------------------
| array             | RB-tree           |
| vector            |   set             |
|    heap           |   map             |
|        priority   |   multiset        |
| list              |   multimap        |
| slist             | hashtable         |
| deque             |   hash_set        |
|    stack          |   hash_map        |
|    queue          |   hash_multiset   |
|                   |   hash_multimap   |
-----------------------------------------
```

关联式容器以键值对对数据进行管理，其会按照其键值大小，以某种特定规则将这个元素放置于适当的位置。关联式容器没有所谓的头尾（只有最大元素和最小元素），所以不会有 push_back、push_front、begin、end 等操作。

关联式容器一般使用的是平衡二叉树 balanced binary tree，以便获得更好的搜索效率。平衡二叉树一般包括：AVL-tree、RB-tree、AA-tree 等，而 STL 中广泛使用的是 RB-tree。

### tree

相关术语：路径长度、深度、高度、节点大小...

**二叉树**：编译器表达式树 expression tree、哈夫曼树...

**二叉树搜索树 binary search tree**：可提供对数时间的元素插入和访问。其放置规则是：**任何节点的键值一定大于其左子树中的每一个节点的键值，而小于其右子树中的每一个节点的键值**。因此其最小值是一直往左走，直到尽头，最大值是一直往右走，直到尽头。插入元素时，可以从根节点开始，遇到键值较大的就往左，遇到键值较小的就往右，一直到尾端，即为插入点。删除元素时，如果目标节点只有一个子节点，则把子节点连接到父节点，如果有两个子节点，则从右节点开始，一直向左走到底，找到最小的节点，用于取代目标节点。而**堆**与之不同，binary heap 是一棵完全二叉树，除了最底层的叶节点外，都是填满的，且最底层的叶节点从左到右是连续的，无空隙。heap 满足节点的值是大于等于（或小于等于）子节点的值，左右子节点是没有大小比较的。因此它总是用于取出最大（或最小）元素。也就是说 heap 要比二叉搜索树的约束更少，二叉搜索树是 heap 的一种特化。

**平衡二叉搜索树 balanced binary search tree**：当二叉搜索树由于进行了某些插入或删除操作而导致树不平衡时，会造成搜寻效率降低。树形平衡没有一个绝对的标准，其大致意思是：没有任何一个节点的过深。不同的平衡条件会导致不同的效率表现，以及不同的实现复杂度，如 AVL-tree、RB-tree、AA-tree 等。由于需要对树进行平衡，因此插入或删除节点会导致平均时间比较长，但能够避免树极度不平衡的情况。

**AVL-tree（Adelson-Velskii-Landis tree）**：AVL 树在平衡二叉树下要求任何节点的左右子树高度相差最多为1，因此其能够保证整棵树的深度为 O(logN)。对于插入操作，首先将元素按照二叉搜索树的规则将元素插入到相应的叶节点，再找到最深的、不满足 AVL 要求的节点 X，然后根据情况选择“单旋操作（左左：插入点位于 X 的左子节点的左子树、右右：插入点位于 X 的右子节点的右子树）”还是“双旋操作（左右：插入点位于 X 的左子节点的右子树、右左：插入点位于 X 的右子节点的左子树）”

单旋操作、双旋转

### RB-tree

RB-tree 在平衡二叉树的情况下要求：（1）每个节点不是红色就是黑色；（2）根节点是黑色；（3）如果一个节点是红色，那么它的子节点就必须是黑色；（4）从任意节点到底部（树的底端）的任何路径，所含有的黑色节点个数是相同的。

根据规则4，新增节点必须是红色的；根据规则3，新增节点的父节点是黑色的。当新增节点按照搜索二叉树的规则插入后，如果不满足上述条件，就要进行旋转调整（旋转调整可能会导致 RB 树并不如 AVL 树平衡，即高度相差1以上，但不影响，因为 RB 树的平衡性是要比 AVL 树弱。经验表明，RB 树的平均搜索效率和 AVL 树几乎相等）。

插入节点：根据插入的位置以及外围节点的颜色，可以分为四种情况。详情见《STL 源码剖析》 209 页。

相关操作具体分析见 [\<stl_tree.h>](./Base-RB-tree/stl_tree.h)

### set

set 中所有元素会根据元素的键值自动排序，set 元素的 key 就是 value，value 就是 key，set 不允许两个元素有相同的键值，其使用的是 RB-tree 的 insert_unique 函数，而 multi_set 使用的是 insert_equal 函数。

set 的迭代器类型为 const iterator，因此不能通过它改变 set 的元素值。即 set 不允许改变 set 的元素值。与 list 一样，set 在进行元素删除或插入时，操作之前的所有迭代器（除了被删除的），在操作完成之后也是有效的。

STL 为 set/multiset 提供了一些相关算法，包括交 set_intersection、并 set_union、差 set_difference、对称差 set_symmetric_differential。

set 以 RB-tree 为底层机制，只是将 RB-tree 提供的各种接口进行了封装。

具体分析见 [\<stl_set.h>](./Set/stl_set.h)

### map

map 中所有元素会根据元素的键值自动排序，map 中的所有元素都是 pair 类型，同时拥有 key 和 value，pair 的第一个元素为 key，第二个元素为 value。pair 定义在 [\<stl_pair>](Map/Pair/stl_pair.h) 中。

map 以 rb-tree 为底层机制，但由于 rb-tree 中的元素都是以 key 为排列依据，因此 map 的迭代器不允许更改 key 的值，但允许更改 value 的值。几乎所有的 map 操作都是对 rb-tree 的操作的封装。

map 不允许两个元素有相同的键值，其使用的是 RB-tree 的 insert_unique 函数，而 multi_map 使用的是 insert_equal 函数。

map 与 list 一样，当对元素进行添加或删除后，其迭代器仍然是有效的（除被删除元素的迭代器）。

具体分析见 [\<stl_map.h>](./Map/stl_map.h)

### multiset

multiset 的特性以及用法与 set 完全相同，唯一的差别在于 multiset 允许键值重复，它采用了 RB-tree 中的 insert_equal() 函数。

具体分析见 [\<stl_multiset.h>](./Set/stl_multiset.h)

### multimap

multimap 的特性以及用法与 map 完全相同，唯一的差别在于 multimap 允许键值重复，它采用了 RB-tree 中的 insert_equal() 函数。

具体分析见 [\<stl_multimap.h>](./Map/stl_multimap.h)

### hashtable

二叉搜索树具有对数平均时间，但这样的表现构造在一个假设上：输入数据有足够的随机性。但使用散列表 hash table，可以在插入、删除、搜寻等操作上也具有常数平均时间。而且这种表现不依赖于数据的随机性。散列函数会将元素映射到 array 某个位置，但这样做会产生碰撞问题，而解决碰撞问题常用的方法有：线性探测、二次探测、开链等。

线性探测：如果 hash function 计算出来的位置上的元素值与搜寻的目标不符，就循序往下一一寻找，直到找到符合的，或直到遇到空格元素。而对于元素的删除，则采用惰性删除，只标记删除符号，实际删除操作则待到表格重新整理 rehashing 时再进行。这是因为 hash table 中的每个元素不仅表述它自己，也关系到其他元素的排列。使用线性探测容易造成主集团 primary clustering 现象，即插入成本的成长幅度远高于负载系数的成长幅度。

二次探测：二次探测主要解决主集团的问题，其方法是如果 hash function 计算出来的位置 H 已经被使用了，那么就依序尝试 H+1^2、H+2^2、H+3^2...，而不是线性探测那样 H+1、H+2...。如果我们保证表格的大小为质数，且永远保存负载系数在 0.5 以下（超过 0.5 进行 rehashing），那么就可以确定每插入一个新元素所需要的探测次数不多于 2。对于扩充 array，首先需要找到下一个足够大（大约两倍）的质数，然后再进行 rehashing。二次探测可以消除主集团，但却可能造成次集团（secondary clustering），即两个元素经过 hashing function 计算出来的位置若相同，则插入时所探测的位置也相同。

开链（separate chaining）：在每一个表格元素中维护一个 list，然后 hash function 将为我们分配某一个 list，然后我们在这个 list 中执行元素的插入、删除、搜寻等操作。**SGI STL 的 hash table 便采用这种方法**。

在 SGI STL 中将 hash table 中的元素称为桶 bucket，而桶指向一个 list。但 bucket 所维护的 linked list 并不是采用 STL 的 list 或者 slist，而是自行维护的 hash table node。而 bucket 聚合体，则是用 vector 完成的。

具体分析见 [\<stl_hashtabel.h>](./Base-Hashtable/stl_hashtable.h)

### hash_set

hash_set 以 hashtable 为底层机制，几乎所有的 hash_set 操作都只是转调用 hashtable 的操作。

set 和 hash_set 都能够快速找到元素，但由于 set 采用了 rb-tree，而 hash_set 采用了 hashtable，因此 set 具有自动排序的功能，而 hash_set 没有。

注意 hashtable 无法处理的类型（除非用户自己编写一个 hash function），hash_set 也无法处理。

具体分析见 [\<stl_hash_set](./Hash-Set/stl_hash_set.h)

### hash_multiset

hash_multiset 几乎与 hash_set 完全一致，最大的差别在于 hash_set 使用了 insert_unique，而 hash_multiset 使用了 insert_equal。因此 hash_set 不允许键值相同的元素插入，而 hash_multiset 允许键值相同的元素插入。

具体分析见 [\<stl_hash_set](./Hash-Set/stl_hash_set.h)

### hash_map

hash_map 以 hashtable 为底层机制，几乎所有的 hash_map 操作都只是转调用 hashtable 的操作。

map 和 hash_map 都能够快速找到元素，但由于 map 采用了 rb-tree，而 hash_map 采用了 hashtable，因此 map 具有自动排序的功能，而 hash_map 没有。

注意 hashtable 无法处理的类型（除非用户自己编写一个 hash function），hash_map 也无法处理。

具体分析见 [\<stl_hash_map](./Hash_Map/stl_hash_map.h)

### hash_multimap

hash_multimap 几乎与 hash_map 完全一致，最大的差别在于 hash_map 使用了 insert_unique，而 hash_multimap 使用了 insert_equal。因此 hash_map 不允许键值相同的元素插入，而 hash_multimap 允许键值相同的元素插入。

具体分析见 [\<stl_hash_map](./Hash_Map/stl_hash_map.h)
