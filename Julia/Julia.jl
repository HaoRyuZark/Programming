# Imported modules
using Printf # Needed to use printf
using Statistics

# ----- VARIABLES -----
# Types are dynamically assigned and can be changed
# Variables start with _, letters and then numbers, or !
s = 0
s = "Dog"
println(s)

# ----- DATA TYPES -----
# You can assert a datatype and an error would be thrown
# if you tried to assign an incorrect value
#function changeNum()
#    x::Int8 = 10
#    x = "Dog"
#end
#changeNum()
# Bool : true or false
canDrive = true

# Int8 : -128 - 127
# Int16 : −32,768 - 32,767
# Int32 : −2,147,483,648 - 2,147,483,647
# Int64 : −2^63 - 2^63 - 1
# Float32, Float64, UInt8, UInt16, etc.

# Float addition is accurate to about 14 digits
bF = 1.111111111111111
println(bF + 0.111111111111111)

# get_bigfloat_precision() in the REPL says
# that BigFloats are by default accurate to
# 256 bits
# We can increase the precision with BigFloats
# Also there is BigInt

# Chars store any UTF-8 unicode character
c1 = 'A'

# ----- CASTING -----
# Cast from Int to Char
c2 = Char(120)
println(c2)

# Cast from Float to Int
i1 = UInt8(trunc(3.14))
println(i1)

# Cast string to Float
f1 = parse(Float64,"1")
println(f1)

# Cast string to Int
i2 = parse(Int8,"1")
println(i2)

# ----- STRINGS -----
s1 = "Just some random words\n"

# Size of string
println(length(s1))

# The 1st index is at 1
println(s1[1])

# Get last character
println(s1[end])

# Get a range
println(s1[1:4])

# Concatenation
s2 = string("Yukiteru", " Amano")
println(s2)

# And
println("Yuno" * " Gasai")

# Interpolation
i3 = 2
i4 = 3
println("$i3 + $i4 = $(i3 + i4)")

# Multiline strings
s3 = """I
have
many
lines"""
println(s3)

# String comparisons with == > < !=
println("Takao" > "Hiyama")

# Find index for character
println(findfirst(isequal('i'), "Keigo"))

# Find a substring
println(occursin("key", "monkey"))

# ----- CONDITIONALS -----
age = 12
if age >= 5 && age <= 6
    println("You're in Kindergarten")
elseif age >= 7 && age <= 13
    println("You're in Middle School")
elseif age >= 14 && age <= 18
    println("You're in High School")
else
    println("Stay Home")
end

@printf("true || false = %s\n", true || false ? "true" : "false")
@printf("!true = %s\n", !true ? "true" : "false")

age = 55
@printf("Can I drive : %s\n", age > 16 ? "true" : "false")

# ----- LOOPING -----
i = 1

while i < 20
    if (i % 2) == 0
        println(i)
        global i += 1
        continue # Skip the rest of the code in the loop
    end

    # Make the code use the global i
    global i += 1

    if i >= 10
        break # Jump out of the loop
    end
end

# Using a range with for
for i = 1:5
    println(i)
end

# Using an array
for i in [2,4,6]
    println(i)
end

# Loop while iterating multiple variables
# The 2nd value in the j range is the step
for i = 1:5, j = 2:2:10
    println((i, j))
end

# ----- ARRAYS -----
# Create an array of zeros
a1 = zeros(Int32, 2, 2)

# Create array of Int32s
a2 = Array{Int32}(undef, 5)

# Or like this
a3 = Float64[]

# Create an array
a4 = [1,2,3]

# Get value at index
println(a4[1])

# Get last value
println(a4[end])

# Check if value exists
println(5 in a4)

# Get 1st index
println(findfirst(isequal(2), a4))

# Find all matches using a generic function
f(a) = (a >= 2) ? true : false
println(findall(f, a4))

# How many items pass the test
println(count(f, a4))

# Get row and column size
println(size(a4))

# Get number of elements
println(length(a4))

# Sum values
println(sum(a4))

# Put values starting at 2nd index
splice!(a4, 2:1, [8,9])
println(a4)

# Remove items at index 2 through 3
splice!(a4, 2:3)
println(a4)

# Get max & min value
println(maximum(a4))
println(minimum(a4))

# Perform calculations on an array without looping
println(a4 * 2)

# You can use multiple types or Any
a5 = [1,3.14,"Hello"]

# You can store functions
a6 = [sin, cos, tan]
for n in a6
    println(n(0))
end

# Multidimensional array
a7 = [1 2 3; 4 5 6]
for n = 1:2, m = 1:3
    @printf("%d ", a7[n,m])
end
println()

# Get every row in the 2nd column
println(a7[:, 2])

# Every row 2nd column
println(a7[2, :])

# Array from a range
a8 = collect(1:5)

# Range with a step (step is 2nd value)
# Or backward collect(4:-1:1)
a9 = collect(2:2:10)
for n in a9 print(n) end
println()

# Create an array with a comprehension
a10 = [n^2 for n in 1:5]

# Add value to array
push!(a10, 36)
println(a10)

# Create a multidimensional array
a11 = [n * m for n in 1:5, m in 1:5]
println(a11)

# Generate a 5 by 5 random array with values between 0 - 9
a12 = rand(0:9, 5, 5)
for n = 1:5
    for m = 1:5
        print(a12[n, m])
    end
    println()
end

# ----- TUPLES -----
# Most array functions work with Tuples except tuple
# values cannot be changed
t1 = (1,2,3,4)
println(t1)

# Get a value
println(t1[1])

# Get all
for i in t1
    println(i)
end

# Multidimensional tuple
t2 = ((1,2), (3,4))
println(t2[1][1])

# Named tuple
t3 = (sue = ("Sue", 100), paul = ("Paul", 23))
println(t3.sue)

# ----- DICTIONARIES -----
# Dictionaries are key value pairs where the key moust be
# unique
d1 = Dict("pi"=>3.14, "e"=>2.718)

# Get value
println(d1["pi"])

# Add a kv
d1["golden"] = 1.618

# Delete a kv
delete!(d1, "pi")

# Check if key exists
println(haskey(d1, "pi"))

# Check for key & value
println(in(("pi"=>3.14)))

# Display all keys
println(keys(d1))

# Display all values
println(values(d1))

# Display both
for kv in d1
    println(kv)
end

# Control display of kv
for(key, value) in d1
    println(key, " : ", value)
end

# ----- SETS -----
# Sets are arrays with all unique values
st1 = Set(["Jim", "Pam", "Jim"])
println(st1)

# Add a value
push!(st1, "Michael")

# Check for value
println(in("Dwight", st1))

# Combine sets
st2 = Set(["Stanley", "Meredith"])
println(union(st1, st2))

# Every item both sets have
println(intersect(st1, st2))

# Items in 1st, but not 2nd
println(setdiff(st1, st2))

# ----- FUNCTIONS -----
# This is a single expression function
getSum(x,y) = x + y
x, y = 1, 2
@printf("%d + %d = %d\n", x, y, x+y)

# Multiple expression functions
# You can asign default values
function canIVote(age=16)
    if age > 18
        println("Can Vote")
    else
        println("Can't Vote")
    end
end
canIVote(43)

# Arguments are pass by value
v1 = 5
function changeV1(v1)
    v1 = 10
end
changeV1(v1)
println(v1)

# You can use globals inside functions
function changeV12()
    global v1 = 10
end
changeV12()
println(v1)

# Variable arguments
function getSum2(args...)
    sum = 0
    for a in args
        sum += a
    end
    println(sum)
end
getSum2(1,2,3,4)

# Return multiple values
function next2(val)
    return (val + 1, val + 2)
end
println(next2(4))

# Functions that return functions
function makeMultiplier(num)
    return function (x) return x * num end
end

mult3 = makeMultiplier(3)
println(mult3(6))

# Handle different types of arguments
function getSum3(num1::Number, num2::Number)
    return num1 + num2
end

function getSum3(num1::String, num2::String)
    return parse(Int32, num1) + parse(Int32, num2)
end

f1 = parse(Float64,"1")

println("5 + 4 = ", getSum3(5,4))
println("5 + 4 = ", getSum3("5","4"))

# ----- ANONYMOUS FUNCTIONS -----
# Functions with no name that are used inline
# Map applies a function to each item
v2 = map(x -> x * x, [1,2,3])
println(v2)

# Add arrays
v3 = map((x,y) -> x + y, [1,2], [3,4])
println(v3)

# Reduce uses a function multiple times for 1 result
v4 = reduce(+, 1:100)
println(v4)

# Get longest word in a sentence
sentence = "This is a string"
# Convert string to array
sArray = split(sentence)
longest = reduce((x, y) -> length(x) > length(y) ? x : y, sArray )
println(longest)


# ----- MATH -----
@printf("5 + 4 = %d\n", (5 + 4))
@printf("5 - 4 = %d\n", (5 - 4))
@printf("5 * 4 = %d\n", (5 * 4))
@printf("5 / 4 = %d\n", (5 / 4))
println("5 % 4 = ", (5 % 4))
@printf("5 ^ 4 = %d\n", (5 ^ 4))

@printf("round(3.5) = %d\n", round(3.5))
@printf("floor(3.5) = %d\n", floor(3.5))
@printf("ceil(3.5) = %d\n", round(3.5))
@printf("abs(-3.5) = %d\n", abs(-3.5))
@printf("sqrt(100) = %d\n", sqrt(100))
@printf("cbrt(100) = %d\n", cbrt(100))
@printf("hypot(90,90) = %d\n", hypot(90,90))
@printf("exp(2) = %d\n", exp(2))
@printf("log(100) = %d\n", log(100))
@printf("log2(100) = %d\n", log2(100))
@printf("log10(100) = %d\n", log10(100))

# Trig Functions : sin, cos, tan, cot, sec, csc
# sinh, cosh, tanh, coth, sech, csch
# asin, acos, atan, acot, asec, acsc
# asinh, acosh, atanh, acoth, asech, acsch
# sinc, cosc

# Shortcuts available += -= *= /= ^=

# You can imply multiplication without *
x = 5
println(2x)

# Dot operators perform operations on arrays
a13 = [1,2,3]
println(a13 .* 3)

# ----- ENUMS -----
@enum Color begin
    red = 1
    blue = 2
    green = 3
end

favColor = green::Color
println(favColor)

# ----- SYMBOLS -----
# Symbols are immutable strings that represent
# a variable as data
:Derek
println(:Derek)

# They are commonly used as keys with dictionaries
d2 = Dict(:pi=>3.14, :e=>2.718)
println(d2[:pi])

# ----- STRUCTS -----
# Structs are composite types, or a type that contains
# many fields
struct Customer
    name::String
    balance::Float32
    id::Int
end

# Create a Customer object
bob = Customer("Bob Smith", 10.50, 123)
println(bob.name)

# Structs by default are immutable
# ERROR bob.name = "Sue Smith"
# You could change that with mutable struct Customer

# ----- ABSTRACT TYPES -----
# Abstract types can't be instantiated like Structs
# but they can have subtypes
abstract type Animal end

struct Dog <: Animal
    name::String
    bark::String
end

struct Cat <: Animal
    name::String
    meow::String
end

bowser = Dog("Bowser", "Ruff")
muffin = Cat("Muffin", "Meow")

function makeSound(animal::Dog)
    println("$(animal.name) says $(animal.bark)")
end

function makeSound(animal::Cat)
    println("$(animal.name) says $(animal.meow)")
end

makeSound(bowser)
makeSound(muffin)

# ----- EXCEPTION HANDLING & USER INPUT -----
# Throw and handle errors
print("Enter a number ")
num1 = chomp(readline())

print("Enter a number ")
num2 = chomp(readline())

try
    val = (parse(Int32, num1)) / (parse(Int32, num2))
    if (val == Inf)
        error("Can't divide by zero")
    else
        println(val)
    end
catch e
    println(e)
end

# ----- FILE IO -----
# Open file for writing
open("random.txt", "w") do file
    write(file, "Here is some random text\nIt is great\n")
end

# Open a file for reading
open("random.txt") do file
    # Read whole file into a string
    data = read(file, String)
    println(data)
end

open("random.txt") do file
    # Read each line 1 at a time
    for line in eachline(file)
        println(line)
    end
end

# ----- MACROS -----
# Macros generate code before the program is run

# Execute passed code a certain number of times
macro doMore(n, exp)
  quote

      # esc hides what it contains until everything
      # is ready to be executed
    for i = 1:$(esc(n))
      $(esc(exp))
    end
  end
end

@doMore(2, println("Hello"))

# Create a do while loop
macro doWhile(exp)
    # Assert that while is the first element passed
  @assert exp.head == :while

  # quote is the same as begin ... end
  esc(quote

  # Contains the body of the loop
    $(exp.args[2])
    $exp
  end)
end

z = 0
@doWhile while z < 10
    global z += 1
    println(z)
end