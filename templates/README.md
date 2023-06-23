# Generic Programming

Generic programming is a style of computer programming in which algorithms are written in terms of types to-be-specified-later that are then instantiated when needed for specific types provided as parameters.
C++ uses templates to enable generic programming techniques. The C++ Standard Library includes the Standard Template Library or STL that provides a framework of templates for common data structures and algorithms. Templates in C++ may also be used for template metaprogramming, which is a way of pre-evaluating some of the code at compile-time rather than run-time. Using template specialization, C++ Templates are considered Turing complete.
There are two kinds of templates: function templates and class templates.

## References

- C++ Templates: The Complete Guide, David Vandevoorde, Nicolai M.Josuttis, ISBN-13: 978-0201734843.
- Modern C++ Design: Generic Programming and Design Patterns Applied, Andrei Alexandrescu, ISBN-13: 978-0201704310
- The C++ Programming Language, 4th Edition, Bjarne Stroustrup, ISBN-13: 978-0321563842

## Defining Templates

A Template Definition starts with the keyword template, followed by a list of Template Parameters. What follows is then either a class definition, or a function definition, defining a class template or a function template respectively. The template parameters introduce names into the scope of the definition, which can be types, values or templates. These names can be used just like any other name of the same kind. Then, when the template is instantiated, real types, values or templates are substituted in place of these names, and the code compiled.

1. [Function Templates](Function_templates.md)
2. [Class Templates](./Class_templates.md)
3. [Template Metaprogramming](Template_metapgroramming.md)
4. [STL overview](./Stl.md)
