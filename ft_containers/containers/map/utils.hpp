#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>

namespace ft
{
	enum Color {RED, BLACK};

	template< bool Cond, class T = void >
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template <bool flag, class IsTrue, class IsFalse>
	struct condition_type_def;

	template <class IsTrue, class IsFalse>
	struct condition_type_def<true, IsTrue, IsFalse>
	{
		typedef IsTrue type;
	};

	template <class IsTrue, class IsFalse>
	struct condition_type_def<false, IsTrue, IsFalse>
	{
		typedef IsFalse type;
	};

	template <class T1, class T2>
	struct pair
	{
		public:
			// typedef	Node<Key, T>						node;
			// typedef	node*								nodePointer;
			typedef T1 first_type;
			typedef T2 second_type;

			first_type first;
			second_type second;

			pair(): first(), second() {}

			~pair() {}

			template<class U, class V>
			pair (const pair<U,V>& pr): first(pr.first), second(pr.second) {}

			pair (const first_type& a, const second_type& b): first(a), second(b) {}

			pair& operator= (const pair& pr)
			{
				if (*this == pr)
					return *this;

				first = pr.first;
				second = pr.second;
				return *this;
			}
	};

	template <class T1, class T2>  bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first == rhs.first) && (lhs.second == rhs.second);
	}
	template <class T1, class T2>  bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs == rhs);
	}
	template <class T1, class T2>  bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);
	}
	template <class T1, class T2>  bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(rhs<lhs);
	}
	template <class T1, class T2>  bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return rhs<lhs;
	}
	template <class T1, class T2>  bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs<rhs);
	}

	template <class Key, class T>
	struct Node
	{
		// pair<const Key, T>	value;
		pair<Key, T>	_pair;
		bool		color;
		Node		*left;
		Node		*right;
		Node		*parent;

		Node()
		: _pair(), color(RED), left(NULL), right(NULL), parent(NULL) {}

		virtual ~Node() {}

		Node(ft::pair<Key, T> val, Node *_parent = NULL,
				Node *_left = NULL, Node *_right = NULL, bool _color = RED)
		: _pair(val), color(_color), left(_left), right(_right), parent(_parent) {}

		// Node(ft::pair<const Key, T> val, Node *_parent = NULL,
		// 		Node *_left = NULL, Node *_right = NULL, bool _color = RED)
		// : _pair(val), _pair(val), color(_color), left(_left), right(_right), parent(_parent) {}

		Node(const Node& cp)
		: _pair(cp._pair), color(cp.color), left(cp.left), right(cp.right),
			parent(cp.parent) {}

		bool isOnLeft() { return this == parent->left; }

		Node *sibling()
		{
			if (parent == NULL)
				return NULL;
		
			if (isOnLeft())
				return parent->right;
		
			return parent->left;
  		}
	};

	template <class Arg1, class Arg2, class Result>
	struct binary_function
	{
		typedef Arg1 first_argument_type;
   		typedef Arg2 second_argument_type;
    	typedef Result result_type;
	};

	template< class T >
	struct less : binary_function<T, T, bool>
	{
		bool operator() (const T& x, const T& y) const { return x < y; }
	};

	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return ( pair<T1,T2>(x,y) );
	}

	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2 )
	{
		while (first1!=last1) {
			if (*first1 != *first2 || *last1 != *last2) return false;
			++first1; ++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2)
	{
		while (first1!=last1)
		{
			if (first2==last2 || *first2<*first1) return false;
			else if (*first1<*first2) return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}
}

#endif