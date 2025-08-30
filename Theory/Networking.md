# Networking

Networking in computer science refers to concept of connection of 
multiple computers.

---

## Sockets

Sockets are an abstraction provided by the operating system to enable communication 
between different processes either on the same machine or over a network. They act as 
endpoints in a two-way communication channel. **Socket = Protocol + IP Address + Port Number**. 

Sockets operate primarily at the **Transport** layer of the **OSI** model. They are called from the 
**Application** layer asking to send or receive data. Then the socket wrap it via **TCP/UDP** and send it to 
the **Network** layer.

---

## What is a File Descriptor?

A **file descriptor (FD)** is a low-level integer handle used by an operating system to uniquely identify an open file or input/output (I/O) resource. File descriptors are central to how operating systems like Unix, Linux, and macOS manage I/O operations, including files, pipes, and sockets.

### Key Characteristics:

* **Integer Identifier**: File descriptors are represented by non-negative integers (e.g., `0`, `1`, `2`).
* **Resource Handle**: Each FD refers to an open I/O resource, such as a file, socket, or device.
* **Process-specific**: FDs are unique within a process and are maintained by the process’s file descriptor table.

### Standard File Descriptors:

By default, every process starts with three open file descriptors:

| FD | Name     | Description     |
| -- | -------- | --------------- |
| 0  | `stdin`  | Standard input  |
| 1  | `stdout` | Standard output |
| 2  | `stderr` | Standard error  |

### File Descriptors and Sockets:

In networking, **sockets are treated like files**. When you create a socket using `socket()`, the system returns a file descriptor that you can use for reading and writing data:

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

In short, file descriptors are integers which represent a current open file.

---

## OSI Model

- Application
- Presentation
- Session
- Transport
- Network 
- Data Link 
- Physical

---

## UDP and TCP

When it comes to computer networking, **UDP (User Datagram Protocol)** and **TCP (Transmission Control Protocol)** are two core transport layer protocols used to send data over the Internet. Each has its own characteristics, strengths, and ideal use cases.

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

### Command ip link 

In linux the `ip link` command will return three device names 

- `lo` for the loop back device 
- `Ethernet Plug` 
- `Ẁifi card`

