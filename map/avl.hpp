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
			typedef ft::pair<const Key, T>							value_type;
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef Compare											key_compare;
			typedef	node<const Key, T, Alloc>						node_type;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename allocator_type::reference				reference;
			typedef typename Alloc::template rebind<node<const Key, T, Alloc> >::other	node_allocator_type;
			typedef typename node_allocator_type::pointer			node_pointer;
			typedef typename node_allocator_type::const_pointer		const_node_pointer;
			typedef size_t											size_type;

		private:
			node_pointer	_head;
			allocator_type	_alloc;
			node_allocator_type	_node_alloc;
			key_compare		_comp;
			size_type	_size;

			node_pointer _delete_all(node_pointer n)
			{
				if (!n) 
					return NULL;
				n->left = _delete_all(n->left);
				n->right = _delete_all(n->right);
				_node_alloc.destroy(n);
				_node_alloc.deallocate(n, 1);
				--_size;
				return (NULL);
			}

			node_pointer create_node(const value_type& val = value_type())
			{
				node_pointer _ptr = NULL;
				_ptr = _node_alloc.allocate(1);
				_node_alloc.construct(_ptr, node_type(val, _alloc));
				return (_ptr);
			}

			node_pointer _insert_all(node_pointer to, node_pointer from)
			{
				if (!from)
					return NULL;
				to = create_node(*from->_ptr);
				to->height = from->height;
				to->left = _insert_all(to->left, from->left);
				if (to->left)
					to->left->parent = to;
				to->right = _insert_all(to->right, from->right);
				if (to->right)
					to->right->parent = to;
				return to;
			}

			node_pointer _find(node_pointer head, const key_type& key)
			{
				if (!head) 
					return NULL;
				if (_comp(key, head->_ptr->first))
					return _find(head->left, key);
				else if (_comp(head->_ptr->first, key))
					return _find(head->right, key);
				return head;
			}

			node_pointer _const_find(node_pointer head, const key_type& key) const
			{
				if (!head) 
					return NULL;
				if (_comp(key, head->_ptr->first))
					return _const_find(head->left, key);
				else if (_comp(head->_ptr->first, key))
					return _const_find(head->right, key);
				return head;
			}

			int height(node_pointer node)
			{
				if (!node)
					return -1;
				return node->height;
			}

			void calculate_height(node_pointer n)
			{
				n->height = std::max(height(n->left), height(n->right)) + 1;
			}
			
			int balance_factor(node_pointer n)
			{
				return height(n->left) - height(n->right);
			}

			bool left_unbalance(node_pointer n)
			{
				return balance_factor(n) > 1;
			}

			bool right_unbalance(node_pointer n)
			{
				return balance_factor(n) < -1;
			}

			node_pointer rotate_left(node_pointer n) {
				node_pointer tmp = n->right;
				n->right = tmp->left;
				tmp->left = n;
				tmp->parent = n->parent;
				n->parent = tmp;
				if (n->right)
					n->right->parent = n;
				if (tmp->left)
					tmp->left->parent = tmp;
				calculate_height(n);
				calculate_height(tmp);
				return (tmp);
			}

			node_pointer rotate_right(node_pointer n) {
				node_pointer tmp = n->left;
				n->left = tmp->right;
				tmp->right = n;
				tmp->parent = n->parent;
				n->parent = tmp;
				if (n->left)
					n->left->parent = n;
				if (tmp->right)
					tmp->right->parent = tmp;
				calculate_height(n);
				calculate_height(tmp);
				return (tmp);
			}

			node_pointer balance_tree(node_pointer head)
			{
				if (right_unbalance(head)) 
				{
					if (balance_factor(head->right) > 0)
						head->right = rotate_right(head->right);
					return rotate_left(head);
				}
				else if (left_unbalance(head)) 
				{
					if (balance_factor(head->left) < 0)
						head->left = rotate_left(head->left);
					return rotate_right(head);
				}
				return (head);
			}

			node_pointer _insert(node_pointer head, const value_type& val, node_pointer* to)
			{
				if (!head)
				{
					_size++;
					*to = create_node(val);
					return *to;
				}
				if (_comp(val.first, head->_ptr->first))
				{
					head->left = _insert(head->left, val, to);
					if (head->left)
						head->left->parent = head;
				}
				else if (_comp(head->_ptr->first, val.first))
				{
					head->right = _insert(head->right, val, to);
					if (head->right)
						head->right->parent = head;
				}
				else
					*to = head;
				calculate_height(head);
				head = balance_tree(head);
				return head;
			}

			node_pointer _delete(node_pointer node)
			{
				if (node->left == NULL || node->right == NULL)
				{
					// node has 1 child or none
					// replace parent by the not NULL "left||right" child
					node_pointer new_node;
					if (node->left)
						new_node = node->left;
					else
						new_node = node->right;
					_node_alloc.destroy(node);
					_node_alloc.deallocate(node, 1);
					node = new_node;
				} 
				else 
				{
					// node has more than 1 child
					// finding max_node in the left subtree
					node_pointer max = max_node(node->left);
					// remove max node from its parent
					if (max == node->left)
						max->parent->left = max->left;
					else
						max->parent->right = max->left;
					if (max->left)
						max->left->parent = max->parent;
					// assign max node the children of node
					max->left = node->left;
					max->right = node->right;
					if (max->left != NULL)
						max->left->parent = max;
					if (max->right != NULL)
						max->right->parent = max;
					_node_alloc.destroy(node);
					_node_alloc.deallocate(node, 1);
					node = max;
				}
				--_size;
				return (node);	
			}

			node_pointer delete_key_node(node_pointer head, const key_type& key)
			{
				if (!head) 
					return NULL;
				if (_comp(key, head->_ptr->first))
				{
					head->left = delete_key_node(head->left, key);
					if (head->left)
						head->left->parent = head;
				} 
				else if (_comp(head->_ptr->first, key)) 
				{
					head->right = delete_key_node(head->right, key);
					if (head->right)
						head->right->parent = head;
				} 
				else
				{
					head = _delete(head);
					if (!head) 
						return NULL;
					head->parent = NULL;
				}
				calculate_height(head);
				head = balance_tree(head);
				return (head);
			}

			node_pointer _delete_node(node_pointer head, node_pointer node) {
				if (!head) 
					return NULL;
				if (_comp(node->_ptr->first, head->_ptr->first)) 
				{
					head->left = _delete_node(head->left, node);
					if (head->left)
						head->left->parent = head;
				} 
				else if (_comp(head->_ptr->first, node->_ptr->first)) 
				{
					head->right = _delete_node(head->right, node);
					if (head->right)
						head->right->parent = head;
				} 
				else
				{
					head = _delete(head);
					if (!head) 
						return NULL;
					head->parent = NULL;
				}
				calculate_height(head);
				head = balance_tree(head);
				return (head);
			}

		public:
			avl(const key_compare& comp = key_compare(), 
					const allocator_type& alloc = allocator_type(),
					const node_allocator_type& node_alloc = node_allocator_type()) :
				_head(NULL), _alloc(alloc), _node_alloc(node_alloc), _comp(comp), _size(0) {}
			avl(const avl& a) : _head(NULL), _size(0) { *this = a; }
			avl& operator = (const avl& a)
			{
				delete_all();
				this->_head = _insert_all(this->_head, a._head);
				this->_alloc = a._alloc;
				this->_node_alloc = a._node_alloc;
				this->_comp = a._comp;
				this->_size = a._size;
				return *this;
			}
			~avl() { delete_all(); }

			node_pointer find(const key_type& k)
			{
				if (empty()) 
					return NULL;
				return _find(_head, k);
			}
			node_pointer const_find(const key_type& k) const
			{
				if (empty())
					return NULL;
				return _const_find(_head, k);
			}

			node_pointer insert(const value_type& v)
			{
				node_pointer to = NULL;
				_head = _insert(_head, v, &to);
				return to;
			}
			node_pointer insert(node_pointer hint, const value_type& val)
			{
				node_pointer tmp = _head;
				while (tmp != NULL) {
					if (tmp == hint)
						break ;
					else if (_comp(val.first, tmp->_ptr->first))
					{
						if (!tmp->left)
							break ;
						tmp = tmp->left;
					} 
					else if (_comp(tmp->_ptr->first, val.first)) 
					{
						if (!tmp->right)
							break ;
						tmp = tmp->right;
					}
					else
						break ;
				}
				node_pointer to = NULL;
				tmp = _insert(tmp, val, &to);
				return to;
			}

			size_type delete_node(const key_type& key, bool is_key)
			{
				size_type old_size = _size;
				if (empty() || !is_key) 
					return 0;
				_head = delete_key_node(_head, key);
				if (_head) 
					_head->parent = NULL;
				return old_size - _size;
			}
			void delete_node(node_pointer node)
			{
				if (empty()) 
					return;
				_head = _delete_node(_head, node);
				if (_head) 
					_head->parent = NULL;
			}
			void delete_all()
			{
				_head = _delete_all(_head);
			}

			node_pointer min_node()
			{
				if (!_head) 
					return NULL;
				return avl::min_node(_head);
			}
			const_node_pointer min_node() const
			{
				if (!_head) 
					return NULL;
				return avl::min_node(_head);
			}
			node_pointer max_node()
			{
				if (!_head) 
					return NULL;
				return avl::max_node(_head);
			}
			const_node_pointer max_node() const
			{
				if (!_head) 
					return NULL;
				return avl::max_node(_head);
			}
			static node_pointer min_node(node_pointer parent) 
			{
				if (parent->left == NULL) 
					return parent;
				return min_node(parent->left);
			}
			static const_node_pointer min_node(const_node_pointer parent) 
			{
				if (parent->left == NULL) 
					return parent;
				return min_node(parent->left);
			}
			static node_pointer max_node(node_pointer parent) 
			{
				if (parent->right == NULL) 
					return parent;
				return max_node(parent->right);
			}
			static const_node_pointer max_node(const_node_pointer parent) 
			{
				if (parent->right == NULL) 
					return parent;
				return max_node(parent->right);
			}

			node_pointer root() const
			{
				return _head;
			}
			size_type size() const
			{
				return _size;
			}
			bool empty() const
			{
				return _size == 0;
			}

			static node_pointer next_node(node_pointer node) 
			{
				key_compare	comp = key_compare();
				if (!node->right)
				{
					node_pointer n = node->parent;
					while (n && comp(n->_ptr->first, node->_ptr->first))
						n = n->parent;
					return n;
				}
				else 
					return min_node(node->right);
			}
			static const_node_pointer next_node(const_node_pointer node) 
			{
				key_compare	comp = key_compare();
				if (!node->right) 
				{
					node_pointer n = node->parent;
					while (n && comp(n->_ptr->first, node->_ptr->first))
						n = n->parent;
					return n;
				}
				else
					return min_node(node->right);
			}
			static node_pointer prev_node(node_pointer node) 
			{
				key_compare	comp = key_compare();
				if (!node->left) 
				{
					node_pointer n = node->parent;
					while (n && comp(node->_ptr->first, n->_ptr->first))
						n = n->parent;
					return n;
				} 
				else
					return max_node(node->left);
			}
			static const_node_pointer prev_node(const_node_pointer node) 
			{
				key_compare	comp = key_compare();
				if (!node->left)
				{
					node_pointer n = node->parent;
					while (n && comp(node->_ptr->first, n->_ptr->first))
						n = n->parent;
					return n;
				} 
				else
					return max_node(node->left);
			}

			node_pointer lower_bound(const key_type& k) 
			{
				if (empty()) 
					return NULL;
				node_pointer n = min_node();
				while (n && _comp(n->_ptr->first, k))
					n = next_node(n);
				return n;
			}
			const_node_pointer lower_bound(const key_type& k) const 
			{
				if (empty()) 
					return NULL;
				const_node_pointer n = min_node();
				while (n && _comp(n->_ptr->first, k))
					n = next_node(n);
				return n;
			}
			node_pointer upper_bound(const key_type& k) 
			{
				if (empty()) 
					return NULL;
				node_pointer n = min_node();
				while (n && _comp(n->_ptr->first, k))
					n = next_node(n);
				if (!n) 
					return NULL;
				if (_comp(k, n->_ptr->first)) 
					return n;
				return next_node(n);
			}
			const_node_pointer upper_bound(const key_type& k) const 
			{
				if (empty()) 
					return NULL;
				const_node_pointer n = min_node();
				while (n && _comp(n->_ptr->first, k))
					n = next_node(n);
				if (!n) 
					return NULL;
				if (_comp(k, n->_ptr->first)) 
					return n;
				return next_node(n);
			}

			void swap(avl& t) {
				node_pointer		tmp_head = t._head;
				allocator_type 		tmp_alloc = t._alloc;
				node_allocator_type	tmp_node_alloc = t._node_alloc;
				key_compare			tmp_comp = t._comp;
				size_type			tmp_size = t._size;

				t._head = this->_head;
				t._alloc = this->_alloc;
				t._node_alloc = this->_node_alloc;
				t._comp = this->_comp;
				t._size = this->_size;

				this->_head = tmp_head;
				this->_alloc = tmp_alloc;
				this->_node_alloc = tmp_node_alloc;
				this->_comp = tmp_comp;
				this->_size = tmp_size;
			}

	};
} // namespace ft
