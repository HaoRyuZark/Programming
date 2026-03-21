# JavaScript

## JavaScript Runtime Environments

JavaScript runs inside a host environment that provides APIs.

```js
console.log(window.location.href); // Browser
console.log(process.version);      // Node.js
```

* Browser: DOM (UI), BOM (browser features)
* Node.js: OS, file system, processes
* Engine (e.g. V8) executes JS code

---

## Basics

### Variables

Declare and store values with different scopes.

```js
let x = 10;
const y = 20;
```

* `var`: function scope (avoid)
* `let`: block scope, mutable
* `const`: block scope, immutable reference

---

### Data Types

Primitive and reference values.

```js
let n = 42;
let s = "text";
let obj = {};
```

* Primitives: number, string, boolean, null, undefined, bigint, symbol
* Objects: arrays, functions, objects

---

### Conditionals

Execute code based on conditions.

```js
if (x > 0) {}
const res = x > 0 ? "yes" : "no";
```

* `if/else`, ternary operator

---

### Loops

Repeat execution.

```js
for (let i = 0; i < 3; i++) {}
for (const v of arr) {}
```

* `for`, `while`, `for...of` (values), `for...in` (keys)

---

### Operators

Perform computations and comparisons.

```js
x + y;
x === y;
a && b;
```

* Arithmetic, comparison, logical
* `===` strict equality (no coercion)

---

### Functions

Reusable blocks of code.

```js
function f(a) { return a; }
const g = a => a;
```

* First-class values (can pass/return)
* Arrow functions are shorter

---

## Input / Output

### Console

Basic output for debugging.

```js
console.log("Hello");
```

* `log`, `error`, `table`

### File System (Node.js)

Read/write files from disk.

```js
fs.readFileSync("file.txt", "utf-8");
```

* Synchronous and async APIs

### Process Arguments

Access command-line input.

```js
process.argv;
```

* Array of CLI arguments

---

## Object-Oriented Programming

### Objects

Key-value data structures.

```js
const obj = { a: 1 };
```

* Methods use `this`


### Classes

Blueprint for creating objects.

```js
class A { constructor(x) { this.x = x; } }
```

* Syntactic sugar over prototypes

### Inheritance

Reuse behavior from another class.

```js
class B extends A {}
```

* `extends`, `super()`


### Prototypes

Underlying inheritance mechanism.

```js
A.prototype.method = function() {};
```

* Objects inherit via prototype chain

---

## Memory & Copying

### Shallow Copy

Copies top-level only.

```js
const copy = { ...obj };
```

* Nested objects still shared

### Deep Copy

Copies entire structure.

```js
structuredClone(obj);
```

* No shared references

---

## Core Data Structures

### Arrays

Ordered lists.

```js
arr.push(1);
```

* Indexed, mutable

### Sets

Unique values collection.

```js
set.add(1);
```

* No duplicates


### Maps

Key-value pairs (any key type).

```js
map.set("k", "v");
```

* Better than objects for dynamic keys

---

## Functional Patterns

### Arrow Functions

Short function syntax.

```js
x => x * 2;
```

* No own `this`

---

### map / filter / reduce

Array transformations.

```js
arr.map(x => x * 2);
```

* `map`: transform
* `filter`: select
* `reduce`: accumulate

---

## Spread Syntax

Expand or copy values.

```js
[...arr];
{ ...obj };
```

* Used for cloning/merging

--- 

## Destructuring

Extract values easily.

```js
const { a } = obj;
```

* Works with arrays and objects

---

## Error Handling

Handle runtime errors safely.

```js
try {} catch (e) {}
```

* Prevent crashes

### Custom Errors

Define specific error types.

```js
class MyError extends Error {}
```

* Useful for structured handling

---

## Asynchronous JavaScript

### Promises

Handle async results.

```js
promise.then().catch();
```

* States: pending, fulfilled, rejected

### async / await

Simplified async syntax.

```js
await fetch(url);
```

* Looks synchronous, uses promises

---

## Modules & Ecosystem

### ES Modules

Standard module system.

```js
import x from "./file.js";
```

* Static, modern

### CommonJS

Older Node.js modules.

```js
require("fs");
```

* Dynamic loading

### npm Basics

Package manager usage.

```bash
npm install pkg
```

* Manage dependencies

---

## Bundlers

Combine multiple files into one.

```js
import "./mod.js";
```

* Resolve imports, optimize code

---

## TypeScript (Quick Reference)

### Basic Types

Add static typing.

```ts
let x: number = 1;
```

* Improves safety

### Arrays & Functions

Typed collections and functions.

```ts
function f(a: number): number {}
```

### Interfaces

Define object shapes.

```ts
interface A { x: number }
```

* Contracts for objects

### Type Aliases

Custom type names.

```ts
type ID = string | number;
```

* Combine types

---

## Practical Tips

* Prefer `const` and immutability
* Use `===` for comparisons
* Handle async with `async/await`
* Validate external input
* Avoid shared mutable state

---

## Quick Patterns

### Default Values

Fallback for null/undefined.

```js
x ?? "default";
```


### Short Circuit

Conditional execution.

```js
cond && fn();
```


### Object Property Shorthand

Short object creation.

```js
const obj = { x };
```

### Dynamic Keys

Computed property names.

```js
{ [key]: value }
```


