#include "rt/math/vector.hh"
#include "rt/math/matrix.hh"
#include "rt/test/debug.hh"

#include <iostream>

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

// constexpr alleen waar het een duidelijk effect heeft:
// - in c++17 kan zo een beetje alles constexpr zijn, maar dat betekent niet dat alles ook echt op compile time runned
// - constexpr heeft niks met optimization te maken, het gaat alleen over of je de functie kan gebruiken in een constexpr context, zoals in een template parameter
// - tot c++20 kunnen we toch geen classes gebruiken als non-type template parameters
// - een constexpr template functie is in de meeste gevallen alsnog niet constexpr omdat de type het niet toe staat

// ik heb best lang nagedacht over make_vector, maar ik denk niet dat het beter kan
// er is "common_type" en "all_same" in type traits die gebruikt zouden kunnen worden voor meer type safety, en het lijkt alsof het beter zou moeten zijn met syntax ook, dan kan je "make_vector(0.1, 0.2, 0.3)" schrijven ipv "make_vector<float>(0.1, 0.2, 0.3)", maar dat is misleidend, "make_vector(0.1, 0.2, 0.3)" maakt nameklijk een vector van doubles, niet floats.

// heb ook een hele tijd nagedacht over typedefs en constexprs zoals "matrix::value_type" en "matrix::size", maar heb nog niets verzonnen waar ik tevreden mee ben. ik had eerder al geschreven dat deze eigenlijk alleen nuttig zijn als je niet zeker bent van type, en om het dan te kunnen gebruiken moeten alle types die het zouden kunnen zijn dezelfde interface hebben. als we consequent willen zijn met de interface van de stl dan zou "matrix::value_type" een vector moeten zijn, want dat is de return value van de index operator, maar dat is niet heel logisch voor een matrix. ook zou "matrix::size" niet een constexpr variable maar een constexpr function moeten zijn, "matrix::size()" dus, maar de size van een matrix zijn 2 getallen, misschien std::pair<std::size_t, std::size_t>, maar dat kan je niet gebruiken als index in een for loop. denk dat we hiermee moeten wachten totdat we er een use case voor hebben en dan doen wat daar handig voor is.

// voor de return type van de coordinate_system functie (inmiddels hernoemd naar "tangents") zou het leuk zijn om een std::tuple<vector, vector> te gebruiken, maar ik denk dat deze functie in de meeste gevallen gebruikt gaat worden om waardes in een struct te zetten:
//     struct basis {
//         vector<float, 3> i, j, k;
//     };
//
//     basis b;
//     b.i = normalize(make_vector<float>(1, 2, 3));
//     tangents(b.i, b.j, b.k);
// en dit werkt niet als je een tuple returned, omdat je voor structured bindings alleen nieuwe variables kan gebruiken, dus dit gaat niet:
//     auto [b.j, b.k] = tangents(b.i);
// het moet zo
//     auto [j, k] = tangents(b.i);
//     b.j = j;
//     b.k = k;
// en dan is by reference toch beter denk ik

// TODO: __device__ voor cuda
// TODO: testing framework
// TODO: quaternions (lijken heel erg op 4d vectors)
// TODO: matrix construction (row, column, casting, translation, scale, rotation)
// TODO: betere matrix inverse

int main() {
	rt::matrix<float, 2, 2> mat;

	mat[0] = rt::make_vector<float>(1, 3);
	mat[1] = rt::make_vector<float>(2, 4);

	std::cout << inverse(mat) << std::endl;
}
