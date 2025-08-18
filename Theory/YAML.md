# YAML

**YAML (YAML Ain’t Markup Language)** is a human-readable data serialization format used for configuration files and data exchange.

* Easy to read and write
* Highly expressive with minimal syntax
* Widely used in DevOps, Kubernetes, CI/CD tools, and configuration files

**File format:** `.yaml` or `.yml`

---

## YAML Example

```yaml
# The user's unique ID (usually a number or UUID)
id: 12345

# The user's name
name: John Doe

# The user's email address
email: johndoe@example.com

# Boolean indicating whether the user is active
isActive: true

# The user's roles (can have multiple)
roles:
  - admin
  - editor

# An object representing the user's profile details
profile:
  # The user's age
  age: 30

  # The user's gender
  gender: male

  # The user's address as a nested object
  address:
    street: 123 Main St
    city: New York
    state: NY
    zip: "10001"

# A list of recent logins, each containing a timestamp and IP address
recentLogins:
  - timestamp: 2025-04-04T10:30:00Z
    ip: 192.168.1.1
  - timestamp: 2025-04-03T09:15:00Z
    ip: 192.168.1.2
```

---

## YAML Syntax Explained

| Element                   | Description                                                                     |
| ------------------------- | ------------------------------------------------------------------------------- |
| **Key-Value Pairs**       | Written as `key: value`                                                         |
| **Indentation**           | Used to represent nesting. Use spaces only (no tabs); 2 or 4 spaces are common. |
| **Lists**                 | Begin with a dash and a space: `- item`                                         |
| **Nested Objects**        | Created by indenting child elements under the parent key                        |
| **Strings**               | Usually unquoted, but quotes (`" "` or `' '`) are used when needed              |
| **Numbers**               | Written directly (e.g., `123`, `3.14`)                                          |
| **Booleans**              | `true` / `false` (lowercase)                                                    |
| **Null**                  | Represented as `null`, `~`, or left empty after a colon                         |
| **Comments**              | Start with `#` and can be placed on their own line                              |
| **No Brackets or Commas** | Unlike JSON, YAML does not use `{}`, `[]`, or commas                            |

---

## YAML vs. JSON (Quick Comparison)

| Feature         | YAML                         | JSON                         |
| --------------- | ---------------------------- | ---------------------------- |
| Readability     | More human-friendly          | Machine-friendly             |
| Verbosity       | Less verbose                 | More structured              |
| Comments        | Supported (`#`)              | Not officially supported     |
| Used In         | Configs (K8s, Ansible, etc.) | APIs, configs, data exchange |
| File Extensions | `.yaml`, `.yml`              | `.json`                      |

---

Let me know if you'd like a downloadable `.md` file, or side-by-side examples for learning purposes.
