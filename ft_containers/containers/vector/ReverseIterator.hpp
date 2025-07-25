#ifndef ReverseVectorIterator_HPP
#define ReverseVectorIterator_HPP

#include "Traits.hpp"

namespace ft
{
	template <class Iterator, bool is_const_rev>
	class ReverseVectorIterator
	{
		public:
			typedef Iterator								iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;

			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;
			static const bool is_iter = true;

			ReverseVectorIterator(): _base_iterator(iterator_type()) {}
			explicit ReverseVectorIterator(iterator_type it): _base_iterator(it) {}
			virtual ~ReverseVectorIterator() {}
			template <class Rev_it>
			ReverseVectorIterator(const ReverseVectorIterator<Rev_it, false>& rev_it) { *this = rev_it; }
			template <class Rev_it>
			ReverseVectorIterator(const ReverseVectorIterator<Rev_it, true>& rev_it) { *this = rev_it; }
			template <class Rev_it>
			ReverseVectorIterator& operator=(const ReverseVectorIterator<Rev_it, false>& cp) { _base_iterator = cp.base(); return *this; }
			template <class Rev_it>
			ReverseVectorIterator& operator=(const ReverseVectorIterator<Rev_it, true>& cp) { _base_iterator = cp.base(); return *this; }

			template <class Rev_it>
			bool operator==(const ReverseVectorIterator<Rev_it, false>& b) const { return this->_base_iterator == b.base(); }
			template <class Rev_it>
			bool operator==(const ReverseVectorIterator<Rev_it, true>& b) const { return this->_base_iterator == b.base(); }
			template <class Rev_it>
			bool operator!=(const ReverseVectorIterator<Rev_it, false>& b) const { return this->_base_iterator != b.base(); }
			template <class Rev_it>
			bool operator!=(const ReverseVectorIterator<Rev_it, true>& b) const { return this->_base_iterator != b.base(); }

			template <class Rev_it>
			bool operator<(const ReverseVectorIterator<Rev_it, false>& b) const { return this->_base_iterator < b.base(); }
			template <class Rev_it>
			bool operator<(const ReverseVectorIterator<Rev_it, true>& b) const { return this->_base_iterator < b.base(); }
			template <class Rev_it>
			bool operator>(const ReverseVectorIterator<Rev_it, false>& b) const { return this->_base_iterator > b.base(); }
			template <class Rev_it>
			bool operator>(const ReverseVectorIterator<Rev_it, true>& b) const { return this->_base_iterator > b.base(); }
			template <class Rev_it>
			bool operator<=(const ReverseVectorIterator<Rev_it, false>& b) const { return this->_base_iterator <= b.base(); }
			template <class Rev_it>
			bool operator<=(const ReverseVectorIterator<Rev_it, true>& b) const { return this->_base_iterator <= b.base(); }
			template <class Rev_it>
			bool operator>=(const ReverseVectorIterator<Rev_it, false>& b) const { return this->_base_iterator >= b.base(); }
			template <class Rev_it>
			bool operator>=(const ReverseVectorIterator<Rev_it, true>& b) const { return this->_base_iterator >= b.base(); }

			iterator_type base() const { return _base_iterator; }
			reference operator*() const { return *_base_iterator; };
			ReverseVectorIterator operator+ (difference_type n) { _base_iterator -= n; return *this; }

			ReverseVectorIterator& operator++() { _base_iterator--; return *this; }
			ReverseVectorIterator  operator++(int) { ReverseVectorIterator tmp = *this; ++(*this); return tmp; }

			ReverseVectorIterator& operator+= (difference_type n) { _base_iterator -= n; return *this; }

			ReverseVectorIterator operator- (difference_type n) { _base_iterator += n; return *this; }

			ReverseVectorIterator& operator--() { _base_iterator++; return *this; }
			ReverseVectorIterator  operator--(int) { ReverseVectorIterator tmp = *this; --(*this); return tmp; }

			ReverseVectorIterator& operator-= (difference_type n) { _base_iterator += n; return *this; }

			pointer operator->() const { return _base_iterator; }
			reference operator[] (difference_type n) const { return *(_base_iterator + n); }

		private:
			iterator_type _base_iterator;

	};
}

#endif