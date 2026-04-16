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

- **Components**: are individual entities like programs, entire systems or a comglomerate of those.
- **End-Points (API)**: are the exposed abtracted functionality of the components.

--- 

## Model View Controller 

The **Model Control View Architecture** defines the structural and functional design that enables interaction between the user interface, 
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

- Handles user commands, input validation, and state synchronization. In other words it handles the reques flow.
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
highly subsjective. But it can also be very easy to understand.

--- 

## Technical Debt 

It is a metaphore for the drawbacks of desing or technical choices which if not handled correctly can lead to unmaintainable 
software and other serious problems. 

--- 

## Event Driven Architecture 

It is a way of defining how different services interact when a message, **event** happends asynchonous. In this 
architecture we have:

- **Producer**: Publishes the events.

- **Broker**: Handles the rediraction of the events to correspondent service. 

- **Consumer**: Gets the event and processes it. 

It is critical for the participants to support async IO, else this architecture can not be accomplised.

--- 

## Domain Driven Design 



--- 

## Microservices 

This are applications wich consists on smaller application which handle parts of the functionality of the main application. 


| **Adavantages** | **Disadvantages** |
| ------------|--------------|
| Easy Scale | Hard to debug | 
| Small releases  | Complex deployment |
| Single Responsability |  Latency due to communication |
| Highly Maintainable | Hard to setup development enviroments if not done right |
| Modularity |  Requiere more infrastructure |
| Easy to refactor |  More complexity in the system |
| Independence of tech-stack | |
| More resisilance | |


--- 

## Monoliths 

Is an application where every functionality is inside one project with high dependence. So the same application contains: 
API-handlers, data processing, payments, etc. 


| **Adavantages** | **Disadvantages** |
| ------------|--------------|
| Easy to debug | Bad scalability | 
| High Coherence  | Bloating |
| Easy to develop |  High coupling |
| High performance | Long Release Process|
| Easy to deploy |  If a part goes wrong the whole app goes down |


--- 


