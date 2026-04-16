# Test Driven Development (TDD)

A practice where tests are written before the code. The cycle follows:

1. **Red**: Write a failing test (Make it Red).
2. **Green**: Write the minimum code to pass the test (Make it Green).
3. **Blue**: Improve the code while ensuring the test still passes (Make it Blue).

## Advantages and Disadvantages 


| **Advantages**                                       | **Disadvantages**                                                              |
| ---------------------------------------------------- | ------------------------------------------------------------------------------ |
| Very specific                                  | Only functional requirements                                               |
| Continuous Integration                                        | Not a complete specification   |
| Concrete definition of Done                                          | Can become tedious            |
| Specific way of meassuring the progress                |  For stakeholders very complex    |


## Software Testing 

Procedure of testing the functionality, resiliancy and behavior of software systems. 

--- 

## How to Stop Bugs

To write (almost) bugfree code we need to:

- **Modular Code**: The code is divided into functions or objects which do exactly one thing, and do not have circular dependence. Although, they 
can work together. 

- **Write Unit and Integration Tests**: We ensure that we cover all possible 

--- 

## Difference Between Error and Limitation

- **Error:** different behavior from the expected one. 
- **Limitation:** limitation of the system for a certain situations. 

--- 

## Error Propagation Model

```
  Error -> Error State -> Failure of the system 
            (Defect)       (Failure)
```

--- 

## Software Quality Assurance 

It is divided into the categories: 

- **Constructive:** whose goal is the reduction of errors via
    - Standards. 
    - Conventions. 
    - Rules.
    - Education.

- **Analitical**: with the goal of the identification of errors via 
    - Dynamic tests: White-Black-Box Tests, Simulations, prototypes. 
    - Static tests: Reviews and statical analysis. 


For the prevention of errors contructives approa

### Main Types of Tests 

- **Static Tests:** tests where the systems is not running, based on the analysis of the code, diagrams, etc. 
- **Dynamic Tests:** the system is running completely or parcially during the test to analyse its behavior via assumptions and validations.

### Components Test 

A good component is: fast, isolated, testable, reproducible, etc. 

### The AAA-Pattern 

- **Arrange** Prepare the tests and assertions.
- **Act** Perform the tests.
- **Assert** Analyse the results.

### Alpha and Beta Tests 

These are system test for all possible environments. 

They consist of a almost complete version of the final product with goal of tesing a real life 
use case and get feedback from the users to improve the product and fix errors. 

- **Alpha Test**: system gets tested by users or an independent team in an enviroment provided by the developers.
- **Beta Test**: the same as alpha test but this time in the environment of the customer.

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

## Static Tests

**Static tests** are tests in which the system is not running either partially or completely.  They are done 
mostly via:

- Code review 
- Compliance analysis with the plan or requierements list 
- Test specifications 
- Coding conventions 
- Controll-flow analysis

--- 

## Black-Box Testing 

Tests in which the source code is not known. Mostly unit, integration and system tests.

## White-Box Testing 

Tests in which the source code is visible. Its mostly used for testing the code-coverage, analyzing the code and 
check for code smells, etc. Can be done with a debugger, but it can also be done staticaly.

The goal is to analyze the code carefully, find parameters, edge-cases, all paths of executions if possible and test all 
of them.
 
### Control-flow Analysis

This is a testing method in which the flow of the program is modelled as a graph emulating an 
activity diagram. The goal is to get a clear view of the control flow of the program to identify errors in a 
visual way. This helps reducing the cognitive charge when analyzing code and at the same time allows for the discovery of edge 
cases.

#### Types of Tests in Control-flow Analysis

- **Statement Testing**: determine testcases such that each statement is executed at least one time. It can be problematic under certain 
criteria becuase it does not care about the data flow i.e. if the test makes sense, but only the coverage.

- **Branch Testing**: determine testcases such all possible branches of excution are included. Necessary for if-statements.

--- 

## Dynamic Tests 

Tests in which the system is partially or entirely running.

### Vocuabulary 

- **System under Test (SUT)**: Part of system beign tested.
- **Point of Observation**: Parameters.
- **Point of Control**: View of the results.

### Types of Dynamic Tests

- **Unit Testing**: Tests individual components (usually functions or classes) in isolation. Fast and localized, it's the foundation of a reliable 
test suite.

- **Integration Testing**: Verifies that multiple components work together as expected. For example, testing interactions between a database and an 
API layer.

- **End-to-End (E2E) Testing**: Simulates real user scenarios through the full stack, testing the system from start to finish. Useful for detecting 
issues in user flows.

- **Smoke Testing**: A basic test suite run to check whether the major functions of an application work after a build or deployment. Often localized 
“build verification tests.”

- **Regression Testing**: Ensures that recent changes haven’t broken existing functionality. It helps prevent reintroducing old bugs.

- **Acceptance Testing**: Tests whether the system meets business requirements. Often done by QA or stakeholders using user stories or criteria.

- **System Testing**: E2E is a form of this testing, but in general it refers to tests dedicated to check if all of the requirements were fullfield.

---

## Behavior Driven Development 

In contrast to classic TDD, but instead of thinking about the inner working of the software for test, we declare what we 
want the software to do; which **behavior** is expected. To accomplish this goal, we use user stories, and high level tests which then are 
used by the developers to implement a test accordingly. If the test is not implemented then via a management engine for the project we can check what 
has been implemented and what not.

### Phases 

- **Definition of Behaviors**: Define what the application should accomplish. This achived in different formats, but more commonly user stories.

- **Defintion of Acceptance Criteria**: Enhance the user stories by adding acceptance criteria for each of them.

- **Write Tests**: Implement the tests for the different aspects of the behavior. Or just define the different scenarios in plain language.

- **Implementation**: Implement the actual code to be tested. It is also possible to do the implementation before coding the tests, but 
only if the testing scenarios are already defined.

### Given-When-Then Naming Convention

A part variant of the Test-Driven Development approach is the Behavior-Driven Development.
This methodology uses the Given-When-Then format to describe tests such that it tells the expected behavior of the system in a human-readable way.

- **Given**: The initial context or state.
- **When**: The action or event that occurs.
- **Then**: The expected outcome or result.

Due to its nature it compatible with TDD.

### User Stories 

**User Story:** Simple narrative illustrating the user goals that a software function will satisfy.

Also, a narrative description of a software requirement, function, feature, or quality
attribute, presented as a narrative of desired user interactions with a software
system.

#### Sentence Template 

```txt
As <Rol> I want <Action>, to <Goal>
```

##### Acceptance Criteria 

After a user story specific criteria can be specified to make the description 
of features more precisse. They are not test case specifications.

```txt
As a customer I want to order a pizza via the mobile app, to be delivered to me

Acceptance criteria:

- The pizza menu has to be displayed 
- The payment possibilities should be presented to the user 
- I need a notification that my order was taken
```

### INVEST Criteria 

Criteria for a good user story.

- **Independent**: The stroy should not be dependent on another user story. Relevant for the implementation case 
in which a feature should not depend on another feature which is going to be implemented in the same sprint.

- **Negotiable**: It prompts but does not describe a solution, that is the work of the developer in charge. This takes 
away the complicated details and makes the story understandable for everyone. This also means that it can be changed in 
the future.

- **Valuable**: The story should represent a small but relevant increment (feature).

- **Estimable**: It should be possible to estimate the amount of work necesary for the implementation of the described functionality.

- **Small**: Each user story is possible to implement in only 1 sprint.

- **Testable**: The fulfillment of the user story is possible to test.


