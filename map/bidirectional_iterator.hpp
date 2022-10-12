#pragma once

#include "iterator_traits.hpp"

namespace ft
{
	template <typename Iter, typename Node>
	struct bidirectional_iterator : public ft::iterator<std::bidirectional_iterator_tag, Iter>
	{
		typedef	Iter									iterator_type;
		typedef	Node									node_pointer;
		typedef typename iterator_type::node_type 		node_type;
		typedef typename iterator_type::value_type		value_type;
		typedef typename iterator_type::pointer			pointer;
		typedef typename iterator_type::const_pointer	const_pointer;
		typedef typename iterator_type::reference		reference;

		private:
			const iterator_type* _tree;
			node_pointer _base;
			node_pointer	_end;
		
		public:
			bidirectional_iterator() : _tree(NULL), _base(NULL), _end(NULL) {}
			bidirectional_iterator(node_pointer head, const iterator_type& tree) :
				_tree(&tree), _base(NULL), _end(NULL)
			{
				if (!head)
					this->_base = _end;
				else
					this->_base = head;
			}
			template <typename Iter1, typename Node1>
			bidirectional_iterator( const bidirectional_iterator<Iter1, Node1>& b) :
				_base(NULL), _end(NULL)
			{
				this->_tree = b.tree();
				if (b.base() == b.end())
					this->_base = this->_end;
				else
					this->_base = b.base();
			}
			bidirectional_iterator( const bidirectional_iterator& b) :
				_tree(NULL), _base(NULL), _end(NULL) 
			{
				*this = b;
			}
			bidirectional_iterator& operator = ( const bidirectional_iterator& b)
			{
				this->_tree = b.tree();
				if (b.base() == b.end())
					this->_base = this->_end;
				else
					this->_base = b.base();
				return *this;
			}
			~bidirectional_iterator() {}

			node_pointer base() const {
				return this->_base;
			}
			node_pointer end() const {
				return this->_end;
			}
			const iterator_type* tree() const {
				return this->_tree;
			}
			
			bool operator == ( const bidirectional_iterator& b )
			{
				return (this->_base == b._base || 
						(this->_base == this->_end && b._base == b._end));
			}
			bool operator != ( const bidirectional_iterator& b )
			{
				return !(*this == b);
			}

			reference operator * () 
			{
				return (*this->_base->_ptr);
			}
			pointer operator-> ()
			{
				return (this->_base->_ptr);
			}
			const_pointer operator-> () const
			{
				return (this->_base->_ptr);
			}

			bidirectional_iterator& operator ++ () {
				_base = iterator_type::next_node(_base);
				return (*this);
			}
			bidirectional_iterator operator ++ ( int ) {
				bidirectional_iterator<Iter, Node> b(*this);
				operator++();
				return (b);
			}
			bidirectional_iterator& operator -- ()
			{
				if (this->_base == iterator_type::min_node(_tree->root()))
					this->_base = iterator_type::prev_node(_end);
				else if (!_base)
					this->_base = iterator_type::max_node(_tree->root());
				else
					this->_base = iterator_type::prev_node(_base);
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
