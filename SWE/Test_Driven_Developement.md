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

### Given-When-Then Naming Convention

A part variant of the Test-Driven Development approach is the Behavior-Driven Development.
This methodology uses the Given-When-Then format to describe tests such that it tells the expected behavior of the system in a human-readable way.

- **Given**: The initial context or state.
- **When**: The action or event that occurs.
- **Then**: The expected outcome or result.

--- 

