# Software Engineering

**Software engineering** is the practical use of scientific methods
for the economic development of software its use and maintenance.

--- 

## Goals of Software Engineering

- **Quality software**
- **Reduction of errors**
- **Reduction of work in time**
- **Reduction of the cognitive charge**
- **Maximize clients**

--- 

## Stakeholder 

Term for the individuals inside the software project: developers, 
investors, product owner, architect, etc.

--- 

## Software Quality 

Capability of sofware product to satisfy steated and implied needs when used under especified 
conditions.

- **Functional Suitability**: The software performs its tasks correctly. It is the right tool for the job.

- **Performance Efficiency**: It can complete the tasks in an acceptable amount or time.

- **Compatibily**: The system can share information with other systems via Standardized formats, share resources, etc.

- **Interaction Capability**: It is user-friendly. A user should not have internal knowledge about the code to use the software appropietly.

- **Reliability**: Critical functionality can be performed in an specific time frame without interruption or unexprected errors.

- **Security**: The system is resiliant to attackers wanting to steal valuable data.

- **Mantainability**: The system can be extended without major complications (good design).

- **Flexibility**: The system can be addapted for new requirements, use-case or infrastructure.

- **Safety**: The software should not put: health, life, property or the enviroment in danger.

--- 

## Conding Conventions 

Preferred way of writing, documenting, structuring and formating code. 
They are mostly decided by the the team and automated with linter, formatters, etc. 

--- 

## Life cycle of software

1. **Analysis of requirements**

2. **Design and Architecture**

3. **Implementation and unit testing**

4. **Integration and Integration testing**

5. **Deployment and Acceptance testing**

6. **Operation & Maintenance**

7. **Retirement**

--- 

## When To Produce New Software

The goal is to minimize the cost of the use of software. The decision is 
**make or buy**

- **Commercial-off-the-Shelf**: With customization for specific customers, and mostly in the form of Software as service.
- **Total Cost of Ownership**: Return of Investment, Costs of the different phases.

### Balance of using already existing software 


| **Advantages**                                         | **Disadvantages**                                                     |
| ------------------------------------------------------ | --------------------------------------------------------------------- |
|  Faster deployment                                    |  Dependence on the vendor: maintenance, further development, support |
|  Quality improvement through many users               |  Costs of custom software are often underestimated                   |
|  Development costs are borne by a large customer base |  Custom adaptations are rarely possible                              |
|  Higher planning reliability                          |  Further development must be coordinated with many stakeholders      |
|  Total Cost of Ownership (TCO) is generally lower     |  No unique selling point in competition                              |
|                                                        |  Lock-in effect                                                      |


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

## Waterfall Model

This model takes the steps of the life cycle and orders them
into descending order as the way software is planed, developed, used and
maintained. It has been criticized for not being realistic.

- **Requirements Analysis**
- **Desing**
- **Implementation and Unit Testing**
- **Integration and Integration Testing**
- **Deployment and Acceptance Testing**
- **Operation and Maintenance**


| **Advantages**                                       | **Disadvantages**                                                              |
| ---------------------------------------------------- | ------------------------------------------------------------------------------ |
|  Simple & intuitive                                 |  Requires a structured approach                                               |
|  Widely used                                        |  Clients are only involved at the beginning, requirements are often unclear   |
|  Documents                                          |  Testing & acceptance occur late, only after the system is complete           |
|  Written specification documentation                |  Continuous quality assurance is problematic                                  |
|  Contract for handover to next phase                |  "Activity" and "phase" are not clearly separated                             |
|  Easy to monitor as quasi-milestones in the project |  Project management: cycles are problematic, no milestones between activities |
|  Transparent process flow                           |                                                                                |


The problems with the waterfall model are that it is too rigid and does not allow for changes once the development process has started.

--- 

## V-Model

The V-Model is an extension of the waterfall model. It emphasizes the importance of testing at each stage of development. The left side of the V
represents the stages of development, while the right side represents the stages of testing. The bottom of the V represents the implementation stage.


| **Left Side of V**        |  **Middle of V**   | **Right Side of V**     |
| :-------------------- | :------------: | ------------------- |
| Requirements Analysis |       <-       | Acceptance Testing  |
| System Design         |       <-       | System Testing      |
| Architecture Design   |       <-       | Integration Testing |
| Specification Design  |       <-       | Unit Testing        |
|                       | Implementation |                     |


Tends to be really tedious and complex. Mostly used for gouverment projects. 

--- 

## Incremental Development

In this model, the software is developed in small increments or modules. Each increment adds new functionality to the software.
This allows for faster delivery of software and the ability to get feedback from users early in the development process.
It is often used in Agile methodologies as well. In contrast to the iterative development, the final shape of the end-product is clearly defined, and 
during each eincrement a part of this vision is implemented.

The disadvantage of this model is that it can lead to integration issues if the increments are not well planned and designed. Also,
sometimes the first proposals are not well-thought-out and lead to problems later on in the development process.

--- 

## Iterative Development

This model allows developers to plan multiple iterations of the steps: Analysis, Proposal, Implementation and Testing.
Each iteration is a mini-waterfall model. This allows for more flexibility and adaptability to changing requirements
and feedback from users. It is often used in Agile methodologies.

In contrast to the increnental development, the iterations do not traslate directly into new functionalities, just additions.

Note that the defintion of done may change after iterations.

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

## Scalability

**Scalability** refers to the capacity of a system to maintain functionality, maintainability and const while growing in size.
Systems when growing can be expanded into ways: 

- **Horizontal**: which refers to the maximization of the resources of the CPU by parallelism, threading, machine code optimization, etc.
This can become really complex and become complex to maintain, but reduces costs.

- **Vertical**: refers to expansion of hardware and resources. On the one side, new hardware can be expensive and also be detrimental to a system if not handled properly, on the 
other side, thsis is sometimes easier than complex machine code optimization.

--- 
