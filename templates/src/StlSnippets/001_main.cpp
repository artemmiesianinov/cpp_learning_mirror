// STL. Vector.
// Add ittems into a vector. Different ways how to iterate a vector.
// $ g++ -Wall -Wextra -std=c++11 001_main.cpp -o 001_main
// $ ./001_main
#include <vector>
#include <iostream>

int main (int, char **)
{
    std::vector <int> v;
    v.push_back (0);
    v.push_back (4);
    v.push_back (1);
    v.push_back (2);

    // Using index.
    std::cout << "1: ";
    for (size_t i = 0; i < v.size (); ++i) {
        std::cout << v [i];
    }
    std::cout << std::endl;

    // Using range-based for loop.
    std::cout << "2: ";
    for (int i : v) {
        std::cout << i;
    }
    std::cout << std::endl;

    // Almost the same as 2nd one.
    std::cout << "3: ";
    for (/*const*/ auto /*&*/ i : v) {
        std::cout << i;
    }
    std::cout << std::endl;

    // Using iterator.
    std::cout << "4: ";
    for (std::vector <int>::iterator i = v.begin (); i < v.end (); ++i) {
        std::cout << * i;
    }
    std::cout << std::endl;

    // Almost the same as 4th one.
    std::cout << "5: ";
    for (auto i = v.begin (); i != v.end (); ++i) {
        std::cout << * i;
    }
    std::cout << std::endl;

    // Using raw-pointer.
    std::cout << "6: ";
    for (size_t i = 0; i < v.size (); ++i) {
        std::cout << * (v.data () + i);
    }
    std::cout << std::endl;


    return EXIT_SUCCESS;
}
