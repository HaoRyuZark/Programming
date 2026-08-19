# Spring Boot

A framework for Java backend development built on top of the Spring Framework.
It eliminates boilerplate configuration through **auto-configuration** and **convention over configuration**.

## Core Features

- **Auto-configuration** - Automatically configures Spring Beans based on classpath dependencies
- **Starter Dependencies** - Predefined dependency bundles (e.g., `spring-boot-starter-web`)
- **Embedded Servers** - Bundles Tomcat, Jetty, or Undertow — no external server needed
- **Spring Boot Actuator** - Production-ready health checks, metrics, and monitoring endpoints
- **Spring Boot CLI** - Command-line tool for rapid prototyping

---

## Project Setup (Maven)

`pom.xml` is used due to **Maven** parent and common starters:

### Sections 

-  `<parent>`: defines the Spring Boot starter parent POM which provides default configurations and dependency management.
-  `<dependencies>`: lists the libraries your application depends on, including Spring Boot starters.
-  `<build>`: defines build configuration, including plugins like the Spring Boot Maven plugin and compiler plugin.
-  `<properties>`: defines project-wide properties, such as Java version.
-  `<repositories>`: specifies additional Maven repositories if needed (optional).
-  `<plugins>`: defines Maven plugins for building, testing, and packaging the application.

Most of the time when looking for dependencies in the [maven repository](https://mvnrepository.com/), you will find the 
`xml` snippet to copy and paste into your `pom.xml`.

### Example

```xml
<parent>

    <!-- The parent section is used to define the Maven parent POM which comes with Spring Boot defaults -->
    <groupId>org.springframework.boot</groupId>

    <!-- The artifactId specifies the Spring Boot starter parent POM -->
    <artifactId>spring-boot-starter-parent</artifactId>

    <!-- The version specifies the Spring Boot version to use -->
    <version>3.3.0</version>
</parent>

    <!-- Define the groupId, artifactId, and version for your project -->
	<groupId>com.booki</groupId>
	<artifactId>booki</artifactId>
	<version>0.0.1-SNAPSHOT</version>

<!---Dependencies  -->	
<dependencies>
    <!-- Web (REST + embedded Tomcat) -->
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>

    <!-- JPA + Hibernate -->
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-data-jpa</artifactId>
    </dependency>

    <!-- Security -->
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-security</artifactId>
    </dependency>

    <!-- Validation (Bean Validation / Hibernate Validator) -->
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-validation</artifactId>
    </dependency>

    <!-- Testing -->
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-test</artifactId>
        <scope>test</scope> <!-- We declare that this dependency is only used for testing and should not be packed for the release version of the application -->
    </dependency>

    <!-- H2 in-memory database (development/testing) -->
    <dependency>
        <groupId>com.h2database</groupId>
        <artifactId>h2</artifactId>
        <scope>runtime</scope> <!-- We declare that this dependency is only used at runtime and should not be included in the compile classpath -->
    </dependency>

    <!-- PostgreSQL driver (production) -->
    <dependency>
        <groupId>org.postgresql</groupId>
        <artifactId>postgresql</artifactId>
        <scope>runtime</scope>
    </dependency>
</dependencies>

    <!-- The build section defines the build configuration for the project, including plugins -->
	<build>
		<plugins>
			<plugin>
				<groupId>org.springframework.boot</groupId>
				<artifactId>spring-boot-maven-plugin</artifactId>
				<configuration>
					<excludes>
						<exclude>
							<groupId>org.projectlombok</groupId>
							<artifactId>lombok</artifactId>
						</exclude>
					</excludes>
				</configuration>
			</plugin>
			<plugin>
				<groupId>org.apache.maven.plugins</groupId>
				<artifactId>maven-compiler-plugin</artifactId>
				<executions>
					<execution>
						<id>default-compile</id>
						<phase>compile</phase>
						<goals>
							<goal>compile</goal>
						</goals>
						<configuration>
							<annotationProcessorPaths>
								<path>
									<groupId>org.projectlombok</groupId>
									<artifactId>lombok</artifactId>
								</path>
							</annotationProcessorPaths>
						</configuration>
					</execution>
					<execution>
						<id>default-testCompile</id>
						<phase>test-compile</phase>
						<goals>
							<goal>testCompile</goal>
						</goals>
						<configuration>
							<annotationProcessorPaths>
								<path>
									<groupId>org.projectlombok</groupId>
									<artifactId>lombok</artifactId>
								</path>
							</annotationProcessorPaths>
						</configuration>
					</execution>
				</executions>
			</plugin>
		</plugins>
	</build>
```

---

## Common Starter Packages

| Starter                             | Purpose                                             |
|-------------------------------------|-----------------------------------------------------|
| `spring-boot-starter-web`           | REST APIs, Spring MVC, embedded Tomcat              |
| `spring-boot-starter-data-jpa`      | JPA, Hibernate, Spring Data repositories            |
| `spring-boot-starter-security`      | Authentication, authorization, CSRF protection      |
| `spring-boot-starter-validation`    | Bean Validation (JSR-380) via Hibernate Validator   |
| `spring-boot-starter-test`          | JUnit 5, Mockito, AssertJ, Spring Test utilities    |
| `spring-boot-starter-thymeleaf`     | Thymeleaf server-side template engine               |
| `spring-boot-starter-actuator`      | Health checks, metrics, info endpoints              |
| `spring-boot-starter-cache`         | Caching abstraction                                 |
| `spring-boot-starter-mail`          | JavaMail integration                                |
| `spring-boot-starter-websocket`     | WebSocket support                                   |
| `spring-boot-starter-aop`           | Aspect-Oriented Programming with AspectJ            |

---

## Java Servlets

A **Servlet** is a Java class that handles HTTP requests and generates responses. Servlets run inside a **Servlet Container** (e.g., Tomcat, Jetty, Undertow), 
which manages their lifecycle, threading, and I/O. Every Spring MVC request ultimately flows through a servlet, Spring's `DispatcherServlet`.

The Servlet API is defined in the `jakarta.servlet` package (formerly `javax.servlet` before Jakarta EE 9).

### How a Servlet Container Works

```txt
    Client
    │
    ▼
    [TCP Connection]
    │
    ▼
    Servlet Container (Tomcat / Jetty / Undertow)
    │  - Accepts the connection
    │  - Parses the raw HTTP bytes
    │  - Wraps request/response in HttpServletRequest / HttpServletResponse
    │
    ▼
    Servlet (doGet / doPost / ...)
    │  - Executes business logic
    │  - Writes to response
    │
    ▼
    Container sends HTTP response back to client
```

Common servlet containers:

| Container    | Embedded in Spring Boot | Notes                                         |
|--------------|-------------------------|-----------------------------------------------|
| **Tomcat**   | Yes (default)           | Most widely used; full Jakarta EE support     |
| **Jetty**    | Yes                     | Lighter; good for async / long-polling        |
| **Undertow** | Yes                     | High-performance; non-blocking I/O            |

Switch the embedded container in `pom.xml`:

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web</artifactId>
    <exclusions>
        <!-- Remove default Tomcat -->
        <exclusion>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-tomcat</artifactId>
        </exclusion>
    </exclusions>
</dependency>

<!-- Add Undertow instead -->
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-undertow</artifactId>
</dependency>
```

### Servlet Lifecycle

The container manages four lifecycle phases:

1. **Loading**:  container instantiates the servlet class (once).

2. **`init(ServletConfig)`**: called once after instantiation; used for one-time setup.

3. **`service(request, response)`**: called on every request; dispatches to `doGet`, `doPost`, etc.

4. **`destroy()`**: called once when the container removes the servlet; used for cleanup.

```java
public class LifecycleServlet extends HttpServlet {

    private String greeting;

    @Override
    public void init(ServletConfig config) throws ServletException {
        // Called once — read init params, open resources
        greeting = config.getInitParameter("greeting");
        if (greeting == null) greeting = "Hello";
    }

    @Override
    protected void service(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        // Default implementation dispatches to doGet, doPost, etc.
        super.service(req, resp);
    }

    @Override
    public void destroy() {
        // Called once — close connections, flush state
        System.out.println("Servlet destroyed");
    }
}
```

### Bare-Bones Servlet Example

```java
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.*;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet(urlPatterns = "/hello")   // maps this servlet to GET /hello
public class HelloServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws IOException {
        String name = req.getParameter("name");   // query param: /hello?name=Alice
        if (name == null) name = "World";

        resp.setContentType("text/plain");
        resp.setCharacterEncoding("UTF-8");

        PrintWriter writer = resp.getWriter();
        writer.println("Hello, " + name + "!");
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws IOException {
        String body = new String(req.getInputStream().readAllBytes());
        resp.setContentType("application/json");
        resp.getWriter().println("{\"received\":\"" + body + "\"}");
    }
}
```

JSON REST servlet (without Spring):

```java
@WebServlet(urlPatterns = "/api/users/*")
public class UserServlet extends HttpServlet {

    private final ObjectMapper mapper = new ObjectMapper();
    private final Map<Long, User> store = new ConcurrentHashMap<>();
    private final AtomicLong idCounter = new AtomicLong(1);

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws IOException {
        resp.setContentType("application/json");
        mapper.writeValue(resp.getWriter(), store.values());
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws IOException {
        User user = mapper.readValue(req.getInputStream(), User.class);
        user.setId(idCounter.getAndIncrement());
        store.put(user.getId(), user);

        resp.setStatus(HttpServletResponse.SC_CREATED);
        resp.setContentType("application/json");
        mapper.writeValue(resp.getWriter(), user);
    }

    @Override
    protected void doDelete(HttpServletRequest req, HttpServletResponse resp) {
        String pathInfo = req.getPathInfo();          // e.g. "/42"
        Long id = Long.parseLong(pathInfo.substring(1));
        store.remove(id);
        resp.setStatus(HttpServletResponse.SC_NO_CONTENT);
    }
}
```

If you, the reader, has already worked with express.js, this will see familiar. For different **URL** we can define different **Serverlets** and for different **HTTP methods** we can define different 
**doGet**, **doPost**, **doDelete** methods.

### Common Classes and Objects

#### HttpServletRequest: the incoming request


| Method                             | Returns              | Description                                      |
|------------------------------------|----------------------|--------------------------------------------------|
| `getMethod()`                      | `String`             | HTTP verb: `"GET"`, `"POST"`, etc.               |
| `getRequestURI()`                  | `String`             | Path part of the URL: `/api/users/42`            |
| `getQueryString()`                 | `String`             | Raw query string: `name=Alice&page=2`            |
| `getParameter(name)`               | `String`             | Single query/form parameter value                |
| `getParameterMap()`                | `Map<String, String[]>` | All query/form parameters                    |
| `getHeader(name)`                  | `String`             | Value of a request header                        |
| `getInputStream()`                 | `ServletInputStream` | Raw request body as a stream                     |
| `getReader()`                      | `BufferedReader`     | Request body as a character reader               |
| `getSession()`                     | `HttpSession`        | Get or create the session                        |
| `getSession(false)`                | `HttpSession`        | Get session without creating one (null if none)  |
| `getAttribute(name)`               | `Object`             | Request-scoped attribute (set by filters)        |
| `setAttribute(name, value)`        | `void`               | Store a request-scoped attribute                 |
| `getCookies()`                     | `Cookie[]`           | All cookies sent by the client                   |
| `getRemoteAddr()`                  | `String`             | Client IP address                                |
| `getPathInfo()`                    | `String`             | Extra path beyond the servlet mapping            |
| `getServletPath()`                 | `String`             | Portion of the URL matching the servlet mapping  |

```java
@Override
protected void doGet(HttpServletRequest req, HttpServletResponse resp)
        throws IOException {
    String method  = req.getMethod();                  // "GET"
    String uri     = req.getRequestURI();              // "/api/users/42"
    String query   = req.getQueryString();             // "sort=name&page=1"
    String sort    = req.getParameter("sort");         // "name"
    String auth    = req.getHeader("Authorization");   // "Bearer eyJ..."
    String ip      = req.getRemoteAddr();              // "192.168.1.5"

    HttpSession session = req.getSession(false);
    if (session != null) {
        Object userId = session.getAttribute("userId");
    }
}
```

#### HttpServletResponse: the outgoing response

| Method                             | Description                                          |
|------------------------------------|------------------------------------------------------|
| `setStatus(int)`                   | Set HTTP status code (e.g., `200`, `404`)            |
| `setContentType(String)`           | Set `Content-Type` header (e.g., `"application/json"`) |
| `setCharacterEncoding(String)`     | Set charset (e.g., `"UTF-8"`)                        |
| `setHeader(name, value)`           | Set a response header                                |
| `addHeader(name, value)`           | Add a header without overwriting existing values     |
| `addCookie(Cookie)`                | Append a `Set-Cookie` header                         |
| `getWriter()`                      | `PrintWriter` for text/character output              |
| `getOutputStream()`                | `ServletOutputStream` for binary output              |
| `sendRedirect(url)`                | Send `302` redirect to the given URL                 |
| `sendError(status, message)`       | Send an error response with optional message         |
| `setContentLength(int)`            | Set `Content-Length` header                          |

```java
@Override
protected void doGet(HttpServletRequest req, HttpServletResponse resp)
        throws IOException {
    resp.setStatus(HttpServletResponse.SC_OK);           // 200
    resp.setContentType("application/json");
    resp.setCharacterEncoding("UTF-8");
    resp.setHeader("X-Request-Id", UUID.randomUUID().toString());

    resp.getWriter().println("{\"status\":\"ok\"}");
}

// Binary response (e.g., PDF download)
@Override
protected void doGet(HttpServletRequest req, HttpServletResponse resp)
        throws IOException {
    byte[] pdf = generatePdf();
    resp.setContentType("application/pdf");
    resp.setHeader("Content-Disposition", "attachment; filename=\"report.pdf\"");
    resp.setContentLength(pdf.length);
    resp.getOutputStream().write(pdf);
}
```

#### HttpSession: server-side session state

```java
// Store data in session after login
HttpSession session = req.getSession(true);   // create if absent
session.setAttribute("userId", user.getId());
session.setMaxInactiveInterval(1800);         // 30 minutes

// Read in subsequent requests
HttpSession session = req.getSession(false);
if (session == null) {
    resp.sendError(HttpServletResponse.SC_UNAUTHORIZED);
    return;
}
Long userId = (Long) session.getAttribute("userId");

// Invalidate on logout
session.invalidate();
```

#### Cookie

```java
// Set a cookie
Cookie cookie = new Cookie("sessionToken", token);
cookie.setHttpOnly(true);    // not accessible via JavaScript
cookie.setSecure(true);      // HTTPS only
cookie.setMaxAge(86400);     // 1 day in seconds
cookie.setPath("/");
resp.addCookie(cookie);

// Read cookies
Cookie[] cookies = req.getCookies();
if (cookies != null) {
    for (Cookie c : cookies) {
        if ("sessionToken".equals(c.getName())) {
            String value = c.getValue();
        }
    }
}
```

#### ServletContext: application-wide shared state

```java
// Access from any servlet
ServletContext ctx = getServletContext();
ctx.setAttribute("dbPool", connectionPool);   // share across servlets
ctx.log("Application started");

String configPath = ctx.getInitParameter("configFile");  // from web.xml
```

### Filters

A **Filter** intercepts requests and responses before/after a servlet executes. Used for authentication, logging, CORS, compression, etc.

```java
@WebFilter("/*")   // applies to all URLs
public class LoggingFilter implements Filter {

    @Override
    public void doFilter(ServletRequest request, ServletResponse response,
                         FilterChain chain) throws IOException, ServletException {
        HttpServletRequest req = (HttpServletRequest) request;
        long start = System.currentTimeMillis();

        System.out.printf("[%s] %s%n", req.getMethod(), req.getRequestURI());

        chain.doFilter(request, response);   // continue to next filter or servlet

        long elapsed = System.currentTimeMillis() - start;
        System.out.printf("Completed in %dms%n", elapsed);
    }
}

// Auth filter example
@WebFilter("/api/*")
public class JwtFilter implements Filter {

    @Override
    public void doFilter(ServletRequest request, ServletResponse response,
                         FilterChain chain) throws IOException, ServletException {
        HttpServletRequest  req  = (HttpServletRequest)  request;
        HttpServletResponse resp = (HttpServletResponse) response;

        String auth = req.getHeader("Authorization");
        if (auth == null || !auth.startsWith("Bearer ")) {
            resp.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Missing token");
            return;   // do NOT call chain.doFilter — request is blocked
        }

        // validate token, then continue
        chain.doFilter(request, response);
    }
}
```

Filters execute in declaration order. Multiple filters form a **filter chain**:

```txt
Request → Filter1 → Filter2 → Filter3 → Servlet
Response ← Filter1 ← Filter2 ← Filter3 ←
```

### How Spring Boot Simplifies Servlets

Writing raw servlets requires manual JSON parsing, routing, error handling, and session management. Spring Boot replaces all of that with declarative annotations on top of the same Servlet API.

| Raw Servlet                              | Spring Boot Equivalent                         |
|------------------------------------------|------------------------------------------------|
| `extends HttpServlet`                    | `@RestController`                              |
| `doGet` / `doPost` method overrides      | `@GetMapping` / `@PostMapping` methods         |
| `req.getParameter("name")`               | `@RequestParam String name`                    |
| `req.getPathInfo()` + manual parsing     | `@PathVariable Long id`                        |
| `mapper.readValue(req.getInputStream())` | `@RequestBody UserDto dto`                     |
| `resp.setStatus(201)` + manual JSON      | `ResponseEntity.status(201).body(dto)`         |
| `@WebFilter` implementing `Filter`       | `OncePerRequestFilter` or `SecurityFilterChain`|
| Manual exception handling in every method | `@RestControllerAdvice` + `@ExceptionHandler` |
| `session.setAttribute("userId", id)`    | Spring Security `SecurityContext`              |

Under the hood, Spring registers a single `DispatcherServlet` that routes all requests to your `@RestController` methods:

```
Request → Tomcat → DispatcherServlet → HandlerMapping
                                             │
                                       @RestController method
                                             │
                                       HttpMessageConverter (Jackson)
                                             │
                                        Response
```

You can still register raw servlets alongside Spring MVC when needed:

```java
// Register a raw servlet as a Spring Bean
@Bean
public ServletRegistrationBean<LegacyServlet> legacyServlet() {
    return new ServletRegistrationBean<>(new LegacyServlet(), "/legacy/*");
}

// Register a filter as a Spring Bean
@Bean
public FilterRegistrationBean<LoggingFilter> loggingFilter() {
    FilterRegistrationBean<LoggingFilter> reg = new FilterRegistrationBean<>();
    reg.setFilter(new LoggingFilter());
    reg.addUrlPatterns("/api/*");
    reg.setOrder(1);   // lower number = runs first
    return reg;
}
```

Spring Security's filter chain is itself a `Filter` registered before your application filters:

```java
@Bean
public SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
    // Internally adds OncePerRequestFilter implementations to the servlet filter chain
    http
        .authorizeHttpRequests(auth -> auth.anyRequest().authenticated())
        .addFilterBefore(jwtFilter, UsernamePasswordAuthenticationFilter.class);
    return http.build();
}
```

--- 

## Application Entry Point

```java
@SpringBootApplication  // = @Configuration + @EnableAutoConfiguration + @ComponentScan
public class MyApplication {
    public static void main(String[] args) {
        SpringApplication.run(MyApplication.class, args);
    }
}
```

---

## Project Structure (Convention)

```
src/
├── main/
│   ├── java/com/example/myapp/
│   │   ├── MyApplication.java        ← entry point
│   │   ├── config/                   ← @Configuration classes
│   │   ├── controller/               ← @RestController / @Controller
│   │   ├── service/                  ← @Service (business logic)
│   │   ├── repository/               ← @Repository / JpaRepository
│   │   ├── model/                    ← @Entity (JPA entities)
│   │   ├── dto/                      ← Data Transfer Objects
│   │   ├── exception/                ← custom exceptions + @ControllerAdvice
│   │   └── security/                 ← security config
│   └── resources/
│       ├── application.properties    ← main config
│       └── application-dev.yml       ← profile-specific config
└── test/
    └── java/com/example/myapp/       ← mirrors main structure
```

---

## Core Annotations

### Component Model

- `@SpringBootApplication`: entry point annotation; combines `@Configuration`, `@EnableAutoConfiguration`, and `@ComponentScan`.

- `@Component`: generic Spring-managed component. Spring registers it as a Bean during classpath scanning.

- `@Service`: specialization of `@Component` for the service layer (business logic). Semantically distinct — no extra behaviour over `@Component`.

- `@Repository`: specialization of `@Component` for the persistence layer. Also translates persistence-specific exceptions to Spring's `DataAccessException`.

- `@Controller`: specialization of `@Component` for the web layer. Returns view names (for template engines).

- `@RestController`: combines `@Controller` and `@ResponseBody`. Every method return value is serialized to JSON/XML and written directly to the HTTP response.

- `@Configuration`: marks a class as a source of Bean definitions. Methods annotated with `@Bean` inside it are managed by the Spring IoC container.

- `@Bean`: declares a single Bean to be managed by Spring. Used inside `@Configuration` classes; the method name becomes the Bean name by default.

```java
// @Component — generic bean
@Component
public class EmailSender { ... }

// @Service — business logic
@Service
public class UserService {
    private final UserRepository repo;

    // Constructor injection (preferred over field injection)
    public UserService(UserRepository repo) {
        this.repo = repo;
    }
}

// @Repository — data access
@Repository
public interface UserRepository extends JpaRepository<User, Long> { }

// @RestController — REST API
@RestController
@RequestMapping("/api/users")
public class UserController { ... }

// @Configuration + @Bean — explicit bean definition
@Configuration
public class AppConfig {

    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }

    @Bean(name = "customRestTemplate")
    public RestTemplate restTemplate() {
        return new RestTemplate();
    }
}
```

### Dependency Injection

- `@Autowired`: injects a Spring Bean into a field, constructor, or setter method. **Constructor injection is preferred** — it makes dependencies explicit and supports immutability.

- `@Qualifier("beanName")`: disambiguates when multiple beans of the same type exist. Used together with `@Autowired`.

- `@Primary`: marks one bean as the default when multiple candidates exist for injection. The `@Qualifier` always overrides `@Primary`.

- `@Value("${property.key}")`: injects a value from `application.properties` / `application.yml` or a SpEL expression.

```java
// Constructor injection (preferred)
@Service
public class OrderService {

    private final PaymentService paymentService;
    private final InventoryService inventoryService;

    public OrderService(PaymentService paymentService,
                        InventoryService inventoryService) {
        this.paymentService = paymentService;
        this.inventoryService = inventoryService;
    }
}

// @Qualifier — resolve ambiguity
public interface NotificationService { void send(String message); }

@Component("emailNotification")
public class EmailNotificationService implements NotificationService { ... }

@Component("smsNotification")
public class SmsNotificationService implements NotificationService { ... }

@Service
public class AlertService {

    private final NotificationService notificationService;

    public AlertService(@Qualifier("emailNotification") NotificationService ns) {
        this.notificationService = ns;
    }
}

// @Value
@Component
public class JwtConfig {

    @Value("${jwt.secret}")
    private String secret;

    @Value("${jwt.expiration:3600}")   // default 3600 if property missing
    private int expiration;

    @Value("#{2 * 60 * 60}")           // SpEL expression
    private int computedExpiration;
}
```

### Conditional Beans

- `@ConditionalOnProperty(name, havingValue, matchIfMissing)`: creates the bean only if a specific property has the specified value.

- `@ConditionalOnBean(type)`: creates the bean only if another bean of the given type is already in the context.

- `@ConditionalOnMissingBean(type)`: creates the bean only if no bean of the given type exists (useful for providing defaults that users can override).

- `@ConditionalOnClass(name)`: creates the bean only if the specified class is on the classpath.

- `@ConditionalOnMissingClass(name)`: creates the bean only if the specified class is NOT on the classpath.

```java
@Configuration
public class CacheConfig {

    // Only active when cache.enabled=true in properties
    @Bean
    @ConditionalOnProperty(name = "cache.enabled", havingValue = "true")
    public CacheManager redisCacheManager() {
        return new RedisCacheManager(...);
    }

    // Fallback when no CacheManager is present
    @Bean
    @ConditionalOnMissingBean(CacheManager.class)
    public CacheManager simpleCacheManager() {
        return new ConcurrentMapCacheManager("default");
    }
}
```

### Bean Scope

- `@Scope("singleton")`: one instance per Spring container (default).
- `@Scope("prototype")`: new instance on each injection/request.
- `@Scope("request")`: one instance per HTTP request (web contexts only).
- `@Scope("session")`: one instance per HTTP session (web contexts only).

```java
@Bean
@Scope("prototype")
public ReportGenerator reportGenerator() {
    return new ReportGenerator();
}
```

---

## Configuration

### application.properties / application.yml

```properties
# application.properties
server.port=8080
server.servlet.context-path=/api

spring.application.name=my-app

# DataSource
spring.datasource.url=jdbc:postgresql://localhost:5432/mydb
spring.datasource.username=postgres
spring.datasource.password=secret
spring.datasource.driver-class-name=org.postgresql.Driver

# JPA / Hibernate
spring.jpa.hibernate.ddl-auto=update       # none | validate | update | create | create-drop
spring.jpa.show-sql=true
spring.jpa.properties.hibernate.format_sql=true
spring.jpa.database-platform=org.hibernate.dialect.PostgreSQLDialect

# Logging
logging.level.root=INFO
logging.level.org.springframework.web=DEBUG
logging.level.com.example=TRACE

# Actuator
management.endpoints.web.exposure.include=health,info,metrics
management.endpoint.health.show-details=always
```

Equivalent YAML (`application.yml`):

```yaml
server:
  port: 8080
  servlet:
    context-path: /api

spring:
  application:
    name: my-app
  datasource:
    url: jdbc:postgresql://localhost:5432/mydb
    username: postgres
    password: secret
  jpa:
    hibernate:
      ddl-auto: update
    show-sql: true

logging:
  level:
    root: INFO
    com.example: DEBUG
```

### @ConfigurationProperties

Binds a group of related properties to a strongly-typed POJO. Preferred over many `@Value` fields.

- `@ConfigurationProperties(prefix)`: maps all properties with the given prefix to fields of the annotated class.
  - `prefix`: the property key prefix (e.g., `"app.jwt"`).

- `@EnableConfigurationProperties(SomeProps.class)`: registers a `@ConfigurationProperties` class as a bean. Alternatively annotate the class with `@Component`.

```properties
# application.properties
app.jwt.secret=mySuperSecretKey
app.jwt.expiration=86400
app.jwt.issuer=my-app
```

```java
@ConfigurationProperties(prefix = "app.jwt")
@Component
public class JwtProperties {
    private String secret;
    private int expiration;
    private String issuer;
    // getters + setters (or use a Java record in Spring Boot 3)
}

@Service
public class JwtService {
    private final JwtProperties props;

    public JwtService(JwtProperties props) {
        this.props = props;
    }
}
```

### Profiles

Profiles activate different configurations per environment (dev, staging, prod).

- `@Profile("profileName")`: restricts a bean or configuration class to the named profile(s).

Activate via property: `spring.profiles.active=dev`

```yaml
# application-dev.yml
spring:
  datasource:
    url: jdbc:h2:mem:testdb
  jpa:
    hibernate:
      ddl-auto: create-drop
```

```java
@Configuration
@Profile("prod")
public class ProdDataSourceConfig {

    @Bean
    public DataSource dataSource() {
        HikariDataSource ds = new HikariDataSource();
        ds.setJdbcUrl("jdbc:postgresql://prod-host:5432/mydb");
        return ds;
    }
}

@Configuration
@Profile("dev")
public class DevDataSourceConfig {

    @Bean
    public DataSource dataSource() {
        return new EmbeddedDatabaseBuilder()
            .setType(EmbeddedDatabaseType.H2)
            .build();
    }
}
```

---

## REST Controllers

- `@RestController`: marks the class as a REST controller. All methods return data (JSON by default) rather than view names.

- `@RequestMapping(path, method, consumes, produces)`: maps HTTP requests to handler methods. Can be placed at class level (base path) and method level (sub-path).
  - `path` / `value`: URL path (e.g., `"/users"`).
  - `method`: HTTP method (e.g., `RequestMethod.GET`). Use the shorthand annotations below instead.
  - `consumes`: restricts by `Content-Type` header.
  - `produces`: restricts by `Accept` header (e.g., `"application/json"`).

- `@GetMapping(path)`: shorthand for `@RequestMapping(method = GET)`.
- `@PostMapping(path)`: shorthand for `@RequestMapping(method = POST)`.
- `@PutMapping(path)`: shorthand for `@RequestMapping(method = PUT)`.
- `@PatchMapping(path)`: shorthand for `@RequestMapping(method = PATCH)`.
- `@DeleteMapping(path)`: shorthand for `@RequestMapping(method = DELETE)`.

### Method Parameters

- `@PathVariable("name")`: binds a URI template variable (e.g., `/users/{id}`) to a method parameter.

- `@RequestParam(name, required, defaultValue)`: binds a query parameter (`/search?q=foo`) to a method parameter.
  - `required`: whether the parameter is mandatory (default `true`).
  - `defaultValue`: fallback value if the parameter is missing.

- `@RequestBody`: deserializes the request body (JSON/XML) into a Java object. Uses Jackson by default.

- `@RequestHeader(name)`: binds an HTTP request header to a method parameter.

- `@CookieValue(name)`: binds a cookie value to a method parameter.

### Response Handling

- `ResponseEntity<T>`: wraps the response body, status code, and headers. Gives full control over the HTTP response.

- `@ResponseStatus(HttpStatus.CREATED)`: sets the default HTTP status for a method or exception class.

```java
@RestController
@RequestMapping("/api/users")
public class UserController {

    private final UserService userService;

    public UserController(UserService userService) {
        this.userService = userService;
    }

    // GET /api/users
    @GetMapping
    public List<UserDto> getAllUsers() {
        return userService.findAll();
    }

    // GET /api/users/42
    @GetMapping("/{id}")
    public ResponseEntity<UserDto> getUserById(@PathVariable Long id) {
        return userService.findById(id)
                .map(ResponseEntity::ok)
                .orElse(ResponseEntity.notFound().build());
    }

    // GET /api/users?page=0&size=10
    @GetMapping("/search")
    public Page<UserDto> searchUsers(
            @RequestParam(defaultValue = "") String name,
            @RequestParam(defaultValue = "0")  int page,
            @RequestParam(defaultValue = "10") int size) {
        return userService.search(name, PageRequest.of(page, size));
    }

    // POST /api/users
    @PostMapping
    @ResponseStatus(HttpStatus.CREATED)
    public UserDto createUser(@Valid @RequestBody CreateUserRequest request) {
        return userService.create(request);
    }

    // PUT /api/users/42
    @PutMapping("/{id}")
    public ResponseEntity<UserDto> updateUser(@PathVariable Long id,
                                              @Valid @RequestBody UpdateUserRequest request) {
        return userService.update(id, request)
                .map(ResponseEntity::ok)
                .orElse(ResponseEntity.notFound().build());
    }

    // DELETE /api/users/42
    @DeleteMapping("/{id}")
    public ResponseEntity<Void> deleteUser(@PathVariable Long id) {
        userService.delete(id);
        return ResponseEntity.noContent().build();
    }

    // Custom response headers
    @GetMapping("/export")
    public ResponseEntity<byte[]> exportUsers() {
        byte[] data = userService.exportCsv();
        return ResponseEntity.ok()
                .header(HttpHeaders.CONTENT_DISPOSITION, "attachment; filename=\"users.csv\"")
                .contentType(MediaType.TEXT_PLAIN)
                .body(data);
    }
}
```

---

## Bean Validation

Annotations from `jakarta.validation.constraints` (requires `spring-boot-starter-validation`).

- `@NotNull`: field must not be `null`.
- `@NotBlank`: string must not be `null`, empty, or whitespace only.
- `@NotEmpty`: collection/string must not be `null` or empty.
- `@Size(min, max)`: string/collection size must be within the range.
- `@Min(value)` / `@Max(value)`: numeric value must be ≥ / ≤ the given value.
- `@Email`: string must be a valid email address.
- `@Pattern(regexp)`: string must match the regular expression.
- `@Positive` / `@PositiveOrZero`: number must be positive (or ≥ 0).
- `@Past` / `@Future`: date must be in the past / future.

Use `@Valid` on method parameters to trigger validation. Spring throws `MethodArgumentNotValidException` on failure.

```java
public class CreateUserRequest {

    @NotBlank(message = "Name is required")
    @Size(min = 2, max = 100)
    private String name;

    @Email(message = "Invalid email address")
    @NotBlank
    private String email;

    @NotNull
    @Min(value = 0, message = "Age must be non-negative")
    @Max(value = 150)
    private Integer age;

    @Pattern(regexp = "^(?=.*[A-Z])(?=.*\\d).{8,}$",
             message = "Password must be ≥8 chars with 1 uppercase and 1 digit")
    private String password;
}
```

---

## Exception Handling

### @ControllerAdvice / @ExceptionHandler

- `@ControllerAdvice`: global exception handler that intercepts exceptions thrown by any `@Controller`.

- `@RestControllerAdvice`: combines `@ControllerAdvice` and `@ResponseBody` — responses are serialized to JSON.

- `@ExceptionHandler(ExceptionType.class)`: handles a specific exception type within the annotated class.

```java
// Custom exception
public class ResourceNotFoundException extends RuntimeException {
    public ResourceNotFoundException(String message) {
        super(message);
    }
}

// Error response DTO
public record ErrorResponse(int status, String message, Instant timestamp) {}

// Global handler
@RestControllerAdvice
public class GlobalExceptionHandler {

    @ExceptionHandler(ResourceNotFoundException.class)
    @ResponseStatus(HttpStatus.NOT_FOUND)
    public ErrorResponse handleNotFound(ResourceNotFoundException ex) {
        return new ErrorResponse(404, ex.getMessage(), Instant.now());
    }

    @ExceptionHandler(MethodArgumentNotValidException.class)
    @ResponseStatus(HttpStatus.BAD_REQUEST)
    public Map<String, String> handleValidationErrors(MethodArgumentNotValidException ex) {
        Map<String, String> errors = new HashMap<>();
        ex.getBindingResult().getFieldErrors().forEach(error ->
            errors.put(error.getField(), error.getDefaultMessage()));
        return errors;
    }

    @ExceptionHandler(Exception.class)
    @ResponseStatus(HttpStatus.INTERNAL_SERVER_ERROR)
    public ErrorResponse handleGeneral(Exception ex) {
        return new ErrorResponse(500, "Internal server error", Instant.now());
    }
}
```

---

## Spring Data JPA / Hibernate

This portion of the framework allows us to map classes to an **Entity/Table** inside the database and provides functionality to access those 
table via **Repositories**.

### JPA Configuration

Full reference for `application.properties` / `application.yml` — datasource, HikariCP pool, and Hibernate settings.

```properties
# ─── Datasource ───────────────────────────────────────────────────────────────
spring.datasource.url=jdbc:postgresql://localhost:5432/mydb
spring.datasource.username=postgres
spring.datasource.password=secret
spring.datasource.driver-class-name=org.postgresql.Driver

# ─── HikariCP connection pool ─────────────────────────────────────────────────
spring.datasource.hikari.pool-name=AppPool
spring.datasource.hikari.maximum-pool-size=10         # max simultaneous connections
spring.datasource.hikari.minimum-idle=2               # idle connections kept open
spring.datasource.hikari.connection-timeout=30000     # ms to wait for a free connection
spring.datasource.hikari.idle-timeout=600000          # ms before idle conn is released
spring.datasource.hikari.max-lifetime=1800000         # ms max lifetime per connection
spring.datasource.hikari.connection-test-query=SELECT 1

# ─── JPA / Hibernate ──────────────────────────────────────────────────────────
spring.jpa.hibernate.ddl-auto=validate    # see table below
spring.jpa.show-sql=true                  # print SQL to console
spring.jpa.properties.hibernate.format_sql=true
spring.jpa.properties.hibernate.use_sql_comments=true
spring.jpa.open-in-view=false             # disable OSIV — always false for REST APIs
spring.jpa.database-platform=org.hibernate.dialect.PostgreSQLDialect

# Batch inserts / updates (huge performance boost for bulk operations)
spring.jpa.properties.hibernate.jdbc.batch_size=50
spring.jpa.properties.hibernate.order_inserts=true
spring.jpa.properties.hibernate.order_updates=true

# Expose N+1 and slow queries during development
spring.jpa.properties.hibernate.generate_statistics=true
logging.level.org.hibernate.stat=DEBUG
logging.level.org.hibernate.SQL=DEBUG
logging.level.org.hibernate.type.descriptor.sql.BasicBinder=TRACE  # logs bind params
```

**`ddl-auto` values:**

| Value | Behaviour | Recommended use |
|-------|-----------|-----------------|
| `none` | Do nothing | **Production** — always use with migrations |
| `validate` | Validate schema against entities; crash on mismatch | Pre-production CI |
| `update` | Alter tables to match — **never in production** | Dev only |
| `create` | Drop and re-create every startup | Dev / local |
| `create-drop` | Create on startup, drop on shutdown | Integration tests |

**Key configuration annotations:**

- `@EnableJpaRepositories(basePackages, entityManagerFactoryRef, transactionManagerRef)`: activates Spring Data repositories. Spring Boot auto-applies this for a single datasource — only needed explicitly in multi-datasource setups.

- `@EntityScan("com.example.model")`: tells Spring where to find `@Entity` classes — required in multi-module projects where entities live in a separate module.

- `@EnableTransactionManagement`: activates `@Transactional` processing. Spring Boot auto-applies this.

```java
// Explicit setup for multi-module apps
@SpringBootApplication
@EntityScan("com.example.domain.model")
@EnableJpaRepositories("com.example.domain.repository")
public class MyApplication { ... }
```

**Multiple datasources** (primary + secondary):

```java
@Configuration
public class DataSourceConfig {

    // ─── Primary ─────────────────────────────────────────────────────────────
    @Bean @Primary
    @ConfigurationProperties("spring.datasource.primary")
    public DataSourceProperties primaryProps() { return new DataSourceProperties(); }

    @Bean @Primary
    public HikariDataSource primaryDataSource(
            @Qualifier("primaryProps") DataSourceProperties p) {
        return p.initializeDataSourceBuilder().type(HikariDataSource.class).build();
    }

    // ─── Secondary ───────────────────────────────────────────────────────────
    @Bean
    @ConfigurationProperties("spring.datasource.secondary")
    public DataSourceProperties secondaryProps() { return new DataSourceProperties(); }

    @Bean
    public HikariDataSource secondaryDataSource(
            @Qualifier("secondaryProps") DataSourceProperties p) {
        return p.initializeDataSourceBuilder().type(HikariDataSource.class).build();
    }
}

// Dedicated JPA config per datasource
@Configuration
@EnableJpaRepositories(
    basePackages            = "com.example.primary.repository",
    entityManagerFactoryRef = "primaryEmf",
    transactionManagerRef   = "primaryTx"
)
public class PrimaryJpaConfig {

    @Bean @Primary
    public LocalContainerEntityManagerFactoryBean primaryEmf(
            @Qualifier("primaryDataSource") DataSource ds) {
        var emf = new LocalContainerEntityManagerFactoryBean();
        emf.setDataSource(ds);
        emf.setPackagesToScan("com.example.primary.model");
        emf.setJpaVendorAdapter(new HibernateJpaVendorAdapter());
        return emf;
    }

    @Bean @Primary
    public PlatformTransactionManager primaryTx(
            @Qualifier("primaryEmf") EntityManagerFactory emf) {
        return new JpaTransactionManager(emf);
    }
}
```

---

### Entity

- `@Entity`: marks the class as a JPA entity (maps to a database table).

- `@Table(name)`: specifies the table name. Defaults to the class name.

- `@Id`: marks the primary key field.

- `@GeneratedValue(strategy)`: configures auto-generation of primary key values.
  - `GenerationType.IDENTITY`: database auto-increment.
  - `GenerationType.SEQUENCE`: uses a database sequence.
  - `GenerationType.UUID`: generates a UUID (JPA 3.1+).

- `@Column(name, nullable, unique, length)`: maps a field to a specific column.

- `@Transient`: field is not persisted to the database.

- `@Enumerated(EnumType.STRING)`: persists an enum as its string name (not ordinal).

- `@CreationTimestamp` / `@UpdateTimestamp`: Hibernate-specific; auto-sets on insert/update.

```java
@Entity
@Table(name = "users")
public class User {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "full_name", nullable = false, length = 100)
    private String name;

    @Column(unique = true, nullable = false)
    private String email;

    @Enumerated(EnumType.STRING)
    private Role role;

    @CreationTimestamp
    @Column(updatable = false)
    private LocalDateTime createdAt;

    @UpdateTimestamp
    private LocalDateTime updatedAt;

    @Transient
    private String displayName;  // not stored in DB

    // getters, setters, no-arg constructor (required by JPA)
}

public enum Role { USER, ADMIN, MODERATOR }
```

### Relationships

- `@OneToOne(mappedBy, cascade, fetch)`: one-to-one relationship.

- `@OneToMany(mappedBy, cascade, fetch)`: one-to-many relationship.

- `@ManyToOne(fetch)`: many-to-one relationship.

- `@ManyToMany(mappedBy)`: many-to-many relationship.

- `@JoinColumn(name)`: specifies the foreign key column.

- `@JoinTable(name, joinColumns, inverseJoinColumns)`: configures the join table for `@ManyToMany`.

- `fetch = FetchType.LAZY`: load related entity only when accessed (default for collections, recommended).

- `fetch = FetchType.EAGER`: load related entity immediately (default for `@ManyToOne`, use sparingly).

- `cascade = CascadeType.ALL`: propagates all operations (persist, merge, remove, refresh, detach).

```java
@Entity
public class Order {

    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    // Many orders belong to one user
    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "user_id", nullable = false)
    private User user;

    // One order has many items (orphanRemoval deletes items when removed from the list)
    @OneToMany(mappedBy = "order", cascade = CascadeType.ALL, orphanRemoval = true)
    private List<OrderItem> items = new ArrayList<>();
}

@Entity
public class UserProfile {

    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @OneToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "user_id")
    private User user;
}

@Entity
public class Student {

    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @ManyToMany
    @JoinTable(
        name = "student_course",
        joinColumns = @JoinColumn(name = "student_id"),
        inverseJoinColumns = @JoinColumn(name = "course_id")
    )
    private Set<Course> courses = new HashSet<>();
}
```

### Repository

`JpaRepository<Entity, ID>` extends `CrudRepository` and `PagingAndSortingRepository`,
providing full CRUD, pagination, and sorting out of the box.

Built-in methods (no need to implement):

- `save(entity)`, `saveAll(entities)`

- `findById(id)` → `Optional<T>`

- `findAll()`, `findAll(Pageable)`, `findAll(Sort)`

- `deleteById(id)`, `delete(entity)`, `deleteAll()`

- `count()`, `existsById(id)`

**Derived query methods**: Spring Data generates SQL from the method **name**:

```java
@Repository
public interface UserRepository extends JpaRepository<User, Long> {

    // SELECT * FROM users WHERE email = ?
    Optional<User> findByEmail(String email);

    // SELECT * FROM users WHERE name LIKE %?% AND role = ?
    List<User> findByNameContainingIgnoreCaseAndRole(String name, Role role);

    // SELECT * FROM users WHERE created_at > ? ORDER BY name ASC
    List<User> findByCreatedAtAfterOrderByNameAsc(LocalDateTime date);

    // EXISTS query
    boolean existsByEmail(String email);

    // Count
    long countByRole(Role role);

    // DELETE
    void deleteByEmail(String email);

    // Custom JPQL query
    @Query("SELECT u FROM User u WHERE u.email = :email AND u.role = :role")
    Optional<User> findByEmailAndRole(@Param("email") String email,
                                      @Param("role")  Role role);

    // Native SQL query
    @Query(value = "SELECT * FROM users WHERE LOWER(name) LIKE LOWER(CONCAT('%', :name, '%'))",
           nativeQuery = true)
    List<User> searchByNameNative(@Param("name") String name);

    // Modifying query (UPDATE / DELETE) — must be inside a transaction
    @Modifying
    @Transactional
    @Query("UPDATE User u SET u.role = :role WHERE u.id = :id")
    int updateRole(@Param("id") Long id, @Param("role") Role role);
}
```

We can also explicitly declare how the repository will fetch the data by declaring our own queries.

### @Transactional

- `@Transactional`: wraps a method (or all methods in a class) in a database transaction.
  - `readOnly = true`: optimizes read-only operations (no dirty checking).
  - `rollbackFor = Exception.class`: rolls back on checked exceptions too (by default, only on `RuntimeException`).
  - `propagation`: controls how transactions propagate (default `REQUIRED` — join existing or create new).
  - `isolation`: transaction isolation level (`READ_COMMITTED`, `REPEATABLE_READ`, etc.).

```java
@Service
@Transactional(readOnly = true)  // default for all methods
public class UserService {

    private final UserRepository userRepository;

    public UserService(UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    public List<User> findAll() {
        return userRepository.findAll();
    }

    @Transactional   // overrides class-level readOnly=true
    public User createUser(CreateUserRequest req) {
        if (userRepository.existsByEmail(req.getEmail())) {
            throw new IllegalArgumentException("Email already in use");
        }
        User user = new User();
        user.setName(req.getName());
        user.setEmail(req.getEmail());
        return userRepository.save(user);
    }

    @Transactional(rollbackFor = Exception.class)
    public void transferBalance(Long fromId, Long toId, BigDecimal amount) {
        // Both operations succeed or both roll back
        accountRepository.debit(fromId, amount);
        accountRepository.credit(toId, amount);
    }
}
```

---

## Spring MVC (Server-Side Rendering)

Used when returning full HTML pages via a template engine (e.g., Thymeleaf).

- `@Controller`: marks the class as an MVC controller. Methods return view names (strings).
- `Model` / `ModelMap`: passes attributes to the view.
- `ModelAndView`: combines a view name and model attributes in one object.
- `RedirectAttributes`: passes flash attributes across a redirect.

```java
@Controller
@RequestMapping("/users")
public class UserViewController {

    private final UserService userService;

    public UserViewController(UserService userService) {
        this.userService = userService;
    }

    @GetMapping
    public String listUsers(Model model) {
        model.addAttribute("users", userService.findAll());
        return "users/list";   // resolves to templates/users/list.html
    }

    @GetMapping("/{id}")
    public String userDetail(@PathVariable Long id, Model model) {
        User user = userService.findById(id)
                .orElseThrow(() -> new ResourceNotFoundException("User not found"));
        model.addAttribute("user", user);
        return "users/detail";
    }

    @PostMapping
    public String createUser(@Valid @ModelAttribute CreateUserRequest request,
                             BindingResult result,
                             RedirectAttributes redirectAttributes) {
        if (result.hasErrors()) {
            return "users/create";  // stay on form page
        }
        userService.create(request);
        redirectAttributes.addFlashAttribute("message", "User created successfully");
        return "redirect:/users";
    }
}
```

### Thymeleaf Template Syntax

```html
<!-- templates/users/list.html -->
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<body>
    <h1>Users</h1>
    <ul>
        <!-- th:each — iteration -->
        <li th:each="user : ${users}">
            <!-- th:text — text content (HTML-escaped) -->
            <span th:text="${user.name}"></span>
            <!-- th:href — dynamic URL -->
            <a th:href="@{/users/{id}(id=${user.id})}">Details</a>
        </li>
    </ul>
    <!-- th:if / th:unless — conditionals -->
    <p th:if="${#lists.isEmpty(users)}">No users found.</p>
</body>
</html>
```

---

## Spring Security

**Spring Security** provides authentication and authorization for Spring applications. It integrates with Spring Boot and Spring MVC seamlessly.

### Basic Configuration (Spring Security 6 / Spring Boot 3)

```java
@Configuration
@EnableWebSecurity
public class SecurityConfig {

    private final UserDetailsService userDetailsService;

    public SecurityConfig(UserDetailsService userDetailsService) {
        this.userDetailsService = userDetailsService;
    }

    @Bean
    public SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
        http
            .csrf(csrf -> csrf.disable())   // disable CSRF for stateless REST APIs
            .authorizeHttpRequests(auth -> auth
                .requestMatchers("/api/auth/**").permitAll()
                .requestMatchers("/api/admin/**").hasRole("ADMIN")
                .requestMatchers(HttpMethod.GET, "/api/users/**").hasAnyRole("USER", "ADMIN")
                .anyRequest().authenticated()
            )
            .sessionManagement(session ->
                session.sessionCreationPolicy(SessionCreationPolicy.STATELESS)
            )
            // Add JWT filter before the default username/password filter
            .addFilterBefore(jwtAuthFilter(), UsernamePasswordAuthenticationFilter.class);

        return http.build();
    }

    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }

    @Bean
    public AuthenticationManager authenticationManager(AuthenticationConfiguration config)
            throws Exception {
        return config.getAuthenticationManager();
    }
}
```

### UserDetailsService

```java
@Service
public class CustomUserDetailsService implements UserDetailsService {

    private final UserRepository userRepository;

    public CustomUserDetailsService(UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    @Override
    public UserDetails loadUserByUsername(String email) throws UsernameNotFoundException {
        User user = userRepository.findByEmail(email)
                .orElseThrow(() -> new UsernameNotFoundException("User not found: " + email));

        return org.springframework.security.core.userdetails.User.builder()
                .username(user.getEmail())
                .password(user.getPassword())  // must be BCrypt-hashed
                .roles(user.getRole().name())
                .build();
    }
}
```

### Method-Level Security

- `@EnableMethodSecurity`: enables `@PreAuthorize`, `@PostAuthorize`, and `@Secured` on methods.
- `@PreAuthorize("expression")`: checks the expression before the method executes.
- `@PostAuthorize("expression")`: checks the expression after the method returns (can inspect return value).
- `@Secured("ROLE_ADMIN")`: allows access only to users with the specified role(s).

```java
@Configuration
@EnableMethodSecurity
public class MethodSecurityConfig { }

@Service
public class UserService {

    @PreAuthorize("hasRole('ADMIN')")
    public void deleteUser(Long id) { ... }

    // Admin can access any user; user can only access their own record
    @PreAuthorize("hasRole('ADMIN') or #id == authentication.principal.id")
    public UserDto getUserById(Long id) { ... }

    @PostAuthorize("returnObject.email == authentication.name")
    public User getMyProfile(Long id) { ... }
}
```

---

## Dependency Injection and Beans (Full Example)

```java
public interface Shape { void draw(); }

@Component
public class Circle implements Shape {
    @Override
    public void draw() { System.out.println("Drawing a Circle"); }
}

@Component
@Primary
public class Square implements Shape {
    @Override
    public void draw() { System.out.println("Drawing a Square"); }
}

@Component
public class ShapeDrawer {

    private final Shape shape;

    // @Primary Square is injected; use @Qualifier("circle") to override
    public ShapeDrawer(Shape shape) {
        this.shape = shape;
    }

    public void drawShape() { shape.draw(); }
}
```

---

## Testing

### JUnit 5

- `@Test`: marks a method as a test case.
- `@BeforeEach`: runs before **each** test method. Used for setup.
- `@AfterEach`: runs after **each** test method. Used for teardown.
- `@BeforeAll`: runs once before **all** test methods in the class. Method must be `static`.
- `@AfterAll`: runs once after **all** test methods. Method must be `static`.
- `@DisplayName("description")`: human-readable test name shown in reports.
- `@Nested`: groups related tests into a nested inner class.
- `@ParameterizedTest`: runs the same test with multiple inputs.
- `@ValueSource(...)` / `@CsvSource(...)` / `@MethodSource(...)`: provides test arguments.
- `@Disabled("reason")`: skips the test.

```java
import org.junit.jupiter.api.*;
import static org.assertj.core.api.Assertions.*;

@DisplayName("Calculator")
class CalculatorTest {

    private Calculator calculator;

    @BeforeAll
    static void initAll() {
        System.out.println("Running all calculator tests...");
    }

    @BeforeEach
    void setUp() {
        calculator = new Calculator();
    }

    @Test
    @DisplayName("adds two positive integers")
    void addPositives() {
        assertThat(calculator.add(2, 3)).isEqualTo(5);
    }

    @Test
    void divideByZeroThrows() {
        assertThatThrownBy(() -> calculator.divide(10, 0))
                .isInstanceOf(ArithmeticException.class)
                .hasMessage("/ by zero");
    }

    @ParameterizedTest
    @CsvSource({"1, 1, 2", "5, 3, 8", "-1, -1, -2"})
    void addParameterized(int a, int b, int expected) {
        assertThat(calculator.add(a, b)).isEqualTo(expected);
    }

    @Nested
    @DisplayName("division")
    class DivisionTests {

        @Test
        void dividePositives() {
            assertThat(calculator.divide(6, 2)).isEqualTo(3);
        }
    }
}
```

### Mockito

- `@Mock`: creates a mock of the annotated field. Does not require Spring context.
- `@InjectMocks`: creates an instance of the class under test and injects `@Mock` / `@Spy` fields into it.
- `@Spy`: wraps a real object — calls are real by default, but individual methods can be stubbed.
- `@ExtendWith(MockitoExtension.class)`: enables Mockito annotations in JUnit 5.
- `when(mock.method()).thenReturn(value)`: stubs a method to return a given value.
- `when(mock.method()).thenThrow(exception)`: stubs a method to throw an exception.
- `verify(mock, times(n)).method(args)`: asserts the method was called `n` times with the given args.
- `verify(mock, never()).method(args)`: asserts the method was never called.
- `ArgumentCaptor<T>`: captures arguments passed to a mock for assertion.

```java
@ExtendWith(MockitoExtension.class)
class UserServiceTest {

    @Mock
    private UserRepository userRepository;

    @Mock
    private PasswordEncoder passwordEncoder;

    @InjectMocks
    private UserService userService;

    @Test
    void createUser_success() {
        when(userRepository.existsByEmail("alice@example.com")).thenReturn(false);
        when(passwordEncoder.encode("password")).thenReturn("hashedPassword");
        when(userRepository.save(any(User.class))).thenAnswer(inv -> {
            User u = inv.getArgument(0);
            u.setId(1L);
            return u;
        });

        UserDto result = userService.createUser(
                new CreateUserRequest("Alice", "alice@example.com", "password"));

        assertThat(result.getId()).isEqualTo(1L);
        assertThat(result.getEmail()).isEqualTo("alice@example.com");

        verify(userRepository).existsByEmail("alice@example.com");
        verify(passwordEncoder).encode("password");
        verify(userRepository).save(any(User.class));
    }

    @Test
    void createUser_duplicateEmail_throws() {
        when(userRepository.existsByEmail(anyString())).thenReturn(true);

        assertThatThrownBy(() -> userService.createUser(
                new CreateUserRequest("Bob", "bob@example.com", "pass")))
                .isInstanceOf(IllegalArgumentException.class)
                .hasMessageContaining("Email already in use");

        verify(userRepository, never()).save(any());
    }

    @Test
    void createUser_captureArgument() {
        ArgumentCaptor<User> captor = ArgumentCaptor.forClass(User.class);
        when(userRepository.existsByEmail(anyString())).thenReturn(false);
        when(userRepository.save(any())).thenReturn(new User());

        userService.createUser(new CreateUserRequest("Carol", "carol@example.com", "abc"));

        verify(userRepository).save(captor.capture());
        assertThat(captor.getValue().getEmail()).isEqualTo("carol@example.com");
    }
}
```

### Mockito Quick Reference

```java
// --- Stubbing ---
when(mock.method(arg)).thenReturn(value);
when(mock.method(arg)).thenThrow(new RuntimeException("error"));
when(mock.method(arg)).thenAnswer(inv -> computeSomething(inv.getArgument(0)));
doNothing().when(mock).voidMethod();     // for void methods
doThrow(ex).when(mock).voidMethod();

// --- Argument Matchers ---
any()                                    // any non-null object
any(User.class)                          // any User instance
anyLong()                                // any long
anyString()                              // any String
eq("exact")                              // equals check
isNull()                                 // null
argThat(u -> u.getEmail().endsWith("@example.com"))  // custom predicate

// --- Verification ---
verify(mock).method(arg);
verify(mock, times(2)).method(arg);
verify(mock, atLeast(1)).method(arg);
verify(mock, atMost(3)).method(arg);
verify(mock, never()).method(arg);
verifyNoInteractions(mock);
verifyNoMoreInteractions(mock);
```

### Spring Boot Integration Tests

- `@SpringBootTest`: loads the **full** application context. Used for integration testing.
  - `webEnvironment = RANDOM_PORT`: starts the server on a random port.
  - `webEnvironment = MOCK`: uses a mock servlet context (default).
  - `properties = {"key=value"}`: overrides specific properties for the test.

- `@MockBean`: replaces a bean in the application context with a Mockito mock.

- `@AutoConfigureMockMvc`: auto-configures `MockMvc` for testing controllers without a real server.

- `@DataJpaTest`: loads only the JPA layer with an in-memory database. Faster than `@SpringBootTest`.

- `@WebMvcTest(Controller.class)`: loads only the web layer for a specific controller. Use `@MockBean` for services.

```java
// Slice test — web layer only
@WebMvcTest(UserController.class)
class UserControllerTest {

    @Autowired
    private MockMvc mockMvc;

    @MockBean
    private UserService userService;

    @Autowired
    private ObjectMapper objectMapper;

    @Test
    void getUser_returns200() throws Exception {
        UserDto dto = new UserDto(1L, "Alice", "alice@example.com");
        when(userService.findById(1L)).thenReturn(Optional.of(dto));

        mockMvc.perform(get("/api/users/1")
                        .contentType(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(jsonPath("$.name").value("Alice"))
                .andExpect(jsonPath("$.email").value("alice@example.com"));
    }

    @Test
    void createUser_invalidBody_returns400() throws Exception {
        CreateUserRequest bad = new CreateUserRequest("", "not-an-email", "x");

        mockMvc.perform(post("/api/users")
                        .contentType(MediaType.APPLICATION_JSON)
                        .content(objectMapper.writeValueAsString(bad)))
                .andExpect(status().isBadRequest());
    }
}

// Repository slice test
@DataJpaTest
class UserRepositoryTest {

    @Autowired
    private UserRepository userRepository;

    @Test
    void findByEmail_returnsUser() {
        User user = new User();
        user.setName("Alice");
        user.setEmail("alice@example.com");
        userRepository.save(user);

        Optional<User> found = userRepository.findByEmail("alice@example.com");
        assertThat(found).isPresent();
        assertThat(found.get().getName()).isEqualTo("Alice");
    }
}

// Full integration test
@SpringBootTest(webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT)
@TestPropertySource(properties = {
    "spring.datasource.url=jdbc:h2:mem:testdb",
    "spring.jpa.hibernate.ddl-auto=create-drop"
})
class UserIntegrationTest {

    @Autowired
    private TestRestTemplate restTemplate;

    @Test
    void createAndFetchUser() {
        CreateUserRequest request = new CreateUserRequest("Alice", "alice@example.com", "Password1");

        ResponseEntity<UserDto> response = restTemplate.postForEntity(
                "/api/users", request, UserDto.class);

        assertThat(response.getStatusCode()).isEqualTo(HttpStatus.CREATED);
        assertThat(response.getBody().getEmail()).isEqualTo("alice@example.com");
    }
}
```

---

## Common Test Annotations Summary

| Annotation                        | Purpose                                                    |
|-----------------------------------|------------------------------------------------------------|
| `@SpringBootTest`                 | Full application context integration test                  |
| `@WebMvcTest(Controller.class)`   | Web layer only — no service or repository beans            |
| `@DataJpaTest`                    | JPA layer only — H2 in-memory DB by default                |
| `@MockBean`                       | Replaces a Spring bean with a Mockito mock                 |
| `@Mock`                           | Mockito mock (no Spring context)                           |
| `@InjectMocks`                    | Class under test; receives `@Mock` and `@Spy` injections   |
| `@Spy`                            | Partial mock — real methods unless stubbed                 |
| `@ExtendWith(MockitoExtension)`   | Enables Mockito annotations in JUnit 5                     |
| `@Test`                           | Marks a test method                                        |
| `@BeforeEach` / `@AfterEach`      | Setup / teardown before/after each test                    |
| `@BeforeAll` / `@AfterAll`        | Setup / teardown once per class (must be `static`)         |
| `@DisplayName`                    | Custom name in test reports                                |
| `@Nested`                         | Groups related tests                                       |
| `@ParameterizedTest`              | Runs a test with multiple inputs                           |
| `@Disabled`                       | Skips the test                                             |

---

## Actuator

The Actuator exposes endpoints for monitoring and managing a running application.

```properties
management.endpoints.web.exposure.include=*
management.endpoint.health.show-details=always
management.server.port=9090   # separate port for management endpoints
```

| Endpoint               | Description                                   |
|------------------------|-----------------------------------------------|
| `/actuator/health`     | Application health status                     |
| `/actuator/info`       | Application metadata (name, version, etc.)    |
| `/actuator/metrics`    | JVM, HTTP, and custom metrics                 |
| `/actuator/env`        | Environment properties                        |
| `/actuator/beans`      | All registered Spring beans                   |
| `/actuator/mappings`   | All `@RequestMapping` routes                  |
| `/actuator/loggers`    | View and change log levels at runtime         |
| `/actuator/conditions` | Auto-configuration decisions (debug)          |
| `/actuator/threaddump` | Current thread dump                           |

Custom health indicator:

```java
@Component
public class DatabaseHealthIndicator implements HealthIndicator {

    private final DataSource dataSource;

    public DatabaseHealthIndicator(DataSource dataSource) {
        this.dataSource = dataSource;
    }

    @Override
    public Health health() {
        try (Connection conn = dataSource.getConnection()) {
            return Health.up().withDetail("database", "reachable").build();
        } catch (Exception e) {
            return Health.down().withDetail("error", e.getMessage()).build();
        }
    }
}
```

---

## Layers in Spring Boot

| Layer          | Annotation          | Responsibility                                          |
|----------------|---------------------|---------------------------------------------------------|
| Controller     | `@RestController`   | HTTP request/response; input validation; routing        |
| Service        | `@Service`          | Business logic; transaction management                  |
| Repository     | `@Repository`       | Database access; CRUD; query execution                  |
| Entity / Model | `@Entity`           | Domain objects; DB schema mapping                       |
| DTO            | (POJO / Record)     | Data transfer between layers; API contracts             |
| Config         | `@Configuration`    | Bean definitions; security; external integrations       |
| Exception      | `@ControllerAdvice` | Global error handling                                   |

---

## Spring Container

The Spring **IoC (Inversion of Control) Container** manages Bean lifecycle:

1. **Instantiation** — Spring creates the Bean instance.
2. **Dependency Injection** — Dependencies are injected via constructor, field, or setter.
3. **Post-processing** — `BeanPostProcessor` hooks run (e.g., `@PostConstruct`).
4. **Initialization** — `InitializingBean.afterPropertiesSet()` or `@PostConstruct`.
5. **In use** — The Bean serves requests.
6. **Destruction** — `DisposableBean.destroy()` or `@PreDestroy`.

```java
@Component
public class ConnectionPool {

    @PostConstruct
    public void init() {
        System.out.println("Opening connection pool...");
        // runs after all dependencies are injected
    }

    @PreDestroy
    public void cleanup() {
        System.out.println("Closing connection pool...");
        // runs before bean is removed from the context
    }
}
```

Two main container types:
- **`BeanFactory`**: lazy initialization; minimal (rarely used directly).
- **`ApplicationContext`**: eager initialization; full feature set (events, i18n, AOP). Always use this.

---

## WireMock

**WireMock** mocks external HTTP APIs during testing, letting you stub responses and verify calls without hitting real services.

- `stubFor(request)`: defines how WireMock should respond to a matching request.
- `verify(count, request)`: asserts that a request pattern was received a specific number of times.

```java
@SpringBootTest(webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT)
@WireMockTest(httpPort = 8089)
class PaymentGatewayTest {

    @Test
    void chargeCard_success() {
        stubFor(post(urlEqualTo("/charge"))
            .withHeader("Content-Type", containing("application/json"))
            .willReturn(aResponse()
                .withStatus(200)
                .withHeader("Content-Type", "application/json")
                .withBody("{\"status\":\"SUCCESS\",\"transactionId\":\"abc123\"}")));

        PaymentResult result = paymentGateway.charge("4111111111111111", 99.99);

        assertThat(result.getStatus()).isEqualTo("SUCCESS");

        verify(postRequestedFor(urlEqualTo("/charge"))
               .withRequestBody(matchingJsonPath("$.amount", equalTo("99.99"))));
    }

    @Test
    void chargeCard_timeout() {
        stubFor(post(urlEqualTo("/charge"))
            .willReturn(aResponse()
                .withStatus(200)
                .withFixedDelay(5000)));   // simulate 5-second delay

        assertThatThrownBy(() -> paymentGateway.charge("4111111111111111", 10.00))
                .isInstanceOf(TimeoutException.class);
    }
}
```

---

## Tomcat

**Tomcat** is the default embedded servlet container in Spring Boot. It handles HTTP connections and delegates requests to Spring's `DispatcherServlet`.

Request lifecycle:
1. Client sends HTTP request.
2. Tomcat accepts the connection and wraps it in `HttpServletRequest` / `HttpServletResponse`.
3. Tomcat routes the request to Spring's `DispatcherServlet`.
4. `DispatcherServlet` consults `HandlerMapping` to find the right `@Controller` / `@RestController`.
5. The handler method executes and returns a value.
6. `DispatcherServlet` uses `HttpMessageConverter` (e.g., Jackson) to serialize the response.
7. Tomcat sends the HTTP response back to the client.

Configure Tomcat in `application.properties`:

```properties
server.port=8080
server.tomcat.max-threads=200
server.tomcat.accept-count=100
server.tomcat.connection-timeout=20000
server.tomcat.accesslog.enabled=true
```

Raw servlet example (rarely needed in Spring Boot):

```java
@WebServlet(name = "exampleServlet", urlPatterns = "/example")
public class ExampleServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        resp.setContentType("text/plain");
        resp.getWriter().write("Hello from servlet");
    }
}

// Enable servlet scanning in the main class:
// @SpringBootApplication
// @ServletComponentScan
```

---

## Debugging Spring Apps

### Enable Debug Logging

```properties
logging.level.org.springframework.web=DEBUG
logging.level.org.springframework.security=DEBUG
logging.level.org.hibernate.SQL=DEBUG
logging.level.org.hibernate.type.descriptor.sql=TRACE   # logs bind parameters
debug=true   # prints full auto-configuration report on startup
```

### Remote Debugging

```bash
java -agentlib:jdwp=transport=dt_socket,server=y,suspend=n,address=*:5005 -jar app.jar
```

### H2 Console (dev)

```properties
spring.h2.console.enabled=true
spring.h2.console.path=/h2-console
spring.datasource.url=jdbc:h2:mem:testdb
```

### Useful Actuator Endpoints for Debugging

| Endpoint               | Use                                               |
|------------------------|---------------------------------------------------|
| `/actuator/conditions` | Which auto-configurations matched/were skipped    |
| `/actuator/beans`      | All registered beans and their types              |
| `/actuator/env`        | All resolved property values                      |
| `/actuator/mappings`   | All HTTP routes                                   |
| `/actuator/loggers`    | Change log level at runtime without restart       |

### Common Issues

| Problem                              | Likely Cause / Fix                                                     |
|--------------------------------------|------------------------------------------------------------------------|
| `NoSuchBeanDefinitionException`      | Missing `@Component` / `@Service`; not in component scan path          |
| `BeanCreationException`              | Exception in constructor or `@PostConstruct`; check stack trace        |
| `LazyInitializationException`        | Accessing lazy collection outside a transaction; add `@Transactional`  |
| `StackOverflowError` in JPA          | Circular reference in `toString()` or Jackson; use DTOs                |
| `DataIntegrityViolationException`    | Constraint violation; check entity `@Column` constraints               |
| `403 Forbidden`                      | Missing role/authority; check `SecurityFilterChain` configuration      |
| `401 Unauthorized`                   | Missing or invalid JWT; check filter order and token parsing           |
| `HttpMessageNotReadableException`    | Malformed JSON body; check field names match the DTO                   |
| `405 Method Not Allowed`             | Wrong HTTP method or missing mapping annotation                        |

---

## Aspect-Oriented Programming (AOP)

AOP separates **cross-cutting concerns** (logging, security, metrics, auditing) from business logic using proxies. Spring AOP intercepts method calls on Spring-managed beans.

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-aop</artifactId>
</dependency>
```

- `@EnableAspectJAutoProxy`: activates AOP proxy creation. Spring Boot auto-applies this with the starter.
- `@Aspect`: marks a class as an aspect. Must also be annotated with `@Component` (or defined as a `@Bean`).
- `@Order(n)`: sets execution order when multiple aspects match the same joinpoint (lower n = runs first).

### Advice Types

| Annotation | Fires |
|------------|-------|
| `@Before` | Before the method executes |
| `@After` | After the method (always — like `finally`) |
| `@AfterReturning` | After successful return — can inspect return value |
| `@AfterThrowing` | After an exception is thrown — can inspect the exception |
| `@Around` | Wraps the entire invocation; must call `pjp.proceed()` |

### Pointcut Expression Syntax

```
execution([modifiers] return-type [declaring-class.]method-name(params) [throws])
```

| Expression | Matches |
|------------|---------|
| `execution(* com.example.service.*.*(..))` | Any method in any class in the service package |
| `execution(public * *(..))` | Any public method |
| `execution(* com.example..*.*(..))` | Any method in `com.example` or any sub-package |
| `within(com.example.service.*)` | Any joinpoint inside the service package |
| `@annotation(Audited)` | Methods annotated with `@Audited` |
| `@within(org.springframework.stereotype.Service)` | Any class annotated with `@Service` |
| `bean(userService)` | All methods on bean named `userService` |
| `args(Long, ..)` | Methods whose first argument is `Long` |

Combine with `&&`, `||`, `!`:

```java
@Pointcut("execution(* com.example.service.*.*(..)) && !execution(* *.find*(..))")
public void serviceExceptReads() {}
```

### Full Aspect Example

```java
@Aspect
@Component
@Order(1)
public class LoggingAspect {

    private static final Logger log = LoggerFactory.getLogger(LoggingAspect.class);

    // Reusable pointcut
    @Pointcut("execution(* com.example.service.*.*(..))")
    public void serviceLayer() {}

    // Log method entry with arguments
    @Before("serviceLayer()")
    public void logBefore(JoinPoint jp) {
        log.info("--> {}.{}({})",
            jp.getTarget().getClass().getSimpleName(),
            jp.getSignature().getName(),
            Arrays.toString(jp.getArgs()));
    }

    // Measure execution time and log result
    @Around("serviceLayer()")
    public Object measureTime(ProceedingJoinPoint pjp) throws Throwable {
        long start = System.currentTimeMillis();
        try {
            Object result = pjp.proceed();
            log.info("<-- {} completed in {}ms",
                pjp.getSignature().getName(), System.currentTimeMillis() - start);
            return result;
        } catch (Throwable ex) {
            log.error("<-- {} failed in {}ms: {}",
                pjp.getSignature().getName(), System.currentTimeMillis() - start, ex.getMessage());
            throw ex;
        }
    }

    // Inspect the return value
    @AfterReturning(pointcut = "serviceLayer()", returning = "result")
    public void logReturn(JoinPoint jp, Object result) {
        log.debug("Returned: {}", result);
    }

    // Inspect exceptions
    @AfterThrowing(pointcut = "serviceLayer()", throwing = "ex")
    public void logException(JoinPoint jp, Exception ex) {
        log.error("Exception in {}: {}", jp.getSignature().getName(), ex.getMessage());
    }
}

// Custom annotation-driven audit aspect
@Target(ElementType.METHOD)
@Retention(RetentionPolicy.RUNTIME)
public @interface Audited { String action() default ""; }

@Aspect
@Component
public class AuditAspect {

    @Around("@annotation(audited)")
    public Object audit(ProceedingJoinPoint pjp, Audited audited) throws Throwable {
        String user = SecurityContextHolder.getContext().getAuthentication().getName();
        Object result = pjp.proceed();
        auditLogRepo.save(new AuditLog(user, audited.action(), Instant.now()));
        return result;
    }
}

// Usage
@Service
public class UserService {
    @Audited(action = "DELETE_USER")
    public void deleteUser(Long id) { ... }
}
```

> AOP proxies only intercept calls from **outside** the bean. `this.someMethod()` within the same class bypasses the proxy entirely.

---

## Caching

Spring's cache abstraction sits on top of any provider (Caffeine, Redis, EhCache, etc.) and is swapped without changing business code.

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-cache</artifactId>
</dependency>
<!-- Caffeine (in-process, fast) -->
<dependency>
    <groupId>com.github.ben-manes.caffeine</groupId>
    <artifactId>caffeine</artifactId>
</dependency>
```

```properties
# Caffeine — in-process
spring.cache.type=caffeine
spring.cache.caffeine.spec=maximumSize=1000,expireAfterWrite=10m

# Redis
spring.cache.type=redis
spring.data.redis.host=localhost
spring.data.redis.port=6379
spring.cache.redis.time-to-live=600000    # ms
```

- `@EnableCaching`: activates caching. Auto-applied by the Spring Boot starter.

- `@Cacheable(value, key, condition, unless)`: returns a cached result on cache hit; calls the method only on a miss.
  - `value`: cache name(s).
  - `key`: SpEL expression for the cache key (default: all method args).
  - `condition`: SpEL — only cache if `true`.
  - `unless`: SpEL — evaluated **after** the method returns; do not cache if `true`.

- `@CachePut(value, key)`: always calls the method **and** updates the cache. Use for write/update operations.

- `@CacheEvict(value, key, allEntries, beforeInvocation)`: removes cache entries.
  - `allEntries = true`: evict every entry in the named cache.
  - `beforeInvocation = true`: evict before the method runs (so eviction still happens on exception).

- `@Caching(cacheable, put, evict)`: groups multiple cache annotations on one method.

- `@CacheConfig(cacheNames)`: class-level default cache name, avoiding repetition on every method.

```java
@Service
@CacheConfig(cacheNames = "users")
public class UserService {

    // Cache result under key = id; method not called on hit
    @Cacheable(key = "#id")
    public UserDto getById(Long id) {
        return userRepo.findById(id).map(this::toDto)
            .orElseThrow(() -> new ResourceNotFoundException("User " + id));
    }

    // Conditional — only cache email results longer than 5 chars; skip null results
    @Cacheable(value = "users", key = "#email",
               condition = "#email.length() > 5",
               unless = "#result == null")
    public UserDto findByEmail(String email) { ... }

    // Always update the cache after a write
    @CachePut(key = "#result.id")
    public UserDto update(Long id, UpdateUserRequest req) { ... }

    // Remove a specific entry
    @CacheEvict(key = "#id")
    public void delete(Long id) { userRepo.deleteById(id); }

    // Clear the entire cache
    @CacheEvict(allEntries = true)
    public void evictAll() {}

    // Multiple evictions in one annotation
    @Caching(evict = {
        @CacheEvict(value = "users",  key = "#id"),
        @CacheEvict(value = "emails", allEntries = true),
    })
    public void suspend(Long id) { ... }
}
```

---

## Scheduling

Run tasks on a fixed schedule or cron expression in the background.

```java
@SpringBootApplication
@EnableScheduling   // activate the scheduler
public class MyApplication { ... }
```

- `@Scheduled`: marks a method as a scheduled task. Methods must have a `void` return type and no arguments.
  - `fixedRate`: run every N ms from the **start** of the last execution.
  - `fixedDelay`: run N ms after the **end** of the last execution.
  - `initialDelay`: wait N ms before the first execution.
  - `cron`: six-field cron expression (`second minute hour day month weekday`).
  - `zone`: timezone string (default: JVM default).

**Cron expression format:**

```
┌── second  (0-59)
│ ┌── minute (0-59)
│ │ ┌── hour   (0-23)
│ │ │ ┌── day-of-month (1-31)
│ │ │ │ ┌── month (1-12 or JAN-DEC)
│ │ │ │ │ ┌── day-of-week (0-7 or MON-SUN; 0=Sunday)
* * * * * *
```

| Expression | Meaning |
|------------|---------|
| `0 * * * * *` | Every minute at second 0 |
| `0 0 * * * *` | Every hour |
| `0 0 8 * * MON-FRI` | Weekdays at 08:00 |
| `0 0 0 1 * *` | First day of every month at midnight |
| `0 */15 9-17 * * MON-FRI` | Every 15 min during business hours |
| `@daily` | Midnight every day (alias) |

```java
@Component
public class ScheduledTasks {

    @Scheduled(fixedRate = 5_000)
    public void heartbeat() { log.debug("Alive at {}", Instant.now()); }

    // 10 seconds after the previous run finishes
    @Scheduled(fixedDelay = 10_000, initialDelay = 5_000)
    public void processQueue() { /* won't overlap */ }

    // Cron driven by a property — safe default if property is absent
    @Scheduled(cron = "${reports.cron:0 0 8 * * MON-FRI}", zone = "Europe/Vienna")
    public void sendDailyReport() { reportService.generateAndSend(); }
}
```

**Parallel scheduling** — by default tasks share a single thread. Configure a pool:

```java
@Configuration
public class SchedulerConfig implements SchedulingConfigurer {

    @Override
    public void configureTasks(ScheduledTaskRegistrar registrar) {
        ThreadPoolTaskScheduler scheduler = new ThreadPoolTaskScheduler();
        scheduler.setPoolSize(5);
        scheduler.setThreadNamePrefix("sched-");
        scheduler.initialize();
        registrar.setTaskScheduler(scheduler);
    }
}
```

---

## Async Processing

Offload method execution to a thread pool without blocking the caller.

```java
@SpringBootApplication
@EnableAsync   // activate async method execution
public class MyApplication { ... }
```

- `@Async`: executes the annotated method in a separate thread. Return type must be `void`, `Future<T>`, or `CompletableFuture<T>`.

> `@Async` only works when the method is called from **outside** the bean (proxy constraint). `this.asyncMethod()` runs synchronously.

```java
@Service
public class NotificationService {

    // Fire-and-forget — does not block the caller
    @Async
    public void sendWelcomeEmail(String to) {
        emailSender.send(buildEmail(to));
    }

    // Caller can chain on or await the result
    @Async
    public CompletableFuture<String> generateReport(Long userId) {
        String report = heavyProcessing(userId);
        return CompletableFuture.completedFuture(report);
    }
}

// Usage in a REST controller
@PostMapping("/api/users")
public ResponseEntity<UserDto> createUser(@Valid @RequestBody CreateUserRequest req) {
    UserDto user = userService.create(req);
    notificationService.sendWelcomeEmail(req.getEmail());   // non-blocking
    return ResponseEntity.status(201).body(user);
}
```

**Custom executor** (configure pool size, queue capacity):

```java
@Configuration
@EnableAsync
public class AsyncConfig {

    @Bean(name = "taskExecutor")
    public Executor taskExecutor() {
        ThreadPoolTaskExecutor executor = new ThreadPoolTaskExecutor();
        executor.setCorePoolSize(4);
        executor.setMaxPoolSize(16);
        executor.setQueueCapacity(100);
        executor.setThreadNamePrefix("async-");
        executor.setRejectedExecutionHandler(new ThreadPoolExecutor.CallerRunsPolicy());
        executor.initialize();
        return executor;
    }
}

@Async("taskExecutor")   // use a specific named executor
public CompletableFuture<String> runOnCustomPool() { ... }
```

---

## Application Events

Spring's publish-subscribe event system for loose coupling between components.

- `ApplicationEventPublisher.publishEvent(event)`: publishes an event synchronously to all registered listeners.
- `@EventListener`: registers a method as a listener. The parameter type selects which event it handles.
- `@TransactionalEventListener(phase)`: like `@EventListener` but fires relative to the enclosing transaction.
  - `phase`: `AFTER_COMMIT` (default), `AFTER_ROLLBACK`, `AFTER_COMPLETION`, `BEFORE_COMMIT`.

```java
// 1. Define the event (use a Java record for immutability — Spring 6+)
public record UserCreatedEvent(Long userId, String email) {}

// 2. Publish from a service
@Service
public class UserService {

    private final ApplicationEventPublisher publisher;

    @Transactional
    public UserDto createUser(CreateUserRequest req) {
        User user = userRepo.save(new User(req.getEmail()));
        publisher.publishEvent(new UserCreatedEvent(user.getId(), user.getEmail()));
        return toDto(user);
    }
}

// 3. Listen anywhere in the context
@Component
public class UserEventListeners {

    // Synchronous — runs inside the same transaction as the publisher
    @EventListener
    public void onCreated(UserCreatedEvent e) {
        log.info("User {} was created", e.email());
    }

    // Fires AFTER transaction commits — safe to call external services
    @TransactionalEventListener(phase = TransactionPhase.AFTER_COMMIT)
    public void sendWelcomeEmail(UserCreatedEvent e) {
        emailService.send(e.email());
    }

    // Asynchronous listener — runs in a separate thread
    @Async
    @EventListener
    public void updateSearchIndex(UserCreatedEvent e) {
        searchService.index(e.userId());
    }
}
```

**Built-in Spring Boot events:**

| Event | When |
|-------|------|
| `ApplicationStartingEvent` | Very start of the run |
| `ApplicationEnvironmentPreparedEvent` | Environment is ready, context not yet created |
| `ApplicationContextInitializedEvent` | Context initialised, beans not loaded |
| `ApplicationPreparedEvent` | Context loaded, not yet refreshed |
| `ApplicationStartedEvent` | Context refreshed, runners not yet called |
| `ApplicationReadyEvent` | App ready to serve requests |
| `ApplicationFailedEvent` | Startup failed |
| `ContextRefreshedEvent` | Context refreshed (also fires on Spring without Boot) |

```java
@EventListener(ApplicationReadyEvent.class)
public void onStartup() { log.info("Server ready — running post-startup tasks"); }
```

---

## REST Clients

### RestTemplate (Legacy — synchronous, blocking)

```java
@Configuration
public class RestConfig {

    @Bean
    public RestTemplate restTemplate(RestTemplateBuilder builder) {
        return builder
            .connectTimeout(Duration.ofSeconds(5))
            .readTimeout(Duration.ofSeconds(30))
            .build();
    }
}

@Service
public class GithubService {

    private final RestTemplate restTemplate;
    private static final String BASE = "https://api.github.com";

    // GET — deserialise response body
    public GithubUser getUser(String username) {
        return restTemplate.getForObject(BASE + "/users/{u}", GithubUser.class, username);
    }

    // GET with custom headers
    public ResponseEntity<GithubUser> getUserWithHeaders(String username) {
        HttpHeaders headers = new HttpHeaders();
        headers.setBearerAuth(token);
        return restTemplate.exchange(
            BASE + "/users/{u}", HttpMethod.GET,
            new HttpEntity<>(headers), GithubUser.class, username
        );
    }

    // POST
    public GithubRepo createRepo(CreateRepoRequest body) {
        return restTemplate.postForObject(BASE + "/user/repos", body, GithubRepo.class);
    }

    // PUT / DELETE
    public void updateRepo(String name, UpdateRepoRequest body) {
        restTemplate.put(BASE + "/repos/{name}", body, name);
    }

    public void deleteRepo(String name) {
        restTemplate.delete(BASE + "/repos/{name}", name);
    }
}
```

### WebClient (Modern — reactive / non-blocking)

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-webflux</artifactId>
</dependency>
```

```java
@Configuration
public class WebClientConfig {

    @Bean
    public WebClient githubClient(WebClient.Builder builder) {
        return builder
            .baseUrl("https://api.github.com")
            .defaultHeader("Authorization", "Bearer " + token)
            .defaultHeader(HttpHeaders.ACCEPT, "application/vnd.github.v3+json")
            .build();
    }
}

@Service
public class GithubService {

    private final WebClient githubClient;

    // Reactive Mono
    public Mono<GithubUser> getUser(String username) {
        return githubClient.get()
            .uri("/users/{u}", username)
            .retrieve()
            .onStatus(HttpStatusCode::is4xxClientError,
                res -> Mono.error(new ResourceNotFoundException("User: " + username)))
            .bodyToMono(GithubUser.class);
    }

    // Blocking wrapper for use in servlet apps
    public GithubUser getUserBlocking(String username) {
        return getUser(username).block(Duration.ofSeconds(10));
    }

    // Reactive Flux (stream of items)
    public Flux<GithubRepo> listRepos(String username) {
        return githubClient.get()
            .uri("/users/{u}/repos?per_page=100", username)
            .retrieve()
            .bodyToFlux(GithubRepo.class);
    }

    // POST with body
    public Mono<GithubRepo> createRepo(CreateRepoRequest body) {
        return githubClient.post()
            .uri("/user/repos")
            .bodyValue(body)
            .retrieve()
            .bodyToMono(GithubRepo.class);
    }
}
```

### Declarative HTTP Client (`@HttpExchange` — Spring 6 / Boot 3)

Define an interface; Spring generates the implementation at runtime — similar to Spring Data repositories.

```java
// Define the interface
@HttpExchange("https://api.github.com")
public interface GithubClient {

    @GetExchange("/users/{username}")
    GithubUser getUser(@PathVariable String username);

    @GetExchange("/users/{username}/repos")
    List<GithubRepo> getRepos(@PathVariable String username,
                              @RequestParam(defaultValue = "30") int per_page);

    @PostExchange("/user/repos")
    GithubRepo createRepo(@RequestBody CreateRepoRequest body);

    @DeleteExchange("/repos/{owner}/{repo}")
    void deleteRepo(@PathVariable String owner, @PathVariable String repo);
}

// Register as a bean
@Configuration
public class HttpClientConfig {

    @Bean
    public GithubClient githubClient(WebClient.Builder builder) {
        WebClient wc = builder.defaultHeader("Authorization", "Bearer " + token).build();
        return HttpServiceProxyFactory
            .builderFor(WebClientAdapter.create(wc))
            .build()
            .createClient(GithubClient.class);
    }
}
```

---

## File Uploads

```properties
# application.properties
spring.servlet.multipart.max-file-size=10MB
spring.servlet.multipart.max-request-size=50MB
```

- `MultipartFile`: represents a file received in a multipart request.
  - `getOriginalFilename()`: original filename supplied by the client — **never trust this directly**.
  - `getContentType()`: MIME type.
  - `getSize()`: file size in bytes.
  - `getBytes()`: full content as `byte[]`.
  - `getInputStream()`: content as a stream.
  - `transferTo(Path dest)`: save to disk efficiently.

```java
@RestController
@RequestMapping("/api/files")
public class FileController {

    private final Path uploadDir = Path.of("uploads");

    @PostConstruct
    void init() throws IOException { Files.createDirectories(uploadDir); }

    // Single file upload
    @PostMapping("/upload")
    public ResponseEntity<Map<String, Object>> upload(
            @RequestParam("file") MultipartFile file) throws IOException {

        if (file.isEmpty()) return ResponseEntity.badRequest().build();

        // Sanitise the filename — never use the client-supplied name directly in a path
        String original = StringUtils.cleanPath(Objects.requireNonNull(file.getOriginalFilename()));
        if (original.contains("..")) throw new AppError("Invalid filename", 400);
        String stored = UUID.randomUUID() + "_" + original;

        file.transferTo(uploadDir.resolve(stored));

        return ResponseEntity.ok(Map.of(
            "filename", stored,
            "size",     file.getSize(),
            "type",     file.getContentType()
        ));
    }

    // Multiple files
    @PostMapping("/upload-batch")
    public List<String> uploadBatch(@RequestParam("files") List<MultipartFile> files)
            throws IOException {
        List<String> stored = new ArrayList<>();
        for (MultipartFile f : files) {
            String name = UUID.randomUUID() + "_" + f.getOriginalFilename();
            f.transferTo(uploadDir.resolve(name));
            stored.add(name);
        }
        return stored;
    }

    // Download a file
    @GetMapping("/{filename:.+}")
    public ResponseEntity<Resource> download(@PathVariable String filename) throws IOException {
        Path path = uploadDir.resolve(filename).normalize();
        if (!path.startsWith(uploadDir)) throw new AppError("Access denied", 403);  // path traversal guard

        Resource resource = new UrlResource(path.toUri());
        if (!resource.exists()) return ResponseEntity.notFound().build();

        return ResponseEntity.ok()
            .header(HttpHeaders.CONTENT_DISPOSITION, "attachment; filename=\"" + filename + "\"")
            .contentType(MediaType.APPLICATION_OCTET_STREAM)
            .body(resource);
    }
}
```

---

## Lombok

Lombok generates Java boilerplate at compile time via annotations. Install the IDE plugin alongside the Maven dependency.

```xml
<dependency>
    <groupId>org.projectlombok</groupId>
    <artifactId>lombok</artifactId>
    <optional>true</optional>   <!-- not bundled in the final JAR -->
</dependency>
```

| Annotation | What it generates |
|------------|-------------------|
| `@Getter` | Getter for every field |
| `@Setter` | Setter for every non-final field |
| `@ToString` | `toString()` with all fields |
| `@EqualsAndHashCode` | `equals()` and `hashCode()` based on fields |
| `@NoArgsConstructor` | No-argument constructor (required by JPA) |
| `@AllArgsConstructor` | Constructor with all fields |
| `@RequiredArgsConstructor` | Constructor for `final` / `@NonNull` fields |
| `@Data` | `@Getter + @Setter + @ToString + @EqualsAndHashCode + @RequiredArgsConstructor` |
| `@Builder` | Builder pattern — `MyClass.builder().field(value).build()` |
| `@Value` | Immutable POJO — all fields `private final`, no setters |
| `@Slf4j` | Injects `private static final Logger log = LoggerFactory.getLogger(...)` |
| `@NonNull` | Adds a null check in setter and constructor; throws NPE |
| `@SneakyThrows` | Rethrows checked exceptions without declaring `throws` |
| `@With` | Generates `withField(value)` that returns a copy with the field changed |

```java
// DTO — concise and immutable with builder
@Value
@Builder
public class UserDto {
    Long   id;
    String email;
    String name;
}

UserDto dto = UserDto.builder().id(1L).email("alice@example.com").name("Alice").build();

// JPA entity — careful Lombok usage
@Entity
@Table(name = "users")
@Getter
@Setter
@NoArgsConstructor                             // JPA requires this
@EqualsAndHashCode(of = "id")                  // base only on id — avoids lazy-load issues
@ToString(exclude = {"password", "orders"})    // exclude sensitive / lazy fields
public class User {

    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String email;
    private String password;

    @OneToMany(mappedBy = "user", fetch = FetchType.LAZY)
    private List<Order> orders;
}

// Service with automatic logger
@Service
@Slf4j
@RequiredArgsConstructor                       // generates constructor for all final fields
public class UserService {

    private final UserRepository userRepo;    // injected via @RequiredArgsConstructor
    private final PasswordEncoder encoder;

    public void createUser(CreateUserRequest req) {
        log.info("Creating user: {}", req.getEmail());   // log is auto-injected by @Slf4j
    }
}
```

> **Avoid `@Data` on JPA entities** — it generates `equals/hashCode` on all fields which causes issues with lazy loading and `StackOverflowError` in bidirectional relationships. Use `@Getter @Setter @EqualsAndHashCode(of = "id")` instead.

---

---

# Pure Spring Framework

Spring Boot is an opinionated layer **on top of** the Spring Framework. Understanding the core framework is essential for advanced configuration, multi-module projects, non-Boot applications, and debugging unexpected Spring behaviour.

```xml
<!-- Minimal Spring Core (no Boot) -->
<dependency>
    <groupId>org.springframework</groupId>
    <artifactId>spring-context</artifactId>
    <version>6.1.0</version>
</dependency>
<!-- Spring Web MVC (no Boot) -->
<dependency>
    <groupId>org.springframework</groupId>
    <artifactId>spring-webmvc</artifactId>
    <version>6.1.0</version>
</dependency>
```

---

## ApplicationContext

The **IoC (Inversion of Control) container** creates, configures, wires, and manages the lifecycle of beans. `ApplicationContext` is the main interface.

### ApplicationContext Types

| Type | Config source | Typical use |
|------|--------------|-------------|
| `AnnotationConfigApplicationContext` | `@Configuration` classes / `@Component` scan | Standalone, tests |
| `ClassPathXmlApplicationContext` | XML on classpath | Legacy apps |
| `FileSystemXmlApplicationContext` | XML from filesystem | Legacy apps |
| `AnnotationConfigWebApplicationContext` | Java config in a web app | Spring MVC without Boot |
| `GenericWebApplicationContext` | Programmatic | Framework integration |

```java
// Standalone Java config
ApplicationContext ctx = new AnnotationConfigApplicationContext(AppConfig.class);

UserService svc  = ctx.getBean(UserService.class);             // by type
UserService svc2 = (UserService) ctx.getBean("userService");   // by name
String[]    names = ctx.getBeanNamesForType(UserService.class); // all matching names

// Graceful shutdown — fires @PreDestroy callbacks
((ConfigurableApplicationContext) ctx).close();

// With component scanning
ApplicationContext ctx2 = new AnnotationConfigApplicationContext("com.example");
```

### XML Configuration (Legacy)

```xml
<!-- beans.xml -->
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
           http://www.springframework.org/schema/beans/spring-beans.xsd">

    <bean id="userService" class="com.example.UserService">
        <constructor-arg ref="userRepository"/>         <!-- constructor injection -->
        <property name="maxResults" value="100"/>       <!-- setter injection -->
    </bean>

    <bean id="userRepository" class="com.example.UserRepositoryImpl"/>

    <bean id="report" class="com.example.ReportGenerator" scope="prototype"/>
</beans>
```

```java
ApplicationContext ctx = new ClassPathXmlApplicationContext("beans.xml");
```

### Java Configuration

```java
@Configuration
@ComponentScan("com.example")
@EnableTransactionManagement
@PropertySource("classpath:app.properties")
public class AppConfig {

    @Value("${db.url}")
    private String dbUrl;

    @Bean
    public DataSource dataSource() {
        DriverManagerDataSource ds = new DriverManagerDataSource();
        ds.setUrl(dbUrl);
        ds.setUsername("user");
        ds.setPassword("pass");
        return ds;
    }

    @Bean
    public PlatformTransactionManager transactionManager(DataSource ds) {
        return new DataSourceTransactionManager(ds);
    }
}
```

---

## Bean Lifecycle (Deep Dive)

```
Instantiate bean
    ↓
Populate properties via dependency injection
    ↓
BeanNameAware.setBeanName()
    ↓
ApplicationContextAware.setApplicationContext()
    ↓
BeanPostProcessor.postProcessBeforeInitialization()   ← @PostConstruct processing happens here
    ↓
InitializingBean.afterPropertiesSet() / custom init-method
    ↓
BeanPostProcessor.postProcessAfterInitialization()    ← AOP proxies are created here
    ↓
Bean is ready — serves requests
    ↓
DisposableBean.destroy() / custom destroy-method      ← on context close
```

**Lifecycle interfaces (prefer annotations — less coupling):**

```java
// Interface-based (tightly coupled to Spring)
@Component
public class DatabasePool implements InitializingBean, DisposableBean, BeanNameAware {

    @Override public void setBeanName(String name) { /* bean name is known */ }
    @Override public void afterPropertiesSet() { openConnections(); }
    @Override public void destroy() { closeConnections(); }
}

// Annotation-based (preferred — no Spring imports needed in the class)
@Component
public class DatabasePool {
    @PostConstruct public void init()     { openConnections(); }
    @PreDestroy    public void cleanup()  { closeConnections(); }
}
```

**`BeanPostProcessor`** — intercepts every bean during container startup:

```java
@Component
public class ValidatingBeanPostProcessor implements BeanPostProcessor {

    @Override
    public Object postProcessBeforeInitialization(Object bean, String beanName) {
        // Validate or wrap beans before they are initialised
        return bean;
    }

    @Override
    public Object postProcessAfterInitialization(Object bean, String beanName) {
        // This is where Spring's AOP proxy wrapping happens internally
        return bean;
    }
}
```

**`BeanFactoryPostProcessor`** — modifies bean **definitions** before any beans are instantiated (e.g., `PropertySourcesPlaceholderConfigurer` resolves `${...}` placeholders here):

```java
@Component
public class MyBFPP implements BeanFactoryPostProcessor {
    @Override
    public void postProcessBeanFactory(ConfigurableListableBeanFactory factory) {
        BeanDefinition def = factory.getBeanDefinition("userService");
        def.setScope("prototype");   // change scope programmatically
    }
}
```

---

## Spring JDBC

Direct SQL with result mapping — simpler than JPA, no ORM overhead, full control over queries.

```xml
<dependency>
    <groupId>org.springframework</groupId>
    <artifactId>spring-jdbc</artifactId>
</dependency>
```

```java
@Configuration
public class JdbcConfig {
    @Bean
    public JdbcTemplate jdbcTemplate(DataSource ds) { return new JdbcTemplate(ds); }

    @Bean
    public NamedParameterJdbcTemplate namedJdbcTemplate(DataSource ds) {
        return new NamedParameterJdbcTemplate(ds);
    }
}
```

**`JdbcTemplate` core methods:**

| Method | Returns | Use |
|--------|---------|-----|
| `queryForObject(sql, type, args...)` | `T` | Single scalar value |
| `queryForObject(sql, rowMapper, args...)` | `T` | Single mapped row |
| `query(sql, rowMapper, args...)` | `List<T>` | Multiple rows |
| `queryForList(sql, type, args...)` | `List<T>` | List of scalars |
| `queryForMap(sql, args...)` | `Map<String,Object>` | Single row as map |
| `update(sql, args...)` | `int` | INSERT / UPDATE / DELETE |
| `batchUpdate(sql, batchArgs)` | `int[]` | Batch DML |
| `execute(sql)` | `void` | DDL |

```java
@Repository
public class UserJdbcRepository {

    private final JdbcTemplate          jdbc;
    private final NamedParameterJdbcTemplate namedJdbc;

    // RowMapper — converts one ResultSet row to a domain object
    private final RowMapper<User> userMapper = (rs, n) -> {
        User u = new User();
        u.setId(rs.getLong("id"));
        u.setEmail(rs.getString("email"));
        u.setCreatedAt(rs.getTimestamp("created_at").toLocalDateTime());
        return u;
    };

    public List<User> findAll() {
        return jdbc.query("SELECT * FROM users ORDER BY id", userMapper);
    }

    public Optional<User> findById(Long id) {
        var rows = jdbc.query("SELECT * FROM users WHERE id = ?", userMapper, id);
        return rows.stream().findFirst();
    }

    // Named parameters — safer and more readable for complex queries
    public List<User> findByRole(String role) {
        var params = new MapSqlParameterSource("role", role);
        return namedJdbc.query("SELECT * FROM users WHERE role = :role", params, userMapper);
    }

    // INSERT returning the generated key
    public Long insert(User user) {
        var params = new MapSqlParameterSource()
            .addValue("email", user.getEmail())
            .addValue("name",  user.getName());
        KeyHolder kh = new GeneratedKeyHolder();
        namedJdbc.update(
            "INSERT INTO users (email, name, created_at) VALUES (:email, :name, NOW())",
            params, kh
        );
        return kh.getKey().longValue();
    }

    public int update(User user) {
        return jdbc.update("UPDATE users SET email = ?, name = ? WHERE id = ?",
            user.getEmail(), user.getName(), user.getId());
    }

    public int deleteById(Long id) {
        return jdbc.update("DELETE FROM users WHERE id = ?", id);
    }

    public long count() {
        return jdbc.queryForObject("SELECT COUNT(*) FROM users", Long.class);
    }

    // Batch insert
    public void insertAll(List<User> users) {
        jdbc.batchUpdate(
            "INSERT INTO users (email, name) VALUES (?, ?)",
            users.stream().map(u -> new Object[]{ u.getEmail(), u.getName() }).toList()
        );
    }
}
```

---

## Transaction Management (Deep Dive)

### Propagation Levels

Controls what happens when a `@Transactional` method is called while a transaction is already active.

| Propagation | Behaviour |
|-------------|-----------|
| `REQUIRED` | Join the existing transaction, or create a new one (default) |
| `REQUIRES_NEW` | Always create a new transaction; suspend the existing one |
| `NESTED` | Create a savepoint inside the existing transaction — roll back to savepoint on failure |
| `SUPPORTS` | Run in a transaction if one exists; otherwise run non-transactionally |
| `NOT_SUPPORTED` | Always run non-transactionally; suspend any existing transaction |
| `MANDATORY` | Must run inside an existing transaction; throw if none exists |
| `NEVER` | Must run non-transactionally; throw if a transaction is active |

### Isolation Levels

Controls what concurrent transactions see from each other.

| Isolation | Dirty Read | Non-Repeatable Read | Phantom Read |
|-----------|------------|---------------------|--------------|
| `READ_UNCOMMITTED` | possible | possible | possible |
| `READ_COMMITTED` (PG default) | prevented | possible | possible |
| `REPEATABLE_READ` | prevented | prevented | possible |
| `SERIALIZABLE` | prevented | prevented | prevented |

```java
@Service
public class PaymentService {

    private final AccountRepository accountRepo;
    private final AuditRepository   auditRepo;

    // REQUIRES_NEW — audit always saved even if the outer transaction rolls back
    @Transactional(propagation = Propagation.REQUIRES_NEW)
    public void logAudit(AuditEntry entry) {
        auditRepo.save(entry);
    }

    // NESTED — caller can catch this exception and recover without a full rollback
    @Transactional(propagation = Propagation.NESTED)
    public void tryReserveStock(Long itemId, int qty) {
        inventoryRepo.reserve(itemId, qty);
    }

    // Custom isolation level
    @Transactional(isolation = Isolation.REPEATABLE_READ)
    public BigDecimal getBalance(Long accountId) {
        // Same read within the transaction will always return the same value
        return accountRepo.getBalance(accountId);
    }

    // rollbackFor — roll back on checked exceptions too (default is only RuntimeException)
    @Transactional(rollbackFor = IOException.class)
    public void processAndEmail(Long orderId) throws IOException {
        orderRepo.markProcessed(orderId);
        emailService.send(orderId);  // throws checked IOException
    }

    // noRollbackFor — do NOT roll back for a specific exception type
    @Transactional(noRollbackFor = ResourceNotFoundException.class)
    public void process(Long orderId) { ... }
}
```

### Programmatic Transactions (TransactionTemplate)

Use when declarative `@Transactional` granularity is insufficient.

```java
@Service
public class OrderService {

    private final TransactionTemplate txTemplate;

    public OrderService(PlatformTransactionManager txManager) {
        this.txTemplate = new TransactionTemplate(txManager);
    }

    public OrderDto placeOrder(CreateOrderRequest req) {
        return txTemplate.execute(status -> {
            try {
                Order order = orderRepo.save(new Order(req));
                inventoryService.reserve(req.getItems());
                return toDto(order);
            } catch (InsufficientStockException ex) {
                status.setRollbackOnly();  // mark for rollback without throwing
                throw ex;
            }
        });
    }
}
```

---

## Spring Expression Language (SpEL)

A powerful expression language used in `@Value`, `@Cacheable`, `@PreAuthorize`, `@ConditionalOnExpression`, and XML config.

**Syntax overview:**

| Expression | Evaluates to |
|------------|-------------|
| `#{ 2 * 60 * 60 }` | `7200` |
| `#{ 'hello'.toUpperCase() }` | `"HELLO"` |
| `#{ T(Math).sqrt(16) }` | `4.0` |
| `#{ T(System).currentTimeMillis() }` | current epoch ms |
| `#{ @myBean.getValue() }` | calls `getValue()` on bean `myBean` |
| `#{ systemProperties['user.home'] }` | JVM system property |
| `#{ systemEnvironment['HOME'] }` | OS environment variable |
| `#{ list.?[age > 18] }` | selection — filter list |
| `#{ list.![name] }` | projection — extract field from each element |
| `#{ value ?: 'default' }` | Elvis operator — default if null |

```java
@Component
public class SpelExamples {

    @Value("#{ 2 * 60 * 60 }")
    private int twoHoursInSeconds;                          // 7200

    @Value("#{ 'App: ' + '${spring.application.name}' }")  // SpEL + property placeholder
    private String appLabel;

    @Value("#{ T(Math).random() * 100 }")
    private double randomScore;

    @Value("#{ @dataSource.connection.catalog }")           // invoke method on a bean
    private String dbName;

    @Value("#{ systemEnvironment['HOME'] ?: '/tmp' }")      // Elvis — default if missing
    private String homeDir;
}

// In @Cacheable — composite key including method name
@Cacheable(value = "users", key = "#root.method.name + ':' + #id")
public UserDto getUser(Long id) { ... }

// In @PreAuthorize — access args and authentication object
@PreAuthorize("#user.id == authentication.principal.id or hasRole('ADMIN')")
public void updateProfile(UserDto user) { ... }
```

---

## Spring MVC (Without Spring Boot)

Manually configure Spring MVC in a standard Servlet container (standalone Tomcat, Jetty, etc.).

**`WebApplicationInitializer`** replaces `web.xml`:

```java
public class WebAppInitializer implements WebApplicationInitializer {

    @Override
    public void onStartup(ServletContext servletContext) {
        // Root application context (services, repositories)
        AnnotationConfigWebApplicationContext rootCtx = new AnnotationConfigWebApplicationContext();
        rootCtx.register(RootConfig.class);
        servletContext.addListener(new ContextLoaderListener(rootCtx));

        // Web context (controllers, view resolvers)
        AnnotationConfigWebApplicationContext webCtx = new AnnotationConfigWebApplicationContext();
        webCtx.register(WebMvcConfig.class);

        // Register the DispatcherServlet
        ServletRegistration.Dynamic dispatcher =
            servletContext.addServlet("dispatcher", new DispatcherServlet(webCtx));
        dispatcher.setLoadOnStartup(1);
        dispatcher.addMapping("/");
    }
}
```

**`WebMvcConfigurer`** — MVC customisation hooks:

```java
@Configuration
@EnableWebMvc
@ComponentScan("com.example.controller")
public class WebMvcConfig implements WebMvcConfigurer {

    // Thymeleaf / JSP view resolver
    @Bean
    public InternalResourceViewResolver viewResolver() {
        InternalResourceViewResolver r = new InternalResourceViewResolver();
        r.setPrefix("/WEB-INF/views/");
        r.setSuffix(".jsp");
        return r;
    }

    // Static resources
    @Override
    public void addResourceHandlers(ResourceHandlerRegistry registry) {
        registry.addResourceHandler("/static/**")
                .addResourceLocations("/WEB-INF/static/")
                .setCachePeriod(3600);
    }

    // Request interceptors
    @Override
    public void addInterceptors(InterceptorRegistry registry) {
        registry.addInterceptor(new LoggingInterceptor())
                .addPathPatterns("/**")
                .excludePathPatterns("/static/**");
    }

    // CORS
    @Override
    public void addCorsMappings(CorsRegistry registry) {
        registry.addMapping("/api/**")
                .allowedOrigins("https://frontend.example.com")
                .allowedMethods("GET", "POST", "PUT", "DELETE")
                .allowCredentials(true)
                .maxAge(3600);
    }

    // Custom type converters
    @Override
    public void addFormatters(FormatterRegistry registry) {
        registry.addConverter(new StringToLocalDateConverter());
    }
}
```

**`HandlerInterceptor`** — equivalent to a Filter but Spring-aware:

```java
public class LoggingInterceptor implements HandlerInterceptor {

    @Override
    public boolean preHandle(HttpServletRequest req, HttpServletResponse res, Object handler) {
        req.setAttribute("startTime", System.currentTimeMillis());
        log.info("--> {} {}", req.getMethod(), req.getRequestURI());
        return true;  // return false to abort the request
    }

    @Override
    public void postHandle(HttpServletRequest req, HttpServletResponse res,
                           Object handler, ModelAndView mav) {
        // After handler method, before view rendering — can modify ModelAndView
    }

    @Override
    public void afterCompletion(HttpServletRequest req, HttpServletResponse res,
                                Object handler, Exception ex) {
        long ms = System.currentTimeMillis() - (long) req.getAttribute("startTime");
        log.info("<-- {} {}ms", req.getRequestURI(), ms);
    }
}
```

---

## Spring Core Utilities

### Environment & Properties

```java
@Component
public class EnvUsage {

    @Autowired
    private Environment env;

    public void show() {
        String url    = env.getProperty("spring.datasource.url");
        int    port   = env.getProperty("server.port", Integer.class, 8080);
        String active = Arrays.toString(env.getActiveProfiles());
    }
}
```

### ResourceLoader

```java
@Component
public class ResourceUsage {

    @Autowired
    private ResourceLoader resourceLoader;

    public String readFile() throws IOException {
        Resource r = resourceLoader.getResource("classpath:data/schema.sql");
        return new String(r.getInputStream().readAllBytes());
    }
}
```

### MessageSource (i18n)

```java
@Configuration
public class I18nConfig {

    @Bean
    public MessageSource messageSource() {
        ReloadableResourceBundleMessageSource ms = new ReloadableResourceBundleMessageSource();
        ms.setBasename("classpath:messages");  // messages.properties, messages_de.properties …
        ms.setDefaultEncoding("UTF-8");
        ms.setCacheSeconds(60);                // reload files every 60s in dev
        return ms;
    }

    @Bean
    public LocaleResolver localeResolver() {
        AcceptHeaderLocaleResolver r = new AcceptHeaderLocaleResolver();
        r.setDefaultLocale(Locale.ENGLISH);
        return r;
    }
}
```

```properties
# messages.properties
user.welcome=Welcome, {0}!
error.notfound=Resource with id {0} was not found.

# messages_de.properties
user.welcome=Willkommen, {0}!
error.notfound=Ressource mit ID {0} wurde nicht gefunden.
```

```java
@Service
public class GreetingService {

    @Autowired
    private MessageSource messages;

    public String greet(String name, Locale locale) {
        return messages.getMessage("user.welcome", new Object[]{ name }, locale);
    }
}
```

### ApplicationContextAware

Access the context programmatically from a bean (use sparingly — prefer direct injection):

```java
@Component
public class BeanFactory implements ApplicationContextAware {

    private ApplicationContext context;

    @Override
    public void setApplicationContext(ApplicationContext ctx) {
        this.context = ctx;
    }

    // Retrieve a prototype bean on demand
    public ReportGenerator getReportGenerator() {
        return context.getBean(ReportGenerator.class);
    }
}
```

### Common Spring Utility Classes

| Class | Purpose |
|-------|---------|
| `StringUtils` | String manipulation (`hasText`, `commaDelimitedListToStringArray`, etc.) |
| `CollectionUtils` | Collection helpers (`isEmpty`, `findFirst`, `unmodifiableList`) |
| `Assert` | Precondition checks that throw `IllegalArgumentException` or `IllegalStateException` |
| `ReflectionUtils` | Reflection helpers without checked exceptions |
| `FileCopyUtils` | Stream / file copy utilities |
| `ResourceUtils` | Classpath / file URL helpers |
| `ObjectUtils` | Null-safe operations (`nullSafeToString`, `isEmpty`) |
| `ClassUtils` | Class introspection helpers |

```java
// Assert — clean precondition checks
Assert.notNull(userId,   "userId must not be null");
Assert.hasText(email,    "email must not be blank");
Assert.isTrue(age >= 0,  "age must be non-negative");
Assert.state(isOpen,     "Connection must be open before calling this method");
```
