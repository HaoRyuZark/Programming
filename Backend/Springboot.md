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

`pom.xml` — parent and common starters:

```xml
<parent>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-parent</artifactId>
    <version>3.3.0</version>
</parent>

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
        <scope>test</scope>
    </dependency>

    <!-- H2 in-memory database (development/testing) -->
    <dependency>
        <groupId>com.h2database</groupId>
        <artifactId>h2</artifactId>
        <scope>runtime</scope>
    </dependency>

    <!-- PostgreSQL driver (production) -->
    <dependency>
        <groupId>org.postgresql</groupId>
        <artifactId>postgresql</artifactId>
        <scope>runtime</scope>
    </dependency>
</dependencies>
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

**Derived query methods** — Spring Data generates SQL from the method name:

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
