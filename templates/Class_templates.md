# Class Templates

## Parametrized Types

Similar to functions, classes can also be parameterized with one or more types.
A class template provides a specification for generating classes based on parameters.
A class template is instantiated by passing a given set of types to it as template arguments.

```c++
template <typename T>
struct Serializer
{
    Serializer (T v) : value {v} {}
    char Data (unsigned);
    union {
    T value;
         char data [sizeof (T)];
     };
};
```

## Template class specialization

To define a member function of a class template, you have to specify that it is a function template, and you have to use the full type qualification of the class template.

```c++
template <typename T>
class Counter
{
public:
    Counter (T);
    bool Update (T);
    T Current () const {return count;}
private:
    T count;
};

template <typename T>
Counter<T>::Counter (T init)
    : count { init < T (0) ? T(0) : init}
{}

template <typename T>
bool Counter <T>::Update (T diff)
{
    if (diff < T (0)) return false;

    count += diff;

    return true;
}

template <>
Counter <unsigned>::Counter (unsigned init)
     : count {init}
{}
template <>
bool Counter <unsigned>::Update (unsigned diff)
{
    count += diff;
    return true;
}
```

## Template Class partial specialization

Class templates can be partially specialized. You can specify special implementations for particular circumstances,
but some template parameters must still be defined by the user.

## Default Template Arguments

Just as functions can have default values for their arguments, so can templates - indeed, this facility works in pretty much the same way. If a template parameter has a default specified, then all subsequent template parameters must also have a default specified. When referencing a template, parameters with default values can be omitted; if a template parameter is omitted, all subsequent template parameters must also be omitted.

## Template parameters

Templates can have one or more template parameters, which can be: - type parameters;

- non-type parameters (e.g. an integer);
- template parameters.

For function and class, template parameters don't have to be types. They can also be ordinary values. As with templates using type parameters, you define code for which a certain detail remains open until the code is used. However, the detail that is open is a value instead of a type. When using such a template, you have to specify this value explicitly. The resulting code then gets instantiated.
Note that non type template parameters carry some restrictions. In general, they may be constant integral values (including enumerations) or pointers to objects with external linkage. Floating-point numbers and class-type objects are not allowed as non type template parameters.
Template Parameters enable a template to be parameterized by the name of another template.

## Variadic Templates

[Example 5](./src/005_main.cpp)

```c++
template <typename T>
T Sum (T x)
{
    return x;
}

template <typename T, typename... U> T Sum (T x, U... y)
{
    return x + Sum (y...);
};
int main (int, char **)
{
    return Sum (1, 2, 3, 4);
}
```

## Function Objects

A function object allows an instance object of a class to be called or invoked as if it were an ordinary function. In C++ this is carried out by overloading operator(). The main benefit of using function objects is that they are objects and hence can contain state, either statically across all instances of the function objects or individually on a particular instance.

## Template Classes Example

- [Example 3](./src/003_main.cpp)

- [Example 4](./src/004_main.cpp)

```bash
 gdb -batch -ex "disassemble/rs _ZN7CounterIjE6UpdateEj" 004_main
 Dump of assembler code for function _ZN7CounterIjE6UpdateEj:
    0x000000000040055e <+0>:  55    push  %rbp
    0x000000000040055f <+1>:  48 89 e5    mov   %rsp,%rbp
    0x0000000000400562 <+4>:  48 89 7d f8 mov   %rdi,-0x8(%rbp)
    0x0000000000400566 <+8>:  89 75 f4    mov   %esi,-0xc(%rbp)
    0x0000000000400569 <+11>: 48 8b 45 f8 mov   -0x8(%rbp),%rax
    0x000000000040056d <+15>: 8b 10   mov (%rax),%edx
    0x000000000040056f <+17>: 8b 45 f4    mov   -0xc(%rbp),%eax
    0x0000000000400572 <+20>: 01 c2   add %eax,%edx
    0x0000000000400574 <+22>: 48 8b 45 f8 mov   -0x8(%rbp),%rax
    0x0000000000400578 <+26>: 89 10   mov %edx,(%rax)
    0x000000000040057a <+28>: b8 01 00 00 00    mov $0x1,%eax
    0x000000000040057f <+33>: 5d    pop   %rbp
    0x0000000000400580 <+34>: c3    retq
End of assembler dump.

$ gdb -batch -ex "disassemble/rs _ZN7CounterIdE6UpdateEd" 004_main
Dump of assembler code for function _ZN7CounterIdE6UpdateEd:
...
```

``` c++
template <class T>
T max (T a, T b) {
    return (a>b ? a : b);
}

int i = 10;
int j = 20;
int k = max<int>(10, 20);

template <class T, class U>
T max (T a, U b) {
    return (a>b ? a : b);
}

int i = 10;
long j = 20;
int k = max<int, long>(10, 20);
```

``` c++
template <class T>
class PlaybackBuffer {
public:
   PlaybackBuffer(int sample_rate, int channels, int bytes_per_sample)
           : mSize(kDefaultBufferSize), mTail(0), mBuffer(new T[mSize]) {
   }

   ~PlaybackBuffer() { delete[] mBuffer; }

   void put(T* buf, const size_t& size) {
       std::lock_guard<std::mutex> lock(mMutex);

       if ((size > mSize)) {
           return;
       }

       if (size > (mSize - mTail)) {
           const size_t bytesNeeded = size - (mSize - mTail);
           mTail -= bytesNeeded;
           memcpy(mBuffer, mBuffer + bytesNeeded, mTail);
       }

       memcpy(mBuffer + mTail, buf, size);
       mTail += size;
   }

size_t get(T* buf, const size_t& size) {
       if (buf == nullptr || size == 0) return 0;
       std::lock_guard<std::mutex> lock(mMutex);

       if (mTail == 0) {
              return 0;
          }

       if (mTail < size) {
           return 0;
       }

       if (mTail < mDelayBufferSize) {
              return 0;
       }

       memcpy(buf, mBuffer, size * sizeof(T));
       mTail -= size;
       memcpy(mBuffer, mBuffer + size, mTail * sizeof(T));
       return size;
   }

private:
   std::mutex mMutex;
   size_t mSize;
   size_t mTail;
   const size_t kDefaultBufferSize = 16384;
   T* mBuffer;
};
```

## typename vs class

[Class keyword is required for template template parameters](https://stackoverflow.com/a/2024173/3175480)

## Template project example

[Project Example](./src/munkres-cpp/src/munkres-cpp/munkres.h)
