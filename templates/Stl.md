# STL Overview

The Standard Template Library (STL) is a software library for the C++ programming language that influenced many parts of the C++ Standard Library. It provides four components called algorithms, containers, functions, and iterators.
The STL provides a set of common classes for C++, such as containers and associative arrays, that can be used with any built-in type and with any user-defined type that supports some elementary operations (such as copying and assignment). STL algorithms are independent of containers, which significantly reduces the complexity of the library.
The STL achieves its results through the use of templates. This approach provides compile-time polymorphism that is often more efficient than traditional run-time polymorphism. Modern C++ compilers are tuned to minimize abstraction penalties arising from heavy use of the STL.

## Containers

A container is a holder object that stores a collection of other objects (its elements). They are implemented as class templates, which allows a great flexibility in the types supported as elements.
The container manages the storage space for its elements and provides member functions to access them, either directly or through iterators (reference objects with similar properties to pointers).
Containers replicate structures very commonly used in programming: dynamic arrays (vector), queues (queue), stacks (stack), heaps (priority_queue), linked lists (list), trees (set), associative arrays (map)...
stack, queue and priority_queue are implemented as container adaptors. Container adaptors are not full container classes, but classes that provide a specific interface relying on an object of one of the container classes (such as deque or list) to handle the elements. The underlying container is encapsulated in such a way that its elements are accessed by the members of the container adaptor independently of the underlying container class used.

Sequence containers:                array, vector, deque, forward_list, list
Associative containers:             set, multiset, map, multimap
Unordered associative containers:   unordered_set, unordered_multiset, unordered_map, unordered_multimap
Container adaptors:                 stack, queue, priority_queue

Other: two class templates share certain properties with containers, and are sometimes classified with them: bitset and valarray.

### Containers Representation

A vector is most likely an array.
A list is most likely represented by a sequence of links pointing to the elements and the number of elements.
A forward_list is most likely represented by a sequence of links pointing the the elements.
A map is most likely implemented as a (balanced) tree of nodes pointing to (key, value) pairs. An unordered_map is most likely implemented as a hash table.
An array is simply a sequence of elements, with no handle.
There are some element requirements which may vary for different containers.

## Iterators

An iterator is any object that, pointing to some element in a range of elements (such as an array or a container), has the ability to iterate through the elements of that range using a set of operators (with at least the increment (++) and dereference (*) operators).

The most obvious form of iterator is a pointer: A pointer can point to elements in an array, and can iterate through them using the increment operator (++). But other kinds of iterators are possible. For example, each container type (such as a list) has a specific iterator type designed to iterate through its elements.

Notice that while a pointer is a form of iterator, not all iterators have the same functionality of pointers.

Depending on the properties supported by iterators, they are classified into five different categories:
Input and output iterators are the most limited types of iterators: they can perform sequential single-pass input or output operations.

Forward iterators have all the functionality of input iterators and -if they are not constant iterators- also the functionality of output iterators, although they are limited to one direction in which to iterate through a range (forward). All standard containers support at least forward iterator types.

Bidirectional iterators are like forward iterators but can also be iterated through backwards.

Random-access iterators implement all the functionality of bidirectional iterators, and also have the ability to access ranges non-sequentially: distant elements can be accessed directly by applying an offset value to an iterator without iterating through all the elements in between. These iterators have a similar functionality to standard pointers (pointers are iterators of this category).

## Algorithms

The header <algorithm> defines a collection of functions especially designed to be used on ranges of elements.
Non-modifying sequence operations; Modifying sequence operations; Partitions;
Sorting;
Binary search (operating on partitioned/sorted ranges); Merge (operating on sorted ranges);
Heap;
Min/max;
Other.

```c++
template <class InputIterator, class UnaryPredicate>
   InputIterator find_if (InputIterator first, InputIterator last, UnaryPredicate pred);
template <class ForwardIterator, class T>
  void fill (ForwardIterator first, ForwardIterator last, const T& val);
template <class RandomAccessIterator, class Compare>
  void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);
```

## Standard conversions

Standard conversions are implicit conversions with built-in meaning.
A standard conversion sequence is a sequence of standard conversions in the following order:

- Zero or one conversion from the following set: lvalue-to-rvalue conversion, array-to-pointer conversion, and function-to-pointer conversion.
- Zero or one conversion from the following set: integral promotions, floating-point promotion, integral conversions, floating-point conversions, floating-integral conversions, pointer conversions, pointer-to- member conversions, and boolean conversions.
- Zero or one function pointer conversion. - Zero or one qualification conversion.
