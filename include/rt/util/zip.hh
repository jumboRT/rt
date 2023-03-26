#ifndef RT_UTIL_ZIP_HH
#define RT_UTIL_ZIP_HH

#include <tuple>
#include <iterator>
#include <utility>
#include <type_traits>

namespace rt {
	namespace detail {
		template<std::size_t... I>
		struct index_sequence {
		};

		template<std::size_t N, std::size_t... I>
		struct make_index_sequence : make_index_sequence<N - 1, N - 1, I...> {
		};

		template<std::size_t... I>
		struct make_index_sequence<0, I...> {
			typedef index_sequence<I...> type;
		};

		template <class T>
		struct select_iterator {
			typedef typename std::conditional<
				std::is_const<typename std::remove_reference<T>::type>::value,
				typename std::decay<typename T::const_iterator>::type,
				typename std::decay<typename T::iterator>::type>::type type;
		};
	}
	
	template <class... Iters>
	class zip_iterator {
		private:
				std::tuple<Iters...> iters;

		public:
		typedef std::tuple<typename std::iterator_traits<Iters>::value_type...> value_type;

		zip_iterator() = delete;
		zip_iterator(Iters &&...iters) : iters(iters...) {}

		zip_iterator& operator++() {
				for (auto &&iter : iters) {
						++iter;
				}
		}

		zip_iterator operator++(int) {
				const zip_iterator ret = *this;
				++*this;
				return ret;
		}

		bool operator==(const zip_iterator &other) const {
			return equal(other);
		}

		bool operator!=(const zip_iterator &other) const {
			return !(*this == other);
		}

		value_type operator*() {
			return deref(typename detail::make_index_sequence<sizeof...(Iters)>::type());
		}

		private:
		template<std::size_t... I>
		bool equal(const zip_iterator &other, detail::index_sequence<I...>) {
			return std::min({ (std::get<I>(iters) == std::get<I>(other.iters))... });
		}

		template<std::size_t... I>
		value_type deref(detail::index_sequence<I...>) {
			return std::make_tuple(*std::get<I>(iters)...);
		}
	};

	template <class... T>
	class zipper {
		private:
			std::tuple<T...> args;

		public:
		typedef zip_iterator<typename detail::select_iterator<T>::type...> iterator;

		template <class... Args>
		zipper(Args&& ...args): args(std::forward<Args>(args)...) {}

		iterator begin() {
			return _begin(typename detail::make_index_sequence<sizeof...(T)>::type());
		}

		iterator end() {
			return _end(typename detail::make_index_sequence<sizeof...(T)>::type());
		}

		private:
		template<std::size_t... I>
		iterator _begin(detail::index_sequence<I...>) {
			return iterator(std::begin(std::get<I>(args))...);
		}

		template<std::size_t... I>
		iterator _end(detail::index_sequence<I...>) {
			return iterator(std::end(std::get<I>(args))...);
		}
	};

	template <class... T>
	zipper<T...> zip(T&& ...t) {
		return zipper<T...>(std::forward<T>(t)...);
	}

}

#endif

#include <vector>
#include <iostream>

int main() {
	std::vector<int> vec1(50, 42);
	std::vector<float> vec2(50, 42);
	
	auto tmp = rt::zip(vec1, vec2);
	for (auto &&x : tmp) {}
	/*
	auto iter = rt::zip(vec1.begin(), vec2.begin());
	std::cout << std::get<0>(*iter) << std::endl;
	*/
}
