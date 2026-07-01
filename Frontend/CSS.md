# CSS 

**CSS (Cascading Style Sheets)** is the language used to define the appearance of HTML elements.
Rules consist of a **selector** that targets elements and a **declaration block** containing property-value pairs.

```css
selector {
  property: value;
  property: value;
}
```

The **cascade** determines which rules apply when multiple rules target the same element, resolved through
**specificity**, **inheritance**, and **source order**.

--- 

## Selectors

Selectors target which HTML elements a rule applies to.

### Basic Selectors

```css
/* Universal — matches every element */
* { box-sizing: border-box; }

/* Type — matches all <p> elements */
p { color: #333; }

/* Class — matches elements with class="card" */
.card { border-radius: 8px; }

/* ID — matches the element with id="hero" */
#hero { background: #000; }

/* Attribute — matches <input type="text"> */
input[type="text"] { border: 1px solid #ccc; }

/* Attribute contains value */
a[href*="example"] { color: red; }

/* Attribute starts with value */
a[href^="https"] { color: green; }

/* Attribute ends with value */
a[href$=".pdf"] { color: orange; }
```

### Grouping & Combinators

```css
/* Grouping — apply the same rules to multiple selectors */
h1, h2, h3 { font-family: sans-serif; }

/* Descendant — any <p> inside a .card, at any depth */
.card p { font-size: 0.9rem; }

/* Child (>) — only direct <li> children of <ul> */
ul > li { list-style: none; }

/* Adjacent sibling (+) — <p> immediately after an <h2> */
h2 + p { margin-top: 0; }

/* General sibling (~) — all <p> siblings after an <h2> */
h2 ~ p { color: #555; }
```

### Pseudo-classes

Target elements based on state or position in the DOM:

```css
a:hover        { text-decoration: underline; }
a:focus        { outline: 2px solid blue; }
a:visited      { color: purple; }
a:active       { color: red; }

button:disabled { opacity: 0.5; cursor: not-allowed; }

input:checked  { accent-color: green; }
input:required { border-color: red; }
input:valid    { border-color: green; }
input:invalid  { border-color: red; }

/* Structural pseudo-classes */
li:first-child       { font-weight: bold; }
li:last-child        { border-bottom: none; }
li:nth-child(2)      { background: #f0f0f0; }   /* 2nd item */
li:nth-child(odd)    { background: #fafafa; }    /* 1st, 3rd, 5th… */
li:nth-child(3n+1)   { color: blue; }            /* every 3rd starting at 1 */
p:not(.intro)        { color: #666; }            /* all <p> without .intro */
section:empty        { display: none; }
```

### Pseudo-elements

Target a specific part of an element:

```css
/* First line / first letter of text */
p::first-line   { font-variant: small-caps; }
p::first-letter { font-size: 2em; float: left; }

/* Insert content before/after element (requires content property) */
.required::after  { content: " *"; color: red; }
.quote::before    { content: "\201C"; }
.quote::after     { content: "\201D"; }

/* Selected text */
::selection { background: #ffdd57; color: #000; }

/* Placeholder text in inputs */
input::placeholder { color: #aaa; font-style: italic; }
```

### Relationship Selector 

The **descendant**, **child**, **adjacent sibling**, and **general sibling** combinators define structural relationships 
between elements and their rules. Choosing the right combinator avoids over-selecting and keeps styles predictable.

```css
/* Style only direct children, not grandchildren */
.nav > li { display: inline-block; }

/* Remove top margin from a paragraph that immediately follows a heading */
h2 + p { margin-top: 0.25rem; }

/* Highlight all sibling paragraphs after an aside (not the aside itself) */
aside ~ p { opacity: 0.8; }

/* Any link inside a footer, at any depth */
footer a { color: #ccc; }
```

### Specificity

When multiple rules target the same element and property, the browser uses **specificity** to decide which wins. Specificity is
a score calculated as `(A, B, C)`:

| Selector type | Contribution |
|---------------|-------------|
| Inline style (`style=""`) | `(1,0,0,0)` — always wins over stylesheets |
| ID (`#id`) | `(0,1,0,0)` |
| Class, attribute, pseudo-class | `(0,0,1,0)` |
| Type (tag), pseudo-element | `(0,0,0,1)` |
| Universal `*`, combinators | `(0,0,0,0)` |

```css
p               { color: black; }    /* (0,0,0,1) */
.intro          { color: blue;  }    /* (0,0,1,0) — wins over type */
#hero p         { color: green; }    /* (0,1,0,1) — wins over class */
```

- **`!important`** overrides all specificity. Avoid except for utility overrides.
- When specificity is equal, the rule declared **last in source order** wins.
- Keep specificity low and flat — avoid deep chains like `#app .sidebar ul > li a`.

--- 

## Basic Styling

Fundamental properties that apply to most elements:

```css
.element {
  /* Color */
  color: #333333;
  background-color: #f5f5f5;
  opacity: 0.9;               /* 0 (transparent) to 1 (opaque) */

  /* Dimensions */
  width: 300px;
  height: 200px;
  min-width: 100px;
  max-width: 800px;
  min-height: 50px;
  max-height: 400px;

  /* Cursor */
  cursor: pointer;            /* auto | default | pointer | not-allowed | grab | text */

  /* Visibility */
  visibility: visible;        /* hidden hides but keeps space; display:none removes it */

  /* Overflow */
  overflow: hidden;           /* visible | hidden | scroll | auto */
  overflow-x: scroll;
  overflow-y: hidden;
}
```

--- 

## Units

CSS units fall into two categories: **absolute** (fixed size) and **relative** (scaled to something else).

### Absolute

| Unit | Description |
|------|-------------|
| `px` | Pixel — the most common absolute unit |
| `pt` | Point — used in print stylesheets (1pt = 1/72 inch) |
| `cm` / `mm` | Centimetres / millimetres — rarely used on screen |

### Relative

| Unit | Relative To |
|------|-------------|
| `%` | Parent element's dimension |
| `em` | Current element's own `font-size` (compounds when nested) |
| `rem` | Root element (`<html>`) `font-size` — predictable, no compounding |
| `vw` | 1% of the viewport width |
| `vh` | 1% of the viewport height |
| `vmin` | 1% of the smaller viewport dimension |
| `vmax` | 1% of the larger viewport dimension |
| `ch` | Width of the `0` character in the current font |
| `lh` | Current line height |

```css
html { font-size: 16px; }     /* 1rem = 16px throughout the page */

h1   { font-size: 2rem; }     /* 32px — relative to root */
p    { font-size: 1rem; }     /* 16px */
p    { padding: 1em; }        /* 16px — relative to p's own font-size */

.hero { height: 100vh; }      /* Full viewport height */
.sidebar { width: 25%; }      /* 25% of parent width */
```

> Prefer `rem` for font sizes and spacing to respect user browser settings. Use `px` for borders and fine details.

--- 

## Box Model 

Every HTML element is a rectangular box. The **box model** describes the layers of that box from inside out.

```txt
┌────────────────────────────── margin ────────────────────────────────┐
│  ┌─────────────────────────── border ─────────────────────────────┐  │
│  │  ┌──────────────────────── padding ────────────────────────┐   │  │
│  │  │                                                         │   │  │
│  │  │                        content                          │   │  │
│  │  │                                                         │   │  │
│  │  └─────────────────────────────────────────────────────────┘   │  │
│  └────────────────────────────────────────────────────────────────┘  │
└──────────────────────────────────────────────────────────────────────┘
```

By default, `width` and `height` only apply to the **content** area. Use `box-sizing: border-box` to include padding and border in those dimensions.

```css
*, *::before, *::after {
  box-sizing: border-box;  /* Industry standard reset */
}
```

- **Content**: The inner area where text and child elements render.

```css
.box {
  width: 400px;
  height: 200px;
}
```

- **Padding**: Space between the content and the border. Inherits the element's background color.

```css
.box {
  padding: 16px;                     /* all sides */
  padding: 8px 16px;                 /* top/bottom  left/right */
  padding: 4px 8px 12px 16px;       /* top right bottom left (clockwise) */

  /* Longhand */
  padding-top: 8px;
  padding-right: 16px;
  padding-bottom: 8px;
  padding-left: 16px;
}
```

- **Border**: The line drawn around the padding area.

```css
.box {
  border: 2px solid #333;            /* width style color — shorthand */
  border-radius: 8px;                /* rounds all corners */
  border-radius: 4px 8px 4px 8px;   /* top-left top-right bottom-right bottom-left */

  /* Longhand sides */
  border-top: 1px dashed red;
  border-bottom: none;

  /* Longhand properties */
  border-width: 2px;
  border-style: solid;               /* solid | dashed | dotted | double | none */
  border-color: #ccc;
}
```

- **Margin**: Space outside the border — transparent, creates distance between elements.

```css
.box {
  margin: 16px;                      /* all sides */
  margin: 0 auto;                    /* top/bottom=0, left/right=auto (centers block elements) */
  margin: 8px 16px 8px 16px;        /* top right bottom left */

  /* Longhand */
  margin-top: 24px;
  margin-bottom: 24px;
}
```

> **Margin collapsing**: vertical margins of adjacent block elements collapse to the larger of the two. Only affects `margin-top` and `margin-bottom`, never horizontal margins.

--- 

## Color 

Colors can be expressed in multiple formats:

```css
.element {
  /* Named */
  color: red;
  color: transparent;

  /* Hex */
  color: #ff0000;           /* #RRGGBB */
  color: #ff0000aa;         /* #RRGGBBAA — with alpha */
  color: #f00;              /* shorthand #RGB */

  /* RGB / RGBA */
  color: rgb(255, 0, 0);
  color: rgba(255, 0, 0, 0.5);   /* alpha: 0=transparent, 1=opaque */

  /* HSL / HSLA — Hue (0-360°) Saturation% Lightness% */
  color: hsl(0, 100%, 50%);
  color: hsla(0, 100%, 50%, 0.5);

  /* Modern syntax (CSS Color Level 4) */
  color: rgb(255 0 0 / 50%);
  color: hsl(0 100% 50% / 0.5);
}
```

### CSS Custom Properties (Variables)

```css
:root {
  --color-primary:   #3b82f6;
  --color-secondary: #6366f1;
  --color-text:      #1f2937;
  --color-bg:        #f9fafb;
}

.button {
  background-color: var(--color-primary);
  color: var(--color-bg);
}

.button:hover {
  background-color: var(--color-secondary);
}
```

Variables cascade and can be overridden at any scope:

```css
.dark-theme {
  --color-text: #f9fafb;
  --color-bg:   #111827;
}
```

--- 

## Display

`display` controls how an element participates in the layout.

```css
.element { display: block; }
```

| Value | Behavior |
|-------|----------|
| `block` | Takes full width, starts on a new line (`<div>`, `<p>`, `<h1>`) |
| `inline` | Flows with text, ignores `width`/`height` (`<span>`, `<a>`, `<strong>`) |
| `inline-block` | Flows like inline but respects `width`/`height` |
| `flex` | Turns element into a flex container |
| `inline-flex` | Flex container that flows inline |
| `grid` | Turns element into a grid container |
| `inline-grid` | Grid container that flows inline |
| `none` | Removes element from layout entirely (not just hidden) |
| `contents` | Element itself has no box; children render as if the element did not exist |
| `table` | Behaves like a `<table>` element |

### Visibility vs Display

```css
.hidden-preserve-space { visibility: hidden; } /* invisible but still takes up space */
.hidden-remove-space   { display: none; }      /* invisible and removed from flow */
```

--- 

## Float

**Float** allows elements to take the space a block would normally occupy and let inline content wrap around it.

```css
.image {
  float: left;      /* left | right | none */
  margin: 0 16px 16px 0; /* spacing around the floated element */
}
```

--- 

## Positioning 

There are different ways to position element inside elements, relative to the normal flow, the viewport, or a containing block.

- **Static** (default) — normal flow, no special positioning.
- **Relative** — offset from its normal position, but still occupies space.
- **Absolute** — positioned relative to the nearest positioned ancestor (not static). Removed from normal flow.
- **Fixed** — positioned relative to the viewport, stays in place on scroll.
- **Sticky** — toggles between relative and fixed, depending on scroll position.

```css
.element {
  position: relative;   /* static | relative | absolute | fixed | sticky */
  top: 16px;            /* offset from top */
  right: 0;             /* offset from right */
  bottom: 0;            /* offset from bottom */
  left: 0;              /* offset from left */
  z-index: 10;          /* stacking order — higher values appear on top */
}
```

--- 

## Flex Box 

**Flexbox** is a one-dimensional layout model — it lays items out along a single axis (row or column).

### Container Properties

- **flex-direction**: determines the main axis direction — row (default), row-reverse, column, column-reverse.

- **justify-content**: aligns items along the main axis (start, end, center, space-between, space-around, space-evenly).

- **align-items**: aligns items along the cross axis (vertically) (stretch, start, end, center, baseline).

- **flex-wrap**: controls whether items wrap onto multiple lines (nowrap, wrap, wrap-reverse).

- **align-content**: aligns wrapped lines along the cross axis (stretch, start, end, center, space-between, space-around).

```css
.flex-container {
  display: flex;

  /* Axis direction */
  flex-direction: row;            /* row | row-reverse | column | column-reverse */

  /* Wrapping */
  flex-wrap: nowrap;              /* nowrap | wrap | wrap-reverse */

  /* Shorthand for flex-direction + flex-wrap */
  flex-flow: row wrap;

  /* Alignment along the main axis (horizontal by default) */
  justify-content: flex-start;   /* flex-start | flex-end | center | space-between | space-around | space-evenly */

  /* Alignment along the cross axis (vertical by default) */
  align-items: stretch;          /* stretch | flex-start | flex-end | center | baseline */

  /* Alignment of wrapped lines along the cross axis */
  align-content: flex-start;     /* same values as justify-content */

  /* Spacing between items */
  gap: 16px;                     /* row-gap column-gap */
  gap: 8px 16px;
}
```

### Item Properties

- **flex-grow**: how much the item grows relative to siblings (default 0). 

- **flex-shrink**: how much the item shrinks when space is tight (default 1).

- **flex-basis**: the base size of the item before grow/shrink is applied (default auto).

- **order**: controls the visual order of items (default 0).

- **flex**: shorthand for `flex-grow`, `flex-shrink`, and `flex-basis`.

- **align-self**: overrides the container's `align-items` for this item only.

```css
.flex-item {
  /* Growth: how much the item grows relative to siblings */
  flex-grow: 1;      /* default 0 — does not grow */

  /* Shrink: how much the item shrinks when space is tight */
  flex-shrink: 1;    /* default 1 — can shrink */

  /* Base size before grow/shrink is applied */
  flex-basis: 200px; /* default auto */

  /* Shorthand: grow shrink basis */
  flex: 1 1 auto;
  flex: 1;           /* equivalent to flex: 1 1 0 */

  /* Override container's align-items for this item only */
  align-self: center;

  /* Reorder visually (does not change DOM order) */
  order: 2;          /* default 0; lower values appear first */
}
```

### Common Patterns

```css
/* Center an item both horizontally and vertically */
.center {
  display: flex;
  justify-content: center;
  align-items: center;
}

/* Equal-width columns that wrap on small screens */
.columns {
  display: flex;
  flex-wrap: wrap;
  gap: 16px;
}
.column {
  flex: 1 1 250px;   /* grow, shrink, min-width before wrapping */
}

/* Push last item to the far end */
.nav {
  display: flex;
  align-items: center;
}
.nav .spacer { flex: 1; }  /* fills all remaining space */
```

--- 

## Grid 

**CSS Grid** is a two-dimensional layout system — rows and columns simultaneously.

### Container Properties

```css
.grid-container {
  display: grid;

  /* Define columns: 3 equal columns */
  grid-template-columns: 1fr 1fr 1fr;
  grid-template-columns: repeat(3, 1fr);      /* shorthand */
  grid-template-columns: 200px 1fr 2fr;       /* mixed sizes */
  grid-template-columns: repeat(auto-fit, minmax(250px, 1fr)); /* responsive */

  /* Define rows */
  grid-template-rows: auto 1fr auto;          /* header, main, footer */

  /* Gaps between tracks */
  gap: 24px;
  gap: 16px 24px;             /* row-gap column-gap */

  /* Named areas */
  grid-template-areas:
    "header header header"
    "sidebar main main"
    "footer footer footer";

  /* Alignment of all items inside their cells */
  justify-items: stretch;     /* stretch | start | end | center */
  align-items: stretch;

  /* Alignment of the grid itself within the container */
  justify-content: start;
  align-content: start;
}
```

### Item Properties

```css
.grid-item {
  /* Span specific columns */
  grid-column: 1 / 3;         /* from line 1 to line 3 (spans 2 columns) */
  grid-column: span 2;        /* span 2 columns from auto-placed position */

  /* Span specific rows */
  grid-row: 1 / 4;
  grid-row: span 2;

  /* Place in a named area */
  grid-area: header;

  /* Override alignment for this item only */
  justify-self: center;
  align-self: end;
}
```

### Named Template Areas

```css
.layout {
  display: grid;
  grid-template-columns: 220px 1fr;
  grid-template-rows: auto 1fr auto;
  grid-template-areas:
    "header  header"
    "sidebar main"
    "footer  footer";
  min-height: 100vh;
}

header  { grid-area: header; }
.sidebar{ grid-area: sidebar; }
main    { grid-area: main; }
footer  { grid-area: footer; }
```

### Responsive Grid (no media queries needed)

```css
.card-grid {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(240px, 1fr));
  gap: 24px;
}
/* Cards automatically reflow: 4 per row on desktop, 1 on mobile */
```

--- 

## Images 

```css
img {
  /* Prevent images from overflowing their container */
  max-width: 100%;
  height: auto;          /* maintains aspect ratio */
  display: block;        /* removes bottom whitespace gap (inline by default) */
}

/* Cover a container while maintaining aspect ratio */
.thumbnail {
  width: 300px;
  height: 200px;
  object-fit: cover;     /* cover | contain | fill | none | scale-down */
  object-position: center top;  /* focus point when cropped */
}

/* Responsive image that fills its grid cell */
.hero-image {
  width: 100%;
  height: 400px;
  object-fit: cover;
}

/* Circular avatar */
.avatar {
  width: 64px;
  height: 64px;
  border-radius: 50%;
  object-fit: cover;
}
```

---

## Background

```css
.element {
  /* Color */
  background-color: #f5f5f5;

  /* Image */
  background-image: url("hero.jpg");

  /* Repeat */
  background-repeat: no-repeat;    /* repeat | repeat-x | repeat-y | no-repeat | space | round */

  /* Size */
  background-size: cover;          /* cover | contain | auto | 100% | 300px 200px */

  /* Position */
  background-position: center;     /* top | bottom | left | right | center | 50% 25% */

  /* Attachment */
  background-attachment: fixed;    /* scroll | fixed | local */

  /* Origin & clip */
  background-origin: border-box;   /* padding-box | border-box | content-box */
  background-clip: text;           /* padding-box | border-box | content-box | text */

  /* Shorthand: color image repeat position / size attachment */
  background: #1a1a2e url("bg.jpg") no-repeat center / cover fixed;

  /* Multiple backgrounds (front to back) */
  background:
    url("overlay.png") no-repeat center / cover,
    url("texture.jpg") repeat,
    #0f3460;
}
```

--- 

## Gradients 

Gradients are generated images — they can be used anywhere an `<image>` value is accepted (most commonly `background-image`).

### Linear Gradient

```css
/* Direction keywords or angle */
background: linear-gradient(to right, #3b82f6, #6366f1);
background: linear-gradient(135deg, #ff6b6b, #feca57, #48dbfb);

/* With color stops and positions */
background: linear-gradient(to bottom,
  #000000 0%,
  #000000 40%,
  #3b82f6 100%
);
```

### Radial Gradient

```css
/* Circle from center */
background: radial-gradient(circle, #3b82f6 0%, #1e1b4b 100%);

/* Ellipse at a specific position */
background: radial-gradient(ellipse at top left, #ff6b6b, #6366f1);
```

### Conic Gradient

```css
/* Pie-chart-like gradient sweeping around a center point */
background: conic-gradient(#3b82f6 0%, #6366f1 50%, #3b82f6 100%);

/* Pie chart segments */
background: conic-gradient(
  #f87171 0deg 90deg,
  #fbbf24 90deg 200deg,
  #34d399 200deg 360deg
);
```

### Repeating Gradients

```css
/* Repeating stripe pattern */
background: repeating-linear-gradient(
  45deg,
  #3b82f6 0px,
  #3b82f6 10px,
  transparent 10px,
  transparent 20px
);
```

--- 

## Fonts 

### Font Family

```css
body {
  /* Font stack: browser tries each in order */
  font-family: "Inter", "Segoe UI", Roboto, Arial, sans-serif;
}

/* Generic families */
font-family: serif;       /* Times New Roman, Georgia */
font-family: sans-serif;  /* Arial, Helvetica */
font-family: monospace;   /* Courier New, Consolas */
font-family: cursive;
font-family: fantasy;
```

### Internal (System / Preloaded)

Using fonts already available on the system or bundled with the project:

```css
/* System font stack — no downloads, fast */
body {
  font-family: system-ui, -apple-system, BlinkMacSystemFont,
               "Segoe UI", Roboto, Oxygen, Ubuntu, sans-serif;
}

/* Self-hosted font using @font-face */
@font-face {
  font-family: "MyFont";
  src: url("fonts/myfont.woff2") format("woff2"),
       url("fonts/myfont.woff")  format("woff");
  font-weight: 400;
  font-style: normal;
  font-display: swap;   /* shows fallback font until custom font loads */
}

body {
  font-family: "MyFont", sans-serif;
}
```

### External

Loading fonts from a remote provider (e.g., Google Fonts):

```html
<!-- In <head> — preconnect for performance -->
<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=Inter:wght@400;600;700&display=swap" rel="stylesheet">
```

```css
/* Then use it in CSS */
body {
  font-family: "Inter", sans-serif;
}
```

--- 

## Text Formatting 

```css
.text {
  /* Size */
  font-size: 1rem;

  /* Weight */
  font-weight: 400;          /* normal | bold | 100–900 */

  /* Style */
  font-style: italic;        /* normal | italic | oblique */

  /* Variant */
  font-variant: small-caps;

  /* Line height */
  line-height: 1.6;          /* unitless preferred — relative to font-size */

  /* Letter & word spacing */
  letter-spacing: 0.05em;
  word-spacing: 0.1em;

  /* Shorthand: style variant weight size/line-height family */
  font: italic small-caps 700 1.25rem/1.4 "Inter", sans-serif;
}
```

--- 

## Text Styling 

```css
.text {
  /* Alignment */
  text-align: left;              /* left | right | center | justify */

  /* Decoration */
  text-decoration: underline;    /* none | underline | overline | line-through */
  text-decoration: underline dotted red;   /* shorthand: line style color */

  /* Transformation */
  text-transform: uppercase;     /* none | uppercase | lowercase | capitalize */

  /* Indentation */
  text-indent: 2em;

  /* Shadow: offset-x offset-y blur-radius color */
  text-shadow: 2px 2px 4px rgba(0,0,0,0.3);
  text-shadow: 0 0 8px #3b82f6;  /* glow effect */

  /* Overflow handling */
  white-space: nowrap;           /* prevents wrapping */
  overflow: hidden;
  text-overflow: ellipsis;       /* shows "…" when text overflows */

  /* Multi-line ellipsis (webkit) */
  display: -webkit-box;
  -webkit-line-clamp: 3;         /* show max 3 lines */
  -webkit-box-orient: vertical;
  overflow: hidden;

  /* Word breaking */
  word-break: break-word;        /* normal | break-all | break-word | keep-all */
  overflow-wrap: anywhere;
}
```

--- 

## Transitions 

Transitions animate a property smoothly from one value to another when it changes (e.g., on hover).

```css
.button {
  background-color: #3b82f6;

  /* Shorthand: property duration timing-function delay */
  transition: background-color 0.3s ease 0s;

  /* Multiple properties */
  transition:
    background-color 0.3s ease,
    transform        0.2s ease-out,
    box-shadow       0.3s ease;

  /* Transition all changing properties */
  transition: all 0.3s ease;
}

.button:hover {
  background-color: #2563eb;
  transform: translateY(-2px);
  box-shadow: 0 4px 12px rgba(0,0,0,0.2);
}
```

### Timing Functions

```css
transition-timing-function: ease;         /* slow start and end (default) */
transition-timing-function: linear;       /* constant speed */
transition-timing-function: ease-in;      /* slow start */
transition-timing-function: ease-out;     /* slow end */
transition-timing-function: ease-in-out;  /* slow start and end */
transition-timing-function: cubic-bezier(0.4, 0, 0.2, 1); /* custom curve */
transition-timing-function: steps(4, end); /* stepped (frame-by-frame) */
```

--- 

## Animations 

Animations let you define **keyframes** — multiple intermediate states — giving more control than transitions.

### Defining Keyframes

```css
@keyframes fade-in {
  from { opacity: 0; transform: translateY(16px); }
  to   { opacity: 1; transform: translateY(0); }
}

@keyframes pulse {
  0%, 100% { transform: scale(1); }
  50%       { transform: scale(1.05); }
}

@keyframes spin {
  from { transform: rotate(0deg); }
  to   { transform: rotate(360deg); }
}
```

### Applying Animations

```css
.card {
  /* Shorthand: name duration timing-function delay iteration-count direction fill-mode */
  animation: fade-in 0.4s ease-out 0s 1 normal forwards;

  /* Longhand */
  animation-name:            fade-in;
  animation-duration:        0.4s;
  animation-timing-function: ease-out;
  animation-delay:           0.1s;
  animation-iteration-count: 1;          /* number | infinite */
  animation-direction:       normal;     /* normal | reverse | alternate | alternate-reverse */
  animation-fill-mode:       forwards;   /* none | forwards | backwards | both */
  animation-play-state:      running;    /* running | paused */
}

/* Infinite spinner */
.spinner {
  animation: spin 1s linear infinite;
}

/* Pause on hover */
.spinner:hover {
  animation-play-state: paused;
}
```

### Reduced Motion

Always respect users who prefer less motion:

```css
@media (prefers-reduced-motion: reduce) {
  *, *::before, *::after {
    animation-duration:   0.01ms !important;
    animation-iteration-count: 1 !important;
    transition-duration:  0.01ms !important;
  }
}
```

--- 

## Best Practices

- Use **`box-sizing: border-box`** globally — it makes sizing predictable.
- Prefer **`rem`** for font sizes so users can scale via browser settings.
- Use **CSS custom properties** (`--var`) for colors, spacing, and typography tokens.
- Keep **specificity low and flat** — avoid IDs in selectors; use classes.
- Use **`transition`** on the base state (not just `:hover`) so the animation plays both ways.
- Always include a **`font-family` fallback stack** — never rely on a single font.
- Wrap all animations in a **`prefers-reduced-motion`** media query.
- Avoid `!important` — it breaks the cascade and makes debugging hard.
- Separate **layout** (Flexbox/Grid), **spacing** (padding/margin), and **decoration** (color/typography) concerns into distinct rules.
- Use **logical properties** (`margin-inline`, `padding-block`) for better internationalisation support.
- Validate with browser DevTools and test across browsers.

--- 

## Libraries

Common CSS frameworks and utility libraries:

| Library | Type | Description |
|---------|------|-------------|
| **Tailwind CSS** | Utility-first | Compose styles with low-level utility classes directly in HTML |
| **Bootstrap** | Component | Pre-built UI components with a grid system |
| **Bulma** | Component | Flexbox-based, no JavaScript dependency |
| **Sass / SCSS** | Preprocessor | Adds variables, nesting, mixins, and functions to CSS |
| **PostCSS** | Preprocessor | Transforms CSS with plugins (autoprefixer, nesting, etc.) |
| **CSS Modules** | Scoping | Locally-scoped class names — used with React, Vue, etc. |
| **Styled Components** | CSS-in-JS | Write CSS inside JavaScript/TypeScript component files |
| **Open Props** | Design tokens | CSS custom property design system |
| **Normalize.css** | Reset | Consistent cross-browser baseline styles |

### Sass / SCSS Quick Reference

```scss
// Variables
$color-primary: #3b82f6;
$spacing-base: 16px;

// Nesting
.card {
  padding: $spacing-base;

  &:hover { box-shadow: 0 4px 12px rgba(0,0,0,0.1); }

  &__title { font-size: 1.25rem; }   // BEM modifier
  &--featured { border: 2px solid $color-primary; }
}

// Mixin
@mixin flex-center {
  display: flex;
  justify-content: center;
  align-items: center;
}

.hero {
  @include flex-center;
  height: 100vh;
}
```

--- 

## Frequently Asked Questions

### Centering a div

There are several ways to center a div both horizontally and vertically, but it is 
mostly done using Flexbox or Grid. Here are some examples:

- **Flexbox**

```css
.centered {
  display: flex;
  justify-content: center; /* horizontal */
  align-items: center;     /* vertical */
  height: 100vh;           /* full viewport height */
}
```

- **Grid**

```css
.centered {
  display: grid;
  place-items: center;     /* shorthand for justify-items + align-items */
  height: 100vh;
}
```

- **Classic absolute positioning**

```css
.centered {
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%); /* offset by half of its own size */
}
```

### Eliminating the margin and padding of the body

This is for our boxes inside the body to take up the full width and height of the viewport. 
It is a common practice to reset the default margin and padding of the body element to ensure 
consistent layout across different browsers.

```css
body {
  margin: 0;
  padding: 0;
}
```

### Image Carousel / Slider

This one is a common UI pattern for displaying multiple images in a slideshow format.

### Automatic Image Carousel with CSS and HTML 


```html
<div id="main_flex_container">
    <img src="../resources/slideshow/main_site_bg.jpg" class="slide slide1">
    <img src="../resources/slideshow/city.jpg"         class="slide slide2">
    <img src="../resources/slideshow/pink_eyes.jpg"  class="slide slide3">

    <h1 id="main_title">AnimeMigUX</h1>
</div>
```

```css 
#main_flex_container {

    border: none;
    padding: none;

    position: relative; /* Position the container relative to its normal position */
    overflow: hidden;

    height: 45rem;
    display: flex;

    flex-direction: row;
    justify-content: center;
    align-items: flex-end;
}

.slide {
    position: absolute; /* Position slides on top of each other */
    z-index: 0;         /* Ensure slides are behind the title */

    top: 0;  /* Position slides at the top of the container */
    left: 0; /* Position slides at the left of the container */

    width: 100%;  /* Make slides take full width of the container */
    height: 100%; /* Make slides take full height of the container */

    animation: slideshow 15s infinite;
}

/* Each slide will have a different animation delay to create the slideshow effect */
.slide1 {
    animation-delay: 0s;
}

.slide2 {
    animation-delay: 5s;
}

.slide3 {
    animation-delay: 10s;
}

/* Keyframes for the slideshow animation using a sliding window effect */
@keyframes slideshow {
    0% {
        opacity: 0;
    }

    8% {
        opacity: 1;
    }

    30% {
        opacity: 1;
    }

    38% {
        opacity: 0;
    }

    100% {
        opacity: 0;
    }    
}

```

### Side Navigation Bar

```html 
    <header id="main_header">
        <nav id="nav">

            <!-- The first list is for the side bar -->
            <ul class="sidebar">
               <li onclick=hideSideBar()><img id="close_burgir" src="../resources/icons/close_24dp_1F1F1F_FILL0_wght400_GRAD0_opsz24.svg"></li> 
               <li><a href="#">Blog</a></li> 
               <li><a href="#">Forum</a></li> 
               <li><a href="#">Forum</a></li> 
               <li><a href="#">About</a></li> 
            </ul>

            <!-- Acutal list for the header-->
            <ul class="topbar">
               <li><a href="./index.html">AnimeMigUX</a></li> 
               <li class="hideOnMobile"><a href="#">Blog</a></li> 
               <li class="hideOnMobile"><a href="#">Forum</a></li> 
               <li class="hideOnMobile"><a href="#">Forum</a></li> 
               <li class="hideOnMobile"><a href="#">About</a></li> 
               <li id="menu-button" onclick=showSidebar()><img id="burgir_menu" src="../resources/icons/menu_24dp_1F1F1F_FILL0_wght400_GRAD0_opsz24.svg"></li>
            </ul>
        </nav>
    </header>
```

```css 
* {
    color: white;
    font-family: 'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif;
    box-sizing: border-box;
    margin: 0;
    padding:0;
}

body { 
    margin: 0;
    padding:0;
    min-height: 100vh;
}

#nav {
    background-color: white;
    box-shadow: 3px 3px 3px rgba(0, 0, 0, 0.1);
}

.topbar {
    width: 100%;
    list-style: none;
    display: flex;
    justify-content: flex-end;
    align-items: center;
}

#nav li {
    height: 50px;
}

#nav a {
    height: 100%;
    padding: 0 30px;
    display: flex;
    align-items: center;
    color: black;
}

#nav a:hover {
    background-color: #f0f0f0;
}

#nav li:first-child {
    margin-right: auto;
}

#burgin_menu {
    height: 26px; 
    width: 26px;
}

#close_burgir {
    height: 26px; 
    width: 26px;
}

.sidebar {

    list-style: none;
    position: fixed;
    top: 0;
    right: 0;
    width: 250px; 
    height: 100vh; 
    z-index: 999;
    background-color: rgba(255, 255, 255, 0.2);
    backdrop-filter: blur(10px);
    box-shadow: -10px 0 10px rgba(0, 0, 0, 0.1);

    display: none;
    flex-direction: column;
    align-items: flex-start;
    justify-content: flex-start;
}

.sidebar li {
    width: 100%;
}
.sidebar a {
    width: 100%;
}

#menu-button {
    display: none;
}

@media(max-width: 800px) {
    .hideOnMobile {
        display: none;
    }
    #menu-button {
        display: block;
    }
}
```


### Centering An Image in a Div

```html
<div class="image-container">
    <img src="image.jpg" alt="Centered Image">
</div>
```

```css
.image-container {
  display: bloc; 
  margin-left: auto;
  margin-right: auto;
  width: 50%; /* Adjust the width as needed */
}
``` 

### Button With Gradient Border And Glow Effect

```html 
<button id="goto_main_bttn">Go to Main</button>
```

```css 
#goto_main_bttn {
    font-size: 2rem;
    font-weight: bold;
    text-align: center;

    padding: 10px;

    height: 70px;
    width: 400px;
    margin: 5px;
    
    border:none;

    border-radius: 1000px;

    background-color: black;
    
    border-top: 1px solid rgba(255, 255, 255, 0.4);
    position: relative;

    display: flex;
    justify-content: center;
    align-items: center;

}

#goto_main_bttn::after {
    content: '';
    position: absolute;
    background-image: linear-gradient(to bottom right, #008cff, #e100ff);
    z-index: -1;
    height: 108%;
    width: 103%;
    border-radius: 1000px;
}

#goto_main_bttn:hover {
    z-index: 0;
    box-shadow: 40px 0 100px #008cff, -40px 0 100px #008cff;
}

#note_and_art_container {
    display: flex;
    align-items: center;
}
```
