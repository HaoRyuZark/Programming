# JavaScript

## JavaScript Runtime Environments

JavaScript runs inside a **host environment** that provides APIs beyond the core language.

```js
// Browser — has window, document, DOM APIs
console.log(window.location.href);
console.log(document.title);

// Node.js — has process, fs, path, etc.
console.log(process.version);    // e.g. "v20.11.0"
console.log(process.platform);   // "linux", "win32", "darwin"
```

| Feature          | Browser              | Node.js               |
|------------------|----------------------|-----------------------|
| Global object    | `window`             | `global` / `globalThis` |
| DOM access       | Yes                  | No                    |
| File system      | No                   | Yes (`fs` module)     |
| HTTP server      | No                   | Yes (`http` module)   |
| Module system    | ES Modules           | CommonJS + ES Modules |

- **Engine** (e.g. V8 in Chrome & Node.js, SpiderMonkey in Firefox): parses and executes JS code.
- **Event loop**: single-threaded, non-blocking I/O via callbacks, promises, and async/await.

It was mainly created to modify the DOM and add dynamism to web-sites without needing a full reload, but like all horrible 
things it was then used for other stuff it was not suppose to do.

### Loading JavaScript

It is recomended to use the key-words `defer` or `async` inside the `script` tags inside the HTML document when loading the script 
since it else completly pauses the HTML-parsing.

- `defer`: The script is loaded on a parallel thread and executed right after the HTML-parsing.
- `async`: The script is loaded on a parallel thread, but once the loading ends it gets executed directly, pausing the HTML-parsing if not completed.

---

## Basics

### Variables

Declare and store values with different scopes.

```js
// let — block-scoped, reassignable
let count = 0;
count = 1; // ok

// const — block-scoped, cannot be reassigned (but object contents can mutate)
const MAX = 100;
// MAX = 200; // TypeError

const user = { name: "Alice" };
user.name = "Bob"; // OK — the object itself is mutable

// var — function-scoped, avoid in modern code
var legacy = "hoisted to function top";
```

**Hoisting**: `var` declarations are moved to the top of their scope and initialized to `undefined`. `let`/`const` are hoisted but stay in the **Temporal Dead Zone** until their line is reached.

```js
console.log(a); // undefined (var is hoisted)
var a = 5;

console.log(b); // ReferenceError: Cannot access 'b' before initialization
let b = 5;
```

**Block scope example:**
```js
{
  let inner = "only here";
  var outer = "everywhere in the function";
}
// console.log(inner); // ReferenceError
console.log(outer);    // "everywhere in the function"
```

---

### Data Types

JavaScript has **7 primitive types** and **1 reference type** (Object).

```js
// Primitives — stored by value
let n     = 42;               // number (64-bit float)
let big   = 9007199254740993n; // bigint (arbitrary precision)
let s     = "hello";          // string
let b     = true;             // boolean
let u     = undefined;        // declared but not assigned
let empty = null;             // intentionally empty
let id    = Symbol("id");     // unique identifier

// Reference type — stored as pointer
let arr  = [1, 2, 3];
let obj  = { x: 1 };
let fn   = function() {};
```

- **Checking types:**

```js
typeof 42           // "number"
typeof "hi"         // "string"
typeof true         // "boolean"
typeof undefined    // "undefined"
typeof null         // "object"  ← historical bug in JS
typeof Symbol()     // "symbol"
typeof {}           // "object"
typeof []           // "object"  ← arrays are objects
typeof function(){} // "function"

// Better checks:
Array.isArray([])       // true
null === null           // true
obj instanceof Object   // true
```

- **Equality gotchas:**
```js
null == undefined   // true  (loose equality)
null === undefined  // false (strict equality)
NaN === NaN         // false — NaN is never equal to itself
Number.isNaN(NaN)   // true  — correct check
```

- **Implicit coercion pitfalls:**

```js
"5" + 3     // "53"  — + prefers string concatenation
"5" - 3     // 2     — - forces numeric conversion
"5" * "2"   // 10
true + true // 2
[] + {}     // "[object Object]"
{} + []     // 0 (in some contexts)

// Always use === to avoid surprises
"5" == 5    // true  (loose — converts "5" to 5)
"5" === 5   // false (strict — no conversion)
```

### Type Conversion

JavaScript coerces types implicitly in many contexts — understanding this prevents bugs.

**Explicit conversion:**
```js
// to Number
Number("42")        // 42
Number("3.14")      // 3.14
Number("")          // 0
Number("abc")       // NaN
Number(true)        // 1
Number(false)       // 0
Number(null)        // 0
Number(undefined)   // NaN
parseInt("10px")    // 10  — stops at first non-digit
parseFloat("3.14x") // 3.14
+"42"               // 42  — unary plus shorthand

// to String
String(42)          // "42"
String(null)        // "null"
String(undefined)   // "undefined"
(42).toString()     // "42"
(255).toString(16)  // "ff"  — hexadecimal
```

### Falsy & Truhty Values 

Values which are evaluted to `false`, `true`.

```js
// to Boolean (falsy values become false)
Boolean(0)          // false
Boolean("")         // false
Boolean(null)       // false
Boolean(undefined)  // false
Boolean(NaN)        // false
Boolean(false)      // false

// Everything else is truthy:
Boolean(1)          // true
Boolean("hello")    // true
Boolean([])         // true  ← empty array is truthy!
Boolean({})         // true  ← empty object is truthy!
```


### Template Literals

Multi-line strings with embedded expressions.

```js
const name = "Alice";
const age  = 30;

// Interpolation
const msg = `Hello, ${name}! You are ${age} years old.`;

// Multi-line
const html = `
  <div>
    <p>${msg}</p>
  </div>
`;

// Expression inside ${}
const price = 9.99;
console.log(`Total: $${(price * 1.2).toFixed(2)}`); // Total: $11.99

// Tagged templates — process the template with a function
function highlight(strings, ...values) {
  return strings.reduce((result, str, i) =>
    result + str + (values[i] !== undefined ? `<b>${values[i]}</b>` : ""), "");
}
const item = "coffee";
const cost = 3.5;
console.log(highlight`I bought ${item} for $${cost}`);
// "I bought <b>coffee</b> for $<b>3.5</b>"
```

---

### Conditionals

Control flow based on conditions.

```js
const score = 85;

// if / else if / else
if (score >= 90) {
  console.log("A");
} else if (score >= 80) {
  console.log("B");
} else {
  console.log("C or below");
}

// Ternary operator — one-liner for simple if/else
const label = score >= 60 ? "pass" : "fail";

// switch — best for exact value matching
const day = "Monday";
switch (day) {
  case "Saturday":
  case "Sunday":
    console.log("Weekend");
    break;
  case "Monday":
    console.log("Start of week");
    break;
  default:
    console.log("Weekday");
}

// Optional chaining — safely access nested properties
const user = null;
console.log(user?.address?.city); // undefined (no error)
console.log(user?.greet());       // undefined (no error)

// Nullish coalescing — fallback only for null/undefined (not 0 or "")
const port = process.env.PORT ?? 3000;
const username = user?.name ?? "Guest";
```

---

### Loops

Iterate over data or repeat operations.

```js
// Classic for loop
for (let i = 0; i < 5; i++) {
  console.log(i); // 0 1 2 3 4
}

// while loop
let i = 0;
while (i < 3) {
  console.log(i++);
}

// do...while — runs at least once
let n = 0;
do {
  console.log(n++);
} while (n < 3);

// for...of — iterate VALUES of any iterable (arrays, strings, Maps, Sets)
const fruits = ["apple", "banana", "cherry"];
for (const fruit of fruits) {
  console.log(fruit);
}

// for...of with index using entries()
for (const [index, fruit] of fruits.entries()) {
  console.log(`${index}: ${fruit}`);
}

// for...in — iterate KEYS of an object (avoid on arrays)
const person = { name: "Alice", age: 30 };
for (const key in person) {
  console.log(`${key}: ${person[key]}`);
}

// forEach — array method (cannot break out)
fruits.forEach((fruit, index) => {
  console.log(`${index}: ${fruit}`);
});

// break and continue
for (let i = 0; i < 10; i++) {
  if (i === 3) continue; // skip 3
  if (i === 6) break;    // stop at 6
  console.log(i);        // 0 1 2 4 5
}

// Labeled break — for nested loops
outer: for (let i = 0; i < 3; i++) {
  for (let j = 0; j < 3; j++) {
    if (j === 1) break outer; // breaks out of both loops
    console.log(i, j);
  }
}
```

---

### Operators

```js
// Arithmetic
5 + 3   // 8
5 - 3   // 2
5 * 3   // 15
5 / 2   // 2.5
5 % 2   // 1  (remainder)
2 ** 10 // 1024 (exponentiation)

// Assignment shorthand
let x = 10;
x += 5;  // x = 15
x -= 3;  // x = 12
x *= 2;  // x = 24
x /= 4;  // x = 6
x **= 2; // x = 36
x ??= "default"; // assign only if x is null/undefined
x ||= "fallback"; // assign if x is falsy
x &&= x + 1;      // assign if x is truthy

// Comparison
5 === 5   // true  (strict — no coercion)
5 !== "5" // true
5 > 3     // true
5 >= 5    // true

// Logical
true && false  // false
true || false  // true
!true          // false

// Short-circuit evaluation
const a = null;
const b = a && a.name; // b = null (stops at a)
const c = a || "default"; // c = "default"
const d = a ?? "default"; // d = "default" (only null/undefined triggers)
const e = 0 || "fallback"; // "fallback" (0 is falsy)
const f = 0 ?? "fallback"; // 0 (0 is NOT null/undefined)

// Bitwise
5 & 3   // 1   (AND)
5 | 3   // 7   (OR)
5 ^ 3   // 6   (XOR)
~5      // -6  (NOT)
5 << 1  // 10  (left shift)
5 >> 1  // 2   (right shift)

// typeof and instanceof
typeof "hello"      // "string"
[] instanceof Array // true

// in operator — check if property exists
"name" in { name: "Alice" } // true
0 in [1, 2, 3]              // true (index 0 exists)

// Comma operator (evaluates left-to-right, returns rightmost)
const val = (1, 2, 3); // val = 3
```

---

### Functions

Functions are **first-class citizens** in JavaScript which means that they can be assigned, passed, and returned like any value.

```js
// Function declaration — hoisted (can call before definition)
function add(a, b) {
  return a + b;
}
console.log(add(2, 3)); // 5

// Function expression — not hoisted
const multiply = function(a, b) {
  return a * b;
};

// Arrow function — shorter, no own `this`
const square = x => x * x;
const greet  = (name) => `Hello, ${name}`;
const noop   = () => {}; // no args, no return

// Default parameters
function greetUser(name = "Guest", greeting = "Hello") {
  return `${greeting}, ${name}!`;
}
greetUser();            // "Hello, Guest!"
greetUser("Alice");     // "Hello, Alice!"
greetUser("Bob", "Hi"); // "Hi, Bob!"

// Rest parameters — collect extra arguments into an array
function sum(...numbers) {
  return numbers.reduce((total, n) => total + n, 0);
}
sum(1, 2, 3, 4); // 10

// Mixing regular and rest
function log(level, ...messages) {
  console.log(`[${level}]`, messages.join(" "));
}
log("INFO", "Server", "started", "on port 3000");
// [INFO] Server started on port 3000

// IIFE — Immediately Invoked Function Expression
const result = (function() {
  const private_data = "secret";
  return { get: () => private_data };
})();
console.log(result.get()); // "secret"

// Functions returning functions
function multiplier(factor) {
  return (n) => n * factor;
}
const double = multiplier(2);
const triple = multiplier(3);
console.log(double(5)); // 10
console.log(triple(5)); // 15
```

---

## Scope & Closures

### Scope

Scope determines where variables are accessible.

```js
const global = "I am global";

function outer() {
  const outerVar = "I am outer";

  function inner() {
    const innerVar = "I am inner";
    console.log(global);   // accessible
    console.log(outerVar); // accessible (via scope chain)
    console.log(innerVar); // accessible
  }

  inner();
  // console.log(innerVar); // ReferenceError
}
```

### Closures

A closure is a function that **remembers its lexical scope** even when executed outside of it.

```js
// Counter using closure
function makeCounter(start = 0) {
  let count = start;
  return {
    increment: () => ++count,
    decrement: () => --count,
    value:     () => count,
    reset:     () => { count = start; }
  };
}

const counter = makeCounter(10);
console.log(counter.increment()); // 11
console.log(counter.increment()); // 12
console.log(counter.decrement()); // 11
counter.reset();
console.log(counter.value());     // 10

// Classic closure bug with var in loops
for (var i = 0; i < 3; i++) {
  setTimeout(() => console.log(i), 100); // 3 3 3 — all share the same `i`
}

// Fix 1: use let
for (let i = 0; i < 3; i++) {
  setTimeout(() => console.log(i), 100); // 0 1 2
}

// Fix 2: IIFE
for (var i = 0; i < 3; i++) {
  ((j) => setTimeout(() => console.log(j), 100))(i); // 0 1 2
}

// Practical: private state with closures
function createBankAccount(initialBalance) {
  let balance = initialBalance;

  return {
    deposit(amount) {
      if (amount > 0) balance += amount;
    },
    withdraw(amount) {
      if (amount > 0 && amount <= balance) balance -= amount;
    },
    getBalance() {
      return balance;
    }
  };
}

const account = createBankAccount(1000);
account.deposit(500);
account.withdraw(200);
console.log(account.getBalance()); // 1300
```

---

## The `this` Keyword

`this` refers to the **execution context** — what called the function.

```js
// In an object method, this = the object
const user = {
  name: "Alice",
  greet() {
    return `Hi, I'm ${this.name}`;
  }
};
console.log(user.greet()); // "Hi, I'm Alice"

// Arrow functions do NOT have their own this — they inherit from enclosing scope
const timer = {
  seconds: 0,
  start() {
    setInterval(() => {
      this.seconds++; // `this` = timer (arrow captures outer this)
      console.log(this.seconds);
    }, 1000);
  }
};

// Losing this — common pitfall
const greet = user.greet;
greet(); // "Hi, I'm undefined" — this = global (or undefined in strict mode)

// Fixing with bind
const boundGreet = user.greet.bind(user);
boundGreet(); // "Hi, I'm Alice"

// call and apply — invoke with explicit this
function introduce(greeting, punctuation) {
  return `${greeting}, I'm ${this.name}${punctuation}`;
}
const person = { name: "Bob" };
introduce.call(person, "Hello", "!");   // "Hello, I'm Bob!"
introduce.apply(person, ["Hi", "..."]);  // "Hi, I'm Bob..."

// bind — returns a new function with fixed this
const bobIntro = introduce.bind(person, "Hey");
bobIntro("?"); // "Hey, I'm Bob?"
```

---

## Strings

Strings are immutable primitives with a rich set of methods.

```js
const str = "Hello, World!";

// Basic info
str.length           // 13
str[0]               // "H"
str.at(-1)           // "!" — negative indexing (modern)
str.charAt(7)        // "W"
str.charCodeAt(0)    // 72 (Unicode code point)
String.fromCharCode(72) // "H"

// Searching
str.includes("World")   // true
str.startsWith("Hello") // true
str.endsWith("!")       // true
str.indexOf("o")        // 4  (first occurrence)
str.lastIndexOf("o")    // 8  (last occurrence)
str.search(/world/i)    // 7  (regex search, returns index)

// Extracting
str.slice(7, 12)         // "World"
str.slice(-6)            // "orld!" (negative = from end)
str.substring(7, 12)     // "World" (no negative support)

// Modifying (returns new string — strings are immutable)
str.toLowerCase()         // "hello, world!"
str.toUpperCase()         // "HELLO, WORLD!"
str.trim()                // removes leading/trailing whitespace
"  hi  ".trimStart()      // "hi  "
"  hi  ".trimEnd()        // "  hi"
str.replace("World", "JS") // "Hello, JS!"
str.replaceAll("l", "L")   // "HeLLo, WorLd!"
str.replace(/[aeiou]/gi, "*") // replace vowels with *

// Splitting and joining
"a,b,c".split(",")      // ["a", "b", "c"]
"hello".split("")        // ["h", "e", "l", "l", "o"]
"hello".split("", 3)     // ["h", "e", "l"] — limit

// Padding and repeating
"5".padStart(3, "0")     // "005"
"hi".padEnd(5, ".")      // "hi..."
"ha".repeat(3)           // "hahaha"

// String comparison (lexicographic)
"apple" < "banana"  // true
"apple".localeCompare("banana") // -1 (negative = comes before)

// Converting other types to string
String(123)          // "123"
(255).toString(16)   // "ff" (hex)
(8).toString(2)      // "1000" (binary)
JSON.stringify({a:1}) // '{"a":1}'
```

---

## Numbers & Math

```js
// Number limits
Number.MAX_SAFE_INTEGER  // 2^53 - 1 = 9007199254740991
Number.MIN_SAFE_INTEGER  // -(2^53 - 1)
Number.MAX_VALUE         // ~1.8 × 10^308
Number.EPSILON           // ~2.22e-16 (smallest difference)
Infinity                 // larger than any number
NaN                      // "Not a Number"

// Checking
Number.isFinite(Infinity)   // false
Number.isFinite(42)         // true
Number.isNaN(NaN)           // true
Number.isNaN("NaN")         // false (unlike global isNaN)
Number.isInteger(4.0)       // true
Number.isSafeInteger(2**53) // false

// Parsing
parseInt("10px", 10)  // 10 (always specify radix!)
parseFloat("3.14abc") // 3.14
Number("   42  ")     // 42 (handles whitespace)

// Formatting
(1234567.89).toLocaleString("en-US")  // "1,234,567.89"
(3.14159).toFixed(2)                   // "3.14" (string)
(12345).toExponential(2)               // "1.23e+4"
(1.5).toPrecision(4)                   // "1.500"

// Math object
Math.abs(-5)       // 5
Math.ceil(4.1)     // 5
Math.floor(4.9)    // 4
Math.round(4.5)    // 5
Math.trunc(4.9)    // 4 (removes decimal, no rounding)
Math.max(1, 3, 2)  // 3
Math.min(1, 3, 2)  // 1
Math.pow(2, 10)    // 1024 (same as 2**10)
Math.sqrt(16)      // 4
Math.cbrt(27)      // 3 (cube root)
Math.log(Math.E)   // 1
Math.log2(8)       // 3
Math.log10(100)    // 2
Math.PI            // 3.141592653589793
Math.E             // 2.718281828459045

// Random
Math.random()              // [0, 1) — never exactly 1
Math.floor(Math.random() * 6) + 1  // random dice roll 1-6
Math.floor(Math.random() * (max - min + 1)) + min // random int in [min, max]

// Floating point precision issue
0.1 + 0.2                  // 0.30000000000000004
Math.abs(0.1 + 0.2 - 0.3) < Number.EPSILON // true — correct comparison

// BigInt — for integers beyond 2^53
const bigNum = 9007199254740993n;
const bigSum = bigNum + 1n; // cannot mix BigInt with Number
```

---

## Dates

```js
// Creating dates
const now       = new Date();                    // current date & time
const specific  = new Date("2025-06-15");        // from ISO string
const fromParts = new Date(2025, 5, 15, 12, 0); // month is 0-indexed!
const fromMs    = new Date(0);                   // epoch (Jan 1 1970)

// Getting parts
now.getFullYear()    // 2025
now.getMonth()       // 0-11 (0 = January)
now.getDate()        // 1-31 (day of month)
now.getDay()         // 0-6  (0 = Sunday)
now.getHours()       // 0-23
now.getMinutes()     // 0-59
now.getSeconds()     // 0-59
now.getTime()        // milliseconds since epoch
Date.now()           // same as new Date().getTime() — faster

// Setting parts
const d = new Date();
d.setFullYear(2030);
d.setMonth(11); // December

// Formatting
now.toISOString()       // "2025-06-15T12:00:00.000Z"
now.toLocaleDateString("de-DE") // "15.6.2025"
now.toLocaleString("en-US", {
  weekday: "long",
  year: "numeric",
  month: "long",
  day: "numeric"
}); // "Sunday, June 15, 2025"

// Arithmetic — work with milliseconds
const oneDay  = 24 * 60 * 60 * 1000;
const tomorrow = new Date(Date.now() + oneDay);
const daysBetween = (a, b) => Math.floor((b - a) / oneDay);
```

---

## Input / Output

### Console

```js
console.log("Hello, World!");          // standard output
console.error("Something went wrong"); // stderr (red in terminal)
console.warn("Warning message");       // stderr (yellow in terminal)
console.info("Info message");          // same as log

// Structured output
const users = [
  { name: "Alice", age: 30 },
  { name: "Bob",   age: 25 }
];
console.table(users);       // formatted table

console.dir(document.body); // displays object properties
console.time("loop");
for (let i = 0; i < 1e6; i++) {}
console.timeEnd("loop");    // "loop: 5.123ms"

// Grouping
console.group("User Info");
console.log("Name: Alice");
console.log("Age: 30");
console.groupEnd();

// Assertion
console.assert(2 + 2 === 4, "Math is broken"); // silent if true
console.assert(2 + 2 === 5, "Math is broken"); // logs error if false
```

### File System (Node.js)

```js
const fs   = require("fs");
const path = require("path");

// Synchronous (blocking — simple scripts only)
const data = fs.readFileSync("file.txt", "utf-8");
fs.writeFileSync("output.txt", "Hello!\n");
fs.appendFileSync("log.txt", "New entry\n");

// Asynchronous with callbacks
fs.readFile("file.txt", "utf-8", (err, data) => {
  if (err) throw err;
  console.log(data);
});

// Asynchronous with promises (modern — prefer this)
const fsp = require("fs/promises");

async function readAndWrite() {
  const content = await fsp.readFile("input.txt", "utf-8");
  const lines   = content.split("\n").filter(Boolean);
  await fsp.writeFile("output.txt", lines.join("\n"));
}

// Directory operations
fs.mkdirSync("new-folder", { recursive: true });
const entries = fs.readdirSync("./");        // list directory
fs.existsSync("file.txt");                   // check existence
fs.statSync("file.txt").size;                // file size in bytes
fs.unlinkSync("file.txt");                   // delete file
fs.renameSync("old.txt", "new.txt");         // rename / move

// Path utilities
path.join("src", "utils", "helper.js"); // "src/utils/helper.js"
path.resolve("./file.txt");             // absolute path
path.basename("/foo/bar/file.txt");     // "file.txt"
path.dirname("/foo/bar/file.txt");      // "/foo/bar"
path.extname("file.txt");               // ".txt"
path.parse("/foo/bar/file.txt");
// { root: '/', dir: '/foo/bar', base: 'file.txt', ext: '.txt', name: 'file' }
```

### Process Arguments (Node.js)

```js
// node script.js arg1 arg2 --flag
process.argv;         // ["node", "/path/script.js", "arg1", "arg2", "--flag"]
process.argv.slice(2); // ["arg1", "arg2", "--flag"] — actual user args

// Parsing named arguments manually
const args = process.argv.slice(2);
const flags = {};
for (let i = 0; i < args.length; i++) {
  if (args[i].startsWith("--")) {
    const key = args[i].slice(2);
    flags[key] = args[i + 1]?.startsWith("--") ? true : args[++i];
  }
}
// node script.js --name Alice --verbose
// flags = { name: "Alice", verbose: true }

// Environment variables
const port = process.env.PORT || 3000;
const env  = process.env.NODE_ENV || "development";

// Exit
process.exit(0);  // success
process.exit(1);  // error
```

### User Input From The Console (Node.js)

```js
// readline — built-in module
const readline = require("readline");

const rl = readline.createInterface({
  input:  process.stdin,
  output: process.stdout
});

// Single question
rl.question("What is your name? ", (answer) => {
  console.log(`Hello, ${answer}!`);
  rl.close();
});

// Async/await wrapper — much cleaner
function ask(question) {
  return new Promise((resolve) => {
    rl.question(question, resolve);
  });
}

async function main() {
  const name = await ask("Name: ");
  const age  = await ask("Age: ");
  console.log(`Hello ${name}, you are ${age} years old.`);
  rl.close();
}
main();
```

### From The Browser

```js
// Simple prompts (blocking — avoid in production)
const name      = prompt("Enter your name:");
const confirmed = confirm("Are you sure?"); // true/false

// DOM input events (preferred approach)
const input = document.querySelector("#username");
input.addEventListener("input", (e) => {
  console.log("Current value:", e.target.value);
});

input.addEventListener("change", (e) => {
  console.log("Final value:", e.target.value);
});

// Form submission
const form = document.querySelector("form");
form.addEventListener("submit", (e) => {
  e.preventDefault(); // prevent page reload
  const formData = new FormData(form);
  const data = Object.fromEntries(formData.entries());
  console.log(data); // { username: "Alice", password: "..." }
});
```

---

## Object-Oriented Programming (OOP)

### Objects

**Objects** are key-value data structures. Keys are strings (or Symbols); values can be anything.
We can set properties to the object even after the definition `obj[new_prop] = "I am new"`. 

- **Basic functionality**:

```js
// Object literal
const person = {
  firstName: "Alice",
  lastName:  "Smith",
  age:       30,
  isActive:  true,
  address: {
    city:    "Berlin",
    country: "Germany"
  },

  // Method shorthand
  fullName() {
    return `${this.firstName} ${this.lastName}`;
  },

  // Getter and setter
  get displayAge() {
    return `${this.age} years old`;
  },
  set newAge(value) {
    if (value > 0 && value < 150) this.age = value;
  }
};

// Accessing properties
person.firstName;          // "Alice" — dot notation
person["lastName"];        // "Smith" — bracket notation (dynamic key)
person.address.city;       // "Berlin"
person.fullName();         // "Alice Smith"
person.displayAge;         // "30 years old" (getter — no parentheses)
person.newAge = 31;        // setter called

// Adding and deleting properties
person.email = "alice@example.com";
delete person.isActive;

```

> They can, but are well suited to use as a hash-map. This is consider poor practice.
 
- **Checking property existence**:

```js
"firstName" in person          // true
person.hasOwnProperty("email") // true
Object.hasOwn(person, "email") // true (modern, preferred)

```

- **Iterating**

```js
Object.keys(person)    // ["firstName", "lastName", ...]
Object.values(person)  // ["Alice", "Smith", ...]
Object.entries(person) // [["firstName", "Alice"], ...]

// Iterating over the object key-value-pairs
for (const [key, value] of Object.entries(person)) {
  console.log(`${key}: ${value}`);
}


// Iterating over the object keys
for (const k of Object.values(obj)) {
  console.log(k)
}
```

- **Default methods and property descriptors**:

```js
// Object methods
Object.assign(target, source1, source2); // shallow merge
Object.freeze(person);   // make immutable (shallow)
Object.isFrozen(person); // true

// Property descriptors — control enumerability, writability, etc.
Object.defineProperty(person, "id", {
  value: 42,
  writable:     false, // cannot reassign
  enumerable:   false, // hidden from for...in and Object.keys
  configurable: false  // cannot delete or redefine
});

// Defining a property dynamically
const obj = {
  val: "name",
  [defined_on_runtime()]: true;
}
```


### Prototypes

Every object has a `__proto__` property which points to the prototype of the object it inherits from.


```js
// Prototype chain lookup
const arr = [1, 2, 3];
// arr → Array.prototype → Object.prototype → null

// Object.create — create object with specific prototype
const proto = {
  greet() {
    return `Hi, I'm ${this.name}`;
  }
};

const alice = Object.create(proto);
alice.name = "Alice";
alice.greet(); // "Hi, I'm Alice"

// Check prototype chain
Object.getPrototypeOf(alice) === proto; // true
proto.isPrototypeOf(alice);             // true

// hasOwnProperty vs inherited
alice.hasOwnProperty("name");   // true  — own property
alice.hasOwnProperty("greet");  // false — inherited
```

**Constructors functions** have the `prototype` property which also allows us to modify the prototype-chain.

### OOP-Classes

Classes are syntactic sugar over prototype-based inheritance.

```js
class Animal {
  // Private fields (truly private — ES2022)
  #name;
  #sound;

  // Static field (shared across all instances)
  static count = 0;

  constructor(name, sound) {
    this.#name  = name;
    this.#sound = sound;
    Animal.count++;
  }

  // Instance method
  speak() {
    return `${this.#name} says ${this.#sound}!`;
  }

  // Getter
  get name() {
    return this.#name;
  }

  // Setter with validation
  set name(value) {
    if (typeof value !== "string" || value.length === 0) {
      throw new Error("Name must be a non-empty string");
    }
    this.#name = value;
  }

  // Static method — called on the class, not an instance
  static create(name, sound) {
    return new Animal(name, sound);
  }

  toString() {
    return `Animal(${this.#name})`;
  }
}

const cat = new Animal("Whiskers", "meow");
console.log(cat.speak());     // "Whiskers says meow!"
console.log(cat.name);        // "Whiskers"
console.log(Animal.count);    // 1
console.log(`${cat}`);        // "Animal(Whiskers)"

const dog = Animal.create("Rex", "woof");
console.log(Animal.count);    // 2
```

### Class Inheritance

```js
class Dog extends Animal {
  #breed;

  constructor(name, breed) {
    super(name, "woof"); // MUST call super() first
    this.#breed = breed;
  }

  // Override parent method
  speak() {
    return `${super.speak()} (${this.#breed})`;
  }

  fetch(item) {
    return `${this.name} fetches the ${item}!`;
  }
}

const rex = new Dog("Rex", "Labrador");
console.log(rex.speak());        // "Rex says woof! (Labrador)"
console.log(rex.fetch("ball"));  // "Rex fetches the ball!"
console.log(rex instanceof Dog);    // true
console.log(rex instanceof Animal); // true

// Mixin pattern — compose behaviors without deep inheritance
const Serializable = (Base) => class extends Base {
  toJSON() {
    return JSON.stringify(this);
  }
};

const Comparable = (Base) => class extends Base {
  compareTo(other) {
    return this.valueOf() - other.valueOf();
  }
};

class Temperature extends Comparable(Serializable(Object)) {
  constructor(celsius) {
    super();
    this.celsius = celsius;
  }
  valueOf() { return this.celsius; }
}
```

---

## Memory & Copying

### Shallow Copy

Only the top-level properties are copied; nested objects still share the same reference.

```js
const original = {
  name: "Alice",
  scores: [100, 95, 87],
  address: { city: "Berlin" }
};

// Methods to shallow copy
const copy1 = { ...original };           // spread
const copy2 = Object.assign({}, original); // Object.assign

copy1.name = "Bob";        // OK — primitive, doesn't affect original
copy1.scores.push(90);     // BAD — mutates original.scores too!
copy1.address.city = "Paris"; // BAD — mutates original.address too!

console.log(original.name);         // "Alice"   ← not affected
console.log(original.scores);       // [100, 95, 87, 90] ← affected!
console.log(original.address.city); // "Paris"   ← affected!

// Array shallow copy
const arrCopy  = [...original.scores];
const arrCopy2 = original.scores.slice();
const arrCopy3 = Array.from(original.scores);
```

### Deep Copy

Copies the entire object graph — no shared references.

```js
// Modern: structuredClone (built-in since Node 17 / modern browsers)
const deep = structuredClone(original);
deep.scores.push(70);
console.log(original.scores); // unchanged

// Note: structuredClone cannot clone functions, DOM nodes, or class instances

// JSON round-trip — simple but loses functions, undefined, Dates become strings
const clone = JSON.parse(JSON.stringify(original));
// Limitations:
// - Functions are dropped
// - undefined values are dropped
// - Date objects become strings
// - Circular references throw an error

// Recursive deep clone (manual)
function deepClone(value) {
  if (value === null || typeof value !== "object") return value;
  if (Array.isArray(value)) return value.map(deepClone);
  return Object.fromEntries(
    Object.entries(value).map(([k, v]) => [k, deepClone(v)])
  );
}
```

---

## Arrays

Ordered, zero-indexed, dynamic lists. Arrays in JavaScript can hold mixed types.

```js
// Creation
const arr  = [1, 2, 3, 4, 5];

const arr2 = new Array(3);         // [undefined, undefined, undefined]
const arr3 = new Array(3).fill(0); // [0, 0, 0]

const arr4 = Array.from("hello");  // ["h", "e", "l", "l", "o"]

// We specify the length and via the closure, how every element should be created. This 
// is the closest to a list comprehension
const arr5 = Array.from({ length: 5 }, (_, i) => i * 2); // [0, 2, 4, 6, 8]

const arr6 = Array.of(1, 2, 3);    // [1, 2, 3]

// Filling
new Array(5).fill(0);           // [0, 0, 0, 0, 0]
[1,2,3,4,5].fill(0, 2, 4);     // [1, 2, 0, 0, 5] — fill from index 2 to 4

// Accessing
arr[0]      // 1
arr.at(-1)  // 5 — negative index (modern)
arr.at(-2)  // 4

// Basic info
arr.length  // 5
Array.isArray(arr) // true

// Reversing
[1, 2, 3].reverse(); // [3, 2, 1] — in place

```

### Adding / removing

```js
const a = [1, 2, 3];

a.push(4, 5);       // add to end → [1,2,3,4,5], returns new length
a.pop();            // remove from end → returns 5, a = [1,2,3,4]
a.unshift(0);       // add to start → [0,1,2,3,4], returns new length
a.shift();          // remove from start → returns 0, a = [1,2,3,4]

```

### Splicing

- `splice(start, deleteCount, ...insertItems)`: it changes the contents of an array by removing or replacing and 
or adding new elements.

```js
const a = [1, 2, 3, 4, 5];

a.splice(1, 0, 99)         // Inserts 99 at index 1 and shifts the rest
a.splice(1, 2);            // remove 2 elements at index 1

a.splice(1, 0, 10, 11);    // insert at index 1 without removing
a.splice(1, 1, 99);        // replace 1 element at index 1 with 99
```

### Sorting 

```js
[3, 1, 2].sort();                        // [1, 2, 3] — default: lexicographic!
[10, 1, 20].sort((a, b) => a - b);       // [1, 10, 20] — numeric ascending
[10, 1, 20].sort((a, b) => b - a);       // [20, 10, 1] — numeric descending
["banana", "apple"].sort();               // ["apple", "banana"]
users.sort((a, b) => a.name.localeCompare(b.name)); // by name alphabetically
```

### Higher-Order Array Methods

Similar to java-streams
```js
const nums = [1, 2, 3, 4, 5];

// Transforming
nums.map(x => x * 2)            // [2, 4, 6, 8, 10]
nums.map((x, i) => `${i}:${x}`) // ["0:1", "1:2", ...]

// Filtering
nums.filter(x => x % 2 === 0)  // [2, 4]
nums.filter(x => x > 3)        // [4, 5]
nums.filter((x, i) => x > 3 && i === 0)        // [4, 5]

// Reducing
nums.reduce((acc, x) => acc + x, 0) // 15 (sum)
nums.reduce((acc, x) => acc * x, 1) // 120 (product)
nums.reduceRight((acc, x) => acc + x, 0) // right-to-left
nums.reduce(func, init)

// Flattening
[[1,2],[3,4]].flat()           // [1, 2, 3, 4]
[1, [2, [3]]].flat(Infinity)   // [1, 2, 3] — flatten all levels
nums.flatMap(x => [x, x * 2]) // [1,2, 2,4, 3,6, 4,8, 5,10]

// Testing
nums.every(x => x > 0)  // true — all pass?
nums.some(x => x > 4)   // true — any pass?

// Slicing
nums.slice(1, 3)         // [2, 3] — indices 1 and 2 (end exclusive)
nums.slice(-2)           // [4, 5] — last 2 elements
nums.slice()             // shallow copy of entire array

// Combining
nums.concat([6, 7], [8])  // [1,2,3,4,5,6,7,8]
[...nums, 6, 7]           // same result with spread

// Joining
nums.join(", ")   // "1, 2, 3, 4, 5"
nums.join("")     // "12345"

// Keys, values, entries (iterators)
[...nums.keys()]    // [0, 1, 2, 3, 4]
[...nums.values()]  // [1, 2, 3, 4, 5]
[...nums.entries()] // [[0,1],[1,2],[2,3],[3,4],[4,5]]
```

### Searching

```js 
let nums = [1,2,3,4,5,5,6,7,7,8,9,9,]

nums.find(x => x > 3)         // 4 — first match (or undefined)
nums.findIndex(x => x > 3)    // 3 — index of first match (or -1)
nums.findLast(x => x < 4)     // 3 — last match (modern)
nums.findLastIndex(x => x < 4) // 2

nums.indexOf(3)                // 2 — strict equality
nums.lastIndexOf(3)            // 2
nums.includes(3)               // true
```

### Array Destructuring

```js
const [first, second, ...rest] = [1, 2, 3, 4, 5];
console.log(first);  // 1
console.log(second); // 2
console.log(rest);   // [3, 4, 5]

// Skip elements
const [, , third] = [1, 2, 3];
console.log(third); // 3

// Default values
const [a = 10, b = 20] = [1];
console.log(a); // 1
console.log(b); // 20

// Swap variables elegantly
let x = 1, y = 2;
[x, y] = [y, x];
console.log(x, y); // 2 1

// From function return
function getMinMax(arr) {
  return [Math.min(...arr), Math.max(...arr)];
}
const [min, max] = getMinMax([3, 1, 4, 1, 5]);
console.log(min, max); // 1 5
```

---

## Sets

A `Set` holds **unique values** of any type, in insertion order.

```js
// Creation
const set = new Set([1, 2, 3, 2, 1]); // {1, 2, 3}
const strSet = new Set("hello");       // {"h", "e", "l", "o"}

// Size (not .length!)
set.size // 3
```

#### Set Methods

```js
const s = new Set();

s.add(1).add(2).add(3).add(2); // {1, 2, 3} — chaining, duplicates ignored

s.has(2);    // true
s.has(99);   // false
s.size;      // 3

s.delete(2); // returns true if existed
s.clear();   // empties the set

// Iterating
const colors = new Set(["red", "green", "blue"]);
for (const color of colors) console.log(color);

[...colors]         // ["red", "green", "blue"] — spread to array
Array.from(colors)  // same

// Set operations (manual)
const a = new Set([1, 2, 3, 4]);
const b = new Set([3, 4, 5, 6]);

const union        = new Set([...a, ...b]);                    // {1,2,3,4,5,6}
const intersection = new Set([...a].filter(x => b.has(x)));   // {3,4}
const difference   = new Set([...a].filter(x => !b.has(x)));  // {1,2}

// Practical: duplicate an array
const arr = [1, 2, 2, 3, 3, 4];
const unique = [...new Set(arr)]; // [1, 2, 3, 4]
```

---

### Maps

A `Map` is an ordered key-value collection where **keys can be any type**.

```js
// Creation
const map = new Map();
const map2 = new Map([
  ["name", "Alice"],
  ["age",  30],
  [true,   "yes"],   // boolean key
  [{},     "obj"]    // object key
]);
```

#### Map Methods

```js
const m = new Map();

m.set("name", "Alice");
m.set("age", 30);
m.set(42, "the answer");   // number key
const keyObj = {};
m.set(keyObj, "obj key");  // object as key

m.get("name");    // "Alice"
m.get(42);        // "the answer"
m.get("missing"); // undefined

m.has("name");    // true
m.size;           // 3

m.delete("age");  // returns true
m.clear();        // removes all

// Iterating
const scores = new Map([
  ["Alice", 95],
  ["Bob",   82],
  ["Carol", 88]
]);

for (const [name, score] of scores) {
  console.log(`${name}: ${score}`);
}

[...scores.keys()]    // ["Alice", "Bob", "Carol"]
[...scores.values()]  // [95, 82, 88]
[...scores.entries()] // [["Alice",95], ["Bob",82], ...]

// Converting
const obj  = Object.fromEntries(scores);  // {Alice:95, Bob:82, Carol:88}
const map3 = new Map(Object.entries(obj)); // back to Map

// Practical: count occurrences
function frequency(arr) {
  return arr.reduce((map, item) => {
    return map.set(item, (map.get(item) ?? 0) + 1);
  }, new Map());
}
frequency(["a","b","a","c","b","a"]);
// Map { "a" => 3, "b" => 2, "c" => 1 }
```

---

### WeakMap & WeakSet

Hold **weak references** — entries can be garbage collected if no other references exist.

```js
// WeakMap — keys must be objects; not iterable
const weakMap = new WeakMap();
let user = { name: "Alice" };
weakMap.set(user, { sessionToken: "abc123" });
console.log(weakMap.get(user)); // { sessionToken: "abc123" }
user = null; // user object can be garbage collected; WeakMap entry disappears

// Use case: private data per instance without memory leaks
const _private = new WeakMap();

class Circle {
  constructor(radius) {
    _private.set(this, { radius });
  }
  get area() {
    return Math.PI * _private.get(this).radius ** 2;
  }
}

// WeakSet — values must be objects; not iterable
const visited = new WeakSet();
function processNode(node) {
  if (visited.has(node)) return;
  visited.add(node);
  // ... process
}
```

---

## Functional Patterns

### Arrow Functions

```js
// Implicit return (no braces)
const double  = x => x * 2;
const add     = (a, b) => a + b;
const greet   = name => `Hello, ${name}`;
const getObj  = x => ({ value: x }); // wrap in () to return object literal

// Explicit return (with braces)
const compute = (a, b) => {
  const sum = a + b;
  return sum * 2;
};

// In array methods
const nums = [1, 2, 3, 4, 5];
nums.filter(n => n % 2 === 0).map(n => n ** 2); // [4, 16]

// Key differences from regular functions:
// 1. No own `this`
// 2. No `arguments` object
// 3. Cannot be used as constructors
// 4. No `prototype` property
```

---

### Higher-Order Functions

Functions that take functions as arguments or return functions.

```js
// map — transform each element
const prices     = [10, 20, 30];
const discounted = prices.map(p => p * 0.9);       // [9, 18, 27]
const formatted  = prices.map(p => `$${p.toFixed(2)}`); // ["$10.00", ...]

// filter — select matching elements
const users = [
  { name: "Alice", age: 30, active: true },
  { name: "Bob",   age: 17, active: false },
  { name: "Carol", age: 25, active: true }
];
const adults       = users.filter(u => u.age >= 18);
const activeAdults = users.filter(u => u.active && u.age >= 18);

// reduce — fold array into single value
const nums = [1, 2, 3, 4, 5];
const sum     = nums.reduce((acc, n) => acc + n, 0);  // 15
const product = nums.reduce((acc, n) => acc * n, 1);  // 120

// Grouping with reduce
const grouped = users.reduce((groups, user) => {
  const key = user.active ? "active" : "inactive";
  (groups[key] ??= []).push(user);
  return groups;
}, {});

// Chaining
const result = users
  .filter(u => u.active)
  .map(u => u.name)
  .sort()
  .join(", "); // "Alice, Carol"

// every and some
users.every(u => u.age >= 18); // false (Bob is 17)
users.some(u => u.age >= 18);  // true
```

---

### Closures & Functional Utilities

```js
// Partial application — pre-fill some arguments
function partial(fn, ...presetArgs) {
  return (...laterArgs) => fn(...presetArgs, ...laterArgs);
}

function multiply(a, b) { return a * b; }
const triple = partial(multiply, 3);
triple(5); // 15

// Currying — transform f(a,b,c) into f(a)(b)(c)
function curry(fn) {
  return function curried(...args) {
    if (args.length >= fn.length) {
      return fn.apply(this, args);
    }
    return (...moreArgs) => curried(...args, ...moreArgs);
  };
}

const curriedAdd = curry((a, b, c) => a + b + c);
curriedAdd(1)(2)(3);   // 6
curriedAdd(1, 2)(3);   // 6

// Function composition
const compose = (...fns) => x => fns.reduceRight((v, f) => f(v), x);
const pipe    = (...fns) => x => fns.reduce((v, f) => f(v), x);

const trim         = s => s.trim();
const toLower      = s => s.toLowerCase();
const removeSpaces = s => s.replace(/\s+/g, "-");

const slugify = pipe(trim, toLower, removeSpaces);
slugify("  Hello World  "); // "hello-world"

// Memoization — cache results of expensive calls
function memoize(fn) {
  const cache = new Map();
  return function(...args) {
    const key = JSON.stringify(args);
    if (cache.has(key)) return cache.get(key);
    const result = fn.apply(this, args);
    cache.set(key, result);
    return result;
  };
}

const fib = memoize(function(n) {
  if (n <= 1) return n;
  return fib(n - 1) + fib(n - 2);
});
fib(40); // fast with memoization
```

---

## Spread & Rest Syntax

```js
// Spread (...) — expand an iterable into individual elements

// Arrays
const a = [1, 2, 3];
const b = [4, 5, 6];
const combined = [...a, ...b];           // [1, 2, 3, 4, 5, 6]
const copy     = [...a];                 // shallow copy
Math.max(...a);                          // 3 (spread as function args)

// Objects
const defaults = { color: "blue", size: "md", weight: 100 };
const custom   = { size: "lg", weight: 200 };
const merged   = { ...defaults, ...custom }; // { color:"blue", size:"lg", weight:200 }
// Later keys override earlier ones

// String spread
const chars = [..."hello"]; // ["h", "e", "l", "l", "o"]

// Rest (...) — collect multiple elements into an array (in function params)
function sum(first, second, ...rest) {
  return first + second + rest.reduce((a, b) => a + b, 0);
}
sum(1, 2, 3, 4, 5); // 15

// Rest in destructuring
const [head, ...tail] = [1, 2, 3, 4];
head; // 1
tail; // [2, 3, 4]

const { name, ...other } = { name: "Alice", age: 30, city: "Berlin" };
name;  // "Alice"
other; // { age: 30, city: "Berlin" }
```

---

## Destructuring

```js
// Object destructuring
const user = { name: "Alice", age: 30, role: "admin", city: "Berlin" };

const { name, age }          = user;       // basic
const { name: userName }     = user;       // rename
const { name, ...rest }      = user;       // rest
const { email = "n/a" }      = user;       // default value

// Function parameter destructuring — very common in React, Node.js
function displayUser({ name, age = 0, role = "user" }) {
  return `${name} (${age}) — ${role}`;
}
displayUser({ name: "Alice", age: 30 }); // "Alice (30) — user"

// Nested destructuring
const { address: { city, country = "Unknown" } } = {
  address: { city: "Berlin" }
};

// Array destructuring
const [first, , third, ...others] = [10, 20, 30, 40, 50];
first;  // 10
third;  // 30
others; // [40, 50]

// Swapping
let a = 1, b = 2;
[a, b] = [b, a]; // a=2, b=1

// Mixed destructuring
const { data: [firstUser, secondUser], meta: { total } } = {
  data: [{ name: "Alice" }, { name: "Bob" }],
  meta: { total: 2 }
};

// Destructuring in loops
const items = [{ id: 1, name: "Alice" }, { id: 2, name: "Bob" }];
for (const { id, name } of items) {
  console.log(`${id}: ${name}`);
}
```

---

## Symbols & Iterators

### Symbols

```js
// Symbols — guaranteed unique, useful as object keys to avoid collisions
const id   = Symbol("id");
const id2  = Symbol("id");
id === id2; // false — every symbol is unique

const user = {
  name: "Alice",
  [id]: 42        // symbol as key (not enumerable)
};
user[id]; // 42
Object.keys(user); // ["name"] — symbols are hidden from normal iteration

// Making objects iterable with Symbol.iterator
class Range {
  constructor(start, end) {
    this.start = start;
    this.end   = end;
  }

  [Symbol.iterator]() {
    let current = this.start;
    const end   = this.end;
    return {
      next() {
        return current <= end
          ? { value: current++, done: false }
          : { value: undefined, done: true };
      }
    };
  }
}

const range = new Range(1, 5);
for (const n of range) console.log(n); // 1 2 3 4 5
[...range]; // [1, 2, 3, 4, 5]
```

### Generators

Functions that can **pause** and **resume** execution.

```js
function* counter(start = 0) {
  while (true) {
    yield start++;
  }
}

const gen = counter(1);
gen.next(); // { value: 1, done: false }
gen.next(); // { value: 2, done: false }

// Finite generator
function* range(start, end, step = 1) {
  for (let i = start; i < end; i += step) {
    yield i;
  }
}
[...range(0, 10, 2)]; // [0, 2, 4, 6, 8]

// Delegating with yield*
function* flatten(arr) {
  for (const item of arr) {
    if (Array.isArray(item)) yield* flatten(item);
    else yield item;
  }
}
[...flatten([1, [2, [3, 4]], 5])]; // [1, 2, 3, 4, 5]

// Infinite sequences (lazy evaluation)
function* fibonacci() {
  let [a, b] = [0, 1];
  while (true) {
    yield a;
    [a, b] = [b, a + b];
  }
}

function take(n, iterable) {
  const result = [];
  for (const value of iterable) {
    result.push(value);
    if (result.length === n) break;
  }
  return result;
}
take(8, fibonacci()); // [0, 1, 1, 2, 3, 5, 8, 13]
```

---

## Error Handling

```js
// try / catch / finally
function divide(a, b) {
  if (b === 0) throw new Error("Division by zero");
  return a / b;
}

try {
  const result = divide(10, 0);
  console.log(result);
} catch (err) {
  console.error(`Error: ${err.message}`); // "Error: Division by zero"
} finally {
  console.log("Always runs — cleanup here");
}

// Built-in error types
new Error("generic error");
new TypeError("wrong type");
new RangeError("value out of range");
new ReferenceError("variable not defined");
new SyntaxError("syntax issue");

// Catching specific error types
try {
  null.property; // TypeError
} catch (err) {
  if (err instanceof TypeError) {
    console.log("Type error:", err.message);
  } else {
    throw err; // re-throw unknown errors
  }
}
```

### Custom Errors

```js
class AppError extends Error {
  constructor(message, code, statusCode = 500) {
    super(message);
    this.name       = this.constructor.name;
    this.code       = code;
    this.statusCode = statusCode;
    if (Error.captureStackTrace) {
      Error.captureStackTrace(this, this.constructor);
    }
  }
}

class ValidationError extends AppError {
  constructor(field, message) {
    super(message, "VALIDATION_ERROR", 400);
    this.field = field;
  }
}

class NotFoundError extends AppError {
  constructor(resource) {
    super(`${resource} not found`, "NOT_FOUND", 404);
    this.resource = resource;
  }
}

// Usage
try {
  throw new ValidationError("email", "Invalid email format");
} catch (err) {
  if (err instanceof ValidationError) {
    console.log(`Field "${err.field}": ${err.message}`);
  }
  console.log(err.statusCode); // 400
}
```

---

## Regular Expressions

Patterns for matching text.

```js
// Creating regex
const re1 = /hello/;           // literal
const re2 = /hello/gi;         // flags: g=global, i=case-insensitive
const re3 = new RegExp("hello", "gi"); // dynamic pattern

// Flags: g (global), i (case-insensitive), m (multiline), s (dotAll), u (unicode)

// Testing
/hello/.test("say hello world"); // true
/^\d+$/.test("123");             // true (only digits)

// Matching
"hello world".match(/\w+/);       // ["hello"] — first match
"hello world".match(/\w+/g);      // ["hello", "world"] — all matches

// Replacing
"Hello World".replace(/o/g, "0");       // "Hell0 W0rld"
"2025-05-31".replace(/(\d{4})-(\d{2})-(\d{2})/, "$3/$2/$1"); // "31/05/2025"
"hello world".replace(/\b\w/g, c => c.toUpperCase()); // "Hello World"

// Splitting
"one, two,  three".split(/,\s*/); // ["one", "two", "three"]

// Common patterns
const patterns = {
  email:    /^[^\s@]+@[^\s@]+\.[^\s@]+$/,
  digits:   /^\d+$/,
  slug:     /^[a-z0-9]+(?:-[a-z0-9]+)*$/,
  hexColor: /^#([A-Fa-f0-9]{6}|[A-Fa-f0-9]{3})$/,
  date_iso: /^\d{4}-\d{2}-\d{2}$/
};

// Capture groups
const dateStr = "2025-05-31";
const [, year, month, day] = dateStr.match(/(\d{4})-(\d{2})-(\d{2})/);

// Named capture groups
const { groups: { y, m, d } } = "2025-05-31"
  .match(/(?<y>\d{4})-(?<m>\d{2})-(?<d>\d{2})/);

// Lookahead
"100px 200em 50%".match(/\d+(?=px)/g); // ["100"]

// Character classes
/[a-z]/ // lowercase letters
/\d/    // digits [0-9]
/\w/    // word chars [a-zA-Z0-9_]
/\s/    // whitespace
/./     // any char except newline
```

---

## JSON

```js
// Serializing (JS → JSON string)
const data = { name: "Alice", age: 30, scores: [95, 87] };

JSON.stringify(data);           // compact
JSON.stringify(data, null, 2);  // pretty-printed

// With replacer — filter or transform keys
JSON.stringify(data, ["name", "age"]);    // only include these keys
JSON.stringify(data, (key, value) => {
  if (typeof value === "number") return value * 2;
  return value;
});

// Parsing (JSON string → JS object)
const parsed = JSON.parse('{"name":"Alice","age":30}');
parsed.name; // "Alice"

// With reviver — transform values during parse
const withDate = JSON.parse('{"created":"2025-01-01T00:00:00Z"}',
  (key, value) => key === "created" ? new Date(value) : value
);
withDate.created instanceof Date; // true

// toJSON — customize how an object serializes
class User {
  constructor(name, password) {
    this.name     = name;
    this.password = password;
  }
  toJSON() {
    return { name: this.name }; // never expose password
  }
}
JSON.stringify(new User("Alice", "secret")); // '{"name":"Alice"}'

// JSON limitations:
// No functions, undefined, Symbol, Infinity, NaN, circular refs
// Dates become strings — use reviver to restore them
// Use structuredClone for deep copy instead
```

---

## Asynchronous JavaScript

JavaScript is **single-threaded** with a non-blocking **event loop**. Async operations are offloaded and their callbacks are queued.

### The Event Loop

The **event loop** is a component of the JavaScript runtime which handles asynchronous tasks. It continuously checks the **call stack** and the **task queues** (microtasks and macrotasks) 
to determine what to execute next depending on a priority order. The need for this component arises from JavaScript being single-threaded and some operations being bounded with a certain latency, like 
I/O operations, timers, and user interactions. The event loop allows JavaScript to perform non-blocking operations by offloading tasks to the system kernel whenever possible.

#### Priority of Execution:

1. **Call Stack**: Executes synchronous code. Place in which all task are placed for execution.

2. **Microtask Queue**: Executes tasks like Promise callbacks and `process.nextTick()`. The tasks in this queue, always execute before the ones in the **macrotask queue**, but they 
still need to wait for the global execution context to be pop out of the task. Only callbacks attached with a promise, mutationOserver, function bodies after a await keyword and a queueMicrotask go
int the microtask queue.

3. **Macrotask Queue**: Executes tasks like `setTimeout`, `setInterval`, and I/O callbacks. A task in this queue is only executed once the call stack is **empty**; this includes 
the global executed context. This tasks are executed by Javascript **itself**, not by a remote API.

### Callbacks

A **callback** is a function passed as an argument to another function, which is then invoked after some operation has completed.

We use `setTimeout` to simulate an asynchronous operation.

```js
const posts = [
  {title: "XZ Utils", author: "Migu"},
  {title: "TDD", author: "Munti"}
];

// Example 1:

function printPosts() {
  setTimeout( () => {
      posts.forEach((post, index) => console.log("${post.title}, ${post.author}"));
    }, 2000
  );
}

let createPost = (author, title, callback) => {
  setTimeout( () => {
      posts.push({title: title, author: author})
      callback()
    }, 2000
  );

createPost("Migu", "Amazonas", printPost()); // Now only after creating the last post, they will be printed

// Example 2:

function fetchUser(id, callback) {
  setTimeout(() => {n
    if (id <= 0) callback(new Error("Invalid ID"), null);
    else callback(null, { id, name: "Alice" });
  }, 100);
}

fetchUser(1, (err, user) => {
  if (err) return console.error(err.message);
  console.log(user.name);
});

}
```

**Example**: Canceling a timeout: 

```js 
let cancellable = function(fn, args, t) {
    
    let tm = setTimeout(() => {
        return fn(...args);
    }, t);
  
    // the execution gets canceled if the transaction takes to long, means if we call this function after being returned.
    let cancelFn = () => clearTimeout(tm);

    return cancelFn;
};
```

##### Callback Hell

This happens when we have a lot of callbacks nested.

```js
function walkTheDog(callback) {
    setTimeout(() => { 
      console.log("Dog");
      callback();
    }, 1000);
}

function cook(callback) {
    setTimeout(() => {
      console.log("cook");
      callback();
    }, 1000);
}

function cleanTheKitchen(callback) {
    setTimeout(() => {
      console.log("Kitchen");
      callback();
    }, 1000);
}

walkTheDog(() => {
    cook(() => {
      cleanTheKitchen(() => console.log("Finished Execution"))
    })
})

```

### Promises

A `Promise` represents a value that will be available in the future and they provide a better syntax and structure than 
a callback hell. They can be in three states: **pending**, **resolve** and **reject**.
They count as a microtask. `new Promise((resolve, reject) => { async code })`. The value passed into the `resolve()` function gets 
returned as the value of the promise.

Basic example:

```js 
function walkTheDog() {

    return new Promise((resolve, reject) => {
      setTimeout(() => { 
        resolve("Dog");
      }, 1000);
    });
}

function cook() {
    return new Promise((resolve, reject) => {
      setTimeout(() => { 
        resolve("Cook");
      }, 1000);
    });
}

function cleanTheKitchen() {
    return new Promise((resolve, reject) => {
      setTimeout(() => { 
        resolve("Kitchen");
      }, 1000);
    });
}

walkTheDog()
  .then(value => { console.log(value); return cook();})
  .then(value => { console.log(value); return cleanTheKitchen();})
  .then(value => console.log(value));
```

Here is an even cleaner way: 

```js 
const delay = (ms, value) => new Promise(resolve => setTimeout(() => resolve(value), ms));

const walkTheDog      = () => delay(1000, "Dog");
const cook            = () => delay(1000, "Cook");
const cleanTheKitchen = () => delay(1000, "Kitchen");

walkTheDog()
  .then(value => { console.log(value); return cook(); })
  .then(value => { console.log(value); return cleanTheKitchen(); })
  .then(value => console.log(value));

```

In the last two examples, we defined our own promises, but we can also use the fact that `.then()` also returns a promise to work 
in a functional way with our first returned value. 

```js
const loadImage = (src) => {
  return new Promise((resolve, reject) => {
    const img = new Image();
    img.onload = () => resolve(img);
    img.onerror = reject;
    img.src = src;
  });
};

loadImage(src)
  .then(image => resizeImage(image))
  .then(image => addWatermark(image))
```

> Important Note: The code inside the function passed to the new Promise(() => ...) gets executed normally in the call stack. Only then `.then()` are microstasks.

```js
// Creating a Promise
const p = new Promise((resolve, reject) => {
  setTimeout(() => {
    const success = true;
    if (success) resolve("Data loaded");
    else reject(new Error("Failed to load"));
  }, 1000);
});

// Consuming
p
  .then(data => console.log(data))     // "Data loaded"
  .catch(err => console.error(err))
  .finally(() => console.log("done")); // always runs

// Chaining — each .then returns a new Promise
fetch("/api/users")
  .then(res => {
    if (!res.ok) throw new Error("HTTP " + res.status);
    return res.json();
  })
  .then(users => users.filter(u => u.active))
  .then(active => console.log(active))
  .catch(err => console.error(err));

// Promisifying a callback function
function delay(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}
```

#### Promise Combinators

They allow us to collect the results of a promise depending on if all resolved or only some. 

```js
// Promise.all — wait for ALL; fail-fast if any rejects
const [users, posts] = await Promise.all([
  fetch("/api/users").then(r => r.json()),
  fetch("/api/posts").then(r => r.json())
]);

// Promise.allSettled — wait for ALL, even if some reject
const results = await Promise.allSettled([
  Promise.resolve(1),
  Promise.reject(new Error("oops")),
  Promise.resolve(3)
]);

// [{ status:"fulfilled", value:1 }, { status:"rejected", reason:... }, ...]
results.forEach(r => {
  if (r.status === "fulfilled") console.log(r.value);
  else console.error(r.reason);
});

// Promise.race — first to settle wins
const timeout = ms => new Promise((_, reject) =>
  setTimeout(() => reject(new Error("Timeout")), ms)
);

const data = await Promise.race([
  fetch("/api/data").then(r => r.json()),
  timeout(5000)
]);

// Promise.any — first to RESOLVE wins; rejects only if ALL reject
const fastest = await Promise.any([
  fetch("https://server1.com/api"),
  fetch("https://server2.com/api")
]);

// Static helpers
Promise.resolve(42).then(v => console.log(v)); // 42
Promise.reject(new Error("fail")).catch(e => console.error(e));

// Promise.all
addTwoPromises = async function(promise1, promise2) {

    return Promise.all([promise1, promise2])
    .then((values) => values.reduce((acc, num) => acc + num, 0));  
};
```

### Async / Await

Syntactic sugar over Promises to read like synchronous code. Instead of calling `.then()` we just use the `await` keyword in front of our function call inside an 
`async` function, and for the error handling we use classical `try-catch` syntax.

```js
// Basic pattern
async function fetchUser(id) {

  const res  = await fetch(`/api/users/${id}`);

  if (!res.ok) throw new Error(`HTTP ${res.status}`);

  return await res.json();
}

// Error handling
async function loadDashboard(userId) {

  try {
 
    const user  = await fetchUser(userId);
    const posts = await fetchPosts(user.id);
     
     return { user, posts };

} catch (err) {
    console.error("Dashboard load failed:", err.message);
    throw err;
  }
}

// Parallel execution (don't await sequentially unless dependent!)
async function loadAll(userId) {
  // Sequential — slow
  const user  = await fetchUser(userId);
  const posts = await fetchPosts(userId);

  // Parallel — fast
  const [user2, posts2] = await Promise.all([
    fetchUser(userId),
    fetchPosts(userId)
  ]);
}

// Async IIFE
(async () => {
  const data = await fetchData();
  console.log(data);
})();

// Top-level await (in ES modules)
const config = await fetch("/config.json").then(r => r.json());
```

### fetch API

The `fetch()` is a function used for HTTPS request to fetch resources. `fetch(url, {method, headers, ...})`.
This method returns a promise, hence, we can use both async/await and our promise methods for doing operations.

Example:

```js
// GET request
const res   = await fetch("https://api.example.com/users");
const users = await res.json();

// POST with JSON body
const newUser = await fetch("https://api.example.com/users", {
  method: "POST",
  headers: {
    "Content-Type": "application/json",
    "Authorization": `Bearer ${token}`
  },
  body: JSON.stringify({ name: "Alice", email: "alice@example.com" })
}).then(res => {
  if (!res.ok) throw new Error(`HTTP ${res.status}`);
  return res.json();
});

// Checking response
res.status;      // 200, 404, 500 ...
res.ok;          // true if 200-299
res.headers.get("Content-Type");

// Reading body (can only be read once!)
await res.json();        // parse as JSON
await res.text();        // parse as text
await res.blob();        // parse as binary Blob
await res.arrayBuffer(); // raw bytes

// Abort a request
const controller = new AbortController();
setTimeout(() => controller.abort(), 5000);

try {
  const res = await fetch(url, { signal: controller.signal });
} catch (err) {
  if (err.name === "AbortError") console.log("Request cancelled");
}

const data = fetch("some_path")
                .then(res => res.json())
                .then(data => console.log(data))
                .catch(err => console.log(err));
```


---

## Modules & Ecosystem

### ES Modules (ESM)

The standard, static module system. Used in modern browsers and Node.js (with `.mjs` or `"type": "module"` in `package.json`).

```js
// --- math.js ---
export const PI = 3.14159;
export function add(a, b) { return a + b; }
export function subtract(a, b) { return a - b; }

// Default export (one per module)
export default class Calculator {
  add(a, b) { return a + b; }
}

// Re-exporting
export { PI as pi } from "./constants.js";
export * from "./helpers.js";

// --- main.js ---
import { add, subtract, PI } from "./math.js";
import { add as addNums }    from "./math.js"; // rename
import Calculator            from "./math.js"; // default import
import * as math             from "./math.js"; // namespace import

math.add(1, 2);
math.PI;

// Dynamic import — lazy loading (returns a Promise)
async function loadHeavyModule() {
  const { default: HeavyClass } = await import("./heavy.js");
  return new HeavyClass();
}

// Conditional import
const locale = "de";
const { messages } = await import(`./locales/${locale}.js`);
```

### CommonJS (CJS)

Legacy Node.js module system. Files are `.js` without `"type": "module"`.

```js
// --- utils.js ---
module.exports = {
  greet(name) { return `Hello, ${name}`; },
  PI: 3.14159
};

// --- main.js ---
const utils       = require("./utils");
const { greet }   = require("./utils");
const fs          = require("fs");     // built-in
const axios       = require("axios");  // npm package

// __dirname and __filename (not available in ESM)
console.log(__dirname);  // absolute path of current directory
console.log(__filename); // absolute path of current file
```

### ESM vs CJS Comparison

| Feature         | ESM                    | CJS                     |
|-----------------|------------------------|-------------------------|
| Syntax          | `import/export`        | `require/module.exports`|
| Loading         | Static (compile-time)  | Dynamic (runtime)       |
| Top-level await | Yes                    | No                      |
| Tree-shaking    | Yes                    | No                      |
| `__dirname`     | No (use `import.meta`) | Yes                     |
| Browser support | Yes (native)           | No (needs bundler)      |

```js
// ESM equivalent of __dirname
import { fileURLToPath } from "url";
import { dirname }       from "path";
const __filename = fileURLToPath(import.meta.url);
const __dirname  = dirname(__filename);
```

### npm Basics

```bash
npm install pkg          # add dependency
npm install -D pkg       # add dev dependency
npm uninstall pkg        # remove
npm update               # update all
npm run script-name      # run script from package.json
npm list --depth=0       # list installed packages
npm outdated             # check for updates
```

---

## Bundlers

Bundle multiple source files into one (or a few) optimized output files.

| Bundler     | Use case                              |
|-------------|---------------------------------------|
| **Vite**    | Modern dev server + production build  |
| **esbuild** | Extremely fast builds (Go-based)      |
| **Webpack** | Highly configurable, large projects   |
| **Rollup**  | Libraries, clean ESM output           |
| **Parcel**  | Zero-config apps                      |

```bash
# Vite — fastest dev experience
npm create vite@latest my-app -- --template vanilla
cd my-app && npm install && npm run dev

# esbuild
npx esbuild src/index.js --bundle --outfile=dist/bundle.js --minify

# Webpack
npm install --save-dev webpack webpack-cli
npx webpack --config webpack.config.js
```

**Typical Vite config (`vite.config.js`):**
```js
import { defineConfig } from "vite";

export default defineConfig({
  build: {
    outDir: "dist",
    minify: true,
    sourcemap: true
  },
  server: {
    port: 3000,
    proxy: {
      "/api": "http://localhost:8080"
    }
  }
});
```

---

## Browser APIs

### DOM Manipulation

```js
// Selecting elements
const el   = document.getElementById("app");
const btn  = document.querySelector(".btn");        // first match
const btns = document.querySelectorAll(".btn");     // NodeList
const divs = document.getElementsByTagName("div");  // HTMLCollection

// Creating and inserting elements
const p = document.createElement("p");
p.textContent  = "Hello World";          // safe (no HTML injection)
p.innerHTML    = "<strong>Hello</strong>"; // HTML — careful with user input!
p.className    = "message";
p.dataset.userId = "123"; // data-user-id attribute

document.body.appendChild(p);
document.body.prepend(p);
btn.before(p);
btn.after(p);
p.remove();

// Attributes
el.setAttribute("aria-hidden", "true");
el.getAttribute("href");
el.removeAttribute("disabled");
el.toggleAttribute("hidden");
el.hasAttribute("disabled");

// Classes
el.classList.add("active", "visible");
el.classList.remove("hidden");
el.classList.toggle("open");
el.classList.contains("active");     // true
el.classList.replace("old", "new");

// Traversal
el.parentElement;
el.children;           // HTMLCollection of child elements
el.firstElementChild;
el.lastElementChild;
el.nextElementSibling;
el.closest(".container"); // nearest ancestor matching selector
```

### Events

```js
// Adding event listeners
btn.addEventListener("click", handleClick);
btn.addEventListener("click", handleClick, { once: true }); // fires only once

function handleClick(event) {
  event.preventDefault();   // cancel default action (link, form submit)
  event.stopPropagation();  // stop event bubbling
  console.log(event.target);        // element that triggered the event
  console.log(event.currentTarget); // element with the listener
}

// Common events
el.addEventListener("click",      handler);
el.addEventListener("dblclick",   handler);
el.addEventListener("mousemove",  handler);
el.addEventListener("mouseenter", handler); // no bubbling
el.addEventListener("keydown",    e => console.log(e.key, e.code));
el.addEventListener("submit",     e => e.preventDefault());
el.addEventListener("input",      handler); // fires on every keystroke
el.addEventListener("change",     handler); // input changed and blurred
el.addEventListener("focus",      handler);
el.addEventListener("scroll",     handler);
window.addEventListener("resize", handler);
document.addEventListener("DOMContentLoaded", handler);

// Event delegation — attach listener to parent, handle children
document.querySelector(".list").addEventListener("click", (e) => {
  const item = e.target.closest(".list-item");
  if (!item) return;
  console.log("Clicked item:", item.dataset.id);
});

// Custom events
const myEvent = new CustomEvent("user:login", {
  detail: { userId: 42 },
  bubbles: true
});
document.dispatchEvent(myEvent);
document.addEventListener("user:login", e => console.log(e.detail.userId));
```

### localStorage & sessionStorage

```js
// localStorage — persists across sessions (no expiry)
localStorage.setItem("theme", "dark");
localStorage.getItem("theme");        // "dark"
localStorage.removeItem("theme");
localStorage.clear();

// sessionStorage — cleared when tab is closed
sessionStorage.setItem("temp", "value");

// Storing objects (must serialize to JSON)
const user = { name: "Alice", preferences: { lang: "en" } };
localStorage.setItem("user", JSON.stringify(user));
const stored = JSON.parse(localStorage.getItem("user"));

// Storage utility with error handling
const storage = {
  get(key, fallback = null) {
    try {
      const item = localStorage.getItem(key);
      return item !== null ? JSON.parse(item) : fallback;
    } catch { return fallback; }
  },
  set(key, value) {
    try { localStorage.setItem(key, JSON.stringify(value)); }
    catch (e) { console.error("Storage write failed", e); }
  },
  remove(key) { localStorage.removeItem(key); }
};
```

---

## TypeScript (Quick Reference)

TypeScript adds **static types** to JavaScript, catching bugs at compile time.

```bash
npm install -D typescript
npx tsc --init       # create tsconfig.json
npx tsc              # compile
npx tsc --watch      # compile on save
```

### Basic Types

```ts
let age:     number    = 30;
let name:    string    = "Alice";
let active:  boolean   = true;
let id:      bigint    = 9007199254740993n;
let nothing: null      = null;
let undef:   undefined = undefined;

// Special types
let anything: any     = "anything"; // opt out of type checking (avoid)
let unknown:  unknown = getData();  // like any, but safer — must narrow before use
let voidFn:   void;                 // function with no meaningful return value

// Type assertions
const input = document.getElementById("name") as HTMLInputElement;
```

### Advanced Types

```ts 
let direction: "top" | "bottom"; // can only have the value of one the declared literals
let unionType: string | number;  // can be either
let name: string | null;         // can be null
let intersection: FirstType & SecondType; // is a combination of both
```

### Arrays & Tuples

```ts
const nums:   number[]       = [1, 2, 3];
const strs:   Array<string>  = ["a", "b"];

// Tuple — fixed-length, typed positions
const point:  [number, number]          = [10, 20];
const entry:  [string, number, boolean] = ["Alice", 30, true];

// Readonly
const fixed: readonly number[] = [1, 2, 3];
// fixed.push(4); // Error
```

### Functions

```ts
function add(a: number, b: number): number {
  return a + b;
}

// Optional and default parameters
function greet(name: string, greeting?: string): string {
  return `${greeting ?? "Hello"}, ${name}`;
}

// Rest params
function sum(...nums: number[]): number {
  return nums.reduce((a, b) => a + b, 0);
}

// Function types
type Transformer = (input: string) => string;
const upper: Transformer = s => s.toUpperCase();

// Overloads
function process(x: string): string;
function process(x: number): number;
function process(x: string | number) {
  if (typeof x === "string") return x.toUpperCase();
  return x * 2;
}
```

### Interfaces

```ts
interface User {
  readonly id: number;  // cannot reassign after creation
  name:        string;
  email?:      string;  // optional
  greet():     string;
}

// Extending interfaces
interface Admin extends User {
  role: "admin" | "superadmin";
  permissions: string[];
}

// Implementing in a class
class UserImpl implements User {
  constructor(public readonly id: number, public name: string) {}
  greet() { return `Hi, I'm ${this.name}`; }
}

// Index signatures
interface StringMap {
  [key: string]: string;
}
const headers: StringMap = { "Content-Type": "application/json" };
```

### Type Aliases

```ts
type ID = string | number;
type Status = "active" | "inactive" | "pending"; // union literal type
type Nullable<T> = T | null;

// Object types
type Point   = { x: number; y: number };
type Point3D = Point & { z: number };  // intersection type

// Generic types
type ApiResponse<T> = {
  data:      T;
  status:    number;
  message:   string;
  timestamp: Date;
};
type UserResponse  = ApiResponse<User>;
type ListResponse<T> = ApiResponse<T[]>;
```

### Generics

```ts
// Generic function
function identity<T>(value: T): T { return value; }
identity<string>("hello");
identity(42); // inferred

// Generic with constraint
function getProperty<T, K extends keyof T>(obj: T, key: K): T[K] {
  return obj[key];
}
getProperty({ name: "Alice", age: 30 }, "name"); // "Alice"

// Generic class
class Stack<T> {
  private items: T[] = [];
  push(item: T): void { this.items.push(item); }
  pop(): T | undefined { return this.items.pop(); }
  get size() { return this.items.length; }
}
const numStack = new Stack<number>();

// Utility types (built-in)
type UserUpdate  = Partial<User>;           // all optional
type UserStrict  = Required<User>;          // all required
type UserReadonly = Readonly<User>;          // all readonly
type UserPreview = Pick<User, "id" | "name">; // select keys
type UserCreate  = Omit<User, "id">;          // exclude keys
type UserFlags   = Record<string, boolean>;   // map type
```

---

## Practical Tips

### Code Quality

- Prefer `const` over `let`; avoid `var`
- Use `===` and `!==` (never `==` or `!=`)
- Use `async/await` over raw `.then()` chains
- Keep functions small and focused (single responsibility)
- Validate external input at system boundaries (API calls, user input, file reads)
- Avoid shared mutable state — use immutable patterns where practical
- Use `Object.freeze()` for constants that should never change

### Performance

```js
// Use Map/Set for frequent lookups (O(1) vs array O(n))
const lookup = new Map(users.map(u => [u.id, u]));
const user = lookup.get(42); // O(1)

// Debounce — limit how often a function fires (e.g. search input)
function debounce(fn, delay) {
  let timer;
  return (...args) => {
    clearTimeout(timer);
    timer = setTimeout(() => fn(...args), delay);
  };
}
const handleInput = debounce(e => search(e.target.value), 300);
input.addEventListener("input", handleInput);

// Throttle — ensure function fires at most once per interval (e.g. scroll)
function throttle(fn, interval) {
  let lastTime = 0;
  return (...args) => {
    const now = Date.now();
    if (now - lastTime >= interval) {
      lastTime = now;
      return fn(...args);
    }
  };
}
window.addEventListener("scroll", throttle(updateUI, 100));
```

### Security

```js
// NEVER use innerHTML with user-supplied data — use textContent instead
el.textContent = userInput; // safe
el.innerHTML   = userInput; // DANGER: XSS vulnerability

// Sanitize before inserting HTML (use a library like DOMPurify)
import DOMPurify from "dompurify";
el.innerHTML = DOMPurify.sanitize(userHtml);

// Avoid eval() — executes arbitrary code
eval("alert('xss')"); // DANGER

// Store tokens in httpOnly cookies, not localStorage
// Use Content-Security-Policy headers
// Validate and sanitize all server-side input
```

### Debugging

```js
// Breakpoint in code
debugger;

// Object inspection
console.log(JSON.stringify(obj, null, 2)); // pretty print
console.dir(obj, { depth: null });          // full depth in Node.js

// Stack trace
console.trace("Where was this called?");

// Performance profiling
console.time("operation");
// ... code ...
console.timeEnd("operation");
```

---

## Quick Patterns

### Default Values

```js
// Nullish coalescing — fallback only for null/undefined
const port = process.env.PORT ?? 3000;
const name = user?.name ?? "Guest";

// Logical OR — fallback for any falsy value (0, "", false too)
const val  = input || "default"; // careful: 0 or "" triggers fallback too

// Destructuring defaults
const { x = 0, y = 0, z = 0 } = point;
```

### Short Circuit

```js
// Conditional execution
isLoggedIn && redirect("/dashboard");
isLoading || render(data);

// Optional chaining — safely access deep properties
const city = user?.address?.city;
const len  = arr?.length ?? 0;
user?.save();  // call method only if user is not null/undefined
arr?.[0];      // access index only if arr is not null/undefined
```

### Object Patterns

```js
// Property shorthand
const name = "Alice", age = 30;
const user = { name, age }; // { name: "Alice", age: 30 }

// Computed property names
const key = "status";
const obj = { [key]: "active" }; // { status: "active" }

// Merge objects
const merged = { ...defaults, ...overrides };

// Remove a key immutably
const { unwanted, ...clean } = obj;

// Conditional property inclusion
const config = {
  host: "localhost",
  port: 3000,
  ...(isDev && { debug: true }),    // only includes debug in dev
  ...(ssl && { https: true })
};
```

### Array Patterns

```js
// Sum, min, max
const nums = [3, 1, 4, 1, 5, 9];
const sum  = nums.reduce((a, b) => a + b, 0); // 23
const min  = Math.min(...nums);                 // 1
const max  = Math.max(...nums);                 // 9

// Unique values
const unique = [...new Set(nums)]; // [3, 1, 4, 5, 9]

// Group by
const grouped = people.reduce((groups, person) => {
  (groups[person.city] ??= []).push(person);
  return groups;
}, {});

// Chunk array into pages
const chunk = (arr, size) =>
  Array.from({ length: Math.ceil(arr.length / size) },
    (_, i) => arr.slice(i * size, i * size + size));
chunk([1,2,3,4,5], 2); // [[1,2],[3,4],[5]]

// Zip two arrays
const zip = (a, b) => a.map((x, i) => [x, b[i]]);
zip([1,2,3], ["a","b","c"]); // [[1,"a"],[2,"b"],[3,"c"]]

// Partition (split into two groups)
const [evens, odds] = nums.reduce(
  ([e, o], n) => n % 2 === 0 ? [[...e, n], o] : [e, [...o, n]],
  [[], []]
);
```

### Async Patterns

```js
// Sequential async (one at a time)
for (const item of items) {
  await processItem(item);
}

// Parallel async (all at once)
await Promise.all(items.map(processItem));

// Retry with exponential backoff
async function withRetry(fn, maxRetries = 3) {
  for (let attempt = 0; attempt < maxRetries; attempt++) {
    try {
      return await fn();
    } catch (err) {
      if (attempt === maxRetries - 1) throw err;
      await new Promise(r => setTimeout(r, 2 ** attempt * 100));
    }
  }
}

// Timeout wrapper
function withTimeout(promise, ms) {
  const timeout = new Promise((_, reject) =>
    setTimeout(() => reject(new Error(`Timed out after ${ms}ms`)), ms)
  );
  return Promise.race([promise, timeout]);
}
```

### Utility Functions

```js
// Type checking
const isString  = v => typeof v === "string";
const isNumber  = v => typeof v === "number" && !Number.isNaN(v);
const isObject  = v => v !== null && typeof v === "object" && !Array.isArray(v);
const isDefined = v => v !== null && v !== undefined;

// Safe JSON parse
function safeJSON(str, fallback = null) {
  try { return JSON.parse(str); }
  catch { return fallback; }
}

// Sleep
const sleep = ms => new Promise(resolve => setTimeout(resolve, ms));
await sleep(1000); // wait 1 second

// Unique ID
const uuid    = () => crypto.randomUUID(); // built-in in modern environments
const shortId = () => Math.random().toString(36).slice(2, 9); // 7-char id

// Capitalize first letter
const capitalize = s => s.charAt(0).toUpperCase() + s.slice(1);

// Truncate text
const truncate = (str, max) =>
  str.length > max ? str.slice(0, max - 3) + "..." : str;

// Escape HTML (prevent XSS when building HTML manually)
function escapeHtml(str) {
  return str
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;")
    .replace(/"/g, "&quot;")
    .replace(/'/g, "&#039;");
}

// Deep equality check
function deepEqual(a, b) {
  if (a === b) return true;
  if (typeof a !== "object" || typeof b !== "object") return false;
  if (a === null || b === null) return false;
  const keysA = Object.keys(a), keysB = Object.keys(b);
  if (keysA.length !== keysB.length) return false;
  return keysA.every(key => deepEqual(a[key], b[key]));
}
```


