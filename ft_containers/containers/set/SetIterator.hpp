#ifndef SET_ITERATOR_HPP
#define SET_ITERATOR_HPP

#include "utils.hpp"
#include <iostream>
#include "setNode.hpp"

namespace ft
{
	template<class T, bool is_const>
	class SetIterator
	{
		public:
			typedef T									key_type;
			typedef	T									value_type_tmp;
			typedef typename condition_type_def<is_const, const value_type_tmp, value_type_tmp>::type value_type;
			typedef	SetNode<T>							node;
			typedef	node*								nodePointer;
			typedef	node&								node_reference;
			typedef	value_type*							pointer;
			typedef	value_type&							reference;

			static const bool is_iter_map = true;

		SetIterator(): _ptr(NULL), _last_ptr(NULL), _first_ptr(NULL), _is_end(0) {}

		virtual ~SetIterator()
		{
			if (_is_end == 1)
			{
				_alloc_node.destroy(_ptr);
				_alloc_node.deallocate(_ptr, 1);
			}
		}

		SetIterator(const nodePointer ptr): _ptr(ptr), _last_ptr(NULL), _first_ptr(NULL), _is_end(0) {}

		SetIterator(const nodePointer ptr, const nodePointer _begin, const nodePointer _end): _ptr(ptr), _is_end(0)
		{
			_last_ptr = _end;
			_first_ptr = _begin;
		}

		SetIterator(const nodePointer _begin, const nodePointer _end): _ptr(NULL), _is_end(0)
		{
			_last_ptr = _end;
			_first_ptr = _begin;
		}

		SetIterator(const SetIterator<key_type, false> &cp)
		{
			if (cp.getIsEnd() == 1)
			{
				nodePointer new_node = _alloc_node.allocate(1);
				_alloc_node.construct(new_node, node(*(cp.getPointer())));
				_ptr = new_node;
			}
			else
				_ptr = cp.getPointer();

			_last_ptr = cp.getLastPtr();
			_first_ptr = cp.getFirstPtr();
			_is_end = cp.getIsEnd();
		}

		SetIterator(const SetIterator<key_type, true> &cp)
		{
			if (cp.getIsEnd() == 1)
			{
				nodePointer new_node = _alloc_node.allocate(1);
				_alloc_node.construct(new_node, node(*(cp.getPointer())));
				_ptr = new_node;
			}
			else
				_ptr = cp.getPointer();

			_last_ptr = cp.getLastPtr();
			_first_ptr = cp.getFirstPtr();
			_is_end = cp.getIsEnd();
		}

		SetIterator &operator=(const SetIterator<key_type, false> &cp)
		{
			if (_is_end == 1)
			{
				_alloc_node.destroy(_ptr);
				_alloc_node.deallocate(_ptr, 1);
			}

			if (cp.getIsEnd() == 1)
			{
				nodePointer new_node = _alloc_node.allocate(1);
				_alloc_node.construct(new_node, node(*(cp.getPointer())));
				_ptr = new_node;
			}
			else
				_ptr = cp.getPointer();

			_last_ptr = cp.getLastPtr();
			_first_ptr = cp.getFirstPtr();
			_is_end = cp.getIsEnd();
			return *this;
		}

		SetIterator &operator=(const SetIterator<key_type, true> &cp)
		{
			if (_is_end == 1)
			{
				_alloc_node.destroy(_ptr);
				_alloc_node.deallocate(_ptr, 1);
			}

			if (cp.getIsEnd() == 1)
			{
				nodePointer new_node = _alloc_node.allocate(1);
				_alloc_node.construct(new_node, node(*(cp.getPointer())));
				_ptr = new_node;
			}
			else
				_ptr = cp.getPointer();

			_last_ptr = cp.getLastPtr();
			_first_ptr = cp.getFirstPtr();
			_is_end = cp.getIsEnd();
			return *this;
		}

		bool operator==(const SetIterator &cp) const
		{
			if (_ptr == NULL && cp.getPointer() == NULL)
				return 1;
			if (_ptr == NULL)
				return 0;
			if (_is_end == 1 && cp.getIsEnd() == 1)
				return 1;
			if (_is_end == 1 || cp.getIsEnd() == 1)
				return 0;
			return _ptr->_pair == cp.getPointer()->_pair;
		}
		bool operator!=(const SetIterator &cp) const
		{
			return !(*this == cp);
		}

		nodePointer getPointer() const { return _ptr; }
        SetIterator operator++(int)
		{
			SetIterator tmp;
			tmp.setIsEnd(0);
			tmp = *this;
			++(*this);
			return tmp;
		}
		SetIterator operator--(int)
		{
			SetIterator tmp;
			tmp.setIsEnd(0);
			tmp = *this;
			--(*this);
			return tmp;
		}
		SetIterator& operator++()
		{
			getNextNode();
			return *this;
		}
		SetIterator& operator--() { getPrevNode(); return *this; }

		reference operator*() { return _ptr->_pair; }
		reference operator*() const { return _ptr->_pair; }
        pointer operator->()
		{
			if (_ptr == NULL)
				throw std::invalid_argument("adress of node not valid");
			return (&_ptr->_pair);
		}
		pointer operator->() const
		{
			if (_ptr == NULL)
				throw std::invalid_argument("adress of node not valid");
			return (&_ptr->_pair);
		}

		void getBegin(size_t size)
		{
			if (size == 0)
			{
				nodePointer new_node = _alloc_node.allocate(1);
				_alloc_node.construct(new_node, node());
				new_node->parent = _last_ptr;
				_ptr = new_node;
				_is_end = 1;
			}
			else
				_ptr = _first_ptr;
		}
		void getEnd()
		{
			nodePointer new_node = _alloc_node.allocate(1);
			_alloc_node.construct(new_node, node());
			new_node->parent = _last_ptr;
			_ptr = new_node;
			_is_end = 1;
		}

		void setIsEnd(bool is_end) { _is_end = is_end; }
		nodePointer getLastPtr() const { return _last_ptr; }
		nodePointer getFirstPtr() const { return _first_ptr; }
		bool getIsEnd() const { return _is_end; }

		private:
			nodePointer	_ptr;
			nodePointer	_last_ptr;
			nodePointer	_first_ptr;
			bool		_is_end;
			std::allocator<SetNode<key_type> > _alloc_node;


			nodePointer getLeftMost(nodePointer _node)
			{
				if (_node == NULL)
					return NULL;
				while (_node->left != NULL)
					_node = _node->left;
				return _node;
			}

			nodePointer getRightMost(nodePointer _node)
			{
				if (_node == NULL)
					return NULL;
				while (_node->right != NULL)
					_node = _node->right;
				return _node;
			}

			void getNextNode()
			{
				if (_ptr == _last_ptr)
				{
					nodePointer new_node = _alloc_node.allocate(1);
					_alloc_node.construct(new_node, node());
					new_node->parent = _ptr;
					_is_end = 1;
					_ptr = new_node;
					return ;
				}
				if (_is_end == 1)
				{
					_is_end = 0;
					_alloc_node.destroy(_ptr);
					_alloc_node.deallocate(_ptr, 1);
					_ptr = _last_ptr;
					return ;
				}
				if (_ptr == NULL)
					std::cout << "ptr is null\n";
				if (_ptr->right != NULL)
					_ptr = getLeftMost(_ptr->right);
				else
				{
					while (_ptr->parent != NULL && _ptr == _ptr->parent->right)
						_ptr = _ptr->parent;
					_ptr = _ptr->parent;
				}
			}

			void getPrevNode()
			{
				if (_ptr == _first_ptr)
				{
					nodePointer new_node = _alloc_node.allocate(1);
					_alloc_node.construct(new_node, node());
					new_node->parent = _ptr;
					_is_end = 1;
					_ptr = new_node;
					return ;
				}
				if (_is_end == 1)
				{
					_is_end = 0;
					_alloc_node.destroy(_ptr);
					_alloc_node.deallocate(_ptr, 1);
					_ptr = _last_ptr;
					return ;
				}
				if (_ptr == NULL)
					return ;
				if (_ptr->left != NULL)
					_ptr = getRightMost(_ptr->left);
				else
				{
					while (_ptr->parent != NULL && _ptr == _ptr->parent->left)
						_ptr = _ptr->parent;
					_ptr = _ptr->parent;
				}
			}
	};
}

#endif