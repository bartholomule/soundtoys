#pragma once

#include <type_traits>

namespace SoundToys
{
	namespace Traits
	{
		template <typename T>
		struct IsTrivialOrVoid
		{
			static const bool value = std::is_trivial<T>::value || std::is_void<T>::value;
		};
	}

	template <typename T>
	void safe_memzero(T* dest, size_t n)
	{
		static_assert(std::is_trivial<T>::value, "Cannot safely use memzero here");
		std::memset(static_cast<void*>(dest), 0, sizeof(T) * n);
	}

	template <typename T, size_t N>
	void safe_memzero(T(&t)[N])
	{
		static_assert(std::is_trivial<T>::value, "Cannot safely use memzero here");
		std::memset(static_cast<void*>(t), 0, sizeof(T) * N);
	}

	template <typename T>
	void safe_memzero(T& t)
	{
		static_assert(std::is_trivial<T>::value, "Cannot safely use memzero here");
		std::memset(static_cast<void*>(&t), 0, sizeof(t));
	}

	template <typename T1, typename T2>
	void* safe_memcpy(T1* dest, const T2* src, size_t count)
	{
		static_assert(Traits::IsTrivialOrVoid<T1>::value, "Cannot safely use memcpy here");
		static_assert(Traits::IsTrivialOrVoid<T2>::value, "Cannot safely use memcpy here");
		return std::memcpy(dest, src, count);
	}

	template <typename T1>
	void safe_memcpy(T1& dest, const T1& src)
	{
		static_assert(std::is_trivial<T1>::value, "Cannot safely use memcpy here");
		safe_memcpy(&dest, &src, sizeof(T1));
	}
}