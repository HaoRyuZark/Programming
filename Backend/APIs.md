# APIs

Application Programming Interface are ways to define how software components
to communicate with each others.

---

## Web Servers 

A **web server** is a software application which handles the HTTP request from a client. It is the program responsible for routing and
delegating the request to the right **service**, just another program running which handles the specific functionality. 

It is also possible for the web server to handle the request itself, but this is not a good practice for large applications.

--- 


## Stateless

**Stateless** in the context of APIs means that each request from the client to the server contains all of the information needed to understand and process the request. 
The server or client do not need to store data to handle the request.

--- 

## Representational State Transfer (REST)

**Representational State Transfer (REST)** is an architectural style for designing networked applications. It relies on a **stateless**, **client-server**, **cacheable** 
communications protocol -- and in virtually all cases, the HTTP protocol is used. RESTful applications use HTTP requests to perform CRUD (Create, Read, Update, Delete) operations on resources, 
which are identified by URIs (Uniform Resource Identifiers).

The resources are reachable through endpoints, which are specific **URLs/URIs** that represent the resource or functionality provided by the API.

### Format

The format looks mostly like: 

```http
GET /api/users HTTP/1.1
Host: example.com
Accept: application/json
Some-Header: value
Status: 200 OK
Body: 
{
    "name": "John Doe",
    "age": 30,
    "email": "john@example.com"
}
``` 

- **Verb**: The HTTP method used to perform the operation (GET, POST, PUT, DELETE).

- **Endpoint**: The URL/URI that identifies the resource being accessed.

- **Headers**: Additional information sent with the request, such as content type and authorization.

- **Status**: The HTTP status code indicating the result of the request (e.g., 200 OK, 404 Not Found, 500 Internal Server Error).

- **Body**: The data sent with the request, typically used in POST and PUT requests.


### When to use REST

- When the API needs to be simple and easy to use.
- When the API needs to be scalable and stateless.
- When the API needs to support multiple data formats (e.g., JSON, XML).
- When the API needs to be easily cacheable for performance optimization.

---

## CRUD Operations

- **POST -Create** - creates a new resource on the server.
- **GET - Read** - get the information from the server.
- **PUT/PATH - Update** - PUT replaces while PATCH modifies the information.
- **DELETE - Delete** - Deletes the resource.

---

## URL/URI

A **Uniform Resource Locator (URL)** or **Uniform Resource Identifier (URI)** is a reference (an address) to a resource on the internet. 
It specifies the location of the resource as well as the protocol used to access it.

---

## Endpoints

An **endpoint** is a specific URL/URI where an API can be accessed by a client application. It represents a specific resource or functionality 
provided by the API.

---

## API Gateway

An **API Gateway** is a server that acts as an intermediary between clients and backend services. It handles incoming API requests, 
routes them to the appropriate service, and returns the response to the client. API gateways can provide additional functionality such 
as authentication, rate limiting, caching, and request/response transformation.

--- 

## How Are APIs Accessed

APIs are accessed through **HTTP requests** sent from a client application to the API server. The client can be a web browser, 
mobile app, or any other software that can make HTTP requests.

The server process listens for incoming requests, processes them, and sends back an HTTP response containing the
requested data or the result of the operation.


--- 

## JSON

**JSON (JavaScript Object Notation)** is a lightweight data interchange format that is easy for humans to read and write, and easy 
for machines to parse and generate. It is commonly used in web APIs to transmit data between a server and a client.

Example:

```json
{
    "name": "John Doe",
    "age": 30,
    "email": "john@example.com"
}
```

---

## HTTP Request

An **HTTP request** is a message sent by a client to a server to request a specific resource or perform an action. It consists of several components, including the request line, headers, and an optional body.

### Parts of HTTP Request

- **Request Line**: Contains the HTTP method (GET, POST, PUT, DELETE), the URL/URI of the resource, and the HTTP version.
- **Headers**: Key-value pairs that provide additional information about the request, such as content type, authorization, and user agent.
- **Body**: Optional part of the request that contains data sent to the server, typically used in POST and PUT requests.

Example:

```http
POST /api/users HTTP/1.1
Host: example.com
Content-Type: application/json
{
    "name": "John Doe",
    "age": 30,
    "email": "john@example.com"
}
```

---

## Caching

**Caching** is the process of storing copies of data or resources in a temporary storage location (cache) to reduce the time it takes to access that data in the future. In the 
context of APIs, caching can improve performance and reduce server load by serving cached responses for frequently requested resources.


### Caching Strategies

- **Client-side caching**: The client stores a copy of the response and uses it for subsequent requests, reducing the need to contact the server.

- **Write-through caching**: The cache is updated whenever the underlying data is modified, ensuring that the cache always contains the most up-to-date information.

- **Write-back caching**: The cache is updated first, and the changes are written to the underlying data store asynchronously, improving write performance but potentially risking data 
loss in case of a failure.

- **Time-based caching**: The cache is set to expire after a specific time period, after which the client must request the resource from the server again.

---

## HTTP Response

An **HTTP response** is a message sent by a server to a client in response to an HTTP request. It consists of several components, including the status line, headers, and an optional body.

### Parts of HTTP Response

- **Status Line**: Contains the HTTP version, status code (e.g., 200, 404, 500), and a reason phrase.
- **Headers**: Key-value pairs that provide additional information about the response, such as content type, content length, and server information.
- **Body**: Optional part of the response that contains the data sent back to the client, typically in JSON or HTML format.

Example:

```http
HTTP/1.1 200 OK
Content-Type: application/json
{
    "id": 1,
    "name": "John Doe",
    "age": 30,
    "email": "john@example.com"
}
```

---

## Middleware

**Middleware** is software that acts as an intermediary between different systems or applications, facilitating communication and data exchange. In the context of APIs, middleware can handle tasks 
such as authentication, logging, request/response transformation, and error handling.

---

## API Contract

An **API contract** is a formal agreement between the API provider and the API consumer that defines the expected behavior, inputs, outputs, and error handling of the API. It serves as a blueprint for how the API should be used and what to expect from it.

Example:

```yaml
paths:
  /users:
    get:
      summary: Retrieve a list of users
      responses:
        '200':
          description: A list of users
          content:
            application/json:
              schema:
                type: array
                items:
                  $ref: '#/components/schemas/User'
components:
  schemas:
    User:
      type: object
      properties:
        id:
          type: integer
        name:
          type: string
        age: 
          type: integer
        email:
          type: string
```

---

## Open API

**OpenApi** is an specification in the form of a yaml file used to define how the service API looks like, what is returned, what is spected, mandatory fields, 
urls, examples etc. The standard is availble online with how endpoints should be declared in the yaml file. It also allows developer to use tools like Swagger to visualize their 
definitions.

Example:

```yaml 

```

It can also be used to generate code from the definition in a specific language. 

> Note: It only supports RESTful APIs

---

## How to Test APIs

---

## GraphQL

GraphQL is a query language for APIs and a runtime for executing those queries by using a type system you define for your data. It allows clients to request only the data they need, making it more efficient than traditional REST APIs.

Example:

```graphql
query {
  user(id: "1") {
    id
    name
    email
  }
}
```

### When to use GraphQL

- When clients need to request specific data and avoid over-fetching or under-fetching.
- When the API needs to support complex queries and relationships between data.
- When the API needs to evolve without breaking existing clients.

---

## gRPC

gRPC is a high-performance, open-source framework developed by Google for remote procedure calls (RPC). It uses Protocol Buffers (protobuf) as its interface definition language and supports multiple programming languages. gRPC is designed for low-latency and high-throughput communication between services.

Example:

```protobuf
syntax = "proto3";
service UserService {
  rpc GetUser (UserRequest) returns (UserResponse);
}
message UserRequest {
  int32 id = 1;
}
message UserResponse {
  int32 id = 1;
  string name = 2;
  string email = 3;
}
```

### When to use gRPC

- When low latency and high throughput are critical for inter-service communication.
- When strong typing and contract-first API design are desired.
- When bidirectional streaming and real-time communication are required.
- When supporting multiple programming languages in a microservices' architecture.

---

## Key Design Principles for APIs

- **Consistency**: Ensure that API endpoints, request/response formats, and error handling are consistent across the entire API.

- **Simplicity**: Design APIs that are easy to understand and use, avoiding unnecessary complexity.

- **Security**: Implement robust authentication and authorization mechanisms to protect API resources.

- **Performance**: Optimize API performance through techniques such as caching, pagination, and efficient data retrieval.

## API Design and Implementation Process

- Identify core use cases and user stories.

- Define the scope and boundaries of the API.
  
- Determine performance requirements and constraints.
  
- Design the API endpoints, request/response formats, and error handling.

- Document the API using tools like OpenAPI/Swagger.

- Test the API thoroughly to ensure it meets requirements and performs as expected.

## API Protocols

We will handle protocols at the application layer. Some common API protocols include:

- **HTTP/HTTPS**: The most common protocol for web APIs, used for RESTful APIs. It supports various methods like GET, POST, PUT, DELETE, etc.

- **WebSockets**: A protocol for full-duplex communication channels over a single TCP connection, often used for real-time applications. Instead
of request-response, it allows continuous data exchange by just establishing the connection once. The server can send data to the client without the client requesting it each time.

- **gRPC**: A high-performance RPC framework developed by Google, using Protocol Buffers for serialization.

- **AMQP**: Advanced Message Queuing Protocol, used for message-oriented middleware. It works on a publish-subscribe model, allowing asynchronous communication between services.

---

## Sorting

**Sorting** is the process of arranging data in a specific order, typically ascending or descending, based on one or more attributes. In the context of APIs, sorting can
be applied to the results of data retrieval operations to enhance usability and data presentation.

---

## Pagination

**Pagination** refers to the process of dividing a large set of data into smaller, manageable chunks or pages. It is used to limit the amount of 
data returned in a single response, improving performance and reducing bandwidth usage. 

Clients can request specific pages of data, allowing for efficient navigation through large datasets.


### Trade-Offs

When designing the API the **page size** should be adjusted to not exagerate the amount of requests necessary from a client. 

### Types Of Pagination

- **Offset-based**: We used a page attribute or an offset with a limit. Then when a request is made we can return data besed on the page number assigned to the 
data in the database. The mapping can be assigned with the row numbers and an ordering.

**Example**:

Query: 

```sql 
SELECT * FROM users LIMIT 10 OFFSET 20;
```

Response:

```http
Response:
HTTP/1.1 200 OK
Content-Type: application/json
{
    "page": 2,
    "size": 10,
    "totalPages": 5,
    "totalElements": 50,
    "content": [
        {
            "id": 11,
            "name": "User 11",
            "email": "user11@example.com"
        }
    ]
}
```

The problems of using this approach are that the query can become slower, new items can messed up the order resulting into inconsisten results. In contrast it is very 
easy to implement.

- **Cursor-based**: This is used with the help of cursor (index) which is used to iterate over the rows in the database. The idenx is embeded into the request.

---

## Query Parameters

**Query parameters** are key-value pairs appended to the end of a URL/URI to provide additional information or filter the results of an API request. They are typically used to
specify options, such as sorting, filtering, pagination, and other parameters that affect the response.

Example:

```http
GET /api/users?sort=age&filter=active&page=2&limit=10
```

--- 


## Versioning

**Versioning** is the practice of managing changes and updates to an API over time. It allows developers to introduce new features, fix bugs, and make improvements without disrupting existing 
clients that rely on the API. Versioning helps maintain backward compatibility and ensures a smooth transition for users when changes are made.

Most of the time you put the version in the URL path `/api/v1/resource`.

Example:

```http
GET /api/v1/users HTTP/1.1
Host: example.com
Accept: application/json
```

Another alternative is to put the version in the request header `Accept: application/vnd.example.v1+json`.

---

## Status Codes

**Status codes** are standardized three-digit numbers returned by a server in response to an HTTP request. They indicate the outcome of the request and provide information about the status of the 
requested resource. Status codes are grouped into five categories based on their first digit:

- **1xx (Informational)**: The request was received, and the server is continuing the process.

- **2xx (Successful)**: The request was successfully received, understood, and accepted.

- **3xx (Redirection)**: Further action is needed to complete the request.

- **4xx (Client Error)**: The request contains bad syntax or cannot be fulfilled.

- **5xx (Server Error)**: The server failed to fulfill a valid request.

---

## Authentication & Authorization

**Authentication** is the process of verifying the identity of a user or system, ensuring that they are who they claim to be. Common authentication methods include 
username/password combinations, API keys, JWT, OAuth tokens, and biometric verification.

**Authorization** is the process of determining whether an authenticated user or system has the necessary permissions to access a 
specific resource or perform a particular action. Authorization typically occurs after authentication and involves checking access control lists (ACLs), roles, or policies to grant or deny access.

### API Keys

This a single unique key used to authorize an user or appliation for using and API. They are mostly passed in the request header when a
request is triggered.

### JSON Web Token (JWT)

This is a string with 3 parts used to grant access to a service and keep the "user" validated as long the session runs instead
doing an authentication check for accessing the resource.

- **Headers**: Type of token and ecryption. 
- **Payload**: Actual encrypted token plus the expiration date.
- **Signature**: Digital signature of the token.

The token is packed in the `Authorization: Bearear<token>` header and sent to the server, where only the signature is checked.

### Sessions 

These are stateful server-side handled authentication. 

1. User fills a login form 
2. The server checks the credentials and crates a session in the database.
3. The session id is end to the client. 
4. The client puts the session id in the cookies maps. 

---

## Rate Limiting

**Rate limiting** is a technique used to control the number of requests a client can make to an API within a specified time period. It helps prevent abuse, ensures fair usage, and protects the 
server from being overwhelmed by excessive requests. Rate limiting can be implemented using various strategies, such as fixed window, sliding window, or token bucket algorithms.

---

