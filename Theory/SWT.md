# Software Engineering

Software engineering is the practical use of scientific methods
for the economic development of software its use and maintenance.

## Goals SWE

- Quality software
- Reduction of errors
- Reduction of work
- Maximize clients

## Life cycle of software

1. Analysis of requirements
2. Design and Architecture
3. Implementation and unit testing
4. Integration and Integration testing
5. Deploymend and Acceptance testing
6. Operation Maintenance
7. Retirement

## Stakeholder 

Term for the individuals inside the software project: developers, investors, poduct owner, architect, etc.

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


## Discovery of Errors 


| **Error made** | **Error detected** |
|-------------|----------------|
| User needs| Operation and Maintenance|
|Requirements Analysis | Deployment and Acceptance Testing |
|Desing | Integration Testing |
|Implementation | Unit Testing |
|Code input | IDE and Compiler |


## Cost of Errors


| **Phase of Error Detection**       | **Cost Factor** |
| ---------------------------------- | :---------------:|
| Requirements Analysis              | 1               |
| Design                             | 3 – 6           |
| Implementation                     | 10              |
| Unit Testing & Integration Testing | 15 – 40         |
| Deployment & Acceptance Testing    | 30 – 70         |
| Operation & Maintenance            | 40 – 1,000      |


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


## Iterative Development

This model allows developers to plan multiple iterations of the steps: Analysis, Proposal, Implementation and Testing.
Each iteration is a mini-waterfall model. This allows for more flexibility and adaptability to changing requirements
and feedback from users. It is often used in Agile methodologies.

The problems with the waterfall model are that it is too rigid and does not allow for changes once the development process has started.

## Incremental Development

In this model, the software is developed in small increments or modules. Each increment adds new functionality to the software.
This allows for faster delivery of software and the ability to get feedback from users early in the development process.
It is often used in Agile methodologies as well.

The disadvantage of this model is that it can lead to integration issues if the increments are not well planned and designed. Also,
sometimes the first proposals are not well-thought-out and lead to problems later on in the development process.

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

## Requirements Engineering

Is the process of defining how a software product is going to be, work, what it needs, etc. There are functional requirements which are very specific
and non-functional which are like 'nice-to-haves'

## Kano Model

For the categorization of requirements. It consists of two axises, one for the happiness and one for the amount of features. There are three 
ploted lines the **base**, **performance** and **excell** features.

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

## Object Oriented Analysis 

It is a method for modeling software projects via `UML` diagramms.

### UML

Stands for Unified Modeling Language. Which is a standard for modeling.

#### UML Types of Diagramms

- **Structure Diagramms:** Objects, Classes, Packages, Components, Composition, Inheritance.
- **Behavior Diagramms:** Use-Case, Activity, State.
- **Interaction Diagramms:** Sequence, Interaction, Time, Communication.








