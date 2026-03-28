# Requirements Engineering

Is the process of defining how a software product is going to be, work, what it needs, etc. There are **functional requirements** which are very specific
and **non-functional** which are like 'nice-to-haves'

The goal is to have a specific list of requirements for the software product to be deployed and general organization.

--- 

## Principles 

- **Cost Orientation:** The cost of each decision has to be stimated. 

- **Stakeholder:** Each stakeholder has an specific role.

- **Mutual Understanding:** Formal standardized documentation.

- **Context:** Specific area of use.

- **Problem -> Requirement -> Solution:** Are always handled together.

- **Validation:** Progress can be validated via the requirement list.

- **Evolution:** Continuous updates to the requirement list.

- **Innovation** Intention to improve the product.

- **Systematic Work** Standardized methodology of work.

--- 

## Work Products

- Documented interim or final result  
- From sketch to contractual specification  
- **Characteristics:** purpose, presentation, scope & lifespan  
- **Presentation:** natural language; template-based; model-based; other forms, e.g., prototype  

### Typical Work Products

- Individual requirement, e.g., *User Story*, *Software Requirements Specification (SRS)*  
- Set of requirements, e.g., use case, graphical models (e.g., UML), interface description, *Epics*, *Product Backlog*, *Story Map*  

### Level of Detail

- Depends on the purpose  
- *Note:* A high level of detail is time-consuming & costly  

### Early Planning & Clarification

- With stakeholders: work products, presentation, levels of detail  

### Guidelines

- Work product fits the purpose  
- Completeness & appropriate structure  
- No redundancies or inconsistencies  
- Clarity & consistent terminology  
- Versioning & traceability

--- 

## Natural Language Workproducts

### Advantages

- Expressiveness & flexibility  
- Direct; no special tools required  
- Easier for clients or users to understand  

### Disadvantages

- Ambiguities, omissions, lack of precision, etc.  

### Recommendations

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

--- 

## Template- and Model-Based Work Products

### Predefined Structures

- **Sentence template:** syntactic sentence structure, e.g., *User Story*  
- **Form template:** specific fields, e.g., *Use Case*  
- **Document template:** structure for a requirements document, e.g., *ISO 29148*  

### Advantages

- Consistent structure  
- Support in capturing important information  

### Disadvantages

- Focus on form instead of content  
- Other aspects may be overlooked  

### Model

- Simplified, abstract representation of reality for specific aspects  
- Often graphical representation  

**Types:**

- Context models  
- Models for structure & data  
- Models for function & process  
- Models for state & behavior  

**Modeling languages:**  

- Use standardized syntax, especially *UML*  

### Limitations

- Not every relevant piece of information can be expressed  

### Challenge

- Integrating and maintaining consistency across various models

--- 

## Requirements Specification & Functional Specification

### Requirements Specification (Lastenheft)

- Defined by the **client**.
- Contains the complete set of **requirements** for the **deliveries and services** of a contractor within a project  

### Functional Specification (Pflichtenheft)

- Developed by the **contractor**
- Contains **implementation guidelines** based on the client’s Requirements Specification  

### Challenges with the Requirements Specification (Lastenheft)

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

## Prototyping

Prototyping is about creating a simplified version of the end product with some of its capabilities. 
The goal is to create a testable object and once there some form of the end product the requirements can be 
adjusted.

### Rapid Prototype 

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

## Agile Requirement Engineering 

In this kind of RE the development team is an active participant of the RE team.The most detailed 
specification of comes very late during the development, and instead the team work with requirements 
as possible test cases.

## User Stories 

**User Story:** Simple narrative illustrating the user goals that a software function will satisfy.

Also, a narrative description of a software requirement, function, feature, or quality
attribute, presented as a narrative of desired user interactions with a software
system.

### Sentence Template 

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

