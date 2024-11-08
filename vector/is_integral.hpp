#pragma once
namespace ft
{

	template <typename T>
	struct is_integral {
		static bool const value = false;
	};

	template<>
	struct is_integral<bool> {
		static const bool value = true;
	};

	template<>
	struct is_integral<int> {
		static const bool value = true;
	};

	template<>
	struct is_integral<char> {
		static const bool value = true;
	};

	template<>
	struct is_integral<short> {
		static const bool value = true;
	};

	template<>
	struct is_integral<long> {
		static const bool value = true;
	};

	template<>
	struct is_integral<long long> {
		static const bool value = true;
	};

	template<>
	struct is_integral<unsigned> {
		static const bool value = true;
	};

	template<>
	struct is_integral<unsigned char> {
		static const bool value = true;
	};

	template<>
	struct is_integral<unsigned short> {
		static const bool value = true;
	};

	template<>
	struct is_integral<unsigned long> {
		static const bool value = true;
	};

	template<>
	struct is_integral<unsigned long long> {
		static const bool value = true;
	};
}
