###############################################################################

# Data Types 

num: int = 10
flt: float = 10.5
string: str = "Hello, World!"
boolean: bool = True
lst: list = [1, 2, 3, 4, 5]
tup: tuple = (1, 2, 3)
dct: dict = {"key1": "value1", "key2": "value2"}
st: set = {1, 2, 3, 4, 5}

###############################################################################

# Control Flow 

if boolean:
    print("Boolean is True")
else:
    print("Boolean is False")

for i in lst:
    print(i)

while num > 0:
    num -= 1    
    print(num)

###############################################################################

# Functions 

def add(a: int, b: int) -> int:
    return a + b

print(add(5, 10))

###############################################################################

# Lambdas 

square = lambda x: x * x
print(square(5))

def apply_function(func, value):
    return func(value)

###############################################################################

# Classes and Objects 

class Person:

    def __init__(self, name: str, age: int):
        self.name = name
        self.age = age

    def greet(self) -> str:
        return f"Hello, my name is {self.name} and I am {self.age} years old."

    def __add__(self, other): # operator overloading
        return Person(f"{self.name} & {other.name}", self.age + other.age)

person = Person("Alice", 30)
print(person.greet())

############################################################################### 

# dunder methods

# Dunder methods allow customization of class behavior for built-in operations.

class Point:

    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y

    def __add__(self, other):
        return Point(self.x + other.x, self.y + other.y)

    def __str__(self):
        return f"Point({self.x}, {self.y})" 

    def __format__(self, format_spec: str) -> str:
        match format_spec:
            case "polar":
                r = (self.x ** 2 + self.y ** 2) ** 0.5
                theta = math.atan2(self.y, self.x)
                return f"Polar(r={r:.2f}, θ={theta:.2f})"
            case _:
                return str(self)

point1 = Point(1, 2)
point2 = Point(3, 4)
point3 = point1 + point2
print(point3)

############################################################################### 

# Operator Overloading

class ComplexNumber:

    def __init__(self, real: float, imag: float):
        self.real = real
        self.imag = imag

    def __add__(self, other):
        return ComplexNumber(self.real + other.real, self.imag + other.imag)

    def __str__(self):
        return f"{self.real} + {self.imag}i"
    
    def __mul__(self, other):   
        real_part = self.real * other.real - self.imag * other.imag
        imag_part = self.real * other.imag + self.imag * other.real
        return ComplexNumber(real_part, imag_part)
    
c1 = ComplexNumber(1, 2)
c2 = ComplexNumber(3, 4)

c3 = c1 + c2
print(c3)
c4 = c1 * c2
print(c4)

############################################################################### 

# Inheritance

class Vehicle:

    def __init__(self, make: str, model: str):
        self.make = make
        self.model = model

    def info(self) -> str:
        return f"{self.make} {self.model}"
    
class Car(Vehicle): 
    
    def __init__(self, make: str, model: str, doors: int):
        super().__init__(make, model)
        self.doors = doors

    def info(self) -> str:
        return f"{super().info()}, Doors: {self.doors}"


############################################################################### 

# Abstract Classes 

from abc import ABC, abstractmethod

class Animal(ABC):

    @abstractmethod         # decorator to define abstract method
    def sound(self) -> str:
        pass

class Dog(Animal):
    
    def sound(self) -> str:
        return "Woof!"

dog = Dog()
print(dog.sound())

############################################################################### 

# Generic Types

from typing import TypeVar, Generic, List

T = TypeVar('T')

class Box(Generic[T]):
    
    def __init__(self, content: T):
        self.content = content

    def get_content(self) -> T:
        return self.content

int_box = Box[int](123)
str_box = Box[str]("Hello")

############################################################################### 

# Interfaces

from typing import Protocol

class Shape(Protocol):

    def area(self) -> float:
        ...

class Rectangle:

    def __init__(self, width: float, height: float):
        self.width = width
        self.height = height

    def area(self) -> float:
        return self.width * self.height
    
rect = Rectangle(5, 10)
print(rect.area())

############################################################################### 

# Generators 

def simple_generator():
    yield 1
    yield 2
    yield 3

# When yield is called, the function's state is saved, and it can be resumed later. 

for value in simple_generator():
    print(value)

x = range(1,11)
print(x)

iter_x = iter(x)

###############################################################################

# List Comprehensions

squared_numbers = [x * x for x in range(10)]
print(squared_numbers)

complex_comprehension = [(x, y) for x in range(3) for y in range(3)]
print(complex_comprehension)

############################################################################### 

# Annotations 

def greet(name: str) -> str:
    return f"Hello, {name}!"

print(greet("Bob"))

###############################################################################

# Dictionaries 

my_dict = {"a": 1, "b": 2, "c": 3}
dict_comprehension = {k: v * v for k, v in my_dict.items()}

for key, value in my_dict.items():
    print(f"{key}: {value}")

ele = my_dict.get("b", "Not Found")
print(ele)

my_dict.update({"d": 4})

print(my_dict)

############################################################################### 

# Other Data Structures and its methods

my_set: set[int] = {1, 2, 3}
my_set.add(4)
my_set.remove(2)
my_set.discard(5)  # No error if element not found
my_set.update({5, 6, 7})
my_set.clear()
print(my_set)

other_set: set[int] = {1,4,5}

# Set math operations 

print(my_set & other_set) # intersection
print(my_set | other_set) # union
print(my_set ^ other_set) # symmetric difference

tuple_example: tuple = (1, 2, 3)
print(tuple_example.count(2))
print(tuple_example.index(3))   


###############################################################################

# Math 

import math

print(math.sqrt(16))
print(math.factorial(5))
print(math.sin(math.pi / 2))
print(math.log(100, 10))

###############################################################################

# Strings 

sample_string: str = "  Hello, Data Science!  "
print(sample_string.lower())
print(sample_string.upper())
print(sample_string.strip())
print(sample_string.replace("Data Science", "Python"))
print(sample_string.split(","))
print(sample_string.find("Data"))

f_string: str = "Name: {}, Age: {}"
print(f_string.format("Alice", 30))


###############################################################################

# Threads 

import threading
def thread_function(name):
    print(f"Thread {name} starting")

thread = threading.Thread(target=thread_function, args=("TestThread",))

thread.start()
thread.join()

###############################################################################

# Processes 

import multiprocessing

def process_function(name):
    print(f"Process {name} starting")   

process = multiprocessing.Process(target=process_function, args=("TestProcess",))
process.start()
process.join()

###############################################################################

# Input / Output 

with open("sample.txt", "w") as file:
    file.write("Hello, World!")

with open("sample.txt", "r") as file:
    content = file.read()
    print(content)

print("Enter your name:")
name = input()
print(f"Hello, {name}!")


###############################################################################

# Iterators 

my_list = [1, 2, 3, 4, 5]
my_iterator = iter(my_list)
print(next(my_iterator))
print(next(my_iterator))
print(next(my_iterator)) 

for item in my_iterator:
    print(item)


###############################################################################

# if __name__ == "__main__"

def main():
    print("This is the main function.")

if __name__ == "__main__": # Entry point of the script
    main()

###############################################################################

# @decorators

# decorators are functions that modify the behavior of other functions. 

def decorator_function(original_function: Callable) ->Callable:

    def wrapper_function(*args, **kwargs): # Accepts any arguments
        print(f"Wrapper executed before {original_function.__name__}") # decorational behavior
        return original_function(*args, **kwargs) # call the original function

    return wrapper_function

@decorator_function
def display():
    print("Display function executed")

display()

###############################################################################

# Comparasion Chainning

a = 5
if 1 < a < 10:
    print(f"{a} is between 1 and 10")

###############################################################################

# Enumerate

my_list = ['apple', 'banana', 'cherry']
for index, value in enumerate(my_list):
    print(f"Index: {index}, Value: {value}")

###############################################################################

#  with 

# with statement is used for resource management and exception handling.

file_path = 'example.txt'
with open(file_path, 'w') as file:
    file.write('Hello, World!')
print(f'File {file_path} written successfully.')

############################################################################### 

# Error Handling

try:
    result = 10 / 0
except ZeroDivisionError as e:
    print(f"Error: {e}")
finally:
    print("Execution completed.")

###############################################################################

# Slicing
# [start:stop:step]

my_list = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

sub_list1 = my_list[2:8:2]  # From index 2 to 7 with step 2
print(sub_list1) 

sub_list2 = my_list[::-1]  # Reverse the list
print(sub_list2)


numbers = [i for i in range(100)]
rev = slice(None, None, -1) # slice object
rev_numbers = numbers[rev]

###############################################################################

# Streams 

import io

stream = io.StringIO()
stream.write("Hello, ")
stream.write("World!")
stream.seek(0) # Move to the beginning of the stream
print(stream.read())

###############################################################################

# mathc 

match_value = 3

match match_value:
    case 1:
        print("Value is 1")
    case 2:
        print("Value is 2")
    case 3:
        print("Value is 3")
    case _:
        print("Value is something else")

###############################################################################

# Walrus Operator

# The walrus operator (:=) allows assignment within expressions.

my_list = [1, 2, 3, 4, 5, 6, 7]

if (n := len(my_list)) > 5:
    print(f"List is too long ({n} elements)")   

###############################################################################

# Options and Defaults

def connect(host: str = "localhost", port: int = 8080):
    print(f"Connecting to {host} on port {port}")

###############################################################################

# Mutltiple Type Hints

def process_data(data: int | str):
    if isinstance(data, int):
        print(f"Processing integer: {data}")
    elif isinstance(data, str):
        print(f"Processing string: {data}")

###############################################################################

# Returning Functions 

from typing import Callable

def outer_function(msg: str) -> Callable:
    def inner_function():
        print(msg)
    return inner_function


###############################################################################

# Async IO 

import asyncio

async def async_function():
    print("Async function started")
    await asyncio.sleep(1)
    print("Async function completed")

asyncio.run(async_function())

###############################################################################

# Exec

# exec function executes dynamically created Python code. 

code = """def hello():
    print("Hello from exec!")
hello()"""

exec(code) 

###############################################################################

# Partial 

from functools import partial

def multiply(x, y):
    return x * y

double = partial(multiply, 2)
print(double(5))  # Output: 10

###############################################################################

# permutations and combinations

from itertools import permutations, combinations, combinations_with_replacement


data = [1, 2, 3]
perm = permutations(data, 2)
comb1 = combinations(data, 2)
comb2 = combinations_with_replacement(data, 2)

print(list(perm))
print(list(comb1))
print(list(comb2))

###############################################################################

# Choice, choices, shuffle, sample, random numbers

import random

data = [1, 2, 3, 4, 5]
print(random.choice(data))  # Single random element
print(random.choices(data, k=3))  # List of 3 random elements with replacement
random.shuffle(data)  # Shuffle the list in place
print(data)
print(random.sample(data, 3))  # List of 3 unique random elements

print(random.randint(1, 10))  # Random integer between 1 and 10
print(random.random())  # Random float between 0.0 and 1.0

###############################################################################

# Unpacking

a, b, *rest = [1, 2, 3, 4, 5]
print(a)      # 1
print(b)      # 2
print(rest)   # [3, 4, 5]

# Using * for unpacking in function calls
def add_3(x, y, z):
    return x + y + z    
numbers = [1, 2, 3]
print(add_3(*numbers))  # Unpacking list into function arguments

###############################################################################

# side effects in functions

# only objects are mutable, not primitives 

side_effect_list = []

def add_to_list(item):
    side_effect_list.append(item)
