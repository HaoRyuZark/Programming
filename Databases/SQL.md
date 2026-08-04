# Structured Query Language (SQL)

This is the primary language for communicating with relational databases. SQL is used to create, modify, and query databases, 
as well as manage data and control access.

--- 

## Types Of Tables 

### Entity Table 

An **entity table** represents a real-world entity and contains its attributes. It usually has a primary key.

```sql
CREATE TABLE IF NOT EXISTS anime (
    anime_id INTEGER PRIMARY KEY, 
    title_jap TEXT NOT NULL, 
    title_romanji TEXT NOT NULL, 
    title_eng TEXT DEFAULT "No english title", 
    summary TEXT NOT NULL,
    number_of_episodes INTEGER NOT NULL,
    status_of_publication INTEGER NOT NULL
);
```

### Bridge Table 

A **bridge table** is a table used to establish a many-to-many relationship between two entity tables. It typically contains foreign keys referencing the primary keys of the related entity tables.

```sql 
-- Using the same anime table as before we can not have different genres

CREATE TABLE IF NOT EXISTS genre (
    genre_id INTEGER PRIMARY KEY,
    genre_name VARCHAR(20) NOT NULL,
    CONSTRAINT uq_genre_name UNIQUE (genre_name)
);


--- Bridge Table
CREATE TABLE IF NOT EXISTS anime_genre (
    anime_id INTEGER NOT NULL, 
    genre_id INTEGER NOT NULL,
    PRIMARY KEY (anime_id, genre_id),
    FOREIGN KEY (anime_id) REFERENCES anime(anime_id) ON DELETE CASCADE,
    FOREIGN KEY (genre_id) REFERENCES genre(genre_id) ON DELETE CASCADE
);
```

### Weak Entity Table

A **weak entity table** is a table that depends on another table (the owner) for its existence. It usually has a composite primary key that includes the primary key of the owner table.

```sql
CREATE TABLE IF NOT EXISTS episode (
    episode_id INTEGER,
    anime_id INTEGER NOT NULL,
    episode_number INTEGER NOT NULL,
    title TEXT NOT NULL,
    PRIMARY KEY (episode_id, anime_id),
    FOREIGN KEY (anime_id) REFERENCES anime(anime_id) ON DELETE CASCADE
);
```

--- 

## Creating a SQL Database 

Inside your SQL file you can start with 

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

## Casting

We can **cast** values with the following syntax:

- `CAST(arg AS type)`

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

`DROP TABLE table_name` deletes a table and all its data. If there exists dependencies with other tables via weak entities, these 
tables will also be deleted.

Example:

```sql
DROP TABLE users;
```

---

## Altering Tables

Use `ALTER TABLE table anem` to modify an existing table by

- Add `ADD`, remove `DROP`, or rename columns, constrains, ros.

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

Use `CREATE TABLE(attr1 type opt, attr2, ..., CONSTRAINT constraint_name <constraint> ...)` to define a new table with its attributes, 
constrains, keys, etc.

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

Defines what happens when a referenced row is deleted.

Example:

```sql
-- when the row/whole table is deleted we set the order_id in the the users table to NULL
CREATE TABLE orders (
    order_id INT PRIMARY KEY,
    user_id INT,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE SET NULL  
);
```

--- 

## On Cascade

Automatically deletes or updates child rows when parent row changes.

Example:

```sql
-- the row get deleted if a user which references the order is deleted
CREATE TABLE orders (
    order_id INT PRIMARY KEY,
    user_id INT,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);
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

We can also declare custom columns by using row attributes and combining them into one column `name, gdp/population`.

- `SELECT` retrieves data from a table.

- `SELECT 1` retrieves 1 for each of the rows matching some criteria.

- `FROM` specifies the table.

- `WHERE` filters rows.

- `ORDER BY col_name` sorts results, we can specify: `ASC`, `DESC`. We can also use a concept called **nested sorting** which consists of applying different sorts on our data 
one after the other.

- `GROUP BY`  it sorts multiple matching rows into groups determined by an specific criteria. This is mostly used for aggregating data.

- `LIMIT` restricts number of rows.

- `LIKE 'pattern'` is used to specify patterns in text using `'%letters%'` `%` is a wild card for any character any number of times and `_` a wild card 
for exactly one character.

- `DISTINC` if used after the SELECT keyword it eliminate duplicates.

- `OR AND NOR NOT` we can use this boolean algebra  operations after the WHERE clause to specify conditions.

**Syntax Order**: 

```sql 
SELECT DISTINC TOP n 
    col1, 
    col2, 
    agggregate_func(col2)
FROM table 
WHERE 
    cond1 AND cond2 ... 
GROUP BY 
    col1 
HAVING 
    func(col2)
ORDER BY col1 ASC/DESC

```

**Execution Order** 

1. `FROM` 
2. `WHERE`
3. `GROUP BY` 
4. `HAVING`
5. `SELECT DISTINC`
6. `ORDER BY`
7. `TOP`

Examples: 

```sql
-- Simple select all
SELECT * FROM users;

-- Select two attributes of the 5 rows with the smaller age (select the 5 youngest)
SELECT name, age FROM users WHERE age > 18 ORDER BY age DESC LIMIT 5;

-- Attribute plus custom column using a where
SELECT name, gdp/population FROM users WHERE gdp >= 10000000;

-- Order by the most recent and by name
SELECT winner, yr, subject FROM nobel WHERE winner LIKE 'Sir%' ORDER BY yr DESC,  winner

-- Nested Sorting (First sorted the countris and then sort the country groups by score)
SELECT * from customers ORDER BY country ASC ORDER BY score DESC

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

```

--- 

## Aggregate Functions 

- `COUNT`: 
- `SUM`:
- `AVG`:
- `MAX`:
- `MIN`:

--- 

## String functions

- `UPPER(str) LOWER(str)`: converts to upper/lower case. 
- `CONCAT(str, ..., strn)`: combines two strings or more strings into one. 
- `LEFT(str, n)`: get the first n  characters from the left.
- `RIGHT(str, n)`: get the first n  characters from the right.
- `SUBSRING(str, start, end)`: extract the substring from start to end.
- `REPLACE(str, pattern, replacement)`: replaces the pattern with a string.
- `TRIM(str)`: removes trailing spaces.
- `LEN(str)`: returns the length of the string.

--- 

## Date functions

A **DateTime** has the format `YYYY.MM.DD hh:mm:ss` while a **Date** or **Time** only consists on the 
corresponding portions.

- `NOW`: 
- `CURDATE`:
- `DAY(date)`: get day.
- `MONTH(date)`: get month.
- `YEAR(date)`: get year.
- `DATEPART(part, date)`: (part: year, month, day, hour, quarter, weekday, week) extracts the specified part
- `DATENAME(part, date)`: (part: month, weekday)
- `DATETRUNC(part, date)`: keeps the date until the specified part, the rest gets reseted to its minimal initial value.
- `EOMONTH(date)`: returns the last day of a month.
- `DATEADD(part, interval, date)`: adds or subtracts a DateTime value a certain interval.
- `DATEDIFF(part, start_date, end_date)`: returns the difference between two dates in the specified part
- `ISDATE(value)`: returns 1 if the value is a date.

```sql 
```


### Formatting 

**Formatting** is used to convert within date/times-formats using the following syntax:

- `FORMAT(value, format_str)`

The formats can be found in the internet. 

### Converting 

Converts a DateTime value another datatype. 

- `CONVERT(data_type, date)`

--- 

## Math Functions 

- `ROUND(num, n)`: rounds up n decimal places. 
- `FLOOR(num, n)`: rounds down n decimal places
- `CEIL(num)`:
- `ABS(num)`: absolute value
--- 

## Comparison 

SQL includes all of the classic comparisons `<, > >= <=, ==, <>(not equal in PostgreSQL), !=,  AND, OR, NOT`

--- 

## NULL Functions 

- `ISNULL(val, replacement)`: replaces the null with a placeholder.
- `COALESCE(val1, val2, ..., replacement)`: returns the first non-null value from a list.
- `NULLIF(val1, val2)`: return null if they are equal, else val1.
- `IS NULL, IS NOT NULL` return 1 or 0 depending on the input.
These functions should be used before performing any kind of operation on the data like joining, mathematical manipulation since 
NULL values lead to errors in such cases.

--- 

## Range 

- `BETWEEN lower AND upper`: checks if a value is a inclusive range.

--- 

## Membership 

- `IN, NOT IN (val1, val2, ...)` checks if a value or is not in a list.

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

## UNION

Combines results of two queries and removes duplicates (`UNION ALL` keeps them). The syntax is `SELECT_ST 1 UNION SELECT_2`

Example:

```sql
-- return a list of all the names from both customers and suppliers.
SELECT name FROM customers
UNION
SELECT name FROM suppliers;
```

We can use aliases to rename our columns if necessary due to the fact that the **first select statement determines the shape of the output**.

---

## EXCEPT or MINUS

Is used as set-minus.

```sql 
-- return customers which are not employees
SELECT name FROM customers 
EXCEPT
SELECT name FROM employees
```

--- 

## INTERSECT

Is used as a set intersection.

```sql 
-- return customers which are also employees
SELECT name FROM customers 
INTERSECT
SELECT name FROM employees
```

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

They are used to combining rows from two or more tables based on a related column between them. It consist on a Cartesian product 
of the relational algebra plus a selection.

**Syntax**: 

```sql 
SELECT t1.attr, t2.attr, ... FROM table1 t1 join_type JOIN table2 t2 ON <condition>
```

We also use **aliases** for the table `table t` to avoid conflicts between column names. We can also use the table name, but they are 
often longer than an alias.

Types:

- **INNER JOIN**: only matching rows based on a condition

```sql 
-- select the user-id and email of user which created a product 
SELECT u.id, u.email, p.name FROM users u INNER JOIN product p ON u.id = p.created.by
```

- **LEFT JOIN**: all left table + matches. This means that in this case if a user has not created a product it will be still be retrieved but with null values 
for the columns related to the product.

```sql 
-- all mathches of the inner join plus all the data of the user table
SELECT u.id, u.email, p.name FROM users u LEFT JOIN product p ON u.id = p.createdBy
```

The order matters in the condition, start with the left table for the selection and the condition.

- **RIGHT JOIN**: all right table + matches. Similar to the **left** join this time products with no creator will also be displayed.

```sql
-- all mathches of the inner join plus all the data of the product table
SELECT u.id, u.email, p.name FROM users u RIGHT JOIN product p ON u.id = p.createdBy
```

The order matters in the condition, start with the **right** table for the selection and the condition.

- **FULL JOIN**: Returns both matches and miss-matches. 

```sql
-- all combinations between all rows
SELECT u.id, u.email, p.id, p.name FROM users u FULL JOIN product p ON u.id = p.createdBy
```

- **CROSS JOIN**: It returns the Cartesian product of the two tables 

```sql
-- all combinations between all rows
SELECT u.id, u.email, p.id, p.name FROM users u CROSS JOIN product p
```

- **LEFT OUTER JOIN**: It returns all tuples from the left relation with not matches on the right. 

```sql 
-- Left Outer Join:
SELECT * FROM T LEFT OUTER JOIN S ON T.a = S.d;
```

- **RIGHT OUTER JOIN**: It returns all tuples from the right relation with not matches on the left.

```sql 
-- Right Outer Join:
SELECT * FROM T RIGHT OUTER JOIN S ON T.a = S.d;
```

- **FULL OUTER JOIN**: It returns all tuples from both relations which are not in the inner join.

```sql 
-- Full Outer Join:
SELECT * FROM T FULL OUTER JOIN S ON T.a = S.d;
```

**Examples**: 

```sql
SELECT users.name, orders.order_id
FROM users
INNER JOIN orders ON users.id = orders.user_id;

-- Another one
SELECT employee.emp_id, employee.first_name, branch.branch_name 
FROM employee 
JOIN 
branch 
ON employee.emp_id = branch.mgr_id
```

--- 

## Static Values

**Static values** in SQL are used mostly as placeholders or default values when creating, inserting or modifying data when a certain condition is meet.

Example: 

```sql 
-- returns a table with an unnamed column containg the value 1
SELECT 1;

-- Selects id, and name from the customer table and appends two new unnamed columns with NULL and 'Unknown' as default values
SELECT id, first_name, NULL, 'Unknown' FROM customers
```

--- 

## Inserting

`INSERT INTO` is used to add data. The sentence is build with `INSERT INTO table (col1, col2, ..) VALUES(val1, val2, val3)`

Example:

```sql
INSERT INTO users (id, name, age) VALUES (1, 'Alice', 25);
```

or if you insert a complete row you can just write

```sql

-- Inserting multiple rows
INSERT INTO users VALUES (1, 'Alice', 25), (2, 'Bob', 20);

-- Inserting data from the customer to the users table 

INSERT INTO users (id, first_name, birthday, phone)
    SELECT id, first_name, NULL, 'Unknown' FROM customers

```

---

## Updating

`UPDATE table_name SET attr1 = val1, attr2 = val2 WHERE <condition>` is used to modify existing data.

- Always use `WHERE` to avoid updating all rows.

Example:

```sql
UPDATE users SET age = 26 WHERE id = 1;
```

---

## Deleting

Use `DELETE FROM table_name WHERE <condition>` to remove rows.

Example:

```sql
-- Simple deleted statement based on a conditon. It is also possible to delete in more complex ways but the simpler the better
DELETE FROM users WHERE age < 18;
```

--- 

## Window Functions 

**Window functions** are special functions which allows us 

- `PARTIAON BY`:
- `ORDER BY`:
- `ROW_NUMBER`:
- `RANK`:
- `DENSE_RANK`:

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

## Stored Procedures

**Stored procedures** are a way of storing common routines which consist on multiple queries which can take parameters. 

```sql 
CREATE OR ALTER PROCEDURE my_stored_procedure(@param1 datatype, @param2 datatype) 
AS  $$
BEGIN 
    SELECT col1, col2 FROM table_name WHERE col1 = @param1;
END; $$;

-- The way it is called depends on the server
CALL my_stored_procedure('migu', 'leo');
EXEC my_stored_procedure('migu', 'leo');
```

They can be useful to reduce the number of queries send by the application to the database, but they can become very complex making the development process 
slower as well as being harder to version control.

--- 

## Dynamic SQL

**Dynamic SQL** is way of creating sql statements at runtime by passing the necessary parameters to a string which then gets executed. It 
can be used in combination with stored procedures which already accept parameters to allow for even more flexibility.

```sql 

```

--- 

## SQL Functions 

```sql 

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

To update we specify the table the column and under which condition we want to update.

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

