#pragma once

#include "iterator_traits.hpp"

namespace ft
{
	template <typename Iter, typename Node>
	struct bidirectional_iterator : public ft::iterator<std::bidirectional_iterator_tag, Iter>
	{
		typedef	Iter	iterator_type;
		typedef	Node	node_pointer;
		typedef typename iterator_type::node_type node_type;
		typedef typename iterator_type::value_type		value_type;
		typedef typename iterator_type::pointer			pointer;
		typedef typename iterator_type::const_pointer	const_pointer;
		typedef typename iterator_type::reference		reference;

		private:
			const iterator_type* _tree;
			node_pointer _head;
			node_pointer	_end;
		
		public:
			bidirectional_iterator() : _head(NULL), _end(NULL), _tree(NULL) {}
			bidirectional_iterator(node_pointer head, const iterator_type& tree) :
				_head(NULL), _tree(&tree), _end(NULL)
			{
				if (!head)
					this->_head = _end;
				else
					this->_head = head;
			}
			template <typename Iter1, typename Node1>
			bidirectional_iterator( const bidirectional_iterator<Iter1, Node1>& b) :
				_head(NULL), _end(NULL)
			{
				this->_tree = b.tree();
				if (b.head() == b.end())
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
				this->_tree = b.tree();
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
			
			bool operator == ( const bidirectional_iterator& b )
			{
				return (this->_head == b._head || 
						(this->_head == this->_end && b._head == b._end));
			}
			bool operator != ( const bidirectional_iterator& b )
			{
				return !(*this == b);
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

			bidirectional_iterator& operator ++ () {
				_head = iterator_type::next_node(_head);
				return (*this);
			}
			bidirectional_iterator operator ++ ( int ) {
				bidirectional_iterator<Iter, Node> b(*this);
				operator++();
				return (b);
			}
			bidirectional_iterator& operator -- ()
			{
				if (this->_head == iterator_type::min_node(_tree->root()))
					this->_head = iterator_type::prev_node(_end);
				else if (!_head)
					this->_head = iterator_type::max_node(_tree->root());
				else
					this->_head = iterator_type::prev_node(_head);
				return (*this);
			}
			bidirectional_iterator operator -- ( int )
			{
				bidirectional_iterator<Iter, Node> b(*this);
				operator--();
				return (b);
			}

	};
	
} // namespace ft
