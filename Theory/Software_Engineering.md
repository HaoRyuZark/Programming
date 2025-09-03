# General Software Engineering Topics

## Table of contents

| Topic                                   | Concepts                                                                                                   |
| :-------------------------------------- |:-----------------------------------------------------------------------------------------------------------|
| Learning                                | How to learn, strategies, preparation, etc.                                                                |
| Responsibility for One's Craft          | Dunning-Kruger Effect,Principle of Least Surprise, Scout Rule, WTF Metric                                  |
| Software Quality and Quality Management | Measurable and Non-measurable                                                                              |
| Software Testing                        | Test Driven Development, Unit, Integration, End-to-End, Smoke, Regression, Acceptance                      |
| Design Principles                       | Visual Hierarchy, Contrast, Consistency, Balance, Feedback, Simplicity, Alignment, Proximity, Repetition   |
| Clean Code & Code Smells                | Readability, Naming-conventions, Dead Code, Long Methods, Magic Numbers, Comments vs. Clarity,Bad practices|
| Coding Paradigms                        | Object-Oriented & Functional Programming, Architectural Decisions, Imperative vs Declarative               |
| Design Patterns & Design Principles     | Coupling, Cohesion, Convention                                                                             |
| Design Patterns & Design Principles     | SOLID: Single Responsibility, Open/Closed, Liskov Substitution, Interface Segregation, Dependency Inversion|
| Design Patterns & Design Principles     | Composite & Adapter                                                                                        |
| Design Patterns & Design Principles     | Builder & Command                                                                                          |
| Design Patterns & Design Principles     | Observer & Singleton                                                                                       |
| Design Patterns & Design Principles     | Dependency Injection & Inversion of Control                                                                |
| Design Patterns & Design Principles     | Model-View-Controller (MVC)                                                                                |
| Design Patterns & Design Principles     | Object-Relational Mapping (Entity, DAO, Services)                                                          |
| Requirements and Task Specification     | User Stories, Use Cases,Acceptance Criteria, INVEST Principle                                              |
| Time Estimation & Time Management       | Planning Poker, Time Boxing,Eisenhower Matrix, Pomodoro Technique                                          |
| Logging                                 | Logging Levels (Info, Debug, Warn, Error), Log Rotation, Centralized Logging, Structured Logs              |
| Error Detection and Debugging           | Breakpoints, Stack Traces, Watch Expressions, Reproducing Bugs, Rubber Duck Debugging                      |
| Profiling                               | CPU Usage, Memory Leaks, I/O Bottlenecks, Tools like perf, JProfiler, VisualVM                             |
| Refactoring                             | Red-Green-Refactor Cycle, Code Simplification, Removing Duplication, Improving Naming                      |
| Unit Testing                            | Arrange-Act-Assert Pattern, Mocking, Test Coverage, Isolation, Assertions                                  |
| Data Protection & Data Security         | GDPR, Encryption, Authentication, Authorization, Secure by Design                                          |
| Technology Radar                        | Hype Cycle                                                                                                 |
| Technology Radar                        | Agile & Lean                                                                                               |
| Technology Radar                        | Continuous Integration &Continuous Deployment                                                              |
| Technology Radar                        | WWW, Web Browser, Web Services                                                                             |
| Technology Radar                        | DevOps, Cloud, PaaS, SaaS, FaaS                                                                            |
| Technology Radar                        | Data Mining, Big Data, DataWarehouse, Data Lake                                                            |
| Technology Radar                        | Digitalization & Internet of Things                                                                        |
| Technology Radar                        | Artificial Intelligence & Machine Learning                                                                 |

---

## Learning 

Learning a new skill, technology or concept takes primarily time and effort. This effort is materialized in the form of reading, watching a video, listening to a podcast, 
attending a course, taking notes and practicing. All of which cost time. Learning always takes time, but there are some strategies which can help 
to optimize the learning process.

### Strategies for learning and solve problems better:

**Active Learning**: Do not just listen or read passively. Practice, ask questions, try making hypotheses and test them. 

**Take Notes**: Either by hand or digitally, taking notes helps reinforce what you learn. Summarize key points in your own words.

**Teach Others**: Explaining concepts to others forces you to clarify your understanding and identify

**Make a Plan**: Set specific learning goals and break them down into manageable tasks. This helps maintain focus and track progress. Also, if the plan fails, then proceed to make 
the necessary adjustments.

**Practice Regularly**: Consistent practice is more effective than cramming. Prepare a set of practice material and work on it. Choose material that is relevant to your learning goals.

**Seek Feedback**: Share your work with peers or mentors to get constructive criticism.

**Exam Conditions**: Simulate exam conditions by timing yourself and working without resources. This helps build confidence and identify areas for improvement.

**Revisit and Reflect**: Regularly review what you’ve learned.

**Breaks**: Do not overdo it. Take breaks and do other activities to let your brain rest and process information.

**Sleep**: Sleep is crucial for memory consolidation.

**Use the Horizon**: When trying to solve a problem, do not just focus on the problem itself and think about solving it mechanically. Instead, look at the bigger picture, 
consider the context, ask how does this problem relate to other problems, and how does it fit into the overall system or project, which techniques or tools can be used to solve it, etc.

## Responsibility for One's Craft

### Dunning-Kruger Effect

This cognitive bias describes how people with low ability at a task overestimate their ability. In software development, it reminds us to stay humble, continuously learn, and seek feedback. As skills improve, one often becomes more aware of what they don’t know.

### Principle of Least Surprise

Code should behave in a way that surprises users and developers the least. When behavior is intuitive and consistent with expectations, it reduces cognitive load and errors. For instance, a method named `getUser()` should not delete data.

### Scout Rule

_“Leave the code better than you found it.”_  
Inspired by the Boy Scouts’ principle, this encourages developers to improve readability, naming, or structure with each change, even in small ways.

### WTF Metric

The “WTFs per minute” metric is a humorous way to measure code quality. Code that is difficult to understand or inconsistent tends to generate more “WTF” reactions from reviewers. The lower the WTF count, the better the code.

---

## Software Quality and Quality Management

### Measurable Quality

These are objective aspects of software that can be quantified, including:

-   Code coverage
-   Performance (latency, throughput)
-   Number of bugs
-   Uptime

### Non-measurable Quality

Subjective and harder to quantify, yet critical for long-term success:

-   Maintainability
-   Developer satisfaction
-   Usability
-   Aesthetic quality
-   Scalability potential

A good quality management approach balances both measurable and non-measurable aspects, using metrics where possible while relying on experience and best practices otherwise.

---

## Test Driven Development (TDD)

A practice where tests are written before the code. The cycle follows:

1. **Red** – Write a failing test.
2. **Green** – Write the minimum code to pass the test.
3. **Refactor** – Improve the code while ensuring the test still passes.

### Unit Testing

Tests individual components (usually functions or classes) in isolation. Fast and localized, it's the foundation of a reliable test suite.

### Integration Testing

Verifies that multiple components work together as expected. For example, testing interactions between a database and an API layer.

### End-to-End (E2E) Testing

Simulates real user scenarios through the full stack, testing the system from start to finish. Useful for detecting issues in user flows.

### Smoke Testing

A basic test suite run to check whether the major functions of an application work after a build or deployment. Often called “build verification tests.”

### Regression Testing

Ensures that recent changes haven’t broken existing functionality. It helps prevent reintroducing old bugs.

### Acceptance Testing

Tests whether the system meets business requirements. Often done by QA or stakeholders using user stories or criteria.

### Given-When-Then Naming Convention

A part variant of the Test-Driven Development approach is the Behavior-Driven Development.
This methodology uses the Given-When-Then format to describe tests such that it tells the expected behavior of the system in a human-readable way.

-   **Given**: The initial context or state.
-   **When**: The action or event that occurs.
-   **Then**: The expected outcome or result.

---

## Design Principles

### Visual Hierarchy

Elements are arranged to indicate their importance. Techniques include size, color, and positioning.

### Contrast

Use of differing colors, fonts, or shapes to distinguish elements and draw attention to key areas.

### Consistency

Uniform use of design elements, such as fonts, colors, and button styles, helps users learn interfaces quickly.

### Balance

The visual weight of elements should be evenly distributed to prevent clutter and enhance readability.

### Feedback

The system should communicate actions, changes, and errors clearly. Examples include button state changes, loading indicators, or error messages.

### Simplicity

Only include what’s necessary. Avoid overcomplicating interfaces or adding options that aren’t used often.

### Alignment

Proper alignment improves structure and readability. Misaligned content can feel chaotic or unprofessional.

### Proximity

Related items should be grouped together. For example, labels and input fields should be near each other.

### Repetition

Reusing elements and styles builds familiarity and reduces the learning curve for users.

---

## Clean Code & Code Smells

### Readability

The primary measure of clean code. It should be easy to read and understand by others (or future you). Good indentation, consistent style, and meaningful structure are key.

### Naming Conventions

Use meaningful and consistent names for variables, functions, and classes. Avoid single-letter names except in trivial contexts.

### Dead Code

Code that is never executed or referenced. It clutters the codebase and should be removed.

### Long Methods

Functions that do too much become hard to test, understand, and maintain. They should be broken into smaller, single-purpose methods.

### Magic Numbers

Using unexplained numeric constants in code. Replace them with named constants to improve clarity and meaning.

### Comments vs. Clarity

Well-written code often needs fewer comments. Use comments to explain _why_ something is done, not _what_ is done — the code should speak for itself.

### Bad Practices

Includes inconsistent formatting, lack of error handling, deep nesting, and premature optimization. Adhering to best practices avoids these and improves code longevity.

---

## Coding Paradigms

### Object-Oriented Programming (OOP)

A paradigm based on objects that encapsulate data and behavior. Key principles include inheritance, polymorphism, encapsulation, and abstraction.

### Functional Programming (FP)

A declarative paradigm where computation is done through pure functions and immutability. FP avoids side effects and favors composability and higher-order functions.

### Architectural Decisions

Choosing the right architecture (e.g., layered, microservices, event-driven) affects scalability, maintainability, and performance. It’s important to consider trade-offs early in the project lifecycle.

### Imperative vs. Declarative

-   **Imperative**: Specifies _how_ to perform tasks step-by-step (e.g., for loops).
-   **Declarative**: Focuses on _what_ the outcome should be, leaving the "how" to the underlying system (e.g., SQL, React).

---

### Coupling

The degree of interdependence between components. Low coupling means components can be changed independently, which improves flexibility and reusability.

### Cohesion

How closely related the responsibilities of a single module are. High cohesion means the module focuses on a single task or area of functionality, which improves readability and maintainability.

### Convention

Establishing and adhering to agreed-upon patterns and naming schemes across a codebase. Conventions reduce cognitive overhead and make code more predictable and standardized.

---

## SOLID

The SOLID principles are a set of five object-oriented design principles aimed at making software designs more understandable, flexible, and maintainable. Coined by Robert C. Martin (Uncle Bob), these principles help developers build robust and scalable systems.

---

**1. Single Responsibility Principle (SRP)**  
_“A class should have only one reason to change.”_  
SRP advocates that a class should do one thing and do it well. It should encapsulate only one responsibility or functionality of the software. When a class is responsible for more than one thing, changes to one responsibility can affect the others, increasing the risk of bugs and reducing maintainability.

_Example:_  
A `UserManager` class should only manage user data and not handle user authentication. Authentication should be a separate responsibility handled by an `Authenticator` class.

---

**2. Open/Closed Principle (OCP)**  
_“Software entities (classes, modules, functions, etc.) should be open for extension but closed for modification.”_  
This principle encourages designing systems in a way that allows the addition of new functionality without altering existing code. This is often achieved using abstractions such as interfaces or abstract classes.

_Example:_  
If you have a class that calculates area for shapes, instead of modifying it every time you add a new shape, use a `Shape` interface with an `area()` method and implement it in each shape class (`Circle`, `Rectangle`, etc.).

---

**3. Liskov Substitution Principle (LSP)**  
_“Objects of a superclass should be replaceable with objects of its subclasses without breaking the application.”_  
LSP ensures that derived classes extend the base classes without changing their behavior. Subclasses must adhere to the expectations set by the parent class.

_Example:_  
If `Bird` has a method `fly()`, then a `Penguin` class extending `Bird` violates LSP because penguins can’t fly. In such cases, hierarchy needs to be rethought, possibly introducing a `FlightlessBird` subclass.

---

**4. Interface Segregation Principle (ISP)**  
_“Clients should not be forced to depend upon interfaces they do not use.”_  
This principle promotes creating smaller, more specific interfaces rather than a large, all-encompassing one. It helps avoid forcing classes to implement methods that are not relevant to them.

_Example:_  
Instead of a single `IMachine` interface with `print()`, `scan()`, and `fax()` methods, create separate interfaces like `IPrinter`, `IScanner`, and `IFaxMachine`. This way, a `Printer` class only implements `IPrinter`.

---

**5. Dependency Inversion Principle (DIP)**  
_“High-level modules should not depend on low-level modules. Both should depend on abstractions.”_  
This principle reduces coupling by ensuring that both high-level and low-level modules depend on interfaces or abstract classes. It also promotes the use of dependency injection to provide concrete implementations.

_Example:_  
A `PaymentProcessor` should not directly instantiate a `StripePaymentService`. Instead, it should depend on an interface `IPaymentService`, and the implementation (`StripePaymentService`) can be injected at runtime.

---

## DevOps

Is a set of practices, tools, and a cultural philosophy  that automate and integrate the processes between 
software development and IT operations teams.

### Phases 

- Plan 
- Code 
- Build
- Test 
- Release 
- Deploy 
- Operate 
- Monitor 
- Repeat



# Design Patterns in Object-Oriented Programming (OOP)

### Singleton Pattern

**Definition:**  
Ensures a class has only one instance and provides a global point of access to it.

**Common Use Cases:**
- Logging services
- Configuration managers
- Thread pools
- Caches
- Database connection pools

### Factory Method Pattern

**Definition:**  
Defines an interface for creating an object, but lets subclasses decide which class to instantiate.

**Common Use Cases:**
- Frameworks that need to standardize object creation
- When object creation should be deferred to subclasses
- Managing and maintaining object creation logic

### Abstract Factory Method Pattern

**Definition:**  
Provides an interface for creating families of related or dependent objects without specifying their concrete classes.

**Common Use Cases:**
- UI toolkits that support multiple themes
- Product configurations across different platforms (e.g., Windows, macOS)
- Ensuring consistency among related products

### Builder Pattern

**Definition:**  
Separates the construction of a complex object from its representation, allowing the same construction process to create different representations.

**Common Use Cases:**
- Creating complex objects with many optional parameters
- Building configurations step-by-step
- Generating different representations of a product

### Adapter Pattern

**Definition:**  
Allows incompatible interfaces to work together by converting one interface into another expected by the client.

**Common Use Cases:**
- Integrating legacy code with new systems
- Reusing existing classes without modifying them
- Working with APIs that are incompatible

### Proxy Pattern

**Definition:**  
Provides a surrogate or placeholder for another object to control access to it.

**Common Use Cases:**
- Lazy loading
- Access control
- Logging and monitoring
- Remote object interaction (e.g., RPC, CORBA)

### Decorator Pattern

**Definition:**  
Adds responsibilities to objects dynamically without modifying their class.

**Common Use Cases:**
- Adding features to UI elements
- Implementing flexible and reusable features
- Logging, authentication, caching

### Composite Pattern

**Definition:**  
Composes objects into tree structures to represent part-whole hierarchies. Allows clients to treat individual objects and compositions uniformly.

**Common Use Cases:**
- Representing hierarchies like file systems or menus
- Organizational structures
- Scene graphs in graphical editors or games

### Observer Pattern

**Definition:**  
Defines a one-to-many dependency between objects, so that when one object changes state, all dependents are notified.

**Common Use Cases:**
- Event handling systems
- Model-View-Controller (MVC) architectures
- Real-time updates in UIs or dashboards

### Strategy Pattern

**Definition:**  
Defines a family of algorithms, encapsulates each one, and makes them interchangeable.

**Common Use Cases:**
- Implementing interchangeable behaviors (e.g., sorting strategies)
- Avoiding conditional logic for algorithm selection
- Plug-and-play functionality

### Command Pattern

**Definition:**  
Encapsulates a request as an object, allowing for parameterization, queuing, logging, and undo functionality.

**Common Use Cases:**
- GUI buttons and menu actions
- Task queues
- Undo/redo operations

### State Pattern

**Definition:**  
Allows an object to alter its behavior when its internal state changes, appearing as if it changed its class.

**Common Use Cases:**
- Finite state machines
- Workflow engines
- Game AI behavior

### Template Method Pattern

**Definition:**  
Defines the skeleton of an algorithm in a base class, letting subclasses override specific steps without changing the overall structure.

**Common Use Cases:**
- Code reuse for invariant algorithm structure
- Frameworks with customizable workflows
- Data processing pipelines

### Visitor Pattern

**Definition:**  
Separates an algorithm from the object structure on which it operates, allowing new operations without modifying the objects.

**Common Use Cases:**
- Operations on complex object structures (e.g., ASTs)
- Performing multiple unrelated operations on objects
- Syntax tree traversal in compilers

### Memento Pattern

**Definition:**  
Captures and externalizes an object’s internal state without violating encapsulation, so it can be restored later.

**Common Use Cases:**
- Undo/redo functionality
- Savepoints in games or editors
- Snapshotting application states

