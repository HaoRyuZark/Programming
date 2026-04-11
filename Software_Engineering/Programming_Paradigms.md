# Programming Paradigms

## Imperative vs. Declarative

-   **Imperative**: Specifies _how_ to perform tasks step-by-step (e.g., for loops).
-   **Declarative**: Focuses on _what_ the outcome should be, leaving the "how" to the underlying system (e.g., SQL, React).

--- 

## Procedural 

This paradigm is based on procedures which can undestood as series of instructions. The poster-boy for this paradigm is `C`

--- 

## Object-Oriented Programming (OOP)

A paradigm based on objects that encapsulate data and behavior. Key principles include inheritance, polymorphism, encapsulation, and abstraction.

### Pilars of OOP

- **Abstraction**: Complex logic should be abtracted away into methods or functions related to one class or object. Example: we use 
a class DatabaseService, which has functions to update, delete and retrive data, but we do not know how it that exaclty done, we just use 
its provided functionalities via functions calls.

- **Encapsulation**: Data and methods who belong together, are together in the same class. Example: a car with all of its 
attributes and methods in the class Car.

- **Inheritance**: The idea that from one class we can derive similar classes who share bhaviours.

- **Polymorphism:** Different behavior for the same function depending on the types passed to it.

### Composition, Aggregation & Association

- **Aggregation**: One object contains another, but they are independent. The contained object can exists without the conatiner object.

- **Composition**: Stricter form of the aggragation in which the child object can not live without the parent. 

- **Association**: Relationship where one object is linto another, but wihout ownership in both ways.

--- 

## Functional Programming (FP)

A declarative paradigm where computation is done through pure functions and immutability. FP avoids side effects and favors composability and higher-order functions.

### Domain Driven Development 

A domain refers to an area of action or concerns inside the application context. Due to its emphazis as the domains and subdomains as 
components with inputs and outputs it can be heavily related to functional modelling.

Domains should be independent and only communicate with the necessary domains as less a possible to avoid corruption of domains. Domains 
only share information if their relation is critical, else they are isolated from each others.

We also define our actions and interactions in and between domains.

Note, that DDD is best suited for large scale projects with complex architectures and multiple components.

#### Repositories and Services 

- **Repositories**: They perform operations at the persistence level of your application like updating the attributes of an entitiy. In simple terms, data access.

- **Services**: Services contain bussines logic, which means that they perform operations on the domain. It can be seen high-level operations while
repositories handle the data access.

--- 

## Logical Programming (LP)

A declarative paradigm where computation is done through first setting the rules of our small universe and then the interpreter 
takes decision based on the rules we have declared.

--- 

