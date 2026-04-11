# Networking

Networking in computer science refers to concept of connection of 
multiple computers.

---

## Client Server Model 

It is a model which assigns roles to the computers connected in a network for an specific interaction. 

- **Server**: Persistent process which waits for requests to be processed. 
 
- **Client**: Short live process which sends requests to the server and eventually waits for a response. 

--- 

## Proxys 

A **proxy** is a computer system which acts as an intermideary between a client requesting a resource and 
a server providing the resource. 


- **Forward Proxy**: Proxy for the anonymisation/in-between-storage of the client-requests or the response of the server. 
The anonymity part is not always obligatory, hence there are also **transparent proxies**.

- **Reverse Proxy**: They act as if tey would be the ordinary server, but they are sending the request to the 
actual server to be further processed.

--- 

## Peer Processes

Direct connections of computer across an specific network allowing for rapid access and sharing of information in the network. 
Common example are torrent which are peer to peer networks.

--- 

## Communication Types 

When sharing information across different devices, there different types of ways this communication can 
be shared 

- **Unicast**: From one sender to exactly one receiver.

- **Multicast**: From one or multiple senders to an specific number of receivers

- **Broadcast**: All to all communication in a network.

- **Anycast**: Sending the data to the closest receiver.

--- 

## Point to Point 

A pair of computers share a direct one to one connection. 

### Types 

- **Full-Duplex**: Sending and receiving of the data is possible at the same time.

- **Half-Duplex**: Either sending or receiving at the same time. 

- **Simplex**: The data only is allowed to go in one direction.

--- 

## Mutli-Access-Networks 

Multiple computers are connected via a network medium. Eeach device is noted with an Adress for identification, thus, 
data is correctly delivered. Use of the `PDU` for protocol data unit for the content plus the address of the receiver.

--- 

## Static and Dynamic Connections

- **Static**: Each computer can have mutliple network connections with no specific time of comminication 
kind specified. The internet uses this and the **store-and-forward-principle** to connected computers all over the world.

- **Dynamic**: Connections have configurable elements for their dynamic use depending on the situation.

--- 

## Criteria for Static Networks

- **Diameter**: Maximal distance between 2 computers. Ideally small.

- **Connectivity**: Minimal number of connnections to be removed for the network to be divided into 2 disjoint networks. Ideally big.

- **Rank**: Number of connections of one computer with one of its neighbours. Ideally small.

Note: if all computers have the same rank, then the network is considered **regular**.

--- 

## Connection Patterns for Static Networks 

- **Chain**: all computers are connected in a chain. Hence a message from the start travels across all computers to reach the end machine.

- **Ring**: Chain where the last computer is connected to the first. 

- **Chordaler Ring**: Ring with some tetraedic connection inside. 

- **Barrel Ring**: Ring where also each node is connected to another if they are separated by two nodes.

--- 

## Networks Sorted By Area

- **PAN**: Personal Area Network, 1m.

- **LAN**: Local Area Network, 100m to 1km.

- **MAN**: Metropolitan Area Network, 1km to 100km.

- **WAN**: Wide Area Network, 100km to 1000km.

- **Internat**: Planet, 10000km.

--- 

## Local Area Networks 

Mostly used for individual homes or organizations. The computers are mostly connected directly to each other, 
and it can be accessed remotely using a **VPN** (Virtual Private Network).

--- 

## Metropolitan Area Network 

Conglomeration of multiple LANs where the networks are not directly connected, but with the use of extra components.

--- 

## Wide Area Network 

Used mostly by large organization across long distances allowing for point to point communication via points of presence. 

--- 

## Wide Area Network 

The same as the WAN but on a much larger scale. It can also be a conglomerate of WANs.

--- 

## Network Protocols

A protocol is a set of rules and practies for transmitting data across a network.

Common protocols include: 

- **Adress Resolution Protocol ARP:** Used for the mapping to MAC addresses.
- **Ethernet:** Used for the direct connection in a network.
- **Internet Control Protocol:** It is for testing reachability and other manners across the internet.

--- 

## Networks Components

--- 

## Ports 

A **port** is a communication endpoint. They are identified by a number and for the operating system, they are a logical construct to identify a process or a 
type of network service. Note that the at the hardware level we also have ports for audio, video, etc., but this are completely different ports.

Ports are regions of memory in the address-space of the operating system. Thus, the OS is reponsible for them.

--- 

## Sockets

Sockets are an abstraction provided by the operating system to enable communication 
between different processes either on the same machine or over a network. They act as 
endpoints in a two-way communication channel. **Socket = Protocol + IP Address + Port Number**. 

Sockets operate primarily at the **Transport** layer of the **OSI** model. They are called from the 
**Application** layer asking to send or receive data. Then the socket wrap it via **TCP/UDP** and send it to 
the **Network** layer.

They are handled by the operating system and commonly provided by **libc**. 

---

## File Descriptors and Sockets:

In networking, **sockets are treated like files**. When you create a socket using `socket()`, the system returns a file descriptor that you can use for reading
and writing data:

```c
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
// sockfd is now a file descriptor for a socket
```

This file descriptor can be used with functions like `read()`, `write()`, `close()`, or `select()` just like regular files.

### Why File Descriptors Matter:

* They provide a **uniform interface** for I/O operations.
* Used heavily in **multiplexing I/O** (e.g., `select()`, `poll()`, `epoll()`).
* Essential for **resource management**—every open FD consumes system resources.

### Closing File Descriptors:

To free up system resources, file descriptors must be explicitly closed using:

```c
close(sockfd); // Closes the socket and releases the FD
```

Failing to close file descriptors can lead to **resource leaks**, limiting how many files or sockets a program can open simultaneously.

---

## OSI Model

It as framework for working with networks. It stands for **Open System Interconnection**. It consist of the following layers:

- **Application:**  It provides network services (https, etc.) for the users by providing protocols like Brave. It also includes the (`GET`, `POST`, `DELETE`) operations.

- **Presentation:** Performs the task of syntax processing. This means to translate data from the application format to network format and viceversa. 
Encryption happens here.

- **Session:** It supports the construction direction and construction of connections of devices. For example: authentication handling.

- **Transport:**  This layer takes care of the transport of data across the network via protocols. It determines how much data to send, 
how fast, etc.

- **Network:** It provides the functional and procedurals means of transfering packages. It decides which physical path the data will take. It handles across 
the routing of the data and the mapping from logical addresses and physical addresses.

- **Data Link:** It receives the data and packages it into frames which are going to be send to the respective targets. It can 
also detect errors occurred at the physical layer and correct hem via algorithms.

- **Physical:** This layer consist on the electrical part of the network. In general the hardware which handles the raw bits.

---

## TCP/IP

**Transmission Control Protocol / Internet Protocol** is a collection of protocl which determine how data 
is formated, transported and used in networks. 

- **Application Layer**: 

- **Transport Layer**: 

- **Internet Layer**: 

- **Network Access Layer**: 

--- 

## Media Access Control 


--- 

## Logical Link Control 


--- 

## ARP

--- 

## Encapsultaion & Decapsulation 


--- 

## UDP and TCP

When it comes to computer networking, **UDP (User Datagram Protocol)** and **TCP (Transmission Control Protocol)** are two core transport layer protocols used to 
send data over the Internet. Each has its own characteristics, strengths, and ideal use cases.

### TCP (Transmission Control Protocol)

TCP is a **connection-oriented** protocol, meaning it establishes a reliable connection between sender and receiver before data transfer begins. It ensures that data is delivered **accurately and in the correct order**. For this it uses a **three-way handshake** which constist of: 
**SYN ->**, **<-SYN ACK** and finally **ACK->**.

**Key features of TCP:**
- **Reliable**: Uses acknowledgments (ACKs), retransmissions, and checksums to ensure data arrives intact.
- **Ordered**: Guarantees the sequence of data packets.
- **Error-checked**: Detects errors and corrects them through retransmission.
- **Flow control**: Manages the rate of data transmission to avoid overwhelming the receiver.
- **Connection-based**: Requires a handshake (three-way handshake) before data is exchanged.

**Common use cases:** Web browsing (HTTP/HTTPS), email (SMTP, IMAP, POP3), file transfers (FTP), and other applications requiring reliable communication.

### UDP (User Datagram Protocol)

UDP is a **connectionless** protocol that sends data without establishing a connection first. It prioritizes **speed over reliability**, making it faster but less reliable than TCP.

**Key features of UDP:**
- **Unreliable**: No guarantee of delivery, order, or duplication protection.
- **No handshakes**: Sends data without establishing a connection.
- **Lightweight**: Less overhead compared to TCP.
- **Broadcast and multicast support**: Useful for sending data to multiple recipients at once.

**Common use cases:** Online gaming, video streaming, voice over IP (VoIP), DNS queries, and other time-sensitive applications where speed is more critical than accuracy.

### Summary


| Feature              | TCP                           | UDP                          |
|----------------------|-------------------------------|------------------------------|
| Connection           | Connection-oriented            | Connectionless               |
| Reliability          | Reliable (ACKs, retransmissions) | Unreliable (no ACKs)        |
| Speed                | Slower due to overhead         | Faster, minimal overhead     |
| Use cases            | Web, email, file transfer      | Gaming, streaming, VoIP      |

Choosing between TCP and UDP depends on the needs of the application—**reliability and order** with TCP, or **speed and simplicity** with UDP.

---

## Localhost

`127.0.0.1` it is a way of treating the current computer as another one using the loopback interface. It is mostly 
used for the local testing of server-side applications, APIs. 

It is important to note that the address is hardcoded by the OS.

--- 

## Socket Lifecycle

The **socket lifecycle** represents the stages a network socket goes through during communication between a client and a server. Understanding this lifecycle is crucial for developing reliable networked applications using either TCP or UDP.

Below is a typical **TCP socket lifecycle**, presented as a top-to-bottom flow with arrows:

```
Client Side                        Server Side
------------                      ------------

   [Socket()]                      [Socket () (creation)]
        ↓                                ↓
[Connect Request]                    [bind() (bind to port)]
        ↓                                ↓
   [connect()] ----------------> [listen() (listening for connections)]
        |                                ↓
        |                            [accept()]
        ↓                                ↓
   [Data Transfer] <----------->  [Data Transfer read() or write()]
        ↓                                ↓
   [close()]  <------------------     [close()]
```

### Lifecycle Stages (TCP):

1. **Socket Created**
   Both client and server create a socket using system calls (e.g., `socket()` in C or Python).

2. **Bind (Server only)**
   The server binds its socket to a specific IP address and port using `bind()`.

3. **Listen (Server only)**
   The server starts listening for incoming connections using `listen()`.

4. **Connect (Client)**
   The client initiates a connection to the server using `connect()`.

5. **Accept (Server)**
   The server accepts the connection using `accept()`, creating a new socket for the client.

6. **Data Transfer**
   Both sides can send and receive data using `send()` and `recv()`.

7. **Close Connection**
   Once communication is done, both sides close their sockets using `close()` or `shutdown()`.

---

## Unix Domain Sockets

**Unix Domain Sockets (UDS)** are a method of inter-process communication (IPC) that allows data exchange between processes running on the same host. Unlike network sockets that use IP addresses and port numbers, Unix Domain Sockets use file system pathnames as their addressing mechanism.

### Key Characteristics

- **Local Communication Only**: UDS can only be used for communication between processes on the same machine.
- **Performance**: They offer lower latency and higher throughput compared to TCP/IP sockets due to bypassing the network stack.
- **Security**: Access control is enforced through standard file system permissions.
- **Socket Types**: Supports `SOCK_STREAM` (like TCP), `SOCK_DGRAM` (like UDP), and `SOCK_SEQPACKET`.

### Typical Use Cases

- Communication between a web server (e.g., Nginx) and an application server (e.g., uWSGI or Gunicorn).
- Fast, secure IPC in containerized or tightly controlled environments.
- Replacement for loopback TCP connections where performance and security are critical.

### Example

Here’s how to create a Unix domain socket in Python:

```python
import socket
import os

server_address = '/tmp/uds_socket'

# Make sure the socket does not already exist
try:
    os.unlink(server_address)
except FileNotFoundError:
    pass

# Create a UDS socket
sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)

# Bind the socket to the address
sock.bind(server_address)

# Listen for incoming connections
sock.listen(1)

print(f"Listening on {server_address}")
```

---

## Command ip link

In linux the `ip link` command will return three device names

- `lo` for the loop back device
- `Ethernet Plug`
- `Wifi card`

--- 

## SSH

Secure shell is a protocol used for providing a secure encrypted connection to a remote machine. It uses asymmetric encryption
and commonly port 22 for the connection.

### Layout

```txt
| Packet length -- Padding Amount -- Payload Padding -- Message Authentication |
```

Everything between packet length and message authentication is encrypted.

---

## IP Adresses 


--- 

## MAC Adresses 


--- 

## Subnetting 


--- 

## Security


--- 


