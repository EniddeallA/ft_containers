#pragma once

#include <iterator>
#include <stddef.h> 

namespace ft {
	template < 	typename Category, typename T, 
				typename Distance = ptrdiff_t,
				typename Pointer = T*, 
				typename Reference = T& 
				>
	struct iterator
	{
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};
}