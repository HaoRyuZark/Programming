# JSON

**JavaScript Object Notation (JSON)** is a lightweight data-interchange format that is:

* Easy for humans to read and write
* Easy for machines to parse and generate
* Natively supported by JavaScript

**File format:** `.json`

---

## JSON Syntax

```json
{
  // The user's unique ID (usually a number or UUID)
  "id": 12345,

  // The user's name
  "name": "John Doe",

  // The user's email address
  "email": "johndoe@example.com",

  // Boolean indicating whether the user is active
  "isActive": true,

  // The user's roles (can have multiple)
  "roles": ["admin", "editor"],

  // An object representing the user's profile details
  "profile": {
    // The user's age
    "age": 30,

    // The user's gender
    "gender": "male",

    // The user's address as a nested object
    "address": {
      "street": "123 Main St",
      "city": "New York",
      "state": "NY",
      "zip": "10001"
    }
  },

  // A list of recent logins, each containing a timestamp and IP address
  "recentLogins": [
    {
      "timestamp": "2025-04-04T10:30:00Z",
      "ip": "192.168.1.1"
    },
    {
      "timestamp": "2025-04-03T09:15:00Z",
      "ip": "192.168.1.2"
    }
  ] // no comma in the last attribute
}
```

---

## JSON Syntax Explained

Here are the key elements of JSON syntax:

| Element                | Description                                                                            |
| ---------------------- | -------------------------------------------------------------------------------------- |
| **Objects**            | Defined by curly braces `{}` and contain key-value pairs.                              |
| **Arrays**             | Defined by square brackets `[]` and contain ordered lists of values.                   |
| **Keys**               | Must be strings (in double quotes).                                                    |
| **Values**             | Can be a string, number, boolean, null, object, or array.                              |
| **Comments**           | Not officially part of JSON. Used here for explanation but not allowed in strict JSON. |
| **Strings**            | Enclosed in double quotes (`" "`).                                                     |
| **Numbers**            | Written without quotes (e.g., `42`, `3.14`).                                           |
| **Booleans**           | `true` or `false`.                                                                     |
| **Null**               | A special value `null` that indicates no value.                                        |
| **No Trailing Commas** | The last item in an object or array must **not** have a trailing comma.                |

---

