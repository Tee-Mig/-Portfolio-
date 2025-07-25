#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include "utils.hpp"
#include <iostream>
#include "red_black_tree.hpp"
#include "MapIterator.hpp"
#include "MapReverseIterator.hpp"

namespace ft
{
	template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> >	>
	class map
	{
		public:
			typedef Key		key_type;
			typedef T		mapped_type;
			typedef	ft::pair<key_type, mapped_type> value_type;
			typedef Compare	key_compare;

			class value_compare : ft::binary_function<value_type,value_type,bool>
			{   
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
				public:
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

			typedef	Alloc allocator_type;
			typedef	typename allocator_type::reference reference;
			typedef	typename allocator_type::const_reference const_reference;
			typedef	typename allocator_type::pointer pointer;
			typedef	typename allocator_type::const_pointer const_pointer;

			typedef typename ft::MapIterator<key_type, mapped_type, false> iterator;
			typedef typename ft::MapIterator<key_type, mapped_type, true> const_iterator;
			typedef typename ft::MapReverseIterator<key_type, mapped_type, false> reverse_iterator;
			typedef typename ft::MapReverseIterator<key_type, mapped_type, true> const_reverse_iterator;
			typedef typename allocator_type::template rebind<Node<key_type, mapped_type>	>::other  alloc_rebind;

			typedef typename std::ptrdiff_t difference_type;
			typedef std::size_t size_type;

			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			{
				(void)comp;
				(void)alloc;
			}

			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
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

			map (const map& x)
			{
				*this = x;
			}

			~map() {}

			map& operator= (const map& x)
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

			size_type max_size() const { alloc_rebind reb; return reb.max_size(); }

			mapped_type& operator[] (const key_type& k)
			{
				nodePointer tmp = _tree.search_key(k);
				if (tmp == NULL)
				{
					_pair_type new_pair(ft::pair<key_type, mapped_type>(k, mapped_type()));
					return _tree.insert(new_pair)->_pair.second;
				}
				return tmp->_pair.second;
			}

			pair<iterator,bool> insert (const value_type& val)
			{
				// insert2(val);
				// return (ft::make_pair(iterator(), true));
				iterator it;
				nodePointer node_tmp = _tree.search_pair(val);
				if (node_tmp != NULL)
				{
					// it = find(val.first);
					return ft::make_pair(iterator(node_tmp), false);
				}
				else
				{
					// insert2(val);
					it = iterator(insert2(val));
					return (ft::make_pair(it, true));
				}

				// for (iterator it = _tree.begin(); it != _tree.end(); it++)
				// {
				// 	if (it.getPointer()->_pair.first == val.first)
				// 		return (ft::make_pair(it, true));
				// }
				// return (ft::make_pair(iterator(), true));
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
						if (it_tmp->first == val.first)
							return it_tmp;
						it_tmp++;
					}
					it_tmp = _tree.begin();
					while (it_tmp != _tree.end())
					{
						if (it_tmp->first == val.first)
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
					_tree.deleteNode(position.getPointer()->_pair.first);
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

			void swap (map& x)
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
					if (it->first == k)
						return it;
				return end();
			}

			const_iterator find (const key_type& k) const
			{
				for (const_iterator it = begin(); it != end(); ++it)
					if (it->first == k)
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
				while (_comp(it->first, k) && it != end())
					it++;
				return it;
			}
			const_iterator lower_bound (const key_type& k) const
			{
				const_iterator it = begin();
				while (_comp(it->first, k) && it != end())
					it++;
				return it;
			}

			iterator upper_bound (const key_type& k)
			{
				iterator it = begin();
				while (_comp(k, it->first) == false && it != end())
					it++;
				return it;
			}

			const_iterator upper_bound (const key_type& k) const
			{
				const_iterator it = begin();
				while (_comp(k, it->first) == false && it != end())
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
				RedBlackTree<Key, T> _tree;

				typedef	Node<key_type, mapped_type>		node;
				typedef Node<key_type, mapped_type>*	nodePointer;
				typedef	ft::pair<key_type, mapped_type> _pair_type;
				typedef	ft::pair<key_type, mapped_type>* _pair_type_ptr;
				key_compare _comp;

				nodePointer insert2(const value_type &value)
				{
					return _tree.insert(value);
				}

	};
}

#endif