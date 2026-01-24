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
#include <span>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <random>
#include <condition_variable>

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

// Memory Management C Style

void memory_management_c_style() {

    // Dynamic memory allocation using malloc and free
    int* arr = (int*)malloc(5 * sizeof(int));

    for (int i = 0; i < 5; ++i) {
        arr[i] = i * 10;
    }

    for (int i = 0; i < 5; ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }

    int* temp = (int*)realloc(arr, 10 * sizeof(int));

    if (temp != nullptr) {
        arr = temp;
        for (int i = 5; i < 10; ++i) {
            arr[i] = i * 10;
        }
    }

    free(arr);
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

// Consts

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
    int data;

    // Unlike in c the struct can have member functions
    void display() {
        std::cout << "Data: " << data << std::endl;
    }
};

class Example {

    private: // Private section
        int privateData = 0; // setting default value
        int otherData = 0;

    public: // Public section

        Example() : privateData(0), otherData(0) { // default constructor
            privateData = 0;
            otherData = 0;
        }
        
        Example (const Example&){} // copy construcor. Is called when =, ()

        Example(int val, int otherVal) : privateData(val), otherData(otherVal) { // contructor supporting uniform initialization
            privateData = val;
            otherData = otherVal;
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
}

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

void call_examples() {
    
    int i = 10; 
    int& ref = i;
    
    lvalue_reference_example(ref);
    
    const int& ref2 = 10;     

    lvalue_reference_example(ref2);
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

// Up and Downcasting  

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

// Queue 


//////////////////////////////////////////////////////////////////////////////////////////////////////

// Stack 


//////////////////////////////////////////////////////////////////////////////////////////////////////

// Multimap 


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

}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Regex

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
}

void mutex_example_1() {

    std::mutex mtx;
    int sharedResource = 0;

    auto task = [&mtx, &sharedResource]() {
        
        // lock_guard is a RAII-style mechanism for owning a mutex for the duration of a scoped block
        std::lock_guard<std::mutex> lock(mtx); // Automatically locks and unlocks the mutex
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
        cv.notify_one(); // Notify the consumer
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

// Template Metaprogramming 

// TODO 

//////////////////////////////////////////////////////////////////////////////////////////////////////

// C strings 

#define MAX_LEN 1000

void c_strings() {
    
    char* str = "A normal string with no much to it";
    
    int len = strnlen(str, MAX_LEN); // number of chats plus \0 terminator 

    // Tokenization (destructive)!!!!
    
    char* piece = strtok(str, " "); // returns the string until the separator 
    // will return "A\0"

    piece = strtok(NULL, " "); // will take the previosly used string but now without "A"
    
    printf("%s", piece);
    
    
    // Newer alternaitves 
    char* original = strdup("AHHHHHH, ajbakjnvkjnc , ijajavja");
    char* rest = original;
    char* token;
    
    // Similar to the original but with only one call
    while ((token = strtok_r(rest, ",", &rest))) {
        printf("Token: %s", token);
    }
    
    // This one also return separators separated by separators 
    while ((token = strsep(&original, ",")) != NULL) {
        printf("Token: %s", token);
    }    
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Tagged Unions 

enum result {
    Some,
    Err,
};

struct result_alg {
    
    enum result res; 

    union {
        char* c;
        void* p;
    } value;
};

void demo_tagged_unions() {

    char abc[2] = {'a', 'b'};

    result_alg r = {r.res = Some, r.value.c =abc};

    switch (r.res) {
        case Some: printf("Some content"); break;
        case Err: printf("Error"); break;
        default: printf("Invalid State");
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// memset, memcpy, strcpy, memmove 

#include <ranges>
char* get_deafult_string(int size) {

    char* s = (char*)malloc(sizeof(char)*size);
    
    if (s == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        s[i] = (char)i;
    }

    return s;
}

void memory_functions_example() {
    
    int size = 10; 
    char* s = get_deafult_string(size);
    char* dest = (char*)malloc(sizeof(char) * size);
    char* dest_2 = (char*)malloc(sizeof(char) * size); 

    memset(s, '1', size); // setting all characters to 1
    memcpy(dest, s, size); 
    memmove(dest, s, size); 
    strncpy(dest_2, s, size);

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

// Main Function

int main() {
    
    std::cout << "AHHHHHHHHHHHHHHH" << std::endl;
    return 0;
}
