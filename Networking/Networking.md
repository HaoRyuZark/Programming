# Networking

Networking in computer science refers to concept of connection of
multiple computers.

---

## Host

**Hosts** are any device which sends or receive traffic.

Every host needs four items for internet connectivity: 

- **IP-address**: the host's identity.
- **Subnetmask**: the size of the host's network.
- **Default Gateway**: router's IP-address.
- **DNS Server IP-addr**: Translates domain names to IPs.

---

## Client Server Model

It is a model which assigns roles to the computers connected in a network for an specific interaction.

- **Server**: Persistent process which waits for requests to be processed.

- **Client**: Short live process which sends requests to the server and eventually waits for a response.

---

## Proxies

A **proxy** is a computer system which acts as an intermediary between a client requesting a resource and
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

## Multi-Access-Networks

Multiple computers are connected via a network medium. Each device is noted with an address for identification, thus,
data is correctly delivered. Use of the `PDU` for protocol data unit for the content plus the address of the receiver.

---

## Static and Dynamic Connections

- **Static**: Each computer can have multiple network connections with no specific time of communication
kind specified. The internet uses this and the **store-and-forward-principle** to connected computers all over the world.

- **Dynamic**: Connections have configurable elements for their dynamic use depending on the situation.

---

## Criteria for Static Networks

- **Diameter**: Maximal distance between 2 computers. Ideally small.

- **Connectivity**: Minimal number of connections to be removed for the network to be divided into 2 disjoint networks. Ideally big.

- **Rank**: Number of connections of one computer with one of its neighbors. Ideally small.

Note: if all computers have the same rank, then the network is considered **regular**.

---

## Connection Patterns for Static Networks

- **Chain**: all computers are connected in a chain. Hence a message from the start travels across all computers to reach the end machine.

- **Ring**: Chain where the last computer is connected to the first.

- **Chordale Ring**: Ring with some tetraedic connection inside.

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

## Global Area Network

The same as the WAN but on a much larger scale. It can also be a conglomerate of WANs.

---

## Network Protocols

A protocol is a set of rules and practices for transmitting data across a network.

Common protocols include:

- **Address Resolution Protocol ARP:** Used for the mapping to MAC addresses.
- **Ethernet:** Used for the direct connection in a network.
- **Internet Control Protocol:** It is for testing reachability and other manners across the internet.

---

## Ports

A **port** is a communication endpoint. They are identified by a number and for the operating system, they are a logical construct to identify a process or a
type of network service. Note that the at the hardware level we also have ports for audio, video, etc., but this are completely different ports.

- Ports are regions of memory in the address-space of the operating system. Thus, the OS is responsible for them.
- Ports in a networking context are always bind with an IP-Address. `IP-Address:Port`

### Assigned Ports

- **System ports (Well-known)**: (0-1023). Standardized for protocols and system communication. (Server-side, can also be the own computer)
- **User ports (Registered)**: (1024-49151). Can be registered by companies or developers for specific services. (Server-side)
- **Dynamic ports  (Private)**: (49152-65535). Free to use. (Client-side).

### Common Ports
 
- **80**: HTTP
- **443**: HTTPS
- **21**: FTP 
- **25**: SMTP
- **22**: SFTP/SSH
- **53**: DNS

### Port Forwarding 

It is a technique used for allowing external devices access to a local network. When a request reaches a router then it gets 
redirected to correct computer and port.

---

## Sockets

Sockets are an abstraction provided by the operating system, i.e a software object/API; to enable communication
between different processes either on the same machine or over a network. They act as
endpoints in a two-way communication channel. **Socket { Protocol, IP Address, Port Number, file_descriptor}**.

When calling a socket API one mostly gets an object or just a file descriptor which references the region where the data is going 
to be put for transfer or receiving.

Sockets operate primarily at the **Transport** layer of the **OSI** model. They are called from the
**Application** layer asking to send or receive data. Then the socket wrap it via **TCP/UDP** and send it to
the **Network** layer.

They are handled by the operating system and commonly provided by **libc**.

### Types Of Sockets

- **Datagram**: Uses UDP.
- **Stream**: Uses TCP.

### Socket Life Cycle

```txt

   Server Side                               Client Side
   ------------                              ------------

   [Socket() (creation)]                     [Socket() (creation)]
        |                                          |
   [bind() (bind to port)]                   [Connect Request]
        |                                          |
   [listen() (listening for connections)]    [connect()]
        |                                          |
   [accept()]                                [Data Transfer]
        |                                          |
   [Data Transfer read() or write()] <-----> [Data Transfer read() or write()]
```

### File Descriptors and Sockets

In networking, **sockets are treated like files**. When you create a socket using `socket()`, the system returns a file descriptor that you can use for reading
and writing data:

```c
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
// sockfd is now a file descriptor for a socket
```

This file descriptor can be used with functions like `read()`, `write()`, `close()`, or `select()` just like regular files.

### Why File Descriptors Matter

- They provide a **uniform interface** for I/O operations.
- Used heavily in **multiplexing I/O** (e.g., `select()`, `poll()`, `epoll()`).
- Essential for **resource management**—every open FD consumes system resources.

### Closing File Descriptors

To free up system resources, file descriptors must be explicitly closed using:

```c
close(sockfd); // Closes the socket and releases the FD
```

Failing to close file descriptors can lead to **resource leaks**, limiting how many files or sockets a program can open simultaneously.

---

## OSI Model

It as framework for working with networks. It stands for **Open System Interconnection**. It consist of the following layers:

7. **Application:**  It provides network services (https, etc.) for the users by providing protocols like Brave. It also includes the (`GET`, `POST`, `DELETE`) 
operations.

6. **Presentation:** Performs the task of syntax processing. This means to translate data from the application format to network format and vice versa.
Encryption happens here.

5. **Session:** It supports the construction direction and construction of connections of devices. For example: authentication handling.

> The previous 3 layer can also be compress into one Application layer.

4. **Transport:**  This layer takes care of the transport of data across the network via protocols. It determines how much data to send,
how fast, if it was send correctly (via the correct protocol, ports, ...), etc. 

- Service to Service (function)
- TCP/UDP Porst (addressing)

3. **Network:** It provides the functional and procedurals means of transfering packages. It decides which physical path the data will take. It handles across
the routing of the data and the mapping from logical addresses and physical addresses.

- End to End (function)
- IP Addresses (addressing)
- Routers, Hosts (devices)

2. **Data Link:** It receives the data and packages it into frames which are going to be send to the respective targets. It can
also detect errors occurred at the physical layer and correct them via algorithms.

- Hop to Hop  (function)
- MAC Addresses (addressing)
- Switches (devices)

1. **Physical:** This layer consist on the electrical part of the network. In general the hardware which handles the raw bits.

- Transport of bits (function)
- Cables, WiFi, Hubs (devices)

---

## Payload

This term refers to the actual, intended data transmitted in a network communication without the headers and extra information.

---

## DHCP 

The **Dynamic Host Configuration Protocol** provides a host with an IP, SM, DG and DNS server dynamically.
This is the protocol responsible for providing access to the internet when a device is connected to the internet by just plugin 
the ethernet cable or the wifi password.

--- 


## TCP/IP

**Transmission Control Protocol / Internet Protocol** is a collection of protocol which determine how data
is formatted, transported and used in networks.

- **Application Layer**: Is the data which is going to be send.

- **Transport:**  This layer takes care of the transport of data across the network via protocols. It determines how much data to send,
how fast, if it was send correctly, etc.. Defines **Segments**.

- **Network:** It provides the functional and procedurals means of transfering packages. It decides which physical path the data will take. It handles across
the routing of the data and the mapping from logical addresses and physical addresses. Defines **frames**.

- **Data Link:** It receives the data and packages it into frames which are going to be send to the respective targets. It can
also detect errors occurred at the physical layer and correct hem via algorithms. Defines **packets**.

- **Physical Layer**: Consists on the hardware components of the system.

### Frames

### Segments

### Packets

---

## Media Access Control

---

## Logical Link Control

---

## Encapsulation & Decapsulation



---

## UDP and TCP

When it comes to computer networking, **UDP (User Datagram Protocol)** and **TCP (Transmission Control Protocol)** are two core transport layer protocols used to
send data over the Internet. Each has its own characteristics, strengths, and ideal use cases.

### TCP (Transmission Control Protocol)

TCP is a **connection-oriented** protocol, meaning it establishes a reliable connection between sender and receiver before data transfer begins. It ensures that data is delivered **accurately and in the correct order**. For this it uses a **three-way handshake** which constist of:

**SYN ->** 
**<-SYN ACK** 
**ACK->**

Key features of TCP:

- **Reliable**: Uses acknowledgments (ACKs), retransmissions, and checksums to ensure data arrives intact.
- **Ordered**: Guarantees the sequence of data packets.
- **Error-checked**: Detects errors and corrects them through retransmission.
- **Flow control**: Manages the rate of data transmission to avoid overwhelming the receiver.
- **Connection-based**: Requires a handshake (three-way handshake) before data is exchanged.

#### TCP Header

```txt 
Source Port (16 bits) | Destination Port (16 bits)
Sequence Number (32 bits)
Acknowledgment Number (32 bits)
Data Offset (4 bits) | Reserved (3 bits) | Flags (9 bits)
Window Size (16 bits)
Checksum (16 bits) | Urgent Pointer (16 bits)
```

- **Source Port**: The port number of the sender.
- **Destination Port**: The port number of the receiver.
- **Sequence Number**: Used to keep track of the order of packets. If a packet is lost, the receiver can request a retransmission.
- **Acknowledgment Number**: Used to acknowledge the receipt of packets. 
- **Data Offset**: Indicates where the data begins.
- **Flags**: Control flags (e.g., SYN, ACK, FIN).
- **Window Size**: Used for flow control. It indicates how much data the sender can send before waiting for an acknowledgment.
- **Checksum**: Used for error-checking the header and data.

#### SYNC Packet Layout

```txt
Source Port (16 bits) | Destination Port (16 bits)
Sequence Number (32 bits) | SYN Flag (1 bit) | Other Flags (8 bits)
```   

#### ACK Packet Layout

```txt
Source Port (16 bits) | Destination Port (16 bits)
Sequence Number (32 bits) | ACK Flag (1 bit) | Other Flags (8 bits)
Acknowledgment Number (32 bits)
```

#### When are ACKS sent?

After receiving a packet, the receiver sends an ACK back to the sender to confirm receipt.

#### The Reset Flag 

The **Reset (RST)** flag is used to abruptly terminate a connection. It can be sent by either the client or the 
server when they want to immediately close the connection without going through the normal FIN-ACK sequence. This can happen in cases of errors, unexpected conditions, or when a connection is refused.

#### Timeout and Retransmission

If a sender does not receive an ACK within a certain time frame, it assumes the packet 
was lost and retransmits it. This process continues until an ACK is received or a maximum number of retransmissions is reached.

#### Graceful Connection Termination

To gracefully terminate a TCP connection, the following sequence of messages is typically exchanged:

1. The client sends a **FIN** (Finish) packet to the server, indicating that it has finished sending data.
2. The server responds with an **ACK** to acknowledge the FIN.
3. The server then sends its own **FIN** packet to the client, indicating that it has also finished sending data.
4. The client responds with an **ACK** to acknowledge the server's FIN, completing the termination process.

#### Ungraceful Connection Termination

In an ungraceful termination, one side simply closes the connection without following the proper FIN-ACK sequence. This can lead to issues such as:

- The other side may not be aware that the connection has been closed, leading to potential resource leaks.
- Data that was in transit may be lost, as there is no acknowledgment of receipt.
- The server may continue to wait for data from the client, leading to timeouts or hanging

### UDP (User Datagram Protocol)

UDP is a **connectionless** protocol that sends data without establishing a connection first. It prioritizes **speed over reliability**, making it faster but less reliable than TCP.

Key features of UDP:

- **Unreliable**: No guarantee of delivery, order, or duplication protection.
- **No handshakes**: Sends data without establishing a connection.
- **Lightweight**: Less overhead compared to TCP.
- **Broadcast and multicast support**: Useful for sending data to multiple recipients at once.

#### UDP Header

```txt 
Source Port (16 bits) | Destination Port (16 bits)
Length (16 bits)
Checksum (16 bits)
```

- **Source Port**: The port number of the sender.
- **Destination Port**: The port number of the receiver.
- **Length**: The length of the UDP header and data.
- **Checksum**: Used for error-checking the header and data.

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
        |                                |
[Connect Request]                    [bind() (bind to port)]
        |                                |
   [connect()] ----------------> [listen() (listening for connections)]
        |                                |
        |                            [accept()]
        |                                |
   [Data Transfer] <----------->  [Data Transfer read() or write()]
        |                                |
   [close()]  <------------------     [close()]
```

### Lifecycle Stages (TCP)

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

## Command ip link

In linux the `ip link` command will return three device names

- `lo` for the loop back device
- `Ethernet Plug`
- `Wifi card`

---

## HTTP & HTTPS

It stands for **Hyper Text Transport Protocol**; the **S** stands for **Secure** and refers to the data 
being encrypted. This is a TCP-based protocol which consists on the following 
life-cycle of a connection.

```txt
               CLient             Server 
               ------             ------
               |                  |
TCP Handshake  | SYN              |
               |----------------->|
               |                  |
               |  SYN ACK         |
               | <----------------|
               |                  |
               |  ACK             |
               |----------------->| Connection Established
               |                  |
Certificate    |   Certificate    |
               | <----------------|
               |                  |
               |  Encrypted Data  |
               | <--------------> |
               |                  | 
```

- The **SYNC** and **ACK** packages do not really contain data, but instead just meta data for checking the connection.

- The main use is for webpages and the information transferred in those.

---

## SSL


--- 

## TLS


--- 
## MAC Addresses

## DNS

**Domain Name System** is a method of mapping domain names in plain text to actual IP-Address of a server.

### Steps

1. Check if the IP address is stored if not, then 

2. The request is redirected to a **resolver** which also checks for the IP-Address, but if not found then: it communicates with a **root** server which tells our 
resolver to which **TLD Top Level Domain Server** to talk which finally tells the resolver the IP. If not, then

3. The resolver is redirected to an specific **Athoriative Name Server** which always know the IP address

--- 

## SSH

Secure shell is a protocol used for providing a secure encrypted connection to a remote machine. It uses asymmetric encryption
and commonly port 22 for the connection.

### Layout

```txt
| Packet length -- Padding Amount -- Payload Padding -- Message Authentication |
```

- **Packet Length**: Size of the package including the headers.
- **Padding Amount**: Bruh.
- **Payload**: Actual Data.
- **Message Authentication**: Cryptographic code.

Everything between packet length and message authentication is encrypted.

---

## IP Addresses

An **IP-Address**, (Internet Protocol Address) is the identity of each computer. Means they are unique.

### IPv4

They are 32-bit long with 2**32 possible addresses.

- Divided into 4 octets of 8 bits

Example:

```text 
192.0.2.146
```

### IPv6

They were implemented to adapt for the demand of new address, due to IPv4 being 
to limited. They are 128-bit long with 2**128 possible addresses

- Divived into 8 segments of 16 bits, hextets.
- Encoded in hex.

Example:

```text 
2001:db8:0:1:1234:0:561:1:2
```

### Public and Private IPs

- **Private**: 
   - Only visible in the local network. 
   - Assigned by the wifi-card.
   - It is also unique.
   - Not routable for the internet.

- **Public**: 
   - Assined by the internet service provider. 
   - It is also unique.
   - Routable for the internet.

The process which translates from private to public and viceversa is the so called **Network Address Translation (NAT)**, which 
does exactly what the name implies and adds a layer of security by masking the private address.

### Static and Dynamic IPs

- **Static**:
   - Do not change
   - Are manually assigned by an admin.
   - Ideal for hosting servers and long-term services.

- **Dynamic**:
   - Dynamically assigned by a network.
   - Flexible.
   - Widely used for consumer devices.

---

## MAC Addresses

**Media Access Control Address** is a 48-bit address used in the local network assigned by the fabricant.

### Structure 

They consists of: 

- 6 hextets.

- Starting from the left, the first 3 hextets are used for the **Organizationally Identifier (OUI)**, which is used for the identification 
of the manufacturer. 

- The other 3 are for the **Network Interface Controller (NIC)**, which is used for the actual networking identification tasks.

--- 

## Repeater

A **repeater** its a device which regenerates signals, it is used to prevent signal decay.

---

## Hub

A **hub** is a multi-port-repeater which allows to connect all devices in a network indirectly via itself.

---

## Bridge

They sit between hub-connected host which allow to regulate the data send by hubs. For example: if we have to
networks connected via two hubs, the bridge between the two ensures that only data from one network reaches the
other if and only if necessary, other data emitted by the hub does not cross the bridge.

---

## Switches

**Switching** is the process of moving data withing networks. **Switches** are a combination of hubs and bridges design to redirect data to the right receiver within a network, 
also they do switching. 

- They use a layer 2 header which consists on the source and destination MAC-addresses.
- They mantain a MAC-Adress Table for matching switch ports to MAC-adresses.

Actions: 

- **Learn**: Update the table with mappings when a packet comes from another hub.

- **Flood**: Duplicate and send frame out all switch ports. This is not a broadcast, since they are performed using and special MAC-adress `ffff.ffff.ffff` while 
flooding only is a send accross all of the open ports of the switch.

- **Forward**: Once an extensive table has been filled, the data gets forwarded without the flood operation.

---

## Node

A **node** is a device that implements IPv6.

--- 

## Routers

For inter-network-communication we have **routers** which connect switches and router of two or more different networks.
A node that forwards IPv6 packets not addressed to itself.

- They maintain a map of all the networks they know about (**routing table**).
- **Routes** are the starts bit sequences of an network. 

### Population Methods For The Routing Table

- **Directly Connected**: Routes for networks which are attached.
- **Static Routes**: Routes manually provided by an administrator.
- **Dynamic Routes**: Routes learned automatically from other routes.

### Router Hierarchy

Routers are commonly deployed in hierarchical structure accomplished via subnetting. In this process parts of
IP-addresses are interpreted depending on the how many octets are going to be used to identify a network. 

### Default Route

It is an special route mostly written as `0.0.0.0 /0`. The adress is just zero and the subnetmask is to read 0 octets of the IP-addr. 
This route is used as "for everythin else, go here" for leaf routes in a tree-structure.

---

## ARP

**Address Resolution Protocol**, is a protocol used for resolving IP to MAC mappings.

---

## FTP 

--- 

## SMTP

--- 


--- 

## Sub-netting


---

## Cookies

**Cookies** are a mechanism to keep track of an client in a server. They are a number mostly 
passed as headers inside HTTPS headers. Once a server inserted a cookie in a response then the browser 
adds the cookie to all of the clients request to tell the server who the client is.

- **First Party Cookies**: Set by the direct server in the current connection.
- **Third Party Cookies**: Set by another server which are used by different server to track a user.

### Cookies Policy

Is a disclosure made by the website about how cookies are used and how he can manage the cookies.

--- 

## Security



---


