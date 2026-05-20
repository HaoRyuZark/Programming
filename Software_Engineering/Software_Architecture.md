# Software Architecture 

Is the way of describing a solution concept for functional and non-functional requirements.

It accomplishes the following goals:

- Concrete high level descriptions of a complex system
- Abstraction
- Organization of resources
- Gives context
- Orientates the planing

--- 

## Components and End-Points

- **Components**: are individual entities like programs, entire systems or a conglomerate of those.
- **End-Points (API)**: are the exposed abstracted functionality of the components.

--- 

## Clean Architecture

**Clean Architecture** is a pattern of software architecture in which the **business logic layer** is split into 
the **Application** and **Domain** layers. 

- **Presentation**: What the user sees. Handles the interactions with users and other computers.
- **Application**: Contains the usa cases of the system
- **Domain**: Contains the domains, models.
- **Infrastructure**: Defines the programs, patterns, etc. i.e. the infrastructure.
- **Data Base**: Actual storage. 

The dependence between the layers is designed in way such that layer-technology can be replaced with alternatives, as long a 
they compliance to our high level defined contracts. 

--- 

## Domain Driven Design

**Domain Driven Design (DDD)** is an approach to software development that emphasizes collaboration between technical and domain experts to create a 
shared understanding of the problem domain. It focuses on modeling the core business concepts and logic, ensuring that the software reflects the real-world processes and rules.

### Key Concepts of DDD:

- **Domain**: The sphere of knowledge and activity around which the application logic revolves. It represents the business problem being solved.

- **Entities**: Objects that have a distinct identity and lifecycle. They are defined by their attributes and behaviors.

- **Value Objects**: Objects that are defined by their attributes rather than a unique identity. They are immutable and often used to represent concepts like money, dates, or measurements.

- **Aggregates**: A cluster of related entities and value objects that are treated as a single unit for data changes. An aggregate has a root entity that controls access to the other entities and value objects within it.

- **Repositories**: Abstractions that provide methods for retrieving and storing aggregates. They act as a bridge between the domain model and the data storage mechanism.

- **Services**: Operations that do not naturally fit within an entity or value object. They encapsulate domain logic that involves multiple entities or value objects.

### Strategic Design

Focus on the overall structure of the software system, including how different components and modules interact with each other. It involves defining the boundaries of the system, 
identifying key components, and determining how they will communicate and collaborate to achieve the desired functionality.

### Tactical Design 

Focus on the design of the software components, ensuring that they adhere to the principles of DDD and are organized in a way that promotes maintainability and scalability.

### Phases of DDD:

1. **Domain Exploration**: Collaborate with domain experts to understand the problem domain and identify key concepts, entities, and relationships.

2. **Modeling**: Create a domain model that captures the essential business logic and rules. This model should be expressed in a ubiquitous language that is shared between technical and domain experts.

3. **Implementation**: Develop the software based on the domain model, ensuring that the code reflects the business logic and rules defined in the model. Use repositories to manage data persistence and services to handle complex
operations.

4. **Refinement**: Continuously refine the domain model and implementation as new insights are gained and requirements evolve. This iterative process helps to ensure that the software remains aligned with the business needs

### Ubiquitous Language

A common language that is used by both technical and domain experts to describe the concepts and processes within the problem domain. It helps to ensure clear communication and a shared 
understanding of the domain model. This is used inside a **bounded context**, which is a defined boundary within which a particular model is applicable.

### Context Map

A visual representation of the relationships between different bounded contexts in a DDD application. It helps to identify how different parts of the system interact and where integration points exist.

### Anti-corruption Layer

A layer that acts as a barrier between different bounded contexts to prevent the corruption of one context's model by another. It translates between the models of different contexts, 
ensuring that they remain independent and maintain their integrity.

---

## Model View Controller 

The **Model View Controller (MVC) Architecture** defines the structural and functional design that enables interaction between the user interface, 
control logic, and underlying model management system. It is organized into modular layers that ensure scalability, maintainability, and 
real-time responsiveness.

### Architectural Overview

The architecture follows a three-tier structure:

#### Presentation Layer (UI) 

Provides the graphical interface through which users interact with the system.

- Displays model status, configuration panels, and performance metrics.
- Supports interactive controls for parameter tuning and monitoring.
- Implements real-time updates using WebSocket or streaming APIs.

#### Control Layer (Logic and Orchestration) 

Acts as the intermediary between the UI and backend model services.

- Handles user commands, input validation, and state synchronization. In other words it handles the request flow.
- Maintains session context and ensures consistent model configurations.
- Implements event-driven communication for responsiveness and low latency.

#### Data and Model Layer (Backend Services) 

Manages the actual models, data pipelines, and configuration storage.

- Provides APIs for model inference, parameter updates, and telemetry data.
- Utilizes caching and database systems for fast retrieval and persistence.
- Integrates with deployment infrastructure for distributed model execution.

### Core Components

Model Controller Coordinates communication between the user interface and model APIs. 

- Responsible for applying updates to model parameters and retrieving system metrics.
- Configuration Manager Handles persistence and versioning of model settings. Enables loading, saving, and restoring of configuration profiles.
- Telemetry Engine Collects and streams performance data such as latency, throughput, and token utilization. Supports visualization in the UI dashboard.
- Access Gateway Enforces security and role-based permissions for users interacting with model controls.

### Data Flow

1. The user issues a control command (e.g., parameter change) through the interface.
2. The Control Layer validates the request and dispatches it to the Model Controller.
3. The Model Controller updates the backend model configuration and logs the event.
4. Updated performance and configuration data are streamed back to the UI for visualization.

### Design Principles

- Modularity – Each component functions independently for ease of maintenance.
- Real-Time Feedback – Low-latency event propagation ensures responsive control.
- Security and Traceability – All operations are authenticated and logged.
- Scalability – Supports multiple concurrent users and models across distributed systems.

--- 

## The Layer Architecture 

Separates each part of the system into independent layers or domains. It can be hard to implement due to the borders between layers being 
highly subjective. But it can also be very easy to understand.

--- 

## Technical Debt 

It is a metaphor for the drawbacks of design or technical choices which if not handled correctly can lead to unmaintainable 
software and other serious problems. 

--- 

## Event Driven Architecture 

It is a way of defining how different services interact when a message, **event** happens asynchronously. In this 
architecture we have:

- **Producer**: Publishes the events.

- **Broker**: Handles the redirection of the events to the corresponding service. 

- **Consumer**: Gets the event and processes it. 

It is critical for the participants to support async IO, else this architecture can not be accomplished.

--- 

## Microservices 

This are applications which consists on smaller application which handle parts of the functionality of the main application. 


| **Advantages** | **Disadvantages** |
| ------------|--------------|
| Easy Scale | Hard to debug | 
| Small releases  | Complex deployment |
| Single Responsibility |  Latency due to communication |
| Highly Maintainable | Hard to setup development environments if not done right |
| Modularity |  Requires more infrastructure |
| Easy to refactor |  More complexity in the system |
| Independence of tech-stack | |
| More resilience | |


--- 

## Monoliths 

Is an application where every functionality is inside one project with high dependence. So the same application contains: 
API-handlers, data processing, payments, etc. 


| **Advantages** | **Disadvantages** |
| ------------|--------------|
| Easy to debug | Bad scalability | 
| High Coherence  | Bloating |
| Easy to develop |  High coupling |
| High performance | Long Release Process|
| Easy to deploy |  If a part goes wrong the whole app goes down |


--- 
