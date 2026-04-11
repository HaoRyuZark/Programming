# Clean Code

Set of practices for maintainable and readable code.

## Readability

The primary measure of clean code. It should be easy to read and understand by others (or future you). Good indentation, consistent style, and meaningful structure are key.

---

## Naming Conventions

Use meaningful and consistent names for variables, functions, and classes. Avoid single-letter names except in trivial contexts.

---

## Avoid Dead Code

Code that is never executed or referenced. It clutters the codebase and should be removed.

---

## Avoid Long Methods

Functions that do too much become hard to test, understand, and maintain. They should be broken into smaller, single-purpose methods.

---

## Avoid Magic Numbers

Using unexplained numeric constants in code. Replace them with named constants to improve clarity and meaning.

---

## Avoid Comments vs. Clarity

Well-written code often needs fewer comments. Use comments to explain _why_ something is done, not _what_ is done — the code should speak for itself.

---

## Bad Practices

Includes inconsistent formatting, lack of error handling, deep nesting, and premature optimization. Adhering to best practices avoids these and improves code longevity.

---

## Coupling

The degree of interdependence between components. Low coupling means components can be changed independently, which improves flexibility and reusability.

---

## Cohesion

How closely related the responsibilities of a single module are. High cohesion means the module focuses on a single task or area of functionality, which improves readability and maintainability.

---

## Convention

Establishing and adhering to agreed-upon patterns and naming schemes across a codebase. Conventions reduce cognitive overhead and make code more predictable and standardized.

---

## SOLID

The SOLID principles are a set of five object-oriented design principles aimed at making software designs more understandable, flexible, and maintainable. Coined by Robert C. Martin (Uncle Bob), these principles help developers build robust and scalable systems.

**1. Single Responsibility Principle (SRP)**: Every Class should do only one thing, and that thing very well. For example, a calculator class should not 
contain database handling logic.

**2. Open/Closed Principle (OCP)**: The system, its classes and its relationships have to planned in a way that allows for extensionality i.e. 
use interfaces, abtract classes and the strategy pattern to allow for compact code intead of for example, lon if-else chains for different types. Like always 
maybe somtimes in specific types of systems such a principle can not always be followed.

**3. Liskov Substitution Principle (LSP)**:  Subclasses of a hierarchy should be capable to be handled as its base class. This means that our inheritance has to make sense, in the way 
that from a square we will not derive a circle.

**4. Interface Segregation Principle (ISP)**: Keep interfaces specific and small, do not make gigant interfaces with disjoint functionalities.  

**5. Dependency Inversion Principle (DIP)**: High-level modules should not depend on low-level modules. Both should depend on abtractions such as interfaces. Define 
contracts for your classes and maintain a relationship of dependence of low-level details from High-level.

--- 

## Common Phrases 

- **KISS:** Keep It Simple Stupid.
- **DRY:** Don't Repeat Yourself.
- **Beware of Premature Optimization:** sometimes the a sulution which is not the most optimal is good enought.
- **Favor Composition over Inheritance:** Use inheritance as less as possible, favor interfaces and composite objects.
- **Source Code Conventions:** Code is more often read than written, attach to the conventions and idioms for readability and idioms.
- **YAGNI:** You Ain't Gonna Need It.

--- 

## Avoid Heavily Nested Code 

Whe code is highly nested, it is moslty possible to simplify by refactoring it carefully separating the conditions. This conditions 
if if-else statements can be then put inside a a function with a descriptive name to further improve readability.

--- 


