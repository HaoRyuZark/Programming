# Cloud Computing

**Cloud computing** refers to a model of business and architecture for software products in which an entity 
provides, hardware resources for another subject to use for an specific software application, host software, etc.

Common examples: software as a service, infrastructure as a service for hosting application, database services on the cloud, etc.

The main reason for such models is to reduce the maintenance costs of hosting a computing centre while also allowing specialized teams to 
focus only on the development of the solutions. Dedicated specialist can be dedicate their time to maintain infrastructure in dedicated companies.

--- 

## Scalable Systems 

**Scalable systems** are systems designed to handle increasing workloads by adding resources, such as servers or storage, to the system. They require careful planning 
at every layer of the system: database, application, and infrastructure.

--- 

## Nodes 

A **node** is a single point of connection in a network. In the context of cloud computing, a node can refer to a server, virtual machine, or container that is part of a larger distributed system. 
Nodes can be added or removed from the system to scale it up or down as needed.

---

## Scaling Variants 

- **Vertical**: scaling by adding more hardware or enhancing resources to a single node. This is limited by the maximum capacity of the hardware and can be expensive.

- **Horizontal**: scaling by adding more nodes to a system, such as adding more servers to a distributed application. 
- This approach can provide better fault tolerance and scalability compared to vertical scaling.  This can also refer to distributing work 
more efficiently across CPUs, threads, etc.

--- 

## Serverless Computing

**Serverless computing** is a cloud computing model in which the cloud provider manages the infrastructure and automatically allocates resources as needed to run applications.
In this model, developers can focus on writing code without worrying about the underlying infrastructure, such as servers, operating systems, or networking. Serverless computing is often used for 
event-driven applications, such as web applications, APIs, and microservices. It can provide cost savings and scalability benefits compared to traditional server-based architectures.

--- 

## Cloud Deployment Models

### Software as a Service (SaaS)

It stands for **Software as a Service (SaaS)**. This model of cloud computing focuses on providing a software
via the internet under a pricing model. It has the advantage that for the customer they do not have to care about the installation, update, etc.

One the biggest selling point is the fact that hardware, OS, etc. are abstracted away and the end users do not to worry about 
installations or technical problems.

Even if the initial idea is great for certain services, companies exploit customers with this model. Be ethical and only 
use it if the application if worth it, not a note taking app.

### Infrastructure as a Service (IaaS)

**Infrastructure as a Service (IaaS)** gives the provider control over the servers, storage, networks, firewalls, and the data center.
The buyer only gets control over which applications they want to host.

### Platform as a Service (PaaS)

In **Platform as a Service (PaaS)**, it is similar to IaaS, but it offers also developer tools, the choice of the OS and more possibilities
for the developers by abstracting the hardware.

--- 

## Event Driven Architecture

**Event-driven architecture (EDA)** is a software architecture pattern that focuses on the production, detection, and reaction to events.
In this architecture, components communicate with each other by producing and consuming events, which are typically represented as messages or notifications which are put in 
a queue. This allows for decoupling of components and enables real-time processing of events.

--- 

## Storage Formats 

Without abstractions all data will be stored as files in a file system. However, there are different formats of storage that can be used to store data and manage it 
in more efficient ways. The most common formats are:

### Block Storage

**Block storage** is a type of storage that stores data in fixed-size blocks. Each block has a unique identifier, 
allowing for efficient data retrieval and management. Block storage is commonly used in cloud computing environments for applications that require 
high performance and low latency, such as databases and virtual machines.

The disadvantage of block storage is that it requires more management and configuration compared to other storage formats, such as file storage or 
object storage.

### File Storage

**File storage** is a type of storage that organizes data in a hierarchical structure of files and folders. Each file has a unique name and can be accessed
using standard file system protocols, such as NFS or SMB. File storage is commonly used in cloud computing environments for applications that require shared access to files, 
such as content management systems and collaboration tools.

### Object Storage

**Object storage** is a type of storage that stores data as objects, which are self-contained units that include the data itself, metadata, and 
a unique identifier. They are like buckets which can be filled with data and then accessed via a unique identifier. 

Object storage is highly scalable and is commonly used in cloud computing environments for applications that require large amounts of unstructured data, 
such as media files, backups, and archives.


