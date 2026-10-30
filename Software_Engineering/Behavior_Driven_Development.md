# Behavior Driven Development 

In contrast to classic TDD, but instead of thinking about the inner working of the software for test, we declare what we 
want the software to do; which **behavior** is expected. 

To accomplish this goal, we use user stories, and high level tests which then are  used by the developers to implement a test accordingly. If the test is not implemented then via a management engine for the project we can check what 
has been implemented and what not.

--- 

## Domain Specific Language (DSL)

The **domain specific language** also known as **ubiquitous language** is a language which is used to describe the domain of the application. It is used to describe the behavior of the system in a 
human-readable way. Its has the purpose of being as interpretation free as possible, so that the requirements, when presented and implemented 
are understood by everyone in the project.

--- 

## Phases 

- **Definition of Behaviors**: Define what the application should accomplish. This achived in different formats, but more commonly user stories.

- **Defintion of Acceptance Criteria**: Enhance the user stories by adding acceptance criteria for each of them.

- **Write Tests**: Implement the tests for the different aspects of the behavior. Or just define the different scenarios in plain language.

- **Implementation**: Implement the actual code to be tested. It is also possible to do the implementation before coding the tests, but 
only if the testing scenarios are already defined.

## Given-When-Then Naming Convention

A part variant of the Test-Driven Development approach is the Behavior-Driven Development.
This methodology uses the Given-When-Then format to describe tests such that it tells the expected behavior of the system in a human-readable way.

- **Given**: The initial context or state.
- **When**: The action or event that occurs.
- **Then**: The expected outcome or result.

Due to its nature it compatible with TDD.

--- 

## User Stories 

**User Story:** Simple narrative illustrating the user goals that a software function will satisfy.

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

--- 
