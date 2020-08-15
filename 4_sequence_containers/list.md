# list
## list对于空间的运用有绝对的精准，一点也不浪费；对于任何位置的元素插入或元素移除，list永远是常数时间。
## list的节点
```c++
template<typename T>
struct __list_node{
    typedef void* void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
};
```
## list的迭代器
### list的插入操作和接和操作都不会造成原有的list的迭代器失效。这在vector是不成立的。list的删除操作也只有“指向被删除元素”的迭代器失效，不影响其他迭代器。
```c++
template <typename T,typename Ref,typename Ptr>
struct __list_iterator{
    typedef __list_iterator<T,T&,T*>  iterator;
    typedef __list_iterator<T,Ref,Ptr> self;
    // list 的迭代器是双向的
    typedef bidirectional_iterator_tag iterator_category; 
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef __list_node<T>* link_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    link_type node; // 指向list的节点
    //constructor
    __list_iterator(){}
    __list_iterator(link_type x):node(x){}
    __list_iterator(const iterator& x) :node(x.node){}

    bool operator==(const self& x){return node==x.node;}
    bool operator!= (const self& x) {return node!=x.node;}
    reference operator* () const{return (*node).data;}
    pointer operator-> () const {return &(operator*());}

    // 前置
    self& operator++(){
        node=(link_type)(*node).next;
        return *this;
    }
    //后置
    self operator++(int){
        self temp=*this;
        ++*this;
        return temp;
    }
    // 前置
    self& operator--(){
        node=(link_type)(*node).prev;
        return *this;
    }
    //后置
    self operator--(int){
        self temp=*this;
        --*this;
        return temp;
    }
};
```
## list 的数据结构
### SGI list 是一个环状双向链表，node是空节点,node->next指向首个节点,node->prev指向最后一个节点。
```c++
template<typename T,typename Alloc/*=alloc*/>
class list{
protected:
    typedef __list_node<T> list_node;
public:
    typedef list_node* link_type;
    typedef link_type iterator;
    typedef size_t size_type;
    typedef list_node& reference;
protected:
    link_type node;
    // ...
public:
    // SGI list 是一个环状双向链表，node是空节点,node->next指向首个节点,node->prev指向最后一个节点
    iterator begin(){
        return (link_type)((*node).next);
    }
    iterator end(){
        return node;
    }
    bool empty(){
        return node->next==node;
    }
    size_type size() const{
        size_type result=0;
        distance(begin(),end(),result);
        return result;
    }
    reference front(){
        return *begin();
    }
    reference back(){
        return *(--end());
    }
};
```