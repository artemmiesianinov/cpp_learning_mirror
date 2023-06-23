// STL. Vector. Erase-remove idiom.
// $ g++ -Wall -Wextra 006_main.cpp -o 006_main
// $ ./006_main
#include <vector>
#include <algorithm>
#include <iostream>

// Helper.
void Print (const std::string & prefix, const std::vector <int> & v)
{
    std::cout << prefix << std::endl;
    for (size_t i = 0; i < v.size (); ++i) {
        std::cout << v [i];
    }
    std::cout << std::endl;
}

int main (int, char **)
{
    std::vector <int> v {0, 4, 1, 2};
    Print ("Init.", v);

    const auto x = std::remove (v.begin (), v.end (), 4);
    Print ("After remove.", v);

    v.erase (x, v.end () );
    Print ("After erase.", v);

    return EXIT_SUCCESS;
}
