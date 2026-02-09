%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Facts

% what is specified inside the parenthesis are the so called atoms which act as constants

loves(romeo, juliet). % this is a fact 

loves(juliet, romeo) :- loves(romeo, juliet). % :- is use as an if 

% More facts
male(albert).
female(juliet).

% An atom can contain letters, numbers, +, -, _, *, /, <, >, :, ., ~, &

% male(X), female(Y). = Show all combinations of male and female

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Rules

happy(albert).
happy(alice) :- happy(albert).
with_albert(alice).

runs(albert) :-  % read: albert runs if he is happy
    happy(albert).

dances(alice) :- 
    happy(alice),   % the coma works as and
    with_albert(alice).

dances_else(alice) :- 
    happy(alice). 

human(i).
human(you).
human(she).

loves(i, X) :- loves(X, i), human(X). % this returns she
loves(she, i).

text_is_equal(T1, T2) :- T1 == T2. 
text_is_not_equal(T1, T2) :- T1 \= T2. 


% when defining two rules with the same name their conditions are treated as  
% or
does_alice_dances(alice) :- dances(alice),
    write('Output string'). % write is used to print output

does_alice_dances(alice) :- dances_else(alice),
    write('Output string').


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Variables
% varialbles are allways upperc case
% loves(X, Y) will give us all possible valid combinations (run inside the terminal)

stabs(tybalt, mercutio, sword). 
hates(romeo, X) :- stabs(X, mercutio, sword).

parent(albert, bob).
parent(albert, betsy).
parent(albert, bill).

parent(alice, bob).
parent(alice, betsy).
parent(alice, bill).

parent(bob, carl).
parent(bob, charlie).

% When you are cycling through the results the no at the end signals
% that there are no more results
% parent(X, bob). X = albert, X = alice

% parent(X, bob), dances(X). X = alice

% We can use _ (anonymous variable) if we won't use the variable more than once

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Case Statements

what_grade(5):- 
    write('Kinder').
    
what_grade(6):- 
    write('Grade').

what_grade(Other):-
    Grade is Other - 5,
    format('Go to grade ~w', [Grade]).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Structures

%pet named Olive?

owns(albert, pet(cat, olive)).


customer(tom, smith, 20.55).
customer(sally, smith, 120.55).

% An anonymous variable is used when we don't want a value returned
% Is there a customer named sally and what is her balance
% customer(sally,_,Bal).

% Use a complex term to define what it means to be a vertical
% versus a horizontal line
vertical(line(point(X, Y), point(X, Y2))).
horizontal(line(point(X, Y), point(X2, Y))).

% vertical(line(point(5, 10), point(5, 20))). = yes
% horizontal(line(point(10, 20), point(30, 20))).

% We can also ask what the value of a point should be to be vertical
% vertical(line(point(5, 10), point(X, 20))). = X = 5

% We could also ask for the X and Y points
% vertical(line(point(5, 10), X)). = X = point(5,_)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Trace



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Recursion

% Use recursion to loop
count_to_10(10) :- write(10), nl.

count_to_10(X) :-
  write(X),nl,
  Y is X + 1,   % re-assign
  count_to_10(Y).

% Receives Low (lowest value) and High (highest value)
count_down(Low, High) :-
  % Assigns values between Low and High to Y
  between(Low, High, Y),
  % Assigns the difference to Z
  Z is High - Y,
  write(Z),nl,
  % Continue looping until Y = 10
  Y = 10.

count_up(Low, High) :-
  between(Low, High, Y),
  Z is Y + Low,
  write(Z), nl,
  Y = 10.

% Loop until they guess a number
% start is a dummy value used to start the looping
guess_num :- loop(start).

% When they guess 15 they execute this message and exit
loop(15) :- write('You guessed it!').

loop(X) :-
  x \= 15,
  write('Guess Number '),
  read(Guess),
  write(Guess),
  write(' is not the number'), nl,
  loop(Guess).

% guess_num.
% Guess Number 12.
% 12 is not the number
% Guess Number 15.
% 15 is not the number
% You guessed it!

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Math 

% Prolog provides 'is' to evaluate mathematical expressions
% X is 2 + 2. = X = 4

% You can use parenthese
% X is 3 + (2 * 10). =  X = 23

% You can also make comparisons
% 50 > 30. = yes
% (3*10) >= (50/2). = yes
% \+ (3 = 10). = yes (How to check for not equal)
% 5+4 =:= 4+5. = yes (Check for equality between expressions)
% 5+4 =\= 4+5. = yes (Check for non-equality between expressions)
% 5 > 10 ; 10 < 100. (Checks if 1 OR the other is true)

% X is mod(7,2). = X = 1 (Modulus)

double_digit(X,Y) :- Y is X*2.
% double_digit(4,Y). = Y = 8
% Take the 1st argument, multiply it times 2 and return it as the
% 2nd argument

% Get random value between 0 and 10
% random(0,10,X).

% Get all values between 0 and 10
% between(0,10,X).

% Add 1 and assign it to X
% succ(2,X).

% Get absolute value of -8
% X is abs(-8).

% Get largest value
% X is max(10,5).

% Get smallest value
% X is min(10,5).

% Round a value
% X is round(10.56).

% Convert float to integer
% X is truncate(10.56).

% Round down
% X is floor(10.56).

% Round up
% X is ceiling(10.56).

% 2^3
% X is 2** 3.

% Check if a number is even
% 10//2 = 5 (is 10 = 2 * 5)
is_even(X) :- Y is X//2, X =:= 2 * Y.

% sqrt, sin, cos, tan, asin, acos, atan, atan2, sinh, cosh, tanh,
% asinh, acosh, atanh, log, log10, exp, pi, e

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% INPUT / OUTPUT

% write('You saw me'), nl.

% writeq('I show quotes'), nl.

% You can read data with read
say_hi :-
  write('What is your name? '),
  read(X),
  write('Hi '),
  write(X).

% Procedure like statement
fav_char :-
  write('What is your favorite character? '),

  % Receives a char and saves its ascii value to X
  get(X),
  format('The Ascii value ~w is ', [X]),

  % Outputs Ascii value as the char
  put(X),nl.

% Write to a file by defining the file, text to write, connection
% to the file (Stream)
write_to_file(File, Text) :-
  open(File, write, Stream),
  write(Stream, Text), nl,
  close(Stream).

% Read from a file
read_file(File) :-
        open(File, read, Stream),

        % Get char from the stream
        get_char(Stream, Char1),

        % Outputs the characters until end_of_file
        process_stream(Char1, Stream),
        close(Stream).

% Continue getting characters until end_of_file
% ! or cut is used to end backtracking or this execution
process_stream(end_of_file, _) :- !.

process_stream(Char, Stream) :-
        write(Char),
        get_char(Stream, Char2),
        process_stream(Char2, Stream).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Lists

% They can be used to store atoms and other more complex terms


% Constructing a list 
wirte([albert | [alice, john]]).

% Get the length
length([1,2,3]).

% Dividing a list
% [H | T] = [a,b,c] % where H = a, T [b, c]

% Check if an element is in a list
%member(a, [a,b,c])

% Custom contains function
contains(X, [X|R]).
contains(X, [Y|R]) :- contains(X, R).

% Reverse a list
% reverse([1,2,3,4,5], X).

% Concatenate 2 lists
% append([1,2,3], [4,5,6], X).

apppend2([], L, L).
apppend2([X|R], L, [X|T]) :- apppend2(R, L, T). % it takes three lists: l1, l2, out output; and L a parameter to work with

% Write items in list on separate line
write_list([]).

wirte_list([Head|Tail]) :-
  write(Head), nl,
  write_list(Tail).
% write_list([1,2,3,4,5]). = Outputs the list

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Strings

% Convert a string into an Ascii character list
% name('A random string', X).

% Convert a Ascii character list into a string
% name(X, [65,32,114,97,110,100,111,109,32,115,116,114,105,110,103]).

% Append can join strings
join_str(Str1, Str2, Str3) :-

  % Convert strings into lists
  name(Str1, StrList1),
  name(Str2, StrList2),

  % Combine string lists into new string list
  append(StrList1, StrList2, StrList3),

  % Convert list into a string
  name(Str3, StrList3).

% join_str('Another ', 'Random String', X). = X = 'Another Random String'

% get the 1st char from a string
/*
name('Derek', List),
nth0(0, List, FChar),
put(FChar).
*/

% Get length of the string
atom_length('Derek',X).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Fibonachi

fib(0, 0).
fib(1, 1).

fib(X, Y):- X > 1, X1 is X - 1, X2 is X-2, fib(X1, Y1), fib(X2, Y2), Y = Y1 + Y2.

% use fib(5, Y): is 5