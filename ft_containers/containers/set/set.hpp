#ifndef FT_SET_HPP
#define FT_SET_HPP

#include "utils.hpp"
#include <iostream>
#include "set_red_black_tree.hpp"
#include "SetIterator.hpp"
#include "SetReverseIterator.hpp"

namespace ft
{
	template <class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
	class set
	{
		public:
			typedef T		key_type;
			typedef T		value_type;
			typedef Compare	key_compare;
			typedef Compare	value_compare;

			typedef	Alloc allocator_type;
			typedef	typename allocator_type::reference reference;
			typedef	typename allocator_type::const_reference const_reference;
			typedef	typename allocator_type::pointer pointer;
			typedef	typename allocator_type::const_pointer const_pointer;

			typedef typename ft::SetIterator<key_type, false> iterator;
			typedef typename ft::SetIterator<key_type, true> const_iterator;
			typedef typename ft::SetReverseIterator<key_type, false> reverse_iterator;
			typedef typename ft::SetReverseIterator<key_type, true> const_reverse_iterator;

			typedef typename std::ptrdiff_t difference_type;
			typedef std::size_t size_type;

			explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			{
				(void)comp;
				(void)alloc;
			}

			template <class InputIterator>
			set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<InputIterator::is_iter_map, InputIterator>::type = 0)
			{
				while (first != last)
				{
					insert(first, first.getPointer()->_pair);
					first++;
				}
				(void)comp;
				(void)alloc;
			}

			set (const set& x)
			{
				*this = x;
			}

			~set() {}

			set& operator= (const set& x)
			{
				clear();
				if (x.size() > 0)
					insert(x.begin(), x.end());
				return (*this);
			}

			iterator begin() { return iterator(_tree.begin()); }
			iterator end() { return iterator(_tree.end()); }
			const_iterator begin() const { return const_iterator(_tree.const_begin()); }
			const_iterator end() const { return const_iterator(_tree.const_end()); }

			reverse_iterator rbegin() { return reverse_iterator(_tree.rbegin()); }
			reverse_iterator rend() { return reverse_iterator(_tree.rend()); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(_tree.const_rbegin()); }
			const_reverse_iterator rend() const { return const_reverse_iterator(_tree.const_rend()); }

			bool empty() const { return (_tree.get_size() == 0) ? 1 : 0; }

			size_type size() const { return _tree.get_size(); }

			size_type max_size() const { return _tree.max_size(); }

			pair<iterator,bool> insert (const value_type& val)
			{
				iterator it;
				nodePointer node_tmp = _tree.search_pair(val);
				if (node_tmp != NULL)
				{
					return ft::make_pair(iterator(node_tmp), false);
				}
				else
				{
					it = iterator(insert2(val));
					return (ft::make_pair(it, true));
				}
			}

			iterator insert (iterator position, const value_type& val)
			{
				(void)position;
				(void)val;
				if (_tree.get_size() > 0 && _tree.search_pair(val) != NULL)
				{
					iterator it_tmp(position);
					while (it_tmp != _tree.end())
					{
						if (*it_tmp == val)
							return it_tmp;
						it_tmp++;
					}
					it_tmp = _tree.begin();
					while (it_tmp != _tree.end())
					{
						if (*it_tmp == val)
							return it_tmp;
						it_tmp++;
					}
				}
				return (insert(val).first);
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					insert(first, first.getPointer()->_pair);
					first++;
				}
			}

			void erase (iterator position)
			{
				if (position.getPointer() != NULL)
					_tree.deleteNode(position.getPointer()->_pair);
			}

			size_type erase (const key_type& k)
			{
				if (_tree.search_key(k) == NULL)
					return 0;
				_tree.deleteNode(k);
				return 1;
			}

			void erase (iterator first, iterator last)
			{
				(void)last;
				iterator prev_it = first;

				while (first != last)
				{
					first++;
					erase(prev_it);
					prev_it = first;
				}
			}

			void swap (set& x)
			{
				_tree.swap(x._tree);
			}


			void clear()
			{
				if (size() > 0)
					erase(begin(), end());
				_tree.set_root_to_null();
			}

			key_compare key_comp() const
			{
				return key_compare();
			}

			value_compare value_comp() const
			{
				return value_compare(key_compare());
			}

			iterator find(key_type k)
			{
				for (iterator it = begin(); it != end(); ++it)
					if (*it == k)
						return it;
				return end();
			}

			const_iterator find (const key_type& k) const
			{
				for (const_iterator it = begin(); it != end(); ++it)
					if (*it == k)
						return it;
				return end();
			}

			size_type count (const key_type& k) const
			{
				return (find(k) != end());
			}

			iterator lower_bound (const key_type& k)
			{
				iterator it = begin();
				while (_comp(*it, k) && it != end())
					it++;
				return it;
			}
			const_iterator lower_bound (const key_type& k) const
			{
				const_iterator it = begin();
				while (_comp(*it, k) && it != end())
					it++;
				return it;
			}

			iterator upper_bound (const key_type& k)
			{
				iterator it = begin();
				while (_comp(k, *it) == false && it != end())
					it++;
				return it;
			}

			const_iterator upper_bound (const key_type& k) const
			{
				const_iterator it = begin();
				while (_comp(k, *it) == false && it != end())
					it++;
				return it;
			}

			pair<iterator,iterator> equal_range (const key_type& k)
			{
				return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
			}
			
			pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
			}


			allocator_type get_allocator() const
			{
				return allocator_type();
			}

			private:
				SetRedBlackTree<T> _tree;

				typedef	SetNode<key_type>		node;
				typedef SetNode<key_type>*	nodePointer;
				key_compare _comp;

				nodePointer insert2(const value_type &value)
				{
					return _tree.insert(value);
				}
	};
}

#endif