# Design Pattern

**Design patterns** are a series of formalized practices tested and verified by developers
for the structure, behaviour and composition of code in the object oriented development.

As a side note, inside this directory only the most relevant design patterns were coded.

--- 

## Creational patterns

They define how objects are created.

--- 

## Behavioral Patterns

How objects interact with each other. 

--- 

## Structural Patterns

How objects are composed either via composition or inheritance.

--- 

## Design Patterns in Object-Oriented Programming (OOP)

### Singleton Pattern

**Definition:**  Ensures a class has only one instance and provides a global point of access to it.

**Common Use Cases:**
- Logging services
- Configuration managers
- Thread pools
- Caches
- Database connection pools

### Factory Method Pattern

**Definition:** Defines an interface for creating an object, but lets subclasses decide which class to instantiate.

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
