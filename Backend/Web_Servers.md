#  Web Servers 

A **web server** is a software piece used for providing a service/application via the internet.

They commonly follow a pattern of  

```txt 
    socket -> bind() 
                |
             listen()
                | 
             select()
                |
        ----> accept()
        |       |
        |   fork() - child -> 
        |       |
        ------close() [if end]
```

--- 

## Multi Processing Modules (MPM)

**Multi Processing Modules (MPM)** are used by web servers to handle multiple requests simultaneously. They determine how client requests are handled by creating 
and managing processes or threads. Different MPMs offer various strategies for handling concurrency, such as:

- **Prefork MPM**: Creates a separate process for each request. This is suitable for non-thread-safe applications, but it is very limited 
for a large number of concurrent requests.

- **Worker MPM**: Uses multiple threads per process, allowing for better scalability and performance.

- **Event MPM**: Similar to Worker MPM but optimized for handling keep-alive connections more efficiently. Uses an event-loop to manage connections, 
which can improve performance under high load.

--- 

## Common Gateway Interface (CGI)

**CGI** is a way of servers to execute external programs to process HTTP-request via a script (cgi-script), commonly written in a scripting language. The output is then
given to the server and returned to the source of the request. It starts a process for each new request, which can be resource intensive.

--- 

## Fast Common Gateway Interface (FastCGI)

**FastCGI** is a protocol for interfacing interactive programs with a web server. It is an improvement over the older Common Gateway Interface (CGI) 
and allows for better performance by keeping the application running in memory, rather than starting a new process for each request. FastCGI can be used with 
various programming languages and is commonly used to serve dynamic content on websites.

--- 

## NGINX




--- 

## Apache HTTP Server

**Apache**  is web server which can be configured inside linux systems in the following way: 

```
    /
    |__etc/apache2/apache2.conf  <- Configuration
    |
    |_usr/sbin/
    |       |_apache2  <- Exe
    |       |_apache2-clt
    |
    |_var/www/
            |_cgi-bin 
            |_html <- Document Root
```


--- 

## Tomcat


--- 

## Java Servlet

A **serverlet** is a java-class which is controlled by a web or application server. The software responsible for this is the so called 
**servler-engine**

--- 
