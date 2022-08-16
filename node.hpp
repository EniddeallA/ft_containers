#pragma once

#include <memory>
#include "pair.hpp"

namespace ft
{
	template < typename key, typename T, typename Alloc = std::allocator< ft::pair<const key, T> > >
	struct node
	{
		public:
			typedef ft::pair<const key, T>  value_type;
			typedef key		key_type;
			typedef T		mapped_type;
			typedef Alloc	allocator_type;
			typedef node<const key, T, Alloc>	node_type;
			typedef typename allocator_type::pointer	pointer;
			typedef typename allocator_type::reference	reference;

		private:
			allocator_type	_alloc;

		public:
			pointer _ptr;
			node_type	*parent;
			node_type	*right;
			node_type	*left;
			int height;

		// Explicit Keyword is used to to not implicitly convert types
		explicit node(const value_type& val, const allocator_type& alloc = allocator_type()) :
			_alloc(alloc), left(NULL), right(NULL), parent(NULL), height(0)
		{
			this->_ptr = this->_alloc.allocate(1);
			this->_alloc.construct(_ptr, val);
		}
		node(const node& n) { *this = n; }
		node& operator = (const node& n)
		{
			this->_ptr = this->_alloc.allocate(1);
			this->_alloc.construct(_ptr, *n._ptr);
			this->parent = n.parent;
			this->right = n.right;
			this->left = n.left;
			this->height = n.height;
			this->_alloc = n._alloc;
			return *this;
		}
		~node()
		{
			this->_alloc.destroy(_ptr);
			this->_alloc.deallocate(_ptr, 1);
		}

		void set_content(const value_type& val)
		{
			if (_ptr != NULL)
				this->_alloc.destroy(_ptr);
			else
				this->_ptr = this->_alloc.allocate(1);
			this->_alloc.construct(_ptr, val);
		}

		bool operator == (const node& n)
		{
			return	(
						*this->_ptr == *n._ptr && this->parent == n.parent
						&& this->left == n.left && this->right == n.right
						&& this->height == n.height
					);
		}
		bool operator != ( const node& n )
		{
			return !(*this == n);
		}
	};
}