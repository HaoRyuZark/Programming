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

`EXISTS` is pretty useful for cases where we just want to select rows if they are inside in another table

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

Combines results of two queries and removes duplicates (`UNION ALL` keeps them).

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

Query inside another query.

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

Run automatically when an event occurs.

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

The transactions are a way of avoding anomalies inside the database by adding the features of `commit` and `rollback`. A
transaction woks under the philosophy of all or nothing.

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

--- 

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

--- 

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

