#ifndef RT_UTIL_SPAN_HH
#define RT_UTIL_SPAN_HH

#include <cstddef>
#include <type_traits>
#include <iterator>

namespace rt {
	template<class T>
	class span {
	private:
		T* ptr;
		std::size_t length;
	public:
		typedef T element_type;
		typedef typename std::remove_cv<T>::type value_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef pointer iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;

		span(T* ptr, std::size_t length) : ptr(ptr), length(length) {}

		reference operator[](size_type index) {
			return ptr[index];
		}

		const_reference operator[](size_type index) const {
			return ptr[index];
		}

		size_type size() const {
			return length;
		}

		iterator begin() const {
			return ptr;
		}

		iterator end() const {
			return ptr + size();
		}

		reverse_iterator rbegin() const {
			return reverse_iterator(end());
		}

		reverse_iterator rend() const {
			return reverse_iterator(begin());
		}
	};
}

#endif
