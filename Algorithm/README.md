# Algorithm

STL 中的算法包括：排序（sorting）、查找（searching）、排列组合（permutation），以及用于数据移动、复制、删除、比较、组合、运算等算法。

### STL 算法总览

表格中将所有的 STL 算法的名称、用途、文件分布等等，依算法名称的字母顺序列表。

表格中凡是不在 STL 标准规格之列的 SGI 专属算法，都以 * 加以表示。

<table>
<thead><tr><th>算法名称</th><th>算法用途</th><th>质变</th><th>所在文件</th></tr></thead>
<tbody>
<tr><td>accumulate</td><td>元素累计</td><td>否</td><td>&lt;stl_numeric.h&gt;</td></tr>
<tr><td>adjacent_difference</td><td>相邻元素的差额</td><td>是 if in-place</td><td>&lt;stl_numeric.h&gt;</td></tr>
<tr><td>adjacent_find</td><td>查找相邻而重复的元素（或者符合某条件）</td><td>否</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>binary_search</td><td>二分查找</td><td>否</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>copy</td><td>复制</td><td>是 if in-place</td><td>&lt;stl_algobase.h&gt;</td></tr>
<tr><td>copy_backward</td><td>逆向复制</td><td>是 if in-place</td><td>&lt;stl_algobase.h&gt;</td></tr>
<tr><td>copy_n *</td><td>复制 n 个元素</td><td>是 if in-place</td><td>&lt;stl_algobase.h&gt;</td></tr>
<tr><td>count</td><td>计数</td><td>否</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>count_if</td><td>在特定条件下计数</td><td>否</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>equal</td><td>判断两个区间是否相等</td><td>否</td><td>&lt;stl_algobase.h&gt;</td></tr>
<tr><td>equal_range</td><td>在有序区间查找某值</td><td>否</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>fill</td><td>改填元素值</td><td>是</td><td>&lt;stl_algobase.h&gt;</td></tr>
<tr><td>fill_n</td><td>改填元素值 n 次</td><td>是</td><td>&lt;stl_algobase.h&gt;</td></tr>
<tr><td>find</td><td>循环查找</td><td>否</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>find_if</td><td>循环查找符合特定条件者</td><td>否</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>find_end</td><td>查找子序列最后一次出现位置</td><td>否</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>find_first_of</td><td>查找子序列元素首次出现位置</td><td>否</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>foreach</td><td>对区间每个元素施行某操作</td><td>否</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>generate</td><td>以特定操作结果填充区间元素</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>generate_n</td><td>以特定操作结果填充区间 n 个元素</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>includes</td><td>是否涵盖于某序列之中</td><td>否</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>inner_product</td><td>内积</td><td>否</td><td>&lt;stl_numeric.h&gt;</td></tr>
<tr><td>inplace_merge</td><td>合并并就地替换</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>iota *</td><td>在区间填入指定的递增序列</td><td>是</td><td>&lt;stl_numeric.h&gt;</td></tr>
<tr><td>is_heap *</td><td>判断区间是否为一个 heap</td><td>否</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>is_sorted *</td><td>判断区间是否已排序</td><td>否</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>iter_swap</td><td>元素互换</td><td>是</td><td>&lt;stl_algobase.h&gt;</td></tr>
<tr><td>lexicographical_compare</td><td>以字典顺序进行比较</td><td>否</td><td>&lt;stl_numeric.h&gt;</td></tr>
<tr><td>lower_bound</td><td>插入指定元素而不影响排序的最低位置</td><td>否</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>max</td><td>最大值</td><td>否</td><td>&lt;stl_algobase.h&gt;</td></tr>
<tr><td>max_element</td><td>最大值所在位置</td><td>否</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>merge</td><td>合并两个序列</td><td>是 if in-place</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>min</td><td>最小值</td><td>否</td><td>&lt;stl_algobase.h&gt;</td></tr>
<tr><td>min_element</td><td>最小值所在位置</td><td>否</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>mismatch</td><td>找出不匹配点</td><td>否</td><td>&lt;stl_algobase.h&gt;</td></tr>
<tr><td>next_premutation</td><td>获得下一个排列组合</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>nth_element</td><td>重新排列序列第 n 个元素的左右两端</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>partial_sort</td><td>局部排序</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>partial_sort_copy</td><td>局部排序并复制到他处</td><td>是 if in-place</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>partial_sum</td><td>局部求和</td><td>是 if in-place</td><td>&lt;stl_numeric.h&gt;</td></tr>
<tr><td>partition</td><td>分割</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>prev_permutation</td><td>获得前一个排列组合</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>power *</td><td>幂次方，表达式可指定</td><td>否</td><td>&lt;stl_numeric.h&gt;</td></tr>
<tr><td>random_shuffle</td><td>随机重排元素</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>random_sample *</td><td>随机取样</td><td>是 if in-place</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>random_sample_n *</td><td>随机取样</td><td>是 if in-place</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>remove</td><td>删除某类元素</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>remove_copy</td><td>删除某类元素并将结果复制到别处</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>remove_if</td><td>有条件地删除某类元素</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>remove_copy_if</td><td>有条件地删除某类元素并将结果复制到别处</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>replace</td><td>替换某类元素</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>replace_copy</td><td>替换某类元素并将结果复制到别处</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>replace_if</td><td>有条件地替换</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>replace_copy_if</td><td>有条件地替换并将结果复制到别处</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>reverse</td><td>反转元素次序</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>reverse_copy</td><td>反转元素次序并将结果复制到别处</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>rotate</td><td>旋转</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>rotate_copy</td><td>旋转并将结果复制到别处</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>search</td><td>查找某个子序列</td><td>否</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>search_n</td><td>查找连续发生 n 次的子序列</td><td>否</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>set_difference</td><td>差集</td><td>是 if in-place</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>set_intersection</td><td>交集</td><td>是 if in-place</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>set_symmetric_difference</td><td>对称差集</td><td>是 if in-place</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>set_union</td><td>并集</td><td>是 if in-place</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>sort</td><td>排序</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>stable_partition</td><td>分割并保持元素相对次序</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>stable_sort</td><td>排序并保持等值元素相对次序</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>swap</td><td>交换元素</td><td>是</td><td>&lt;stl_algobase.h&gt;</td></tr>
<tr><td>swap_ranges</td><td>交换指定区间</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>transform</td><td>以两个序列为基础交互产生第三个序列</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>unique</td><td>将重复元素折叠使之唯一</td><td>是</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>unique_copy</td><td>将重复元素折叠使之唯一并复制到别处</td><td>是 if in-place</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>upper_bound</td><td>插入指定元素而不影响排序的最高位置</td><td>否</td><td>&lt;stl_algo.h&gt;</td></tr>
<tr><td>make_heap</td><td>制造一个 heap</td><td>是</td><td>&lt;stl_heap.h&gt;</td></tr>
<tr><td>pop_heap</td><td>从 heap 取出一个元素</td><td>是</td><td>&lt;stl_heap.h&gt;</td></tr>
<tr><td>push_heap</td><td>将一个元素推进 heap 内</td><td>是</td><td>&lt;stl_heap.h&gt;</td></tr>
<tr><td>sort_heap</td><td>对 heap 排序</td><td>是</td><td>&lt;stl_heap.h&gt;</td></tr>
</tbody>
</table>

质变算法（mutating algorithms）：会改变操作对象的值。所有的 STL 算法都作用在迭代器 [first,last) 所标示出来的区间上，质变算法会改变迭代器所指元素的内容，如：copy、swap、replace、fill、remove、permutation、partition、random shuffling、sort 等算法。

非质变算法（non-mutating algorithm）：不会改变操作对象的值，如 find、search、count、for_each、equal、mismatch、max、min 等算法。

STL 算法要求区间左闭右开，且能够支持 increment 操作。每一个 STL 算法的声明都会表现出它所需的最低程度的迭代器类型。

质变算法通常提供两个版本：in-place 就地版，就地改变操作对象；另一个 copy 另地版（将操作对象的内容复制一份副本，然后在副本上进行修改，并返回副本）。

```c++
/**
 * -----------------------------------------------------
 * | <stl_numeric.h>                  ---> <numeric>   |
 * | <stl_algo.h> && <stl_algobase.h> ---> <algorithm> |
 * -----------------------------------------------------
 */
```

### 数值算法 <stl_numeric.h>

其中包含的函数有：accumulate、inner_product、partial_sum、adjacent_difference、power、iota

具体分析见 [\<stl_numeric.h>](Numeric/stl_numeric.h)

### 基本算法 <stl_algobase.h>

其中包含的函数有：iter_swap、swap、min、max、copy（如果 copy 的类型是 trivial 类型，如 char int long 等，则调用的是 memmove，如果是 input_iterator 则使用的是 first!=last 进行比较，如果是 random_iterator 则使用的是 distance: n>0 判断，显然 random_iterator 的速度更快）、copy_backward、copy_n（返回的是 pair（拷贝后的源地址和目的地址））、fill、fill_n、mismatch（返回的是 pair（区间 1 和区间 2 第一个不匹配的地方，注意要检查是否到达了迭代器 end））、equal、lexicographical_compare（如果类型是 trivial 类型，则调用 memcmp）、lexicographical_compare_3way（返回 3 值结果，-1 表示第一个区间比第二个区间小，0 表示两个区间相等，1 表示第一个区间大于第二个区间）

<stl_algobase.h> 中定义了基本算法，其他算法定义在 <stl_algo.h> 中。

具体分析见 [\<stl_algobase.h>](./Algobase/stl_algobase.h)

### set 相关算法 <stl_algo.h>

STL 一共提供了五种与 set 相关的算法：包含 includes、并集 union、交集 intersection、差集 difference、对称差集 symmetric difference（它们都有两种版本，一种是使用的默认 '<'，另一种是使用用户自己提供的 comp（**注意不要擅自改为 <=，可能会原本的答案并不一样**））。

**注意这四种算法所接受的 set 必须是有序区间（sorted range），也就是说，它们可以接受 set 和 multiset，而不能接受 hash_set 和 hash_multiset，当然它们也可以接受 sorted 的 array 等。**

- includes：`bool includes(_InputIter1 __first1, _InputIter1 __last1, _InputIter2 __first2, _InputIter2 __last2)`（区间 1 是否含有区间 2 中的所有元素。）

- set_union（stable）: 构造 s1 和 s2 的并集。由于 s1 和 s2 内的每个元素都不唯一，因此如果某个值在 s1 出现 n 次，在 s2 出现 m 次，那么该值在输出区间中会出现 max(m,n) 次，其中 n 个来自 s1，其余来自 s2。

- set_intersection（stable）：构造 s1 和 s2 的交集。由于 s1 和 s2 内的每个元素都不唯一，因此如果某个值在 s1 出现 n 次，在 s2 出现 m 次，那么该值在输出区间中会出现 min(m,n) 次，且全部来自 s1。

- set_difference（stable）：构造 s1 和 s2 的差集（s1 有而 s2 没有的元素）。由于 s1 和 s2 内的每个元素都不唯一，因此如果某个值在 s1 出现 n 次，在 s2 出现 m 次，那么该值在输出区间中会出现 max(n-m,0) 次，且全部来自 s1。

- set_symmetric_difference（stable）：构造 s1 和 s2 的对称差集（(s1-s2)∪(s2-s1)）。由于 s1 和 s2 内的每个元素都不唯一，因此如果某个值在 s1 出现 n 次，在 s2 出现 m 次，那么该值在输出区间中会出现 |n-m| 次，如果 n > m，输出区间内的最后 n - m 个元素将由 s1 复制而来，如果 n < m，则输出区间内的最后 m - n 个元素由 s2 复制而来。

### heap 相关算法

heap 相关算法，如 make_heap push_heap pop_heap sort_heap 被定义在 [\<stl_heap.h>](../Sequence-Containers/Priority-Queue/Heap/stl_heap.h) 文件中，而 <stl_algo.h> 文件又包含了它，因此通过引入 <algorithm> 头文件也能使用 heap 相关算法。

### 其他算法

- adjcent_find：找出第一组满足条件的相邻元素（默认为两元素相等，也可以用户指定）。

- find：找出区间中第一个与指定值相等的元素。

- find_if：找出区间中第一个满足 pred 条件的元素。

- find_end：在区间 1 中查找区间 2 最后一次出现点，如果没有找到区间 2，则返回区间 1 的尾迭代器。

- find_first_of：在区间 1 中查找区间 2 中任一字符最早出现的位置。时间复杂度很高，就是依次拿区间 2 的字符跟区间 1 的当前字符进行比较，判断是否出现（用户可以自己指定函数 bool comp(区间 1 的元素，区间 2 的元素）。

- count：把区间中的所有元素与指定值进行比较，返回与指定值相等的元素个数。count 和 count_if 函数存在两个版本，一个旧版本，计数器由参数提供 `void count(_InputIter __first, _InputIter __last, const _Tp& __value, _Size& __n)`，另一个版本返回 difference_type `typename terator_traits<_InputIter>::difference_type count(_InputIter __first, _InputIter __last, const _Tp& __value) `。

- count_if：将指定操作 pred 实施于区间中的每**一个元素**（也就是说 pred 只接受一个参数，后面介绍如何使用 bind2nd 函数来定义第二个参数），将返回计算结果为 true 的元素个数 `void count_if(_InputIter __first, _InputIter __last, _Predicate __pred, _Size& __n)`。

- for_each：将区间中的每个函数都应用于函数 f。

- generate：将仿函数 gen 的计算结果依次（gen 每次都会被调用）赋值给区间中的所有元素。

- generate：将仿函数 gen 的计算结果依次（gen 每次都会被调用）赋值给 first 开始的 n 个元素。

- max_element：返回最大元素迭代器（用户可指定 comp）。

- min_element：返回最小元素迭代器（用户可指定 comp）。

- merge：将两个 **sorted** 集合合并成一个 sorted 集合（用户可指定 comp）。

- partition（not stable）：区间中的元素重新排序，满足 pred 条件的放在区间前段，被 pred 判定为 false 的元素放在区间后段。

- stable_partition

- remove_copy：将等于 value 的元素从区间中移除，放至 result 中，相当于将不等于 value 的元素拷贝至 result 中，注意原始空间中的元素是没有任何改变的

- remove_copy_if：使用 pred 条件，移除被 pred 判定为 true 的元素，即每个 pred(*first) 不成立的元素会被拷贝到 result

- remove：删除区间中等于 value 的元素。**注意该函数不会改变区间的大小，它只会将不等于 value 的元素放在区间前段（该函数的返回值为区间前段结束位置），区间的后半段是残余的数据**，这是因为它是调用了 remove_copy 函数，将目的地址设置为第一个等于 value 的地址。

- remove_if：移除被 pred 判定为 true 的元素。注意该函数与 remove 一样，不会改变区间的大小，前半段是判定为 false 的元素，后半段是残余的数据。

- replace：将区间中的旧值元素用新值替换。

- replace_copy：将区间中的旧值元素用新值替换，结果存储在目标域中。

- replace_if：将 pred 为真的元素用新值替换。

- replace_copy_if：将区间中的 pred 为 true 的元素用新值替换，结果存储在目标域中。

- reverse：将序列中的元素颠倒。

- reserve：将区间中的元素颠倒，结果放入 result 中。

- rotate：将 [first, midlle) 和 [middle, last) 中的元素互换，返回前段区间结束的位置。

- rotate_copy：另地交换两段区间，返回整个区间结束位置。

- search：在区间 1 中搜索区间 2 首次出现的位置（另一个版本用户可提供 pred 仿函数）。

- search_n：搜索 count 个 value 第一次在区间中出现的位置（另一个版本用户可提供 pred 仿函数，如使用 less<int>() 表示查找第一个连续 count 个小于 value 的子序列的起始位置）。

- swap_ranges：交换长度相等的两个区间的元素。

- transform：第一个版本：将区间中的每个元素都应用 opr（只有一个参数）操作，并将结果赋值到目标域中，跟 for_each 很像，不过 for_each 并不将结果赋值到目标域中。第二个版本：将区间 1 和区间 2 的每个元素同时作用于 op（两个参数，一个是区间 1 的，另一个是区间 2 的）操作，并将结果赋值到目标域中

- unique_copy：将区间 1 中的元素复制到目标域中，如果区间 1 中相邻元素重复，那么只会复制第一个元素（用户可提供 pred 仿函数，pred(前一个元素，后一个元素)）。

- unique：移除相邻重复的元素，当区间中遇到相邻有重复的元素时，只保留第一个元素。注意该函数并不改变容器大小，也就是说，存在残余数据（与 remove 函数一样）。该函数返回移除相邻重复元素后的尾迭代器。如果用户想要删除所有重复的元素，应该现排序，再调用该函数（用户可提供 pred 仿函数）。

- lower_bound：返回一个迭代器，指向第一个不小于 value 的元素（用户可指定 comp 仿函数 comp(*middle, val) 默认是 '<'，可以这样理解：返回 [first,last) 中最远的迭代器 i，使 [first, i) 中的每个迭代器 j 都满足 “comp(\*j,val) 为真）。

- upper_bound：返回一个迭代器，指向第一个大于 value 的元素（用户可指定 comp 仿函数 comp(val, *middle) 默认是 '<',可以这样理解：返回 [first,last) 中最远的迭代器 i，使 [first, i) 中的每个迭代器 j 都满足 “comp(val,\*j) 不为真）。

- binary_search：检查 value 是否存在序列中，其实就是调用 lower_bound（用户可指定仿函数）。

- equal_range：查找等于 value 的子区间（用户可指定仿函数）。

- next_permutation：获取 [first, last) 序列的下一个排列组合，如果没有下一个，则返回 false。注意该函数是根据 less-than 做字典序排序的，如 abc -> acb -> bac -> bca -> cab -> cba。因此如果想要全部的排列组合，则要先对区间进行**排序**（用户可指定 comp 函数）。

- prev_permutation：与 next_permutation 相反，找到前一个排序组合（用户可指定 comp 仿函数）。

- random_shuffle：将 [first, last) 中的元素重新排列，该排列组合是从 n! 个总的排列组合中均匀随机选取的。该函数会利用到随机数生成器（默认是 lrand48 或者 c 标准库 rand，当然用户也可以指定，注意若用户指定随机数生成器，那么 random_shuffle 是引用传递该生成器的，这是因为随机数生成器有一个重要特性：它拥有局部状态（local state），每次被调用时它的内部状态都会改变，从而保证生成的数足够随机。

- partial_sort：将 [first, last) 中的 middle-first 个最小元素以递增的方式放在 [first, middle) 中，其余元素放在后面，并不保证之间的顺序，用户可指定 comp 仿函数。（该函数其实是利用了**最大堆排序**，并没有对整个序列排序。迭代器类型必须为 random access iterator）

- partial_sort_copy：与上述函数逻辑大致相同，只是将结果拷贝到 [result_first, result_last) 中，用户可指定 comp 函数。

- 下面开始着重介绍 sort 算法：
  - 首先需要注意的一点是 sort 算法接受两个 **random access iterator**。在 STL 中所有关联容器都拥有自动排序功能（底层容器采用 rb-tree 的），不需要用到该算法，而序列式容器中的 stack、queue、priority_queue 由于特别的出入口，不允许用户对其进行排序，剩下的 vector、deque 是 random access iterator，而 list、slist 迭代器属于 forward iterator，不能应用于 sort 算法，而要使用它们自己的成员函数 sort。
  - 在 STL 中的 sort 算法，数据量大时会采用 quick sort，分段递归排序，而分段后的数据量小于某个阈值（具体多少无定论，实际的最佳值因设备而异，在此版本的 STL 中设定的是 16 个元素，即若 [first,last) 中的元素个数大于 16 个，则允许进行 partition，否则认为元素小于16个的子序列已经有相当程度的排序了，因此将调用插入排序），为避免 quick sort 递归调用所带来的过大额外负荷（overhead），就改用 insertion sort，如果递归层次过深，还会改用 heap sort。
  - insertion sort：插入排序
  - quick sort：快速排序（**由于快速排序的效率很大程度上依赖于 pivot 点的随机性，因此在快速排序中最稳当的方式是取整个序列的头、中间、尾三个位置的元素，以其中间值（median）作为 pivot。Daivd R.Musser 在 1996 年提出了一种混合式排序算法：Introspective Sorting，即 IntroSort，其行为在大部分情况下几乎与三点中值完全相同。但当 partition 行为有恶化为二次行为的倾向时（其实就是限制递归调用的层数），能够自我侦测，转而改用 heap sort，使其效率在 O(nlogn)。这又比一开始使用 heap sort 又好**）
  - final insertion sort：当某个大小下的序列处于“几近排序但尚未完成”状态时，一般认为插入排序的效果比较好。因此最后会再以一次插入排序将这些“几近排序但尚未完成”的子序列做一次完整的排序。
  - stable_sort：基于**归并排序**，这里不多介绍，具体可以看源文件，很好理解。

- inplace_merge（stable）：如果两个连接在一起的序列 [first, middle) 和 [middle, last) 都已排序，那么该函数可以将它们合并成一个最终有序的序列。

- nth_element：该函数会重新排列 [first, last)，使迭代器 nth 所指的元素，与整个 [first, last) 完整排序后，同一位置的元素同值，并保证 [nth, last) 内没有任何一个元素不大于 [first, nth) 内的元素。

- merge_sort：归并排序（尽管时间复杂度是 O(nlogn)，但需要额外的存储空间，以及数据复制也需要耗时，因此效率比不上快速排序）。
