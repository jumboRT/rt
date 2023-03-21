#include "rt/math/vector.hh"
#include "rt/math/matrix.hh"
#include "rt/test/debug.hh"

// auto is niet handig:
// - "for (auto i = 0; i < std::size_t(N); i++)" is nog steeds een int

// absolute includes zijn beter:
// - dezelfde file heeft overal dezelfde include naam

// indentation in namespace is beter:
// - overal indentation na braces is meer consequent
// - makkelijker te lezen met meerdere classes per file
// - dit ziet er raar uit:
// }
//
// }

// classes zijn beter dan structs:
// - private by default zorgt voor betere abstraction
// - forceerd je erover na te denken voordat je implementation details public maakt

// noexcept (in ieder geval voor templates) is een slecht idee:
// - als een functie van de generic type throwed called het std::terminate
// - conditional noexcept overal is te veel moeite
// - optimizations zijn niet significant

// default assignment operator is prima

// (sommige) operators kunnen beter als friend:
// - "vector * scalar" heeft anders een extra overload nodig
// - "vector == 0" ook
// - https://stackoverflow.com/questions/4421706/what-are-the-basic-rules-and-idioms-for-operator-overloading

// andere functions kunnen beter freestanding:
// - generic type inference voor return type
// - argument dependent lookup https://en.cppreference.com/w/cpp/language/adl

// "&" aan de kant van de type: "int& foo;" ipv "int &foo;"

// binary functions niet generic over bijde operands:
// - makkelijk om fouten mee te maken
// - "fvec3 * fvec3; fvec3 * ivec3;" synthesized naar 2 *verschillende* functies
// - "fvec3 * fvec3; fvec3 * vector<float, 3>(ivec3)" is maar 1 functie
// - explicit casting

// const reference is beter dan value *behalve* als de reference alleen word gebruikt om een kopie te maken
// - value in operator+, anders heb je "vector(lhs) += rhs"
// - const reference in "abs", anders maak je voor niks een kopie

// naming conventions voor simpele functies:
// - een enkel argument: "arg"
// - twee arguments, volgorde maakt niet uit of is duidelijk: "a", "b"
// - temporary local voor return value: "out"
// - index die niet word gebruikt in loop: "index"

// TODO: typedefs en constexprs
// TODO: __device__ voor cuda
// TODO: return type van "make_tangents"
// TODO: betere "make_vector" (rvalue reference? metaprogramming magic?)
// TODO: testing framework
// TODO: nut van overal constexpr? floating point operators zijn namelijk niet constexpr

#include <iostream>

int main() {
	rt::matrix<float, 4, 4> identity = 1;

	std::cout << identity << std::endl;
}
