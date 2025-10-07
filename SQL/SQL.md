# Databases

A quick reference guide for common SQL commands, concepts and 
databases in general.

---

## Database System 

A **databases-system** is made of databases-management-engine and clients which 
make request to this server.

Other parts: 

- **Data Manipulation Language**
- **Data Definition Language**
- **Processing steps for requests**
- **Schema (Metadata)**
- **Synchronization**

## Definitions

**Date** is sequence of characters and symbols. 

**Information** is given by data 
when meaning can be given to it. 

**Knowledge** is won by the systematic connection 
of datapoints, information and the own experience.

**Relation** refers to the logical connection between data points.

**Consistency** refers to the state of data which attached to specific rules and it does 
not violates these last.

**Integrity** correctness and completness of the data set 

**Redundancy** multiple occurrences of data. It can be harmful, but also necessary in some 
situtations.

**Persistency** data is available and not erased after the server is down 

**Error Recovery** self explanatory


--- 

## SQL Basics
- `SELECT` retrieves data from a table
- `FROM` specifies the table
- `WHERE` filters rows
- `ORDER BY` sorts results
- `LIMIT` restricts number of rows

Example:
```sql
SELECT name, age 
FROM users 
WHERE age > 18 
ORDER BY age DESC 
LIMIT 5;
````

---

## Data Types

* **Numeric**:

  * `INT` – whole numbers
  * `DECIMAL(p, s)` – fixed-point (precision, scale)
  * `FLOAT`, `REAL` – approximate values
* **String**:

  * `CHAR(n)` – fixed length
  * `VARCHAR(n)` – variable length
  * `TEXT` – long text
* **Date/Time**:

  * `DATE` – YYYY-MM-DD
  * `TIME` – HH\:MM\:SS
  * `DATETIME` – YYYY-MM-DD HH\:MM\:SS
  * `TIMESTAMP` – auto-updated date/time
* **Boolean**:

  * `BOOLEAN` or `TINYINT(1)` (0 = false, 1 = true)

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

## Creating Tables

* Use `CREATE TABLE` to define a new table.

Example:

```sql
CREATE TABLE users (
    id INT PRIMARY KEY,
    name VARCHAR(100),
    age INT
);
```

---

## Dropping Tables

* `DROP TABLE` deletes a table and all its data.

Example:

```sql
DROP TABLE users;
```

---

## Altering Tables

* Use `ALTER TABLE` to modify an existing table.
* Add, remove, or rename columns.
* Add or remove constraints.

Examples:

```sql
-- Add a column
ALTER TABLE users ADD email VARCHAR(150);

-- Drop a column
ALTER TABLE users DROP COLUMN age;

-- Rename a column
ALTER TABLE users RENAME COLUMN name TO full_name;

-- Add a constraint
ALTER TABLE users ADD CONSTRAINT unique_email UNIQUE (email);
```

---

## Keys

* **Primary Key**: uniquely identifies each row.
* **Unique Key**: ensures all values are unique.
* **Composite Key**: primary key with multiple columns.

Example:

```sql
CREATE TABLE orders (
    order_id INT PRIMARY KEY,
    product_id INT,
    user_id INT UNIQUE
);
```

---

## Constraints

* `NOT NULL` – value cannot be null
* `UNIQUE` – all values must be different
* `CHECK` – condition must be met
* `DEFAULT` – assigns a default value

Example:

```sql
CREATE TABLE products (
    id INT PRIMARY KEY,
    name VARCHAR(50) NOT NULL,
    price DECIMAL(10,2) CHECK (price > 0),
    stock INT DEFAULT 0
);
```

---

## Foreign Keys

* Establish relationship between tables.
* References another table’s primary key.

Example:

```sql
CREATE TABLE orders (
    order_id INT PRIMARY KEY,
    user_id INT,
    FOREIGN KEY (user_id) REFERENCES users(id)
);
```

---

## Inserting

* Use `INSERT INTO` to add data.

Example:

```sql
INSERT INTO users (id, name, age) 
VALUES (1, 'Alice', 25);
```

---

## Updating

* Use `UPDATE` to modify existing data.
* Always use `WHERE` to avoid updating all rows.

Example:

```sql
UPDATE users 
SET age = 26 
WHERE id = 1;
```

---

## Deleting

* Use `DELETE` to remove rows.

Example:

```sql
DELETE FROM users 
WHERE age < 18;
```

---

## Functions

* **Aggregate functions**: `COUNT`, `SUM`, `AVG`, `MAX`, `MIN`
* **String functions**: `UPPER`, `LOWER`, `CONCAT`
* **Date functions**: `NOW`, `CURDATE`

Example:

```sql
SELECT COUNT(*) AS total_users, AVG(age) AS avg_age 
FROM users;
```

---

## Nested Queries

* Query inside another query.

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

* Run automatically when an event occurs.

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

## Union

* Combines results of two queries.
* Removes duplicates (`UNION ALL` keeps them).

Example:

```sql
SELECT name FROM customers
UNION
SELECT name FROM suppliers;
```

---

## Joins

* **INNER JOIN**: only matching rows
* **LEFT JOIN**: all left table + matches
* **RIGHT JOIN**: all right table + matches
* **FULL OUTER JOIN**: all rows

Example:

```sql
SELECT users.name, orders.order_id
FROM users
INNER JOIN orders ON users.id = orders.user_id;
```

---

## On Delete

* Defines what happens when a referenced row is deleted.

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

* Automatically deletes or updates child rows when parent row changes.

Example:

```sql
CREATE TABLE orders (
    order_id INT PRIMARY KEY,
    user_id INT,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);
```

---

## Transactions

* Used to group multiple SQL statements into a single unit of work.
* Ensures **atomicity** (all or nothing).
* Commands:

  * `BEGIN` or `START TRANSACTION`: start a transaction
  * `COMMIT`: save changes
  * `ROLLBACK`: undo changes

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
---

## Schema Example:

```sql

CREATE TABLE IF NOT EXISTS maps (
    id INTEGER,
    name VARCHAR(50) NOT NULL,
    wid INTEGER NOT NULL,
    len INTEGER NOT NULL,
    PRIMARY KEY(id),
    UNIQUE (name),
    CONSTRAINT valid_area CHECK (wid * len <= 100000),
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
