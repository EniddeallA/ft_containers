#pragma once

#include "utils.hpp"
#include "bidirectional_iterator.hpp"
#include "rbidirectional_iterator.hpp"
#include "pair.hpp"
#include "avl.hpp"

namespace ft
{
	template <typename Key, typename T,
			typename Compare = std::less<Key>,
			typename Alloc = std::allocator< ft::pair<const Key, T> >
			>
	class map 
	{
		public:
			typedef ft::pair<const Key, T>										value_type;
			typedef Key															key_type;
			typedef T 															mapped_type;
			typedef Compare 													key_compare;
			typedef Alloc														allocator_type;
			typedef typename allocator_type::pointer 							pointer;
			typedef typename allocator_type::const_pointer 						const_pointer;
			typedef typename allocator_type::reference 							reference;
			typedef typename allocator_type::const_reference 					const_reference;
			typedef typename ft::avl<Key, T, Compare, Alloc> 					tree;
			typedef typename tree::node_type									node_type;
			typedef typename tree::node_pointer									node_pointer;
			typedef typename tree::const_node_pointer 							const_node_pointer;
			typedef ft::bidirectional_iterator<tree, node_pointer>  			iterator;
			typedef ft::bidirectional_iterator<tree, const_node_pointer>		const_iterator;
			typedef ft::rbidirectional_iterator<iterator> 						reverse_iterator;
			typedef ft::rbidirectional_iterator<const_iterator>					const_reverse_iterator;
			typedef size_t 														size_type;
			
			class value_compare;

		private:
			allocator_type 	_alloc;
			tree			_tree;
			key_compare		_comp;
			value_compare	v_comp;

			iterator create_iterator(node_pointer p) {
				return iterator(p, _tree);
			}

			const_iterator create_iterator(const_node_pointer p) const {
				return const_iterator(p, _tree);
			}

		public:
			explicit map(const key_compare& comp = key_compare(), 
							const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _comp(comp), v_comp(comp) {}

			template <class InputIterator>
			map(InputIterator first, InputIterator last, 
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _comp(comp), v_comp(comp)
			{
				insert<InputIterator>(first, last);
			}
			map(const map& m) : v_comp(	_comp)
			{
				*this = m;
			}
			map& operator = (const map& m)
			{
				_tree = m._tree;
				_comp = m._comp;
				_alloc = m._alloc;
				v_comp = m.v_comp;
				return *this;
			}
			~map() {}

			iterator begin(){ return create_iterator(_tree.min_node()); }
			const_iterator begin() const { return create_iterator(_tree.min_node()); }
			iterator end() { return create_iterator(NULL); }
			const_iterator end() const { return create_iterator(NULL); }
			reverse_iterator rbegin() { return reverse_iterator(end());	}
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
			reverse_iterator rend() { return reverse_iterator(begin()); }
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

			bool empty() const { return _tree.empty(); }
			size_type size() const { return _tree.size(); }
			size_type max_size() const { return this->_alloc.max_size(); }
			allocator_type get_allocator() const { return _alloc; }

			mapped_type& operator[] (const key_type& k)
			{
				node_pointer p = _tree.find(k);
				if (!p)
					p = _tree.insert(ft::make_pair(k, mapped_type()));
				return p->_ptr->second;
			}

			void clear() {
				_tree.delete_all();
			}

			ft::pair<iterator, bool> insert(const value_type& val)
			{
				size_type size = _tree.size();
				node_pointer p = _tree.insert(val);
				return ft::make_pair(create_iterator(p), _tree.size() > size);
			}
			iterator insert(iterator pos, const value_type& val)
			{
				node_pointer p = NULL;
				if (empty() || pos.base() == pos.end() 
						|| !pos.base()->parent)
					p = _tree.insert(val);
				else
					p = _tree.insert(pos.base(), val);
				return create_iterator(p);
			}
			template<class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				while (first != last)
					insert(*(first++));
			}

			void erase(iterator pos)
			{
				if (pos.base() == pos.end())
					_tree.delete_node(NULL);
				else
					_tree.delete_node(pos.base());
			}
			size_type erase(const key_type& k)
			{
				return _tree.delete_node(k, true);
			}
			void erase(iterator first, iterator last)
			{
				while (first != last)
					erase(first++);
			}

			void swap(map& m) {
				allocator_type tmp_alloc = m._alloc;
				key_compare tmp_comp = m._comp;
				value_compare tmp_v_comp = m.v_comp;

				m._alloc = this->_alloc;
				m._comp = this->_comp;
				m.v_comp = this->v_comp;

				this->_alloc = tmp_alloc;
				this->_comp = tmp_comp;
				this->v_comp = tmp_v_comp;

				this->_tree.swap(m._tree);
			}

			size_type count(const key_type& k) const 
			{
				const_iterator it = find(k);
				return (it == end() ? 0 : 1);
			}

			iterator find(const key_type& k) 
			{
				node_pointer n = _tree.find(k);
				return create_iterator(n);
			}
			const_iterator find(const key_type& k) const 
			{
				node_pointer n = _tree.const_find(k);
				return create_iterator(n);
			}

			iterator lower_bound(const key_type& k) 
			{
				node_pointer n = _tree.lower_bound(k);
				return create_iterator(n);
			}
			const_iterator lower_bound (const key_type& k) const 
			{
				const_node_pointer n = _tree.lower_bound(k);
				return create_iterator(n);
			}

			iterator upper_bound(const key_type& k) 
			{
				node_pointer n = _tree.upper_bound(k);
				return create_iterator(n);
			}
			const_iterator upper_bound(const key_type& k) const
			{
				const_node_pointer n = _tree.upper_bound(k);
				return create_iterator(n);
			}

			ft::pair<iterator, iterator> equal_range(const key_type& k) 
			{
				iterator it = lower_bound(k);
				if (_comp(k, it->first))
					return ft::make_pair(it, create_iterator(it.base()));
				return ft::make_pair(it++, it);
			}
			ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const 
			{
				const_iterator it = lower_bound(k);
				if (_comp(k, it->first))
					return ft::make_pair(it, create_iterator(it.base()));
				return ft::make_pair(it++, it);
			}
			
			key_compare key_comp() const { return _comp; }
			value_compare value_comp() const { return v_comp; }

	};

	template <typename Key, typename T, 
			typename Compare, typename Alloc
			>
	class map<Key, T, Compare, Alloc>::value_compare : std::binary_function<value_type, value_type, bool>
	{
		protected:
			Compare _comp;
		public:
			value_compare (Compare c) : _comp(c) {}
			bool operator() (const value_type& lhs, const value_type& rhs) const
			{
				return _comp(lhs.first, rhs.first);
			}
	};

	template <class Key, class T, class Compare, class Alloc>
  	bool operator== (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator!= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs == rhs);
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator<  (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator<= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs > rhs);
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator>  (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return rhs < lhs;
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator>= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
  	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) {
		x.swap(y);
	}
} // namespace ft
