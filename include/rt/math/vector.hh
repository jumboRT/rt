#ifndef RT_MATH_VECTOR_HH
#define RT_MATH_VECTOR_HH

#include "rt/math/math.hh" // FIXME: absolute of relative include paths?

#include <cstddef>

// FIXME: moeten we tabs invoegen na een namespace?
namespace rt {
	// FIXME: ff nadenken of iterators misschien niet toch een goed idee zijn
	// ook voor matrix

	// FIXME: struct of class?
	template<class T, std::size_t N>
	class vector {
	private:
		// FIXME: moet data public zijn?
		T data[N];
	public:
		// FIXME: member typedefs en constexprs voor value_type en size enzo
		// FIXME: noexcept zooi
		constexpr vector() = default;

		constexpr vector(const T& value) {
			// FIXME: "auto i = 0; ...", voordelen? nadelen? boeit het? waarschijnlijk niet...
			// kwestie van code style denk ik, even met daan overleggeni
			// auto is wel korter, leest misschien makkelijker
			for (std::size_t i = 0; i < N; i++) {
				data[i] = value;
			}
		}

		template<class U>
		constexpr explicit vector(const vector<U, N>& other) {
			for (std::size_t i = 0; i < N; i++) {
				data[i] = static_cast<T>(other[i]);
			}
		}

		constexpr T& operator[](std::size_t index) {
			return data[index];
		}

		constexpr const T& operator[](std::size_t index) const {
			return data[index];
		}

		// FIXME: friend of freestanding?
		constexpr friend bool operator==(const vector& lhs, const vector& rhs) {
			for (std::size_t i = 0; i < N; i++) {
				if (lhs[i] != rhs[i]) {
					return false;
				}
			}

			return true;
		}

		constexpr friend bool operator!=(const vector& lhs, const vector& rhs) {
			return !(lhs == rhs);
		}

		// FIXME: nadelen van implementeren als "0 - *this"?
		// word een andere operator gecalled, in theorie is huidige implementatie meer consequent
		constexpr vector operator-() const {
			vector result;

			for (std::size_t i = 0; i < N; i++) {
				result[i] = -data[i];
			}

			return result;
		}

		constexpr vector& operator+=(const vector& rhs) {
			for (std::size_t i = 0; i < N; i++) {
				data[i] += rhs[i];
			}

			return *this;
		}

		constexpr vector& operator-=(const vector& rhs) {
			for (std::size_t i = 0; i < N; i++) {
				data[i] -= rhs[i];
			}

			return *this;
		}

		constexpr vector& operator*=(const vector& rhs) {
			for (std::size_t i = 0; i < N; i++) {
				data[i] *= rhs[i];
			}

			return *this;
		}

		constexpr vector& operator/=(const vector& rhs) {
			for (std::size_t i = 0; i < N; i++) {
				data[i] /= rhs[i];
			}

			return *this;
		}

		// FIXME: friend of freestanding?
		constexpr friend vector operator+(vector lhs, const vector& rhs) {
			return lhs += rhs;
		}

		constexpr friend vector operator-(vector lhs, const vector& rhs) {
			return lhs -= rhs;
		}

		constexpr friend vector operator*(vector lhs, const vector& rhs) {
			return lhs *= rhs;
		}

		constexpr friend vector operator/(vector lhs, const vector& rhs) {
			return lhs /= rhs;
		}
	};

	// FIXME: helebool functies zijn hier alleen omdat ze in pbrt staan beschreven, misschien is de helft niet nodig

	// FIXME: kan die beter?
	// misschien met wat fancy c++17 features
	// zou fijn zijn om het in een constructor te proppen maar dan zit je te kloten met static_assert om te kijken of de hoeveelheid parameters wel overeenkomt met de size van de vector
	// hier is de size van de vector gewoon gelijk aan de hoeveelheid parameters
	// ook kut dat een parameter pack niet een fixed type kan hebben
	// misschien kan het beter met std::initializer_list?
	template<class T, class... Args>
	constexpr vector<T, sizeof...(Args)> make_vector(const Args&... args) {
		T data[] = { static_cast<T>(args)... };
		vector<T, sizeof...(Args)> result;

		for (std::size_t i = 0; i < sizeof...(Args); i++) {
			result[i] = data[i];
		}

		return result;
	}

	// FIXME: deze functie kan vec by value nemen dan is de interne "vector<T, N> result" niet nodig
	// voordelen: korter
	// nadelen: extra copy? word waarschijnlijk geoptimized, maar durf het niet met zekerheid te zeggen
	// benchmarks en godbolt zullen het weten
	template<class T, std::size_t N>
	constexpr vector<T, N> floor(const vector<T, N>& vec) {
		vector<T, N> result;

		for (std::size_t i = 0; i < N; i++) {
			result[i] = floor(vec[i]);
		}

		return vec;
	}

	template<class T, std::size_t N>
	constexpr vector<T, N> ceil(const vector<T, N>& vec) {
		vector<T, N> result;

		for (std::size_t i = 0; i < N; i++) {
			result[i] = ceil(vec[i]);
		}

		return vec;
	}

	template<class T, std::size_t N>
	constexpr vector<T, N> abs(const vector<T, N>& vec) {
		vector<T, N> result;

		for (std::size_t i = 0; i < N; i++) {
			result[i] = abs(vec[i]);
		}

		return vec;
	}

	template<class T, std::size_t N>
	constexpr vector<T, N> min(const vector<T, N>& lhs, const vector<T, N>& rhs) {
		vector<T, N> result;

		for (std::size_t i = 0; i < N; i++) {
			result[i] = min(lhs[i], rhs[i]);
		}

		return lhs;
	}

	template<class T, std::size_t N>
	constexpr vector<T, N> max(const vector<T, N>& lhs, const vector<T, N>& rhs) {
		vector<T, N> result;

		for (std::size_t i = 0; i < N; i++) {
			result[i] = max(lhs[i], rhs[i]);
		}

		return lhs;
	}

	template<class T, std::size_t N>
	constexpr std::size_t min_index(const vector<T, N>& vec) {
		std::size_t result = 0;

		for (std::size_t i = 1; i < N; i++) {
			if (vec[i] < vec[result]) {
				result = i;
			}
		}

		return result;
	}

	template<class T, std::size_t N>
	constexpr std::size_t max_index(const vector<T, N>& vec) {
		std::size_t result = 0;

		for (std::size_t i = 1; i < N; i++) {
			if (vec[i] > vec[result]) {
				result = i;
			}
		}

		return result;
	}

	template<class T, std::size_t N>
	constexpr T& min(vector<T, N>& vec) {
		return vec[min_index(vec)];
	}

	template<class T, std::size_t N>
	constexpr const T& min(const vector<T, N>& vec) {
		return vec[min_index(vec)];
	}

	template<class T, std::size_t N>
	constexpr T& max(vector<T, N>& vec) {
		return vec[max_index(vec)];
	}

	template<class T, std::size_t N>
	constexpr const T& max(const vector<T, N>& vec) {
		return vec[max_index(vec)];
	}

	// FIXME: gaan we ooit een sum(vector) nodig hebben?
	// zo ja; kan dit worden geimplementeerd als "sum(lhs * rhs)"
	template<class T, std::size_t N>
	constexpr T dot(const vector<T, N>& lhs, const vector<T, N>& rhs) {
		T result = 0;

		for (std::size_t i = 0; i < N; i++) {
			result += lhs[i] * rhs[i];
		}

		return result;
	}

	template<class T, std::size_t N>
	constexpr T abs_dot(const vector<T, N>& lhs, const vector<T, N>& rhs) {
		return abs(dot(lhs, rhs));
	}

	template<class T, std::size_t N>
	constexpr T length_squared(const vector<T, N>& vec) {
		return dot(vec, vec);
	}

	template<class T, std::size_t N>
	constexpr T length(const vector<T, N>& vec) {
		return sqrt(length_squared(vec));
	}

	template<class T, std::size_t N>
	constexpr T distance_squared(const vector<T, N>& lhs, const vector<T, N>& rhs) {
		return length_squared(lhs - rhs);
	}

	template<class T, std::size_t N>
	constexpr T distance(const vector<T, N>& lhs, const vector<T, N>& rhs) {
		return length(lhs - rhs);
	}

	template<class T, std::size_t N>
	constexpr vector<T, N> normalize(const vector<T, N>& vec) {
		return vec / length(vec);
	}

	template<class T>
	constexpr vector<T, 3> cross(const vector<T, 3>& lhs, const vector<T, 3>& rhs) {
		T x = lhs[1] * rhs[2] - lhs[2] * rhs[1];
		T y = lhs[2] * rhs[0] - lhs[0] * rhs[2];
		T z = lhs[0] * rhs[1] - lhs[1] * rhs[0];
		return make_vector<T>(x, y, z);
	}

	// FIXME: waar is permute voor nodig? 't is een soort van poor man's matrix
	template<class T, std::size_t N, std::size_t M>
	constexpr vector<T, M> permute(const vector<T, N>& lhs, const vector<std::size_t, M>& rhs) {
		vector<T, M> result;

		for (std::size_t i = 0; i < M; i++) {
			result[i] = lhs[rhs[i]];
		}

		return result;
	}

	// FIXME: waar is coordinate_system precies voor?
	template<class T>
	constexpr void coordinate_system(const vector<T, 3>& i, vector<T, 3>& j, vector<T, 3>& k) {
		if (abs(i[0]) > abs(i[1])) {
			j = normalize(make_vector<T>(-i[2], 0, i[0]));
		} else {
			j = normalize(make_vector<T>(0, i[2], -i[1]));
		}

		k = cross(i, j);
	}

	// FIXME: volgorde van arguments onduidelijk, betere namen?
	template<class T, std::size_t N>
	constexpr vector<T, N> face_forward(const vector<T, N>& lhs, const vector<T, N>& rhs) {
		return dot(lhs, rhs) < 0 ? -lhs : lhs;
	}
}

#endif
