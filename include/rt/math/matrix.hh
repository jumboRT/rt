#ifndef RT_MATH_MATRIX_HH
#define RT_MATH_MATRIX_HH

#include "vector.hh" // FIXME: relative of absolute include paths?
#include <cstdint> // FIXME: std::size_t zit ook in <cstddef>
#include <algorithm>

// FIXME: moeten we tabs invoegen na een namespace?
// ik denk dat een extra level tabs niet heel erg is
// in c++17 kan "namespace rt::math {}" bijvoorbeeld indien nodig
namespace rt {

// FIXME: struct of class?
template<class T, std::size_t M, std::size_t N>
struct matrix {
	// FIXME: "vec" vind ik een beetje onduidelijk
	// als we de conventions van de stl willen behouden zou het iets worden als "vector_type"
	// maar ik denk dat het beter is als er "row" in voor komt om duidelijk te maken dat het row vectors zijn
	// misschien "row_vector" of "row_vector_type"
	// FIXME: ik denk wel dat het een goed idee is om meer van dit soort typedefs toe te voegen
	// misschien ook voor value_type, maar dat breekt de convention dat de index operator altijd value_type returned
	// kan ook voor "constexpr std::size_t rows = M; constexpr std::size_t colums = N;"
	// moet ik ook nog bij m'n vector erbij zetten dan maar totdat we eruit zijn hoe laat ik dat nog even
	using vec = vector<T, N>;
	// FIXME: moet rows private zijn?
	vec rows[M];

	// FIXME: uitzoeken wat handig is om met noexcept te doen
	// heb het voor nu in vector weggelaten
	constexpr matrix() noexcept = default;

	// FIXME: explicit?
	// FIXME: static_cast<>()?
	template<class U>
	constexpr matrix(const matrix<U, M, N> &other) noexcept {
		for (std::size_t row = 0; row < M; ++row)
			rows[row] = other[row];
	}

	constexpr vec& operator[](std::size_t idx) noexcept {
		return rows[idx];
	}

	constexpr const vec& operator[](std::size_t idx) const noexcept {
		return rows[idx];
	}

	// FIXME: static member of freestanding?
	// voordeel van static member is dat "T::identity()" werkt met generic T
	// maar ik denk niet dat we vaak een matrix T gaan hebben
	// de enige reden waarom we T zouden willen is als we niet zeker weten dat het een matrix is
	// als we niet zeker weten dat het een matrix is willen we ook geen identity() erop aanroepen
	// als we dat toch willen is het misschien beter om T::value_type, T::rows, T::columns te hebben en dan "rt::identity<T::value_type, T::rows, T::columns>()"
	// heb ergens een artiekel gelezen dat freestanding functions beter zijn maar kan me niet herinneren waarom
	static constexpr matrix identity() noexcept {
		// FIXME: matrix is niet zero initialized
		matrix result;
		// FIXME: std:: prefix voor functions kan problemen opleveren met generic arguments
		// is in dit geval geen probleem want de type van N en M is altijd std::size_t
		// maar voor vector had ik hetzelfde probleem met "min()" en daarvoor heb ik een "min()" gemaakt in rt namespace
		// denk dat het beter is om die overal te gebruiken
		// dan heb je ook niet de dure <algorithm> header nodig: c++ compile times are a pain in the ass
		for (auto idx = 0; idx < std::min(N, M); ++idx)
			result[idx][idx] = 1;
	}
};
/*
 * A B C	F
 * C D E	G
 *			H
 */

template<class T, class U, std::size_t M, std::size_t N, std::size_t P>
constexpr auto operator*(const matrix<T, M, N> &lhs, const matrix<U, N, P> &rhs) noexcept -> matrix<decltype(lhs[0][0] * rhs[0][0]), M, P> {
	//NOT DONE
	matrix<decltype(lhs[0][0] * rhs[0][0]), M, P> result;
	for (auto i = 0; i < P; ++i)
		for (auto j = 0; i < N; ++j)
			for (auto c = 0; i < N; ++j)
				result[j][i] += lhs[j][c] * rhs[c][i];
	return result;
}

// FIXME: is het een goed idee om dit te implementeren voor matrixen van verschillende types?
// denk juist dat explicit wel handig is zodat het echt duidelijk is dat er informatie verloren gaat door de comparison te down
// FIXME: freestanding of friend?
// ik heb altijd friend gedaan maar deze post suggereerd dat dit soort operators moeten worden geimplementeerd als "non-member" functions
// https://stackoverflow.com/questions/4421706/what-are-the-basic-rules-and-idioms-for-operator-overloading/4421729#4421729
// dit is eigenlijk een fixme voor vector.hh maar ik ben nu toch hier
// FIXME: als matrix geimplementeed is als "vector<vector<T, N>, M>" kan "return lhs.rows == rhs.rows;"
template<class T, class U, std::size_t M, std::size_t N>
constexpr bool operator==(const matrix<T, M, N> &lhs, const matrix<U, M, N> &rhs) noexcept {
	for (std::size_t row = 0; row < M; ++row)
		if (lhs[row] != rhs[row])
			return false;
	return true;
}

template<class T, class U, std::size_t M, std::size_t N>
constexpr bool operator!=(const matrix<T, M, N> &lhs, const matrix<U, M, N> &rhs) noexcept {
	return !(lhs == rhs);
}
// FIXME: twee keer "}" op dezelfde indentation ziet er raar uit
}

#endif
