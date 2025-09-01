**Regular Expressions (Regex) Syntax and Explanation**

---

### 1. Basic Characters
- `a` : Matches character 'a' exactly.
- `abc` : Matches the string "abc" exactly.

### 2. Meta Characters (Special Characters)
- `.` : Matches any single character except a newline.
- `\` : Escape character (used to escape special characters, e.g., `\.` to match a literal period).
- `^` : Matches the start of a string.
- `$` : Matches the end of a string.
- `|` : Alternation (logical OR, e.g., `cat|dog` matches either "cat" or "dog").

### 3. Character Classes
- `[abc]` : Matches any one of 'a', 'b', or 'c'.
- `[^abc]` : Matches any character except 'a', 'b', or 'c'.
- `[a-z]` : Matches any lowercase letter.
- `[A-Z]` : Matches any uppercase letter.
- `[0-9]` : Matches any digit.
- `[a-zA-Z0-9]` : Matches any alphanumeric character.
- `.` : Matches any character except newline.
- `\d` : Matches any digit (equivalent to `[0-9]`).
- `\D` : Matches any non-digit character.
- `\w` : Matches any word character (letters, digits, underscore).
- `\W` : Matches any non-word character.
- `\s` : Matches any whitespace character (spaces, tabs, newlines).
- `\S` : Matches any non-whitespace character.

### 4. Quantifiers
- `*` : Matches 0 or more occurrences of the preceding character (e.g., `a*` matches "", "a", "aa", etc.).
- `+` : Matches 1 or more occurrences (e.g., `a+` matches "a", "aa", etc.).
- `?` : Matches 0 or 1 occurrence (e.g., `a?` matches "" or "a").
- `{n}` : Matches exactly `n` occurrences (e.g., `a{3}` matches "aaa").
- `{n,}` : Matches at least `n` occurrences (e.g., `a{2,}` matches "aa", "aaa", etc.).
- `{n,m}` : Matches between `n` and `m` occurrences (e.g., `a{2,4}` matches "aa", "aaa", or "aaaa").

### 5. Grouping and Capturing
- `(abc)` : Capturing group, treats "abc" as a single unit.
- `(?:abc)` : Non-capturing group, groups "abc" without capturing.
- `\n` : Refers to the nth captured group (e.g., `(\w)\1` matches doubled letters like "oo").

### 6. Assertions and Anchors
- `^` : Matches the start of a string.
- `$` : Matches the end of a string.
- `\b` : Matches a word boundary (e.g., `\bword\b` matches "word" but not "sword").
- `\B` : Matches a non-word boundary.
- `(?=...)` : Positive lookahead (e.g., `a(?=b)` matches 'a' only if followed by 'b').
- `(?!...)` : Negative lookahead (e.g., `a(?!b)` matches 'a' only if NOT followed by 'b').
- `(?<=...)` : Positive lookbehind (e.g., `(?<=a)b` matches 'b' only if preceded by 'a').
- `(?<!...)` : Negative lookbehind (e.g., `(?<!a)b` matches 'b' only if NOT preceded by 'a').

### 7. Advanced Constructs
- `(?(condition)yes|no)` : Conditional expression.
- `(?P<name>...)` : Named capturing group (e.g., `(?P<word>\w+)`).
- `(?P=name)` : Refers to a named capturing group.
- `(?#...)` : Comment within regex for readability.
- `(*UTF8)` : Enforces UTF-8 mode for international text processing.
- `(?>...)` : Atomic group (prevents backtracking within the group).

### 8. Examples
1. **Email validation:**
   ```regex
   ^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$
   ```
   Matches valid email addresses.

2. **Phone number validation:**
   ```regex
   ^\(?\d{3}\)?[-.]?\d{3}[-.]?\d{4}$
   ```
   Matches US phone numbers like (123) 456-7890, 123-456-7890, or 123.456.7890.

3. **URL validation:**
   ```regex
   ^https?:\/\/(www\.)?[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}(/\S*)?$
   ```
   Matches URLs like http://example.com or https://www.example.com/path.

4. **Hex color code validation:**
   ```regex
   ^#([A-Fa-f0-9]{6}|[A-Fa-f0-9]{3})$
   ```
   Matches hex color codes like #FFF or #A1B2C3.

5. **Date format (YYYY-MM-DD) validation:**
   ```regex
   ^\d{4}-\d{2}-\d{2}$
   ```
   Matches dates formatted as 2024-03-01.

---

This document provides a comprehensive guide to regex syntax, from simple to advanced constructs. Regex is powerful and widely used in search, validation, and text manipulation.


