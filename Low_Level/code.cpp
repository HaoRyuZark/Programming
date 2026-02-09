#include <array>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <mutex>
#include <ostream>
#include <random>
#include <thread>
#include <vector>
#include <atomic>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <map>
#include <set>
#include <list>
#include <string>
#include <functional>
#include <optional>
#include <variant>
#include <tuple>
#include <fstream>
#include <memory>
#include <string.h>
#include <stdlib.h>
#include <queue>
#include <stack>
#include <unordered_map>
#include <regex>
#include <random>
#include <condition_variable>
#include <chrono>

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Basic C++ Features

void basic_cpp() {
    // Basic input/output
    std::cout << "Hello, World!" << std::endl;

    // Variables and types
    int a = 10;
    double b = 20.5;
    std::string str = "C++17";

    // Control structures
    if (a < b) {
        std::cout << a << " is less than " << b << std::endl;
    } else {
        std::cout << a << " is not less than " << b << std::endl;
    }

    for (int i = 0; i < 5; ++i) {
        std::cout << "Iteration: " << i << std::endl;
    }

    // there are also while and do-while loops

}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// restrict

void restrict_example() {
    // 'restrict' is not a standard C++ keyword, but it is used in C99 and some C++ compilers as an extension.
    // It indicates that a pointer is the only reference to the object it points to, allowing for potential optimizations.

    // Example usage (compiler-specific):
    /*
    void foo(int* __restrict a, int* __restrict b) {
        for (int i = 0; i < 100; ++i) {
            a[i] += b[i];
        }
    }
    */
}  

//////////////////////////////////////////////////////////////////////////////////////////////////////

// volatile

void volatile_example() {
    volatile int flag = 0;

    // In a multi-threaded context, one thread might modify 'flag'
    // while another thread reads it. The 'volatile' keyword prevents
    // the compiler from optimizing away repeated reads of 'flag'.

    while (flag == 0) {
        // Wait for flag to be set by another thread
    }

    std::cout << "Flag has been set!" << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// inline 

inline int add(int a, int b) {
    return a + b;
}


void inline_example() {
    // Inline functions suggest to the compiler to insert the function's code directly at the call site
    // to reduce function call overhead. However, the compiler may ignore this suggestion.

    int result = add(5, 10);
    std::cout << "Result of addition: " << result << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// C features 

// Unlike structs it only has space for the largerst datatype it has.
union Kinds {
    int a;
    char b;
};

//Some C features that are also used in C++
void c_features() {

    // C-style strings
    const char* cstr = "C-style string";
    std::cout << cstr << std::endl;
    printf("Using printf: %s\n", cstr);

    // Structs in C
    typedef struct CStruct {
        int id;
        float value;
    } CStruct;

    CStruct cs;
    cs.id = 1;
    cs.value = 10.5f;

    std::cout << "CStruct ID: " << cs.id << ", Value: " << cs.value << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// conts

#define PI1 3.14f // c practice

const int constant = 1; // only for the programmer use to mark and for the compiler to catch errors
constexpr double PI = 3.14; // alternative to use #define. It can also be used to declare funcions the compiler can run 
                            // and whose result is put in the code which is going to be compiled
constexpr double get_pi() {return 3.14; } // DOES NOT GARANTEE THAT IT WILL BE EVALUATED AT COMPILE TIME

constexpr double get_pi2() {return 3.14; } // GARANTEES THAT IT WILL BE EVALUATED AT COMPILE TIME. Only can be used for functions 

// How the const key words acts: Unless it is the most left thing in the expression, const applies only to the thing at its left 

void constants() {

    const int a = 1; // constant number 
    int b = 1;
    int const *ptr_a = &a; // pointer to const int
    int* const ptr_b = &b; // unmutable pointer to an int
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Math functions 

void math_functions() {

    double value = 9.0;
    double sqrtValue = std::sqrt(value);
    double powValue = std::pow(value, 2);
    double sinValue = std::sin(value);
    double logValue = std::log(value);

    std::cout << "Square root of " << value << " is " << sqrtValue << std::endl;
    std::cout << value << " raised to the power of 2 is " << powValue << std::endl;
    std::cout << "Sine of " << value << " is " << sinValue << std::endl;
    std::cout << "Natural logarithm of " << value << " is " << logValue << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// noexcept

void noexcept_example() {

    // Function that is guaranteed not to throw exceptions
    auto safeFunction = []() noexcept {
        std::cout << "This function will not throw exceptions." << std::endl;
    };

    safeFunction();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////


// Initializtion Types 

void initialization_types() {

    // Direct Initialization
    // This form calls the constructor directly
    int x(5);
    double y(10.5);

    // Copy Initialization
    // This form uses the assignment operator
    int a = 15;
    double b = 20.5;

    // Uniform Initialization (C++11 and later)
    // Prevents narrowing conversions
    int arr[] = {1, 2, 3, 4, 5};
    std::vector<int> vec = {6, 7, 8, 9, 10};
    
    int narrow = {static_cast<int>(3.14)}; // Explicit cast needed
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// OOP Concepts 

// Rule of Four: When implementing classes always implement:
// - Overloaded Assigment Operator 
// - Constructor
// - Copy Constructor 
// - Destructor 

// Structs are similar to classes but default to public access
struct Structure {

private:
    int secret = 0;

public: 

    Structure() : data(0) {} // default constructor
    Structure(int data) : data(data) {} // parameterized constructor
    int data;
    static int var;

    // Unlike in c the struct can have member functions
    void display() {
        std::cout << "Data: " << data << std::endl;
    }
};

int Structure::var = 10; // static members have to be initialized outside the class. Do not ask

// C++ is allowed to do one implicit conversion like for example Entity a = 22; if Entity has a constructor which accepts an int it 
// will interpert the line as a call to that constructor. 
//
// THIS IS HORRIBLE!!!!!!! NEVER USE THAT!!!!!!!!!!
//
// Explicit disables implicit conversion for objects now the constructor has to be called explicitely 
class Example {

    private: // Private section
        int privateData = 0; // setting default value
        int otherData = 0;

    public: // Public section

        explicit Example() : privateData(0), otherData(0) { // default constructor
            privateData = 0;
            otherData = 0;
        }
        
        Example (const Example&){} // copy construcor. Is called when =, ()

        explicit Example(int val, int otherVal) : privateData(val), otherData(otherVal) { // contructor supporting uniform initialization
            privateData = val;
            otherData = otherVal;
        }

        Example operator= (const Example& other) { // overloaded assignment operator
            if (this != &other) { // self-assignment check
                privateData = other.privateData;
                otherData = other.otherData;
            }
            return *this;
        }


        void show() {
            std::cout << "Private Data: " << privateData << std::endl;
        }

        ~Example() {
            // Destructor
            std::cout << "Example object destroyed." << std::endl;
        }
};

void oop_concepts() {

    Structure s;
    s.data = 100;
    s.display();

    Structure s2{200}; // Uniform initialization
    s2.display();

    Example ex{300, 400}; // Uniform initialization

}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Inheritance and Polymorphism

class Base {
    public:
        virtual void show1() {
            std::cout << "Base class show function called." << std::endl;
        }

        void show() {
            std::cout << "AHHHHHHH" << std::endl;
        }

    virtual ~Base() {
            // Virtual destructor
        }
};

class Derived : public Base {
    public:
        void show1() override {
            std::cout << "Derived class show function called." << std::endl;
        }
};

void inheritance_polymorphism() {
    Base* basePtr;
    Derived derivedObj;
    basePtr = &derivedObj;

    basePtr->show1(); // Calls Derived's show function due to polymorphism
}

// Multiple Inheritance Example

class AnotherBase {
    public:
        void display() {
            std::cout << "AnotherBase class display function called." << std::endl;
        }
        
        void show() {
            std::cout << "AHHHHHHH" << std::endl;
        }
};

class MultiDerived : public Base, public AnotherBase {
    public:
        void show1() override {
            std::cout << "MultiDerived class show function called." << std::endl;
        }
};

void multiple_inheritance() {

    MultiDerived multiObj;
    Base* basePtr = &multiObj;
    basePtr->show1(); // Calls MultiDerived's show function

    AnotherBase* anotherBasePtr = &multiObj;
    anotherBasePtr->display(); // Calls AnotherBase's display function
    
    multiObj.Base::show(); // is we do not specify the parent class we will have abiguity due to the show function being defined in both parent classes
}

// There is also virtual inheritance which allows us to when having a diamond problem in which 
// we call a function which also in the subclasses we can just reference the original class at the top of the hierarchy 

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Copy Constructor and Initialization-types

void copy_constructor_initialization_types() {

    Example original(42, 84); // Parameterized constructor
    Example copy = original;   // Copy constructor

    copy.show();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Exception Handling

void exception_handling() {

    try {
        int dividend = 10;
        int divisor = 0;

        if (divisor == 0) {
            throw std::runtime_error("Division by zero error");
        }

        int result = dividend / divisor;
        std::cout << "Result: " << result << std::endl;

    } catch (const std::runtime_error& e) {
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Caught an unknown exception." << std::endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Reading and Writing Files 

void read_files() {

    std::ifstream inputFile("example.txt");

    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::string line;

    while (std::getline(inputFile, line)) {
        std::cout << line << std::endl;
    }

    inputFile.close();
}

void write_files() {

    std::ofstream outputFile("output.txt");

    if (!outputFile) {
        std::cerr << "Error creating file!" << std::endl;
        return;
    }

    outputFile << "This is a line written to the file." << std::endl;
    outputFile << "C++ file handling example." << std::endl;

    outputFile.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Abstract Classes and Interfaces

class AbstractBase {
    public:
        virtual void pureVirtualFunction() = 0; // Pure virtual function

        virtual ~AbstractBase() {
            // Virtual destructor
        }
};

class ConcreteDerived : public AbstractBase {
    public:
        void pureVirtualFunction() override {
            std::cout << "Implementation of pure virtual function in ConcreteDerived." << std::endl;
        }
};

void abstract_classes_interfaces() {
    ConcreteDerived obj;
    obj.pureVirtualFunction();
}

class Interface {
    public:
        virtual void interfaceMethod() = 0; // Pure virtual function

        virtual ~Interface() {
            // Virtual destructor
        }
};

class InterfaceImpl : public Interface {
    public:
        void interfaceMethod() override {
            std::cout << "Implementation of interface method in InterfaceImpl." << std::endl;
        }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////

// List 

void list_methods() {
    std::list<int> numList;

    // Adding elements
    numList.push_back(10);
    numList.push_back(20);
    numList.push_front(5);

    // Iterating through the list
    std::cout << "List elements: ";
    for (const int& num : numList) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Removing elements
    numList.pop_back();
    numList.remove(5); // Remove specific value

    std::cout << "List after removals: ";
    for (const int& num : numList) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Strings

void string_examples() {

    std::string str1 = "Hello, ";
    std::string str2 = "World!";
    
    // Concatenation
    std::string str3 = str1 + str2;
    std::cout << str3 << std::endl;

    // Substring
    std::string subStr = str3.substr(7, 5); // "World"
    std::cout << "Substring: " << subStr << std::endl;

    // Find
    size_t pos = str3.find("World");
    if (pos != std::string::npos) {
        std::cout << "'World' found at position: " << pos << std::endl;
    }

    // Length
    std::cout << "Length of str3: " << str3.length() << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Pointers and References

void modify_value_1(int* ptr) {
    *ptr = 20; // Modifying value at the address pointed to by ptr
}

void modify_value_2(int& ref) {
    ref = 30; // Modifying value via reference
}

void does_not_modify(int val) {
    val = 40; // This modification won't affect the original variable   
}

void pointers_references() {
    int var = 42;
    int* ptr = &var; // Pointer to var | can be changed to point to another variable
    int& ref = var;  // Reference to var | cannot be changed to refer to another variable
                     // does not actually occupy memory it is just an alias

    std::cout << "Value of var: " << var << std::endl;
    std::cout << "Value via pointer: " << *ptr << std::endl;
    std::cout << "Value via reference: " << ref << std::endl;

    // Modifying value via pointer
    *ptr = 100;
    std::cout << "Modified var via pointer: " << var << std::endl;

    // Modifying value via reference
    ref = 200;
    std::cout << "Modified var via reference: " << var << std::endl;
}

// Function to be pointed to
void sampleFunction(int x) {
    std::cout << "Sample Function called with value: " << x << std::endl;
}

void function_pointers(int* a) {
    // Function pointer declaration
    void (*funcPtr)(int);

    // Assigning function to pointer
    funcPtr = sampleFunction;

    // Calling function via pointer
    funcPtr(*a);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Smart Pointers

void smart_pointers() {
    
    // Using unique_ptr
    // Only one unique_ptr can own the object at a time
    std::unique_ptr<int> uniquePtr(new int(10));
    std::cout << "Unique Pointer Value: " << *uniquePtr << std::endl;

    // Transferring ownership
    std::unique_ptr<int> anotherUniquePtr = std::move(uniquePtr);

    if (!uniquePtr) {
        std::cout << "uniquePtr is now null after move." << std::endl;
    }

    std::cout << "Another Unique Pointer Value: " << *anotherUniquePtr << std::endl;

    //make_unique: this returns a unique pointer to a newly created object
    auto makeUniquePtr = std::make_unique<int>(15);

    // Using shared_ptr
    // Multiple shared_ptr can own the same object. Reference counting is used to manage the object's lifetime.
    // Mutable shared ownership
    std::shared_ptr<int> sharedPtr1(new int(20));

    {
        std::shared_ptr<int> sharedPtr2 = sharedPtr1; // Shared ownership
        std::cout << "Shared Pointer 2 Value: " << *sharedPtr2 << std::endl;
        std::cout << "Reference Count: " << sharedPtr1.use_count() << std::endl;
    } // sharedPtr2 goes out of scope here

    std::cout << "Reference Count after sharedPtr2 goes out of scope: " << sharedPtr1.use_count() << std::endl;

    // Using weak_ptr
    // weak_ptr does not own the object. It is used to break circular references.
    std::weak_ptr<int> weakPtr = sharedPtr1;

    if (auto tempPtr = weakPtr.lock()) { // Check if the object is still alive
        std::cout << "Weak Pointer Value: " << *tempPtr << std::endl;
    } else {
        std::cout << "Object has been deleted." << std::endl;
    }

    // smart pointer with non primitive types
    std::shared_ptr<Example> examplePtr = std::make_shared<Example>(50, 100);
    examplePtr->show();

    std::unique_ptr<std::vector<int>> vecPtr = std::make_unique<std::vector<int>>();

}

void playing_with_strings() {
    
    std::array<const char*, 4> arr = {"This", "is", "a", "sentence"};

    auto length = [](char* str){ return strlen(str) + 1; };

    auto reverse = [](char* str){
        
        size_t len = strlen(str);

        char* r_str = (char *)malloc(sizeof(char) * len);

        for (int i = 0; i < len; i++) {
            r_str[i] = str[len - 1 - i];
        }

        return r_str;
    };
 
    auto reverse_2 = [](char* str){
        
        size_t len = strlen(str);

        std::unique_ptr<char[]> r_v(new char[len]);

        for (int i = 0; i < len; i++) {
            r_v[i] = str[len - 1 - i];
        }
    
        return r_v;
    };   

    std::cout << length(const_cast<char*>(arr[0])) << std::endl;

    char* r_str = reverse(const_cast<char*>(arr[0]));
    std::cout << r_str  << std::endl;
    free(r_str);

    std::unique_ptr<char[]> r2 = reverse_2(const_cast<char*>(arr[0]));
    std::cout << r2.get()  << std::endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

// Rule of 5

// When implementing classes that manage resources, consider implementing the following five special 
// member functions:
// 1. Destructor
// 2. Copy Constructor
// 3. Copy Assignment Operator
// 4. Move Constructor
// 5. Move Assignment Operator

class ma_container {
public:
    explicit ma_container(int* a,
                          std::unique_ptr<int> b,
                          std::shared_ptr<std::vector<int>> c)
        : int_ptr(a), // just pointer assignment
          unique_ptr(std::move(b)), // transfer ownership
          shared_vector_ptr(std::move(c)) {} // shared ownership

    // Copy constructor
    ma_container(const ma_container& other)
        : int_ptr(other.int_ptr ? new int(*other.int_ptr) : nullptr), // deep copy of the pointer
          unique_ptr(other.unique_ptr ? std::make_unique<int>(*other.unique_ptr) : nullptr), // deep copy of unique_ptr
          shared_vector_ptr(other.shared_vector_ptr) // deep copy of shared_ptr 
    {}
    
    // Assignment operator
    ma_container& operator=(const ma_container& other) {
        
        if (this == &other) return *this; // handling self-assignment

        int* new_int = other.int_ptr ? new int(*other.int_ptr) : nullptr; // deep copy of the pointer
        auto new_unique = other.unique_ptr ? std::make_unique<int>(*other.unique_ptr) : nullptr; // deep copy of unique_ptr

        int_ptr = new_int; // assign the new deep copied pointer
        unique_ptr = std::move(new_unique); // assign the new deep copied unique_ptr
        shared_vector_ptr = other.shared_vector_ptr; // deep copy of shared_ptr

        return *this;
    }
    
    // Move constructor
    ma_container(ma_container&& other) noexcept 
        : int_ptr(other.int_ptr), // shallow copy of the pointer
          unique_ptr(std::move(other.unique_ptr)), // transfer ownership
          shared_vector_ptr(std::move(other.shared_vector_ptr)) { // transfer ownership
        other.int_ptr = nullptr;
    }

    // Move assignment
    ma_container& operator=(ma_container&& other) noexcept {
        if (this == &other) return *this;

        delete int_ptr; // free existing resource
        int_ptr = other.int_ptr; // shallow copy of the pointer
        unique_ptr = std::move(other.unique_ptr); // transfer ownership
        shared_vector_ptr = std::move(other.shared_vector_ptr); // transfer ownership

        other.int_ptr = nullptr;
        return *this;
    }

    ~ma_container() {
        delete int_ptr; // free the raw pointer resource other are automatically managed
    }

private:
    int* int_ptr;
    std::unique_ptr<int> unique_ptr;
    std::shared_ptr<std::vector<int>> shared_vector_ptr;
};




//////////////////////////////////////////////////////////////////////////////////////////////////////

// Templates

// Function Template for generics
template <typename T>
T add(T a, T b) {
    return a + b;
}

// Class Template for generics
template <typename T>
class Pair {
    private:
        T first, second;
    public:
        Pair(T a, T b) : first(a), second(b) {}
        T getFirst() const {
            return first;
        }
        T getSecond() const {
            return second;
        }
};

void template_examples() {
    // Using function template
    int intSum = add<int>(5, 10);
    double doubleSum = add<double>(5.5, 10.5);

    std::cout << "Integer Sum: " << intSum << std::endl;
    std::cout << "Double Sum: " << doubleSum << std::endl;

    // Using class template
    Pair<int> intPair(1, 2);
    Pair<std::string> stringPair("Hello", "World");

    std::cout << "Integer Pair: (" << intPair.getFirst() << ", " << intPair.getSecond() << ")" << std::endl;
    std::cout << "String Pair: (" << stringPair.getFirst() << ", " << stringPair.getSecond() << ")" << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Virtual Functions and the virutal table 
// Virtual functions allow derived classes to override methods in base classes, enabling polymorphism.
// The virtual table (vtable) is a mechanism used by C++ to support dynamic dispatch of virtual functions.
// 
// The process when a method using a vtable functions is obj-vtbale->method. Due to this reason 
// Inheritance can hurt performance


// Dynamic Dispatch
// When a virtual function is called through a base class pointer or reference, the 
// actual function that gets executed is determined at runtime based on the type of the object being pointed to.

// Static vs Dynamic Binding
// Static binding occurs at compile-time, while dynamic binding occurs at runtime for virtual functions.

void example_virtual_functions() {
    Base* basePtr;
    Derived derivedObj;
    basePtr = &derivedObj;

    basePtr->show1(); // Calls Derived's show function due to polymorphism
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Move Semantics

// This topic refers to the action of mitigating unnecessary copies of objects 

// Rvalue references allow the resources of temporary objects to be moved rather than copied, improving performance. Formally 
// it can only reside on the right side of the assignment operator.
//
// lvalue is a value that resides in value. It is addressable and can not be moved.

// lvalue references: This are normal references which act as pointers. We can bind an rvalue to a const lvalue reference 
void lvalue_reference_example(const int& ref) {
    printf("Printing");
}

// const allows us to accept both lvalues and rvalues
void print_string(const std::string& str) {
    std::cout << str << std::endl;
}

// accepts only temporary objects. Parameter is an rvalue reference
void print_string(std::string&& str) {
    std::cout << str << std::endl;
}

void call_examples() {
    
    //rvalue = 10 
    //lvalue = i
    int i = 10; 

    int& ref = i;
    
    lvalue_reference_example(ref);
    
    // without const we get an error, because 10 is not an lvalue
    const int& ref2 = 10;  // the reason this works it beacuse the compiler will do something like 
    // int temp = 10; int& ref2 = temp;

    lvalue_reference_example(ref2);
    
    std::string str1 = "AHHH";
    std::string str2 = "AHHH";
    std::string str = str1 + str2;

    print_string(str); // works without const 
    print_string(str1 + str2); // does not work without const
}



// rvalue references bind only to rvalues and represented as &&
void rvalue_references_perfect_forwarding() {

    // Function that takes an rvalue reference
    auto process = [](std::string&& str) {
        std::cout << "Processing rvalue string: " << str << std::endl;
    };

    std::string temp = "Temporary String";
    process(std::move(temp)); // std::move converts lvalue to rvalue
}

// std::move 
// is a function for casting to an rvalue reference.

//////////////////////////////////////////////////////////////////////////////////////////////////////

// RAII
// Resource Acquisition Is Initialization. This is a programming idiom used in C++ to manage resource allocation and deallocation.
// Instead of manually releasing resources, RAII ties resource management to object lifetime.

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Casting 

// short -> byte -> int -> long -> float -> double
//                   |<-> char

// C style 
void c_tyle_cast() {
    int a = (int)'a';
}

class Animal {
    virtual void do_stuff(){}
};

class Dog: Animal {};

// c++ 
void c_pp_casting() {

    // Static cast 
    // is more restrive than a c cast. Avoids invalid conversions
    // If twe have a conversion operator overloaded for a class like string(), the staic cast user the 
    // conversion constructor 
    //
    // for contring into and from void* it is also useful
    int a = static_cast<int>('a');

    // Dynamic cast 
    // It safely converts from pointer or reference to base type to a derivaded type
    // We also have the typeid which tells us the type of the object at runtime
    Animal b;
    Animal& ref  = b;
    Dog& ref2 = dynamic_cast<Dog&>(ref); // only works on classes with virtual functions

    // Const cast 
    // it is used to cast away the constness of a variable 
    const int val = 5; 
    const int* c = &val;
    
    int* ptr = const_cast<int*>(ptr);
    
    // Reinterpret cast
    // Allows any pointer to be converted ino any other pointer type 
    // Allows any integral type to be converted into any pointer type and vice versa

    int n = 25;
    char n1 = 'a';
    char* pn1 = &n1;

    int* rpn1 = reinterpret_cast<int*>(pn1);
    // In c we already do something similar when casting an struct as an char array or 
    // similars. In cpp this is done is a more standardize way.
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Lambda Expressions 

void lambda_expressions() {
    // A simple lambda that adds two numbers
    
    auto add = [](int x, int y) {
        return x + y;
    };

    int result = add(5, 10);
    std::cout << "Result of addition: " << result << std::endl;

    // A lambda that captures variables by value
    int factor = 2;
    auto multiply = [factor](int x) {
        return x * factor;
    };

    int mulResult = multiply(5);
    std::cout << "Result of multiplication: " << mulResult << std::endl;

    // capture block 
    // this allows us to capture all variables in the scope by value or reference

    int a = 10;
    int b = 20;

    auto capture_all_by_value = [=]() {
        return a + b;
    };

    auto capture_all_by_reference = [&]() {
        return a + b;
    };

    std::cout << "Capture all by value: " << capture_all_by_value() << std::endl;
    std::cout << "Capture all by reference: " << capture_all_by_reference() << std::endl;

    // parameterized capture by reference
    auto capture_by_reference = [&a, &b]() {
        return a + b;
    };
    
    // parameterized capture by value
    auto capture_by_value = [a, b]() {
        return a + b;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////// 

// Vector 

void vector_methods() {

    std::vector<int> numbers;

    // Adding elements
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);

    // Accessing elements
    std::cout << "First element: " << numbers.front() << std::endl;
    std::cout << "Last element: " << numbers.back() << std::endl;

    // Iterating through the vector
    std::cout << "Vector elements: ";
    for (const int& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Removing last element
    numbers.pop_back();
    std::cout << "After pop_back, last element: " << numbers.back() << std::endl;

    // find
    auto it = std::find(numbers.begin(), numbers.end(), 20);
    if (it != numbers.end()) {
        std::cout << "Element 20 found in the vector." << std::endl;
    } else {
        std::cout << "Element 20 not found in the vector." << std::endl;
    }

    //size 
    std::cout << "Vector size: " << numbers.size() << std::endl;

    // copy 
    std::vector<int> copy{1,2};
    numbers.insert(numbers.begin(), copy.begin(), copy.end()); // 1,2 at the start and shifts the rest

}


//////////////////////////////////////////////////////////////////////////////////////////////////////

// Deque
// Double-ended queue

void deque_methods() {

    std::deque<int> numDeque;

    // Adding elements
    numDeque.push_back(10);
    numDeque.push_back(20);
    numDeque.push_front(5);

    // Accessing front and back elements
    std::cout << "Front element: " << numDeque.front() << std::endl;
    std::cout << "Back element: " << numDeque.back() << std::endl;

    // Iterating through the deque
    std::cout << "Deque elements: ";
    for (const int& num : numDeque) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Removing elements
    numDeque.pop_back();
    numDeque.pop_front();

    std::cout << "Deque after removals: ";
    for (const int& num : numDeque) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Queue 

void queue_methods() {
    std::queue<int> numQueue;

    // Adding elements
    numQueue.push(10);
    numQueue.push(20);
    numQueue.push(30);

    // Accessing front and back elements
    std::cout << "Front element: " << numQueue.front() << std::endl;
    std::cout << "Back element: " << numQueue.back() << std::endl;

    // Removing elements
    numQueue.pop();
    std::cout << "After pop, front element: " << numQueue.front() << std::endl;

    // Size of the queue
    std::cout << "Queue size: " << numQueue.size() << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Stack 

void stack_methods() {
    std::stack<int> numStack;

    // Adding elements
    numStack.push(10);
    numStack.push(20);
    numStack.push(30);

    // Accessing top element
    std::cout << "Top element: " << numStack.top() << std::endl;

    // Removing elements
    numStack.pop();
    std::cout << "After pop, top element: " << numStack.top() << std::endl;

    // Size of the stack
    std::cout << "Stack size: " << numStack.size() << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Multimap 

// A multimap is an associative container that contains a sorted list of key-value pairs,
// where multiple elements can have the same key.

void multimap_methods() {
    std::multimap<std::string, int> ageMap;

    // Inserting elements
    ageMap.insert({"Alice", 30});
    ageMap.insert({"Bob", 25});
    ageMap.insert({"Alice", 35}); // Duplicate key

    // Accessing elements
    std::cout << "Ages of Alice:" << std::endl;
    auto range = ageMap.equal_range("Alice");
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << it->second << std::endl;
    }

    // Iterating through the map
    std::cout << "Age Map:" << std::endl;
    for (const auto& pair : ageMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // Erasing elements with a specific key
    ageMap.erase("Bob");
    std::cout << "Bob erased from the map." << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Unordered Map 

// The unordered_map is the hash map of c++ 

void unordered_map_methods() {
    std::unordered_map<std::string, int> ageMap;

    // Inserting elements
    ageMap["Alice"] = 30;
    ageMap["Bob"] = 25;
    ageMap["Charlie"] = 35;

    // Accessing elements
    std::cout << "Alice's age: " << ageMap["Alice"] << std::endl;

    // Iterating through the map
    std::cout << "Age Map:" << std::endl;
    for (const auto& pair : ageMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // Finding an element
    auto it = ageMap.find("Bob");
    if (it != ageMap.end()) {
        std::cout << "Bob's age found: " << it->second << std::endl;
    } else {
        std::cout << "Bob not found in the map." << std::endl;
    }

    // Erasing an element
    ageMap.erase("Charlie");
    std::cout << "Charlie erased from the map." << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////// 

// map 

// this is a dictionary in a tree structure

void map_example() {

    std::map<std::string, int> ageMap;

    // Inserting elements
    ageMap["Alice"] = 30;
    ageMap["Bob"] = 25;
    ageMap["Charlie"] = 35;

    // Accessing elements
    std::cout << "Alice's age: " << ageMap["Alice"] << std::endl;

    // Iterating through the map
    std::cout << "Age Map:" << std::endl;
    for (const auto& pair : ageMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // Finding an element
    auto it = ageMap.find("Bob");

    if (it != ageMap.end()) {
        std::cout << "Bob's age found: " << it->second << std::endl;
    } else {
        std::cout << "Bob not found in the map." << std::endl;
    }

    // Erasing an element
    ageMap.erase("Charlie");
    std::cout << "Charlie erased from the map." << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Regex

void regex_examples() {
    std::string text = "The quick brown fox jumps over the lazy dog.";
    std::regex vowel_regex("[aeiou]");

    // Find all vowels in the text
    auto words_begin = std::sregex_iterator(text.begin(), text.end(), vowel_regex);
    auto words_end = std::sregex_iterator();

    std::cout << "Vowels found: ";
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::cout << i->str() << " ";
    }
    std::cout << std::endl;

    // Replace vowels with '*'
    std::string replaced_text = std::regex_replace(text, vowel_regex, "*");
    std::cout << "Text after replacement: " << replaced_text << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Set

void set_methods() {
    std::set<int> numSet;

    // Inserting elements
    numSet.insert(5);
    numSet.insert(2);
    numSet.insert(8);
    numSet.insert(5); // Duplicate, will not be added

    // Iterating through the set
    std::cout << "Set elements: ";
    for (const int& num : numSet) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Finding an element
    auto it = numSet.find(2);
    if (it != numSet.end()) {
        std::cout << "Element 2 found in the set." << std::endl;
    } else {
        std::cout << "Element 2 not found in the set." << std::endl;
    }

    // Erasing an element
    numSet.erase(2);
    std::cout << "Element 2 erased from the set." << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Enums 

void enum_examples() {
    // Traditional enum
    enum Color { RED, GREEN, BLUE };
    Color myColor = RED;

    if (myColor == RED) {
        std::cout << "Color is RED" << std::endl;
    }

    // Scoped enum (enum class)
    enum class Direction { NORTH, SOUTH, EAST, WEST };
    Direction myDirection = Direction::NORTH;

    if (myDirection == Direction::NORTH) {
        std::cout << "Direction is NORTH" << std::endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Tuples

void tuple_examples() {

    // Creating a tuple
    std::tuple<int, std::string, double> myTuple(1, "C++17", 3.14);

    // Accessing tuple elements
    std::cout << "Tuple elements: " 
              << std::get<0>(myTuple) << ", " 
              << std::get<1>(myTuple) << ", " 
              << std::get<2>(myTuple) << std::endl;

    // Modifying tuple elements
    std::get<0>(myTuple) = 42;
    std::cout << "Modified first element: " << std::get<0>(myTuple) << std::endl;

    // Tuple size
    std::cout << "Tuple size: " << std::tuple_size<decltype(myTuple)>::value << std::endl;

    // iterate over tuple
    std::apply([](auto&&... args) {
        ((std::cout << args << " "), ...);
    }, myTuple);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// const function 

class ConstExample {
    private:
        int data;
    public:
        ConstExample(int val) : data(val) {}

        // Const member function
        int getData() const {
            return data;
        }

        // Non-const member function
        void setData(const int val) const { // this consts the member function itself, not the parameter. This means it cannot modify any member variables
            // data = val; // This would cause a compilation error
            std::cout << "setData called with value: " << val << std::endl;
        }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////

// Iterators

// Iterators provide a way to access elements of a container (like vector, list, etc.) sequentially without exposing the underlying structure of the container.
void iterator_examples() {

    std::vector<int> vec = {1, 2, 3, 4, 5};

    // Using iterator to traverse the vector
    std::cout << "Vector elements: ";
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Using const_iterator
    std::cout << "Vector elements (const_iterator): ";
    for (std::vector<int>::const_iterator cit = vec.cbegin(); cit != vec.cend(); ++cit) {
        std::cout << *cit << " ";
    }
    std::cout << std::endl;

    // Using reverse_iterator
    std::cout << "Vector elements (reverse_iterator): ";
    for (std::vector<int>::reverse_iterator rit = vec.rbegin(); rit != vec.rend(); ++rit) {
        std::cout << *rit << " ";   
    }

    // begin and end 
    auto start = vec.begin();
    auto finish = vec.end();
    
    int index = 1;
   
    // iterator starting from 1  
    auto somewhere = vec.begin() + index;

    // Range 
    for (int ele: vec) { 
        std::cout << ele << " ";   
    }

    // iterating over a map 

}

// Writing Iterators 

class My_Vector {
    private:
        int* data;
        size_t size;
    public:
        My_Vector(size_t s) : size(s) {
            data = new int[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = i; // Initialize with some values
            }
        }

        ~My_Vector() {
            delete[] data;
        }

        // Nested iterator class
        class Iterator {
            private:
                int* ptr;
            public:
                Iterator(int* p) : ptr(p) {}

                int& operator*() {
                    return *ptr;
                }

                Iterator& operator++() {
                    ++ptr;
                    return *this;
                }

                bool operator!=(const Iterator& other) const {
                    return ptr != other.ptr;
                }
        };

        Iterator begin() {
            return Iterator(data);
        }

        Iterator end() {
            return Iterator(data + size);
        }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////

// using 

// The using keyword in C++ is used to create type aliases, making code more readable and easier to manage.
void using_example() {
    // Creating a type alias for a complex type
    using StringIntMap = std::map<std::string, int>;

    StringIntMap ageMap;

    ageMap["Alice"] = 30;
    ageMap["Bob"] = 25;

    for (const auto& pair : ageMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Struture binding

void structure_binding_example() {

    std::unordered_map<std:: string,  std::string> colors = {
        {"red", "0x1000"},
        {"yellow", "0x1000"},
        {"blue", "0x1000"},
    };

    // binding reference to the pair fields
    for (auto&[color, hex]: colors) {
        std::cout << color << " " << hex << std::endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Operator Overloading 

class Complex {
    private:
        double real;
        double imag;
    public:
        Complex(double r = 0, double i = 0) : real(r), imag(i) {}

        // Overloading the + operator
        Complex operator+(const Complex& other) {
            return Complex(real + other.real, imag + other.imag);
        }

        Complex operator*(const Complex& other) {
            return Complex(real * other.real - imag * other.imag,
                           real * other.imag + imag * other.real);
        }

        // Overloading the << operator for output
        friend std::ostream& operator<<(std::ostream& os, const Complex& c) { // the friend keyword allows access to private members
            os << c.real << " + " << c.imag << "i";
            return os;
        }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Template Specialization
// Template specialization allows you to define a specific implementation of a template for a particular data type.

template <typename T>
class Calculator {
    public:
        T add(T a, T b) {
            return a + b;
        }
}; 

// Specialization for std::string
template <>
class Calculator<std::string> {
    public:
        std::string add(std::string a, std::string b) {
            return a + " " + b; // Concatenate with a space
        }
};

template<typename T>
void specialized_addition(T a, int b) {
    Calculator<T> calc;
    T result = calc.add(a, b);
    std::cout << "Addition Result: " << result << std::endl;
}

// Template class that calculates the power of a number at compile time
template <int B, int N> 
struct Power {
    constexpr static int b_hoch_n = B * Power<B, N - 1>::value;
};

template<int B>
struct Power<B, 0> {
    constexpr static int b_hoch_n = 1;
};



//////////////////////////////////////////////////////////////////////////////////////////////////////

// STL Algorithms

void stl_algorithms() {
    
    std::vector<int> vec = {5, 2, 8, 1, 4};

    // Sorting the vector
    std::sort(vec.begin(), vec.end());

    std::cout << "Sorted vector: ";
    for (const int& num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Finding an element
    auto it = std::find(vec.begin(), vec.end(), 4);
    
    if (it != vec.end()) {
        std::cout << "Element 4 found in the vector." << std::endl;
    } else {
        std::cout << "Element 4 not found in the vector." << std::endl;
    }

    // Accumulating sum of elements
    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    std::cout << "Sum of vector elements: " << sum << std::endl;

    // for_each 
    std::for_each(vec.begin(), vec.end(), [](int& a){return a * a;});    
    
    // Heap 
    std::vector<int> v2(vec);

    std::make_heap(v2.begin(), v2.end());
    std::pop_heap(v2.begin(), v2.end());
    
    // fill 
    std::vector<int> to_be_used;

    // generate 
    std::fill(to_be_used.begin(), to_be_used.end(), 42);
    std::generate(to_be_used.begin(), to_be_used.end(), [](){}); // generate empty 

    // transform 
    std::transform(vec.begin(), vec.end(), vec.begin(), [](int& a) { return a * a;});

    // copy 
    std::copy(vec.begin(), vec.end(), to_be_used.begin());

    // copy_if  
    std::copy_if(vec.begin(), vec.end(), to_be_used.begin(), [](int& a, int& b){ return a % 2 == 0;});

}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Threads 

void simple_thread_example() {
   
    auto task = []() {
        std::cout << "Thread is running." << std::endl;
    };

    // The thread function can accept the following arguments:
    //  - A function pointer
    //  - A lambda expression
    //  - A functor (an object that overloads the operator()) 
    std::thread t(task);
    t.join(); // Wait for the thread to finish

    // Multiple Threads
    std::vector<std::thread> threads; 

    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([i]() {
            std::cout << "Thread " << std::this_thread::get_id() << " is running." << std::endl;
        });
    }

    for (auto& th : threads) {
        th.join();
    }

}

void scope_lock_example() {
    
    std::mutex mtx;
    int sharedResource = 0;

    auto task = [&mtx, &sharedResource]() {
   
        // unique_lock is a more flexible locking mechanism than lock_guard
        // it can also handle multiple locks and unlocks within the same scope
        std::unique_lock<std::mutex> lock(mtx); // Automatically locks and unlocks the mutex via RAII
        for (int i = 0; i < 1000; ++i) {
            ++sharedResource;
        }
    };

    std::thread t1(task);
    std::thread t2(task);

    t1.join();
    t2.join();

    std::cout << "Final value of sharedResource: " << sharedResource << std::endl;
}

void mutex_example_1() {

    std::mutex mtx;
    int sharedResource = 0;

    auto task = [&mtx, &sharedResource]() {
        
        // lock_guard is a RAII-style mechanism for owning a mutex for the duration of a scoped block
        // it is also useful to avoid deadlocks in case of exceptions
        std::lock_guard<std::mutex> lock(mtx); // Automatically locks and unlocks the mutex via RAII
        for (int i = 0; i < 1000; ++i) {
            ++sharedResource;
        }
    };

    std::thread t1(task);
    std::thread t2(task);

    t1.join();
    t2.join();

    std::cout << "Final value of sharedResource: " << sharedResource << std::endl;
}

void mutex_example_2() {

    std::mutex mtx;
    int sharedResource = 0;

    auto task = [&mtx, &sharedResource]() {

        mtx.lock();                         // Alternative way to lock the mutex
        for (int i = 0; i < 1000; ++i) {
            ++sharedResource;
        }
        mtx.unlock();
    };

    std::thread t1(task);
    std::thread t2(task);

    t1.join();
    t2.join();

    std::cout << "Final value of sharedResource: " << sharedResource << std::endl;
}

void mutex_example_3() {
    
    std::mutex mtx;
    int sharedResource = 0;

    auto task = [&mtx, &sharedResource]() {

        // try_lock attempts to lock the mutex without blocking
        if (mtx.try_lock()) {               // Try to lock the mutex without blocking
            for (int i = 0; i < 1000; ++i) {
                ++sharedResource;
            }
            mtx.unlock();
        } else {
            std::cout << "Could not acquire lock." << std::endl;
        }
    };

    std::thread t1(task);
    std::thread t2(task);

    t1.join();
    t2.join();

    std::cout << "Final value of sharedResource: " << sharedResource << std::endl;
}

// Atomic 

void atomic_example() {

    std::atomic<int> atomicCounter(0); // atomic allows safe concurrent access without explicit locks

    auto task = [&atomicCounter]() {
        for (int i = 0; i < 1000; ++i) {
            atomicCounter.fetch_add(1); // Atomically increment the counter
        }
    };

    std::thread t1(task);
    std::thread t2(task);

    t1.join();
    t2.join();

    std::cout << "Final value of atomicCounter: " << atomicCounter.load() << std::endl;
}

// Condition Variables

// The idea is that even if the treads should run concurrently, sometimes we need one thread to act first on some 
// data before the other thread can proceed. Condition variables allow threads to wait for certain conditions to be met.
void condition_variable_example() {

    std::mutex mtx;
    std::condition_variable cv;
  
    bool ready = false;
    int sharedData = 0;

    auto producer = [&]() {

        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work
        {
            std::lock_guard<std::mutex> lock(mtx);
            sharedData = 42;
            ready = true;
        }
        cv.notify_one(); // Notify the consumer, there is also notify_all() for multiple consumers
    };

    auto consumer = [&]() {
       
        // unique_lock is a more flexible locking mechanism than lock_guard
        std::unique_lock<std::mutex> lock(mtx);

        cv.wait(lock, [&]() { return ready; }); // Wait until notified and ready is true
        std::cout << "Consumed data: " << sharedData << std::endl;
    };

    std::thread prodThread(producer);
    std::thread consThread(consumer);

    prodThread.join();
    consThread.join();
}

// Example of a thread that modifies a variable and returns its value
void thread_example_with_return_value() {

    auto task = [](int& x) {
        x += 10;
    };

    int result = 0;
    std::thread t(task, std::ref(result)); // Use std::ref to pass by reference
    t.join();
    std::cout << "Result from thread: " << result << std::endl;

}


// detached threads

void detached_thread_example() {

    auto task = []() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Detached thread finished work." << std::endl;
    };

    std::thread t(task);
    t.detach(); // Detach the thread to run independently, this means we cannot join it later

    std::cout << "Main thread continues execution." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3)); // Wait to see detached thread output
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Random Numbers 

void random_numbers() {
    
    // C like 
    srand(time(0));
    std::cout << rand() << std::endl;

    // Bruh 
    std::random_device random_device;
    std::mt19937 rng(random_device());
    std::uniform_real_distribution<double> dist6(1,6);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// mutable 

// mutable in classes
class Example_Mutable {

private:
    std::string name;
    mutable int count = 0; // allows to modify in const methods

public:
    const std::string& get_name() const {
        count++;
        return name;
    }
};

// mutable in lambdas
void mutable_example() {

    int x = 0;
    auto f = [=]() mutable { //allows to modify the copy of the value in the lambda
        x++;
        std::cout<< x << std::endl;
    };

    f();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Optional 

void optional_example() {
    
    std::optional<int> optInt; // initially empty

    if (!optInt.has_value()) {
        std::cout << "optInt is empty." << std::endl;
    }

    optInt = 42; // assigning a value

    if (optInt.has_value()) {
        std::cout << "optInt has value: " << optInt.value() << std::endl;
    }

    // Using value_or to provide a default value
    int value = optInt.value_or(0);
    std::cout << "Value from optInt or default: " << value << std::endl;

    // Resetting the optional
    optInt.reset();

    if (!optInt) {
        std::cout << "optInt is now empty after reset." << std::endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////// 

//  Variant

// is like a union but safer. It can hold one of several types at a time.
void variant_example() {
    
    std::variant<int, float, std::string> var; // can hold int, float, or string

    var = 42; // holds an int
    std::cout << "Variant holds int: " << std::get<int>(var) << std::endl;

    var = 3.14f; // holds a float
    std::cout << "Variant holds float: " << std::get<float>(var) << std::endl;

    var = "Hello, Variant!"; // holds a string
    std::cout << "Variant holds string: " << std::get<std::string>(var) << std::endl;

    // Using std::visit to handle different types
    std::visit([](auto&& arg) {
        std::cout << "Variant contains: " << arg << std::endl;
    }, var);
}

////////////////////////////////////////////////////////////////////////////////////////////////////// 

// String view 

// string_view is a lightweight, non-owning reference to a sequence 
// of characters. It is useful for passing around strings without copying them.
void string_view_example() {
    
    std::string str = "Hello, String View!";
    std::string_view strView(str); // Create a string_view from a std::string

    std::cout << "String View: " << strView << std::endl;

    // Accessing characters
    for (size_t i = 0; i < strView.size(); ++i) {
        std::cout << strView[i] << " ";
    }
    std::cout << std::endl;

    // Substring
    std::string_view subView = strView.substr(7, 6); // "String"
    std::cout << "Substring: " << subView << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////// 

// Functional

void functional_example() {
    
    // Using std::function to store a lambda
    std::function<int(int, int)> add = [](int a, int b) {
        return a + b;
    };

    int result = add(5, 10);
    std::cout << "Result of addition: " << result << std::endl;

    // Using std::bind to create a new function with some arguments fixed
    auto add_five = std::bind(add, 5, std::placeholders::_1);
    int result2 = add_five(10); // equivalent to add(5, 10)
    std::cout << "Result of adding five: " << result2 << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////// 

// Full example with most of the above features

template<typename T>
class Node {

private:
    std::shared_ptr<Node<T>> next;
    std::shared_ptr<Node<T>> previous;
    T data;

public:
     
    explicit Node(T data): data(data), next(nullptr), previous(nullptr) {}
   
    Node(T data, std::shared_ptr<Node<T>> next, std::shared_ptr<Node<T>> previous): data(data), next(next), previous(previous) {}
    
    // Copy Constructor
    Node(const Node& other): 
        data(other.data), 
        next(other.next), // shared ownership
        previous(other.previous) // shared ownership
        {}

    // Move Constructor
    Node (Node&& other) noexcept: data(other.data), next(std::move(other.next)), previous(std::move(other.previous)) {}

    // Assignment operator
    Node& operator=(const Node& other) {
        if (this == &other) {return *this; }
     
        data = other.data;
        next = other.next;
        previous = other.previous;
        return *this;
    }
    
    // Move assignment 
    Node& operator=(Node&& other) noexcept {
        if (this == &other) {return *this; }
        
        data = other.data;
        next = std::move(other.next);
        previous = std::move(other.previous);

        return *this;
    }

    T get_data() const {
        return this->data;
    }

    std::shared_ptr<Node<T>> get_next() const {
        return this->next;
    }

    std::shared_ptr<Node<T>> get_previous() const {
        return this->previous;
    }

    void set_data(T data) {
        this->data = data;
    }

    void set_next(std::shared_ptr<Node<T>> next) {
        this->next = next; // shared ownership
    }

    void set_previous(std::shared_ptr<Node<T>> previous) {
        this->previous = previous; // shared ownership
    }
    
    bool operator==(Node<T>& other) { 
        return this->data == other.data;
    }

    friend std::ostream& operator<<(std::ostream& os, const Node<T>& node) {
        os << node.data;
        return os;
    }
};

template <typename T>
class Double_Linked_List {

private:

    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> tail;

    size_t len;

public:
    
    // Default Constructor
    Double_Linked_List(): head(nullptr), tail(nullptr), len(0) {}

    // Parameterized Constructor no pointers
    explicit Double_Linked_List(T data): head(std::make_shared<Node<T>>(Node<T>(data))), tail(head), len(1) {}
    
    // Copy constructor
    explicit Double_Linked_List(const Double_Linked_List<T>& other): head(other.head), tail(other.tail), len(other.len) {}

    // Move constructor 
    Double_Linked_List(Double_Linked_List<T>&& other): head(std::move(other.head)), tail(std::move(other.tail)), len(other.len) {}

    // Assigment Operator
    Double_Linked_List<T>& operator=(const Double_Linked_List<T>& other) {

        if (this == &other) return *this;

        head = other.head;
        tail = other.tail;
        len = other.len;

        return *this;
    }

    void append_at_the_start(T data) {
        
        if (this->head == nullptr) {
            this->head = std::make_shared<Node<T>>(Node<T>(data));
            this->tail = this->head;
            this->len++;
            return;
        };
        
        std::shared_ptr<Node<T>> temp = this->head;
        
        Node<T> node = Node<T>(data, temp, this->tail);

        this->head = std::make_shared<Node<T>>(node);
        temp->set_previous(this->head);
        this->tail->set_next(this->head);
        this->len++;
    }

    void append_at_the_end(T data) {

        if (this->head == nullptr) {
            this->head = std::make_shared<Node<T>>(Node<T>(data));
            this->tail = this->head;
            this->len++;
            return;
        };
        
        std::shared_ptr<Node<T>> temp = this->tail;
        
        Node<T> node = Node<T>(data, this->head, temp); 

        this->tail = std::make_shared<Node<T>>(node);
        temp->set_next(this->tail);
        this->head->set_previous(this->tail);

        this->len++;
    }

    void append_at_index(T data, size_t index) {

        if (index >= this->len) return;

        std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>(Node<T>(data));

        int pos= 0;
        std::shared_ptr<Node<T>> dummy = this->head; 

        while (pos < index) {
            pos++;
            dummy = dummy->get_next();
        }
        
        std::shared_ptr<Node<T>> previous = dummy->get_previous(); 
        std::shared_ptr<Node<T>> next = dummy->get_next();

        previous->set_next(node);

        node->set_next(dummy);
        node->set_previous(previous);

        dummy->set_previous(node);

        this->len++;
    }

    void set_at_index(T data, size_t index) {
        
        if (index >= this->len) return;

        std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>(Node(data));

        int pos= 0;
        std::shared_ptr<Node<T>> dummy = this->head; 

        if (this->head == nullptr) {
            
            this->head = std::make_shared<Node<T>>(Node<T>(data));
            this->tail = this->head;
            this->len++;
            return;
        }

        while (pos < index) {
            pos++;
            dummy = dummy->get_next();
        }

        dummy->set_data(data); 
    }

    T get_at_index(size_t index) {

        if (index >= this->len) return T();
        
        int pos= 0;
        std::shared_ptr<Node<T>> dummy = this->head; 
        
        while (pos < index) {
            pos++;
            dummy = dummy->get_next();
        }

        return dummy->get_data();
    }

    T first() {
        return this->head->get_data();
    }

    T last() {
        return this->tail->get_data();
    }

    void remove_head() {

        if (this->head == nullptr) return;

        if (this->head == this->tail) {
            this->head = nullptr;
            this->tail = nullptr;
            this->len--;
            return;
        }

        std::shared_ptr<Node<T>> new_head = this->head->get_next();

        this->tail->set_next(new_head);
        new_head->set_previous(this->tail);
        this->head = new_head;
        this->len--; 
    }
    
    void remove_tail() {
        if (this->head == nullptr) return;
        
        if (this->head == this->tail) {
            this->head = nullptr;
            this->tail = nullptr;
            this->len--;
            return;
        }
        std::shared_ptr<Node<T>> dummy = this->tail;

        std::shared_ptr<Node<T>> new_tail = this->tail->get_previous();
        
        this->head->set_previous(new_tail);
        new_tail->set_next(this->head);
        this->tail = new_tail;
        this->len--;     
    }

    void remove_at_index(size_t index) {

        if (index >= this->len) return;

        if (index == 0) {
            remove_head();
            return;
        }

        if (index == this->len - 1) {
            remove_tail();
            return;
        }

        int pos= 0;
        std::shared_ptr<Node<T>> dummy = this->head; 

        while (pos < index) {
            pos++;
            dummy = dummy->get_next();
        }

        std::shared_ptr<Node<T>> prev = dummy->get_previous(); 
        std::shared_ptr<Node<T>> next = dummy->get_next(); 

        prev->set_next(next);
        next->set_previous(prev);
        this->len--;

    }

    bool operator==(const Double_Linked_List<T>& other) {

        if (this->len != other.len) return false;

        std::shared_ptr<Node<T>> dummy1 = this->head;
        std::shared_ptr<Node<T>> dummy2 = other.head;

        while (dummy1 != nullptr) {
            if (dummy1->get_data() != dummy2->get_data()) {
                return false;
            }
            dummy1 = dummy1->get_next();
            dummy2 = dummy2->get_next();
        }

        return true;
    }

};


// Main Function

int main(int argc, char** argv) {
    
    std::cout << "AHHHHHHHHHHHHHHH" << std::endl;
    return 0;
}
