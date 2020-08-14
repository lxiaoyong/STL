//
// Created  on 2020/8/14.
//
#include "../3_iterators_and_traits/my_iterator.h"

#ifndef STUDY_STL_MY_LIST_H
#define STUDY_STL_MY_LIST_H

#endif //STUDY_STL_MY_LIST_H
template<typename T>
struct __list_node{
    typedef void* void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
};

template <typename T,typename Ref,typename Ptr>
struct __list_iterator{
    typedef __list_iterator<T,T&,T*>  iterator;
    typedef __list_iterator<T,Ref,Ptr> self;

    typedef bidirectional_iterator_tag iterator_category; // list 的迭代器是双向的
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
    //__list_iterator(const iterator& x) :node(x.node){}

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