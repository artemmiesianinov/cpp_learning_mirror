// STL. Algorithm.
// A few examples.
// $ g++ -Wall -Wextra 007_main.cpp -o 007_main
// $ ./007_main
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

// Helper.
void Print (const std::string & prefix, const std::vector <long> & v)
{
    std::cout << prefix << std::endl;
    for (size_t i = 0; i < v.size (); ++i) {
        std::cout << v [i];
    }
    std::cout << std::endl;
}

int main (int, char **)
{
    std::vector <long> v (10);
    Print ("Init.", v);

    std::fill (v.begin (), v.end (), 1);
    Print ("After fill.", v);

    const long s = std::accumulate (v.begin (), v.end (), 0, std::plus <long>{});
    std::cout << "Sum: " << s << std::endl;

    std::generate (v.begin (), v.end (), [](){static int cnt = 0; return ++cnt;});
    Print ("After generate.", v);

    const auto r = std::remove_if (v.begin (), v.end (), [](const long & v){return !(v % 3);});
    Print ("After remove.", v);

    v.erase (r, v.end () );
    Print ("After erase.", v);

    std::sort (v.begin (), v.end (), std::greater <long> {});
    Print ("After sort.", v);

    return EXIT_SUCCESS;
}
