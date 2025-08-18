# Spring Boot

Is a framework for Java Backend development.

## Core Features

- Auto-configuration - Automatically configures Spring Beans based on dependencies  
- Starter Dependencies - Predefined dependency bundles for different functionalities  
- Embedded Servers - Comes with Tomcat, Jetty, and Undertow for running apps without external servers  
- Spring Boot CLI - Command-line tool for quick app development  
- Spring Boot Actuator - Provides production-ready monitoring & health checks

## Spring Boot Starter Common Packages

- spring-boot-starter-web - For building web applications  
- spring-boot-starter-data-jpa - For working with databases using JPA & Hibernate  
- spring-boot-starter-security - Provides security & authentication features  
- spring-boot-starter-test - Includes testing dependencies like JUnit, Mockito, and Spring Test  
- spring-boot-starter-thymeleaf - For integrating Thymeleaf templates  

## Dependency Injection and Beans

**Dependency Injection** is way of designing object which have other objects as attributes. One example is if we have an object which will have some attribute "shape", instead of defining different attributes for each shape type we define
an interface or abstract class and then we only need to define one attribute for our object.

Example:

```java

    public interface Shape {
        void draw();
    }
    
    @Component
    public class Circle implements Shape {
        @Override
        public void draw() {
            System.out.println("Drawing a Circle");
        }
    }

    @Component
    public class Square implements Shape {
        @Override
        public void draw() {
            System.out.println("Drawing a Square");
        }
    }

    @Component
    public class ShapeDrawer {
        
        @Autowired
        private final Shape shape;

        public ShapeDrawer(Shape shape) {
            this.shape = shape;
        }
        
        public setShape(Shape shape) {
            this.shape = shape;
        }

        public void drawShape() {
            shape.draw();
        }
    }
```

## Beans

In Spring, a **Bean** is an object that is instantiated, assembled, and managed by the Spring IoC (Inversion of Control) container. Beans are created from classes annotated with `@Component`, `@Service`, `@Repository`, or `@Controller`, or defined in a configuration class using `@Bean`.

## Common Annotations

- @Bean - Declares a Spring Bean which can be injected into other components  
- @Component - Marks a class as a Spring-managed component
- @Configuration - Indicates a class contains Spring Bean definitions
- @Service - Specialization of @Component for service layer classes
- @Controller - Specialization of @Component for web controllers
- @RestController - Combines @Controller and @ResponseBody for RESTful web services
- @Repository - Specialization of @Component for data access layer classes
- @Autowired - Automatically injects a Spring Bean into a field, constructor, or method
- @Value - Injects values from properties files or environment variables
- @Qualifier - Specifies which bean to inject when multiple options exist  
- @Primary - Marks a bean as the primary choice  
- @Scope - Defines the bean's lifecycle scope (singleton, prototype, etc.)  
- @SpringBootApplication - Combines @Configuration, @EnableAutoConfiguration, and @ComponentScan for main application class
- @EnableAutoConfiguration - Enables Spring Boot's auto-configuration feature
- @ComponentScan - Configures component scanning directives for use with @Configuration
- @ConditionalOnBean - Conditionally creates a bean based on the presence of another bean
- @ConditionalOnMissingBean - Conditionally creates a bean if another bean is not present
- @ConditionalOnProperty - Conditionally creates a bean based on a property value
- @ConditionalOnClass - Conditionally creates a bean if a specific class is present on the classpath
- @ConditionalOnMissingClass - Conditionally creates a bean if a specific class is not present on the classpath
- @ConfigurationProperties - Binds properties from application.properties or application.yml to a Java class

## Test Annotations

- @SpringBootTest - Loads the full application context for integration tests. We can also specify which classes and arguments to use.
- @MockBean - Creates a mock bean for testing purposes
- @Test - Marks a method as a test case
- @BeforeEach - Runs before each test method
- @AfterEach - Runs after each test method
- @BeforeAll - Runs once before all test methods
- @AfterAll - Runs once after all test methods
- @DisplayName - Provides a custom name for test methods
- @Nested - Groups related test methods together
- @InjectMocks - Injects mock beans into the class under test
- @Mock - Creates a mock object for testing

## Configuration for the Application

- **application.properties**: Main configuration file for Spring Boot applications, used to define properties like server port, database connection, etc.
- **application.yml**: Alternative configuration file format using YAML syntax, often preferred for complex configurations
- **Configuration Class**: Java class annotated with `@Configuration` to define beans and application settings programmatically. This class is often stored in a config package.

## Configuration for the Testing

Configuration for testing is accomplished using the same properties files, but often with a separate `application-test.properties` or `application-test.yml` file. This allows for different configurations during testing, such as using an in-memory database or different server ports.

You can also use @SpringBootTest with specific properties to override the default configuration for tests.

## Layers in Spring Boot

- **Controller Layer**: Handles HTTP requests and responses, maps URLs to methods, and returns views or data.
- **Service Layer**: Contains business logic, processes data, and interacts with repositories.
- **Repository Layer**: Manages data access, interacts with the database, and performs CRUD operations.
- **Model Layer**: Represents the data structure, often using JPA entities or POJOs (Plain Old Java Objects).
- **Configuration Layer**: Contains configuration classes, properties, and beans that define application settings and dependencies.
- **Security Layer**: Manages authentication, authorization, and security configurations.
- **Testing Layer**: Contains test classes and methods for unit and integration testing, often using JUnit and Mockito.
- **Persistence Layer**: Handles database interactions, often using JPA repositories or custom DAO (Data Access Object) implementations.
