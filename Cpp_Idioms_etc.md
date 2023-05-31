# C++ Idioms and few other topics

## Template Classes

Function templates are special functions that can operate with generic types. This allows us to create a function template whose functionality can be adapted to more than one type or class without repeating the entire code for each type.

In C++ this can be achieved using template parameters. A template parameter is a special kind of parameter that can be used to pass a type as argument: just like regular function parameters can be used to pass values to a function, template parameters allow to pass also types to a function. These function templates can use these parameters as if they were any other regular type.

The format for declaring function templates with type parameters is:

`template <class identifier> function_declaration;`
`template <typename identifier> function_declaration;`

The only difference between both prototypes is the use of either the keyword class or the keyword typename. Its use is indistinct, since both expressions have exactly the same meaning and behave exactly the same way.

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

## PIMPL

"Pointer to implementation" or "pImpl" is a C++ programming technique that removes implementation details of a class from its object representation by placing them in a separate class, accessed through an opaque pointer:

``` c++
#include “gadget.h”
#include <string>
#include <vector>

class Widget
{
public:
    Widget();
private:
    std::string name ;
    std::vector<double> data ;
    Gadget g1, g2, gЗ ; // user defined class
};

class Widget {
public:
   Widget();
   ~Widget();
private:

   // forward declaration
   struct Impl;
   Impl *pImpl;
};
```

``` c++
/* widget.cpp */
#include "widget.h"
#include “gadget.h”
#include <string>
#include <vector>

struct Widget::Impl
{
    std::string name;
    std::vector<double> data;
    Gadget g1, g2, gЗ;
};

Widget::Widget()
: pImpl (new Impl) {}

Widget::~Widget() {
   delete pImpl;
}
```

## RAII

Resource Acquisition Is Initialization or RAII, is a C++ programming technique which binds the life cycle of a resource that must be acquired before use (allocated heap memory, thread of execution, open socket, open file, locked mutex, disk space, database connection — anything that exists in limited supply) to the lifetime of an object.


RAII guarantees that the resource is available to any function that may access the object (resource availability is a class invariant, eliminating redundant runtime tests). It also guarantees that all resources are released when the lifetime of their controlling object ends, in reverse order of acquisition. Likewise, if resource acquisition fails (the constructor exits with an exception), all resources acquired by every fully-constructed member and base subobject are released in reverse order of initialization. This leverages the core language features (object lifetime, scope exit, order of initialization and stack unwinding) to eliminate resource leaks and guarantee exception safety. Another name for this technique is Scope-Bound Resource Management (SBRM), after the basic use case where the lifetime of an RAII object ends due to scope exit.
RAII can be summarized as follows:

1) encapsulate each resource into a class, where
    - the constructor acquires the resource and establishes all class invariants or throws an exception if that cannot be done,
    - the destructor releases the resource and never throws exceptions;always use the resource via an instance of a RAII-class that either

2) always use the resource via an instance of a RAII-class that either
    - has automatic storage duration or temporary lifetime itself, or
    - has lifetime that is bounded by the lifetime of an automatic or temporary object

Move semantics make it possible to safely transfer resource ownership between objects, across scopes, and in and out of threads, while maintaining resource safety.

Classes with `open()/close()`, `lock()/unlock()`, or `init()/copyFrom()/destroy()` member functions are typical examples of non-RAII classes

``` c++
std::mutex m;

void bad()
{
    m.lock();                        // acquire the mutex
    f();                             // if f() throws an exception, the mutex is never released
    if(!everything_ok()) return;     // early return, the mutex is never released
    m.unlock();                     // if bad() reaches this statement, the mutex is released
}

void good()
{
    std::lock_guard<std::mutex> lk(m); // RAII class: mutex acquisition is initialization
    f();                               // if f() throws an exception, the mutex is released
    if(!everything_ok()) return;       // early return, the mutex is released
}
```

## std::ostringstream

Output stream class to operate on strings.

Objects of this class use a string buffer that contains a sequence of characters. This sequence of characters can be accessed directly as a string object, using member str()

Characters can be inserted into the stream with any operation allowed on output streams.
``` c++
   std::ostringstream outstr;
   double price = 380.0;
   char* ps = " for a copy of the ISO/EIC C++ standard!";
   outstr.precision(2);
   outstr << std::fixed;
   outstr << "Pay only CHF " << price << ps << std::endl;
   std::string str = outstr.str();
   std::cout << str;

   //output: Pay only CHF 380.00 for a copy of the ISO/EIC C++ standard!
```

## Input and output with files

C++ provides the following classes to perform output and input of characters to/from files:

**ofstream**: Stream class to write on files
**ifstream**: Stream class to read from files
**fstream**: Stream class to both read and write from/to files.

An open file is represented within a program by a stream (i.e., an object of one of these classes) and any input or output operation performed on this stream object will be applied to the physical file associated to it.

For ifstream and ofstream classes, ios::in and ios::out are automatically and respectively assumed, even if a mode that does not include them is passed as second argument to the open member function (the flags are combined).

For fstream, the default value is only applied if the function is called without specifying any value for the mode parameter. If the function is called with any value in that parameter the default mode is overridden, not combined.

File streams opened in binary mode perform input and output operations independently of any format considerations. Non-binary files are known as text files, and some translations may occur due to formatting of some special characters (like newline and carriage return characters).

To check if a file stream was successful opening a file, you can do it by calling to member is_open. This member function returns a bool value of true in the case that indeed the stream object is associated with an open file, or false otherwise:

``` c++
if (!myfile.is_open())
{
cout<< “Error opening file!”;
return;
}
```

When we are finished with our input and output operations on a file we shall close it so that the operating system is notified and its resources become available again. For that, we call the stream's member function close. This member function takes flushes the associated buffers and closes the file:

``` c+++
myfile.close();
```

In case that an object is destroyed while still associated with an open file, the destructor automatically calls the member function close.

``` c++
istream& getline (istream&  is, string& str, char delim);
istream& getline (istream&& is, string& str, char delim);

istream& getline (istream&  is, string& str);
istream& getline (istream&& is, string& str);
```

Extracts characters from is and stores them into str until the delimitation character delim is found (or the newline character, '\n', for last two functions).

The extraction also stops if the end of file is reached in is or if some other error occurs during the input operation.

If the delimiter is found, it is extracted and discarded (i.e. it is not stored and the next input operation will begin after it).

Note that any content in str before the call is replaced by the newly extracted sequence.

Each extracted character is appended to the string as if its member push_back was called.

The value returned by getline is a reference to the stream object itself, which when evaluated as a boolean expression (as in this while-loop) is true if the stream is ready for more operations, and false if either the end of the file has been reached or if some other error occurred.

## Checking state flags

- `bad()` - Returns true if a reading or writing operation fails. For example, in the case that we try to write to a file that is not open for writing or if the device where we try to write has no space left.

- `fail()` - Returns true in the same cases as bad(), but also in the case that a format error happens, like when an alphabetical character is extracted when we are trying to read an integer number.

- `eof()` - Returns true if a file open for reading has reached the end.

- `good()` - It is the most generic state flag: it returns false in the same cases in which calling any of the previous functions would return true. Note that good and bad are not exact opposites (good checks more state flags at once).

## Get and put stream positioning

All i/o streams objects keep internally -at least- one internal position:
ifstream, like istream, keeps an internal get position with the location of the element to be read in the next input operation.
ofstream, like ostream, keeps an internal put position with the location where the next element has to be written.
Finally, fstream, keeps both, the get and the put position, like iostream.

These internal stream positions point to the locations within the stream where the next reading or writing operation is performed. These positions can be observed and modified using the following member functions:
`tellg()` and `tellp()`

These two member functions with no parameters return a value of the member type streampos, which is a type representing the current get position (in the case of tellg) or the put position (in the case of tellp).
seekg() and seekp()
These functions allow to change the location of the get and put positions. Both functions are overloaded with two different prototypes.

The first form is:

`seekg ( streamoff offset, ios_base::seekdir direction );`
`seekp ( streamoff offset, ios_base::seekdir direction );`

Using this prototype, the get or put position is set to an offset value relative to some specific point determined by the parameter direction. offset is of type streamoff. And direction is of type seekdir, which is an enumerated type that determines the point from where offset is counted from, and that can take any of the following values:

 `ios::beg`  offset counted from the beginning of the stream

 `ios::curr` offset counted from the current position

 `ios::end`  offset counted from the end of the stream

``` c++
  std::ofstream outfile;
  outfile.open("test.txt");

  outfile.write("This is an apple", 16);
  long pos = outfile.tellp();
  outfile.seekp(pos - 7);
  outfile.write(" sam", 4);

  outfile.close();

  ifstream myfile ("~/example.bin", ios::binary);
  streampos begin = myfile.tellg();
  myfile.seekg (0, ios::end);
  streampos end = myfile.tellg();
  myfile.close();
  cout << "file size is: " << (end - begin) << " bytes.\n";
```

For binary files, reading and writing data with the extraction and insertion operators (<< and >>) and functions like getline is not efficient, since we do not need to format any data and data is likely not formatted in lines.

File streams include two member functions specifically designed to read and write binary data sequentially: write and read. The first one (write) is a member function of ostream (inherited by ofstream). And read is a member function of istream (inherited by ifstream). Objects of class fstream have both. Their prototypes are:

`basic_ostream& write(const char_type* s, std::streamsize count );`

`basic_istream& read( char_type* s, std::streamsize count );`

``` c++
  ifstream file ("~/example.bin", ios::in|ios::binary|ios::ate);

  if (file.is_open())
  {
    streampos size = file.tellg();
    char* memblock = new char [size];
    file.seekg (0, ios::beg);
    file.read (memblock, size);
    file.close();

    delete[] memblock;
  }
```

When we operate with file streams, these are associated to an internal buffer object of type `streambuf`. This buffer object may represent a memory block that acts as an intermediary between the stream and the physical file. For example, with an `ofstream`, each time the member function put (which writes a single character) is called, the character may be inserted in this intermediate buffer instead of being written directly to the physical file with which the stream is associated.

The operating system may also define other layers of buffering for reading and writing to files.

When the buffer is flushed, all the data contained in it is written to the physical medium (if it is an output stream).
This process is called **synchronization** and takes place under any of the following circumstances:

- **When the file is closed**: before closing a file, all buffers that have not yet been flushed are synchronized and all pending data is written or read to the physical medium.
- **When the buffer is full**: Buffers have a certain size. When the buffer is full it is automatically synchronized.
- **Explicitly, with manipulators**: When certain manipulators are used on streams, an explicit synchronization takes place. These manipulators are: flush and endl.
- **Explicitly, with member function sync()**: Calling the stream's member function sync() causes an immediate synchronization. This function returns an int value equal to `-1` if the stream has no associated buffer or in case of failure. Otherwise (if the stream buffer was successfully synchronized) it returns `0`.
