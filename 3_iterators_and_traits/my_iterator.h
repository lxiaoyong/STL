//
// Created  on 2020/8/14.
//

#include <cstddef>  // ptrdiff_t

#ifndef STUDY_STL_MY_ITERATOR_H
#define STUDY_STL_MY_ITERATOR_H

#endif //STUDY_STL_MY_ITERATOR_H
// 节选自 SGI STL <stl_iterator.h>
struct input_iterator_tag{};
struct output_iterator_tag{};
struct forward_iterator_tag:public input_iterator_tag{};
struct bidirectional_iterator_tag: public forward_iterator_tag{};
struct random_access_iterator_tag: public bidirectional_iterator_tag{};

template <typename Category,typename T,typename Distance = ptrdiff_t,typename Pointer=T*,
        typename Reference = T&>
struct iterator{
    typedef Category iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
};

// traits
template<typename Iterator>
struct iterator_traits{
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
};

// 针对原生指针而设计的 traits 偏特化版
template<typename T>
struct iterator_traits<T*>{
    // 原生指针是 random_access_iterator_tag 型
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
};

// 针对原生的pointer-to-const 而设计的 traits 偏特化版
template<typename T>
struct iterator_traits<const T*>{
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
};

template<typename Iterator>
inline typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&){
    typedef typename iterator_traits<Iterator>::iterator_category category;
    return category (); // 返回 category 的一个对象
}

template<typename Iterator>
inline typename iterator_traits<Iterator>::difference_type
distance_type (const Iterator&){
    return static_cast<typename iterator_traits<Iterator>::difference_type* >(0);
}

template<typename Iterator>
inline typename iterator_traits<Iterator>::value_type
value_type(const Iterator&){
    return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

//distance and advance