#pragma once

#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "is_integral.hpp"
#include "enable_if.hpp"
#include <algorithm>
#include <iterator>

namespace ft
{
   template<
        typename T,
        typename Allocator = std::allocator<T>
    >
    class vector {
		public:
			typedef T                                                       value_type;
			typedef std::size_t                                             size_type;
			typedef std::ptrdiff_t                                          difference_type;
			typedef Allocator                                               allocator_type;
			typedef typename allocator_type::reference                      reference;
			typedef typename allocator_type::const_reference                const_reference;
			typedef typename allocator_type::pointer                        pointer;
			typedef typename allocator_type::const_pointer                  const_pointer;
			typedef typename ft::vector_iterator<pointer>                   iterator;
			typedef typename ft::vector_iterator<const_pointer>             const_iterator;
			typedef typename ft::reverse_iterator<iterator>                 reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>           const_reverse_iterator;

		private:
			allocator_type  m_alloc;
			pointer         m_valptr;
			size_type       m_size;
			size_type       m_capacity;

			void clean() {
				clear();
				if (m_capacity)
					m_alloc.deallocate(m_valptr, m_capacity);
			}

			template<typename InputIt>
			void push_iter(InputIt first, InputIt last ) 
			{
				while (first != last)
					push_back(*first++);
			}

			void push_val(size_type n, value_type const& val = value_type() ) 
			{
				for (size_type i = 0; i < n; i++)
					push_back(val); 
			}

			void copyVector(vector const& other ) 
			{
				m_valptr = other.m_valptr;
				m_alloc = other.m_alloc;
				m_size = other.m_size;
				m_capacity = other.m_capacity;
			}

			void resetVector() 
			{
				m_valptr = NULL;
				m_size = 0;
				m_capacity = 0;
			}

		public:
			explicit vector(allocator_type const &alloc = allocator_type())
			{
				m_alloc = alloc;
				m_size = 0;
				m_capacity = 0;
				m_valptr = NULL;
			}

			explicit vector(size_type n, value_type const &val = value_type(), 
				allocator_type const &alloc = allocator_type()) 
			{
				m_alloc = alloc;
				m_size = n;
				m_capacity = n;
				m_valptr = m_alloc.allocate(n);
				for (size_type i = 0; i < m_size; i++) {
					m_alloc.construct(&m_valptr[i], val);
				}
			}

			template<typename InputIt>
			vector (InputIt first, InputIt last, allocator_type const &alloc = allocator_type(),
					typename ft::enable_if< !is_integral<InputIt>::value, InputIt>::type* = NULL)
			{
				m_size = 0;
				m_capacity = 0;
				m_valptr = NULL;
				m_alloc = alloc;
				reserve(std::distance(first, last));
				push_iter(first, last);
			}

			vector(vector const &copy )
			{
				m_size = 0;
				m_capacity = copy.m_capacity;
				m_valptr = m_alloc.allocate(m_capacity);
				push_iter(copy.begin(), copy.end());
			}

			vector &operator=(vector const &rhs )
			{
				clear();
				reserve(rhs.m_size);
				push_iter(rhs.begin(), rhs.end());
				return *this;
			}

			~vector() { clean(); }

			void push_back(const_reference val ) 
			{
			if (m_size >= m_capacity)
				reserve(!(m_capacity * 2) ? 1 : m_capacity * 2 );
			m_alloc.construct(m_valptr + m_size++, val);
			}

			void pop_back() 
			{
				if (m_size && m_capacity)
					m_alloc.destroy(&m_valptr[--m_size]);
			}

			void resize(size_type n, value_type val = value_type())
			{
				if (n > m_capacity ) 
				{
					size_type i = m_size - 1;
					if (n > (m_capacity * 2) )
						reserve(n);
					else
						reserve(m_capacity * 2);
					while (++i < n)
						push_back(val);
				} 
				else if (n < m_size )
				{
					size_type i = n;
					while (i < m_size)
						m_alloc.destroy(m_valptr + i++);
					m_size = n;
				} 
				else if (n > m_size )
				{
					size_type i = m_size - 1;
					while (++i < n)
						push_back(val);
				}
			}

			void reserve(size_type n )
			{
				if (n > max_size())
					throw std::length_error("ft::vector: new capacity exceeds ram max length");
				else if (n > m_capacity)
				{
					pointer newValptr;
					newValptr = m_alloc.allocate(n);
					for (size_type i = 0; i < m_size; i++) {
						m_alloc.construct(newValptr + i, m_valptr[i]);
						m_alloc.destroy(m_valptr + i);
					}
					if (m_capacity)
						m_alloc.deallocate(m_valptr, m_capacity);
					m_valptr = newValptr;
					m_capacity = n;
				}
			}

			void assign(size_type n, const_reference val )
			{
				if (n > m_capacity)
					reserve(n);
				for (size_type i = 0; i < m_size; i++)
					m_alloc.destroy(&m_valptr[i]);
				for (size_type i = 0; i < n; i++)
					m_alloc.construct(&m_valptr[i], val);
				m_size = n;
			}

			template <class InputIt>
			void assign (InputIt first, InputIt last,
					typename ft::enable_if< !is_integral<InputIt>::value, InputIt >::type* = NULL) 
			{
				clear();
				reserve(std::distance(first, last));
				push_iter(first, last);
			}

			iterator insert(iterator position, value_type const& val )
			{
				difference_type start = position - begin();
				size_type element_to_move = end() - position;
				vector tmp;
				tmp.assign(position, end());
				if ((m_size + 1) > m_capacity )
					reserve(m_size * 2);
				m_size = start;
				push_val(1, val);
				for (size_type i = 0; i < element_to_move; i++)
					push_back(tmp[i]);
				return begin() + start;
			}
		
			void insert(iterator position, size_type n, value_type const& val)
			{
				difference_type start = position - begin();
				size_type element_to_move = end() - position;
				vector tmp;
				tmp.assign(position, end());
				if ((n + m_capacity) > (m_capacity * 2) )
					reserve(m_size + n);
				else if (!m_size)
					reserve(n);
				else if (n > m_capacity)
					reserve(n * 2);
				m_size = start;
				push_val(n, val);
				for (size_type i = 0; i < element_to_move; i++)
					push_back(tmp[i]);
			}

			template<typename InputIt>
			void insert(iterator position, InputIt first, InputIt last,
					typename ft::enable_if<!is_integral<InputIt>::value, InputIt >::type* = NULL)
			{
				difference_type pos = position - begin();
				size_type element_to_move = end() - position;
				vector tmp;
				tmp.assign(position, end());
				difference_type n = std::distance(first, last);
				if ((n + m_capacity) > (m_capacity * 2))
					reserve(m_size + n);
				else if (!m_size)
					reserve(n);
				else if ((size_type)n > m_capacity )
					reserve(n * 2);
				m_size = pos;
				push_iter(first, last);
				for (size_type i = 0; i < element_to_move; i++)
					push_back(tmp[i]);
			}

			void swap(vector& src )
			{
				vector tmp;

				tmp.copyVector(*this);
				copyVector(src);
				src.copyVector(tmp);

				tmp.resetVector();
			}

			void clear()
			{
				for (size_type i = 0; i < m_size; i++)
					m_alloc.destroy(m_valptr + i);
				m_size = 0;
			}

			iterator erase(iterator position )
			{
				difference_type pos = position - begin();
				m_alloc.destroy(m_valptr + pos);

				size_type element_to_move = end() - position - 1;

				m_size = pos;
				for(size_type i = 0; i < element_to_move; i++)
					push_back(m_valptr[i+ pos + 1]);
				return position;
			}

			iterator erase(iterator first, iterator last )
			{
				difference_type start_pos = first - begin();
				difference_type last_pos = last - begin();

				for (int i = start_pos; i < last_pos; i++)
					m_alloc.destroy(m_valptr + i);
				size_type element_to_move = end() - last;
				m_size = start_pos;
				for (size_type i = 0; i < element_to_move; i++)
					push_back(m_valptr[i + last_pos]);
				return first;
			}

			size_type max_size() const { return m_alloc.max_size(); };

			size_type size() const { return m_size; }

			size_type capacity() const { return m_capacity; }

			bool empty() const { return m_size == 0; }

			allocator_type get_allocator() const { return m_alloc; }

			reference operator[](size_type n) { return m_valptr[n]; }

			const_reference operator[](size_type n ) const { return m_valptr[n]; }

			reference back() { return m_valptr[m_size - 1]; }

			const_reference back() const { return m_valptr[m_size - 1]; }

			reference at(size_type n )
			{
				if (n >= m_size) 
					throw std::out_of_range("ft::vector: element's out of bounds");
				return m_valptr[n];
			}

			const_reference at(size_type n ) const
			{
				if (n >= m_size) 
					throw std::out_of_range("ft::vector: element's out of bounds");
				return m_valptr[n];
			}

			reference front() { return m_valptr[0]; }

			const_reference front() const { return m_valptr[0]; }

			iterator	begin() { return iterator(m_valptr); }

			const_iterator begin() const { return const_iterator(m_valptr); }

			iterator	end() { return iterator(m_valptr + m_size); }

			const_iterator end() const { return const_iterator(m_valptr + m_size); }

			reverse_iterator rbegin() { return reverse_iterator(end()); }

			reverse_iterator rend() { return  reverse_iterator(this->begin()); }

			const_reverse_iterator rbegin() const { return const_reverse_iterator(end());  }

			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
       
    }; // class vector

    template<typename T, typename U>
    bool operator==(vector<T> const& lhs, vector<U> const& rhs ) {
        if (lhs.size() != rhs.size())
            return false;
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template<typename T, typename U>
    bool operator!=(vector<T> const& lhs, ft::vector<U> const& rhs ) {
        return !operator==(lhs, rhs);
    }

    template<typename T, typename U>
    bool operator<(vector<T> const& lhs, vector<U> const& rhs) {
        if (operator==(lhs, rhs))
            return false;
        return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end() );
    }

    template<typename T, typename U>
    bool operator<=(vector<T> const& lhs, ft::vector<U> const& rhs ) {
        return operator==(lhs, rhs) || operator<(lhs, rhs);
    }

    template<typename T, typename U>
    bool operator>(vector<T> const& lhs, vector<U> const& rhs) {
        if (operator==(lhs, rhs))
            return false;
        return !operator<(lhs, rhs);
    }

    template<typename T, typename U>
    bool operator>=(vector<T> const& lhs, ft::vector<U> const& rhs) {
        return operator==(lhs, rhs) || operator>(lhs, rhs);
    }

    template<typename T, typename Alloc>
    void swap(vector<T, Alloc>& x, vector<T, Alloc>& y ) {
        x.swap(y);
    }

} // namespace ft
