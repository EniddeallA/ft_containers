#pragma once

#include "iterator.hpp"

namespace ft
{
	template <typename Iter, typename Node>
	struct bidirectional_iterator : public ft::iterator<std::bidirectional_iterator_tag, Iter>
	{
		typedef	Iter	iterator_type;
		typedef	Node	node_ptr;
		typedef typename iterator_type::node_type node_type;
		typedef typename iterator_type::value_type		value_type;
		typedef typename iterator_type::pointer			pointer;
		typedef typename iterator_type::const_pointer	const_pointer;
		typedef typename iterator_type::reference		reference;

		private:
			const iterator_type* _tree;
			node_ptr _head;
			node_ptr	_end;
		
		public:
			bidirectional_iterator() : _head(NULL), _end(NULL), _tree(NULL) {}
			bidirectional_iterator(node_ptr head, const iterator_type& tree) :
				_head(NULL), _tree(&tree), _end(NULL)
			{
				if (head == NULL)
					this->_head = _end;
				else
					this->_head = head;
			}
			template <typename Iter1, typename Node1>
			bidirectional_iterator( const bidirectional_iterator<Iter1, Node1>& b) :
				_head(NULL), _end(NULL)
			{
				this->_tree = b.tree();
				if (b.head() == b.end())\
					this->_head = this->_end;
				else
					this->_head = b.head();
			}
			bidirectional_iterator( const bidirectional_iterator& b) :
				_head(NULL), _end(NULL), _tree(NULL)
			{
				*this = b;
			}
			bidirectional_iterator& operator = ( const bidirectional_iterator& b)
			{
				this->_tree - b.tree();
				if (b.head() == b.end())\
					this->_head = this->_end;
				else
					this->_head = b.head();
				return *this;
			}
			~bidirectional_iterator() {}

			node_pointer head() const {
				return this->_head;
			}
			node_pointer end() const {
				return this->_end;
			}
			const iterator_type* tree() const {
				return this->_tree;
			}
			
			bool operator == ( const bidir_iterator& other )
			{
				return (this->_base == other._base || 
						(this->_base == this->_past_end && other._base == other._past_end));
			}
			bool operator != ( const bidir_iterator& other )
			{
				return !(*this == other);
			}

			reference operator * () 
			{
				return (*this->_head->_ptr);
			}
			pointer operator-> ()
			{
				return (this->_head->_ptr);
			}
			const_pointer operator-> () const
			{
				return (this->_head->_ptr);
			}

			


	};
	
} // namespace ft
