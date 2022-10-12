#pragma once

#include "iterator_traits.hpp"

namespace ft
{
	template <typename Iter>
	struct rbidirectional_iterator : public ft::iterator<std::bidirectional_iterator_tag, Iter>
	{
		typedef	Iter									iterator_type;
		typedef typename iterator_type::value_type		value_type;
		typedef typename iterator_type::pointer			pointer;
		typedef typename iterator_type::reference		reference;

		private:
			iterator_type _base;
		
		public:
			rbidirectional_iterator( void ) : _base() {}
			rbidirectional_iterator( const iterator_type& base ) : _base(base) {}
			rbidirectional_iterator( const rbidirectional_iterator<iterator_type>& rb ) 
			{
				*this = rb;
			}
			template<typename Iter2>
			rbidirectional_iterator( const rbidirectional_iterator<Iter2>& rb )
			{
				this->_base = rb.base();
			}
			rbidirectional_iterator& operator = ( const rbidirectional_iterator<iterator_type>& rb ) 
			{
				this->_base = rb.base();
				return (*this);
			}
			~rbidirectional_iterator() {}

			iterator_type base() const 
			{
				return _base;
			}

			bool operator == ( rbidirectional_iterator const & i ) 
			{
				return (this->_base == i._base);
			}
			bool operator != ( rbidirectional_iterator const & i ) 
			{
				return (this->_base != i._base);
			}

			reference operator * ()  { return (*(this->_base - 1)); }
			pointer operator-> ()  { return &(operator*()); }

			rbidirectional_iterator& operator ++ () 
			{
				--this->_base;
				return (*this);
			}
			rbidirectional_iterator operator ++ ( int ) 
			{
				rbidirectional_iterator<iterator_type> i(*this);
				--this->_base;
				return (i);
			}
			rbidirectional_iterator& operator -- () 
			{
				++this->_base;
				return (*this);
			}
			rbidirectional_iterator operator -- ( int ) 
			{
				rbidirectional_iterator<iterator_type> i(*this);
				++this->_base;
				return (i);
			}

	};
	
} // namespace ft
