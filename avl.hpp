#pragma once

#include "node.hpp"

namespace ft
{
	template <	typename Key, typename T,
				typename Compare = std::less<Key>,
				typename Alloc = std::allocator< ft::pair<const Key, T> > >
	class avl
	{
		public:
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef ft::pair<const Key, T>							value_type;
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef Compare											key_compare;
			typedef	node<const Key, T, Alloc>						node_type;
			typedef Alloc											allocator_type;
			typedef typename Alloc::template rebind<node<const Key, T, Alloc> >::other	node_allocator_type;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename allocator_type::reference				reference;
			typedef typename node_allocator_type::pointer			node_pointer;
			typedef typename node_allocator_type::const_pointer		const_node_pointer;
			typedef size_t											size_type;

		private:
			node_pointer	_root;
			allocator_type	_alloc;
			node_allocator_type	_node_alloc;
			key_compare		_comp;
			size_type	_size;

			node_pointer _delete_all(node_pointer head)
			{
				if (!head) return NULL;
				head->left = _delete_all(head->left);
				head->right = _delete_all(head->right);
				_node_alloc.destroy(head);
				_node_alloc.deallocate(head, 1);
				--_size;
				return (NULL);
			}

			node_pointer insert_all(node_pointer to, node_pointer from)
			{
				if (!from)	return NULL;
				to = make_node(*from->_ptr);
				to->height = from->height;
				to->left = insert_all(to->left, from->left);
				if (to->left)	to->left->parent = to;
				to->right = _insert_all(parent->right, from->right);
				if (to->right)	to->right->parent = to;
				return to;
			}

		public:
			avl(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
					const node_allocator_type& node_alloc = node_allocator_type()) :
				_root(NULL), _alloc(NULL), _node_alloc(node_alloc), _comp(comp), _size(0) {}

			avl(const avl& a) : _root(NULL), _size(0)
			{
				*this = a;
			}
			avl& operator = (const avl& a)
			{
				delete_all();
				this->_alloc = a._alloc;
				this->_node_alloc = a._node_alloc;
				this->_comp = a._comp;
				this->_size = a._size;
				this->_root = insert_all(this->_root, a._root);
				return *this;
			}
			~avl_tree()
			{
				delete_all();
			}

			

			void delete_all()
			{
				_root = _delete_all(_root);
			}
	};
} // namespace ft
