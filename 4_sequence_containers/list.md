#list
##list对于空间的运用有绝对的精准，一点也不浪费；对于任何位置的元素插入或元素移除，list永远是常数时间。
##list的节点
```c++
template<typename T>
struct __list_node{
    typedef void* void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
};
```