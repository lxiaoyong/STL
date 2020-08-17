# deque
## deque是一种双向开口的连续线性空间，可以在头尾两端分别做元素的插入和删除操作。
## deque与vector差异在于：1.deque允许于常数时间内对起头端进行元素的插入或移除；2.deque没有所谓容量的概念，因为它是动态地以分段连续空间组合而成，随时可以增加一段新的空间并链接起来。
## 虽然duque也提供 Random Access Iterator，但它的迭代器并不是普通指针。对deque进行的排序操作，为了最高效率，可将deque先完整复制到vector，将vector排序后，在复制回deque。
## deque 的中控器
### deque 采用一块所谓的map（不是STL的map）作为主控。map是一小块连续空间，其中每个元素(node)都是指针，指向另一段较大的连续线性空间(缓冲区)，缓冲区才是deque的存储空间主体。
```c++
template <typename T,typename Alloc=alloc,size_t BufSiz=0>
class deque{
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef size_t size_type;
    //...
protected:
    typedef pointer * map_pointer;
    map_pointer map;
    size_type map_size;
    //...
};
```
## deque的迭代器
### 
```c++
inline size_t __deque_buf_size(size_t n,size_t sz){
    return n!=0?n:(sz<512?size_t(512/sz):size_t(1));
}

template<typename T,typename Ref,typename Ptr,size_t BufSiz>
struct __deque_iterator{
    typedef __deque_iterator<T,T&,T*,BufSiz> iterator;
    typedef __deque_iterator<T,const T&,const T*,BufSiz> const_iterator;
    static size_t buffer_size(){
        return __deque_buf_size(BufSiz,sizeof(T));
    }

    // 未继承 std::iterator
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T** map_pointer;

    typedef __deque_iterator self;

    T* cur; // 指向缓冲区的现行元素
    T* first;   // 指向缓冲区的头
    T* last;    // 指向缓冲区的尾(含备用空间)
    map_pointer node; // 指向主控区
};
```