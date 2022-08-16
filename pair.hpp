#pragma once

namespace ft
{
	template <typename T1, typename T2>
	struct pair
	{
		typedef T1 type1;
		typedef T2 type2;

		type1 first;
		type2 second;

		pair() : first(), second() {}
		template <typename U, typename V>
		pair(const pair<U, V>& p) : 
			first(static_cast<type1>(p.first)), second(static_cast<type2>(p.second)) {}
		pair(const type1& p1, const type2& t2) :
			first(p1), second(p2)	{}
		pair& operator = (const pair& p)
		{
			this->first = p.first;
			this->second = p.second;
			return *this;
		}
		
	};
	template <typename T1, typename T2>
	bool operator== (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}
	template <typename T1, typename T2>
	bool operator!= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(lhs == rhs);
	}
	template <typename T1, typename T2>
	bool operator<  (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}
	template <typename T1, typename T2>
	bool operator<= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(rhs < lhs);
	}
	template <typename T1, typename T2>
	bool operator>  (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return rhs < lhs;
	}
	template <typename T1, typename T2>
	bool operator>= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(lhs < rhs);
	}

	template <typename T1, typename T2>
	pair<T1, T2> make_pair(T1 p1, T2 p2)
	{
		return (pair<T1, T2>(p1, p2));
	}

} // namespace ft
