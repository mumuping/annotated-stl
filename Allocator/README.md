# Allocator

allocator 主要用于给 container 提供数据存取所需的空间。

STL 规定 allocator 定义于 \<memory> 中，\<memory> 主要包含三个头文件：<stl_construct.h>（定义`construct()`和`destroy()`）、<stl_alloc.h>（两层配置器 alloc）、<stl_uninitialized.h>（定义了一些全局函数，用于填充或复制大块内存）

* <stl_construct.h> 中定义了 `construct()` 和 `destroy()`，主要用于在已经分配好的空间中调用对象的构造函数或析构函数，具体分析见 [stl_construct.h](stl_construct.h)。
* <stl_alloc.h> 中主要完成所需空间的配置和释放，它包含了两层的配置器，第一层配置器是当配置区块大小超过 128bytes 时直接使用 `malloc()` 和 `free()` ，第二级配置器则视情况采用不同的策略，其主要的思想是设计一个内存池用于快速地实现内存分配和回收，同时也能很好地管理内存碎片的问题。具体分析见 [stl_alloc.h](stl_alloc.h)
* <stl_uninitialized.h> 中定义了内存基本处理工具，包括 `uninitialized_copy()`，`uninitialized_fill()` 和 `uninitialized_fill_n()` 等，分别对应了 `copy()`，`fill()` 和 `fill_n()` 等。具体分析见 [stl_uninitialized.h](stl_uninitialized.h)。

各文件的函数/类关系图见下：

![stl_construct](Structure-Diagram/stl_construct.h.jpg)

---

![stl_alloc](Structure-Diagram/stl_alloc.h.jpg)

---

![stl_uninitialized](Structure-Diagram/stl_uninitialized.h.jpg)
