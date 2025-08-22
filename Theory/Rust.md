# Rust, Rust Compiler & Cargo Cheatsheet

## Basic Compilation with `rustc`

- **Compile a Rust file**
  ```sh
  rustc main.rs
  ```
- **Compile and specify output file**
  ```sh
  rustc main.rs -o output
  ```
- **Enable debugging symbols**
  ```sh
  rustc -g main.rs
  ```
- **Optimize for performance**
  ```sh
  rustc -O main.rs
  ```

## Cargo Basics

- **Create a new project**
  ```sh
  cargo new project_name
  ```
- **Create a new library**
  ```sh
  cargo new project_name --lib
  ```
- **Compile and run the project**
  ```sh
  cargo run
  ```
- **Build the project**
  ```sh
  cargo build
  ```
- **Build in release mode**
  ```sh
  cargo build --release
  ```
- **Check for compilation errors without building**
  ```sh
  cargo check
  ```

## Dependencies and Crates

- **Add a dependency to `Cargo.toml`**
  ```sh
  cargo add crate_name
  ```
- **Update dependencies**
  ```sh
  cargo update
  ```

## Testing

- **Run all tests**
  ```sh
  cargo test
  ```
- **Run a specific test**
  ```sh
  cargo test test_name
  ```

## Formatting and Linting

- **Format code**
  ```sh
  cargo fmt
  ```
- **Check for linting errors (Clippy)**
  ```sh
  cargo clippy
  ```

## Documentation

- **Generate documentation**
  ```sh
  cargo doc --open
  ```

## Running Benchmarks

- **Run benchmarks (nightly only)**
  ```sh
  cargo bench
  ```

## Miscellaneous

- **Clean the build directory**
  ```sh
  cargo clean
  ```
- **List installed Rust versions**
  ```sh
  rustup show
  ```
- **Change Rust version (nightly, stable, etc.)**
  ```sh
  rustup override set nightly
  ```

This cheatsheet covers essential `rustc` and Cargo commands for Rust development. For more details, use `cargo --help` or check the official Rust documentation.


## Rust String Types: Definitions and Use Cases

Rust offers a variety of string-related types optimized for different use cases involving ownership, borrowing, concurrency, and efficiency. This document provides a concise guide to the most common string types and their usage.

---

### `str` (String Slice)

- **Type**: `str`
- **Example**: `"hello"` or `&str`
- **Definition**: A dynamically sized, immutable view into a string. Commonly used as `&str`.
- **Use Case**:
  - Passing string data without taking ownership.
  - Reading string literals and borrowed strings.
- **Example**:
  ```rust
  fn greet(name: &str) {
      println!("Hello, {name}!");
  }
  ```

---

### `String`

- **Type**: `String`
- **Definition**: An owned, heap-allocated, growable UTF-8 string.
- **Use Case**:
  - Creating or modifying string data.
  - Interfacing with APIs that take ownership.
- **Example**:
  ```rust
  let mut s = String::from("Hello");
  s.push_str(", world!");
  ```

---

### `Box<str>`

- **Type**: `Box<str>`
- **Definition**: An owned, heap-allocated string slice with fixed size.
- **Use Case**:
  - Efficient immutable storage of strings when growth is not needed.
  - Reducing memory usage compared to `String`.
- **Example**:
  ```rust
  let boxed: Box<str> = "hello".to_owned().into_boxed_str();
  ```

---

### `Rc<str>`

- **Type**: `Rc<str>`
- **Definition**: A reference-counted immutable string slice.
- **Use Case**:
  - Sharing read-only string data between multiple owners in a single thread.
- **Example**:
  ```rust
  use std::rc::Rc;
  let s = Rc::from("shared string");
  ```

---

### `Arc<str>`

- **Type**: `Arc<str>`
- **Definition**: An atomically reference-counted immutable string slice.
- **Use Case**:
  - Sharing string data across multiple threads safely.
- **Example**:
  ```rust
  use std::sync::Arc;
  let s = Arc::from("thread-safe string");
  ```

---

### `Vec<u8>`

- **Type**: `Vec<u8>`
- **Definition**: A growable vector of raw bytes.
- **Use Case**:
  - Working with binary data, raw encodings, or UTF-8 manipulation.
- **Example**:
  ```rust
  let mut bytes = vec![72, 101, 108, 108, 111];
  bytes.push(33); // '!'
  ```

---

### `[u8]` (Byte Slice)

- **Type**: `[u8]` or `&[u8]`
- **Definition**: A borrowed slice of bytes.
- **Use Case**:
  - Reading a portion of a byte buffer.
  - Efficient zero-copy parsing.
- **Example**:
  ```rust
  fn process(bytes: &[u8]) {
      println!("Bytes: {:?}", bytes);
  }
  ```

---

### String Literals

- **Type**: `&'static str`
- **Definition**: A string slice with `'static` lifetime embedded directly into the binary. Can also use raw bytes inside if 
   prefixed by `b`. If prefixed by `r` then special characters can be used wihtout backslashes, you also have to 
   add `#` after `b` and at the end of the string. Both prefixes can be combined.
- **Use Case**:
  - Constants and messages hardcoded in the source.
- **Example**:
  ```rust
  const GREETING: &str = "Hello, world!";
  let png_signature = br#"\x89PNG\r\n\x1a\n"#;
  ```

---

### `Cow<'a, str>`

- **Type**: `Cow<'a, str>`
- **Definition**: Clone-on-write string that can be either a borrowed `&'a str` or an owned `String`.
- **Use Case**:
  - API design that avoids unnecessary allocations while allowing mutation when needed.
- **Example**:
  ```rust
  use std::borrow::Cow;

  fn to_uppercase(input: &str) -> Cow<str> {
      if input.chars().all(char::is_uppercase) {
          Cow::Borrowed(input)
      } else {
          Cow::Owned(input.to_uppercase())
      }
  }
  ```

## Interoperablity strings

- `OsString`: For OS specific string formats.
- `Path` and `PathBuf`: For paths. 
- `Cstr` and `CString`: For interacting with **C** libraries
---

## Summary Table

| Type         | Owned | Mutable | Thread-safe | Use Case                                     |
|--------------|-------|---------|-------------|----------------------------------------------|
| `&str`       | ❌     | ❌       | ✅           | Borrowed strings                             |
| `String`     | ✅     | ✅       | ❌           | Owned, growable string                       |
| `Box<str>`   | ✅     | ❌       | ❌           | Immutable, heap-allocated string             |
| `Rc<str>`    | ✅     | ❌       | ❌           | Shared strings in single-threaded context    |
| `Arc<str>`   | ✅     | ❌       | ✅           | Shared strings in multi-threaded context     |
| `Vec<u8>`    | ✅     | ✅       | ❌           | Binary or UTF-8 manipulation                 |
| `&[u8]`      | ❌     | ❌       | ✅           | Borrowed byte slices                         |
| String Literal | ❌   | ❌       | ✅           | Static, compile-time strings                 |
| `Cow<'a, str>` | ✅/? | ✅/?     | ✅           | Efficient string APIs                        |

---

## Declarative Macros

### Syntax

- **Macro Export**

It is used to allow the usesage macros declared in other files. `#[macro_export]`

- **The macro_rules! Keyword**

All declarative macros begin with the macro_rules! keyword, followed by the macro's name and a block of rules enclosed in curly braces.

```rust
macro_rules! my_macro {
    // Rules go here
}
```

- **Macro Rules: Pattern and Transcriber**

Each rule within a `macro_rules!` definition consists of two main parts: a pattern and a transcriber. These are separated by an => token.

```rust
macro_rules! my_macro {
    // Pattern => Transcriber;
    ($val:expr) => {
        println!("The value is: {}", $val);
    };
}
```

- **Patterns**

The pattern specifies the syntax the macro expects to match when it's invoked. Patterns are similar to Rust's expression syntax but include special "metavariables" that capture parts of the input.

* Metavariables: Metavariables are denoted by a dollar sign ($) followed by a name (e.g., $name) and a fragment specifier (e.g., :expr, :ty, :ident). The fragment specifier tells the macro what kind of Rust syntax it should expect to capture.

Common fragment specifiers include:

* :expr: Matches a Rust expression (e.g., 1 + 2, my_function(), x).

* :ty: Matches a Rust type (e.g., i32, String, &[T]).

* :ident: Matches a Rust identifier (e.g., foo, Bar, my_variable).

* :path: Matches a Rust path (e.g., std::collections::HashMap, crate::my_module::MyStruct).

* :pat: Matches a Rust pattern (e.g., Some(x), [a, b, ...], _).

* :stmt: Matches a single Rust statement.

* :block: Matches a Rust block of code (e.g., { let x = 5; x + 1 }).

* :item: Matches a Rust item (e.g., a function, a struct, an enum).

* :meta: Matches a meta item inside an attribute (e.g., #[derive(Debug)]).

* :tt: Matches a single token tree (any sequence of tokens that is balanced, e.g., (1, 2), { 3 }, [4]).

Repetition Operators: You can specify that a pattern can occur zero or more times, or one or more times, using repetition operators:

* \*: Matches zero or more repetitions of the preceding pattern.

* +: Matches one or more repetitions of the preceding pattern.

* ?: Matches zero or one occurrence of the preceding pattern (optional).

These operators are often used with a separator (e.g., ,, ;) to indicate how the repeated elements are separated. The repetition and separator are enclosed in parentheses: ( $metavariable:fragment_specifier $(separator)? )* or +.

```rust
macro_rules! sum_all {
    // Matches one or more expressions separated by commas
    ($($num:expr),+) => {
        // ...
    };
}
```

- **Transcribers**

The transcriber is the code that the macro expands to when its corresponding pattern is matched. It uses the metavariables captured in the pattern to generate new Rust code. The transcriber is 
typically enclosed in curly braces {}.

```rust
macro_rules! debug_print {
    ($($arg:expr),*) => { // Pattern: zero or more expressions separated by commas
        $( // Repetition in the transcriber
            println!("DEBUG: {}", $arg); // Use the captured metavariable
        )*
    };
}

// Example usage:
// debug_print!("hello", 123, true);
// This would expand to:
// println!("DEBUG: {}", "hello");
// println!("DEBUG: {}", 123);
// println!("DEBUG: {}", true);
```

- **Multiple Rules**

A single macro_rules! definition can have multiple rules, allowing the macro to handle different input syntaxes or argument 
counts. The macro tries to match the input against each rule in order from top to bottom. The first rule that successfully matches is used for expansion.

```rust
macro_rules! greet {
    // Rule 1: No arguments
    () => {
        println!("Hello, World!");
    };
    // Rule 2: One argument (an identifier)
    ($name:ident) => {
        println!("Hello, {}!", stringify!($name));
    };
    // Rule 3: One argument (an expression)
    ($message:expr) => {
        println!("{}", $message);
    };
}

// greet!();           // Expands to println!("Hello, World!");
// greet!(Rustacean);  // Expands to println!("Hello, Rustacean!");
// greet!("Good morning!"); // Expands to println!("Good morning!");
```

In the greet! macro, stringify! is another macro that converts a token tree (like an identifier) into a string literal. This is often useful for debugging or 
generating descriptive output.


