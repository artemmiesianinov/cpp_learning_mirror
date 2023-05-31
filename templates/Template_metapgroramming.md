# Template metaprogramming

Template metaprogramming is a programming technique in which templates are used by a compiler to generate temporary source code, which is merged by the compiler with the rest of the source code and then compiled. The output of these templates include compile-time constants, data structures, and complete functions. The use of templates can be thought of as compile-time execution.
The syntax and idioms of template metaprogramming are esoteric compared to conventional C++ programming, and template metaprograms can be very difficult to understand.(??)

## SFINAE

Substitution failure is not an error (SFINAE) refers to a situation in C++ where an invalid substitution of template parameters is not in itself an error.
David Vandevoorde first introduced the acronym SFINAE to describe related programming techniques.
Specifically, when creating a candidate set for overload resolution, some (or all) candidates of that set may be the result of instantiated templates with (potentially deduced) template arguments substituted for the corresponding template parameters. If an error occurs during the substitution of a set of arguments for any given template, the compiler removes the potential overload from the candidate set instead of stopping with a compilation error, provided the substitution error is one the C++ standard grants such treatment. If one or more candidates remain and overload resolution succeeds, the invocation is well-formed.

## C++11 type_traits

The <type_traits> header defines a series of classes to obtain type information on compile-time. The header contains:

- helper classes: standard classes to assist in creating compile-time constants;
- type traits: classes to obtain characteristics of types in the form of compile-time constant values;
- type transformations: classes to obtain new types by applying specific transformations to existing types.

### type_traits example

```c++
template<typename T>
struct matrix_base
{
    using value_type = T;
    ...
    template <typename V = value_type>
    constexpr typename std::enable_if<std::is_integral<V>::value, bool>::type
    is_zero (size_t row, size_t column) const { return operator () (row, column) == 0;}

    template <typename V = value_type>
    constexpr typename std::enable_if<!std::is_integral<V>::value, bool>::type
    is_zero (size_t row, size_t column) const {return FP_ZERO == std::fpclassify (operator () (row, column) );}
};
```

## Template compilation model

Inclusion model (preferable).
Explicit instantiation.
Separate model (it is not supported by most compilers and deprecated in C++11).
