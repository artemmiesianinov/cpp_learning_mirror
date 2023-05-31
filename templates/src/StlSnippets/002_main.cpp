// STL. Vector.
// CopyConstructible requirement.
// $ g++ -Wall -Wextra 002_main.cpp -o 002_main
#include <vector>
#include <memory>
#include <iostream>

struct Person
{
    Person () {};
    Person (const Person &) = delete;
    const char * name {nullptr};
};

int main (int, char **)
{
    std::vector <Person> v;
    // error: use of deleted function ‘Person::Person(const Person&)’.
    //v.push_back ({});
    
    std::vector <std::shared_ptr <Person> > p;
    p.push_back (std::make_shared <Person> () );

    return EXIT_SUCCESS;
}
