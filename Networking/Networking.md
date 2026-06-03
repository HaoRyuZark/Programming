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

- **Chordale Ring**: Ring with some tetradic connection inside.

- **Barrel Ring**: Ring where also each node is connected to another if they are separated by two nodes.

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
- TCP/UDP Ports (addressing)

3. **Network:** It provides the functional and procedural means of transferring packages. It decides which physical path the data will take. It handles across
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
to limited 2^32. They are 128-bit long with 2^128 possible addresses

- Divided into 8 segments of 16 bits, hextets.
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

`10.0.0.0/8`, `172.16.0.0/12`, `192.168.0.0/16` are the private IP ranges, which are reused across different local networks, 
thus they are not unique globally.


|Classs | Range | Subnetmask |
|:-----:|--------|-----------|
|A | 10.0.0.0 - 10.255.255.255 | 255.0.0.0 |
|B | 172.16.0.0 - 172.31.0.0| 255.255.0.0 |
|C | 192.168.0.0 - 192.168.225.255.255 | 255.255.255.0 |


- **Public**: 
   - Assigned by the internet service provider for the router.
   - It is also unique.
   - Routable for the internet.

The process which translates from private to public and vice versa is the so called **Network Address Translation (NAT)**, which 
does exactly what the name implies and adds a layer of security by masking the private address.

> No traffic between private to private is allowed, but traffic between private to public and public to private is allowed.

### Classes of IPv4 


|Classs | Range | Subnetmask | Purpose |
|:-----:|--------|-----------|----------|
|A | 1.0.0.0 - 126.255.255.255 | 255.0.0.0 | |
| loopback | 127.0.0.0 - 125.255.255.255 | 255.0.0.0  | |
|B | 128.0.0.0 - 191.255.0.0| 255.255.0.0 | |
|C | 192.0.0.0 - 223.255.255.0 | 255.255.255.0 | |
|D | 224.0.0.0 - 239.255.255.255 | | |
|E | 240.0.0.0 - 255.255.255.255| | |


### Static and Dynamic IPs

- **Static**:
   - Do not change
   - Are manually assigned by an admin.
   - Ideal for hosting servers and long-term services.

- **Dynamic**:
   - Dynamically assigned by a network.
   - Flexible.
   - Widely used for consumer devices.

### Assignment Of Ip Addresses

- **Automatic Prive IP Adressing**: uses 169.254.0 to 169.254.255.255 without the first and last 256 adresses. It uses ARP to check than an adress is not in used in the 
local network.

---

## Network Address Translation NAT

**NAT** is a method used in networks to translate private IP addresses to public IP addresses and vice versa. It allows multiple devices on a local network 
to share a single public IP address when accessing the internet.

- **NAT** modifies the layer 3 (Network layer) header of the packets as they pass through a router or firewall, changing the source or destination IP address.

- **PAT (Port Address Translation)** modifies both the layer 3 (Network layer) and layer 4 (Transport layer) headers, changing the source or destination IP address and port numbers to allow multiple devices to share a single public IP address.

### Static vs Dynamic

- **Static**: Explicit mapping between pre-translation and post-translation attributes.
- **Dynamic**: Mapping is created on-the-fly as needed, without pre-configuration, but the admin defines the pre and post-translation attributes.
Only the translation is done by the device.

### Static NAT

- The purpose is to make an internal resource externally accessible.
- Inbound packet: destination is translated.
- Outbound packet: source is translated.
- Packets are translated in both directions.
- Does not conserve addresses, as each internal resource requires a unique public IP address.

### Static PAT

- Similar to the static NAT, but it also translates the port number.
- Multiple servers can use one public IP address, but they must use different port numbers to distinguish between them.
- Conserves address-space.

### Dynamic NAT

The same as static NAT, but the mapping is created on-the-fly as needed, without pre-configuration, but the admin defines the pre and post-translation attributes.

- Mostly unused, as it does not conserve addresses and it is not flexible.
- Can be used for lazy static NAT.

### Dynamic PAT

Is similar to the dynamic NAT, but it also translates the port number. Multiple servers can use one public IP address, but they must use different port numbers to distinguish between them. 
Conserves address-space.

- Traffic is unidirectional, meaning that only outbound traffic is translated. Inbound traffic is not allowed unless a static mapping is created for it.
- The ports in the outbound side is also randomized.
- Each shared public IP address allows 65.000 simultaneous connections.

### Policy NAT

This is the **translation decision** based on matching both source and destination. For example given a packet with the destination 
address of `192.168.1.10` and the source address of `45.168.1.1`,  because our destination starts with `192.168.*.*` we decide to map our source in the router to 
`10.200.1.1` and then send the packet to the destination. This is a destination-based policy NAT. We can also have source-based policy NAT, where the decision is made based on the source address instead of the destination.

### Twice NAT

This is a combination of both source and destination-based policy NAT, where the decision is made based on both the source and destination addresses. 
For example, given a packet with the destination address of `192.168.1.10` and the source address of `45.168.1.1`, we can decide to map our source in the router to 
`10.200.1.1` and then send the packet to the destination. This is a twice NAT.

The use of this is for example when we have two companies with the same private IP address range and they want to communicate with each other, thus they need to use twice NAT to avoid address conflicts.

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

## Subnetting

**Subnetting** is the process of taking a network and dividing it into sub-networks.

Attributes of each sub-network:

- **Network ID** First IP address of the sub-network. 

- **Broadcast IP**: Last IP address in each sub-network.

- **Number of IP addresses**: Number of addresses in the sub-network.

- **First Host IP**: IP after the network ID.

- **Last Host IP**: IP before the broadcast IP.

- **CIDR/Subnet Mask**: Notation to represent the subnet mask. `11111111.11111111.11111111.00000000` can be represented as `/24` or `255.255.255.0`.

### The Subnett Mask

The **subnetmask** tells us whihc part of the IP-address is a part of the **network address**. It is a sequence of 4 octes which 
consists on the number of a sequence of 1 and zeros.

```txt
11111111.11111111.11111111.00000000 (bin)

255.255.255.0 (dec)
```

The portion which consists only of zeroes is the **host portion**. Those bits are free to be any number in the range 1 to 255 giving s more 
addresses to work with inside the network.

The mask can be have different sizes depending on the network adrress. This is can be marked as `/x`, where x tells us how 
many bits starting from left to the right of the network address are being read.

```txt
11111111.11111111.11111111.00000000 -> /24
```

### Wildcard Mask

This is a subnetmask where the bits are inverted, meaning that the bits which are `1` in the subnet mask are `0` in the wildcard mask and vice versa. 
For example, if we have a subnet mask of `255.255.255.0`, the wildcard mask would be `0.0.0.255`.

### Host Size

Given a subnet mask, we can determine the number of host inside a network by rasing 2 to the power of the number of zeros in 
the subnetmask minus 2 because the first address and last address are reserved for the network id and the broadcast address.

### The Increment

The **increment** is the last positional power of 2 (starting from the left) in the current byte in the subnetmask we which was flipped while subnneting.

For example:

```md
11111111.11111111.11111111.00000000 -> /24
   gets converted to 
11111111.11111111.11111111.1**1**000000 -> /26 (255.255.255.192)
```

With increment: **64**.

### Performing Subnetting 

To get more subnetworkrs from our local network we need to work with our host portion of our address.
For example if from our original network from one network to 4 networks we would do the following:

```txt
11111111.11111111.11111111.00000000 -> /24
   gets converted to 
11111111.11111111.11111111.11000000 -> /26 (255.255.255.192)
```

Example: 

Subnett the the following network `192.168.1.0` to a 5 networks.

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

### Subnetting Cheatsheet


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

Given `10.1.55 /28` find all the sub-network information.

- We start with the CIDR notation, which is `/28`, hence we look at the cheatsheet and find that the subnet mask is `255.255.255.240`.

- Then we calculate the number of IP addresses in the sub-network, which is `2^(32-28) = 16`. Or the same as the group size.

- For the network ID we take the first 3 octets of the given IP address and starting from `0` we add the group size until we reach a number which is bigger than the given IP address 
at that octet. In our case we have `0, 16, 32, 48, 64`, hence the network ID is `48` because `48` is the biggest number which is smaller than `55`. The number after is the next network ID, which is `64`. 

- The broadcast IP is the last IP address in the sub-network, which is `10.1.55.63`.

- The first host IP is the IP address after the network ID, which is `10.1.55.49`.

- The last host IP is the IP address before the broadcast IP, which is `10.1.55.62`.

--- 

## Network Protocol Definition

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

### Port Security

It allows to control which source MAC-Addresses are allowed to enter an specific switch port.
It cab be done in the following ways:

- Limiting the set of MAC-addresses for the port.
- Limiting the number of devices per port.
- Allowing only a certain list of MAC-addressess. 

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

- **Network:** It provides the functional and procedural means of transferring packages. It decides which physical path the data will take. It handles across
the routing of the data and the mapping from logical addresses and physical addresses. Defines **frames**.

- **Data Link:** It receives the data and packages it into frames which are going to be send to the respective targets. It can
also detect errors occurred at the physical layer and correct hem via algorithms. Defines **packets**.

- **Physical Layer**: Consists on the hardware components of the system.

### Frames

A **frame** is a layer 2 PDU (Protocol Data Unit) which consists of a header, payload and trailer. 
The header contains the destination and source MAC addresses, while the trailer includes error-checking information (CRC).

### Packets

A **packet** is a layer 3 PDU (Protocol Data Unit) used in the network layer. It consists of a header and a payload. The header contains source and destination IP addresses, which are used for routing the packet across the network.

### Segments

A **segment** is a layer 4 PDU (Protocol Data Unit) used in the transport layer. It contains a header and a payload. The header includes information such as source and destination ports, sequence numbers, and acknowledgment numbers, which are essential for ensuring reliable data transfer.

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

TCP is a **connection-oriented** protocol, meaning it establishes a reliable connection between sender and receiver before data transfer begins. It ensures that data is delivered 
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

### TLS/SSL Handshake

1. The certificate autority provides a signed certificate with a public and private key.

2. The server generates its own set or private and public key. Then it generates a **Certificate Signing Request (CSR)** which includes the 
public key and it is signed with the private key of the server.

3. The CA inspects and validates the certificate. The certifacate is signed with the private key of the CA. It also inlcudes the public key of the server.

4. The server can use the certifacte to validate its identity.

5. Clients already have a signed certificate which includes the public key of the CA.

6. The clients requests the cerficate of the server by chekcing the sign with the CA's public key.

7. The handshake then creates a pair of public and private keys (**Session Keys**) used by both the client and server for asymmetric encryption. 

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

Because of the first visit still being vulnerable. A concetp called **HSTS Preload** was developed, which 
consists on a static list of HSTS sites maintained by the browsers locally.

--- 

## Domains


--- 

## DNS

**Domain Name System** is a method of mapping domain names in plain text to actual IP-Address of a server.

- The IP-address of the resolver of the **resolver** is hardcoded into the router by the internet service provider. 
the goes for the address of the **root**, **tld** and **authoritative name** server in the **resolver**.

- The **stub resolver** is the client dns running in you computer. 

- The **recursive resolver** is a DNS server which does not know the IP-address if not chached but it knows the addresses of the **root** servers. 

- **Root Servers** know the right **ANS** servers to ask for the given ip address. 

- The **Authoritative Name Server** is the one server containing the actual ip address which knows the targets ip address.

### Root Servers 


### Steps

1. The stup resolver checks the cache and if the IP is not in the cache a request is triggered to hardcoded IP-address of the one program used to 
ask for the domain.

2. A request is triggered to the recursive resolver which will the **root** server of an specific **top level domain** like `.com`

3. The resolver is redirected to an specific **Authoritative Name Server** which always know the IP address.

4. The address is given to recursive resolver. 

5. The resolver returns the id to the computer. 

### Structure 

- **Top Level Domain**: This is the portion at the end of the url commonly: `.com, .org, .io`
- **Second Level Domain**:
- 

```text 
   aaaaaaaaaaaaaaaaaa.google.com
                              |
                     Top level domain
```

### Zone Files 


--- 

## SSH

Secure shell is a protocol used for providing a secure encrypted connection to a remote machine. It uses asymmetric encryption
and commonly **port 22** for the connection.

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

## Repeater

A **repeater** its a device which regenerates signals, it is used to prevent signal decay.

---

## Bridge

They sit between hub-connected host which allow to regulate the data send by hubs. For example: if we have to
networks connected via two hubs, the bridge between the two ensures that only data from one network reaches the
other if and only if necessary, other data emitted by the hub does not cross the bridge.

--- 

## Hub 

A **hub** is a device which redirects data in a local network, but it always send the data to all devices instead of being selective like a swithc. 

--- 

## Switches

**Switching** is the process of moving data withing networks. **Switches** are a combination of hubs and bridges design to redirect data to the right receiver within a network, 
also they do switching. 

- They use a layer 2 header which consists on the source and destination MAC-addresses.
- They maintain a **MAC-Addresses Table** for matching switch ports to MAC-addresses.

Actions: 

- **Learn**: Update the table with mappings when a packet comes from another hub.

- **Flood**: Duplicate and send the frame out all switch ports. This is not a broadcast, since they are performed using and special MAC-address `ffff.ffff.ffff` while 
flooding only is a send across all of the open ports of the switch.

- **Forward**: Once an extensive table has been filled, the data gets forwarded without the flood operation.

---

## Modem

A **modem** demodulates incomning analog signals into a digital signal and modulates outcoming signals as analog signals. 
Inside home networks routers, modems and even swithces are put into one device. 

--- 

## Node

A **node** is a device that implements IPv6.

--- 

## Routers

For inter-network-communication we have **routers** which connect switches and router of two or more different networks.
A node that forwards IPv6 packets not addressed to itself.

**Gateway** is a term also used for routers, but it is more general and can refer to any device that acts as an entry point to another network, not necessarily a router.

- They maintain a map of all the networks they know about (**routing table**).
- **Routes** are the starts bit sequences of an network. 
- They assign an ip address to every computers in the local network. 

### Population Methods For The Routing Table

- **Directly Connected**: Routes for networks which are attached.
- **Static Routes**: Routes manually provided by an administrator.
- **Dynamic Routes**: Routes learned automatically from other routes.

### Router Hierarchy

Routers are commonly deployed in hierarchical structure accomplished via subnetting. In this process parts of
IP-addresses are interpreted depending on the how many octets are going to be used to identify a network. 

### Default Route

It is an special route mostly written as `0.0.0.0 /0`. The address is just zero and the subnetmask is to read 0 octets of the IP-addr. 
This route is used as "for everything else, go here" for leaf routes in a tree-structure.

---

## Default Gateway

The **default gateway** is commonly the address of the router which allows us to communicate with outside networks. 
When the target is in the same network the address of the switch is used instead for the communication. 

### Use with the Subnetmask 

Using the subnetmask it is determined which devices are inside the network. This is configured by the admin.

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

## ARP

**Address Resolution Protocol**, is a protocol used for resolving IP to MAC mappings.

A workflow of ARP is as follows:

1. A host needs to send a packet to another host on the same local network, but it only knows the destination's IP address.

2. The host broadcasts an ARP request to all devices on the local network (broadcast), asking "Who has this IP address? Tell me your MAC address."

3. The device with the matching IP address responds with an ARP reply, providing its MAC address to the requester.

4. The requesting host receives the ARP reply and updates its ARP table with the new IP-to-MAC mapping, allowing it to send the packet directly to the destination using 
the resolved MAC address.

### ARP Packet Structure

```txt
| Hardware Type (16 bits) | Protocol Type (16 bits) |
| Hardware Size (8 bits) | Protocol Size (8 bits) |
| Opcode (16 bits) |
| Sender MAC Address (48 bits) |
| Sender IP Address (32 bits) |
| Target MAC Address (48 bits) |
| Target IP Address (32 bits) |
```

- **Hardware Type**: Specifies the type of hardware (e.g., Ethernet).
- **Protocol Type**: Specifies the type of protocol (e.g., IPv4).
- **Hardware Size**: Length of the hardware address (e.g., 6 for Ethernet).
- **Protocol Size**: Length of the protocol address (e.g., 4 for IPv4).
- **Opcode**: Indicates whether the message is a request (1) or a reply (2).
- **Sender MAC Address**: The MAC address of the sender.
- **Sender IP Address**: The IP address of the sender.
- **Target MAC Address**: The MAC address of the target (unknown in requests).
- **Target IP Address**: The IP address of the target.  

### Types of ARP Entries 

- **Dynamic**: Updated via a broadcast request during the update process. 
- **Static**: Manually entered in the table via the **arp** command using the targets ip and mac-address: 

```bash 
arp -s ip_addr mac_addr
```

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

--- 

## FTP 

--- 

## SMTP


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



