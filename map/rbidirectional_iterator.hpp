#pragma once

#include "iterator_traits.hpp"

namespace ft
{
	template <typename Iter>
	struct rbidirectional_iterator : public ft::iterator<std::bidirectional_iterator_tag, Iter>
	{
		typedef	Iter	iterator_type;
		typedef typename iterator_type::value_type		value_type;
		typedef typename iterator_type::pointer			pointer;
		typedef typename iterator_type::const_pointer	const_pointer;
		typedef typename iterator_type::reference		reference;

		private:
			iterator_type _head;
		
		public:
			rbidirectional_iterator( void ) : _head() {}
			rbidirectional_iterator( const iterator_type& head ) : _head(head) {}
			rbidirectional_iterator( const rbidirectional_iterator<iterator_type>& rb ) 
			{
				*this = rb;
			}
			template<typename Iter2>
			rbidirectional_iterator( const rbidirectional_iterator<Iter2>& rb )
			{
				this->_head = rb.base();
			}
			rbidirectional_iterator& operator = ( const rbidirectional_iterator<iterator_type>& rb ) 
			{
				this->_head = rb.base();
				return (*this);
			}
			~rbidirectional_iterator() {}

			iterator_type head() const 
			{
				return _head;
			}

			bool operator == ( rbidirectional_iterator const & i ) 
			{
				return (this->_head == i._head);
			}
			bool operator != ( rbidirectional_iterator const & i ) 
			{
				return (this->_head != i._head);
			}

			reference operator * () 
			{
				iterator_type i = this->_head;
				--i;
				return (*i);
			}
			pointer operator-> () 
			{
				return &(operator*());
			}

			rbidirectional_iterator& operator ++ () 
			{
				--this->_head;
				return (*this);
			}
			rbidirectional_iterator operator ++ ( int ) 
			{
				rbidirectional_iterator<iterator_type> i(*this);
				--this->_head;
				return (i);
			}
			rbidirectional_iterator& operator -- () 
			{
				++this->_head;
				return (*this);
			}
			rbidirectional_iterator operator -- ( int ) 
			{
				rbidirectional_iterator<iterator_type> i(*this);
				++this->_head;
				return (i);
			}

	};
	
} // namespace ft
