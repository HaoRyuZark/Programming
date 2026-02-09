# Databases

A quick reference guide for common SQL commands, concepts and
databases in general.

---

## Database System

A **databases-system** is made of databases-management-engine and clients which
make request to this server.

Other components:

- **Data Manipulation Language:** Way of making requests for specific data.

- **Data Definition Language Compiler:** Like DML for data structures

- **Processing steps for requests**

- **Database Manager:** Coordination unit for the database-system

- **Schema (Metadata)**

- **Synchronization**

- **Transaction system**

## Definitions

- **Data** is sequence of characters and symbols.

- **Information** is given by data
when meaning can be given to it.

- **Knowledge** is won by the systematic connection
of data-points, information and the own experience.

- **Relation** refers to the logical connection between data points.

- **Consistency** refers to the state of data which attached to specific rules, and it does
not do violate these last.

- **Integrity** correctness and completeness of the data set

- **Redundancy** multiple occurrences of data. It can be harmful, but also necessary in some
situations.

- **Persistency** data is available and not erased after the server is down

- **Error Recovery** self-explanatory

---

## Types of Relations 

- **One to One:** (1 to 1) in Min-Max Notation (1,1) - (1,1), in Chen Notatation 1--1

- **One to Many:** (1 to n) in Min-Max Notation (1,1) - (0,n), in Chen Notation 1--n

- **Many to One:** (n to 1) in Min-Max Notation (0,n) - (1,1), in Chen Notation n--1

- **Many to Many:** (n to m) in Min-Max Notation (0,n) - (0,m), in Chen Notation n--m

---

## ANSI/SPARC Architecture

- **External Level:** It defines how the users interact with the database via APIs, etc.

- **Conceptual Level:** Complete and redundancy free representation of all information. ER-Models and database
schema with data and relations. It is the abstract representation.

- **Internal/Physical Level:** Physical components of the database, the computer. In general all the technical aspects of the
database system.

This architecture brings us the following advantages:

- **Logical Data-Independence:** Changes at the conceptual level do not affect the external level.

- **Physical Data-Independence:** Changes at the internal level do not affect the conceptual or external level.

---

## Anomalies 

- **Delete:** we delete data unintenional when deleting other data
- **Update:** we create inconsistency accross the data base when updating rows
- **Insert:** we can not insert rows due to unnecessary dependencies

---

## Creating a SQL Database 

Inside your sql file you can start with 

```sql

-- Creation
CREATE DATABASE database_name; 

-- Telling the DBMS that the queries comming are for the following database
USE database_name;

-- Starting from here you can define you tables and write you queries
```

---

## SQL Data Types

- **Numeric**:

  - `INT` – whole numbers
  - `DECIMAL(p, s)` – fixed-point (precision, scale)
  - `FLOAT`, `REAL` – approximate values

- **String**:

  - `CHAR(n)` – fixed length
  - `VARCHAR(n)` – variable length
  - `TEXT` – long text

- **Date/Time**:

  - `DATE` – YYYY-MM-DD
  - `TIME` – HH\:MM\:SS
  - `DATETIME` – YYYY-MM-DD HH\:MM\:SS
  - `TIMESTAMP` – auto-updated date/time

- **Boolean**:

  - `BOOLEAN` or `TINYINT(1)` (0 = false, 1 = true)

Example:

```sql
CREATE TABLE employees (
    id INT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    salary DECIMAL(10,2),
    hire_date DATE,
    is_active BOOLEAN DEFAULT 1
);
```

--- 

## Keys

- **Primary Key**: uniquely identifies each row.
- **Unique Key**: ensures all values are unique.
- **Composite Key**: primary key with multiple columns.

Example:

```sql
CREATE TABLE orders (
    order_id INT PRIMARY KEY,
    product_id INT,
    user_id INT UNIQUE
);
```

---

## Foreign Keys

- Establish relationship between tables.
- References another table’s primary key.

Example:

```sql
CREATE TABLE orders (
    order_id INT PRIMARY KEY,
    user_id INT,
    FOREIGN KEY (user_id) REFERENCES users(id)
);
```

---

## Dropping Tables

- `DROP TABLE` deletes a table and all its data.

Example:

```sql
DROP TABLE users;
```

---

## Altering Tables

- Use `ALTER TABLE` to modify an existing table.
- Add, remove, or rename columns.
- Add or remove constraints.

Examples:

```sql
-- Add a column
ALTER TABLE users ADD email VARCHAR(150);

ALTER TABLE Employee ADD managerId INT;

-- Drop a column
ALTER TABLE users DROP COLUMN age;

-- Rename a column
ALTER TABLE users RENAME COLUMN name TO full_name;

-- Add a constraint
ALTER TABLE users ADD CONSTRAINT unique_email UNIQUE (email);

-- Renaming table 
RENAME TABLE products TO product
```


## Constraints

- `NOT NULL` – value cannot be null
- `UNIQUE` – all values must be different
- `CHECK` – condition must be met
- `DEFAULT` – assigns a default value

Example:

```sql
CREATE TABLE products (
    id INT PRIMARY KEY,
    name VARCHAR(50) NOT NULL DEFAUlt "No name",
    price DECIMAL(10,2) CHECK (price > 0),
    stock INT DEFAULT 0
);
```

---

## Creating Tables

- Use `CREATE TABLE` to define a new table.

Example:

```sql
CREATE TABLE users (
    id INT PRIMARY KEY,
    name VARCHAR(100),
    age INT
);
```

--- 

## On Delete

- Defines what happens when a referenced row is deleted.

Example:

```sql
CREATE TABLE orders (
    order_id INT PRIMARY KEY,
    user_id INT,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE SET NULL
);
```

--- 

## On Cascade

- Automatically deletes or updates child rows when parent row changes.

Example:

```sql
CREATE TABLE orders (
    order_id INT PRIMARY KEY,
    user_id INT,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);
```

---

## Functions

- **Aggregate functions**: `COUNT`, `SUM`, `AVG`, `MAX`, `MIN` can be used inside SELECT statements to create complex queries
- **String functions**: `UPPER`, `LOWER`, `CONCAT`, `LEFT`, `RIGHT`
- **Date functions**: `NOW`, `CURDATE`
- **Math Functions**: `ROUND`, `FLOOR`, `CEIL`

Example:

```sql

-- 
SELECT COUNT(-) AS total_users, AVG(age) AS avg_age 
FROM users;

-- Count the occurrences of  male and female in the table
SELECT COUNT(sex), sex FROM employee GROUP by sex 

-- ROUND gdp per capita to the neares 1000
SELECT name, ROUND(gdp/population, -3) FROM world WHERE gdp >= 1000000000000

-- Just rounding  
SELECT name, ROUND(population/1000000, 2), ROUND(gdp/1000000000, 2) FROM world WHERE continent='South America'

-- Show the name and the capital where the first letters of each match. Don't include countries where the name and the capital are the same word.
SELECT name, capital FROM world WHERE name <> capital AND LEFT(name, 1) = LEFT(capital, 1)

-- Select the project_id and average experience in years of the empoyees participating
SELECT project_id, ROUND(AVG(experience_years), 2) as average_years 
FROM Project p 
JOIN Employee e  
ON
p.employee_id = e.employee_id 
GROUP BY 
project_id;

-- Select the name plus, some other date based on computation grouped by the name
SELECT 
    query_name, 
    ROUND(AVG(rating / position), 2) as quality, 
    ROUND(SUM(CASE WHEN rating < 3 THEN 1 ELSE 0 END) / COUNT(*),4 )*100 as poor_query_percentage 
FROM 
    Queries 
GROUP BY
    query_name;

-- Get id and the avarage price of a product during a specific time
SELECT p.product_id, IFNULL(ROUND(SUM(p.price * u.units)/SUM(u.units), 2), 0) as average_price 
FROM Prices p 
    LEFT JOIN UnitsSold u ON p.product_id = u.product_id AND u.purchase_date BETWEEN p.start_date AND p.end_date 
GROUP BY p.product_id;


```

--- 

## GROUP BY

`GROUP BY` is an SQL functions which allows to group mathcing rows by an specific criteria done by an aggregate function.
In plain english it would mean: Apply 'aggregate function on xy' for the elements in the groups generated by 'col'  

```sql 

-- Make a count of each of the orders associated with one product and display them
SELECT product_id, COUNT(*) FROM orders GROUP BY product_id;

-- Returns the number of products created by each person with their corresponding name only if they have created at least 2 products
SELECT count(p.id), u.name FROM product p LEFT JOIN user u on u.id = p.createdBy GROUP BY p.createdBy HAVING count(p.id) >= 2;

-- Get the amount of money made by day
SELECT SUM(amount), order_date FROM transactions GROUP BY order_date;
```

--- 

## HAVING

`HAVING` is used instead of `WHERE` when using `GROUP BY` and it is wirtten after it.

```sql
-- Selecting the total amount of all the customers which have spent more than 100 dollars in total
SELECT customer_id, SUM(amount) FROM transactions GROUP BY customer_id HAVING SUM(amount) > 100;

-- SELECT the greates number which appears in the MyNumber table only once. If no mathces return NULL
SELECT MAX(num) as num FROM MyNumbers n WHERE num IN(SELECT num FROM myNumbers GROUP BY num HAVING COUNT(*) = 1 );
```

--- 

## SQL SELECT

Selecting is by far the most common operation in sql and thus, also the most complex. There are a lot of variations for  
the SELECT statements

The common structure looks like:

```sql 
SELECT col1, col2, ..., cols3 AS 'this is an alias' FROM table_1 p "(this p refers o the relation which is going to be created from a JOIN or subquery, thus 
it is optinal)" WHERE cond1, cond2, cond3;
```

The common keywords are 

- `SELECT` retrieves data from a table
- `SELECT 1` retrives 1 for each of the rows matching some criteria 
- `FROM` specifies the table
- `WHERE` filters rows
- `ORDER BY` sorts results, we can specify: `ASC`, `DESC`
- `GROUP BY`  it sorts mutiple matching eows into groups determined by an specific criteria
- `LIMIT` restricts number of rows
- `LIKE` is used to specify patterns in text using `'%letters%'` % is a wild card for any character any number of times 
- `DISTINC` if used after the SELECT keyword it eliminate duplicates.Example:
- `OR AND NOR` we can use this boolean algebra  operations after the WHERE clause to specify conditions

Examples: 

```sql
-- Simple select
SELECT name, age FROM users WHERE age > 18 ORDER BY age DESC LIMIT 5;

SELECT name, gdp/population FROM users WHERE gdp >= 10000000;

-- Order by the most recent and by name
SELECT winner, yr, subject FROM nobel WHERE winner LIKE 'Sir%' ORDER BY yr DESC,  winner

-- Show the 1984 winners and subject ordered by subject and winner name; but list chemistry and physics last.
SELECT winner, subject FROM nobel WHERE yr = 1984 ORDER BY subject IN ('chemistry','physics'), subject, winner; -- because IN () returns in this case 0 or 1 they go last

-- Select using renaming and alises
SELECT e.name as 'Employee' FROM Employee e WHERE e.salary > (SELECT m.salary FROM Employee m WHERE e.managerId = m.id);

-- More Elegant solutions of the previous query using joins
SELECT e.name as 'Employee' FROM Employee e INNER JOIN Employee m ON e.managerId = m.id WHERE e.salary > m.salary;

-- Returning duplicated rows
SELECT e.email as 'Email' FROM Person e GROUP BY email HAVING COUNT(email) > 1;

-- Select the customers which have never make an order
SELECT name as 'Customers' FROM Customers LEFT JOIN Orders ON Customers.id = Orders.customerId WHERE Orders.customerId IS NULL; 

````

---

## EXISTS

`EXISTS` is pretty useful for cases where we just want to select rows if they are inside in other table

```sql
SELECT p.name
FROM SalesPerson p
WHERE NOT EXISTS (
    SELECT 1
    FROM Orders o
    JOIN Company c ON o.com_id = c.com_id
    WHERE o.sales_id = p.sales_id
      AND c.name = 'RED'
);
``` 

--- 

## Union

- Combines results of two queries.
- Removes duplicates (`UNION ALL` keeps them).

Example:

```sql
SELECT name FROM customers
UNION
SELECT name FROM suppliers;
```

The query above will return a list of all the names from both customers and suppliers.

---

## CASE 

We can use a switch-statement like in SQL 

```sql
SELECT x, y, z, 
    CASE 
        WHEN x + y > z AND x + z > y AND y + z > x  THEN 'Yes'
        ELSE 'No' 
    END
AS 'triangle' FROM Triangle;
```

--- 

## Joins

They are used to combining rows from two or more tables based on a related column between them.

- **INNER JOIN**: only matching rows 

```sql 
SELECT u.id, u.email, p.name FROM users u INNER JOIN product p ON u.id = p.created.by
```

- **LEFT JOIN**: all left table + matches. This means that in this case if a user has not created a product it will be still be retrived but with null values 
for the columns related to the product

```sql 
SELECT u.id, u.email, p.name FROM users u LEFT JOIN product p ON u.id = p.created.by

```

- **RIGHT JOIN**: all right table + matches. Similar to the left join this time products with no creato will also be displayed

```sql
SELECT u.id, u.email, p.name FROM users u RIGHT JOIN product p ON u.id = p.created.by
```

- **CROSS JOIN**: It returns the cartesian product of the two tables 

```sql
SELECT u.id, u.email, p.id, p.name FROM users u CROSS JOIN product p
```

Examples: 

```sql
SELECT users.name, orders.order_id
FROM users
INNER JOIN orders ON users.id = orders.user_id;
```

Another example: "Find all branches and the names of their managers"

```sql
SELECT employee.emp_id, employee.first_name, branch.branch_name 
FROM employee 
JOIN 
branch 
ON employee.emp_id = branch.mgr_id
```

--- 

## Inserting

- Use `INSERT INTO` to add data. The sentence is build with `INSERT INTO tabe (col1, col2, ..) VALUES(val1, val2, val3)`

Example:

```sql
INSERT INTO users (id, name, age) 
VALUES (1, 'Alice', 25);
```

or if you insert a complete row you can just write

```sql

-- Inserting multiple rows
INSERT INTO users
VALUES (1, 'Alice', 25), (2, 'Bob', 20);
```

---

## Updating

- Use `UPDATE` to modify existing data.
- Always use `WHERE` to avoid updating all rows.

Example:

```sql
UPDATE users 
SET age = 26 
WHERE id = 1;
```

---

## Deleting

- Use `DELETE` to remove rows.

Example:

```sql
-- Simple deleted statement based on a conditon. It is also possible to delete in more complex ways but the simpler the better
DELETE FROM users 
WHERE age < 18;
```

--- 

## Nested Queries

- Query inside another query.

Example:

```sql
SELECT name 
FROM users 
WHERE id IN (
    SELECT user_id 
    FROM orders 
    WHERE product_id = 10
);
```

--- 

## Triggers

- Run automatically when an event occurs.

Example:

```sql
CREATE TRIGGER update_stock
AFTER INSERT ON orders
FOR EACH ROW
BEGIN
    UPDATE products 
    SET stock = stock - 1 
    WHERE id = NEW.product_id;
END;
```

--- 

## Updating 

To update we speify the table the column and under which condition we want to update.

```sql
UPDATE accounts SET balance = balance - 100 WHERE id = 1;
```

--- 

## Reformating a table only for the SELECT 

```sql 
SELECT id, 
    MAX(IF(month="Jan", revenue, NULL)) AS Jan_Revenue, 
    MAX(IF(month="Feb", revenue, NULL)) AS Feb_Revenue, 
    MAX(IF(month="Mar", revenue, NULL)) AS Mar_Revenue,
    MAX(IF(month="Apr", revenue, NULL)) AS Apr_Revenue,
    MAX(IF(month="May", revenue, NULL)) AS May_Revenue,
    MAX(IF(month="Jun", revenue, NULL)) AS Jun_Revenue,
    MAX(IF(month="Jul", revenue, NULL)) AS Jul_Revenue,
    MAX(IF(month="Aug", revenue, NULL)) AS Aug_Revenue,
    MAX(IF(month="Sep", revenue, NULL)) AS Sep_Revenue,
    MAX(IF(month="Oct", revenue, NULL)) AS Oct_Revenue,
    MAX(IF(month="Nov", revenue, NULL)) AS Nov_Revenue,
    MAX(IF(month="Dec", revenue, NULL)) AS Dec_Revenue
    
FROM Department
GROUP BY id
ORDER BY id
```

The oringal table just had month, id an revenue, but we instead return a new table with id, and the revenue of each month.

--- 

## Transactions

- Used to group multiple SQL statements into a single unit of work.
- Ensures **atomicity** (all or nothing).
- Commands:

  - `BEGIN` or `START TRANSACTION`: start a transaction
  - `COMMIT`: save changes
  - `ROLLBACK`: undo changes

Example:

```sql
START TRANSACTION;

UPDATE accounts SET balance = balance - 100 WHERE id = 1;
UPDATE accounts SET balance = balance + 100 WHERE id = 2;

-- Commit changes if no errors
COMMIT;

-- If something goes wrong
ROLLBACK;
```

### Shared LOCK 

Multiple reads are permitted  

### Exclusion Lock  

Only one write 

## Schema Example

```sql

CREATE TABLE IF NOT EXISTS maps (
    id INTEGER,
    name VARCHAR(50) NOT NULL,
    wid INTEGER NOT NULL,
    len INTEGER NOT NULL,
    PRIMARY KEY(id),
    UNIQUE (name),
    CONSTRAINT valid_area CHECK (wid - len <= 100000),
    CONSTRAINT valid_dimensions CHECK (wid > 0 AND len > 0)
);

CREATE TABLE IF NOT EXISTS locations (
    map_id INTEGER NOT NULL,
    name CHAR(1) NOT NULL,
    x_coord INTEGER NOT NULL,
    y_coord INTEGER NOT NULL,
    PRIMARY KEY (map_id, name),
    FOREIGN KEY (map_id) REFERENCES maps(id) ON DELETE CASCADE,
    CONSTRAINT valid_name CHECK (name BETWEEN 'A' AND 'Z'),
    CONSTRAINT unique_coordinates UNIQUE (map_id, x_coord, y_coord),
    CONSTRAINT valid_coordinates CHECK (x_coord >= 0 AND y_coord >= 0)
);

CREATE TABLE IF NOT EXISTS obstacles (
    id INTEGER,
    map_id INTEGER NOT NULL,
    x_coord INTEGER NOT NULL,
    y_coord INTEGER NOT NULL,
    PRIMARY KEY (id),
    FOREIGN KEY (map_id) REFERENCES maps(id) ON DELETE CASCADE,
    CONSTRAINT unique_coordinates UNIQUE (map_id, x_coord, y_coord),
    CONSTRAINT valid_coordinates CHECK (x_coord >= 0 AND y_coord >= 0)
);

CREATE TABLE IF NOT EXISTS paths (
    id INTEGER,
    map_id INTEGER NOT NULL,
    start_loc CHAR(1) NOT NULL,
    end_loc CHAR(1) NOT NULL,
    path_length INTEGER NOT NULL,
    PRIMARY KEY (id),
    FOREIGN KEY (map_id) REFERENCES maps(id) ON DELETE CASCADE,
    FOREIGN KEY (map_id, start_loc) REFERENCES locations(map_id, name) ON DELETE CASCADE,
    FOREIGN KEY (map_id, end_loc) REFERENCES locations(map_id, name) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS path_coordinates (
    id INTEGER,
    path_id INTEGER NOT NULL,
    x_coord INTEGER NOT NULL,
    y_coord INTEGER NOT NULL,
    PRIMARY KEY (id),
    FOREIGN KEY (path_id) REFERENCES paths(id) ON DELETE CASCADE,
    CONSTRAINT valid_coordinates CHECK (x_coord >= 0 AND y_coord >= 0)
);

CREATE TRIGGER IF NOT EXISTS check_obstacle_bounds
    BEFORE INSERT ON obstacles
        FOR EACH ROW
        WHEN (NEW.x_coord >= (SELECT len FROM maps WHERE id = NEW.map_id) OR
          NEW.y_coord >= (SELECT wid FROM maps WHERE id = NEW.map_id))
        BEGIN
        SELECT RAISE(ABORT, 'Obstacle out of bounds');
END;

CREATE TRIGGER IF NOT EXISTS check_location_bounds
    BEFORE INSERT ON locations
        FOR EACH ROW
        WHEN (NEW.x_coord >= (SELECT len FROM maps WHERE id = NEW.map_id) OR
              NEW.y_coord >= (SELECT wid FROM maps WHERE id = NEW.map_id))
        BEGIN
        SELECT RAISE(ABORT, 'Location coordinates out of map bounds');
END;

CREATE TRIGGER IF NOT EXISTS check_path_coordinate_bounds
    BEFORE INSERT ON path_coordinates
    FOR EACH ROW
        WHEN (NEW.x_coord >= (SELECT len FROM maps WHERE id = (SELECT map_id FROM paths WHERE id = NEW.path_id)) OR
              NEW.y_coord >= (SELECT wid FROM maps WHERE id = (SELECT map_id FROM paths WHERE id = NEW.path_id)))
        BEGIN
        SELECT RAISE(ABORT, 'Path coordinate out of map bounds');
END;

CREATE TRIGGER IF NOT EXISTS check_location_not_obstacle
    BEFORE INSERT ON locations
    FOR EACH ROW
        WHEN EXISTS (
            SELECT 1 FROM obstacles
            WHERE obstacles.map_id = NEW.map_id
            AND obstacles.x_coord = NEW.x_coord
            AND obstacles.y_coord = NEW.y_coord
        )
    BEGIN
        SELECT RAISE(ABORT, 'Location coordinates cannot be the same as an obstacle');
END;

CREATE TRIGGER IF NOT EXISTS check_obstacle_not_location
    BEFORE INSERT ON obstacles
    FOR EACH ROW
        WHEN EXISTS (
            SELECT 1 FROM locations
            WHERE locations.map_id = NEW.map_id
            AND locations.x_coord = NEW.x_coord
            AND locations.y_coord = NEW.y_coord
        )
    BEGIN
        SELECT RAISE(ABORT, 'Obstacle coordinates cannot be the same as a location');
END;
```

## Example II

```sql
CREATE TABLE employee (
  emp_id INT PRIMARY KEY,
  first_name VARCHAR(40),
  last_name VARCHAR(40),
  birth_day DATE,
  sex VARCHAR(1),
  salary INT,
  super_id INT,
  branch_id INT
);

CREATE TABLE branch (
  branch_id INT PRIMARY KEY,
  branch_name VARCHAR(40),
  mgr_id INT,
  mgr_start_date DATE,
  FOREIGN KEY(mgr_id) REFERENCES employee(emp_id) ON DELETE SET NULL
);

ALTER TABLE employee
ADD FOREIGN KEY(branch_id)
REFERENCES branch(branch_id)
ON DELETE SET NULL;

ALTER TABLE employee
ADD FOREIGN KEY(super_id)
REFERENCES employee(emp_id)
ON DELETE SET NULL;

CREATE TABLE client (
  client_id INT PRIMARY KEY,
  client_name VARCHAR(40),
  branch_id INT,
  FOREIGN KEY(branch_id) REFERENCES branch(branch_id) ON DELETE SET NULL
);

CREATE TABLE works_with (
  emp_id INT,
  client_id INT,
  total_sales INT,
  PRIMARY KEY(emp_id, client_id),
  FOREIGN KEY(emp_id) REFERENCES employee(emp_id) ON DELETE CASCADE,
  FOREIGN KEY(client_id) REFERENCES client(client_id) ON DELETE CASCADE
);

CREATE TABLE branch_supplier (
  branch_id INT,
  supplier_name VARCHAR(40),
  supply_type VARCHAR(40),
  PRIMARY KEY(branch_id, supplier_name),
  FOREIGN KEY(branch_id) REFERENCES branch(branch_id) ON DELETE CASCADE
);


-- -----------------------------------------------------------------------------

-- Corporate
INSERT INTO employee VALUES(100, 'David', 'Wallace', '1967-11-17', 'M', 250000, NULL, NULL);

INSERT INTO branch VALUES(1, 'Corporate', 100, '2006-02-09');

UPDATE employee
SET branch_id = 1
WHERE emp_id = 100;

INSERT INTO employee VALUES(101, 'Jan', 'Levinson', '1961-05-11', 'F', 110000, 100, 1);

-- Scranton
INSERT INTO employee VALUES(102, 'Michael', 'Scott', '1964-03-15', 'M', 75000, 100, NULL);

INSERT INTO branch VALUES(2, 'Scranton', 102, '1992-04-06');

UPDATE employee
SET branch_id = 2
WHERE emp_id = 102;

INSERT INTO employee VALUES(103, 'Angela', 'Martin', '1971-06-25', 'F', 63000, 102, 2);
INSERT INTO employee VALUES(104, 'Kelly', 'Kapoor', '1980-02-05', 'F', 55000, 102, 2);
INSERT INTO employee VALUES(105, 'Stanley', 'Hudson', '1958-02-19', 'M', 69000, 102, 2);

-- Stamford
INSERT INTO employee VALUES(106, 'Josh', 'Porter', '1969-09-05', 'M', 78000, 100, NULL);

INSERT INTO branch VALUES(3, 'Stamford', 106, '1998-02-13');

UPDATE employee
SET branch_id = 3
WHERE emp_id = 106;

INSERT INTO employee VALUES(107, 'Andy', 'Bernard', '1973-07-22', 'M', 65000, 106, 3);
INSERT INTO employee VALUES(108, 'Jim', 'Halpert', '1978-10-01', 'M', 71000, 106, 3);


-- BRANCH SUPPLIER
INSERT INTO branch_supplier VALUES(2, 'Hammer Mill', 'Paper');
INSERT INTO branch_supplier VALUES(2, 'Uni-ball', 'Writing Utensils');
INSERT INTO branch_supplier VALUES(3, 'Patriot Paper', 'Paper');
INSERT INTO branch_supplier VALUES(2, 'J.T. Forms & Labels', 'Custom Forms');
INSERT INTO branch_supplier VALUES(3, 'Uni-ball', 'Writing Utensils');
INSERT INTO branch_supplier VALUES(3, 'Hammer Mill', 'Paper');
INSERT INTO branch_supplier VALUES(3, 'Stamford Lables', 'Custom Forms');

-- CLIENT
INSERT INTO client VALUES(400, 'Dunmore Highschool', 2);
INSERT INTO client VALUES(401, 'Lackawana Country', 2);
INSERT INTO client VALUES(402, 'FedEx', 3);
INSERT INTO client VALUES(403, 'John Daly Law, LLC', 3);
INSERT INTO client VALUES(404, 'Scranton Whitepages', 2);
INSERT INTO client VALUES(405, 'Times Newspaper', 3);
INSERT INTO client VALUES(406, 'FedEx', 2);

-- WORKS_WITH
INSERT INTO works_with VALUES(105, 400, 55000);
INSERT INTO works_with VALUES(102, 401, 267000);
INSERT INTO works_with VALUES(108, 402, 22500);
INSERT INTO works_with VALUES(107, 403, 5000);
INSERT INTO works_with VALUES(108, 403, 12000);
INSERT INTO works_with VALUES(105, 404, 33000);
INSERT INTO works_with VALUES(107, 405, 26000);
INSERT INTO works_with VALUES(102, 406, 15000);
INSERT INTO works_with VALUES(105, 406, 130000);

```

## Model

- **Entity:** Representation of an abstract or concrete object. $E:[e_1, e_2, ..., e_n]$

- **Relation:** Interaction between entities. $(e, a) | e \in E \land a \in A$

- **Attribute:** Trait of an entity or relation $E:e_1$

- **Composite Attribute:** An attribute made of more attributes $E:{D}$

- **Cardinality:** Number of participants in a relation. Must be given in both ways. $1:n$ or $1:1$ etc.,
There is also the Min-Max notation which is $(min, max)$

---

## ER-Model to Relational Model Translation

The process of translating an **Entity-Relationship Model** to a **Relational Model** follows systematic rules to transform entities, attributes, and relationships into tables (relations) with proper structure.

### Notation

**Entity Set:**

$$E: <[S],\{K\}>$$

$$S=[A_1,...,A_n]$$

$$K=\{A_{i1},...,A_{im}\}$$

where:
- $E$ is the entity name
- $S$ is the set of attributes
- $K$ is the set of key attributes (must be a subset of $S$)

**Attribute:** 

$$A:D$$

where $A$ is the attribute name and $D$ is its domain (data type).

**Multivalued Attribute:** 

$$A:\{D\}$$

Represents an attribute that can have multiple values (e.g., phone numbers).

**Composite Attribute:** 

$$A:[A_1:D_1, ..., A_n:D_n]$$

Represents an attribute composed of multiple sub-attributes.

### Translation Rules

#### 1. Strong Entity Sets

Each entity set becomes a relation with all its simple attributes. The primary key of the entity becomes the primary key of the relation.

**Rule:** $E: <[S],\{K\}> \rightarrow R(A_1,...,A_n)$ with $PK = K$

#### 2. Weak Entity Sets

A weak entity depends on a strong entity (owner) and includes the owner's key as a foreign key. The primary key is the combination of the owner's key and the weak entity's partial key.

**Rule:** Include owner's primary key + partial key as composite primary key.

#### 3. Composite Attributes

Replace with their atomic components. Only store the leaf-level attributes.

**Example:** $Address:[Street:VARCHAR, City:VARCHAR, ZIP:INT]$ becomes three separate attributes: $Street$, $City$, $ZIP$.

#### 4. Multivalued Attributes

Create a separate relation containing:
- The multivalued attribute
- The primary key of the parent entity (as foreign key)

**Rule:** $E$ with multivalued attribute $M$ creates: $R_M(PK_E, M)$ with composite primary key $(PK_E, M)$.

#### 5. Relationships

**Binary 1:1 Relationship:**
- Add the primary key of one entity as a foreign key to the other entity's relation.
- Preferably add to the entity with total participation.

**Binary 1:N Relationship:**
- Add the primary key of the "1" side as a foreign key to the "N" side.

**Binary N:M Relationship:**
- Create a new relation with:
  - Primary keys of both entities (as foreign keys)
  - Any attributes of the relationship
  - Composite primary key from both foreign keys

### University Example

Consider a university database with **Students**, **Professors**, and **Courses**:

**ER-Model Entities:**

**Student:**
- Simple attributes: `StudentID`, `FirstName`, `LastName`, `Email`, `EnrollmentDate`
- Composite attribute: `Address:[Street:VARCHAR(100), City:VARCHAR(50), ZIP:INT]`
- Multivalued attribute: `PhoneNumbers:{VARCHAR(15)}`

$$Student: <[StudentID, FirstName, LastName, Email, EnrollmentDate, Address], \{StudentID\}>$$

$$Address: [Street:VARCHAR(100), City:VARCHAR(50), ZIP:INT]$$

$$PhoneNumbers: \{VARCHAR(15)\}$$

**Professor:**
- Simple attributes: `ProfessorID`, `FirstName`, `LastName`, `Email`, `HireDate`, `Salary`, `DepartmentID`
- Composite attribute: `Office:[Building:VARCHAR(50), RoomNumber:VARCHAR(10)]`

$$Professor: <[ProfessorID, FirstName, LastName, Email, HireDate, Salary, DepartmentID, Office], \{ProfessorID\}>$$

$$Office: [Building:VARCHAR(50), RoomNumber:VARCHAR(10)]$$

**Course:**
- Simple attributes: `CourseID`, `CourseName`, `Credits`, `DepartmentID`

$$Course: <[CourseID, CourseName, Credits, DepartmentID], \{CourseID\}>$$

**Relationships:**

1. **Enrollment** (Student - Course): N:M relationship with attribute `Grade`, `EnrollmentDate`
2. **Teaches** (Professor - Course): 1:N relationship (one professor teaches many courses)
3. **Advises** (Professor - Student): 1:N relationship with attribute `SinceDate`

**Relational Model Translation:**

```sql
-- 1. Student entity (without composite and multivalued attributes)
CREATE TABLE Student (
    StudentID INT PRIMARY KEY,
    FirstName VARCHAR(50) NOT NULL,
    LastName VARCHAR(50) NOT NULL,
    Email VARCHAR(100) UNIQUE NOT NULL,
    EnrollmentDate DATE NOT NULL,
    -- Composite attribute Address expanded
    Street VARCHAR(100),
    City VARCHAR(50),
    ZIP INT
);

-- 2. Multivalued attribute PhoneNumbers becomes separate table
CREATE TABLE StudentPhone (
    StudentID INT,
    PhoneNumber VARCHAR(15),
    PRIMARY KEY (StudentID, PhoneNumber),
    FOREIGN KEY (StudentID) REFERENCES Student(StudentID) ON DELETE CASCADE
);

-- 3. Professor entity (composite attribute expanded)
CREATE TABLE Professor (
    ProfessorID INT PRIMARY KEY,
    FirstName VARCHAR(50) NOT NULL,
    LastName VARCHAR(50) NOT NULL,
    Email VARCHAR(100) UNIQUE NOT NULL,
    HireDate DATE NOT NULL,
    Salary DECIMAL(10,2) NOT NULL,
    DepartmentID INT NOT NULL,
    -- Composite attribute Office expanded
    OfficeBuilding VARCHAR(50),
    OfficeRoomNumber VARCHAR(10)
);

-- 4. Course entity
CREATE TABLE Course (
    CourseID INT PRIMARY KEY,
    CourseName VARCHAR(100) NOT NULL,
    Credits INT CHECK (Credits > 0),
    DepartmentID INT NOT NULL,
    -- 1:N relationship - add ProfessorID as foreign key
    ProfessorID INT,
    FOREIGN KEY (ProfessorID) REFERENCES Professor(ProfessorID) ON DELETE SET NULL
);

-- 5. N:M relationship Enrollment becomes separate table
CREATE TABLE Enrollment (
    StudentID INT,
    CourseID INT,
    Grade VARCHAR(2),
    EnrollmentDate DATE NOT NULL,
    PRIMARY KEY (StudentID, CourseID),
    FOREIGN KEY (StudentID) REFERENCES Student(StudentID) ON DELETE CASCADE,
    FOREIGN KEY (CourseID) REFERENCES Course(CourseID) ON DELETE CASCADE
);

-- 6. 1:N relationship Advises
-- Add to the N side (Student table) or create separate table
CREATE TABLE Advises (
    ProfessorID INT,
    StudentID INT,
    SinceDate DATE NOT NULL,
    PRIMARY KEY (StudentID), -- Each student has only one advisor
    FOREIGN KEY (ProfessorID) REFERENCES Professor(ProfessorID) ON DELETE SET NULL,
    FOREIGN KEY (StudentID) REFERENCES Student(StudentID) ON DELETE CASCADE
);
```

**Summary of Translation:**

| ER Concept | Translation | Example |
|------------|-------------|---------|
| Strong Entity | Table with PK | `Student`, `Professor`, `Course` |
| Composite Attribute | Flatten to atomic attributes | `Address` → `Street`, `City`, `ZIP` |
| Multivalued Attribute | Separate table with FK | `PhoneNumbers` → `StudentPhone` table |
| 1:N Relationship | FK in N side | `Teaches` → `ProfessorID` in `Course` |
| N:M Relationship | New table with both FKs as composite PK | `Enrollment(StudentID, CourseID)` |
| Relationship Attributes | Add to relationship table | `Grade` in `Enrollment` |

---

## Types of Keys

A **key** is an attribute or combination of attributes (**composite key**) which uniquely identifies an entity.

- **Candidate Key:** The term refers to the attributes which are suited for being the key.

- **Irreducible:** A key has to be as atomic as possible.

- **Super key:** It consists of a candidates key's attributes + potentially some extra attributes.

- **Alternate Key:** This is an alternative primary key. This means that the UNIQUE constraints will be imposed on the attribute/s.

- **Surrogate Key:** This key has only meaning inside the database. Example: ID → Person's Name.

- **Foreign Key** This key is an attribute of one table which references another table.

--- 

## Normal Forms

A **normalized** table are protected from data inconsistencies and make the tables more readable.

- **I Normal Form:**
  - No row order for information.
  - No Mixing data types in the same column.
  - No Tables without a primary key.
  - No Repeating groups.

This normal is mostly given in relational algebra problems.

- **II Normal Form:** Each non-key attribute must depend on the entire primary key.
  - The relation is in the second normal form if it is already in the first normal form and each **non-key** attribute is functionally dependent on the **key-candidate**.

- **III Normal Form:** Every non-key attribute in a table should depend on the key, the whole key, and nothing but the key.
  - The relation is in the third normal form if it is already in the second normal form and each **non-key** attribute is not dependent on other **non-key** attribute.
  - **Boyce-Cood III Normal Form:** Every attribute in a table should depend on the key, the whole key, and nothing but the key.

- **IV Normal Form:** Multivalued dependencies in a table must be multivalued dependencies on the key.

- **V Normal Form:** Our table in the forth normal form cannot be describable as the logical result of joining some other tables

--- 

## Practical Use of SQL in Code with Java as Example: 

--- 

## Embeded SQL 

 --- 

## API's

--- 

## ORM, JPA and Hibernate

### JPA

### ORM 

### Static Mapping

### Dynamic Mapping

### Hybernate

### Entity Classes 

### Inheritance Handling

### Foreign Keys 

### Relations

--- 

## NoSQL Databases



