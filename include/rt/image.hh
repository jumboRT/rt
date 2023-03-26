#ifndef RT_IMAGE_HH
#define RT_IMAGE_HH

#include <cstddef>
#include <vector>
#include "rt/util/span.hh"

namespace rt {

	template <class T>
	class image {
		private:
			std::vector<T> data;
			const std::size_t width = 0, height = 0;

		public:

			image() = delete;

			image(std::size_t width, std::size_t height, const T &value = T()) : width(width), height(height), data(width * height, value) {}

			template<class U>
			image(const image<U> other) : image(other.width, other.height, T()) {
			}

			const span<T> operator[](std::size_t index) const {
				return span<T>(data[width * index], width);
			}

			span<T> operator[](std::size_t index) {
				return span<T>(data[width * index], width);
			}
	};

}

#endif
