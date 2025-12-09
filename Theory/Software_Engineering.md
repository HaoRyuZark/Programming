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

## Common Phrases 

- **KISS:** Keep It Simple Stupid.
- **DRY:** Don't Repeat Yourself.
- **Beware of Premature Optimization:** sometimes the a sulution which is not the most optimal is good enought.
- **Favor Composition over Inheritance:** Use inheritance as less as possible, favor interfaces and composite objects.
- **Source Code Conventions:** Code is more often read than written, attach to the conventions and idioms for readability and idioms.
- **YAGNI:** You Ain't Gonna Need It.

--- 

## Conding Conventions 

Preferred way of writing, documenting, structuring and formating code. 

They are mostly decided by the the team and automated with linter, formatters, etc. 

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


### When is it right to use Agile Planing 


| **Use when** | **Do not use if** |
|-------|---------|
| Fast development of new solution  | Gouverment Projects | 
| Internal projects | Software requires strict planning |
| Both the client and the develpers need to communicate together | Only puntual communication |

--- 

## Software Testing 

Procedure of testing the functionality, resiliancy and behavior of software systems. 

- **Error:** different behavior from the expected one. 
- **Lack:** limitation of the system for a certain situations. 

### Error Propagation

```
  Error -> Error State -> Failure of the system 
```

### Software Quality Assurance 

It is divided into the categories: 

- **Constructive:** whose goal is the reduction of errors via
    - Standards. 
    - Conventions. 
    - Rules.
    - Eucation.

- **Analitical** with the goal of the identification of errors via 
    - Dynamic tests: White-Black-Box Tests, Simulations, prototypes. 
    - Static tests: Reviews and statical analysis. 

#### Main Types of Tests 

- **Static Tests:** tests where the systems is not running, based on the analysis of the code, diagrams, etc. 
- **Dynamic Tests:** the system is running completely or parcially during the test to analyse its behavior via assumptions and validations.

#### Components Test 

A good component is: fast, isolated, testable, reproducible, etc. 

### The AAA-Pattern 

- **Arrange** Prepare the tests and assertions.
- **Act** Perform the tests.
- **Assert** Analyse the results.

## Alpha and Beta Tests 

These are system test for all possible environments. 

They consist of a almost complete version of the final product with goal of tesing a real life 
use case and get feedback from the users to improve the product and fix errors. 

## Cyclic Complexity by McCabe 

This complexity borrowed from the graph theory is given by 

```
v(G) = e - n + 2 
```

with e being the number of edges and n the number of nodes. 

It is commonly used to analyse the complexity of controlflow diagrams.

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

```
                                          ________________________Retrospective_____________________________________________
                                         |                                                                                  |
Product Owner -> Product Backlog -> Sprint Planing -> Sprint Backlog -> Sprint -> Product Increment -> Sprint Review ->  Product Ownwer -> Product                                                        |
                                     \                                                                                   /       
                                                                Daily Scrum
```

### Roles

- **Product Owner:** Responsable for the economic success. He prepares the product backlog, updates it, checks the product increment
and he can not interrupt a sprint.

- **Scrum Master:** He plans the scrum organisation, is not technical, communicates between PO and the development team.

- **Development Team:** It consist of 3 to 9 people and it has to know the comple Know-how for the apllication. The social component is also
very important.

The team consisting of this three roles is independent, there is no "boss" outside, etc. They conver 
all the necessary skills to develop the project.

### Time Boxing 

The duration of a sprint can not change ocnce it was setted.

### Artifacts

- **Product backlog:** List of requirements for the product which changes over time. It also contains planning 
details for the next sprint.

- **Spring backlog:** List of backlog items for the sprint. It contains the goal of the sprint, the task for each member of the team and it is also 
dynamic.

- **Product-increment:** The actual product, update,, etc. It can used an be deployed.

### Events 

- **Sprint:** Sprints are the iterations of the scrum process which consist of the sprint planning, 
the sprint backlog, increment and the sprint review in a time of 2 to 4 weeks. Not dynamically adaptable.

- **Sprint Planning:** Meeting of the whole team to answer the following questions: For what?, What? and How? Max of 2 hours per week. 

- **Daily Scrum:** Meeting of the whole team eventually without the scrum master. It is done for checking communication, what has been done, 
what do we want to accomplish, which obstacles have been encountered. It is basically a daily information exchange.

- **Sprint Review:** Demonstration of the increment. Honest review of what was accomplished and what was not. Team plus stakeholders. 

- **Sprint Retrospective:** Meeting of the developer team without the product owner. Self evaluation of the sprint, 
what was good and what was bad, etc. The goal is that in the next Sprint Backlog the problems will be partially or completely solved. It 
is also a moment to evaluate the tools, practices, etc.

--- 

## Kanban

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

The goal is to have a specific list of requirements for the software product to be deployed and general organization.

### Principles 

- **Cost Orientation:** The cost of each decision has to be stimated. 

- **Stakeholder:** Each stakeholder has an specific role.

- **Mutual Understanding:** Foraml standardized documentation.

- **Context:** Specific area of use.

- **Problem -> Requirement -> Solution:** Are always handled together.

- **Validation:** Progress can be validated via the requirement list.

- **Evolution:** Continuous updates to the requirement list.

- **Innovation** Intention to improve the product.

- **Systematic Work** Standardized methodology of work.

### Work Products

- Documented interim or final result  
- From sketch to contractual specification  
- **Characteristics:** purpose, presentation, scope & lifespan  
- **Presentation:** natural language; template-based; model-based; other forms, e.g., prototype  

#### Typical Work Products

- Individual requirement, e.g., *User Story*, *Software Requirements Specification (SRS)*  
- Set of requirements, e.g., use case, graphical models (e.g., UML), interface description, *Epics*, *Product Backlog*, *Story Map*  

#### Level of Detail

- Depends on the purpose  
- *Note:* A high level of detail is time-consuming & costly  

#### Early Planning & Clarification

- With stakeholders: work products, presentation, levels of detail  

#### Guidelines

- Work product fits the purpose  
- Completeness & appropriate structure  
- No redundancies or inconsistencies  
- Clarity & consistent terminology  
- Versioning & traceability

### Natural Language Workproducts

#### Advantages

- Expressiveness & flexibility  
- Direct; no special tools required  
- Easier for clients or users to understand  

#### Disadvantages

- Ambiguities, omissions, lack of precision, etc.  

#### Recommendations

- Use short and well-structured sentences  
- Define and consistently use a uniform technical vocabulary  
- Avoid vague or ambiguous terms and phrases  
- Be aware of common sources of error, e.g.:
  - Incompleteness  
  - Overuse of nouns  
  - Conditions  
  - Passive formulations  
  - Universal quantifiers  
  - Nominalizations  
- **Guideline:** *SOPHIST rule set*, based on *Neuro-Linguistic Programming (NLP)*

### Template- and Model-Based Work Products

#### Predefined Structures

- **Sentence template:** syntactic sentence structure, e.g., *User Story*  
- **Form template:** specific fields, e.g., *Use Case*  
- **Document template:** structure for a requirements document, e.g., *ISO 29148*  

#### Advantages

- Consistent structure  
- Support in capturing important information  

#### Disadvantages

- Focus on form instead of content  
- Other aspects may be overlooked  

#### Model

- Simplified, abstract representation of reality for specific aspects  
- Often graphical representation  

**Types:**

- Context models  
- Models for structure & data  
- Models for function & process  
- Models for state & behavior  

**Modeling languages:**  

- Use standardized syntax, especially *UML*  

#### Limitations

- Not every relevant piece of information can be expressed  

#### Challenge

- Integrating and maintaining consistency across various models


### Requirements Specification & Functional Specification

#### Requirements Specification (Lastenheft)

- Defined by the **client**
- Contains the complete set of **requirements** for the **deliveries and services** of a contractor within a project  

#### Functional Specification (Pflichtenheft)

- Developed by the **contractor**
- Contains **implementation guidelines** based on the client’s Requirements Specification  

#### Challenges with the Requirements Specification (Lastenheft)

- Describes requirements from the **client’s perspective** in their **domain-specific language**  
- Often created by many different stakeholders, e.g.:
  - Company management  
  - Business departments  
  - IT department  
  - Works or staff council  
  - Data protection officer  
  - Equal opportunity officer  
- “Non-technicians” often struggle to formally specify requirements  
  - Leads to **implicit assumptions**, **gaps**, **ambiguities**, and **contradictions**  
- Includes both:
  - **Functional requirements**
  - **Non-functional requirements**, **constraints**, **acceptance criteria**, etc.  
- Often lacks **clear separation** between these categories

### Prototyping

Prototyping is about creating a simplified version of the end product with some of its capabilities. 
The goal is to create a testable object and once there some form of the end product the requirements can be 
adjusted.

#### Rapid Prototype 

Type of prototyping in which emphasis is placed on developing
prototypes early in the development process to permit early feedback and analysis
in support of the development process.

### Requirement contrats 

- **Identity:** The requirements are identical.

- **Complementarity:** Implementing one requirement leads to (partial) fulfillment of the other requirements.

- **Neutrality:** The implementation of the requirements is independent of each other.

- **Competition:** Both requirements cannot be implemented to the same extent at the same time.

- **Antinomy:** The requirements are mutually exclusive.

### Priorization 

The categories talk by themselves: **must, should, could won't**

### Agile Requirement Engineering 

In this kind of RE the development team is an active participant of the RE team.The most detailed 
specification of comes very late during the development, and instead the team work with requirements 
as possible test cases.

### User Stories 

**User Story:** Simple narrative illustrating the user goals that a software function
will satisfy.

Also, a narrative description of a software requirement, function, feature, or quality
attribute, presented as a narrative of desired user interactions with a software
system.

#### Sentence Template 

```txt
As <Rol> I want <Action>, to <Goal>
```

#### Acceptance Criteria 

After a user story specific criteria can be specified to make the description 
of features more precisse. They are not test case specifications.

```txt
As a customer I want to order a pizza via the mobile app, to be delivered to me

Acceptance criteria:

- The pizza menu has to be displayed 
- The payment possibilities should be presented to the user 
- I need a notification that my order was taken
```

### Invest Criteria 

Criterial for a good user story.

**Independent, Negotiable, Valuable, Estimable, Small, Testable**

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

--- 

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

### Procedural 

This paradigm is based on procedures which can undestood as series of instructions. The poster-boy for this paradigm is `C`

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

**1. Single Responsibility Principle (SRP)**  _“A class should have only one reason to change.”_  
SRP advocates that a class should do one thing and do it well. It should encapsulate only one responsibility or functionality of the software. When a class is responsible for more than one thing, changes to one responsibility can affect the others, increasing the risk of bugs and reducing maintainability.

_Example:_  
A `UserManager` class should only manage user data and not handle user authentication. Authentication should be a separate responsibility handled by an `Authenticator` class.

**2. Open/Closed Principle (OCP)**  _“Software entities (classes, modules, functions, etc.) should be open for extension but closed for modification.”_  
This principle encourages designing systems in a way that allows the addition of new functionality without altering existing code. This is often achieved using abstractions such as interfaces or abstract classes.

_Example:_  
If you have a class that calculates area for shapes, instead of modifying it every time you add a new shape, use a `Shape` interface with an `area()` method and implement it in each shape class (`Circle`, `Rectangle`, etc.).

**3. Liskov Substitution Principle (LSP)**  _“Objects of a superclass should be replaceable with objects of its subclasses without breaking the application.”_  
LSP ensures that derived classes extend the base classes without changing their behavior. Subclasses must adhere to the expectations set by the parent class.

_Example:_  
If `Bird` has a method `fly()`, then a `Penguin` class extending `Bird` violates LSP because penguins can’t fly. In such cases, hierarchy needs to be rethought, possibly introducing a `FlightlessBird` subclass.

**4. Interface Segregation Principle (ISP)**  _“Clients should not be forced to depend upon interfaces they do not use.”_  
This principle promotes creating smaller, more specific interfaces rather than a large, all-encompassing one. It helps avoid forcing classes to implement methods that are not relevant to them.

_Example:_  
Instead of a single `IMachine` interface with `print()`, `scan()`, and `fax()` methods, create separate interfaces like `IPrinter`, `IScanner`, and `IFaxMachine`. This way, a `Printer` class only implements `IPrinter`.

**5. Dependency Inversion Principle (DIP)**  
_“High-level modules should not depend on low-level modules. Both should depend on abstractions.”_  
This principle reduces coupling by ensuring that both high-level and low-level modules depend on interfaces or abstract classes. It also promotes the use of dependency injection to provide concrete implementations.

_Example:_  

A `PaymentProcessor` should not directly instantiate a `StripePaymentService`. Instead, it should depend on an interface `IPaymentService`, and the implementation (`StripePaymentService`) can be injected at runtime.

---

## Design Patterns in Object-Oriented Programming (OOP)

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

**Example:**

```java 

interface Command {
  void execute();
}

public class TurnOff implements Command {
  
  private Bulb receiver;

  public TurnOff(Bulb bulb) {
    this.receiver = bulb;
  }

  void execute() {
    System.out.println("Turning off")
  }
}

public class TurnOn implements Command {
  
  private Bulb receiver;

  public TurnOn(Bulb bulb) {
    this.receiver = bulb;
  }

  void execute() {
    System.out.println("Turning on")
  }
}

public class Bulb {
  public Bulb(){}
}

public class RemoteControl {

  public void submit(Command command) {
    command.execute();
  }

}

public class Main {

  public static void main(String[] args) {
      Bulb bulb = new Bulb();
      
      Command turnOff = new TurnOff(bulb);
      Command turnOn = new TurnOn(bulb);

      RemoteControl remoteControl = new RemoteControl();

      remoteControl.submit(turnOn);
      remoteControl.submit(turnOff);
  }
}
```

### State Pattern

**Definition:**  
Allows an object to alter its behavior when its internal state changes, appearing as if it changed its class.

**Common Use Cases:**
- Finite state machines
- Workflow engines
- Game AI behavior

**Example:**

```java

interface CoffeeMachineState {
  void insertCoin();
  void dispendCoffee();  // These are the transistions
  void selectCoffee();
}

public class DispensingState implements CoffeeMachineState {

  private CoffeeMachine coffeeMachine;
  
  public DispensingState(CoffeeMachine coffeeMachine) {
    this.coffeeMachine = coffeeMachine
  }

  @Override
  public void insertCoin() {
    System.out.println("Sike");
  }

  @Override
  public void dispendCoffee() {
    System.out.println("Coffe dispensed");
    coffeeMachine.setState(coffeeMachine.getIdleState());
  }

  @Override
  public void selectCoffee() {
    System.out.println("Sike");
  }
}

public class SelectingState implements CoffeeMachineState {

  private CoffeeMachine coffeeMachine;
  
  public SelectingState(CoffeeMachine coffeeMachine) {
    this.coffeeMachine = coffeeMachine
  }
 
  @Override
  public void insertCoin() {
    System.out.println("Sike");
  }

  @Override
  public void dispendCoffee() {
    System.out.println("Sike");
  }

  @Override
  public void selectCoffee() {
    System.out.println("Coffee selected");
    coffeeMachine.setState(coffeeMachine.getDispensingState());
  }

}

public class IdleState implements CoffeeMachineState {

  private CoffeeMachine coffeeMachine;
  
  public IdleState(CoffeeMachine coffeeMachine) {
    this.coffeeMachine = coffeeMachine
  }
 
  @Override
  public void insertCoin() {
    System.out.println("Coin inserted");
    coffeeMachine.setState(coffeeMachine.getSelectingState());
  }

  @Override
  public void dispendCoffee() {
    System.out.println("Sike");
  }

  @Override
  public void selectCoffee() {
    System.out.println("Sike");
  }
}
public class CoffeeMachine {
 
  private CoffeeMachineState idleState;
  private CoffeeMachineState selectingState;
  private CoffeeMachineState dispensingState;

  private CoffeeMachineState current;
  
  public CoffeeMachine() {
    
    idleState = new IdleState(this);
    selectingState = new SelectingState(this);
    dispensingState = new DispensingState(this);
   
    current = this.idleState;
  }

  public void setState(CoffeeMachineState state) {
    current = state;
  }

  public void insertCoin() {
    state.insertCoin();
  }

  public void selectCoffee() {
    state.selectCoffee();
  }

  public void dispendCoffee() {
    state.dispendCoffee();
  }

}

```
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


**Example**

```java 

public class Memento {

  private String state;

  public Memento(String state) {
    this.state = state;
  }

  public String getState() {
    return this.state;
  }
}


public class Caretaker {

  private ArrayList<Memento> mementi;

  public Caretaker() {
    this.mementi = new ArrayList<>();
  }
  
  public void addMemento(Memento m) {
    this.mementi.add(m);
  }

  public Memento getMemento(int index) {
    return this.mementi.get(index);
  }
}

public class TextEditor {

  private StringBuilder text;
  
  public TextEditor() {
    this.text = new StringBuilder();
  }

  public void append(String text) {
    text.append(text);
  }

  public String getContent() {
    return this.text.toString();
  }

  public Memento save() {
    return new Memento(text.toString());
  }

  public void restore(Memento memento) {
    text = new StringBuilder(memento.getState());
  }
}

public class Main {

  public state void main(String[] args) {

    TextEditor textEditor = new TextEditor();
    Caretaker caretaker = new Caretaker();

    textEditor.append("Hello");
    caretaker.addMemento(textEditor.sava());

    textEditor.append("World");
    caretaker.addMemento(textEditor.sava());

    textEditor.restore(caretaker.getMemento(0));
    
    textEditor.restore(caretaker.getMemento(1));
  }
}
```
--- 

## Common Programming Patterns in LeetCode and How to Approach Them

This guide covers major programming patterns frequently used in solving LeetCode problems, including their use cases, examples, and approaches.

### Backtracking

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

### Two Pointers

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

### Sliding Window

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

### Dynamic Programming (DP)

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

### BFS & DFS

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

### Binary Search

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

### Priority Queues

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

### Trie

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

### Greedy

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


### Sorting

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

### Pattern Matching

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

## Continuous Integration (CI)

Continuous Integration (CI) is a software development practice where developers frequently merge their code changes into a shared repository, often multiple times a day. Each merge triggers an automated build and test process to detect integration issues early, ensuring faster feedback and 
higher software quality. 

Goals:

- **Feature Driven Development**
- **Automatic Tests** 
- **Availability of demo and test-systems**
- **Increase of software quality**


### Principles 

- **Shared Code Base:** Maintained via a version-control-system.

- **Automatic translation:** Standardized definition of tests, static checks by each integration.

- **Automatic Distribution and Mirrors:** Division of distributions in DEV, TEST and PROD. Changes are tested 
in the production environment.

- **Frequent Integration:** Reduces the number of errors in the code-base. (Trunk-Based-Development).

- **Continuous Test Development:** For each change in the code, documentation and anaylsis there is a test or check.

- **Documentation:** Makes it easier for anybody to understand the procduct.

### Key Concepts of CI

* **Frequent Commits:** Developers integrate changes into the main branch frequently.
* **Automated Builds:** Code is compiled, packaged, and validated automatically.
* **Automated Testing:** Unit, integration, and regression tests run on every build.
* **Early Feedback:** Failures are detected quickly and resolved faster.
* **Collaboration:** Encourages team-wide ownership of code quality.


### Phases of CI

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


### Functions of CI

* **Automation of Builds & Tests:** Eliminates manual intervention, reduces errors.
* **Early Bug Detection:** Prevents accumulation of defects by testing frequently.
* **Improved Code Quality:** Enforces coding standards through linting & analysis.
* **Reduced Integration Risk:** Small incremental changes reduce integration conflicts.
* **Faster Delivery:** Streamlined pipelines accelerate release cycles.
* **Collaboration & Transparency:** CI dashboards and logs improve visibility.


### DevOps

Is a set of practices, tools, and a cultural philosophy that automate and integrate the processes between 
software development and IT operations teams.

#### Phases and Tools 

- **Plan:** Jira, Common Sense
- **Code:** Git, GitHub, Nvim
- **Build:** Maven, Make, Cargo
- **Test:** Azure. (Quality Assurance, not code tests)  
- **Release:** Jenkins 
- **Deploy:**  Docker, Nix, Kubernetes
- **Operate:** CHEF, Ansible  
- **Monitor:** Grafana, Graylog

### Popular CI Tools

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


### Example CI Workflow (Simplified)

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

### Best Practices in CI

* Commit small, frequent changes.
* Keep builds fast and reliable.
* Use version control for pipeline configurations.
* Run tests in parallel to reduce time.
* Fail fast: stop pipelines early when errors occur.
* Monitor pipeline health with dashboards.
* Secure the pipeline (secrets, dependencies, access).

### CI vs. CD


| Aspect         | Continuous Integration (CI) | Continuous Delivery/Deployment (CD) |
| -------------- | --------------------------- | ----------------------------------- |
| Focus          | Automating build & test     | Automating release & deployment     |
| Goal           | Detect integration issues   | Deliver software faster & safer     |
| Deployment     | Not always included         | Always included (staging/prod)      |
| Risk Reduction | Early bug detection         | Minimized release risk              |


---

## Version Control 

Version control refers to the process of keeping track of each change in a code base via a version control system.
This is accomplished by saving checkpoints for each change and creating different development branches for different versions 
of the system.

### Central VC

The code base is stored in one computer and each develper access the server to edit the code. 
Example: Concurrent Versions System.

### Distributed VC 

Each developer acts a as code base. This means that it is not necessary to have one central unit, where every request is handled, instead 
developer can get specific versions of the code from one another. Example Git.

### Branching 

Branching refers to the process of creating new development branches for different features or versions. There is 
also a main branch which works as the reference point for the base of multiple products or as the main version 
of a software.

### Traceability

Degree to which a relationship can be established between to or more products of the development process, especially products 
having a predecessor-successor or master-subordinate realtionship to one another.

- **Pre-Requirements:** Where do the requirements come from? Who was responsible? Which stakeholder? 

- **Post-Requirements:** Which new requirements do we have? 

### Reasons for VC 

- **Impact Analysis:** Effects of the changes. 

- **Requirements Coverage Analysis:** Which requirements has been covered. 

- **Test Coverage:** How much has been tested. 

- **Reusability**

- **Debugging**

--- 

## Model Control View Architecture

The **Model Control View Architecture** defines the structural and functional design that enables interaction between the user interface, control logic, and underlying model management system. It is organized into modular layers that ensure scalability, maintainability, and real-time responsiveness.

### 1. Architectural Overview

The architecture follows a **three-tier structure**:

1. **Presentation Layer (UI)**
   Provides the graphical interface through which users interact with the system.

   * Displays model status, configuration panels, and performance metrics.
   * Supports interactive controls for parameter tuning and monitoring.
   * Implements real-time updates using WebSocket or streaming APIs.

2. **Control Layer (Logic and Orchestration)**
   Acts as the intermediary between the UI and backend model services.

   * Handles user commands, input validation, and state synchronization. In other words it handles the reques flow.
   * Maintains session context and ensures consistent model configurations.
   * Implements event-driven communication for responsiveness and low latency.

3. **Data and Model Layer (Backend Services)**
   Manages the actual models, data pipelines, and configuration storage.

   * Provides APIs for model inference, parameter updates, and telemetry data.
   * Utilizes caching and database systems for fast retrieval and persistence.
   * Integrates with deployment infrastructure for distributed model execution.

### 2. Core Components

* **Model Controller**
  Coordinates communication between the user interface and model APIs. Responsible for applying updates to model parameters and retrieving system metrics.

* **Configuration Manager**
  Handles persistence and versioning of model settings. Enables loading, saving, and restoring of configuration profiles.

* **Telemetry Engine**
  Collects and streams performance data such as latency, throughput, and token utilization. Supports visualization in the UI dashboard.

* **Access Gateway**
  Enforces security and role-based permissions for users interacting with model controls.

### 3. Data Flow

1. The user issues a control command (e.g., parameter change) through the interface.
2. The Control Layer validates the request and dispatches it to the Model Controller.
3. The Model Controller updates the backend model configuration and logs the event.
4. Updated performance and configuration data are streamed back to the UI for visualization.

### 4. Design Principles

* **Modularity** – Each component functions independently for ease of maintenance.
* **Real-Time Feedback** – Low-latency event propagation ensures responsive control.
* **Security and Traceability** – All operations are authenticated and logged.
* **Scalability** – Supports multiple concurrent users and models across distributed systems.

--- 

## Object-Relational Mapping (ORM) Architecture

The **Object-Relational Mapping (ORM) Architecture** provides a structured mechanism for bridging the gap between **object-oriented programming models** and 
**relational database systems**. It allows developers to manipulate database entities using native programming language constructs, abstracting away the 
complexities of SQL queries and database schemas.

### 1. Architectural Overview

The ORM architecture is typically divided into **four main layers**, each responsible for a specific aspect of data interaction:

1. **Domain Model Layer**
   Represents business entities as objects (classes) within the application.

   * Encapsulates business logic, relationships, and data validation.
   * Each class corresponds to a database table, and each object instance maps to a table row.

2. **Mapping Layer**
   Defines the correspondence between object attributes and database columns.

   * Uses metadata (annotations, XML, or configuration files) to describe how objects relate to tables.
   * Handles inheritance, relationships (one-to-one, one-to-many, many-to-many), and type conversions.

3. **Persistence Layer**
   Manages the translation of object operations into SQL commands.

   * Automates CRUD (Create, Read, Update, Delete) operations.
   * Optimizes query generation and manages transactions and caching.
   * Ensures synchronization between in-memory objects and persistent data.

4. **Database Layer**
   Represents the underlying relational database management system (RDBMS).

   * Stores and retrieves data based on SQL commands issued by the persistence layer.
   * Maintains integrity constraints, indexing, and query optimization.

### 2. Core Components

* **Entity Manager / Session**
  Acts as the interface for creating, reading, updating, and deleting entities. Manages the lifecycle of persistent objects and their database representations.

* **DAO** 
  Data Access Objects are the classes used for exposing an API for interacting with the different entities inside out database. 

* **Query Builder / ORM Query Language**
  Provides an abstraction over SQL to allow developers to define queries using object-oriented syntax (e.g., JPQL, HQL, or LINQ).

* **Transaction Manager**
  Ensures atomic and consistent database operations, supporting rollback and commit mechanisms.

* **Caching Layer**
  Improves performance by reducing redundant database queries through first-level (session) and second-level (shared) caching.

### 3. Data Flow

1. The application interacts with domain objects rather than writing SQL directly.
2. The ORM framework translates these object operations into appropriate SQL statements.
3. The persistence layer executes these statements on the database.
4. Results are mapped back into objects and returned to the application for further processing.

### 4. Design Principles

* **Abstraction** – Isolates database details from application logic.
* **Consistency** – Ensures object states remain synchronized with database records.
* **Portability** – Enables easy migration across different database systems.
* **Maintainability** – Reduces boilerplate code, improving readability and long-term maintainability.
* **Performance Optimization** – Leverages lazy loading, caching, and query optimization techniques.

The **Object-Relational Mapping Architecture** streamlines database interactions, allowing developers to focus on business logic rather than SQL syntax. It serves as a crucial architectural component in modern applications that require seamless integration between object-oriented design and relational data storage.

--- 

## Software Architecture 

Is the way of describing a solution concept for functional and non-functional requirements. 

It accomplishes the following goals: 

- Concrete high level descriptions of a complex system 
- Abstraction
- Organization of resources 
- Gives context 
- Orientates the planing 

### Components and End-Points 

- **Components** are individual entities like programs, entire systems or a comglomerate of those. 
- **End-Points (API)** are the exposed abtracted functionality of the components. 
--- 

## OOA 

Stands for object oriented analysis. Procedure of analysing a problem and modeling it in terms of classes and objects and finally implementing 
their relations in those terms or functions, methods, etc.

--- 

## OOD

Stands for object oriented desing. Procedure of implementing, improving and refining the resutls of the OOA and also applying 
the concept of objects to rest of the development and architectural decisions. 

--- 

## Patterns in Software Engineering 

There are mainly three types of patterns:

- **Architectural Patterns:** Ways of defining a system composed of components and API's 

- **Desing Patterns:** Ways of desining the internals of a system based on the programming paradigma and the relations of the different entities. 

- **Idioms:** Language specific conventions and preferred ways of writing code. It also inlcudes best practices.

--- 

## The Layer Architecture 

Separates each part of the system into independent layers or domains. It can be hard to implement due to the borders between layers being 
highly subsjective. But it can also be very easy to understand.

--- 

## Technical Debt 

It is a metaphore for the drawbacks of desing or technical choices which if not handled correctly can lead to unmaintainable 
software and other serious problems.

--- 

