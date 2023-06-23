# Function Templates

A function template is a pattern for creating ordinary functions based upon the parameterizing types supplied when instantiated. Function templates provide a functional behavior that can be called for different types. In other words, a function template represents a family of functions. The representation looks a lot like an ordinary function, except that some elements of the function are left undetermined: these elements are parameterized.

Function templates are special functions that can operate with generic types. This allows us to create a function template whose functionality can be adapted to more than one type or class without repeating the entire code for each type.

In C++ this can be achieved using template parameters. A template parameter is a special kind of parameter that can be used to pass a type as argument: just like regular function parameters can be used to pass values to a function, template parameters allow to pass also types to a function. These function templates can use these parameters as if they were any other regular type.

The format for declaring function templates with type parameters is:

`template <class identifier> function_declaration;`
`template <typename identifier> function_declaration;`

## References

- [Template argument deduction](https://en.cppreference.com/w/cpp/language/template_argument_deduction)

## Source code examples

- [Example 1](./src/001_main.cpp)
- [Example 2](./src/002_main.cpp)

## Argument Deduction

In order to instantiate a function template, every template argument must be known ,but not every template argument has to be specified. When possible, the compiler will deduce the missing template arguments from the function arguments. This occurs when a function call is attempted, when an address of a function template is taken, and in some other contexts:

```c++
template<typename To, typename From>
To convert(From f);

void g(double d)
{
    int i = convert<int>(d);    // calls convert<int, double>(double)
    char c = convert<char>(d);  // calls convert<char, double>(double)
    int(*ptr)(float) = convert; // instantiates convert<int, float>(float)
                                // and stores its address in ptr
}
```

This mechanism makes it possible to use template operators, since there is no syntax to specify template arguments for an operator other than by re-writing it as a function call expression:

```c++
#include <iostream>

int main()
{
    std::cout << "Hello, world" << std::endl;
    // operator<< is looked up via ADL as std::operator<<,
    // then deduced to operator<<<char, std::char_traits<char>> both times
    // std::endl is deduced to &std::endl<char, std::char_traits<char>>
}
```

Template argument deduction takes place after the function template name lookup (which may involve argument-dependent lookup) and before template argument substitution (which may involve SFINAE) and overload resolution.

Template argument deduction is also performed when the name of a class template is used as the type of an object being constructed:

```c++

/* since C++17*/
std::pair p(2, 4.5);
std::tuple t(4, 3, 2.5);
std::copy_n(vi1, 3, std::back_insert_iterator(vi2));
std::for_each(vi.begin(), vi.end(), Foo([&](int i) {...}));
auto lck = std::lock_guard(foo.mtx);
std::lock_guard lck2(foo.mtx, ul);
```

Template argument deduction for class templates takes place in declarations and in explicit cast expressions.
See class template argument deduction for details.

## Function Templates Overloading

Can be overloaded

```c++
template <typename T>
void Swap (T & a, T & b)
{
    T c = a; a = b; b = c;
}

template <typename T>
void Swap (T * const a, T * const b)
{
    Swap(*a, *b);
}
```

