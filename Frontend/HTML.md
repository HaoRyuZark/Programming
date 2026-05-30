# HTML 

**HTML (Hyper Text Markup Language)** is the standard language used to define the structure of a webpage.
It works by nesting **elements** (tags) which can carry **attributes** to define extra behavior or metadata.

Each element has a semantic purpose that helps browsers, screen readers, and search engines understand the content.
Technically, one can design an entire site using only `<div>`s, but this is considered poor practice.

--- 

## Versions & Changes

| Version | Year | Key Changes |
|:-------:|:----:|-------------|
| HTML 1.0 | 1991 | Basic text, links, and images |
| HTML 2.0 | 1995 | Forms introduced |
| HTML 3.2 | 1997 | Tables, scripting support |
| HTML 4.01 | 1999 | CSS separation, accessibility attributes |
| XHTML 1.0 | 2000 | Stricter XML-based HTML |
| HTML5 | 2014 | Semantic elements, audio/video, canvas, local storage |
| HTML Living Standard | Ongoing | Maintained by WHATWG; continuously updated |

**HTML5** is the current standard. It introduced:

- Semantic tags: `<article>`, `<section>`, `<nav>`, `<aside>`, `<header>`, `<footer>`
- Native media: `<audio>`, `<video>`
- New input types: `email`, `date`, `range`, `color`, etc.
- APIs: LocalStorage, WebSockets, Geolocation, Canvas

--- 

## Tags 

Tags are the building blocks of HTML which come in pairs: an **opening tag** `<>` and a **closing tag** `</>`.

```html
<tagname attribute="value">Content</tagname>
```

**Void (self-closing) elements** have no closing tag:

```html
<img src="image.png" alt="description">
<br>
<hr>
<input type="text">
<meta charset="UTF-8">
<link rel="stylesheet" href="style.css">
```

### Tag Categories

- **Block-level**: Take up the full width available, start on a new line. (`<div>`, `<p>`, `<h1>`, `<section>`)
- **Inline**: Only take up as much width as needed, do not break the flow. (`<span>`, `<a>`, `<strong>`, `<img>`)

--- 

## HTML Header 

The `<head>` element contains metadata about the document — information not directly visible on the page.

```html 
<!DOCTYPE html>
<html lang="en"> 
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="A brief page description for SEO">
    <title>Page Title</title>
    <link rel="stylesheet" href="style.css">
    <link rel="icon" href="favicon.ico" type="image/x-icon">
    <script src="app.js" defer></script>
  </head>
  <body>
    <!-- Visible content goes here -->
  </body>
</html>
```

Common `<head>` elements:

- **`<meta charset="UTF-8">`**: Declares the character encoding for the document.

- **`<meta name="viewport" ...>`**: Controls layout on mobile browsers. Essential for responsive design.

- **`<meta name="description" ...>`**: Short description used by search engines.

- **`<title>`**: Text shown in the browser tab and used by search engines.

- **`<link rel="stylesheet">`**: Links an external CSS file.

- **`<link rel="icon">`**: Sets the favicon shown in the browser tab.

- **`<script src="..." defer>`**: Links an external JS file. `defer` ensures the script runs after HTML parsing. `async` can also be used 
if we want the script to be executed as soon as it was completely parsed.

- **`<base href="...">`**: Sets the base URL for all relative links in the document.

--- 

## Body

The `<body>` element contains all visible content rendered on the page.

```html
<body>
  <header>...</header>
  <main>
    <section>...</section>
    <article>...</article>
    <aside>...</aside>
  </main>
  <footer>...</footer>
</body>
```

Everything a user sees — text, images, links, forms — lives inside `<body>`. The body should follow a semantic structure using
appropriate tags rather than generic `<div>`s.

--- 

## Headers 

Heading tags define titles and subtitles in a document. They range from `<h1>` (most important) to `<h6>` (least important).

```html
<h1>Main Page Title</h1>
<h2>Section Title</h2>
<h3>Subsection Title</h3>
<h4>Sub-subsection</h4>
<h5>Minor heading</h5>
<h6>Smallest heading</h6>
```

- There should be only **one `<h1>`** per page — it represents the page's primary topic.
- Headings are used by screen readers and search engines to understand the document outline.
- Do not skip levels (e.g., go from `<h2>` directly to `<h4>`) for accessibility reasons.

--- 

## Divs

`<div>` is a generic **block-level container** with no inherent semantic meaning. Used for grouping elements for styling or scripting purposes.

```html
<div class="card">
  <div class="card-header">
    <h2>Title</h2>
  </div>
  <div class="card-body">
    <p>Some content here.</p>
  </div>
</div>
```

- Use `<div>` only when no semantic element fits the purpose.
- Prefer semantic elements (`<section>`, `<article>`, `<aside>`) when the content has a defined role.

--- 

## Lists 

### Unordered List

For items with no specific order. Renders as bullet points by default.

```html
<ul>
  <li>Apples</li>
  <li>Oranges</li>
  <li>Bananas</li>
</ul>
```

### Ordered List

For items with a specific sequence. Renders as numbered list by default.

```html
<ol>
  <li>Boil water</li>
  <li>Add pasta</li>
  <li>Drain and serve</li>
</ol>
```

`<ol>` attributes:
- **`type`**: Numbering style — `1` (default), `A`, `a`, `I`, `i`
- **`start`**: Starting number — `<ol start="5">`
- **`reversed`**: Counts down instead of up

### Description List

For key-value pairs or glossary-style entries.

```html
<dl>
  <dt>TCP</dt>
  <dd>Transmission Control Protocol — reliable, connection-oriented.</dd>

  <dt>UDP</dt>
  <dd>User Datagram Protocol — fast, connectionless.</dd>
</dl>
```

### Nested Lists

```html
<ul>
  <li>Frontend
    <ul>
      <li>HTML</li>
      <li>CSS</li>
    </ul>
  </li>
  <li>Backend</li>
</ul>
```

--- 

## Links 

The `<a>` (anchor) tag creates hyperlinks.

```html
<a href="https://google.com" target="_blank" rel="noopener noreferrer" >Go to Google</a>
```

Common attributes:

- **`href`**: The URL or path to navigate to.
- **`target="_blank"`**: Opens the link in a new tab.
- **`rel="noopener noreferrer"`**: Security best practice when using `target="_blank"` — prevents the new tab from accessing the originating page.
- **`download`**: Prompts the browser to download the linked resource.
- **`title`**: Tooltip shown on hover.

```html
<!-- External link (new tab) -->
<a href="https://example.com" target="_blank" rel="noopener noreferrer">External</a>

<!-- Internal link (same page anchor) -->
<a href="#section-id">Jump to Section</a>

<!-- Email link -->
<a href="mailto:user@example.com">Send Email</a>

<!-- Phone link -->
<a href="tel:+1234567890">Call Us</a>

<!-- Download link -->
<a href="report.pdf" download>Download Report</a>
```

--- 

## Images & Videos 

### Images

```html
<img src="photo.jpg" alt="A mountain landscape" width="800" height="600">
```

- **`src`**: Path or URL to the image.
- **`alt`**: Alternative text for accessibility and when the image fails to load. Always include it.
- **`width` / `height`**: Dimensions in pixels. Setting both prevents layout shift.
- **`loading="lazy"`**: Defers loading until the image is near the viewport — improves performance.

```html
<!-- Responsive image with multiple sources -->
<picture>
  <source srcset="image-large.webp" media="(min-width: 800px)" type="image/webp">
  <source srcset="image-small.webp" type="image/webp">
  <img src="image-small.jpg" alt="Fallback description">
</picture>
```

### Videos

```html
<video width="720" controls autoplay muted loop>
  <source src="video.mp4" type="video/mp4">
  <source src="video.webm" type="video/webm">
  Your browser does not support the video tag.
</video>
```

Common attributes:

- **`controls`**: Shows play/pause/volume controls.
- **`autoplay`**: Plays automatically on load (requires `muted` in most browsers).
- **`muted`**: Mutes the audio.
- **`loop`**: Restarts when finished.
- **`poster`**: Image shown before the video plays.

### Audio

```html
<audio controls>
  <source src="audio.mp3" type="audio/mpeg">
  <source src="audio.ogg" type="audio/ogg">
  Your browser does not support the audio element.
</audio>
```

--- 

## Attributes

Attributes provide additional information or configuration for elements. They are always placed in the **opening tag**.

```html
<element attribute="value">Content</element>
```

### Global Attributes

Available on every HTML element:

| Attribute | Description |
|-----------|-------------|
| `id` | Unique identifier within the page. Used for anchors, CSS, and JS. |
| `class` | One or more space-separated class names for CSS/JS targeting. |
| `style` | Inline CSS styles (use sparingly). |
| `title` | Tooltip text shown on hover. |
| `lang` | Language of the element's content (e.g., `lang="en"`). |
| `hidden` | Hides the element (equivalent to `display: none`). |
| `tabindex` | Controls keyboard focus order. |
| `data-*` | Custom data attributes for storing extra info in JS. |
| `contenteditable` | Makes the element's content editable in the browser. |
| `draggable` | Specifies whether the element can be dragged. |
| `aria-*` | Accessibility attributes for screen readers. |

```html
<div id="main-content" class="container active" data-user-id="42" aria-label="Main content">
  Content
</div>
```

--- 

## Paragraphs 

The `<p>` tag defines a paragraph of text. Browsers add vertical spacing above and below it automatically.

```html
<p>This is a standard paragraph of text.</p>
<p>Each paragraph is separated by whitespace in the rendered output.</p>
```

- Whitespace and newlines inside a `<p>` are collapsed to a single space by the browser.
- Do not nest block elements (like `<div>` or `<h1>`) inside `<p>`.

--- 

## Line Breaks & Lines

### Line Break

`<br>` inserts a single line break within inline content. It is a void element.

```html
<p>Street Address<br>City, Country</p>
```

Use sparingly — for actual line breaks in content (e.g., addresses, poems), not for spacing between elements.

### Horizontal Rule

`<hr>` renders a thematic break as a horizontal line.

```html
<section>
  <h2>Chapter 1</h2>
  <p>...</p>
</section>
<hr>
<section>
  <h2>Chapter 2</h2>
  <p>...</p>
</section>
```

--- 

## Semantic HTML

**Semantic elements** clearly describe their purpose to both the browser and the developer.

| Element | Purpose |
|---------|---------|
| `<header>` | Introductory content or navigation for its nearest section or the page |
| `<footer>` | Footer content: copyright, contact, links |
| `<main>` | The dominant unique content of the page. Only one per page. |
| `<section>` | A thematic grouping of content, usually with a heading |
| `<article>` | Self-contained piece of content (blog post, news item, comment) |
| `<aside>` | Tangentially related content (sidebars, callouts) |
| `<nav>` | A set of navigation links |
| `<figure>` | Self-contained content like images or diagrams |
| `<figcaption>` | Caption for a `<figure>` |
| `<time>` | A specific date/time |
| `<mark>` | Highlighted/relevant text |
| `<summary>` / `<details>` | Disclosure widget (accordion) |

```html
<article>
  <header>
    <h2>Post Title</h2>
    <time datetime="2026-05-24">May 24, 2026</time>
  </header>
  <p>Article body content...</p>
  <footer>
    <p>Author: Miguel</p>
  </footer>
</article>
```

--- 

## Best Practices

- Use **semantic elements** over generic `<div>`s wherever possible.
- Always include `alt` on `<img>` tags.
- Always set `lang` on `<html>`: `<html lang="en">`.
- Use one `<h1>` per page and maintain a logical heading hierarchy.
- Separate structure (HTML), style (CSS), and behavior (JS).
- Use `rel="noopener noreferrer"` on external `target="_blank"` links.
- Validate HTML with the [W3C Validator](https://validator.w3.org/).
- Indent nested elements consistently (2 or 4 spaces).
- Keep `<script>` tags at the bottom of `<body>` or use `defer`/`async` in `<head>`.
- Use lowercase for all tag names and attribute names.

--- 

## Text Formatting

Inline elements for formatting text content:

| Tag | Rendering | Semantic Meaning |
|-----|-----------|-----------------|
| `<strong>` | **Bold** | Important content |
| `<em>` | *Italic* | Stressed emphasis |
| `<b>` | **Bold** | Stylistic bold, no semantic weight |
| `<i>` | *Italic* | Stylistic italic (terms, titles) |
| `<u>` | Underline | Annotated / misspelled text |
| `<s>` | ~~Strikethrough~~ | No longer accurate |
| `<del>` | ~~Strikethrough~~ | Deleted content (semantic) |
| `<ins>` | Underline | Inserted content (semantic) |
| `<mark>` | Highlighted | Highlighted/relevant text |
| `<small>` | Smaller text | Fine print, legal text |
| `<sub>` | Subscript | H₂O |
| `<sup>` | Superscript | x² |
| `<code>` | Monospace | Inline code snippet |
| `<pre>` | Preserved whitespace | Preformatted text blocks |
| `<kbd>` | Keyboard key | `Ctrl + C` |
| `<abbr>` | Abbreviation with tooltip | `<abbr title="HyperText">HTML</abbr>` |
| `<blockquote>` | Indented quote | Long quotation from another source |
| `<q>` | Inline quote | Short inline quotation |
| `<cite>` | Italic | Title of a work |

```html
<p>Press <kbd>Ctrl + S</kbd> to save.</p>
<p>Water is written as H<sub>2</sub>O and energy as E=mc<sup>2</sup>.</p>
<p>Use <code>git commit -m "message"</code> to commit.</p>

<pre>
  Preserved
  whitespace
</pre>

<blockquote cite="https://example.com">
  "The best way to predict the future is to invent it."
</blockquote>
```

--- 

## Tables

Tables are for **tabular data** — not for page layout.

```html
<table>
  <caption>Monthly Sales</caption>
  <thead>
    <tr>
      <th scope="col">Month</th>
      <th scope="col">Revenue</th>
      <th scope="col">Units</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>January</td>
      <td>$4,200</td>
      <td>84</td>
    </tr>
    <tr>
      <td>February</td>
      <td>$3,800</td>
      <td>76</td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <td>Total</td>
      <td>$8,000</td>
      <td>160</td>
    </tr>
  </tfoot>
</table>
```

Key elements:

- **`<table>`**: The container.
- **`<caption>`**: Title of the table (accessibility).
- **`<thead>`**: Header row group.
- **`<tbody>`**: Main data row group.
- **`<tfoot>`**: Footer row group (totals, summaries).
- **`<tr>`**: A table row.
- **`<th>`**: Header cell — bold and centered by default. Use `scope="col"` or `scope="row"`.
- **`<td>`**: Data cell.

Spanning cells:

```html
<td colspan="2">Spans 2 columns</td>
<td rowspan="3">Spans 3 rows</td>
```

--- 

## Span 

`<span>` is a generic **inline container** with no semantic meaning. Used to target a specific portion of text for styling or scripting.

```html
<p>The price is <span class="highlight">$99.99</span> today only.</p>
```

- Block equivalent: `<div>`
- Use only when no semantic inline element fits (`<strong>`, `<em>`, `<mark>`, etc.)

--- 

## Nav 

`<nav>` marks a section of the page that contains **navigation links**.

```html
<nav aria-label="Main navigation">
  <ul>
    <li><a href="/">Home</a></li>
    <li><a href="/about">About</a></li>
    <li><a href="/blog">Blog</a></li>
    <li><a href="/contact">Contact</a></li>
  </ul>
</nav>
```

- A page can have multiple `<nav>` elements (main nav, breadcrumbs, footer nav).
- Use `aria-label` to distinguish between multiple `<nav>` elements for screen readers.
- Wrap links in a `<ul>` list — it conveys the number of items to screen readers.

--- 

## Buttons 

The `<button>` element creates a clickable button.

```html
<button type="button">Click Me</button>
<button type="submit">Submit Form</button>
<button type="reset">Reset Form</button>
```

`type` attribute:

- **`button`**: No default behavior. Used for JS-triggered actions.
- **`submit`**: Submits the nearest `<form>`. This is the **default** if `type` is omitted inside a form.
- **`reset`**: Resets all form fields to their default values.

Other attributes:

- **`disabled`**: Disables the button.
- **`name` / `value`**: Included in form data when submitted.
- **`form`**: Links the button to a form by its `id` (even if outside the `<form>` element).

```html
<button type="button" disabled>Unavailable</button>

<!-- Button with icon content -->
<button type="button" aria-label="Close">
  <img src="close-icon.svg" alt="">
</button>

<!-- Button inside nav -->
<a href="./about">
    <button>About</button>
</a>
```

> Prefer `<button>` over `<a>` for actions, and `<a>` over `<button>` for navigation.

--- 

## Forms

Forms collect user input and submit it to a server or handle it via JavaScript.

```html
<form action="/submit" method="POST">
  <!-- Fields go here -->
  <button type="submit">Send</button>
</form>
```

`<form>` attributes:

- **`action`**: URL to send the form data to.
- **`method`**: `GET` (data in URL) or `POST` (data in request body).
- **`enctype`**: Encoding type. Use `multipart/form-data` for file uploads.
- **`novalidate`**: Disables browser-side validation.

### Input Types

```html
<input type="text"     name="username"  placeholder="Enter username">
<input type="password" name="password">
<input type="email"    name="email"     required>
<input type="number"   name="age"       min="0" max="120">
<input type="tel"      name="phone">
<input type="url"      name="website">
<input type="date"     name="birthday">
<input type="time"     name="meeting">
<input type="range"    name="volume"    min="0" max="100" step="5">
<input type="color"    name="color">
<input type="checkbox" name="agree"     value="yes">
<input type="radio"    name="gender"    value="male">
<input type="file"     name="avatar"    accept="image/*">
<input type="hidden"   name="token"     value="abc123">
<input type="search"   name="query">
<input type="submit"   value="Send">
<input type="reset">
```

### Label

Always associate a label with its input using `for` + `id` or by nesting:

```html
<!-- Explicit association -->
<label for="email">Email Address</label>
<input type="email" id="email" name="email">

<!-- Implicit association (nesting) -->
<label>
  Email Address
  <input type="email" name="email">
</label>
```

### Textarea

Multi-line text input:

```html
<label for="message">Message</label>
<textarea id="message" name="message" rows="5" cols="40" placeholder="Your message..."></textarea>
```

### Select (Dropdown)

It is as the name implies a simple list of fields to be filled by single clicks.

```html
<label for="country">Country</label>
<select id="country" name="country">
  <option value="">-- Select --</option>
  <optgroup label="Europe">
    <option value="de">Germany</option>
    <option value="es">Spain</option>
  </optgroup>
  <optgroup label="Americas">
    <option value="us">United States</option>
  </optgroup>
</select>
```

### Fieldset & Legend

Groups related inputs with a visible border and title:

```html
<fieldset>
  <legend>Shipping Address</legend>
  <label for="street">Street</label>
  <input type="text" id="street" name="street">
  <label for="city">City</label>
  <input type="text" id="city" name="city">
</fieldset>
```

### Datalist

Provides autocomplete suggestions for an input:

```html
<input type="text" name="browser" list="browsers">
<datalist id="browsers">
  <option value="Firefox">
  <option value="Chrome">
  <option value="Safari">
</datalist>
```

### Common Input Attributes

| Attribute | Description |
|-----------|-------------|
| `name` | Key used when submitting form data |
| `id` | For associating with `<label>` |
| `value` | Default or submitted value |
| `placeholder` | Hint text shown when field is empty |
| `required` | Field must be filled before submission |
| `disabled` | Disables the field; not submitted |
| `readonly` | Field is visible but not editable |
| `min` / `max` | Min/max values for number/date inputs |
| `minlength` / `maxlength` | Character count limits |
| `pattern` | Regex the value must match |
| `autocomplete` | `on` or `off` for browser autocomplete |
| `autofocus` | Focuses the field on page load |
| `multiple` | Allows multiple values (file, email) |
| `step` | Increment for numeric inputs |

--- 

## Aside 

`<aside>` represents content **tangentially related** to the surrounding content. Typically rendered as a sidebar.

```html
<main>
  <article>
    <h2>Main Article</h2>
    <p>Article content...</p>
  </article>

  <aside>
    <h3>Related Topics</h3>
    <ul>
      <li><a href="/css">CSS Basics</a></li>
      <li><a href="/js">JavaScript Intro</a></li>
    </ul>
  </aside>
</main>
```

Use cases:
- Pull quotes
- Glossary definitions
- Author bios
- Related links or advertisements

--- 

## IFrames

`<iframe>` embeds another HTML document or external content inline.

```html
<iframe
  src="https://example.com"
  width="600"
  height="400"
  title="Example site"
  loading="lazy"
  sandbox="allow-scripts allow-same-origin">
</iframe>
```

- **`src`**: URL of the content to embed.
- **`title`**: Required for accessibility (screen readers).
- **`loading="lazy"`**: Defers loading until near the viewport.
- **`sandbox`**: Restricts capabilities of the embedded content. Values include `allow-scripts`, `allow-forms`, `allow-same-origin`, etc.
- **`allowfullscreen`**: Allows the iframe to go fullscreen (for videos).

> Be cautious embedding untrusted content — always use the `sandbox` attribute.

--- 

## Accessibility (ARIA)

**ARIA (Accessible Rich Internet Applications)** attributes extend HTML semantics for screen readers and assistive technologies.

```html
<!-- Role -->
<div role="alert">Form submitted successfully!</div>

<!-- Label for elements without visible text -->
<button aria-label="Close dialog">X</button>

<!-- Describes an element using another element's text -->
<input type="text" aria-describedby="hint">
<p id="hint">Must be at least 8 characters.</p>

<!-- Hide decorative elements from screen readers -->
<img src="decorative-line.svg" alt="" aria-hidden="true">

<!-- Live regions: announce dynamic changes -->
<div aria-live="polite" id="status"></div>

<!-- Expandable widget state -->
<button aria-expanded="false" aria-controls="menu">Toggle Menu</button>
<ul id="menu" hidden>...</ul>
```

Common ARIA attributes:

| Attribute | Description |
|-----------|-------------|
| `role` | Defines the element's role (e.g., `button`, `alert`, `dialog`) |
| `aria-label` | Provides an accessible name |
| `aria-labelledby` | Points to element(s) that label this one |
| `aria-describedby` | Points to element(s) that describe this one |
| `aria-hidden` | Hides from accessibility tree |
| `aria-expanded` | State of collapsible elements |
| `aria-live` | Announces dynamic content changes |
| `aria-required` | Marks form field as required |
| `aria-disabled` | Marks element as disabled |

> First rule of ARIA: use native HTML elements whenever possible. Only add ARIA when HTML semantics are insufficient.

--- 

## Meta Tags (SEO & Social)

Beyond the basics, meta tags control how pages appear in search results and social sharing previews.

```html
<head>
  <!-- Basic SEO -->
  <meta name="description" content="Learn HTML from scratch with this complete guide.">
  <meta name="keywords" content="HTML, web development, frontend">
  <meta name="author" content="Miguel">
  <meta name="robots" content="index, follow">

  <!-- Open Graph (Facebook, LinkedIn) -->
  <meta property="og:title" content="HTML Cheatsheet">
  <meta property="og:description" content="A complete HTML reference.">
  <meta property="og:image" content="https://example.com/thumbnail.png">
  <meta property="og:url" content="https://example.com/html">
  <meta property="og:type" content="website">

  <!-- Twitter Cards -->
  <meta name="twitter:card" content="summary_large_image">
  <meta name="twitter:title" content="HTML Cheatsheet">
  <meta name="twitter:description" content="A complete HTML reference.">
  <meta name="twitter:image" content="https://example.com/thumbnail.png">

  <!-- Canonical URL (prevents duplicate content penalty) -->
  <link rel="canonical" href="https://example.com/html">
</head>
```

--- 

## Scripts & Styles

### Inline vs External

```html
<!-- External CSS (preferred) -->
<link rel="stylesheet" href="style.css">

<!-- Inline CSS (avoid for large styles) -->
<style>
  body { font-family: sans-serif; }
</style>

<!-- Inline style on element (last resort) -->
<p style="color: red;">Warning</p>

<!-- External JS with defer (preferred) -->
<script src="app.js" defer></script>

<!-- External JS with async (for independent scripts) -->
<script src="analytics.js" async></script>

<!-- Inline JS -->
<script>
  console.log("Hello");
</script>
```

`<script>` loading strategies:

| Strategy | Behavior |
|----------|----------|
| *(none)* | Blocks HTML parsing while downloading and executing |
| `defer` | Downloads in parallel, executes **after** HTML is fully parsed |
| `async` | Downloads in parallel, executes **immediately** when ready (may block parsing) |

> Use `defer` for most scripts. Use `async` only for scripts independent of the DOM (analytics, ads).

--- 

## Aside

`<aside>` represents content that is **tangentially related** to the content surrounding it — meaning it could be removed and the main content would still make complete sense. It is most commonly used as a sidebar, but it is not exclusively a visual concept; it is a **semantic** one.

The key question to determine whether `<aside>` is appropriate: *"If this block were removed, would the surrounding content still be fully understandable?"* If yes, it is a candidate for `<aside>`.

### Sidebar

The classic use case — supplementary content placed next to the main body:

```html
<main>
  <article>
    <h2>Introduction to Networking</h2>
    <p>Networking connects computers together to share resources...</p>
  </article>

  <aside>
    <h3>Quick Reference</h3>
    <ul>
      <li>OSI Model has 7 layers</li>
      <li>TCP is connection-oriented</li>
      <li>UDP is connectionless</li>
    </ul>
  </aside>
</main>
```

### Pull Quote

Highlighting a quote extracted from the surrounding article:

```html
<article>
  <p>
    The internet relies on a vast infrastructure of cables, routers, and protocols
    that most users never see.
  </p>

  <aside>
    <blockquote>
      "The internet relies on a vast infrastructure most users never see."
    </blockquote>
  </aside>

  <p>At the physical layer, signals travel through fiber optic cables...</p>
</article>
```

### Author Bio

Contextual information about the author, tangential to the article itself:

```html
<article>
  <h2>Understanding TCP Handshakes</h2>
  <p>The three-way handshake establishes a reliable connection...</p>

  <aside>
    <h3>About the Author</h3>
    <img src="author.jpg" alt="Miguel">
    <p>Miguel is a systems programmer with a focus on low-level networking.</p>
  </aside>
</article>
```

### Callout / Tip Box

A note, tip, or warning that supplements the main text:

```html
<section>
  <h2>Subnetting</h2>
  <p>To subnet a network, borrow bits from the host portion of the IP address...</p>

  <aside>
    <strong>Tip:</strong> Always verify your subnet math with the formula
    <code>2<sup>n</sup> - 2</code> for usable hosts, where <em>n</em> is the
    number of host bits.
  </aside>

  <p>The resulting sub-networks each have their own network ID and broadcast address...</p>
</section>
```

### `<aside>` vs Similar Elements

| Element | Use When |
|---------|----------|
| `<aside>` | Content is tangentially related — can be removed without loss of meaning |
| `<section>` | Content is a thematic part of the page — belongs to the main flow |
| `<div>` | No semantic meaning needed; purely for layout or styling |
| `<figure>` | A self-contained unit like an image, diagram, or code listing |

--- 

## Page Structuring

Good HTML structure is the foundation of maintainable, accessible, and SEO-friendly pages.
The goal is to use semantic elements that accurately communicate the role of each region to browsers,
search engines, and screen readers.

### Header

`<header>` contains introductory content for its parent element. At the page level it holds the site logo, title, and primary navigation. Inside an `<article>` or `<section>` it holds the heading and metadata for that block.

- There can be **multiple `<header>` elements** on a page — one per sectioning element.
- Do not confuse with `<head>` (metadata) — `<header>` is visible content.

```html
<!-- Page-level header -->
<header>
  <a href="/" aria-label="Homepage">
    <img src="logo.svg" alt="SiteName">
  </a>
  <h1>SiteName</h1>
  <nav aria-label="Main navigation">
    <ul>
      <li><a href="/">Home</a></li>
      <li><a href="/blog">Blog</a></li>
      <li><a href="/contact">Contact</a></li>
    </ul>
  </nav>
</header>
```

```html
<!-- Article-level header -->
<article>
  <header>
    <h2>Understanding Subnetting</h2>
    <p>By Miguel &mdash; <time datetime="2026-05-24">May 24, 2026</time></p>
  </header>
  <p>Subnetting is the process of dividing a network...</p>
</article>
```

### Footer

`<footer>` contains closing content for its parent — copyright notices, contact links, legal text, or secondary navigation. Like `<header>`, it can appear inside any sectioning element, not just at the page level.

```html
<!-- Page-level footer -->
<footer>
  <nav aria-label="Footer navigation">
    <ul>
      <li><a href="/privacy">Privacy Policy</a></li>
      <li><a href="/terms">Terms of Service</a></li>
      <li><a href="/sitemap">Sitemap</a></li>
    </ul>
  </nav>
  <p>&copy; 2026 SiteName. All rights reserved.</p>
</footer>
```

```html
<!-- Article-level footer -->
<article>
  <h2>TCP vs UDP</h2>
  <p>...</p>
  <footer>
    <p>Tags: <a href="/tag/networking">Networking</a>, <a href="/tag/tcp">TCP</a></p>
  </footer>
</article>
```

### Navigation Bar

`<nav>` wraps **primary sets of navigation links**. Not every group of links qualifies — only those that represent major navigation for the document or site.

- Use `aria-label` when there are multiple `<nav>` elements on a page.
- Wrap the links in a `<ul>` so screen readers announce the number of items.
- Mark the current page with `aria-current="page"`.

```html
<!-- Top navigation bar -->
<nav aria-label="Main navigation">
  <ul>
    <li><a href="/" aria-current="page">Home</a></li>
    <li><a href="/about">About</a></li>
    <li>
      <a href="/topics">Topics</a>
      <!-- Dropdown submenu -->
      <ul>
        <li><a href="/topics/networking">Networking</a></li>
        <li><a href="/topics/algorithms">Algorithms</a></li>
      </ul>
    </li>
    <li><a href="/contact">Contact</a></li>
  </ul>
</nav>

<!-- Breadcrumb navigation -->
<nav aria-label="Breadcrumb">
  <ol>
    <li><a href="/">Home</a></li>
    <li><a href="/networking">Networking</a></li>
    <li aria-current="page">Subnetting</li>
  </ol>
</nav>
```

### Sections

`<section>` represents a **thematic grouping** of content that belongs to the page's main flow. Each section should have a heading that identifies its topic.

- Use `<section>` when the content is part of the page's primary outline.
- Do not use `<section>` as a generic wrapper — that is what `<div>` is for.
- A `<section>` without a heading is almost always wrong; use `<div>` instead.

```html
<main>
  <section id="introduction">
    <h2>Introduction</h2>
    <p>HTML is the backbone of every webpage...</p>
  </section>

  <section id="history">
    <h2>History</h2>
    <p>HTML was created by Tim Berners-Lee in 1991...</p>
  </section>

  <section id="features">
    <h2>Key Features of HTML5</h2>
    <ul>
      <li>Semantic elements</li>
      <li>Native audio and video</li>
      <li>Canvas API</li>
    </ul>
  </section>
</main>
```

### Articles

`<article>` is for **self-contained, independently distributable content**. The test: could this content be syndicated (e.g., via RSS) and still make sense on its own? If yes, it is an article.

- Blog posts, news items, forum posts, comments, product cards, and widget blocks are all valid uses.
- `<article>` elements can be nested — a comment inside a blog post is an `<article>` inside an `<article>`.

```html
<main>
  <h1>Latest Posts</h1>

  <article>
    <header>
      <h2><a href="/posts/tcp-handshake">How TCP Handshakes Work</a></h2>
      <p><time datetime="2026-05-20">May 20, 2026</time> &mdash; by Miguel</p>
    </header>
    <p>The three-way handshake is the process by which TCP establishes a connection...</p>
    <footer>
      <a href="/posts/tcp-handshake">Read more &rarr;</a>
    </footer>
  </article>

  <article>
    <header>
      <h2><a href="/posts/subnetting">Subnetting Explained</a></h2>
      <p><time datetime="2026-05-18">May 18, 2026</time> &mdash; by Miguel</p>
    </header>
    <p>Subnetting divides a network into smaller sub-networks...</p>
    <footer>
      <a href="/posts/subnetting">Read more &rarr;</a>
    </footer>
  </article>
</main>
```

### Sidebar

A sidebar is an `<aside>` placed alongside the main content. It holds supplementary content — related links, ads, author info, tag clouds, or recent posts — that enriches but does not define the page.

```html
<div class="layout">
  <main>
    <article>
      <h2>DNS Explained</h2>
      <p>DNS translates domain names to IP addresses...</p>
    </article>
  </main>

  <aside aria-label="Sidebar">
    <section>
      <h3>Related Articles</h3>
      <ul>
        <li><a href="/posts/ip-addresses">IP Addresses</a></li>
        <li><a href="/posts/routing">Routing Basics</a></li>
      </ul>
    </section>

    <section>
      <h3>Topics</h3>
      <ul>
        <li><a href="/tag/networking">Networking</a></li>
        <li><a href="/tag/protocols">Protocols</a></li>
      </ul>
    </section>
  </aside>
</div>
```

### Images and Videos in Context

Images and videos that are directly referenced by surrounding content should be wrapped in `<figure>` with a `<figcaption>`. Purely decorative images go inside regular elements without `<figure>`.

```html
<!-- Contextual image with caption -->
<figure>
  <img
    src="osi-model.png"
    alt="Diagram of the 7-layer OSI model with labels for each layer"
    width="800"
    height="500"
    loading="lazy">
  <figcaption>Figure 1: The OSI Model and its 7 layers.</figcaption>
</figure>

<!-- Responsive image -->
<figure>
  <picture>
    <source srcset="diagram-large.webp" media="(min-width: 900px)" type="image/webp">
    <source srcset="diagram-small.webp" type="image/webp">
    <img src="diagram-small.jpg" alt="Network topology diagram">
  </picture>
  <figcaption>Figure 2: Star topology network.</figcaption>
</figure>

<!-- Contextual video -->
<figure>
  <video controls width="720" poster="thumbnail.jpg">
    <source src="tcp-demo.mp4" type="video/mp4">
    Your browser does not support video.
  </video>
  <figcaption>Video: TCP three-way handshake animated.</figcaption>
</figure>

<!-- Decorative image (no figure needed) -->
<header>
  <img src="hero-banner.jpg" alt="" aria-hidden="true">
  <h1>Welcome to the Blog</h1>
</header>
```

### `<div>` vs Semantic Elements

`<div>` is a **layout tool**, not a content descriptor. The rule of thumb: reach for a semantic element first; only fall back to `<div>` when none fits.

| Situation | Use |
|-----------|-----|
| Page-level intro with logo and nav | `<header>` |
| Page-level closing content | `<footer>` |
| Primary unique content of the page | `<main>` |
| Thematic content group with a heading | `<section>` |
| Standalone, distributable content | `<article>` |
| Tangentially related supplementary content | `<aside>` |
| Navigation link group | `<nav>` |
| Image or media with a caption | `<figure>` + `<figcaption>` |
| Generic layout box with no semantic role | `<div>` |
| Generic inline wrapper with no semantic role | `<span>` |

```html
<!-- Wrong: div soup -->
<div class="header">
  <div class="nav">
    <div class="nav-item"><a href="/">Home</a></div>
  </div>
</div>
<div class="content">
  <div class="post">...</div>
  <div class="sidebar">...</div>
</div>

<!-- Correct: semantic structure -->
<header>
  <nav>
    <ul>
      <li><a href="/">Home</a></li>
    </ul>
  </nav>
</header>
<main>
  <article>...</article>
  <aside>...</aside>
</main>
```

When `<div>` is appropriate:

```html
<!-- Wrapping elements solely for CSS layout (e.g., a flex/grid container) -->
<div class="card-grid">
  <article class="card">...</article>
  <article class="card">...</article>
  <article class="card">...</article>
</div>

<!-- Grouping unrelated elements for a JS component boundary -->
<div id="modal" role="dialog" aria-modal="true" aria-labelledby="modal-title">
  <h2 id="modal-title">Confirm Action</h2>
  <p>Are you sure you want to delete this item?</p>
  <button type="button">Cancel</button>
  <button type="button">Delete</button>
</div>
```

### Forms, Buttons, and Inputs

Forms are interaction points embedded within the page structure. Their placement follows the same semantic logic as the rest of the document — they should live inside the element that best describes their context.

**Where to place forms:**

| Context | Container |
|---------|-----------|
| Site-wide search | `<header>` or `<nav>` |
| Newsletter signup in sidebar | `<aside>` |
| Contact or feedback form | `<section>` inside `<main>` |
| Comment submission below an article | `<article>` (nested) or `<section>` after `<article>` |
| Login / registration page | `<main>` with a single focused `<section>` |
| Checkout step in a multi-step flow | `<main>` + `<fieldset>` per step |

**Search bar in header:**

```html
<header>
  <a href="/" aria-label="Homepage"><img src="logo.svg" alt="SiteName"></a>
  <nav aria-label="Main navigation">
    <ul>
      <li><a href="/">Home</a></li>
      <li><a href="/blog">Blog</a></li>
    </ul>
  </nav>
  <form role="search" action="/search" method="GET">
    <label for="search" class="visually-hidden">Search</label>
    <input type="search" id="search" name="q" placeholder="Search posts...">
    <button type="submit" aria-label="Submit search">&#128269;</button>
  </form>
</header>
```

**Contact form in its own section:**

```html
<main>
  <section id="contact" aria-labelledby="contact-heading">
    <h2 id="contact-heading">Get in Touch</h2>
    <p>Fill in the form below and I will get back to you within 48 hours.</p>

    <form action="/contact" method="POST">
      <fieldset>
        <legend>Your Details</legend>

        <label for="name">Full Name</label>
        <input type="text" id="name" name="name" required autocomplete="name">

        <label for="email">Email Address</label>
        <input type="email" id="email" name="email" required autocomplete="email">
      </fieldset>

      <fieldset>
        <legend>Message</legend>

        <label for="subject">Subject</label>
        <input type="text" id="subject" name="subject" required>

        <label for="body">Message</label>
        <textarea id="body" name="body" rows="6" required
                  placeholder="Describe your question or topic..."></textarea>
      </fieldset>

      <div class="form-actions">
        <button type="reset">Clear</button>
        <button type="submit">Send Message</button>
      </div>
    </form>
  </section>
</main>
```

**Comment form nested inside an article:**

```html
<article>
  <header>
    <h2>TCP Handshakes Explained</h2>
    <time datetime="2026-05-20">May 20, 2026</time>
  </header>

  <p>The three-way handshake establishes a TCP connection...</p>

  <!-- Comments are articles nested inside the parent article -->
  <section aria-labelledby="comments-heading">
    <h3 id="comments-heading">Comments (2)</h3>

    <article>
      <header>
        <strong>Alice</strong> &mdash;
        <time datetime="2026-05-21">May 21, 2026</time>
      </header>
      <p>Great explanation! The diagram really helped.</p>
    </article>

    <article>
      <header>
        <strong>Bob</strong> &mdash;
        <time datetime="2026-05-22">May 22, 2026</time>
      </header>
      <p>Could you also cover the FIN sequence for closing a connection?</p>
    </article>
  </section>

  <!-- Comment submission form -->
  <section aria-labelledby="leave-comment-heading">
    <h3 id="leave-comment-heading">Leave a Comment</h3>
    <form action="/comment" method="POST">
      <input type="hidden" name="post-id" value="tcp-handshake">

      <label for="author">Name</label>
      <input type="text" id="author" name="author" required autocomplete="name">

      <label for="comment">Comment</label>
      <textarea id="comment" name="comment" rows="4" required></textarea>

      <button type="submit">Post Comment</button>
    </form>
  </section>
</article>
```

**Button placement rules:**

- Use `<button type="button">` for JS-driven actions (open modal, toggle menu, copy to clipboard).
- Use `<button type="submit">` only inside a `<form>` — it submits the form.
- Use `<a>` for navigation, never `<button>` with an `onclick` that changes the URL.
- Group destructive and safe actions so the safe option comes first:

```html
<div class="dialog-actions">
  <button type="button">Cancel</button>       <!-- safe first -->
  <button type="button" class="danger">Delete</button>
</div>
```

---

### Full Page Structure Example

A complete blog-style page combining all of the above:

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta name="description" content="A blog covering programming, networking, and systems.">
  <title>TechBlog &mdash; Home</title>
  <link rel="stylesheet" href="style.css">
  <link rel="icon" href="favicon.ico">
  <script src="app.js" defer></script>
</head>
<body>

  <!-- ==================== SITE HEADER ==================== -->
  <header>
    <a href="/" aria-label="TechBlog homepage">
      <img src="logo.svg" alt="TechBlog">
    </a>

    <!-- Primary navigation -->
    <nav aria-label="Main navigation">
      <ul>
        <li><a href="/" aria-current="page">Home</a></li>
        <li><a href="/networking">Networking</a></li>
        <li><a href="/algorithms">Algorithms</a></li>
        <li><a href="/about">About</a></li>
      </ul>
    </nav>
  </header>

  <!-- ==================== MAIN CONTENT ==================== -->
  <main>

    <!-- Hero section -->
    <section id="hero">
      <h1>Programming Notes & Cheatsheets</h1>
      <p>Deep-dive references for networking, algorithms, systems, and more.</p>
      <a href="/posts">Browse all posts &rarr;</a>
    </section>

    <!-- Layout: article feed + sidebar -->
    <div class="layout">

      <!-- Article feed -->
      <section id="recent-posts" aria-labelledby="recent-heading">
        <h2 id="recent-heading">Recent Posts</h2>

        <article>
          <header>
            <h3><a href="/posts/tcp-handshake">How TCP Handshakes Work</a></h3>
            <p>
              By <a href="/about">Miguel</a> &mdash;
              <time datetime="2026-05-20">May 20, 2026</time>
            </p>
          </header>

          <figure>
            <img
              src="tcp-diagram.png"
              alt="Sequence diagram of the TCP three-way handshake: SYN, SYN-ACK, ACK"
              width="600"
              height="300"
              loading="lazy">
            <figcaption>Figure 1: TCP three-way handshake.</figcaption>
          </figure>

          <p>
            Before data is exchanged, TCP establishes a connection using a
            three-way handshake: SYN &rarr; SYN-ACK &rarr; ACK...
          </p>

          <footer>
            <a href="/posts/tcp-handshake">Read more &rarr;</a>
            <p>Tags: <a href="/tag/networking">Networking</a>, <a href="/tag/tcp">TCP</a></p>
          </footer>
        </article>

        <article>
          <header>
            <h3><a href="/posts/subnetting">Subnetting Explained</a></h3>
            <p>
              By <a href="/about">Miguel</a> &mdash;
              <time datetime="2026-05-18">May 18, 2026</time>
            </p>
          </header>
          <p>
            Subnetting divides a single network into smaller sub-networks
            by borrowing bits from the host portion of an IP address...
          </p>
          <footer>
            <a href="/posts/subnetting">Read more &rarr;</a>
          </footer>
        </article>

      </section>

      <!-- Sidebar -->
      <aside aria-label="Sidebar">

        <section>
          <h2>About</h2>
          <img src="avatar.jpg" alt="Miguel" width="80" height="80">
          <p>Systems programmer writing about networking, algorithms, and low-level topics.</p>
          <a href="/about">More about me &rarr;</a>
        </section>

        <section>
          <h2>Topics</h2>
          <ul>
            <li><a href="/networking">Networking</a></li>
            <li><a href="/algorithms">Algorithms</a></li>
            <li><a href="/low-level">Low Level</a></li>
            <li><a href="/data-structures">Data Structures</a></li>
          </ul>
        </section>

        <section>
          <h2>Newsletter</h2>
          <form action="/subscribe" method="POST">
            <label for="email">Email address</label>
            <input type="email" id="email" name="email" required
                   placeholder="you@example.com">
            <button type="submit">Subscribe</button>
          </form>
        </section>

      </aside>

    </div><!-- /.layout -->

  </main>

  <!-- ==================== SITE FOOTER ==================== -->
  <footer>
    <nav aria-label="Footer navigation">
      <ul>
        <li><a href="/privacy">Privacy</a></li>
        <li><a href="/terms">Terms</a></li>
        <li><a href="/contact">Contact</a></li>
      </ul>
    </nav>
    <p>&copy; 2026 TechBlog. All rights reserved.</p>
  </footer>

</body>
</html>
```

--- 


## Full Example 

This is an example using almost all of the concepts above.

```html

```



