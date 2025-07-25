#ifndef RANDOM_ACCESS_ITERATOR
#define RANDOM_ACCESS_ITERATOR

#include "Traits.hpp"
#include "../map/utils.hpp"

namespace ft
{
	template <class T, bool is_const>
	class VectorIterator
	{
		public:
			typedef typename std::random_access_iterator_tag iterator_category;
			typedef typename std::ptrdiff_t difference_type;
			typedef typename condition_type_def<is_const, const T, T>::type value_type;
			typedef value_type* pointer;
			typedef value_type& reference;
			static const bool is_iter = true;

			VectorIterator(): m_ptr(0) {}
			VectorIterator(pointer ptr): m_ptr(ptr) {}

			VectorIterator(const VectorIterator<T, false>& cp) { *this = cp; }
			VectorIterator(const VectorIterator<T, true>& cp) { *this = cp; }
			VectorIterator& operator=(const VectorIterator<T, false>& cp) { m_ptr = cp.getPtr(); return *this; }
			VectorIterator& operator=(const VectorIterator<T, true>& cp) { m_ptr = cp.getPtr(); return *this; }
			virtual ~VectorIterator() {}

			bool operator==(const VectorIterator<T, false>& b) const { return this->m_ptr == b.getPtr(); }
			bool operator==(const VectorIterator<T, true>& b) const { return this->m_ptr == b.getPtr(); }
        	bool operator!=(const VectorIterator<T, false>& b) const { return this->m_ptr != b.getPtr(); }
			bool operator!=(const VectorIterator<T, true>& b) const { return this->m_ptr != b.getPtr(); }

			reference operator*() const { return *m_ptr; }
        	pointer operator->() const { return m_ptr; }

			VectorIterator& operator++() { m_ptr++; return *this; }
        	VectorIterator operator++(int) { VectorIterator tmp = *this; ++(*this); return tmp; }

			VectorIterator& operator--() { m_ptr--; return *this; }
        	VectorIterator operator--(int) { VectorIterator tmp = *this; --(*this); return tmp; }

			VectorIterator operator+(difference_type val) { m_ptr += val; return *this; }
			VectorIterator operator-(difference_type val) { m_ptr -= val; return *this; }
			difference_type operator+(VectorIterator cp) const { return (cp.getPtr() + m_ptr); }
			difference_type operator-(VectorIterator cp) const { return (cp.getPtr() - m_ptr); }

			bool operator<(const VectorIterator<T, false>& b) const { return this->m_ptr < b.getPtr(); }
			bool operator<(const VectorIterator<T, true>& b) const { return this->m_ptr < b.getPtr(); }
			bool operator>(const VectorIterator<T, false>& b) const { return this->m_ptr > b.getPtr(); }
			bool operator>(const VectorIterator<T, true>& b) const { return this->m_ptr > b.getPtr(); }
			bool operator<=(const VectorIterator<T, false>& b) const { return this->m_ptr <= b.getPtr(); }
			bool operator<=(const VectorIterator<T, true>& b) const { return this->m_ptr <= b.getPtr(); }
			bool operator>=(const VectorIterator<T, false>& b) const { return this->m_ptr >= b.getPtr(); }
			bool operator>=(const VectorIterator<T, true>& b) const { return this->m_ptr >= b.getPtr(); }

			void operator+=(difference_type n) { m_ptr += n; }
			void operator-=(difference_type n) { m_ptr -= n; }

			value_type& operator[] (difference_type index) { return *(m_ptr + index); }
			pointer getPtr() const { return m_ptr; }
		private:
			pointer m_ptr;
	};
}

#endif