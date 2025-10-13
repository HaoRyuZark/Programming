# Software Engineering

Software engineering is the practical use of scientific methods
for the economic development of software its use and maintenance.

--- 

## Goals SWE

- Quality software
- Reduction of errors
- Reduction of work
- Maximize clients

--- 

## Life cycle of software

1. Analysis of requirements
2. Design and Architecture
3. Implementation and unit testing
4. Integration and Integration testing
5. Deploymend and Acceptance testing
6. Operation Maintenance
7. Retirement

--- 

## Stakeholder 

Term for the individuals inside the software project: developers, investors, poduct owner, architect, etc.

--- 

## Software Quality 

Capability of sofware product to satisfy steated and implied needs when used under especified conditions.

- **Functional Suitability**
- **Performance Efficiency**
- **Compatibily**
- **Interaction Capability**
- **Reliability**
- **Security** 
- **Mantainability**
- **Safety** 

--- 

## When To Produce New Software

The goal is to minimize the cost of the use of software. The decision is 
**make or buy**

- **Commercial off the Shelf:** Customization, Software as service
- **Total Cost of Ownership:** Return of Investment, Costs of the different phases.

### Balance of using already existing software 


| **Advantages**                                         | **Disadvantages**                                                     |
| ------------------------------------------------------ | --------------------------------------------------------------------- |
| ▪ Faster deployment                                    | ▪ Dependence on the vendor: maintenance, further development, support |
| ▪ Quality improvement through many users               | ▪ Costs of custom software are often underestimated                   |
| ▪ Development costs are borne by a large customer base | ▪ Custom adaptations are rarely possible                              |
| ▪ Higher planning reliability                          | ▪ Further development must be coordinated with many stakeholders      |
| ▪ Total Cost of Ownership (TCO) is generally lower     | ▪ No unique selling point in competition                              |
|                                                        | ▪ Lock-in effect                                                      |


--- 

## Discovery of Errors 


| **Error made** | **Error detected** |
|-------------|----------------|
| User needs| Operation and Maintenance|
|Requirements Analysis | Deployment and Acceptance Testing |
|Desing | Integration Testing |
|Implementation | Unit Testing |
|Code input | IDE and Compiler |


--- 

## Cost of Errors


| **Phase of Error Detection**       | **Cost Factor** |
| ---------------------------------- | :---------------:|
| Requirements Analysis              | 1               |
| Design                             | 3 – 6           |
| Implementation                     | 10              |
| Unit Testing & Integration Testing | 15 – 40         |
| Deployment & Acceptance Testing    | 30 – 70         |
| Operation & Maintenance            | 40 – 1,000      |


--- 

## Waterfall Model

This model takes the steps of the life cycle and orders them
into descending order as the way software is planed, developed, used and
maintained. It has been criticized for not being realistic.

- **Requirements Analysis**
- **Desing**
- **Implementation and Unit Testing**
- **Integration Testing**
- **Deployment and Acceptance Testing**
- **Operation and Maintenance**


| **Advantages**                                       | **Disadvantages**                                                              |
| ---------------------------------------------------- | ------------------------------------------------------------------------------ |
| ▪ Simple & intuitive                                 | ▪ Requires a structured approach                                               |
| ▪ Widely used                                        | ▪ Clients are only involved at the beginning, requirements are often unclear   |
| ▪ Documents                                          | ▪ Testing & acceptance occur late, only after the system is complete           |
| ▪ Written specification documentation                | ▪ Continuous quality assurance is problematic                                  |
| ▪ Contract for handover to next phase                | ▪ "Activity" and "phase" are not clearly separated                             |
| ▪ Easy to monitor as quasi-milestones in the project | ▪ Project management: cycles are problematic, no milestones between activities |
| ▪ Transparent process flow                           |                                                                                |


--- 

## V-Model

The V-Model is an extension of the waterfall model. It emphasizes the
importance of testing at each stage of development. The left side of the V
represents the stages of development, while the right side represents the
stages of testing. The bottom of the V represents the implementation stage.


| **Left Side of V**        |  **Middle of V**   | **Right Side of V**     |
| :-------------------- | :------------: | ------------------- |
| Requirements Analysis |       <-       | Acceptance Testing  |
| System Design         |       <-       | System Testing      |
| Architecture Design   |       <-       | Integration Testing |
| Specification Design  |       <-       | Unit Testing        |
|                       | Implementation |                     |


--- 

## Iterative Development

This model allows developers to plan multiple iterations of the steps: Analysis, Proposal, Implementation and Testing.
Each iteration is a mini-waterfall model. This allows for more flexibility and adaptability to changing requirements
and feedback from users. It is often used in Agile methodologies.

The problems with the waterfall model are that it is too rigid and does not allow for changes once the development process has started.

--- 

## Incremental Development

In this model, the software is developed in small increments or modules. Each increment adds new functionality to the software.
This allows for faster delivery of software and the ability to get feedback from users early in the development process.
It is often used in Agile methodologies as well.

The disadvantage of this model is that it can lead to integration issues if the increments are not well planned and designed. Also,
sometimes the first proposals are not well-thought-out and lead to problems later on in the development process.

--- 

## The Agile Manifest

### The Four Commitments

The part on the right is still important, but we left part should be priorized.

- **Individuals and interactions** are more important than the process and the tools.

- **Functional software** is more important than the documentation.

- **Working together with the clients** instead of contrats.

- **Correct reactions when changes happen** instead of rigid plans.

### The Twelfe Principles

- Our highest priority is to satisfy the customer
  through early and continuous delivery
  of valuable software.

- Welcome changing requirements, even late in
  development. Agile processes harness change for
  the customer's competitive advantage.

- Deliver working software frequently, from a
  couple of weeks to a couple of months, with a
  preference to the shorter timescale.

- Business people and developers must work
  together daily throughout the project.

- Build projects around motivated individuals.
  Give them the environment and support they need,
  and trust them to get the job done.

- The most efficient and effective method of
  conveying information to and within a development
  team is face-to-face conversation.

- Working software is the primary measure of progress.

- Agile processes promote sustainable development.
  The sponsors, developers, and users should be able
  to maintain a constant pace indefinitely.

- Continuous attention to technical excellence
  and good design enhances agility.

- Simplicity--the art of maximizing the amount
  of work not done--is essential.

- The best architectures, requirements, and designs
  emerge from self-organizing teams.

- At regular intervals, the team reflects on how
  to become more effective, then tunes and adjusts
  its behavior accordingly.

### Agile vs Classic


| **Agile** | **Classic** |
|-------|---------|
| Adaptable  | Predicative | 
| Total cost is defined only for each iteration | Total costs are completely calculated |


--- 

## Test Driven Development (TDD)

A practice where tests are written before the code. The cycle follows:

1. **Red** – Write a failing test (Make it Red).
2. **Green** – Write the minimum code to pass the test (Make it Green).
3. **Refactor** – Improve the code while ensuring the test still passes (Make it Blue).

### Advantages and Disadvantages 


| **Advantages**                                       | **Disadvantages**                                                              |
| ---------------------------------------------------- | ------------------------------------------------------------------------------ |
| Very specific                                  | Only functional requirements                                               |
| Continuous Integration                                        | Not a complete specification   |
| Concrete definition of Done                                          | Can become tedious            |
| Specific way of meassuring the progress                |  For stakeholders very complex    |


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

## Refactoring 

To restructure software code without altering its behavior for the purpose of improving quality attributes, easing future extension or adaptation, or 
adhering to an architectural style.

--- 

## Scrum

It is a method which implements the agile principles. It is empiric, incremental and iterative. The goal is
to release functional software in short cycles (sprints).

### Scrum Process

```txt
Product Backlog -> Sprint Planing -> Sprint Backlog -> Sprint -> Product Increment -> Sprint Review -> Retrospective
                                                         |
                                                    Daily Scrum
```

### Roles

- **Product Owner:** Responsable for the economic success. He prepares the product backlog, updates it, checks the product increment
  and he can not interrupt a sprint.

- **Scrum Master:** He plans the scrum organisation, is not technical, communicates between PO and the development team.

- **Development Team:** It consist of 3 to 9 people and it has to know the comple Know-how for the apllication. The social component is also
  very important.

### Artifacts

- **Product backlog:** List of requirements for the product.
- **Spring backlog:** List of backlog items for the sprint.
- **Product-increment:** The actual product, update,, etc.

### Kanban

Another methodology from Japan. Principles:

- **Visualize the workflow** `Backlog : To-Do : In progress : Testing : Done `
- **Regulate the number of tickets**
- **Regulate the flow of tickets to avoid problems like bottlenecks**
- **Define clear rules**
- **Optimize the process**

--- 

## Requirements Engineering

Is the process of defining how a software product is going to be, work, what it needs, etc. There are functional requirements which are very specific
and non-functional which are like 'nice-to-haves'

--- 

## Kano Model

For the categorization of requirements. It consists of two axises, one for the happiness and one for the amount of features. There are three 
ploted lines the **base**, **performance** and **excell** features.

--- 

## Approximation of Work

For the economic viability of a project. Can be accomplised via the approximation of an expert, a group or the Delphi-Method. There are also algorithmic methods.

### Delphi-Method

It is done by making different approximation with different parameters of which an statistic is made to analyse. 

### COCOMO

`Constructive Cost Model` is an algorithmic model to approximate the cost of production of software.

It uses the unit of **Delivered Source Instructions(DSI)**, it starts before the project design and ends with the test by the users.

#### Process 

- Stimate the number of **KDSI** (1000 DSI)
- Stimate complexity: Organic, semidetached or Embeded mode depending on the size of the project.
- Calculate the stimate.

--- 

## Object Oriented Analysis 

It is a method for modeling software projects via `UML` diagramms.

### UML

Stands for Unified Modeling Language. Which is a standard for modeling.

#### UML Types of Diagramms

- **Structure Diagramms:** Objects, Classes, Packages, Components, Composition, Inheritance.
- **Behavior Diagramms:** Use-Case, Activity, State.
- **Interaction Diagramms:** Sequence, Interaction, Time, Communication.

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

Is a set of practices, tools, and a cultural philosophy that automate and integrate the processes between 
software development and IT operations teams.

### Phases and Tools 

- **Plan:** Jira, Common Sense
- **Code:** Git, GitHub, Nvim
- **Build:** Maven, Make, Cargo
- **Test:** Azure. (Quality Assurance, not code tests)  
- **Release:** Jenkins 
- **Deploy:**  Docker, Nix, Kubernetes
- **Operate:** CHEF, Ansible  
- **Monitor:** Grafana, Graylog


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

--- 

# Common Programming Patterns in LeetCode and How to Approach Them

This guide covers major programming patterns frequently used in solving LeetCode problems, including their use cases, examples, and approaches.

---

## 1. Backtracking

**Use Cases:**

* Permutations
* Combinations
* Sudoku Solver
* N-Queens Problem

**Example Problems:**

* [Permutations](https://leetcode.com/problems/permutations/) (LC 46)
* [Combination Sum](https://leetcode.com/problems/combination-sum/) (LC 39)
* [Sudoku Solver](https://leetcode.com/problems/sudoku-solver/) (LC 37)

**Approach:**

1. Use recursion to explore all potential options.
2. Add a base case for stopping the recursion.
3. Use backtracking to undo previous choices.
4. Prune invalid paths early for efficiency.

---

## 2. Two Pointers

**Use Cases:**

* Sorted array problems
* Linked list manipulation
* Opposite-direction searching

**Example Problems:**

* [Two Sum II - Input array is sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/) (LC 167)
* [Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/) (LC 26)

**Approach:**

1. Initialize two pointers at start and end.
2. Move pointers based on the condition.
3. Commonly used for sorted arrays.

---

## 3. Sliding Window

**Use Cases:**

* Subarray problems
* Maximum/minimum in a window
* Longest substring problems

**Example Problems:**

* [Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/) (LC 3)
* [Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/) (LC 209)

**Approach:**

1. Maintain a window using two pointers.
2. Expand/shrink the window based on constraints.
3. Track max/min/required values within the window.

---

## 4. Dynamic Programming (DP)

**Use Cases:**

* Optimization problems
* Overlapping subproblems
* Optimal substructure

**Example Problems:**

* [Climbing Stairs](https://leetcode.com/problems/climbing-stairs/) (LC 70)
* [Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/) (LC 5)
* [Coin Change](https://leetcode.com/problems/coin-change/) (LC 322)

**Approach:**

1. Identify subproblems.
2. Define state variables.
3. Create recurrence relations.
4. Optimize using memoization or tabulation.

---

## 5. BFS & DFS

**Use Cases:**

* Tree and graph traversal
* Path finding
* Connected components

**Example Problems:**

* [Number of Islands](https://leetcode.com/problems/number-of-islands/) (LC 200)
* [Clone Graph](https://leetcode.com/problems/clone-graph/) (LC 133)

**Approach:**

* **DFS:** Recursively or using stack; explore as deep as possible.
* **BFS:** Use queue; explore level by level.

---

## 6. Binary Search

**Use Cases:**

* Searching in sorted arrays
* Monotonic functions
* Finding bounds (first/last occurrence)

**Example Problems:**

* [Binary Search](https://leetcode.com/problems/binary-search/) (LC 704)
* [Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/) (LC 153)

**Approach:**

1. Define low and high bounds.
2. Use mid = low + (high - low) / 2.
3. Adjust bounds based on condition.

---

## 7. Priority Queues

**Use Cases:**

* Task scheduling
* Finding k-largest/smallest elements
* Dijkstra's algorithm

**Example Problems:**

* [Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/) (LC 23)
* [Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/) (LC 347)

**Approach:**

1. Use `heapq` in Python or `PriorityQueue` in Java.
2. Define custom comparator if needed.

---

## 8. Trie

**Use Cases:**

* Prefix search
* Autocomplete
* Dictionary storage

**Example Problems:**

* [Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/) (LC 208)
* [Word Search II](https://leetcode.com/problems/word-search-ii/) (LC 212)

**Approach:**

1. Implement a TrieNode with children and word-end marker.
2. Build Trie for dictionary.
3. Use it for efficient prefix queries.

---

## 9. Greedy

**Use Cases:**

* Interval scheduling
* Resource allocation
* Path optimization

**Example Problems:**

* [Jump Game](https://leetcode.com/problems/jump-game/) (LC 55)
* [Greedy Jump Game II](https://leetcode.com/problems/jump-game-ii/) (LC 45)
* [Activity Selection](https://www.geeksforgeeks.org/greedy-algorithms-set-1-activity-selection-problem/)

**Approach:**

1. Make the locally optimal choice.
2. Prove or validate it leads to a global optimum.
3. Sort if necessary to prioritize selection.

---

## 10. Sorting

**Use Cases:**

* Array transformation
* Counting problems
* Prioritization

**Example Problems:**

* [Merge Intervals](https://leetcode.com/problems/merge-intervals/) (LC 56)
* [Meeting Rooms II](https://leetcode.com/problems/meeting-rooms-ii/) (LC 253)

**Approach:**

1. Choose correct comparator logic.
2. Sort data upfront.
3. Combine sorted results as needed.

---

## 11. Pattern Matching

**Use Cases:**

* String comparison
* Regex-like problems
* Word patterns

**Example Problems:**

* [Word Pattern](https://leetcode.com/problems/word-pattern/) (LC 290)
* [Regular Expression Matching](https://leetcode.com/problems/regular-expression-matching/) (LC 10)

**Approach:**

1. Map between characters and words (for bijection).
2. Use backtracking or DP for regex patterns.

---

## Notes

* These patterns often overlap.
* Combine multiple patterns to solve complex problems.
* Practice recognizing which pattern applies based on constraints and input size.

---

## Continuous Integration (CI)

Continuous Integration (CI) is a software development practice where developers frequently merge their code changes into a shared repository, often multiple times a day. Each merge triggers an automated build and test process to detect integration issues early, ensuring faster feedback and higher software quality.

---

### 🔑 Key Concepts of CI

* **Frequent Commits:** Developers integrate changes into the main branch frequently.
* **Automated Builds:** Code is compiled, packaged, and validated automatically.
* **Automated Testing:** Unit, integration, and regression tests run on every build.
* **Early Feedback:** Failures are detected quickly and resolved faster.
* **Collaboration:** Encourages team-wide ownership of code quality.

---

### ⚙️ Phases of CI

1. **Code Commit**

   * Developers push code changes to a shared version control system (e.g., Git).
   * Trigger for the CI pipeline.

2. **Build Phase**

   * Source code is compiled.
   * Dependencies are downloaded and packaged.
   * Artifacts (executables, libraries, containers) are generated.

3. **Test Phase**

   * Unit tests run first to validate code logic.
   * Integration and regression tests ensure stability.
   * Security and static code analysis can be included.

4. **Feedback & Reporting**

   * Results of builds/tests are shared with the team.
   * Developers receive notifications about failures.

5. **Artifact Management**

   * Successful builds produce deployable artifacts stored in artifact repositories.

6. **Deployment (Optional in CI, mandatory in CD)**

   * Artifacts are deployed to staging/test environments for validation.
   * If extended to **Continuous Deployment (CD)**, production deployment can be automated.

---

### 🎯 Functions of CI

* **Automation of Builds & Tests:** Eliminates manual intervention, reduces errors.
* **Early Bug Detection:** Prevents accumulation of defects by testing frequently.
* **Improved Code Quality:** Enforces coding standards through linting & analysis.
* **Reduced Integration Risk:** Small incremental changes reduce integration conflicts.
* **Faster Delivery:** Streamlined pipelines accelerate release cycles.
* **Collaboration & Transparency:** CI dashboards and logs improve visibility.

---

### 🛠️ Popular CI Tools

#### 1. **Jenkins**

* Open-source automation server.
* Highly customizable with plugins.
* Supports pipelines as code.

#### 2. **GitHub Actions**

* CI/CD built into GitHub repositories.
* Easy YAML-based workflows.
* Strong community integrations.

#### 3. **GitLab CI/CD**

* Integrated with GitLab platform.
* Built-in container registry.
* Supports auto DevOps pipelines.

#### 4. **CircleCI**

* Cloud-native CI/CD platform.
* Optimized for parallelization.
* Strong Docker support.

#### 5. **Travis CI**

* Hosted CI/CD service.
* Simple YAML-based configuration.
* Free for open-source projects.

#### 6. **Azure DevOps Pipelines**

* Microsoft’s CI/CD solution.
* Strong integration with Azure cloud.
* Multi-language and platform support.

---

### 🏗️ Example CI Workflow (Simplified)

```yaml
# Example GitHub Actions CI Workflow
name: CI Pipeline

on: [push, pull_request]

jobs:
  build-and-test:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout Code
        uses: actions/checkout@v3

      - name: Set up Node.js
        uses: actions/setup-node@v3
        with:
          node-version: '18'

      - name: Install Dependencies
        run: npm install

      - name: Run Tests
        run: npm test
```

---

### ✅ Best Practices in CI

* Commit small, frequent changes.
* Keep builds fast and reliable.
* Use version control for pipeline configurations.
* Run tests in parallel to reduce time.
* Fail fast: stop pipelines early when errors occur.
* Monitor pipeline health with dashboards.
* Secure the pipeline (secrets, dependencies, access).

---

### 📌 CI vs. CD

| Aspect         | Continuous Integration (CI) | Continuous Delivery/Deployment (CD) |
| -------------- | --------------------------- | ----------------------------------- |
| Focus          | Automating build & test     | Automating release & deployment     |
| Goal           | Detect integration issues   | Deliver software faster & safer     |
| Deployment     | Not always included         | Always included (staging/prod)      |
| Risk Reduction | Early bug detection         | Minimized release risk              |

---











