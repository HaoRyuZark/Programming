# Markdown

Concise reference for commonly used Markdown features with embedded examples.

Reference: https://www.markdownguide.org/basic-syntax/

---

# Headers

```markdown
# H1
## H2
### H3
#### H4
##### H5
###### H6
```

# H1

## H2

### H3

#### H4

##### H5

###### H6

---

# Bold / Italics

```markdown
**Bold text**

*Italic text*

***Bold and italic***
```

**Bold text**
*Italic text*
***Bold and italic***

---

# Paragraphs

```markdown
This is a paragraph.

This is another paragraph separated by a blank line.
```

This is a paragraph.

This is another paragraph separated by a blank line.

---

# Formatting (Inline)

```markdown
Inline `code`

Use horizontal rules:

---
```

Inline `code`

---

# Flavors

Different Markdown implementations support additional features.

Common variants:

* **CommonMark**
* **GitHub Flavored Markdown (GFM)**
* **Pandoc Markdown**
* **Markdown Extra**

Example (GFM table support):

```markdown
| A | B |
|---|---|
| 1 | 2 |
```

---

# Strikethrough / Highlight

```markdown
~~Strikethrough~~

==Highlight==   (supported in some flavors)
```

~~Strikethrough~~

==Highlight==

---

# Lists, Sublists, Enumerations

Unordered list:

```markdown
- Item 1
- Item 2
  - Subitem
  - Subitem
```

* Item 1
* Item 2

  * Subitem
  * Subitem

Ordered list:

```markdown
1. First
2. Second
3. Third
```

1. First
2. Second
3. Third

---

# Tables

```markdown
| Column A | Column B | Column C |
|----------|----------|----------|
| A1       | B1       | C1       |
| A2       | B2       | C2       |
```

| Column A | Column B | Column C |
| -------- | -------- | -------- |
| A1       | B1       | C1       |
| A2       | B2       | C2       |

---

# LaTeX Embedding

Supported in many Markdown renderers (e.g., Jupyter, Pandoc, MathJax).

```markdown
Inline: $E = mc^2$

Block:

$$
\int_0^1 x^2 dx
$$
```

Inline: $E = mc^2$

Block:

$$
\int_0^1 x^2 dx
$$

---

# Superscript / Subscript

Common in extended Markdown flavors.

```markdown
x^2^

H~2~O
```

x^2^
H~2~O

---

# Emojis

```markdown
:smile:
:rocket:
:warning:
:thumbsup:
```

:smile:
:rocket:
:warning:
:thumbsup:

---

# Code Blocks

Inline code:

```markdown
`print("Hello")`
```

Block code:

````markdown
```python
def hello():
    print("Hello world")
```
````

```python
def hello():
    print("Hello world")
```

---

# Links

```markdown
[Markdown Guide](https://www.markdownguide.org)
```

[Markdown Guide](https://www.markdownguide.org)

---

# Pictures

```markdown
![Alt text](image.png)
```

Example:

```markdown
![Architecture Diagram](diagram.png)
```

---

# Block Quotes

```markdown
> This is a block quote.
>
> It can span multiple lines.
```

> This is a block quote.
>
> It can span multiple lines.

---

# Check Lists

(GitHub Flavored Markdown)

```markdown
- [x] Completed task
- [ ] Pending task
- [ ] Another task
```

* [x] Completed task
* [ ] Pending task
* [ ] Another task

---

# Escaping Characters

Use `\` to escape Markdown syntax characters.

```markdown
\*This is not italic\*

\# This is not a header
```

*This is not italic*

# This is not a header

---

# Best Practices

* Use **consistent header hierarchy** (`#` → `##` → `###`).
* Keep **lines reasonably short** (≈80–100 characters) for readability.
* Prefer **lists and tables** for structured information.
* Use **code blocks with language identifiers** for syntax highlighting.
* Avoid excessive formatting (bold, italics).
* Keep **one blank line between sections**.
* Use **descriptive link text** instead of raw URLs.
* Use **alt text for images** to improve accessibility.
* Maintain **consistent list indentation** (typically 2 spaces).
* Prefer **GitHub Flavored Markdown** for compatibility.
* Avoid renderer-specific features unless necessary.
* Keep documents **modular and logically structured**.
* Use **version control** for Markdown documentation.

---

