#  Web Servers 

A **web server** is a software piece used for the utilizing for providing a service/application via the internet.

--- 

## Multi Processing Modules (MPM)

Multi Processing Modules (MPM) are used by web servers to handle multiple requests simultaneously. They determine how client requests are handled by creating 
and managing processes or threads. Different MPMs offer various strategies for handling concurrency, such as:

- **Prefork MPM**: Creates a separate process for each request. This is suitable for non-thread-safe applications, but it is very limited 
for a large number of concurrent requests.

- **Worker MPM**: Uses multiple threads per process, allowing for better scalability and performance.

- **Event MPM**: Similar to Worker MPM but optimized for handling keep-alive connections more efficiently. Uses an event-loop to manage connections, 
which can improve performance under high load.

--- 

## Fast Common Gateway Interface (FastCGI)

FastCGI is a protocol for interfacing interactive programs with a web server. It is an improvement over the older Common Gateway Interface (CGI) 
and allows for better performance by keeping the application running in memory, rather than starting a new process for each request. FastCGI can be used with 
various programming languages and is commonly used to serve dynamic content on websites.

--- 

## nginx


--- 


## Apache HTTP Server


--- 

## Tomcat


--- 

## Java Servlet


--- 
