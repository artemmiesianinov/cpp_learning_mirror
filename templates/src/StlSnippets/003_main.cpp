// STL. List.
// List usage example. Erase elements from a list.
// $ g++ -Wall -Wextra 003_main.cpp -o 003_main
// $ ./003_main
#include <list>
#include <iostream>

// Helper.
void Print (const std::string & prefix, const std::list <int> & l)
{
    std::cout << prefix << std::endl;
    for (auto it = l.begin (); it != l.end (); ++it) {
        std::cout << * it;
    }
    std::cout << std::endl;
}

int main (int, char **)
{
    std::list <int> l {0, 4, 1, 2};
    Print ("Init.", l);

    l.remove (4);
    Print ("After remove.", l);

    return EXIT_SUCCESS;
}
