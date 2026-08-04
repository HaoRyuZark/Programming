# Databases

A quick reference guide for common SQL commands, concepts and databases in general.

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

## Types Of Databases

- **Relational**: Orders data in rows and columns which may share relations via shared columns. Uses relational algebra as foundation. Examples: PostgreSQL, 
MySQL, Microsoft SQL Server. (The focus of this reference).

- **Key-Value**: Stores data in a key-value pairs like a hashmap. Examples Redis, Amazon Dynamo DB. 

- **Column Bases**: Stores data in columns e.g. Apache Cassandra, Amazon Redshift. 

- **Graph**: Uses concepts from graph theory to organize data e.g. Neo4J 

- **Document Based**: Organizes data into documents which represent objects.

--- 

## Storage 

Data is mostly stored in pages in the disk which are organize with indices in a **B-tree** data-structure.

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

