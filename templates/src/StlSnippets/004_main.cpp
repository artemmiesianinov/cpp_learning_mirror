// STL. Map.
// Compare requirement.
// $ g++ -Wall -Wextra -std=c++11 004_main.cpp -o 004_main
#include <map>
#include <string>
#include <iostream>

struct Id
{
    std::string prefix;
    unsigned number;
};

struct Person
{
    std::string name;
};

bool operator < (const Id & a, const Id & b)
{
    if (a.prefix == b.prefix) {
        return a.number < b.number;
    }
    return a.prefix < b.prefix;
}

int main (int, char **)
{
    std::map <Id, Person> m;
    m.insert ({ {"BC", 223355}, {} });
    m.insert ({ {"CD", 678543}, {} });

    return EXIT_SUCCESS;
}
