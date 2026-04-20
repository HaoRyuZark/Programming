# TOML

**TOML (Tom's Obvious, Minimal Language)** is a minimal configuration file format designed to be easy to read due to its obvious semantics.

- Designed to map unambiguously to a hash table / dictionary
- Strongly typed — values have explicit types
- Widely used in Rust projects (`Cargo.toml`), Python packaging (`pyproject.toml`), and other tooling

---

## TOML Syntax Example

```toml
# The user's unique ID
id = 12345

# The user's name
name = "John Doe"

# The user's email address
email = "johndoe@example.com"

# Boolean indicating whether the user is active
is_active = true

# The user's roles
roles = ["admin", "editor"]

# An object representing the user's profile details
[profile]
age = 30
gender = "male"

  [profile.address]
  street = "123 Main St"
  city = "New York"
  state = "NY"
  zip = "10001"

# A list of recent logins
[[recent_logins]]
timestamp = 2025-04-04T10:30:00Z
ip = "192.168.1.1"

[[recent_logins]]
timestamp = 2025-04-03T09:15:00Z
ip = "192.168.1.2"
```

---

## TOML Syntax Explained

| Element             | Description                                                                  |
| ------------------- | ---------------------------------------------------------------------------- |
| **Key-Value Pairs** | Written as `key = value`; whitespace around `=` is optional                  |
| **Comments**        | Start with `#` and run to the end of the line                                |
| **Tables**          | Defined with `[table_name]`; equivalent to a nested object/section           |
| **Arrays of Tables**| Defined with `[[table_name]]`; each block appends a new element to an array  |
| **Strings**         | Enclosed in double quotes `"` or single quotes `'` for literal strings       |
| **Numbers**         | Integers and floats written directly (e.g., `42`, `3.14`)                    |
| **Booleans**        | `true` or `false` (lowercase)                                                |
| **Dates/Times**     | ISO 8601 format (e.g., `1979-05-27T07:32:00Z`)                               |
| **Arrays**          | Inline with square brackets: `[1, 2, 3]`                                     |
| **Inline Tables**   | Compact single-line objects: `{ key = "value" }`                             |
| **Dotted Keys**     | Shorthand for nested tables: `profile.address.city = "NY"`                  |

---

## Comments

Comments begin with `#` and extend to the end of the line. There are no multi-line comment syntax in TOML.

```toml
# This is a full-line comment
name = "Migumin"  # This is an inline comment
```

---

## Strings

TOML has four types of strings:

**Basic string** — supports escape sequences (`\n`, `\t`, `\"`, `\\`, etc.):

```toml
greeting = "Hello, \"World\"!\nNew line here."
```

**Literal string** — no escape processing; what you write is what you get:

```toml
path = 'C:\Users\Migumin\Documents'
```

**Multi-line basic string** — delimited by `"""`:

```toml
bio = """
This is a
multi-line string.
Leading newline is trimmed.
"""
```

**Multi-line literal string** — delimited by `'''`; no escaping at all:

```toml
regex = '''
\d+\.\d+
'''
```

---

## Numbers

**Integer** — supports underscores as visual separators, and hex/octal/binary literals:

```toml
population   = 8_000_000_000
hex_color    = 0xDEADBEEF
octal_perms  = 0o755
binary_flags = 0b11001010
```

**Float** — supports underscores, `inf`, and `nan`:

```toml
pi          = 3.141_592_653
speed_of_light = 2.998e8
infinity    = inf
not_a_num   = nan
```

---

## Booleans

```toml
is_active = true
is_deleted = false
```

Only lowercase `true` and `false` are valid.

---

## Dates and Times

TOML natively supports ISO 8601 date/time types:

**Offset date-time** (with timezone):

```toml
created_at = 1979-05-27T07:32:00Z
updated_at = 2025-04-19T14:00:00+02:00
```

**Local date-time** (no timezone):

```toml
scheduled = 2025-06-01T09:00:00
```

**Local date** (date only):

```toml
birthday = 1995-03-21
```

**Local time** (time only):

```toml
alarm = 07:30:00
```

---

## Arrays

Arrays hold values of any type. Mixed types are **not** allowed.

```toml
ports     = [8080, 8443, 9090]
languages = ["Rust", "Python", "C"]
matrix    = [[1, 2], [3, 4], [5, 6]]
```

Multi-line arrays with trailing commas are allowed:

```toml
colors = [
  "red",
  "green",
  "blue",  # trailing comma is fine
]
```

---

## Tables

A **table** (also called a section) is defined with a header in square brackets. All key-value pairs below it belong to that table until the next header.

```toml
[server]
host = "localhost"
port = 8080

[database]
host = "db.example.com"
port = 5432
name = "mydb"
```

Tables can be nested using dotted headers:

```toml
[server.tls]
enabled = true
cert = "/etc/ssl/cert.pem"
```

---

## Dotted Keys

A shorthand for defining a nested structure inline without creating a full table header:

```toml
server.host = "localhost"
server.port = 8080
```

This is equivalent to:

```toml
[server]
host = "localhost"
port = 8080
```

Dotted keys and their table counterpart cannot be mixed after the fact — define a key in one way only.

---

## Inline Tables

Inline tables are single-line compact tables. They are useful for small, self-contained objects and **cannot** span multiple lines.

```toml
point   = { x = 1, y = 2 }
address = { street = "123 Main St", city = "New York" }
```

---

## Arrays of Tables

`[[double_bracket]]` headers define an array of tables. Each occurrence appends a new table to the array.

```toml
[[products]]
name  = "Hammer"
price = 9.99

[[products]]
name  = "Wrench"
price = 14.99

[[products]]
name  = "Screwdriver"
price = 7.49
```

This is equivalent to a JSON array of objects:

```json
{
  "products": [
    { "name": "Hammer",      "price": 9.99  },
    { "name": "Wrench",      "price": 14.99 },
    { "name": "Screwdriver", "price": 7.49  }
  ]
}
```

Nested arrays of tables are also possible:

```toml
[[fruits]]
name = "apple"

  [[fruits.varieties]]
  name = "red delicious"

  [[fruits.varieties]]
  name = "granny smith"

[[fruits]]
name = "banana"
```
