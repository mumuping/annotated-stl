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

### set 相关算法 <algorithm>

STL 一共提供了五种与 set 相关的算法：包含 includes、并集 union、交集 intersection、差集 difference、对称差集 symmetric difference（它们都有两种版本，一种是使用的默认 '<'，另一种是使用用户自己提供的 comp（**注意不要擅自改为 <=，可能会原本的答案并不一样**））。

**注意这四种算法所接受的 set 必须是有序区间（sorted range），也就是说，它们可以接受 set 和 multiset，而不能接受 hash_set 和 hash_multiset，当然它们也可以接受 sorted 的 array 等。**

includes：`bool includes(_InputIter1 __first1, _InputIter1 __last1, _InputIter2 __first2, _InputIter2 __last2)`（区间 1 是否含有区间 2 中的所有元素。）

set_union（stable）: 构造 s1 和 s2 的并集。由于 s1 和 s2 内的每个元素都不唯一，因此如果某个值在 s1 出现 n 次，在 s2 出现 m 次，那么该值在输出区间中会出现 max(m,n) 次，其中 n 个来自 s1，其余来自 s2。

set_intersection（stable）：构造 s1 和 s2 的交集。由于 s1 和 s2 内的每个元素都不唯一，因此如果某个值在 s1 出现 n 次，在 s2 出现 m 次，那么该值在输出区间中会出现 min(m,n) 次，且全部来自 s1。

set_difference（stable）：构造 s1 和 s2 的差集（s1 有而 s2 没有的元素）。由于 s1 和 s2 内的每个元素都不唯一，因此如果某个值在 s1 出现 n 次，在 s2 出现 m 次，那么该值在输出区间中会出现 max(n-m,0) 次，且全部来自 s1。

set_symmetric_difference（stable）：构造 s1 和 s2 的对称差集（(s1-s2)∪(s2-s1)）。由于 s1 和 s2 内的每个元素都不唯一，因此如果某个值在 s1 出现 n 次，在 s2 出现 m 次，那么该值在输出区间中会出现 |n-m| 次，如果 n > m，输出区间内的最后 n - m 个元素将由 s1 复制而来，如果 n < m，则输出区间内的最后 m - n 个元素由 s2 复制而来。
