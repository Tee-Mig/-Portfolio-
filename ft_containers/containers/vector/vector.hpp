#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <sstream>
#include <iostream>
#include <iterator>
#include "VectorIterator.hpp"
#include "ReverseIterator.hpp"
#include "../map/utils.hpp"
#include <exception>

namespace ft
{
	class EmptyVector: public std::exception
	{
		const char * what () const throw ()
		{
      		return "empty vector";
		}
	};

	template <class T, class Alloc = std::allocator<T>	> 
	class vector
	{
		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;

			typedef typename ft::VectorIterator<value_type, false> iterator;
			typedef typename ft::VectorIterator<value_type, true> const_iterator;
			typedef typename ft::ReverseVectorIterator<iterator, false> reverse_iterator;
			typedef typename ft::ReverseVectorIterator<const_iterator, true> const_reverse_iterator;
			typedef typename std::ptrdiff_t difference_type;
			typedef std::size_t size_type;

			explicit vector(const allocator_type& alloc = allocator_type()): _alloc(alloc), _capacity(0), _size(0), _begin(NULL), _end(NULL) {};

			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _alloc(alloc), _capacity(n), _size(n)
			{
				_begin = _alloc.allocate(n);
				_end = _begin;
				for (size_type i = 0; i < n; i++)
				{
					_alloc.construct(_end, val);
					_end++;
				}
			};

			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<InputIterator::is_iter, InputIterator>::type = 0):_alloc(alloc), _capacity(0), _size(0)
			{
				while (first != last)
				{
					push_back(*first);
					first++;
				}
			}

			vector (const vector& x): _alloc(x._alloc), _capacity(0), _size(0)
			{
				if (x.size() > 0)
					*this = x;
			}

			vector& operator= (const vector& x)
			{
				clear();
				if (x.size() > 0)
				{
					for (const_iterator it = x.begin(); it != x.end(); ++it)
						push_back(*it);
				}
				return (*this);
			}

			virtual ~vector()
			{
				if (_capacity > 0)
				{
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(_begin + i);
					_alloc.deallocate(_begin, _capacity);
				}
			};

			iterator begin() { return iterator(_begin); };
			const_iterator begin() const { return const_iterator(_begin); }

			iterator end() { return iterator(_end); };
			const_iterator end() const { return const_iterator(_end); }

			reverse_iterator rbegin() { return reverse_iterator(_end - 1); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(_end - 1);}

			reverse_iterator rend() { return reverse_iterator(_begin - 1); }
			const_reverse_iterator rend() const { return const_reverse_iterator(_begin - 1); }

			size_type size() const { return _size; }

			size_type max_size() const {return _alloc.max_size(); }

			void resize (size_type n, value_type val = value_type())
			{
				if (n < _size)
				{
					pointer tmp_begin, tmp_end;
					tmp_begin = _alloc.allocate(_capacity);
					tmp_end = tmp_begin;
					for (size_type i = 0; i < n; i++)
					{
						_alloc.construct(tmp_end, *(_begin + i));
						tmp_end++;
					}
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(_begin + i);
					_alloc.deallocate(_begin, _capacity);
					_size = n;
					_begin = tmp_begin;
					_end = tmp_end;
				}
				else if (n > _size)
				{
					while (_size < n)
						push_back(val);
				}
			}

			size_type capacity() const
			{
				return (_capacity);
			}

			bool empty() const
			{
				if (_size == 0)
					return true;
				return false;
			}

			void reserve (size_type n)
			{
				if (n > _capacity)
				{
					pointer tmp_begin, tmp_end;
					tmp_begin = _alloc.allocate(n);
					tmp_end = tmp_begin;
					for (size_type i = 0; i < _size; i++)
					{
						_alloc.construct(tmp_end, *(_begin + i));
						_alloc.destroy(_begin + i);
						tmp_end++;
					}
					if (_capacity > 0)
						_alloc.deallocate(_begin, _capacity);
					_capacity = n;
					_begin = tmp_begin;
					_end = tmp_end;
				}
			}

			reference operator[] (size_type n)
			{
				if (n < 0 || n >= _size)
				{
					std::stringstream errMsg;
					errMsg << "element at index " << n << " is out of range(" << _size << ")";
					throw (std::out_of_range(errMsg.str().c_str()));
				}
				return *(_begin + n);
			}
			const_reference operator[] (size_type n) const
			{
				if (n < 0 || n >= _size)
				{
					std::stringstream errMsg;
					errMsg << "element at index " << n << " is out of range(" << _size << ")";
					throw (std::out_of_range(errMsg.str().c_str()));
				}
				return *(_begin + n);
			}

			reference at (size_type n)
			{
				if (n < 0 || n >= _size)
				{
					std::stringstream errMsg;
					errMsg << "element at index " << n << " is out of range(" << _size << ")";
					throw (std::out_of_range(errMsg.str().c_str()));
				}
				return *(_begin + n);
			}
			const_reference at (size_type n) const
			{
				if (n < 0 || n >= _size)
				{
					std::stringstream errMsg;
					errMsg << "element at index " << n << " is out of range(" << _size << ")";
					throw (std::out_of_range(errMsg.str().c_str()));
				}
				return *(_begin + n);
			}

			reference front()
			{
				if (_size > 0)
					return (*_begin);
				throw (std::out_of_range("Vector is empty"));
			}
			const_reference front() const
			{
				if (_size > 0)
					return (*_begin);
				throw (std::out_of_range("Vector is empty"));
			}

			reference back()
			{
				if (_size > 0)
					return (*(_end - 1));
				throw (std::out_of_range("Vector is empty"));
			}

			const_reference back() const
			{
				if (_size > 0)
					return (*(_end - 1));
				throw (std::out_of_range("Vector is empty"));
			}

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last,
							typename ft::enable_if<InputIterator::is_iter, InputIterator>::type = 0)
			{
				clear();
				for (iterator it = first; it != last; it++)
					push_back(*it);
			}
			void assign (size_type n, const value_type& val)
			{
				clear();
				for (size_type i = 0; i < n; i++)
					push_back(val);
			}

			void push_back(const value_type& val)
			{
				if (_size == _capacity || size() == 0)
					_extend_capacity();
				_alloc.construct(_end, val);
				_end++;
				_size++;
			}

			void pop_back()
			{
				if (_size > 0)
				{
					_end--;
					_alloc.destroy(_end);
					_size--;
				}
			}

			iterator insert (iterator position, const value_type& val)
			{
				(void)position;
				(void)val;
				difference_type diff = begin() - position;
				iterator it_diff = begin() + diff;
				
				if (size() != 0)
				{
					vector	tmp(it_diff, end());
					if (_size == _capacity)
						_extend_capacity();

					for (size_t i = 0; i < tmp.size(); i++)
						pop_back();
					push_back(val);
					iterator it = tmp.begin();
					for (size_t i = 0; i < tmp.size(); i++, it++)
						push_back(*it);
				}
				else
					push_back(val);
				return begin() + diff;
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				difference_type diff = begin() - position;
				iterator it_diff = begin() + diff;
				if (size() != 0)
				{
					vector	tmp(it_diff, end());

					while ((_size + n) > _capacity)
						_extend_capacity();
					for (size_t i = 0; i < tmp.size(); i++)
						pop_back();
					for (size_type i = 0; i < n; i++)
						push_back(val);
					iterator it = tmp.begin();
					for (size_t i = 0; i < tmp.size(); i++, it++)
						push_back(*it);
				}
				else
					push_back(val);
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,
							typename ft::enable_if<InputIterator::is_iter, InputIterator>::type = 0)
			{
				difference_type diff = begin() - position;
				iterator it_diff = begin() + diff;
				vector	tmp(it_diff, end());

				difference_type len = first - last;

				while ((_size + len) > _capacity)
					_extend_capacity();

				for (size_t i = 0; i < tmp.size(); i++)
					pop_back();

				while (first != last)
					push_back(*first++);

				iterator it = tmp.begin();
				for (size_t i = 0; i < tmp.size(); i++, it++)
					push_back(*it);
			}

			iterator erase (iterator position)
			{
				difference_type diff = begin() - position;
				iterator it_diff = begin() + diff;
				vector	tmp(it_diff, end());

				for (size_t i = 1; i < tmp.size(); i++)
					pop_back();
				pop_back();
				iterator it = tmp.begin();
				it++;
				for (size_t i = 1; i < tmp.size(); i++, it++)
					push_back(*it);
				return position;
			}
			iterator erase (iterator first, iterator last)
			{
				iterator tmp(first);
				while (tmp != last)
				{
					erase(first);
					tmp++;
				}
				return first;
			}

			void swap (vector& x)
			{
				pointer tmp_begin = x._begin;
				pointer tmp_end = x._end;
				size_t tmp_size = x._size;
				size_t tmp_capacity = x._capacity;
				allocator_type tmp_alloc = x._alloc;

				x._begin = _begin;
				x._end = _end;
				x._size = _size;
				x._capacity = _capacity;
				x._alloc = _alloc;

				_begin = tmp_begin;
				_end = tmp_end;
				_size = tmp_size;
				_capacity = tmp_capacity;
				_alloc = tmp_alloc;
			}

			void clear()
			{
				if (_capacity > 0)
				{
					for (size_type i = 0; i < _size; i++)
					{
						_end--;
						_alloc.destroy(_end);
					}
					_size = 0;
				}
			}

			allocator_type get_allocator() const
			{
				return (allocator_type());
			}


		private:
			allocator_type		_alloc;
			size_type			_capacity;
			size_type			_size;
			pointer				_begin;
			pointer				_end;

			void _extend_capacity()
			{
				if (_capacity == 0)
				{
					_capacity = 1;
					_begin = _alloc.allocate(_capacity);
					_end = _begin;
				}
				else
				{
					pointer tmp_begin, tmp_end;
					_capacity *= 2;
					tmp_begin = _alloc.allocate(_capacity);
					tmp_end = tmp_begin;
					for (size_type i = 0; i < _size; i++)
					{
						_alloc.construct(tmp_end, *(_begin + i));
						_alloc.destroy(_begin + i);
						tmp_end++;
					}
					_alloc.deallocate(_begin, _capacity / 2);
					_begin = tmp_begin;
					_end = tmp_end;
				}
			}
	};

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		typename vector<T, Alloc>::const_iterator it_lhs = lhs.begin();
		typename vector<T, Alloc>::const_iterator it_rhs = rhs.begin();
		while ((it_lhs != lhs.end()) && (it_rhs != rhs.end()) && (*it_lhs == *it_rhs))
		{
			it_lhs++;
			it_rhs++;
		}
		if (it_lhs != lhs.end() || it_rhs != rhs.end())
			return false;
		return true;
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		typename vector<T, Alloc>::const_iterator it_lhs = lhs.begin();
		typename vector<T, Alloc>::const_iterator it_rhs = rhs.begin();
		for (; (it_lhs != lhs.end()) && (it_rhs != rhs.end()); ++it_lhs, (void) ++it_rhs)
		{
			if (*it_lhs == *it_rhs)
				continue;
			if (*it_lhs < *it_rhs)
				return true;
			if (*it_lhs > *it_rhs)
				return false;
		}
	
		return (it_lhs == lhs.end()) && (it_rhs != rhs.end());
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif