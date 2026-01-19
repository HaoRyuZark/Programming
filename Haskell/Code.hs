-- Comment 
import Data.List 
import System.IO

-- Arithmetic -------------------------------------------------------------------------

x = 5 
y = 10 

s = x + y
d = y - x
p = x * y
q = y `div` x
r = y `mod` x

-- Lists -------------------------------------------------------------------------

primeNumbers = 2 : 3 : 5 : []

revPrimeNumbers = reverse primeNumbers

secondPrime = primeNumbers !! 1  -- !! is used to access list elements by index

firstPrime = head primeNumbers  -- head gets the first element of the list
lastPrime = last primeNumbers    -- last gets the last element of the list

is7InPrimes = 7 `elem` primeNumbers  -- elem checks for membership in a list

morePrimes = init primeNumbers ++ [7, 11, 13]  -- init gets all but the last element

numbers :: [Int]
numbers = [1, 2, 3, 4, 5]

squaredNumbers :: [Int]
squaredNumbers = map (^2) numbers

evenNumbers :: [Int]
evenNumbers = filter even numbers

evenList = [2,4..20]  -- List of even numbers from 2 to 20
oddList = [1,3..19]   -- List of odd numbers from 1
mixedList = [1,2..10]  -- List of numbers from 1 to 10

manyPrimes = take 5 (repeat 7)  -- List with five 7s

listTimes2 = [x * 2 | x <- [1..10]]  -- List comprehension to double each number

sumOfLists = zipWith (+) [1,2,3] [4,5,6]  -- Element-wise addition of two lists

getListItems :: [Int] -> String 
getListItems []       = "The list is empty." -- Pattern matching for empty list
getListItems (x:[])   = "The list has one item: " ++ show x -- Pattern matching for single item list
getListItems (x:y:[]) = "The list has two items: " ++ show x ++ " and " ++ show y -- Pattern matching for two item list
getListItems (x:xs)   = "The list has many items. The first item is: " ++ show x -- Pattern matching for list with many items

areStringsEqual :: String -> String -> Bool
areStringsEqual [] [] = True 
areStringsEqual (x:xs) (y:ys) = x == y && areStringsEqual xs ys
areStringsEqual _ _ = False

-- Pattern Matching -------------------------------------------------------------------------

describeNumber :: Int -> String
describeNumber 0 = "Zero"
describeNumber 1 = "One"
describeNumber 2 = "Two"
describeNumber _ = "A number greater than two"  -- _ is a wildcard pattern

-- x:xs pattern splits the list into head (x) and tail (xs) 

getFirstItem :: String -> String

getFirstItem [] = "The string is empty." 
getFirstItem all@(x:xs) = "The first character is: " ++ [x] ++ " in the string: " ++ all -- as-pattern to capture the whole string

-- Functions -------------------------------------------------------------------------

greet :: String -> String
greet personName = "Hello, " ++ personName ++ "!"  -- ++ is used for concatenation

factorial :: Int -> Int
factorial 0 = 1
factorial n = n * factorial (n - 1) 

getAddFunc :: Int -> (Int -> Int)
getAddFunc x y = x + y

adds3 = getAddFunc 3 


-- Built-in Math Functions -------------------------------------------------------------------------

absoluteValue :: Int -> Int
absoluteValue n = abs n 

maximumValue :: [Int] -> Int
maximumValue nums = maximum nums

minimumValue :: [Int] -> Int
minimumValue nums = minimum nums

squareRoot :: Floating a => a -> a -- => indicates a type constraint
squareRoot n = sqrt n

power :: (Num a, Integral b) => a -> b -> a -- multiple type constraints
power base exp = base ^ exp

logarithm :: Floating a => a -> a
logarithm n = log n

-- Tuples -------------------------------------------------------------------------

person :: (String, Int)
person = ("Alice", 30)

names = ["Alice", "Bob", "Charlie"]
ages = [30, 25, 35]

namesAndAges :: [(String, Int)]
namesAndAges = zip names ages  -- zip combines two lists into a list of tuples

-- Guards and Where ------------------------------------------------
-- Guards are used for conditional expressions

bmiCategory :: Double -> Double -> String

bmiCategory weight height
    | bmi <= 18.5 = "Underweight"
    | bmi <= 24.9 = "Normal weight"
    | bmi <= 29.9 = "Overweight"
    | otherwise   = "Obesity"
    where bmi = weight / (height ^ 2)   

-- Lambdas ------------------------------------------------

doubleList :: [Int] -> [Int]
doubleList nums = map (\x -> x * 2) nums  -- Lambda function to double each element

-- If Else ------------------------------------------------
isEven :: Int -> String
isEven n = if n `mod` 2 == 0
        then "Even"
        else "Odd"


-- Case ------------------------------------------------

describeList :: [a] -> String
describeList xs = case xs of
    [] -> "The list is empty."
    [x] -> "The list has one item."
    [x,y] -> "The list has two items."
    _ -> "The list has many items." 

-- Enumerations ------------------------------------------------

data Day = Monday | Tuesday | Wednesday | Thursday | Friday | Saturday | Sunday deriving (Show, Eq, Enum) -- Enum allows listing all values 

-- deriving Show allows printing the values
-- deriving Eq allows comparison of values
-- deriving Enum allows enumeration of values

-- Custom Data Types ------------------------------------------------

data Shape = Circle Double | Rectangle Double Double deriving (Show) -- Circle with radius, Rectangle with width and height

area :: Shape -> Double
area (Circle r) = pi * r ^ 2
area (Rectangle w h) = w * h    

-- dot and dollar sign operators 
-- dot operator (.) is used for function composition | f . g means f(g(x))
-- dollar sign operator ($) is used to avoid parentheses 

circle = Circle 10 

sumValue = putStrLn . show $ area circle 

calculateCircleArea :: Double -> Double
calculateCircleArea r = area (Circle r)

calculateRectangleArea :: Double -> Double -> Double
calculateRectangleArea w h = area (Rectangle w h)

-- Type Classes ------------------------------------------------
-- Define a type which implements a function
class Describable a where
    describe :: a -> String

-- Type Instance

data ShirtSize = S | M | L
instance Eq ShirtSize where  -- Specify behaviour of the Eq Type class for the Shirtsize
    S == S = True
    M == M = True
    L == L = True
    _ == _ = False 

-- Monads and IO ------------------------------------------------

printGreeting :: String -> IO ()
printGreeting name = putStrLn ("Hello, " ++ name ++ "!")  -- putStrLn is an IO action that prints to standard output
readAndPrint :: IO ()
readAndPrint = do
    putStrLn "Enter your name:"
    name <- getLine  -- getLine is an IO action that reads a line from standard input
    putStrLn ("Hello, " ++ name ++ "!") -- Using do notation to sequence IO actions

-- Open and Read Files ------------------------------------------------

writeToFile = do 
    theFile <- openFile "test.txt" WriteMode
    hPutStrLn theFile "Random Text"
    hClose theFile

readFile = do 
    theFile <- openFile "test.txt" ReadMode
    contents <- hGetContents theFile
    putStr contents
    hClose theFile


-- Fibonacci 

fib1 :: Int -> Int 
fib1 1 = 1 
fib1 0 = 1 
fib1 x = fib1 (x - 1) + fib1 (x - 2)  

fib2 :: Int -> [Int]
fib2 n = [fib1 x | x <- [1..n]]

-- main function ------------------------------------------------

main :: IO ()
main = do 
    putStrLn "Hello" -- putStrLn prints a line to standard output





