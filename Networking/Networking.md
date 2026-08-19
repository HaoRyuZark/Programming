# Networking

**Networking** in computer science refers to the concept of connecting multiple computers.

---

## How Do We Access The Internet? 

Even with all of the wireless technologies available, they are only used to connect our devices to the router of our local network. This router is wired 
via a cable given by you internet provider which is the real connection to the real internet.

--- 

## Host

**Hosts** are any device which sends or receive traffic.

Every host needs four items for internet connectivity: 

- **IP-address**: the host's identity.

- **Subnetmask**: the size of the host's network.

- **Default Gateway**: router's IP-address, the device which connects networks.

- **DNS Server IP-addr**: Translates domain names to IPs.

- **MAC-Addresses**: the address for the local network. 

---

## Payload

This term refers to the actual, intended data transmitted in a network communication without the headers and extra information.

---

## Client Server Model

It is a model which assigns roles to the computers connected in a network for an specific interaction.

- **Server**: Persistent process which waits for requests to be processed.

- **Client**: Short live process which sends requests to the server and eventually waits for a response.

---

## Proxies

A **proxy** is a computer system which acts as an intermediary between a client requesting a resource and
a server providing the resource. This helps keep the IP address secret for the internet except for the proxy.

- **Forward Proxy**: Proxy for the anonymisation/in-between-storage of the client-requests or the response of the server.
The anonymity part is not always obligatory, hence there are also **transparent proxies**.

- **Reverse Proxy**: They act as if tey would be the ordinary server, but they are sending the responses to the clients. The 
real requests are still processed by the real server, but the proxy acts as the entry point.

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

**Multi-access-networks** consist of multiple computers which are connected via a network medium. Each device is noted with an address for identification, thus,
data is correctly delivered. Use of the **PDU** for **protocol data unit** for the content plus the address of the receiver.

---

## Static and Dynamic Connections

- **Static**: Each computer can have multiple network connections with no specific time of communication
kind specified. The internet uses this and the **store-and-forward-principle** to connected computers all over the world.

- **Dynamic**: Connections have configurable elements for their dynamic use depending on the situation.
This is mostly used internal communication inside the computer.

---

## Criteria for Static Networks

- **Diameter**: Maximal distance between 2 computers. Ideally small.

- **Connectivity/ Bisection-rank**: Minimal number of connections to be removed for the network to be divided into 2 disjoint networks. Ideally **big**.

- **Rank**: Number of connections of one computer with one of its neighbors. Ideally small.

Note: if all computers have the same rank, then the network is considered **regular**.

---

## Network Topology 

- **Bus**: all computers are connected in a chain. Hence a message from the start travels across all computers to reach the end machine.
   - Simple, but easy to break.

- **Ring**: Chain where the last computer is connected to the first.
   - Faster but also if the connection breaks on two ends, the network becomes unusable. 

- **Star**: Similar to a ring, but with a central point of redirection. 
   - Simple yet very effective. 
   - Not very scalabel for large networks. 

- **Chordale Ring**: Ring with some tetradic connection inside.
   - Effective, but complex. 

- **Barrel Ring**: Ring where also each node is connected to another if they are separated by two nodes.
   - Not scalable yet very reliable.

- **Mesh**: All computers are connected via a complex graph, but inlike the previous ring variants the connections to some computers are just transitive and not direct. 
   - Very scalable 
   - May fail if a sector is dependent on just one machine, but it is the de-facto topology of the internet.
   - Lots of reduncancy

In real-life scenarios combinations of the patterns are used depending on the size and requirements of the network.

---

## Networks Sorted By Area

- **PAN**: Personal Area Network, 1m.

- **LAN**: Local Area Network, 100m to 1km.

- **MAN**: Metropolitan Area Network, 1km to 100km.

- **WAN**: Wide Area Network, 100km to 1000km.

- **Internat**: Planet, 10000km.


### Local Area Networks

Mostly used for individual homes or organizations. The computers are mostly connected directly to each other,
and it can be accessed remotely using a **VPN** (Virtual Private Network).


### Metropolitan Area Network

Conglomeration of multiple LANs where the networks are not directly connected, but with the use of extra components.


### Wide Area Network

Used mostly by large organization across long distances allowing for point to point communication via points of presence.


### Global Area Network

The same as the WAN but on a much larger scale. It can also be a conglomerate of WANs.

---

## Protocols 

A **protocol**, in the context of networking, is the sum of all agreements, rules and algorithms between software applications for the purpose of a communication.

--- 

## Hub 

A **hub** is a device which redirects data in a local network, but it always send the data to all devices connected 
through ports instead of being selective like a **switch**. They do **not** have knowledge of addresses.
They are a layer 1 device. **Do not block broadcasts**

--- 

## Bridge

**Bridges** sit between hub-connected host which allow to regulate the data send by hubs. They segment a LAN.
They use **MAC-addresses** to determine if the data should cross the bridge. They are a layer 2 device.
**Do not block broadcasts**

For example: if we have two networks connected via two hubs, the bridge between the two ensures that only data from one network reaches the other 
if and only if necessary, other data emitted by the hub does not cross the bridge.

---  

## Switches

**Switching** is the process of moving data withing networks. **Switches** are a combination of hubs and bridges design to redirect data to the right receiver within a network, 
also they do switching. **Do not block broadcasts**

- They use a layer 2 header which consists on the source and destination MAC-addresses.
- They maintain a **MAC-Addresses Table** for matching switch ports to MAC-addresses.

Actions: 

- **Learn**: Update the table with mappings when a packet comes from another hub.

- **Flood**: Duplicate and send the frame out all switch ports. This is not a broadcast, since they are performed using and special MAC-address `ffff.ffff.ffff` while 
flooding only is a send across all of the open ports of the switch.

- **Forward**: Once an extensive table has been filled, the data gets forwarded without the flood operation.

When a package is from **A** sent to **C** the following process occurs: 

1. The data reaches the bridge, if the mac-address of the sender is not in the able it gets added.

2. If destination address is not in the table, it sends the data across all ports.

3. The next time **C** sends a package, the switch will also store its mac-address and also because **A** is already 
in the table it will redirect the package just to **A**.

---

## Modem

A **modem** demodulates incoming analog signals into a digital signal and modulates outcoming signals as analog signals. 
Inside home networks routers, modems and even swithces are put into one device. 

--- 

## Routers

For **inter-network-communication** we have **routers** which connect switches and router of two or more different networks.
**Do block broadcasts**

The are mostly inside networks as a **gateway** which is a term also used for routers, but it is more general and can 
refer to any device that acts as an entry point to another network, not necessarily a router.

- They maintain a map of all the networks they know about (**routing table**).

- **Routes** are the starts bit sequences of an network. 

- They assign an IP-address to every computers in the local network. 

- They are a layer 3 device.

- They can have more than one internet card, and hence, more than one IP-address.

### Population Methods For The Routing Table

- **Directly Connected**: Routes for networks which are directly connected via cables.

- **Static Routes**: Routes manually provided by an administrator. They are mostly used for forwarding packages to the next hop.

- **Dynamic Routes**: Routes learned automatically from other routes using dynamic routing protocols.

### Router Hierarchy

Routers are commonly deployed in hierarchical structure accomplished via subnetting. In this process parts of
IP-addresses are interpreted depending on the how many octets are going to be used to identify a network. 

### Default Route

It is an special route mostly written as `0.0.0.0 /0`. The address is just zero and the subnetmask is to read 0 octets of the IP-addr. 
This route is used as "for everything else, go here" for leaf routes in a tree-structure.

### Routing 

When a package is send across the internet which is connection of networks via routers; the way routers know how to pass the package to 
the right router is accomplished via shortest parth algorithms as well as well as hardcoded adress to distributor servers.

- Router groups are divided into local areas which know a range of IP adresses which minimizes the amount of
computation and memory required for the routing table processes.
 
### Routing Protocols

Routers need to coordinate traffic in between their own organization they belong to and also other organization. For this purpose they have to use 
different approaches, so called **routing protocols**. They mostly communicate with their direct neighbors and also 
coordinate how their routing tables should be filled.

One example of these algorithms is the Dijkstra algorithm for path-finding and other methods of sharing routing tables.
Another example is for routers to have specific domains of the IP-space which simplifies the number of entries a ISP-router needs to know to redirect traffic efficiently.

Common protocols include: 

- **RIP**: it measures distance between routers by counting hops. It is well suited for small networks which do not need more **15** hops.
   - Neighboring routers exchange their routing table every 30 seconds
   - Each routers only knows about their neighbor.
   - The only metric is the hop-count without taking speed or quality into consideration.

- **OSPF**: routers exchange information about the connection and is better suited for medium size networks. 
   - Divides networks into areas for efficiency.. 
   - Routers share information about the **link-state** to build full maps of the network.

- **BGP**: is used for connect autonomous systems. It is the protocol used to power the internet as it connects big networks together.
   - It counts the number of autonomous systems a package has traveled.
   - It is policy based.

---

## Default Gateway

The **default gateway** is commonly the address of the router which allows us to communicate with outside networks. 
When the target is in the same network the address of the switch is used instead for the communication. 

### Use with the Subnetmask 

Using the subnetmask it is determined which devices are inside the network. This is configured by the admin.

--- 

## Network Interface Card (NIC) 

The **NIC** is a micro-controller used for handling the communications of a computer, it can provide the sending and receiving 
of data, policy and other functionalities which provides better functionality for OS since it does not have to care about all of the setup for connection 
and only uses the drivers and reducing the number of interrupts.

--- 

## OSI Model

It as framework for working with networks. It stands for **Open System Interconnection**. It consist of the following layers:

7. **Application:**  It provides the API's and network services (https, etc.) for the users by providing protocols like Brave. It also includes the (`GET`, `POST`, `DELETE`) 
operations.

- SMTP.
- FTP.
- HTTPS.
- Telnet, etc.

6. **Presentation:** Performs the task of syntax processing. This means to translate data from the application format to network format and vice versa.
Encryption happens here. It can be summarized as how the data is formated /represented.

- Encryption. 
- Text-based format. 
- Encodings.

5. **Session:** It supports the construction direction and termination of connections of devices. For example: authentication handling.

- JSWT.
- Sessions.

> The previous 3 layer can also be compress into one Application layer.

4. **Transport:**  This layer takes care of the transport of data across the network via protocols. It determines how much data to send,
how fast, if it was send correctly (via the correct protocol, ports, ...), etc. 

- Service to Service (function).
- TCP/UDP Protocol.
- Ports.
- **Segments**

3. **Network:** It provides the functional and procedural means of transferring packages. It decides which physical path the data will take. It handles across
the routing of the data and the mapping from logical addresses and physical addresses.

- End to End (function)
- IP Addresses (addressing)
- Routers, Hosts (devices)
- **Packets**

2. **Data Link:** It receives the data and packages it into frames which are going to be send to the respective targets. It can
also detect errors occurred at the physical layer and correct them via algorithms.

- Hop to Hop  (function)
- MAC Addresses (addressing)
- Switches (devices)
- **Frames**

1. **Physical:** This layer consist on the electrical part of the network. In general the hardware which handles the raw bits.

- Transport of bits (function)
- Cables, WiFi, Hubs (devices)

This model is not really used anymore, but it is closely related to TCP/IP model.

### Encapsulation & Decapsulation

This is the process undergoes data when traveling through the different layers of the OSI Model. 
Layer will add and discard extra data related only to its domain. 

Example: 

**Encapsulation**:

- Application: user sends an email. The data is text send via SMTP.

- Presentation: the data is encrypted and transformed into the most apropiate format for the comming transport.

- Session: a session for the user is started to handle its current action.

- Transport: a TCP **segment** containing source and destination ports is added.

- Network: source and destination IP-address are added as a **packet**

- Data Link: the MAC-addresses of source and destination are added as a **frame**.

- Physical: the data is send using Ethernet.

**Decapsulation**:

Starting from the physical layer, the data travels across the layers by discarding extra data added during the process like the segments, frames, etc. 
when they are not needed anymore.

--- 

## Transmission Control Protocol (TCP)

**TCP** is a **connection-oriented** protocol, meaning it establishes a reliable connection between sender and receiver before data transfer begins. It ensures that data is delivered 
**accurately and in the correct order**. For this it uses a **three-way handshake** which consists of:

**SYN ->** 
**<-SYN ACK** 
**ACK->**

Key features of TCP:

- **Reliable**: Uses acknowledgments (ACKs), retransmissions, and checksums to ensure data arrives intact.
- **Ordered**: Guarantees the sequence of data packets.
- **Error-checked**: Detects errors and corrects them through retransmission.
- **Flow control**: Manages the rate of data transmission to avoid overwhelming the receiver.
- **Connection-based**: Requires a handshake (three-way handshake) before data is exchanged.

### TCP Header

```txt
| Source Port (16 bits) | Destination Port (16 bits)                                |
|                                                                                   |
|           Sequence Number (32 bits)                                               |
|                                                                                   |
|        Acknowledgment Number (32 bits)                                            |
|                                                                                   |
| Data Offset (4 bits) | Reserved (3 bits) | Flags (9 bits) | Window Size (16 bits) |
|                                                                                   |
|        Checksum (16 bits) |  Urgent Pointer (16 bits)                             |
```

- **Source Port**: The port number of the sender.

- **Destination Port**: The port number of the receiver.

- **Sequence Number**: Used to keep track of the order of packets. If a packet is lost, the receiver can request a retransmission.

- **Acknowledgment Number**: Used to acknowledge the receipt of packets. 

- **Data Offset**: Indicates where the data begins.

- **Flags**: Control flags (e.g., SYN, ACK, FIN).
   - **URG** urent pointer field. 
   - **PSH**: this segment request a push.
   - **SYN**: synchronize sequence numbers. 
   - **ACK**: Acknowledgement. 
   - **RST**: reset the connection. 
   - **FIN**: sender has reached end of this byte stream.

- **Window Size**: Used for flow control. It indicates how much data the sender can send before waiting for an acknowledgment.

- **Checksum**: Used for error-checking the header and data. Before the data is send it is performed and send with the data, so that the other computer can check if they get the same checksum.

### SYNC Packet Layout

```txt
Source Port (16 bits) | Destination Port (16 bits)
Sequence Number (32 bits) | SYN Flag (1 bit) | Other Flags (8 bits)
```   

### ACK Packet Layout

```txt
Source Port (16 bits) | Destination Port (16 bits)
Sequence Number (32 bits) | ACK Flag (1 bit) | Other Flags (8 bits)
Acknowledgment Number (32 bits)
```

#### When are ACKS sent?

After receiving a packet, the receiver sends an ACK back to the sender to confirm receipt.

### The Reset Flag 

The **Reset (RST)** flag is used to abruptly terminate a connection. It can be sent by either the client or the 
server when they want to immediately close the connection without going through the normal FIN-ACK sequence. This can happen in cases of errors, unexpected conditions, or when a connection is refused.

### Timeout and Retransmission

If a sender does not receive an ACK within a certain time frame, it assumes the packet 
was lost and retransmits it. This process continues until an ACK is received or a maximum number of retransmissions is reached.

### Graceful Connection Termination

To gracefully terminate a TCP connection, the following sequence of messages is typically exchanged:

1. The client sends a **FIN** (Finish) packet to the server, indicating that it has finished sending data.
2. The server responds with an **ACK** to acknowledge the FIN.
3. The server then sends its own **FIN** packet to the client, indicating that it has also finished sending data.
4. The client responds with an **ACK** to acknowledge the server's FIN, completing the termination process.

### Ungraceful Connection Termination

In an **ungraceful termination**, one side simply closes the connection without following the proper FIN-ACK sequence. This can lead to issues such as:

- The other side may not be aware that the connection has been closed, leading to potential resource leaks.

- Data that was in transit may be lost, as there is no acknowledgment of receipt.

- The server may continue to wait for data from the client, leading to timeouts or hanging

### Flow Control

This is a method to ensusere that the sender is not overwhelming the receiver, because the receiver has a finite buffer to 
handler data. This is accomplished by modifying the **window size** field of the header.

This done by sharing the window-size of both server and client and then both participants automatically will administrate the communication 
with the respective size. If the size changes for any of the sides, then this is also automatically communicated.

### Stop And Wait 

This is a method in which the server always waits for an acknowlegment once the send-window size if full. 
Sometimes they even just send one segment at a time.

### The Sliding Window Protocol

Instead of one frame at the time and waiting of an acknowledgment, the **sliding window protocol** uses an array 
with a number of entries being equal to the number of frames to be sent after splitting the packet; and then sends groups 
of frames each time an acknowledgment is received the "window" is slided to send another next frame and so on. 

If no acknoledgment arraives, the window stays in place, until the acknowledgment is recieved or an external condition terminates the communication.
There are different variations with different techniques which include sending dupplicates, dynamic window sizes, etc.

**Example:**

We have a window size of 4 and 10 segments. 

We would send 4 segments, wait for an acknowledgment, send 4 more segments and let us pretend the 7th 
segment did not reach the destination, so we will re-send along side the remaining 2 segments and moves the window.

### Go Back N ARQ

We have a window size $n$ which represents the number of frames we accept before sending an acknowledgment. If no acknowledgment is received then 
all frames in the current window are re-transmited. Each time the sender gets an ACK for the oldest frame the window is moved by one.

### Selective Repeat 

In contrast to the last protocol, we only re-transmit the frames which got lost. The difference is that the other frames are not re-transmitted, but instead 
the window still moves on. The sending terminates only when all the lost packages are re-transmitted successfully or a timeout hits. The window only moves after 
all acks are received.

--- 

## User Datagram Protocol (UDP)

**UDP** is a **connectionless** protocol that sends data without establishing a connection first. It prioritizes **speed over reliability**, making it faster but less reliable than TCP.

Key features of UDP:

- **Unreliable**: No guarantee of delivery, order, or duplication protection.
- **No handshakes**: Sends data without establishing a connection.
- **Lightweight**: Less overhead compared to TCP.
- **Broadcast and multicast support**: Useful for sending data to multiple recipients at once.

### UDP Header

```txt 
| Source Port (16 bits) | Destination Port (16 bits) |
| Length (16 bits)      | Checksum (16 bits)         |
```

- **Source Port**: The port number of the sender.

- **Destination Port**: The port number of the receiver.

- **Length**: The length of the UDP header and data.

- **Checksum**: Used for error-checking the header and data.

**Common use cases:** Online gaming, video streaming, voice over IP (VoIP), DNS queries, and other time-sensitive applications where speed is more critical than accuracy.

---

## Ports

A **port** is a communication endpoint commonly used to identify an application in a communication. They are identified by a number and for the operating system, 
they are a logical construct to identify a process or a type of network service. Note that the at the hardware level we also have ports for audio, video, etc., 
but this are completely different ports.

- Ports are regions of memory in the address-space of the operating system. Thus, the OS is responsible for them. Can be seem as letter-boxes.
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

**Port forwarding** is a technique used to map certain ports in a router to computer inside the local network.

$$ \text{Port } \mapsto \text{ IP-address } $$

- A request arrives at the router with an specific port **X**. 

- The request gets mapped to an specific computers, static IP-address inside the network. This could be a machine 
running a service like streaming, cloud-storage, etc.

Note, that is used for when some computer from the outside tries to access the local private network.

### Port Security

It allows to control which source MAC-Addresses are allowed to enter an specific switch port.

It can be done in the following ways:

- Limiting the set of MAC-addresses for the port.

- Limiting the number of devices per port.

- Allowing only a certain list of MAC-addresses. 

- Only allowing certain ports at machines.

---

## IP Addresses

An **IP-Address**, (Internet Protocol Address) is the identity of each computer. Means they are unique.

--- 

## IPv4

**IPv4** address are 32-bit long which means 2**32 possible addresses.

- Divided into **4 octets** of 8 bits which means that each octed can represent a number between 0 and 255.

Example:

```text 
192.0.2.146
```


- The address is separated into two parts: the network which are the first n bits, and host which consist on the rest of 
bits. This can be read using the subnetmask which will come later in the document.

Example: 

We want to send data to the address `192.168.5.3` with the subnetmask of `255.255.255.0` this means that the network address is 
`192.168.5.0` and our target computer in the network is identified as `3`.

### Static and Dynamic IPs

- **Static**:
   - Do not change
   - Are manually assigned by an admin.
   - Ideal for hosting servers and long-term services.

- **Dynamic**:
   - Dynamically assigned by a network.
   - Flexible.
   - Widely used for consumer devices.

### Classes of IPv4 

In the early days of the internet it was decided to classify the addresses into different classes for different uses. This turned out 
to be a horrible decision since the engineers could not predict the impact the internet would have in the future and some organizations 
now posses a large amount of IP-address for no purpose.


|Classs | Range | Subnetmask | Purpose | Hosts |
|:-----:|--------|-----------|----------|-------|
|A | 1.0.0.0 - 126.255.255.255 | 255.0.0.0 /8 | | 16,777,214 |
| loopback | 127.0.0.0 - 125.255.255.255 | 255.0.0.0 /8 |  |Dos not matter since it is a loopback|
|B | 128.0.0.0 - 191.255.255.255| 255.255.0.0 /16 | | 65,534 |
|C | 192.0.0.0 - 223.255.255.255 | 255.255.255.0 /24 |  | 254 |
|D | 224.0.0.0 - 239.255.255.255 | | | |
|E | 240.0.0.0 - 255.255.255.255| | | |


This fragmentation problem was solved by implementing private and public IP-address as well as subnets.

### Public and Private IPs

- **Public**: 
   - Assigned by the internet service provider for the router.
   - They are unique.
   - Routable for the internet.

- **Private**: 
   - Only visible in the local network. 
   - Assigned by the wifi-card.
   - They are unique in the LAN, but not unique at the global scale. 
   - Not routable for the internet.

`10.0.0.0/8`, `172.16.0.0/12`, `192.168.0.0/16` are the private IP ranges, which are reused across different local networks, 
thus they are not unique globally.


|Classs | Private Range | Subnetmask |
|:-----:|--------|-----------|
|A | 10.0.0.0 - 10.255.255.255 | 255.0.0.0  /8 |
|B | 172.16.0.0 - 172.31.0.0| 255.255.0.0 /16 |
|C | 192.168.0.0 - 192.168.225.255.255 | 255.255.255.0 /24 |


The process which translates from private to public and vice versa is the so called **Network Address Translation (NAT)**, which 
does exactly what the name implies and adds a layer of security by masking the private address.

> No traffic between private to private is allowed, but traffic between private to public and public to private is allowed.

### Host Addresses In A Network

Given an IP-address with its respective network and host section we can assign to a host any number in between first and last IP address 
in the range except for the first and last address. 

- The first address is used `x.x.x.0` is used to identify the network to identify the network.

- The last address is used `x.x.x.255` is a so called **broadcast** address used to broadcast data inside the network. 

### Assignment Of IP-Addresses

- **Automatic Prive IP Adressing**: uses 169.254.0 to 169.254.255.255 without the first and last 256 addresses. 

It uses ARP to check than an address is not in used in the 
local network.

### IPv4 Header

It has a size of **20 bytes**.

```text
+-------+-------+---------------+-------------------------------+
|Version|  IHL  | DSCP/ECN ToS  |         Total Length          |
+-------------------------------+-------+-----------------------+
|       Identification          | Flags |    Fragment Offset    |
+-------------------------------+-------+-----------------------+
|      TTL      |   Protocol    |      Header Checksum          |
+---------------------------------------------------------------+
|                     Source IP Address                         |
+---------------------------------------------------------------+
|                  Destination IP Address                       |
+---------------------------------------------------------------+
|           Options (optional) + Padding (if needed)            |
+---------------------------------------------------------------+
|                         Payload (Data)                        |
+---------------------------------------------------------------+
```

- **Version (4 bits)**: Specifies the IP version used. For IPv4, this field is always **4**.

- **IHL (Internet Header Length, 4 bits)**: Specifies the length of the IPv4 header in **32-bit words**.
   - Minimum value: **5** → `5 × 4 = 20 bytes` (no options)
   - Maximum value: **15** → `15 × 4 = 60 bytes`

* **DSCP / ECN (formerly ToS, 8 bits)**: Originally called **Type of Service (ToS)**. Today it is divided into:
  - **DSCP (6 bits):** Differentiated Services Code Point for Quality of Service (QoS)
  - **ECN (2 bits):** Explicit Congestion Notification

Used to indicate how routers should prioritize or handle the packet.

- **Total Length (16 bits)**: Specifies the total size of the IPv4 packet in **bytes**, including:
  - Header
  - Payload

  Maximum value: $ 2^{16}-1 = 65,!535 \text{ bytes} $

- **Identification (16 bits)**: A unique identifier assigned by the sender. It is used to **reassemble fragmented packets** at the destination.
All fragments belonging to the same original packet have the **same Identification value**.

- **Flags (3 bits)**: Controls fragmentation.
  - **Bit 0:** Reserved (always **0**)
  
  - **Bit 1 (DF):** Don't Fragment
    - `0` = Fragmentation allowed
    - `1` = Packet must not be fragmented

  - **Bit 2 (MF):** More Fragments
    - `0` = Last fragment (or packet wasn't fragmented)
    - `1` = More fragments follow

- **Fragment Offset (13 bits)**: Indicates **where this fragment belongs** within the original packet.
The offset is measured in **8-byte (64-bit) units**, **not bytes**.

- **TTL (Time To Live, 8 bits)**: Limits the lifetime of a packet by preventing routing loops.
Every router forwarding the packet decrements the TTL by **at least 1**. If TTL reaches **0**, the packet is discarded and an ICMP *Time Exceeded* message is usually returned.


- **Protocol (8 bits)**: Identifies the protocol encapsulated in the payload (the next layer), **not a port number**.
Common protocol numbers:

  - `1` → ICMP
  - `6` → TCP
  - `17` → UDP
  - `89` → OSPF

- **Header Checksum (16 bits)**: Error-detection checksum that protects **only the IPv4 header**, **not the payload**.
Since the TTL changes at every router, routers must recompute the checksum after forwarding the packet.

- **Source Address (32 bits)**: IPv4 address of the sender.

- **Destination Address (32 bits)**: IPv4 address of the intended recipient.

- **Options + Padding (0–40 bytes)**: Optional field used for special purposes such as:

   Security
  - Timestamping
  - Record Route
  - Source Routing

Padding is added so that the header length is always a multiple of **32 bits (4 bytes)**.

Most IPv4 packets do **not** include options, resulting in the minimum **20-byte header**.

--- 

## IPv6

They were implemented to adapt for the demand of new address, due to IPv4 being 
to limited to 2^32 addresses. They are 128-bit long with 2^128 possible addresses

- Divided into **8 hextets**,  segments of 16 bits.
- Encoded in hex.
- No public and private address needed, every device will get a unique address.

Example:

```text 
2001:db8:0:1:1234:0:561:1:2
```

### IPv6 Header 

It has a size of **40 bytes**.

```txt 
+-------+-----------------+-------------------------------------+
|Version|  Traffic Class  |      Flow Label                     |
+-------------------------------+--------------+----------------+
|       Payload Length          | Next Header  | Hop Limit      |
+-------------------------------+--------------+----------------+
|                     Source IP Address                         |
+---------------------------------------------------------------+
|                  Destination IP Address                       |
+---------------------------------------------------------------+
|                         Payload (Data)                        |
+---------------------------------------------------------------+
```

- **Version (4 bits)**: Version of the IP-protocols. 

- **Traffic Class (8 bits)**: It defines the priority of the packet.

- **Flow Label (20 bits)**: Identifier for the fast routing of the packet.

- **Payload Length (16 bits)**: Total length of the packet consisting on header and payload.

- **Next Header (8 bits)**: Port of the transport protocol.

- **Hop Limit (8 bits)**: maximal number of redirections, similar to TTL.

- **Source Addres (128 bits)**: IP of the source

- **Destination Address (128 bits)**: Address of the intended recipient.

- **IPv6-Header-Extensions (8 bits)**: optional information for the header.

---

## MAC Addresses

**Media Access Control Address (MAC)** is a 48-bit address used in the local network assigned by the fabricant. They are 
called physical addresses. They are used to identify a device directly inside a network and are unique.

They consists of: 

- 6 hextets.

- Starting from the left, the first 3 hextets are used for the **Organizationally Identifier (OUI)**, which is used for the identification 
of the manufacturer. 

- The other 3 are for the **Network Interface Controller (NIC)**, which is used for the actual networking identification tasks.

Example for the same address in different formats:

```txt 
08:00:27:EC:10:61 Linux Mac

08-00-27-EC-10-61 Windows

0800.27EC.1061 CISCO
```

### Types Of MAC-Addresses

- **Unicast**: refers to particular device.

- **Multicast**: they refer to a specific application or protocol. Mostly identifiable via a prefix in the address.

- **Broadcast**: (FF-FF-FF-FF-FF-FF) sends the request to all devices in the network.

--- 

## ARP

**Address Resolution Protocol**, is a protocol used for resolving IP to MAC mappings.

A workflow of **ARP** is as follows:

1. A host needs to send a packet to another host on the same local network, but it only knows the destination's IP address.

2. The host broadcasts an ARP request to all devices on the local network (broadcast), asking "Who has this IP address? Tell me your MAC address."

3. The device with the matching IP address responds with an ARP reply, providing its MAC address to the requester.

4. The requesting host receives the ARP reply and updates its ARP table with the new IP-to-MAC mapping, allowing it to send the packet directly to the destination using 
the resolved MAC address.

This also works for packages across networks, but the package would first need to be routed.

It also important to note that MAC-addresses are cached once resolved inside the **ARP Cache**.

### ARP Packet Structure

ARP-packages have a size of 28 bytes.

```txt
| Hardware Type (16 bits) | Protocol Type (16 bits) |
| Hardware Size (8 bits)  | Protocol Size (8 bits)  |
| Opcode (16 bits)                                  |
| Sender MAC Address (48 bits)                      |
| Sender IP Address (32 bits)                       |
| Target MAC Address (48 bits)                      |
| Target IP Address (32 bits)                       |
```

- **Hardware Type (16 bits)**: Specifies the type of hardware (e.g., Ethernet).

- **Protocol Type (16 bits)**: Specifies the type of protocol (e.g., IPv4).

- **Hardware Size (8 bits)**: Length of the hardware address (e.g., 6 for Ethernet).

- **Protocol Size (8 bits)**: Length of the protocol address (e.g., 4 for IPv4).

- **Opcode (16 bits)**: Indicates whether the message is a request (1) or a reply (2).

- **Sender MAC Address (48 bits)**: The MAC address of the sender.

- **Sender IP Address (32 bits)**: The IP address of the sender.

- **Target MAC Address (48 bits)**: The MAC address of the target (unknown in requests).

- **Target IP Address (32 bits)**: The IP address of the target.  

### Types of ARP Entries 

This are the types of entries in our cache.

- **Dynamic**: Updated via a broadcast request during the update process. 

- **Static**: Manually entered in the table via the **arp** command using the targets ip and mac-address: 

```bash 
arp -s ip_addr mac_addr
```

--- 

## Network Address Translation (NAT)

**NAT** is a method used in networks to translate private IP addresses to public IP addresses and vice versa. It allows multiple devices on a local network 
to share a single public IP-address when accessing the internet.

- **NAT** modifies the layer 3 (Network layer) header of the packets as they pass through a router or firewall, changing the source or destination IP address.

- **PAT (Port Address Translation)** modifies both the layer 3 (Network layer) and layer 4 (Transport layer) headers, changing the source or destination IP address 
and port numbers to allow multiple devices to share a single public IP address. We can use one IP-address and depending on the port redirect the data to the corresponding computer.

### Static vs Dynamic

- **Static**: Explicit mapping between pre-translation and post-translation attributes.

- **Dynamic**: Mapping is created on-the-fly as needed, without pre-configuration, but the admin defines the pre and post-translation attributes.
Only the translation is done by the device.

#### Static NAT

The purpose is to make an internal resource externally accessible.

- **Inbound packet**: destination is translated.

- **Outbound packet**: source is translated.

- Packets are translated in **both directions**.

- Does not conserve addresses, as each internal resource requires a unique public IP address.

#### Static PAT

Similar to the static NAT, but it also translates the port number.

- Multiple servers can use one public IP address, but they must use **different port numbers** to distinguish between them.

- Conserves address-space as mentioned in the introduction.

#### Dynamic NAT

The same as static NAT, but the mapping is created on-the-fly as needed, without pre-configuration, but the admin defines the pre and post-translation attributes.

- Mostly unused, as it does not conserve addresses and it is not flexible.

- Can be used for lazy static NAT.

#### Dynamic PAT

Is similar to the dynamic NAT, but it also translates the port number. Multiple servers can use one public IP address, but they must use different port numbers to distinguish 
between them. 

- Conserves address-space.

- Traffic is unidirectional, meaning that only **outbound** traffic is translated. Inbound traffic is not allowed unless a static mapping is created for it.

- The ports in the outbound side are also **randomized**.

- Each shared public IP address allows 65.000 simultaneous connections.

### Policy NAT

This is the **translation decision** based on matching both source and destination. For example given a packet with the destination 
address of `192.168.1.10` and the source address of `45.168.1.1`,  because our destination starts with `192.168.*.*` we decide to map our source in the router to 
`10.200.1.1` and then send the packet to the destination. This is a destination-based policy NAT. We can also have source-based policy NAT, where the decision is made based on the 
source address instead of the destination.

### Twice NAT

This is a combination of both source and destination-based policy NAT, where the decision is made based on both the source and destination addresses. 
For example, given a packet with the destination address of `192.168.1.10` and the source address of `45.168.1.1`, we can decide to map our source in the router to 
`10.200.1.1` and then send the packet to the destination. This is a twice NAT.

The use of this is for example when we have two companies with the same private IP address range and they want to communicate with each other, thus they need to use twice NAT 
to avoid address conflicts.

--- 

## What Arrives At A Computer at the other End?

After seeing the frames, packets and frames, we can know show how what arrives during an IPv4, TCP connection 

```txt 

-- Frame
| Hardware Type (16 bits) | Protocol Type (16 bits) |
| Hardware Size (8 bits)  | Protocol Size (8 bits)  |
| Opcode (16 bits)                                  |
| Sender MAC Address (48 bits)                      |
| Sender IP Address (32 bits)                       |
| Target MAC Address (48 bits)                      |
| Target IP Address (32 bits)                       |


-- Packet
+-------+-------+---------------+-------------------------------+
|Version|  IHL  | DSCP/ECN ToS  |         Total Length          |
+-------------------------------+-------+-----------------------+
|       Identification          |Flags  |    Fragment Offset    |
+-------------------------------+-------+-----------------------+
|      TTL      |   Protocol    |      Header Checksum          |
+---------------------------------------------------------------+
|                     Source IP Address                         |
+---------------------------------------------------------------+
|                  Destination IP Address                       |
+---------------------------------------------------------------+
|           Options (optional) + Padding (if needed)            |
+---------------------------------------------------------------+
|                         Payload (Data)                        |
+---------------------------------------------------------------+

-- Segment
| Source Port (16 bits) | Destination Port (16 bits)                                |
|                                                                                   |
|           Sequence Number (32 bits)                                               |
|                                                                                   |
|        Acknowledgment Number (32 bits)                                            |
|                                                                                   |
| Data Offset (4 bits) | Reserved (3 bits) | Flags (9 bits) | Window Size (16 bits) |
|                                                                                   |
|        Checksum (16 bits) |  Urgent Pointer (16 bits)                             |
```

--- 

## Sockets

**Sockets** are an abstraction provided by the operating system, i.e a software object/API; to enable communication
between different processes either on the same machine or over a network - They represent a connection between processes or computer. They act as
endpoints in a two-way communication channel. 

A socket is composed of: 

**Socket { Protocol, IP-address, Port Number, File Descriptor}**

When calling a socket API one mostly gets an object or just a file descriptor which references the region where the data is going 
to be put for transfer or receiving.

Sockets operate primarily at the **Transport** layer of the **OSI** model. They are called from the
**Application** layer asking to send or receive data. Then the socket wrap it via **TCP/UDP** and send it to
the **Network** layer.

They are handled by the operating system and commonly provided by **libc**.

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

## Internet Service Providers (ISP)

**ISP's** are companies and organizations responsible for providing the infrastructure for internet communications like: 
DNS-servers, cables, towers, routers, etc.

They can be classified into tiers:

- **Tier 1**: The big ones which provide the most part of the infrastructure and own large chunks of IP-addresses. Provide resources 
and infrastrucutre for connecting large networks together.

- **Tier 2**: Regional scale ISP's which mostly use resources of Tier 1 ISP's by paying.
Same task as the Tier 1, but on a smaller scale. 

- **Tier 3**: Responsible for connecting clients directly, they responsible for installing equipment.

As a consequence of this, the internet is a collection of autonomous systems.

--- 

## Virtual Local Area Network (VLAN)

**VLAN's** are used to separate a LAN into smaller chunks. The reasons for this are divers, but for example we can do this to 
separete concerns, limit broadcasts, avoid buying more switches and improving security. This works by assigning numeric **interfaces** to the different 
VLAN's in the **switch**. They are a **software-level-division**.

The way  VLAN is set up is by assigning sets of ports to specific the different VLAN's.
We can also create specific ports for connecting VLAN's.

- **Trunks** are access ports between different interfaces.

- **Tags** are used by switches to control traffic between VLAN's added by the switch in the frame.

- By default the VLAN is 1, but we can assign VLAN's for specific devices.

- VLAN's are mostly used for limiting broadcasts, explicit communication they are not taken into 
consideration. Hence, routers and hosts participating into host-to-host communication have access to all VLAN's.

- **Native VLAN's** are the default interface, mostly 1 which the switch assumes is for its VLAN which is 1.

--- 

## Spanning Tree Protocol (STP)

The **spanning tree protocol** is a way avoiding **broadcast-storms** caused from switches being connected to each other in a loop.
It works by designing a **root** switch and ports which are designated to traverse the switch-tree. Note that the goal is to make a 
minimal spanning tree.

- STP prevents loops by blocking redundant ports.

The protocol works as follows:

1. We use **BDPU** packets which are send from each switch across all ports. This helps us create our graph. 

2. The switch with lowest id becomes the root bridge. The lowest MAC-addresses.
   - All switches have the default priority value **32769**. 

3. All port on the root bridge are put in a forwarding state, and other switches in the topology must 
have a path to reach the root bridge.

4. Root ports are elected by the lowest path cost which determined by the medium's internet speed.

5. The remaining ports are then again blocked based on who hast the higher MAC-addresses.

This algorithm is basically a minimal spanning tree with costs optimization problem with additional rules for determining the root. It can  
also adapt under situation when one or multiple switches fail by electing a new root switch and re-computing the paths.

--- 

## Subnetting

**Subnetting** is the process of taking a network and dividing it into sub-networks **physically** unlike VLAN's which are **software-level-division**.

As a recap we need to know that in IPv4 the address consist on a network and host portion. The network portion is used for routing to the right network and the host portion for 
identifying the individual devices in the network.

### The Subnet Mask

To identify the network portion of the IP-address an **subnetmask** is used. It resembles an IP-address and reveals how many 
bits in the IP-address are used for the network by **masking (AND (1))** the network portion of the address.

It is a sequence of 4 octets which consists on the number of a sequence of 1 and zeros.

```txt
11111111.11111111.11111111.00000000 (bin)

255.255.255.0 (dec)
```

The portion which consists only of zeroes is the **host portion**. Those bits are free to be any number in the range 1 to 255 giving more 
addresses to work with inside the network.

The mask can be have different sizes depending on the network address. This is can be marked as `/x`, where x tells us how 
many bits starting from left to the right of the network address are being read.

```txt
11111111.11111111.11111111.00000000 -> /24
```

> When performing subnetting we will start setting ranges in the last octet the subnetmask affected.

### Classless Inter-Domain Routing (CIDR)

**Classless inter-domain routing** similar to subnetmask it is used to determine which portion of an IP-address is used network and host by giving
the number of bits to read relevant for the network portion from left to right `/x`. 

For example: `147.142.128.0 /17` read the first 17-bits.

Now we can have identical address but different in essence due to the different portions for host and network.
Also routers make their choices by using a **longest prefix match** on the routing table.


### Subnetworks

A **subnetwork** is a portion of an early physically not separated bigger network.

They are created by taking bits of the host portion of the IP-address and using them to identify 
subnets. This is accomplished by increasing the number of one's in the subnetmask.

Attributes of each sub-network:

- **Network ID** First IP address of the sub-network. 

- **Broadcast IP**: Last IP address in each sub-network.

- **Number of IP addresses**: Number of addresses in the sub-network.

- **First Host IP**: IP after the network ID.

- **Last Host IP**: IP before the broadcast IP.

- **CIDR/Subnet Mask**: Notation to represent the subnet mask. `11111111.11111111.11111111.00000000` can be represented as `/24` or `255.255.255.0`.

#### Host Size

Given a subnet mask, we can determine the number of host inside a network by raising 2 to the power of the number of zeros in 
the subnetmask minus 2 because the first address and last address are reserved for the network id and the broadcast address.

Example: 

We have the following address and subnet mask

```txt
180.62.91.0    255.255.255.0
```

Currently we can have up to 254 hosts, but we decide to create a subnet. We will just take the most 
significant bit of the host portion giving us the following mask: 

```txt 
11111111.11111111.11111111.10000000 -> 255.255.255.128
```

Now we have two subnets with $2^7 - 2 = 126$ **hosts** and $2^7$ addresses.

### Wildcard Mask

This is a subnetmask where the bits are inverted, meaning that the bits which are `1` in the subnet mask are `0` in the wildcard mask and vice versa. 
For example, if we have a subnet mask of `255.255.255.0`, the wildcard mask would be `0.0.0.255`.

### The Increment

The **increment** is the last positional power of 2 (starting from the left) in the current byte in the subnet-mask we which was flipped while subnneting.
This is used to determines the size of the subnets and the range of IP addresses in each subnet.

For example:

```md
11111111.11111111.11111111.00000000 -> /24
   gets converted to 
11111111.11111111.11111111.1**1**000000 -> /26 (255.255.255.192)
```

With increment: **64**. This means that the subnets will be created with a size of **64** addresses each.

### Block-Size 

The **block-size** helps determine the broadcast address of a network. We compute $256 - \text{mask-value}$, where the mask-value is the value of 
the first non-zero octet in the subnetmask. 

When found we start incrementing from the network address until we pass the original value. The broadcast address is the last address before the next network.
Like `0. 16, 32, 48, 64, 80, 96, 112, 128, 144, 160, 176, 192` and so on.

Example: 

Given the address `175.224.176.0` with the subnetmask `255.255.240.0`, find the broadcast address.

1. We compute our block-size $256 - 240 = 16$.
2. We increment until we get pass our original value `0, 16, 32, ..., 176, 192`. 
3. Hence, our broadcast is before the next network `.192` which implies that the bc-address is **175.224.191.255**

### Broadcast Address 

To get the broadcast address of any network we need to take the network address and add the block-size to the last octet of the network address. 
Then we subtract 1 from the last octet to get the broadcast address.

Example:

We are given the subnet `137.226.0.0 /17` and we need to find the broadcast address and the first and last host addresses.

We first need to find the block-size, which is $256 - 128 = 128$. Then we increment until we get pass our original value `0, 128, 256`.

- So the broadcast address is `137.226.127.255` since the next network is `137.226.128.0`.
- The first host address is `137.226.0.1`.
- The last host address is `137.226.127.254`.


### Performing Subnetting 

To get more subnetworks from our local network we need to work with our host portion of our address.

- **Number of Created Subnetworks**: $2^n$ where $n$ is the number of bit taken from the host-portion.

For example, if from our original network from one network to 4 networks we would do the following:

```txt
11111111.11111111.11111111.00000000 -> /24
   gets converted to 
11111111.11111111.11111111.11000000 -> /26 (255.255.255.192)
```

Example: 

Subnet the following network `192.168.1.0` to a 5 networks.

1. We need 5 networks which means that we need to flip 5 bits which will result into 8 networks

```txt
11111111.11111111.11111111.11100000 -> /27 (255.255.255.224)
```

Hence, our increment is **32** giving us the following addresses:

1. 192.168.1.0   to 192.168.1.31

2. 192.168.1.32  to 192.168.1.63

3. 192.168.1.64  to 192.168.1.95

4. 192.168.1.96  to 192.168.1.127

5. 192.168.1.128 to 192.168.1.159

6. 192.168.1.160 to 192.168.1.191

7. 192.168.1.192 to 192.168.1.223

8. 192.168.1.224 to 192.168.1.255

With a host size of $2^5 - 2 = 30$

The process can also be done based on the number of hosts which are going to be inside a subnetwork.

### Reverse Subnetting

Given a subnet mask and an IP-address we need to find the increment and relevant addresses.

This is better explained with an example: `172.17.16.255 / 255.255.240.0`

```md
255.255.240.0 

11111111.11111111.111**1**0000.00000000
```


Our increment is 16 

Now we can create our ranges 


1. 172.17.0.0 to 172.17.15.255
2. 172.16.0.0 to 172.17.31.255

and so on for for 14 times more or 16 in total.

### Subnetting Cheatsheet For Finding Subnet-Information


|Group Size (# of addresses) |128 | 64 | 32 | 16 | 8 | 4 | 2 | 1 |
|-----------|-----|-----|-----|-----|-----|-----|-----|-----|
|Subnet Mask| 128 | 192 | 224 | 240 | 248 | 252 | 254 | 255 |
|CIDR| /25 | /26 | /27 | /28 | /29 | /30 | /31 | /32 |
| Number of Bits to Flip |7 | 6 | 5| 4 |3 | 2 | 1 | 0 |


How it was calculated:

1. Start with 1, double until your reach 128 (right to left)
2. Subtract each number from 256 to get the subnet mask.
3. From /32, list CIDR notation until /25.

**Example:** 

Given `10.1.55.x /28` find all the sub-network information.

- We start with the CIDR notation, which is `/28`, hence we look at the cheatsheet and find that the subnet mask is `255.255.255.240`.

- Then we calculate the number of IP addresses in the sub-network, which is `2^(32-28) = 16`. Or the same as the group size.

- For the network ID we take the first 3 octets of the given IP address and starting from `0` we add the group size until we reach a number which is bigger than the given IP address 
at that octet. In our case we have `0, 16, 32, 48, 64`, hence the network ID is `48` because `48` is the biggest number which is smaller than `55`. The number after is the next network ID, which is `64`. 

- The broadcast IP is the last IP address in the sub-network, which is `10.1.55.63`.

- The first host IP is the IP address after the network ID, which is `10.1.55.49`.

- The last host IP is the IP address before the broadcast IP, which is `10.1.55.62`.

--- 

## Dynamic Host Configuration Protocol (DHCP)

The **Dynamic Host Configuration Protocol** provides a host with an IP-address, subnetmask, default gateway and domain name resolution server dynamically.
This is the protocol responsible for providing access to the internet when a device is connected to the internet by just plugin 
the ethernet cable or the wifi password.

They way this is accomplished using a server which is mostly the routers. 

- It is performed by the router's DHCP-server to assign private IP-addresses. 
- Computers run a DHCP-client to receive the IP-address from the router.
- Routers get a public IP-address assigned by the ISP. 

--- 

## What happens the first time a computer gets access to a network? 

Let us assume that we have a computer which has never been connected to any network and it is going make its first requests to 
a machine outside the network. 

1. The computer wants to send a packet, but it does not have a default gateway or knowledge about other devices. Hence it sends a broadcast asking 
for the MAC-address of the router and it has not IP-address.

2. It gets to the switch which redirects it to the router. 

3. The router determines that this machine needs a private IP-address and a DG for further communication, so it sends this data determined by DHCP server to our 
computer. 

4. The computer DG gets configured and the address of the switch is cached. 

5. Any further communication is done using the typical procedures like ARP, TCP, etc.

--- 

## Transmission Control Protocol / Internet Protocol (TCP/IP)

**TCP/IP** is a collection of protocol which determine how data
is formatted, transported and used in networks.

- **Application Layer**: Is the data which is going to be send.

- **Transport:**  This layer takes care of the transport of data across the network via protocols. It determines how much data to send,
how fast, if it was send correctly, etc.. Defines **Segments**.

- **Network:** It provides the functional and procedural means of transferring packages. It decides which physical path the data will take. It handles across
the routing of the data and the mapping from logical addresses and physical addresses. Defines **frames**.

- **Data Link:** It receives the data and packages it into frames which are going to be send to the respective targets. It can
also detect errors occurred at the physical layer and correct hem via algorithms. Defines **packets**.

- **Physical Layer**: Consists on the hardware components of the system.

### Frames, Packets And Segments

- A **frame** is a layer 2 PDU (Protocol Data Unit) which consists of a header, payload and trailer. 
The header contains the destination and source MAC addresses, while the trailer includes error-checking information (CRC).

- A **packet** is a layer 3 PDU (Protocol Data Unit) used in the network layer. It consists of a header and a payload. The header contains source 
and destination IP addresses, which are used for routing the packet across the network.

- A **segment** is a layer 4 PDU (Protocol Data Unit) used in the transport layer. It contains a header and a payload. The header includes information 
such as source and destination ports, sequence numbers, and acknowledgment numbers, which are essential for ensuring reliable data transfer.

#### Simplified depiction

```txt 
Data | Source port | Destination port | Protocol |  <- Segment
Data | Source port | Destination port | Protocol | Source IP | Destination IP |  <- Packet
Data | Source port | Destination port | Protocol | Source IP | Destination IP | Source MAC | Destination MAC |  <- Frame
```

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

## Uniform Resource Identifier (URI) / Uniform Resource Locator (URL) /Uniform Resource Name (URN)

A **URI/URL/URN** has the purpose of being a unique identifier to a resource in the internet.

$$\mathrm{URI} = \mathrm{URL} \cup \, \mathrm{URN}$$

- **URL**: locator to the information object with the specification of the protocol for communication.
- **URN**: locator to the information object without the specification of the protocol for communication.

Examples: 

```txt
URI: example.com
URL: http://www.example.com/datei.txt
URL: mailto:test@example.com
URL: ftp://127.0.0.1/dump.sql
URN: urn:isbn:0596517742
```

---

## Hyper Text Transport Protocol / Secure (HTTP & HTTPS)

**TCP** and **HTTPS** the **S** stands for **Secure** and refers to the data being encrypted; are state-less protocols
for sending data across the internet in text format. This is a TCP-based protocol which consists on the following 
life-cycle of a connection.

**Communication**: 

```txt
               CClient             Server 
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

If HTTPS is used the **TLS/SSL** handshake is performed after the TCP handshake and before the data transfer. 
This ensures that the data is encrypted and secure.


```txt 
               CClient          Server 
               ------           ------
               |                  |
TCP Handshake  | SYN              |
               |----------------->|
               |                  |
               |  SYN ACK         |
               | <----------------|
               |                  |
               |  ACK             | 
               |----------------->|
               |                  |
TLS Handshake  |   Client Hello   |
               |----------------->|
               |                  |
               |   Server Hello   |
               | <----------------|
               |                  |
               |   Certificate    |
               | <----------------|
               |                  |
               |   Key Exchange   |
               | <----------------|
               |                  |
HTTP/HTTPS     |   Data Transfer  |
(Data Transfer)|<---------------->|
               |                  |
```   

### Syntax Of A HTTP URL

Example syntax bellow, this can vary depending on the implementation.

```http 

http://<user>:<password>@<host>:<port>/<url-path>?<query-parameter>


http://user:pw@example.com:80/datei.html?q=123
```


### Headers 

An HTTP header is a field of an HTTP request or response that passes additional context and metadata
about the request or response. 

Example: 

```http 
content-type:text/html 
http-method:GET
```

### Status Code

In this protocol a **status code** needs to be send to describe the status of the operation. 

- **1xx**: Informational
- **2xx**: The request was successful.
- **3xx**: The client is redirected to a different resource.
- **4xx**: The request contains some kind of error.
- **5xx**: THe server errored while fulfilling the request.

### Request

An **HTTP request** is a message sent by a client to a server to initiate an action or retrieve information. It consists of 
several components, including the request line, headers, and an optional body.

```http 
method sp URL sp version cr if 
header field name: value cr if 
...
header field name: value cr if 
cr if 
   Body

```

Example: 

```http
GET https://www.fh-aachen.de/ HTTP/1.1
Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
Accept-Encoding: gzip, deflate, br
Accept-Language: de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7
Cache-Control: no-cache
Connection: keep-alive
Cookie:_pk_ref.4.19d4=%5B%22%22%2C%22%22%2C1670832293%2C%22https%3A%2F%2Fwww.google.com%2F%22%5D;
_pk_id.4.19d4=4115fa9a7f694583.1670832293.; fhac_cookiemodal-selection=[%22essential%22%2C%22analytics%22%2C%22search%22];
fe_typo_user=bf03b5cab5fc0cdae56a04e56a4413a5
Host: www.fh-aachen.de
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.0.0.0 Mobile Safari/537.36
```

### Response

**Response** syntax:

```http 
version sp status code sp phrase cr if 
header field name: value cr if 
...
header field name: value cr if 
cr if 
   Body

```

Example:

```http
HTTP/1.1 200 OK
Connection: keep-alive
Content-Encoding: gzip
Content-Language: de
Content-Length: 13083
Content-Type: text/html; charset=utf-8
Date: Mon, 06 Feb 2023 09:17:41 GMT
Server: nginx/1.18.0 (Ubuntu)
Strict-Transport-Security: max-age=31536000
<!DOCTYPE html>
<html>
...
```

### HTML Example With Form 

```html 
<form action="do.php?q=login" method="post">
   <input type="text" name="username" />
   <input type="password" name="pw" />
   <input type="submit" value="Login" />
</form>
```


This will generate: 

```http 
POST /do.php?q=login HTTP/1.1
Host: www.example.com
...
Content-Type: application/x-www-form-urlencoded
Content-Length: 31
Connection: keep-alive
username=vosa&pw=supersecret123
```

### Mutiplexing

The **multiplexing** implemented from HTPP 2.0 allows to send multiple requests without always waiting for a response. A **resquest-stream** 
is open until a `END_STREAM` flag is set to end the close it. The same goes for the responses.

The key difference to **pipelining** is that the responses do not need to be in the same order as the request were sent.

### QUIC

**QUIC** is a UDP-based protocol which supports TLS and is used for HTTP 3.0 along side the classic TCP protocols used for 
HTTP.

--- 

## Transport Layer Security (TLS) & Secure Sockets Layer (SSL)

**SSL/TLS** creates a secure, protected "tunnel" across the internet via encryption, hashing and the public key infrastructure to ensure 
confidentiality, integrity and authentication. The acronyms refer to 2 version of the same protocol.

### Actors

- **Client**: 
   - Entity initatin the TLS handshake.
   - Optionally authenticated.

- **Server**:
   - Entity receiving the the TLS handshake.
   - Always authenticated.

- **Certificate Authority**:
   - Provides certificates for servers.
   - The generated certificate lins an asymmetric key parit to a specific indentity.
   - The certificate is also signed by the CA.

The combination of these 3 is called a **PKI public key infrastructure**.

### Certificates

**Certificates** are a cryptographic signs which are used to verify the identity of a server. They are sold by trusted organizations.

- The server generates its own set of private and public key. Then it generates a **Certificate Signing Request (CSR)** which includes the 
**public key** and it is signed with the **private key of the server**.

- The certificate autority (CA) provides a signed certificate with a **public and private key for the server**.

- The CA inspects and validates the certificate. The certificate is signed with the **private key of the CA**. It also includes the public key of the server.

- The server can use the certificate to validate its identity.

- Clients already have a signed certificate which includes the **public key of the CA**.

- The clients requests the certificate of the server by checking the sign with the **CA's public key**.

### TLS/SSL Handshake

Previous to the hand shake a TCP connection is established using the three-way handshake. 

1. The client sends a hello-message to the server which includes meta data and the encryption supported. 

2. The server reads the meta data and chooses an encryption algorithm. The algorithm, a public key and the certificate are send to the client.

3. The client checks the validity of the certificate. 

4. If the certificate is valid, it generates a random session key which is encrypted with the servers public key and send to him (RSA). 
Now that both parties have the same seed values, this is used to generate the private key pairs for symmetric encryption. There are two pairs 
due to one being used for the server-to-client and the other for the client-to-server communication.

It is also important to notice that instead of RSA the Diffie-Dellman exchange is used for the generation of the shared secret.

5. The server decrypts the session key and sends a finish message. This includes a digest of all the other messages. 

### HTTP Strict Transport Security HSTS

**HSTS** instructs the browser that a site should always be HTTPS. This ensures that SSL can not be fooled 
by tricks like having a man in the middle acting as the server.

This is accomplished via a the `max-age` directive in http requests which ensures that a maximum time of response 
needs to specified for the the site.

Example:

```http 
Strict-Transport-Security: max-age=63072000
Strict-Transport-Security: includeSubDomains
Strict-Transport-Security: preload 
```

Because of the first visit still being vulnerable. A concept called **HSTS Preload** was developed, which 
consists on a static list of HSTS sites maintained by the browsers locally.

--- 

## Content Delivery Networks (CDN)

A **content delivery network (CDN)** connects different services and delivers content in form of static resources, libraries, or a service 
to distribute load and data more efficiently. They consist mostly on a series of proxy servers connected to a specific data center.

They work by stablishing a series of geographically scattered **edge-servers** which cache the contents of an service and local data. The agglomerations of 
this server is calle a **point of presence (POP)**. 

The improve availability and speed, but reduce the consistency of the data since, it is virtually impossible to have all of the three at the 
same time.

--- 

## Fragmentation

**Fragmentation** refers to the splitting of datagrams due to capacity constraints in the physical or 
logical medium for transmitting information. The only obligatory unit of transmition in the internet are datagrams of **576 bytes in total**.
The **IP-header** helps keeping the order of the datagrams by adding both a sequence number for the order and flags for signaling if more datagrams are comming.

```text
+-------+-------+---------------+-------------------------------+
|Version|  IHL  | DSCP/ECN ToS  |         Total Length          |
+-------------------------------+-------+-----------------------+
|       Identification          |Flags  |    Fragment Offset    |
+-------------------------------+-------+-----------------------+
|      TTL      |   Protocol    |      Header Checksum         |
+--------------------------------------------------------------+
|                     Source IP Address                        |
+--------------------------------------------------------------+
|                  Destination IP Address                     |
+--------------------------------------------------------------+
|           Options (optional) + Padding (if needed)          |
+--------------------------------------------------------------+
|                         Payload (Data)                      |
+--------------------------------------------------------------+
```

- **Maximum Payload**: $\text{MP} = \text{MTU} - \text{Header Size}$

- **Multiple Of 8**: $\mathrm{floor}\left(\frac{MP}{8}\right) * 8$

- **Fragment Offset**: $\frac{\text{Bytes before this fragment}}{8}$ **only the cumulative payload without header!**

- **MF** : 1 if more fragments 0 for the final fragment. 

Example:

We have a total payload of **4200** bytes we want to from A to R and from R to B with a MTU's of 1800 and 1200 bytes respectively.


Our first MP is $1800 - 20 = 1780$. We compute our frament size of $1776$ bytes. Our actual payload is $4200 - 20 = 4180$, hence we have: 

We have the following sizes: 

- 1776 
- 1776 
- 648


| Fragment | Length | Payload | Offset | MF | 
|----------|--------|---------|--------|----|
| F1 | 1796 | 1776 | 0 | 1 | 
| F2 | 1796 | 1776 | (1776 / 8) = 222 | 1 | 
| F3 | 648 | 628 | (3552/8) = 444 | 0 | 


Four our second step we have a MP of $1200 - 20 = 1180$ which after divided by 8 an rounded down gives us a size of $1176$ now we need to compute for 
each of our previous fragments their respective fragmentation. 

For **F1**: 

- 1176 
- 600


| Fragment | Length | Payload | Offset | MF | 
|----------|--------|---------|--------|----|
| F1.1 | 1196 | 1176 | 0 | 1 | 
| F2.2 | 620 | 600 | (1176 / 8) = 147 | 1 | 


For **F2**: 

The sizes are the same but the offset changes 


| Fragment | Length | Payload | Offset | MF | 
|----------|--------|---------|--------|----|
| F2.1 | 1196 | 1176 | (1776/8) = 222 | 1 | 
| F2.2 | 620 | 600 | (2952 / 8) = 369 | 1 | 



For **F3**: 

Since its size is smaller than the MTU it just gets redirected 


| Fragment | Length | Payload | Offset | MF | 
|----------|--------|---------|--------|----|
| F3 | 648 | 628 | 444 | 0 | 



--- 

## Internet Control Message Protocol (ICMP)

**ICMP** is a protocol used for handling the lifetime and actions to take for IP packets under normal and exceptional situations, like:
how long does a package live until it gets discarded, a packet did not arrive, should it be re-sended, etc.

The header has the following structure: 

```txt 
| IP Header                    |
| Type / Code | Checksum       | 
| Identifier | Sequence Number | 
| Optional Data                |
```

- **Type/Code**: informs about the type of the message like: 

   - `0`: Destination unreachable (can not send the packet)
   - `3`: Echo Request/Reply (used by ping)
   - `4`: Source Quench (Choke-packet, reduce the datarate)
   - `11`: Time exceeded for Datagram (TTL reaced 0).
   - `12`: Parameter Problem on Datagram (a header field is wrong)
   - `15/16`: Information Request/Reply 
   - `30`: Traceroute (TTL does not work)

--- 

## Domain Name System (DNS)

**Domain Name System** is set protocol and infrastructure used for mapping **domain names** in plain text to actual **IP-address** of a server.

Important facts: 

-  For the time of this writing, there are 13 root servers. 

- **Zones** are defined areas of the IP-namespace which are handled by one or multiple specific servers.

- The IP-address of the resolver of the **resolver** is hard-coded into the router by the internet service provider (ISP). 
Then it goes for the address of the **root**, **tld** and **authoritative name** server in the **resolver**.

- The **stub resolver** is the client DNS-server running in your computer. 

- The **recursive resolver** is a DNS-server which does not know the IP-address if not chached but it knows the addresses of the **root** servers. 

- **Root Servers** know the right **authoritative name server (ANS)** servers to ask for the given IP-address. 

- The **ANS** is the one server containing the actual IP-address which knows the targets ip address.

- In DNS there are always more than one server for each servers to maximize availability.

### Root Servers 

The **root** name servers are which are responsible for the hidden final `.` at the end of each domain name. 

### Steps

1. The **resolver** checks the cache and if the IP is not in the cache a request is triggered to hard-coded IP-address of the one program used to 
ask for the domain.

2. A request is triggered to the recursive resolver which will the **root** `.` server of an specific **top level domain** like `.com`

3. The root server returns the address od a **top-level-domain (TLD)** server or resolver. To which a request is send.

4. The resolver's request is redirected to an specific **Authoritative Name Server (ANS)** which always will have the IP-address if registred.

5. The address is given to recursive resolver which caches the address. 

6. The resolver returns the IP to the computer which can now make a request. 

### Structure 

- **Top Level Domain**: This is the portion at the end of the url commonly: `.com, .org, .io`
- **Second Level Domain**:
- 

```text 
   www.aaaaaaaaaaaaaaaaaa.google.com
   |           |             |
Subdomain   2d-domain    Top level domain
```


### DNS Zones 

A **DNS zone** is a section of a domain name space that a certain administrator has been delegated control over.

### Zone Files 

**Zone files** are the files which contain the mapping of domain names to IP-addresses. They are used by the **Authoritative Name Servers** to resolve domain names.

It is composed of different parts: 

- **$ORIGIN**: This is the domain name of the zone file. It is used to specify the domain name for which the zone file is authoritative.
- **$TTL**: This is the time to live for the zone file. It is used to specify how long the zone file should be cached by the resolver.
- **SOA (Start of Authority)**: This record indicates the authoritative DNS server for the zone.
- **NS (Name Server)**: This record specifies the authoritative name servers for the zone.
- **A (Address)**: This record maps a domain name to an IPv4 address.
- **AAAA (IPv6 Address)**: This record maps a domain name to an IPv6 address.
- **CNAME (Canonical Name)**: This record creates an alias for a domain name.
- **MX (Mail Exchange)**: This record specifies the mail servers for the domain.

This parts are called **Resource Records** and they are used to map domain names to IP-addresses.

- **Structure of a record**

```txt
OWNER CLASS TYPE VALUES
```

Example: 

```txt
$ORIGIN example.com. 
$TTL 86400 
@	IN	SOA	dns1.example.com.	hostmaster.example.com. (
			2001062501 ; serial                     
			21600      ; refresh after 6 hours                     
			3600       ; retry after 1 hour                     
			604800     ; expire after 1 week                     
			86400 )    ; minimum TTL of 1 day  
		     
		           
	IN	NS	dns1.example.com.       
	IN	NS	dns2.example.com.        
	
	
	IN	MX	10	mail.example.com.       
	IN	MX	20	mail2.example.com.        

	
dns1	IN	A	10.0.1.1
dns2	IN	A	10.0.1.2	

			       
server1	IN	A	10.0.1.5        
server2	IN	A	10.0.1.6

       
ftp	IN	A	10.0.1.3
	IN	A	10.0.1.4
	
mail	IN	CNAME	server1
mail2	IN	CNAME	server2


www	IN	CNAME	server1
```

#### Typical Records

- *A*: maps a domain name to an IPv4-address.
- *AAAA*: maps a domain name to an IPv6-address.
- **CNAME (canonical name)**: resolves a domain or subdomain to another domain name.
- **MX**: uses for mail exchage. 
- **SOA**: it stands for start of authority a stored administrative information for a zone.
- **NS**: provides the name of the authoritative name server within a domain.
- **SRV**: points to a server and a service by including a port number. 
- **PTR**: maps an IP-address to a domain name. It can be used to check the authenticity of an email.

--- 

## SSH

Secure shell is a protocol used for providing a secure encrypted connection to a remote machine. It uses asymmetric encryption
and runs commonly on **port 22**. It uses either a password or asymmetric encryption for connection without using a password.

### Process 

1. **Stablish a TCP connection**: typical process. 

2. **SSH Version Check**: Check if both server and host are using the same SSH version. 

3. **Key Exchange process**: Diffie-Dellman key exchange in most cases.

4. **Server authentication**: The server returns its public key to the client which is added to the file `/home/user/.ssh/known_hosts`.

5. **Client Authentication**: The server checks the password given by the client.

6. **Start of the actual SHH**

### Tunneling 

SSH allows to stablish a secure connection which is then used for sharing data and commands directed to other applications in the system.

### Layout Of An SSH Packet

```txt
| Packet length -- Padding Amount -- Payload Padding -- Message Authentication |
```

- **Packet Length**: Size of the package including the headers.
- **Padding Amount**: Bruh.
- **Payload**: Actual Data.
- **Message Authentication**: Cryptographic code.

Everything between packet length and message authentication is encrypted with asymmetric encryption.

Example use case: 

- **Creating key**:

```bash 
ssh-key-gen
```

- **Sharing The Key**:

```bash 
ssh-copy-id <host>
```

- **Adding SSH to skip enter the passphrase for the Key**:

```bash 
ssh-add
```

- **Connecting**:

```bash 
ssh <user>@<adresss of te host>
```


--- 

## Node

A **node** is a device that implements IPv6.

---

## Repeater

A **repeater** its a device which regenerates signals, it is used to prevent signal decay.

---

## Ethernet

**Ethernet** is a family of networking technologies used for LANs. It is concerned with the physical and data link layers.
For example, it defines the frame structure, the MAC addressing, and the method of access to the shared medium (CSMA/CD).

- **Ethernet frames** consist of a header, payload, and trailer. The header contains the destination and source MAC addresses, while the trailer includes error-checking information (CRC).

- **CSMA/CD (Carrier Sense Multiple Access with Collision Detection)** is a protocol used in Ethernet networks to manage access to the shared communication medium. It allows devices to detect collisions and retransmit data when necessary, ensuring efficient communication in a network with multiple devices.

- **Ethernet Cable**: is a type of network cable used to connect devices in an Ethernet network. It typically consists of twisted pairs of copper wires and is used for wired connections.

--- 

## Network Architecture

This term refers to the way a network is structured which can be mostly categorized into 3 tiers depending on the number of layers.

- **Access Layer**: The individual devices connected to one of multiple switches, which are connected to the router/s. Cheap, but fragile for 
businesses use except for very small stores. Used for homes. (**Tier 1**).

- **Distribution Layer**: In this layer one or multiple **distribution switches** are connected to the ordinary the switches. They act as the 
in between the layer to distribute traffic accordingly from the routers. More expensive, but also more reliable. Suited for small to medium size businesses.
(**Tier 2**).

- **Core Layer**: Adds an even more powerfull to distribute the traffic even more efficient. Expensive and only for big businesses. (**Tier 3**).

--- 

## Complete Data Flow in a Network Communication

We have two networks with switches and routers, and a computer in each network. The data flow for a communication between the two computers would be as follows:


```txt
                     DNS Server + Other Servers
                             |
                             | 
      Computer A (Source)    |                    Computer B (Destination)
      -----------------      |                    -----------------
                |            |                              | 
                |            |                              |
Computer 2 --- Switch A      |                         Switch B --- Other Computer
                |            |                              |
                |            |                              |
             Router A _______|                            Router B
                |                                           |
                |                                           |
             Internet                                    Internet
                |                                           |
                |___________________________________________|
```

1. Computer A wants to communicate with Computer B, but it only knows the domain name of Computer B. 
It sends a DNS query to the DNS server to resolve the domain name to an IP address. This is done by sending 
a sending a UDP packet to the switch A, which then forwards it to Router A, which then sends it to the DNS server.

2. The DNS server responds with the IP address of Computer B, which is sent back to Computer A through the same path.

3. Now that Computer A has the IP address of Computer B, it can send data to Computer B. It creates a TCP connection to Computer B's IP address and sends the data.
This TCP packet is sent to Switch A, which forwards it to Router A, which then sends it through the internet to Router B, which then forwards it to Switch B, and finally to Computer B.

4. Computer B receives the TCP packet, processes it, and can send a response back to Computer A using the same path in reverse.

--- 

## Firewall

A **firewall** is a system which prevents incoming connections from external computers. By default they completely block the whole traffic unless 
**rules** are modified. These rules allow control over which IP-address and ports are allowed inside the network.

Most firewall are **stateful** which means that once traffic from the inside of the network to the outside is allowed, then the reponses from those sources are 
automatically allowed inside the farawall's rules. More modern firewalls also have capabilities of blocking emails by content, patterns, etc.

--- 

## File Transfer Protocol (FTP) 

**FTP** is the standard for exchanging files commonly on port **21**. The setup is done by setting up a server 
with a number of files accessible for user which should have **no rights** for modifying the server except for viewing and downloading.

- The domain looks like `ftp.some_computer.com` or `ftp://192.12.43.1`

- The data is in plain text.

- **SFTP** is FTP but with encryption.

- FTP are connection oriented (TCP).

- **TFTP** is a protocol done for transfering file in a local area network and it is connectionless.

--- 

## Simple Mail Transfer Protocol (SMTP)

**SMTP** is a protocol used for sending emails. 

An email is sent to the SMTP server of the sender which forwards the email to the SMTP server of the receiver to then 
be finally sent to the receiver's computer.

- It uses TCP. 

### MIME

**MIME** is a standard for formatting email messages to support text in character sets other than ASCII, as well as attachments of audio, video, images, and application programs.
It works by adding headers to the email message that specify the type of content being sent, as well as the encoding used to represent that content.

Example:

```txt
MIME-Version: 1.0
Content-Type: multipart/mixed; boundary="boundary_string"
--boundary_string
Content-Type: text/plain; charset="UTF-8"
This is the body of the email message.
--boundary_string
Content-Type: image/jpeg
Content-Disposition: attachment; filename="image.jpg"
[Binary data of the image]
--boundary_string--
```

The binary data is encoded using base64 or quoted-printable encoding to ensure that it can be transmitted over email protocols that may not support binary data.

--- 

## Load Balancers 

A **load balancers** is a piece of software or hardware used to distribute work in a computer network. For example to redistribute 
request to a service across multiple severs.

The techniques used for this can be either **static** which are fixed rules which do take into consideration the state of the servers or **dynamic** which 
do distribute work according to compute power, which servers has more work, etc.

--- 

## Websockets

**Websockets** is a way of stablishing a duplex connection between a frontend and backend for an 
even-driven data request. This is ideal for real-time applications.

It works as following 

1. The client performs an HTTP-request for stablishing a websockets connection.

2. The servers agrees an switches the protocol 

Now both computers share a two-way connection which is based on events.

--- 

## Cookies

**Cookies** are a small piece of data sent from a website and stored in the user's web browser while the user is browsing. They are designed to be a reliable mechanism 
for websites to remember stateful information or to record the user's browsing activity. The format mostly consists on a key-value pair with a name, value, expiration date, path, domain, and security flags.

```http
Set-Cookie: <name>=<value>; Expires=<date>; Path=<path>; Domain=<domain>; Secure; HttpOnly; SameSite=<samesite>
```

Cookies are always sent to the server with every request to the same domain, which allows the server to identify the user and maintain session state.

--- 

## Authentication

**Authentication** is the process of verifying the identity of a user or system.  

### Bearer Token

A **bearer token** is a type of access token called a "bearer" token because the client must "bear" 
the token in order to access the protected resource. The token is typically included in the HTTP request header as follows:

```http
Authorization: Bearer <token>
```

The token is usually a long string of characters that is generated by the server and sent to the client.

### JSON Web Token (JWT)

A **JSON Web Token** is a token which is compact, URL-safe means of representing claims to be transferred between two parties. The token consists of three parts: 

- **Header**: Which specifies the algorithm used for signing the token and the type of token.
- **Payload**: The claims or statements about an entity (typically, the user) and additional metadata.
- **Signature**: The cryptographic signature used to verify the integrity of the token and the authenticity of the sender.

```json
Header: 
{
  "alg": "HS256",
  "typ": "JWT"
}
Payload:
{
  "sub": "1234567890",
  "name": "John Doe",
  "iat": 1516239022
}
Signature:
HMACSHA256(
  base64UrlEncode(header) + "." +
  base64UrlEncode(payload),
  secret
)
```

### OAuth 2.0

**OAuth 2.0** is an authorization framework that allows third-party applications to obtain limited access to a user's resources without exposing their credentials. 
It works by issuing access tokens to the client application, which can then be used to access protected resources on behalf of the user.

This is used for example, when we want to login to a website using our Google or Facebook account. The website does not need to know our password, it just needs to get an access token from Google 
or Facebook to access our profile information.

#### Protocol Flow

1. The client application requests authorization from the user to access their resources.

2. The user grants authorization and the client application receives an authorization code.

3. The client application exchanges the authorization code for an access token from the authorization server.

4. The client application uses the access token to access the user's resources from the resource server.

5. The access token has a limited lifespan and can be refreshed using a refresh token, if provided.

The format of the access token is usually a JSON Web Token (JWT) or an opaque token, which is a random string that has no meaning to the client application.

--- 

## Authorization

**Authorization** is the process of determining whether a user or system has permission to access a resource or perform an action. It always comes after authentication.

### Attribute-Based Access Control (ABAC)

**Attribute-Based Access Control (ABAC)** is a model for controlling access to resources based on attributes of the user, resource, and environment. Mostly accomplished by 
utulizing the attributes of entities at the **data layer** to determine access rights.

Example: A user with the attribute "role=admin" can access all resources, while a user with the attribute "role=user" can only access resources that are marked as "public".

### Access Control Lists (ACLs)

**Access Control Lists (ACLs)** are a list of permissions attached to an object that specifies which users or systems are granted access to that object and what operations they can perform.
For example, an ACL for a file might specify that user A has read and write access, while user B has read-only access.

They are commonly used in file systems, network devices, and operating systems to control access to resources, not really scalable for large systems; only systems with a small number of users and resources.

Example:

```txt
File: /home/user/file.txt
Owner: user
Permissions:
user: read, write
group: read
other: none
```

### Role-Based Access Control (RBAC)

**Role-Based Access Control (RBAC)** is a model for controlling access to resources based on the roles assigned to users. Each role has a set of permissions that define what actions can be 
performed on which resources. The roles are handled by the **application layer** and are used to determine access rights.

Example: A user with the role "admin" can access all resources, while a user with the role "user" can only access resources that are marked as "public".


### Delegation of Authority

**Delegation of Authority** is a process by which a user or system can delegate their access rights to another user or system. This allows for temporary or limited access to resources without
granting full access to the delegating user or system. It is commonly used in scenarios where a user needs to grant access to another user for a specific task or time period.

A common case of this practice is with OAuth 2.0, where a user can grant access to their resources to a third-party application without sharing their credentials.

--- 

## Session Management

A **session** is a way to maintain state between a client and a server across multiple requests. They are not 
directly supported by the HTTP protocol, which is stateless. Sessions are typically managed using session IDs stored in cookies or URL parameters.
These session IDs have a limited lifespan, once expired, the session is no longer valid.

They are handled by the **server** which generates a unique session ID for each user and stores it in a database or memory. The session ID is then sent to the client as a cookie or URL parameter, 
which is included in subsequent requests to the server. This sessions IDs should be **randomly generated** and **hard to guess** to prevent session hijacking. 

It is a good practice to delete the session after a certain period of inactivity or when the user logs out.

--- 

## Wireless Access Point (WAP)

This devices are used to repeat the signal from the router with a cable, so that 
we can extend the range of the signal. 

--- 

## Repeaters 

Unlike WAP's which use a direct connection from th router, **repeaters** only re-amplify the waves for them to 
have a larger range.

---

## Data Link Layer Technologies

The **data-link layer** has the job of preparing the data for the physical layer and checking for errors during the transmission process.

Common technologies in this layer include: 

- Checksums
- Error correction codes like Hamming code.
- ARP
- MAC-addresses.

### Logical Link Control (LLC)

It establishes path for devices in a network to share information. 

### Media Access Control (MAC)

Provides the indentifiers for the devices in the local network.

### Carrier Sense Multiple Access with Collision Detection (CSMA/CD)

**CSMA/CD** is used as a standard to reduce data-collisions. It works as follows: 

- It checks for data in the medium, if there is none its send the first bit.
- If the bit is send without collisions it sends the next bits while always checking for collisions.
- If a collision occurs then it computes a waiting time before the bit gets re-send.

It is deprecated currently almost all cables support duplex-connections, therefore, collisions do not happen anymore.

### Hamming Codes 

**Hamming codes** are a method of error detection and correction that can detect and correct single-bit errors in data transmission. 
They work by adding redundant bits to the original data, allowing the receiver to identify and correct errors.

### Checksums

**Checksums** are a simple form of error detection that involves calculating a value based on the data being transmitted. 
The sender computes the checksum and appends it to the data. The receiver recalculates the checksum upon receiving the data and 
compares it to the transmitted checksum to verify data integrity.

--- 

## Ethernet

**Ethernet** is a set of wired-communication standards. They use frames for communication over the medium.

It mostly used **twisted pair cables** which consist of 4-color wires twisted with or without a shield.

---