// STL. Map.
// Erase item from a map.
// $ g++ -Wall -Wextra 005_main.cpp -o 005_main
// $ ./005_main
#include <map>
#include <string>
#include <iostream>

// Helper.
void Print (const std::string & prefix, const std::map <int, std::string> & m)
{
    std::cout << prefix << std::endl;
    for (auto it = m.begin (); it != m.end (); ++it) {
        std::cout << it->first << ":" << it->second << " ";
    }
    std::cout << std::endl;
}


int main (int, char **)
{
    std::map <int, std::string> m {
        {1, "1st"}
      , {2, "2nd"}
      , {3, "3rd"}
    };
    m.insert ({4, "4th"});

    Print ("Init.", m);

    for (auto it = m.begin (); it != m.end ();) {
        if (it->first < 4) {
            it = m.erase (it);
        }
        else {
            ++it;
        }
    }

    Print ("After erase.", m);

    return EXIT_SUCCESS;
}
