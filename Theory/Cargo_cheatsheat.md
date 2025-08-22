# Rust Compiler & Cargo Cheatsheet

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


