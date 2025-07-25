#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft
{
    template <class T>
    struct iterator_traits
	{
        typedef typename T::iterator_category     iterator_category;
        typedef typename T::value_type            value_type;
        typedef typename T::difference_type       difference_type;
        typedef typename T::pointer               pointer;
        typedef typename T::reference             reference;
    };

	struct true_type { static const bool value = true; };

	struct false_type { static const bool value = false; };

	template <class T>
	struct is_integral: public false_type {};

	template<>
	struct is_integral<bool>: public true_type {};

	template<>
	struct is_integral<char>: public true_type {};

	template<>
	struct is_integral<wchar_t>: public true_type {};

	template<>
	struct is_integral<signed char>: public true_type {};

	template<>
	struct is_integral<short int>: public true_type {};

	template<>
	struct is_integral<int>: public true_type {};

	template<>
	struct is_integral<long int>: public true_type {};

	template<>
	struct is_integral<long long int>: public true_type {};

	template<>
	struct is_integral<unsigned char>: public true_type {};

	template<>
	struct is_integral<unsigned short int>: public true_type {};

	template<>
	struct is_integral<unsigned int>: public true_type {};

	template<>
	struct is_integral<unsigned long int>: public true_type {};

	template<>
	struct is_integral<unsigned long long int>: public true_type {};
}

#endif