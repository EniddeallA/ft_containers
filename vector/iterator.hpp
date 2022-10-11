#pragma once

#include "iterator_traits.hpp"

namespace ft {

    template<typename Iterator>
    struct vector_iterator {
        typedef Iterator                                                    iterator_type;
        typedef typename iterator_traits<iterator_type>::iterator_category  iterator_category;
        typedef typename iterator_traits<iterator_type>::value_type         value_type;
        typedef typename iterator_traits<iterator_type>::difference_type    difference_type;
        typedef typename iterator_traits<iterator_type>::pointer            pointer;
        typedef value_type const *                                          const_pointer;
        typedef typename iterator_traits<iterator_type>::reference          reference;
        typedef value_type const &                                          const_reference;
        pointer it;

        vector_iterator(): it(NULL) {}
        vector_iterator(pointer pIter): it(pIter) {}
        ~vector_iterator() {}

        vector_iterator base() const { return vector_iterator(it); }

        operator vector_iterator<const_pointer> () const 
		{
            return vector_iterator<const_pointer>(it);
        }

        vector_iterator& operator=( value_type const& oIt ) 
		{
            it = &oIt;
            return *this;
        }

        reference operator*() const { return *it; }

        pointer operator->() { return it; }

        reference operator[](size_t val) { return it[val]; }

        vector_iterator &operator++() 
		{
            it++;
            return *this;
        }

        vector_iterator operator++(int) 
		{
            vector_iterator tmp = *this;
            it++;
            return tmp;
        }

        vector_iterator &operator--()
		{
            it--;
            return *this;
        }

        vector_iterator operator--(int)
		{
            vector_iterator tmp = *this;
            it--;
            return tmp;
        }

        vector_iterator& operator+=( int value )
		{
            it += value;
            return *this;
        }

        vector_iterator &operator-=(int value)
		{
            it -= value;
            return *this;
        }

        friend vector_iterator operator+( vector_iterator o, difference_type i )
		{
            return o.it + i;
        }

        friend vector_iterator operator+( difference_type i, vector_iterator o )
		{
            return o.it + i;
        }

        friend vector_iterator operator-( vector_iterator o, difference_type i)
		{
            return (o.it - i);
        }

        vector_iterator operator-(int value) const {
            vector_iterator tmp = *this;
            return tmp -= value;
        }

        difference_type operator-(vector_iterator const &o) const {
            return it - o.it;
        }
    }; // class vector_iterator

    template<typename T, typename U>
    bool operator!=(vector_iterator<T> const& lhs, const vector_iterator<U>& rhs ) {
        return lhs.it != rhs.it;
    }

    template<typename T, typename U>
    bool operator>=(vector_iterator<T> const& lhs, vector_iterator<U> const& rhs ) {
        return lhs.it >= rhs.it;
    }

    template<typename T, typename U>
    bool operator<=( vector_iterator<T> const& lhs, vector_iterator<U> const& rhs ) {
        return lhs.it <= rhs.it;
    }

    template<typename T, typename U>
    bool operator>(vector_iterator<T> const& lhs, vector_iterator<U> const& rhs ) {
        return lhs.it > rhs.it;
    }

    template<typename T, typename U>
    bool operator<( vector_iterator<T> const& lhs, vector_iterator<U> const& rhs ) {
        return lhs.it < rhs.it;
    }

    template<typename T, typename U>
    bool operator==( vector_iterator<T> const& lhs, vector_iterator<U> const& rhs ) {
        return lhs.it == rhs.it;
    }
}