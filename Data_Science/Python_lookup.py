

###############################################################################

# GIL 

# The global interpreter lock is mutex which allows only one thread to run python code at the time
# The reason for this, it to make the reference counting system to be thread-safe, but it has the effect that true parallelism is impossible.
# The GIL is progressively being removed to increase the performance.

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

# Python allows both single and multiple Inheritance

class Vehicle:

    def __init__(self, make: str, model: str):
        self.make = make
        self.model = model

    def info(self) -> str:
        return f"{self.make} {self.model}"

# By polymorphism instances of this class can be traated as Cars or Vehicles
class Car(Vehicle): 
    
    def __init__(self, make: str, model: str, doors: int):
        super().__init__(make, model) # calling parent constructor
        self.doors = doors

    def info(self) -> str:
        return f"{super().info()}, Doors: {self.doors}"


############################################################################### 

# Ducktyping 

# Another way of achiving polymorphism by enforcing objects to have a minimum necessary attributes or methods

class Person:
    alive = True 
    def be(self):
        print("Be")

class Otaku(Person): 
    likes= "Anime" 

class Normie(Person):
    has_a_girlfriend = True 

class Element:
    def be(self): # elements satisfies the minimal requirement for the functionality implemented in the loop below
        print("Be")

duck_list = [Otaku(), Normie(), Element()]

for e in duck_list:
    e.be()  

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

# They are used to return values, pausing the function and them be resumed if the main thread 
# tells the function to continue

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

# We can also ask a generator to produce a value via the next() method 

gen_obj = simple_generator()

next(gen_obj) # return 1 
next(gen_obj) # return 2 
next(gen_obj) # return 3
# next(gen_obj) now return an iteration error

def prime_generator(start, end):
    
    if start > end:
        return

    for num in range(start, end + 1):
        limit = int(math.sqrt(num)) + 1
        for n in range(2, limit):

            if num % n == 0:
                break;
            if n == limit:
                yield num
 
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

sample_string.capitalize()

sample_string.lower() 

sample_string.upper()

sample_string.casefold() # returns a version where the case does not matter for comparasions

sample_string.center(20) # centers the text in the console

sample_string.count('H') # count occurences of a pattern

sample_string.encode(encoding="UTF-8") # returns a byte array of the string

sample_string.endswith('a') # returnf if the string ends with the substring
sample_string.endswith(('', ' ')) # tuple work as or

sample_string.strip('pattern') # remove the pattern

sample_string.replace("Data Science", "Python", 1) # the last parameter is the limit which is optional

sample_string.split(",") # split at separator

sample_string.find("Data") # finds the index first and last occurence of the substring

sample_string_2 = 'I love {person}'
sample_string_2.format(person='Ren')

f_string: str = "Name: {}, Age: {}"
print(f_string.format("Alice", 30))

dict_t = {'person': 'Micha'}
sample_string_2.format_map(dict_t)

sample_string.index('Science') # return the start index of the first occurrence of the pattern

sample_string.isalnum() # is alpha numeric

sample_string.isalpha()

sample_string.isascii()

sample_string.isdecimal() # if all characters in the string are decimal and there is at least one character in the string

sample_string.isdigit() # if all characters in the string are digits and there is at least one character in the string

sample_string.isnumeric() # if all characters in the string are numeric and there is at least one character in the strin

sample_string.isidentifier() # if can be used as a var name in python

sample_string.islower()

sample_string.isprintable() # if there are not scape-sequences

sample_string.isspace()

sample_string.istitle() # if in Title Syntax

sample_string.isupper()

text = '-'.join(['a', 'b', 'c'])

text.ljust(20, '_') #  adjust left and fill the rest with the other sequence

text.rjust(20, '-') # same as left but for the right

sample_string.lstrip() #

table = text.maketrans('a', 'z') # translation table
text.translate(table)

text.partition('-') # split at the pattern

sample_string.removeprefix('Hello')

sample_string.removesuffix('Sciece!')

text.rfind('c') # find starting from the end

text.rindex('c') # same as above but for the right-starting case

text.rpartition('=')

text.rsplit('-')

sample_string.rstrip() # string from the right side

sample_string.splitlines(keepends=True)

sample_string.startswith(' ')

sample_string.swapcase()

sample_string.title() # convert to title case

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

from typing import Union 

def process_data(data: int | str):  # union of tyoes
    if isinstance(data, int):
        print(f"Processing integer: {data}")
    elif isinstance(data, str):
        print(f"Processing string: {data}")

var: Union[float, str] = 10 # variable which can be either a string, a float or all the subtypes of float like int

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

###############################################################################

# Counter

from collections import Counter

l = ["A", "B", "C"]

c = Counter(l) # returns a dictionary with the uniques of the list as keys as their occurrences as values
c.update(["A"]) # based on its previous state it updates it accordingly to its content

###############################################################################

# List Methods

l = [1,2,3,4,5,5,6,6,7,6,6,43,1]

l.append(68) # add 68 to the tail

lc = l.copy() # creates a shallow copy

l.count(4) # count occurrences of 4

l.extend([9,0,1]) # concatenates the other list

l.index(42) # return the index of the first occurence

l.insert(0, 29) # at index i put element x

l.pop() # return the last element

l.pop(0) # return the element at the specified index

l.remove(6) # remove the element x

l.reverse() # reverses the list

l.sort() # sorts

l.clear() # empties the list

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

users = {0: 'A', 1: 'B', 2 : 'C'}

users.keys() # iterator over the keys

users.values() # iterator over the values

users_c = users.copy() # creates a shallow copy

users.get(0) # get element based on the key

users.setdefault(99, '99') # if the key does not exist it is inserted with the value and then returned

dict2 = users.fromkeys(['A', 'B', 'C'], 'Something') # creates a dictionary from an iterable whose elements are going to be the keys
# we can also pass a default val for the values instead of having None

users.items() # returns all the key value pairs

users.update({3: 'James'})

users.pop(0) # removes by key and return the value

users.popitem() # pops the last item

users.clear() # deletes the contents






