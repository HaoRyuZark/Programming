# LaTeX

Quick reference for latex. 

--- 

## Files

- `.tex`: source code.
- `.dvi`: output.
- `.log`: protocol of the compilation.
- `.aux`: auxiliary file for the compilation process, used for referencing and linking among others.
- `.toc`: table of contents.
- `.lof`: list of figures.
- `.lot`: list of tables.
- `.bib`: used for the literature references.
- `.bbl`: output of bibtex.
- `.blg`: protol for bibtex.

---

## Command Structure 

The optional parameters are mostly used for configuration. While the other if not present lead to errors.


| Command Class     | Description                                             |
| --------- | ------------------------------------------------------- |
| `\command` | No parameters |
| `\command{P1}`  | One parameter           |
| `\command{P1}{P2}`    | Two parameters          |
| `\command[P1]`  | One optional parameter                                    |
| `\command[P1]{P2}`  | One optional parameter and one obligatory parameter                                              |
| `\command(P1, P2)`  | Two parameter but in braket notation           |


--- 

## Spacing 

- `\,`: small space in math mode.
- `\`: space between words.
- ` `: normal space in text mode 
- `~`: space in between words but not for new lines. 
- `\@`: space at the end of a sentence.
- `.lof`: list of figures.
- `\/`: exta spacing for italics.
- `//`: new line.

--- 

## Document Class

The **document class** defines the overall structure, layout rules, and default behavior of a LaTeX document. It determines features such as section hierarchy, page layout, title formatting, and availability of chapters.

Basic syntax:

```latex
\documentclass[options]{class}
````

### Common Document Classes


| Class     | Description                                             |
| --------- | ------------------------------------------------------- |
| `article` | Short documents such as papers, reports, research notes |
| `report`  | Longer documents with chapters (e.g., theses)           |
| `book`    | Large structured works with parts and chapters          |
| `beamer`  | Presentations/slides                                    |
| `letter`  | Letters                                                 |
| `memoir`  | Flexible class combining book/report features           |


Example:

```latex
\documentclass[12pt,a4paper]{article}
```

### Common Options

**Font size**

| Option | Size        |
| ------ | ----------- |
| `10pt` | Default     |
| `11pt` | Medium      |
| `12pt` | Larger text |

Example:

```latex
\documentclass[11pt]{article}
```


**Paper size**


| Option        | Paper               |
| ------------- | ------------------- |
| `a4paper`     | A4 (Europe default) |
| `letterpaper` | US Letter           |
| `legalpaper`  | Legal size          |
| `a5paper`     | A5                  |


Example:

```latex
\documentclass[a4paper]{report}
```


**Page layout**


| Option      | Description                                  |
| ----------- | -------------------------------------------- |
| `twocolumn` | Two-column layout                            |
| `onecolumn` | Single column                                |
| `twoside`   | Different margins for odd/even pages (books) |
| `oneside`   | Same margins on all pages                    |
| `openright` | Chapters start on right pages                |
| `openany`   | Chapters start anywhere                      |


Example:

```latex
\documentclass[twocolumn]{article}
```


**Title page**


| Option        | Description                        |
| ------------- | ---------------------------------- |
| `titlepage`   | Creates a dedicated title page     |
| `notitlepage` | Title appears at top of first page |


**Draft mode**


| Option  | Description                           |
| ------- | ------------------------------------- |
| `draft` | Shows overfull boxes, disables images |
| `final` | Normal compilation                    |


Example:

```latex
\documentclass[draft]{article}
```

## Document Formatting

Document formatting defines the **structure and layout of the content** within the document.

### Section Hierarchy

LaTeX automatically numbers sections and organizes them into a hierarchy.

```latex
\section{Section}
\subsection{Subsection}
\subsubsection{Subsubsection}
\paragraph{Paragraph}
\subparagraph{Subparagraph}
```

Hierarchy (highest -> lowest):

1. `\part`
2. `\chapter` (only in `book` and `report`)
3. `\section`
4. `\subsection`
5. `\subsubsection`
6. `\paragraph`
7. `\subparagraph`

Unnumbered sections:

```latex
\section*{Introduction}
```

### Table of Contents

Automatically generated from section headings.

```latex
\tableofcontents
```

Depth can be controlled:

```latex
\setcounter{tocdepth}{2}
```

### Page Layout and Margins

Margins and page layout are typically controlled with the `geometry` package.

Example:

```latex
\usepackage[a4paper, margin=1in]{geometry}
```

Common parameters:

| Option   | Description      |
| -------- | ---------------- |
| `margin` | Sets all margins |
| `top`    | Top margin       |
| `bottom` | Bottom margin    |
| `left`   | Left margin      |
| `right`  | Right margin     |

Example:

```latex
\usepackage[top=2cm,bottom=2cm,left=2.5cm,right=2.5cm]{geometry}
```

### Paragraph Formatting

Paragraph indentation and spacing can be controlled.

Disable indentation:

```latex
\setlength{\parindent}{0pt}
```

Add spacing between paragraphs:

```latex
\setlength{\parskip}{6pt}
```

### Line Spacing

Line spacing can be modified with the `setspace` package.

```latex
\usepackage{setspace}
```

Examples:

```latex
\singlespacing
\onehalfspacing
\doublespacing
```

### Page Numbering

Page numbering style can be changed.

```latex
\pagenumbering{arabic}
```

Available styles:

| Style    | Example    |
| -------- | ---------- |
| `arabic` | 1, 2, 3    |
| `roman`  | i, ii, iii |
| `Roman`  | I, II, III |
| `alph`   | a, b, c    |
| `Alph`   | A, B, C    |


### Columns

Documents can use multiple columns.

```latex
\twocolumn
```

or temporarily:

```latex
\begin{multicols}{2}
Text
\end{multicols}
```

(using the `multicol` package)

### Minipage

The **`minipage` environment** creates a small page-like block inside a document. It allows content (text, images, tables, etc.) to be placed in a 
**fixed-width container**, which is especially useful for placing elements **side-by-side**.

Unlike floating environments (`figure`, `table`), `minipage` content **stays exactly where it is written**.

Basic syntax:

```latex
\begin{minipage}[alignment]{width}
content
\end{minipage}
````

Parameters:


| Parameter   | Description                                                                          |
| ----------- | ------------------------------------------------------------------------------------ |
| `alignment` | Vertical alignment relative to surrounding content (`t` top, `c` center, `b` bottom) |
| `width`     | Width of the minipage (e.g., `0.5\textwidth`, `5cm`)                                 |


Example: Two images side by side

```latex
\begin{minipage}{0.45\textwidth}
\centering
\includegraphics[width=\linewidth]{image1.png}
\captionof{figure}{First image}
\end{minipage}
\hfill
\begin{minipage}{0.45\textwidth}
\centering
\includegraphics[width=\linewidth]{image2.png}
\captionof{figure}{Second image}
\end{minipage}
```

Example: Text and image side-by-side

```latex
\begin{minipage}{0.6\textwidth}
This is explanatory text describing the image shown on the right.
\end{minipage}
\hfill
\begin{minipage}{0.35\textwidth}
\includegraphics[width=\linewidth]{example.png}
\end{minipage}
```

### Page Breaks and Layout Control

Force page break:

```latex
\newpage
```

Suggest page break:

```latex
\pagebreak
```

Prevent page break:

```latex
\nopagebreak
```

Column break:

```latex
\columnbreak
```

## Fonts

Fonts in LaTeX can be changed globally or locally. LaTeX provides commands for font families, shapes, and sizes.

Examples:

```latex
\texttt{monospace}
\textsf{sans-serif}
\textrm{roman}
```

Font size commands:

```latex
\tiny
\small
\normalsize
\large
\Large
\huge
```

With packages like `fontspec` (XeLaTeX/LuaLaTeX), system fonts can be used.

## Title

LaTeX provides built-in commands to define a document title, author, and date.

Example:

```latex
\title{My Research Document}
\author{John Doe}
\date{\today}

\begin{document}
\maketitle
```

`\maketitle` renders the title block in the document.

## Geometry Package (Page Layout and Margins)

The **`geometry` package** is the standard tool in LaTeX for configuring **page layout**, including margins, paper size, text area, 
header/footer spacing, and page orientation. It provides a simple interface for controlling the printable area without manually adjusting low-level 
layout parameters.

Basic usage:

```latex
\usepackage{geometry}
````

A full configuration can be specified directly when loading the package:

```latex
\usepackage[a4paper, margin=2.5cm]{geometry}
```

This automatically sets all page margins to **2.5 cm** on A4 paper.

### Core Concept: Page Layout Model

LaTeX page layout consists of several regions:

```
+----------------------------------+
|              Top Margin          |
|   +--------------------------+   |
|   |        Header            |   |
|   +--------------------------+   |
|   |                          |   |
|   |        Text Body         |   |
|   |                          |   |
|   +--------------------------+   |
|            Footer                |
|           Bottom Margin          |
+----------------------------------+
```

The `geometry` package allows direct control over these components.

### Basic Margin Configuration

The most common use is setting margins.

Set all margins:

```latex
\usepackage[margin=1in]{geometry}
```

Set vertical and horizontal margins separately:

```latex
\usepackage[hmargin=2.5cm, vmargin=2cm]{geometry}
```

Individual margin control:

```latex
\usepackage{
    top=2cm,
    bottom=2cm,
    left=3cm,
    right=3cm
}{geometry}
```

### Paper Size

`geometry` supports many predefined paper formats.

Common options:

| Option        | Description  |
| ------------- | ------------ |
| `a4paper`     | A4 paper     |
| `letterpaper` | US Letter    |
| `legalpaper`  | Legal format |
| `a5paper`     | A5           |
| `b5paper`     | B5           |


Example:

```latex
\usepackage[a4paper]{geometry}
```

Custom paper size:

```latex
\usepackage[
    paperwidth=210mm,
    paperheight=297mm
]{geometry}
```

### Text Area Size

Instead of specifying margins, you can define the **text area directly**.

Example:

```latex
\usepackage[
    textwidth=16cm,
    textheight=24cm
]{geometry}
```

LaTeX will automatically compute the margins needed.

### Header and Footer Spacing

Control space allocated to headers and footers.


| Parameter    | Description                       |
| ------------ | --------------------------------- |
| `headheight` | Height of header                  |
| `headsep`    | Space between header and text     |
| `footskip`   | Distance from text body to footer |


Example:

```latex
\usepackage[
    headheight=15pt,
    headsep=10pt,
    footskip=20pt
]{geometry}
```

This is often required when using packages like `fancyhdr`.

### Include Header and Footer in Margin Calculations

By default, margins only refer to the **text body**. The following options include headers/footers in the margin computation.


| Option            | Meaning                      |
| ----------------- | ---------------------------- |
| `includehead`     | Header included in text area |
| `includefoot`     | Footer included in text area |
| `includeheadfoot` | Include both                 |


Example:

```latex
\usepackage[
    margin=2.5cm,
    includeheadfoot
]{geometry}
```

### Binding Offset (Books and Theses)

When printing double-sided documents, extra space may be needed near the binding.

Example:

```latex
\usepackage[
    inner=3cm,
    outer=2cm,
    bindingoffset=1cm
]{geometry}
```

Useful for:

* printed theses
* books
* double-sided reports


### Two-Sided Documents

For documents with mirrored margins:

```latex
\usepackage[
    inner=3cm,
    outer=2cm
]{geometry}
```

Terminology:


| Term    | Meaning             |
| ------- | ------------------- |
| `inner` | Margin near binding |
| `outer` | Outer page margin   |


Works best with:

```latex
\documentclass[twoside]{book}
```

### Landscape Orientation

Pages can be rotated to landscape format.

```latex
\usepackage[landscape]{geometry}
```

Alternatively for specific pages (using other packages):

```latex
\usepackage{pdflscape}
```

### Changing Layout Inside the Document

Geometry settings can also be changed mid-document.

Example:

```latex
\newgeometry{margin=1.5cm}
```

Restore original settings:

```latex
\restoregeometry
```

Useful for:

* large tables
* figures
* appendices
* title pages

### Debugging Layout

The `showframe` option draws visible layout guides.

```latex
\usepackage[showframe]{geometry}
```

This displays:

* margin boundaries
* header area
* footer area
* text body limits

Helpful when adjusting layout precisely.

### Typical Layout Configurations

**Academic paper**

```latex
\usepackage[
    a4paper,
    margin=2.5cm
]{geometry}
```

**Thesis layout**

```latex
\usepackage[
    a4paper,
    inner=3.5cm,
    outer=2.5cm,
    top=3cm,
    bottom=3cm
]{geometry}
```

**Compact notes**

```latex
\usepackage[
    margin=1.5cm
]{geometry}
```

### Best Practices

* Prefer **`margin`** for simple layouts.
* Use **`inner` / `outer`** for printed or double-sided documents.
* Use **`bindingoffset`** for theses and books.
* Use **`showframe`** when debugging layout issues.
* Keep margins **≥ 2–2.5 cm** for readability and printing.

The `geometry` package greatly simplifies page layout control and is recommended for **nearly all LaTeX documents**, especially academic papers, reports, and theses.

```
```
## Headers

Headers and footers are typically controlled using the `fancyhdr` package.

Example:

```latex
\usepackage{fancyhdr}
\pagestyle{fancy}

\fancyhead[L]{Research Notes}
\fancyhead[R]{\thepage}
```

Common elements:

* Left / center / right header
* Left / center / right footer
* Page numbers

## Packages

Packages extend LaTeX with additional functionality. They are loaded in the preamble using `\usepackage`.

```latex 
\usepackage{graphicx}
\usepackage{amsmath, amssymb, amsthm}
\usepackage{bbm}
\usepackage{mathrsfs}
\usepackage{geometry}
\usepackage{enumitem}
\usepackage{tikz, tcolorbox}
\usepackage{hyperref}
\usepackage{booktabs}
\usepackage{fullpage}
\usepackage{pgfplots}
\usepackage{multicol}
\usepackage[siunitx]{circuitikz}
\usepackage{caption}
\usepackage{float}
\usepackage{multirow}
\usepackage{polynom}
\usepackage{tikz-cd}
\usepackage[utf8]{inputenc}
\usepackage{pst-eucl}
\usepackage{tabu}
\usepackage{comment}
\usepackage{subcaption}
\usepackage{fancyvrb}
\usepackage{fancyhdr}
\usepackage{etoolbox}
\usepackage{fncychap}
\usepackage{setspace}
\usepackage{listings}
\usepackage{tkz-euclide}
\usepackage{parskip}
\usepackage{bookmark}
```

## Text Formatting

Text formatting commands modify the appearance of text.

Examples:

```latex
\textbf{Bold text}
\emph{Fancy text}
\textit{Italic text}
\underline{Underlined text}
\textsc{Small Caps}
```

Formatting can also be applied using declarations:

```latex
{\bfseries Bold text}
```

## Line Breaks

Different commands control line and paragraph breaks.

Examples:

```latex
\\        % line break
\newline  % line break
```

Paragraph break:

```
(empty line in source)
```

Page break:

```latex
\newpage
```


## Inline Math

Inline math allows mathematical expressions to appear within a line of text.

```latex 
Hello \(\sin(x)\)
```

## Block Math

Displayed math is centered and separated from the main text.

```latex 
\[
  \iiint_{R} x dx
\]
```

### Spacing Inside Math Environments

LaTeX automatically inserts spacing between mathematical elements, but manual spacing can be added when finer control is needed. This is useful for improving readability in complex formulas.

Common spacing commands (from smallest to largest):

| Command | Description |
|--------|-------------|
| `\!` | Negative thin space |
| `\,` | Thin space |
| `\:` | Medium space |
| `\;` | Thick space |
| `\quad` | Large space |
| `\qquad` | Extra large space |
| `\hfill` | Evenspacing filling |


Example:

```latex
a\,b \quad a\;b \qquad a\:b
````

These commands are especially useful in **block math environments** like `equation`, `align`, or `gather` when separating terms or improving visual structure.

Example in block math:

```latex
\begin{equation}
f(x) = a x^2 \;+\; b x \;+\; c
\end{equation}
```

For automatic spacing around operators, LaTeX usually handles this correctly when standard operators (`+`, `-`, `=`, `\times`, etc.) are used.

```
```

## Math Functions, Parentheses, Subscripts, Superscripts, Sets

LaTeX provides many commands for mathematical notation.

Common math functions:

```latex
\sin
\cos
\tan
\log
\ln
\exp
\sqrt{x}
\frac{a}{b}
```

Subscripts and superscripts:

```latex
x_i
x^2
x_{i+1}
```

Parentheses that scale automatically:

```latex
\left( \frac{a}{b} \right)
```

Sets and common symbols:

```latex
\in
\subset
\subseteq
\cup
\cap
\forall
\exists
\emptyset
```

Number sets (from `amsfonts` or `amssymb`):

```latex
\mathbb{N}
\mathbb{Z}
\mathbb{Q}
\mathbb{R}
\mathbb{C}
```

## Tables (Different Variants)

Tables in LaTeX are typically created using the **`tabular` environment**, which defines column alignment and structure. Tables are often wrapped inside a 
**`table` environment** to allow captions, labels, and floating placement.

Basic structure:

```latex
\begin{tabular}{column specification}
cell1 & cell2 & cell3 \\ 
cell4 & cell5 & cell6 \\
\end{tabular}
````

Key symbols:

| Symbol   | Meaning              |                               |
| -------- | -------------------- | ----------------------------- |
| `&`      | Separates columns    |                               |
| `\\`     | Ends the current row |                               |
| `\hline` | Horizontal line      |                               |
| `        | `                    | Vertical line between columns |


### Column Alignment

The column layout is defined in the argument of `tabular`.


| Column Specifier | Meaning                                         |                    |
| ---------------- | ----------------------------------------------- | ------------------ |
| `l`              | Left aligned column                             |                    |
| `c`              | Center aligned column                           |                    |
| `r`              | Right aligned column                            |                    |
| `                | `                                               | Vertical separator |
| `p{width}`       | Fixed-width column with automatic line wrapping |                    |


Example:

```latex
\begin{tabular}{lcr}
Left & Center & Right \\
A & B & C \\
\end{tabular}
```

With borders:

```latex
\begin{tabular}{|l|c|r|}
\hline
Left & Center & Right \\
\hline
1 & 2 & 3 \\
\hline
\end{tabular}
```

### Horizontal and Vertical Lines

LaTeX allows several ways to draw lines in tables.

#### Horizontal lines

```latex
\hline
```

Example:

```latex
\begin{tabular}{|c|c|}
\hline
A & B \\
\hline
1 & 2 \\
\hline
\end{tabular}
```

#### Partial horizontal lines

```latex
\cline{start-end}
```

Example:

```latex
\begin{tabular}{|c|c|c|}
\hline
A & B & C \\
\cline{2-3}
1 & 2 & 3 \\
\hline
\end{tabular}
```

This draws a line only across selected columns.

### Table Environment

The `table` environment allows LaTeX to automatically place tables and enables captions and referencing.

Example:

```latex
\begin{table}
\centering
\begin{tabular}{cc}
A & B \\
1 & 2 \\
\end{tabular}
\caption{Example Table}
\label{tab:example}
\end{table}
```

Common placement options:

| Option | Meaning                     |
| ------ | --------------------------- |
| `h`    | Place table here            |
| `t`    | Top of page                 |
| `b`    | Bottom of page              |
| `p`    | Separate float page         |
| `!`    | Override LaTeX restrictions |


Example:

```latex
\begin{table}[ht]
```

Referencing a table:

```latex
Table~\ref{tab:example}
```

### Fixed Width Columns

Columns with a fixed width allow text wrapping.

Example:

```latex
\begin{tabular}{|p{4cm}|p{4cm}|}
\hline
Long text automatically wraps inside the column &
Another long text entry \\
\hline
\end{tabular}
```

Useful for tables containing paragraphs or descriptions.

### Table Alignment

Tables are typically centered using:

```latex
\centering
```

or

```latex
\begin{center}
...
\end{center}
```

Inside the `table` environment, `\centering` is preferred.

### Multi-Column Cells

Cells can span multiple columns.

Syntax:

```latex
\multicolumn{num_cols}{alignment}{content}
```

Example:

```latex
\begin{tabular}{|c|c|c|}
\hline
\multicolumn{3}{|c|}{Combined Header} \\
\hline
A & B & C \\
\hline
\end{tabular}
```

### Multi-Row Cells

Rows can span multiple rows using the `multirow` package.

Example:

```latex
\usepackage{multirow}
```

```latex
\begin{tabular}{|c|c|}
\hline
\multirow{2}{*}{A} & B \\
 & C \\
\hline
\end{tabular}
```

### Long Tables (Multi-Page)

For tables that span multiple pages use `longtable`.

```latex
\usepackage{longtable}
```

Example:

```latex
\begin{longtable}{|c|c|}
\hline
A & B \\
\hline
\endfirsthead
\hline
A & B \\
\hline
\endhead
1 & 2 \\
3 & 4 \\
\hline
\end{longtable}
```

### Automatically Sized Tables

`tabularx` allows tables to automatically stretch to the text width.

```latex
\usepackage{tabularx}
```

Example:

```latex
\begin{tabularx}{\textwidth}{|X|X|}
\hline
Column 1 & Column 2 \\
\hline
Long text automatically expands &
Another long entry \\
\hline
\end{tabularx}
```

`X` columns expand to fill available space.

### Professional Table

For high-quality tables (often used in research papers), the `booktabs` package provides better line commands.

```latex
\usepackage{booktabs}
```

Commands:

| Command       | Meaning     |
| ------------- | ----------- |
| `\toprule`    | Top line    |
| `\midrule`    | Middle line |
| `\bottomrule` | Bottom line |

Example:

```latex
\begin{tabular}{ccc}
\toprule
A & B & C \\
\midrule
1 & 2 & 3 \\
4 & 5 & 6 \\
\bottomrule
\end{tabular}
```

These produce visually cleaner tables than repeated `\hline`.

### Colors 

All elements in a table can be customized to use a specific colour. Again, this functionality is provided by xcolor so you must add
`\usepackage[table]{xcolor}`

Below is a description about how to change the colour of each element in the table:

- **Colour of the lines**: The command `\arrayrulecolor` is used for this. In the example an HTML format is used, but other formats are 
available too.

- **Background colour of a cell**: Use the command `\cellcolor`. You can either enter the name directly inside the braces (red, gray, green and so on) 
or pass a format parameter inside brackets (HTML in the example) and then set the desired colour inside the braces using the established format.

- **Background colour of a row**: In this case \rowcolor will accomplish that. The same observations about colour selection mentioned in the two previous 
commands are valid for this one.

- **Background colour of a column** This one is a bit tricky, but the easiest way is to define a new column type. The command

`\newcolumntype{s}{>{\columncolor[HTML]{AAACED}} p{3cm}}`

define a column type called s whose alignment is p, the column width is 3cm and the colour is set with HTML format to AAACED. This new column type is used 
in the tabular environment.

Example: 

```latex 
\documentclass{article}
\usepackage[table]{xcolor}

\setlength{\arrayrulewidth}{1mm}
\setlength{\tabcolsep}{18pt}

\renewcommand{\arraystretch}{2.5}
\newcolumntype{s}{>{\columncolor[HTML]{AAACED}} p{3cm}}
\arrayrulecolor[HTML]{DB5800}

\begin{document}

\begin{tabular}{ |s|p{3cm}|p{3cm}| }
\hline
\rowcolor{lightgray} \multicolumn{3}{|c|}{Country List} \\
\hline
Country Name or Area Name& ISO ALPHA 2 Code &ISO ALPHA 3 \\
\hline
Afghanistan & AF &AFG \\
\rowcolor{gray}
Aland Islands & AX & ALA \\
Albania   &AL & ALB \\
Algeria  &DZ & DZA \\
American Samoa & AS & ASM \\
Andorra & AD & \cellcolor[HTML]{AA0044} AND    \\
Angola & AO & AGO \\
\hline
\end{tabular}

\end{document}
```
### Table Best Practices

Common recommendations:

* Prefer `booktabs` over excessive `\hline`
* Avoid too many vertical lines
* Align numbers using `r`
* Use fixed-width columns (`p{}`) for text-heavy tables
* Use captions and labels for referencing

```
```

## Environments: align, equation, enumerate, itemize

LaTeX environments define structured blocks.

Lists:

```latex
\begin{itemize}
\item First
\item Second
\end{itemize}
```

Numbered lists:

```latex
\begin{enumerate}
\item Step one
\item Step two
\end{enumerate}
```

Math environments:

```latex
\begin{equation}
E = mc^2
\end{equation}
```

## Custom Commands and Environments

Custom macros allow reuse of frequently used expressions.

New command:

```latex
\newcommand{\R}{\mathbb{R}}
```

Usage:

```latex
x \in \R
```

Custom environments:

```latex
\newenvironment{important}
{\begin{center}\bfseries}
{\end{center}}
```

These help maintain consistent formatting and simplify large documents.

## Definition, Theorem, Proof

LaTeX provides functionality for this kinds of mathematical environments via the package `asmthr`

```latex 
% Put in the preamble
\newtheorem{theorem}{Theorem}[section]
\newtheorem{corollary}{Corollary}[section]

% Use 
\begin{theorem}[Title]

\end{theorem}

% Corollaries
\begin{corollary}[Title]

\end{corollary}

% Proofs
\begin{proof}

\end{proof}
```

## Images

Images are typically included with the `graphicx` package.

Example:

```latex
\usepackage{graphicx}

\includegraphics[width=0.5\textwidth]{image.png}
```

Common options:

* `width`
* `height`
* `scale`
* `angle`

## Vectors, Matrices, Arrays

Vectors and matrices are represented using specialized environments.

Vector example:

```latex
\vec{v}
```

Matrix:

```latex
\begin{bmatrix}
1 & 2 \\
3 & 4
\end{bmatrix}
```

Array environment:

```latex
\begin{array}{cc}
a & b \\
c & d
\end{array}
```

Common matrix environments (from `amsmath`):

* `matrix`
* `pmatrix`
* `bmatrix`
* `vmatrix`

--- 

## Figures

Figures allow images to be placed with captions and references.

Example:

```latex
\begin{figure}
\includegraphics{image.png}
\caption{Example figure}
\label{fig:example}
\end{figure}
```

Figures can be referenced elsewhere:

```latex
Figure~\ref{fig:example}
```

## Centering

Content can be centered using environments or commands.

Environment:

```latex
\begin{center}
Centered text
\end{center}
```

For figures and tables:

```latex
\centering
```

This is commonly placed inside `figure` or `table`.

## Including Code Blocks

LaTeX provides several ways to include **source code or verbatim text** inside a document. Code environments preserve formatting, 
spacing, and special characters that would normally be interpreted by LaTeX.

### Verbatim Environment

The simplest way to display code is the **`verbatim` environment**, which prints text exactly as written.

Example:

```latex
\begin{verbatim}
for i in range(10):
    print(i)
\end{verbatim}
````

Characteristics:

* Preserves spaces and indentation
* Displays special characters (`# $ % _ { }`) without escaping
* No syntax highlighting

Inline verbatim text can be written using:

```latex
\verb|print("Hello World")|
```

The delimiter (`|` here) can be replaced with another character if needed.

### Fancy Verbatim

Vie the `fancyvrb` package we can not especify frames, color and other parameters of our Verbatim environments. Note the capital.

```latex 
\begin{Verbatim}[numbers=left, framed=single]
  \begin{center}
    for i in range(10):
        print(i)
  \end{center}
\end{Verbatim}
```

### Listings Package (Recommended for Code)

The **`listings` package** provides a powerful environment for displaying source code with formatting options and optional syntax highlighting.

Load the package:

```latex
\usepackage{listings}
```

Basic example:

```latex
\begin{lstlisting}
def hello():
    print("Hello World")
\end{lstlisting}
```

### Specifying Programming Languages

`listings` supports many languages such as Python, C, Java, and Bash.

Example:

```latex
\begin{lstlisting}[language=Python]
def square(x):
    return x*x
\end{lstlisting}
```

This enables language-specific formatting.

### Adding Captions and Labels

Code blocks can be referenced similarly to figures or tables.

Example:

```latex
\begin{lstlisting}[language=Python, caption={Example Python Code}, label={lst:python}]
def add(a, b):
    return a + b
\end{lstlisting}
```

Referencing:

```latex
Listing~\ref{lst:python}
```

### Displaying External Source Files

Entire files can be included directly.

Example:

```latex
\lstinputlisting[language=Python]{script.py}
```

This inserts the contents of `script.py` into the document.

### Basic Formatting Options

Common configuration options:

| Option       | Description                            |
| ------------ | -------------------------------------- |
| `language`   | Programming language                   |
| `caption`    | Caption for the code block             |
| `label`      | Reference label                        |
| `numbers`    | Line numbers (`left`, `right`, `none`) |
| `frame`      | Border around code (`single`, `lines`) |
| `basicstyle` | Font style                             |


Example:

```latex
\begin{lstlisting}[
language=Python,
numbers=left,
frame=single
]
def example():
    return 42
\end{lstlisting}
```

### Global Configuration

Default settings can be defined using `\lstset`.

Example:

```latex
\lstset{
    language=Python,
    numbers=left,
    frame=single,
    basicstyle=\ttfamily
}
```

All following code blocks will use these settings unless overridden.

### Alternative: Minted Package

The **`minted` package** provides advanced syntax highlighting using the external **Pygments** library.

Example:

```latex
\usepackage{minted}
```

```latex
\begin{minted}{python}
def hello():
    print("Hello")
\end{minted}
```

Note: `minted` requires compiling with the `-shell-escape` option.

### Best Practices

* Use **`verbatim`** for quick code snippets.
* Use **`listings`** for structured code blocks with numbering and captions.
* Use **`minted`** for advanced syntax highlighting in technical documents.
* Keep code blocks in **monospace fonts** for readability.

--- 

## TikZ

TikZ is a powerful LaTeX package for creating diagrams, graphs, and vector graphics directly in 
LaTeX.

The minimal requirements are: 

```latex
\usepackage{tikz}
\usepackage{pgfplots}
\usetikzlibrary{positioning} % more libraries can be added for different use cases
```

### Basic Drawign 

```latex 
\tikz \draw (0,0) -- (2,1) -- (3,2)
```

### Tikz Environment

```latex
\begin{tikzpicture}
  \draw (0,0) circle (1); %circle of radius 1
  \draw (1,1) rectangle (5,4); 
  \draw (1,1) grid (5,4);  % fills the rectangle
\end{tikzpicture}
```

### Thickness

```latex 
\begin{tikzpicture}
  \draw[ultra thick] (0,3) -- (2,3);
  \draw[very thick] (0,2.5) -- (2,2.5);
  \draw[thick] (0,2) -- (2,2);
  \draw[thin] (0,1.5) -- (2,1.5);
  \draw[very thin] (0,1) -- (2,1);
  \draw[ultra thin] (0,.5) -- (2,.5);

  \draw node at (3, 3) {Ultra Thick};
  \draw node at (3, 2.5) {Very Thick};
  \draw node at (3, 2) {Thick};
  \draw node at (3, 1.5) {Thin};
  \draw node at (3, 1) {Very Thin };
  \draw node at (3, 0.5) {Ultra Thin};
\end{tikzpicture}
```

### Sphere with arcs, shade and gradients

```latex
\begin{center}
    \begin{tikzpicture}[transform canvas={scale=4.0}]  %%[scale=4] ONLY changes distances, not the canvas
    \draw[blue] (0,1) arc (90:-90:0.5cm and 1cm);
    \draw[dashed, red] (0,1) arc (90:270:0.5cm and 1cm);
    \draw (0,0) circle (1cm);
    \filldraw[red] (0,1) circle  (0.05); %add fill=, and draw= to have separate colours
    \filldraw[red] (0,-1) circle (0.05);
    \shade[ball color=blue!10!white,opacity=0.20] (0,0) circle (1cm);
    \end{tikzpicture}
\end{center}
```

### Specifying Styles 

```latex 

\begin{tikzpicture}[
youngnode/.style={rectangle, draw=red!60, fill=red!5, very thick, minimum size=40},
oldnode/.style={rectangle, draw=blue!60, fill=blue!5, very thick, minimum size=40},
]

  %Nodes
  \node[oldnode]        (SusO)                            { $S_O(t)$};
  \node[oldnode]        (InfO)       [below=of SusO]      { $I_O(t)$};
  \node[oldnode]        (RecO)       [below=of InfO]      { $R_O(t)$};

  \node[youngnode]      (SusY)        [left=of SusO]      { $S_Y(t)$};
  \node[youngnode]      (InfY)        [left=of InfO]      { $I_Y(t)$};
  \node[youngnode]      (RecY)        [left=of RecO]      { $R_Y(t)$};

  %Lines
  \draw[->, very thick] (SusO.south east)  to node[right] {$a_{OO}$} (InfO.north east);
  \draw[->, very thick] (InfO.south)  to node[right] {$b_O$} (RecO.north);
  \draw[->, very thick] (RecO.east)  .. controls  +(right:17mm) and +(right:17mm)   .. (SusO.east);

  \draw[->, very thick] (SusY.south west)  to node[left] {$a_{YY}$} (InfY.north west);
  \draw[->, very thick] (InfY.south)  to node[left] {$b_Y$} (RecY.north);
  \draw[->, very thick] (RecY.west) .. controls  +(left:17mm) and +(left:17mm)   .. (SusY.west);

  \draw[dashed,->, very thick] (InfO.north west)  to  (SusY.south east);
  \draw[->, very thick] (SusY.south east)  to node[left] {$a_{OY}$} (InfY.north east);

  \draw[->, very thick] (SusO.south west)  to node[right] {$a_{YO}$} (InfO.north west);
  \draw[dashed,->, very thick] (InfY.north east)  to  (SusO.south west);
\end{tikzpicture}

```

### Atomata and Graphs


### 2D Plots

```latex 
\begin{tikzpicture}

  \begin{axis}[xmin=-2, xmax=2, ymin=10, ymin=-10, axis lines=middle]
    \addplot{x^2};  
    \addplot[color=red, dashed, mark=*, sample=50]{x};
  \end{axis}

\end{tikzpicture}

\begin{tikzpicture}

  % Axis square
  \begin{axis}[xmin=-2, xmax=2, ymin=10, ymin=-10]
    \addplot{x^2};  
    \addplot[color=red, dashed, mark=*, sample=50]{x};
  \end{axis}

\end{tikzpicture}


```

### 3D Plots 


### Geometry


--- 

## Footnotes 

You can use footnotes usigin `\footnote{text}`. If you want to define it later you can use `\footnotemark` and later use `\footnotetext{text}`.

## Colors Boxes

The **`tcolorbox` package** provides highly customizable colored boxes for highlighting content such as definitions, examples, warnings, notes, or code 
blocks. It is widely used in lecture notes, textbooks, and research documents to visually separate important information.

Basic usage:

```latex
\usepackage{tcolorbox}
````

A simple box:

```latex
\begin{tcolorbox}
This is a simple highlighted box.
\end{tcolorbox}
```

### Basic Customization

`tcolorbox` allows customization of colors, borders, and background.

Example:

```latex
\begin{tcolorbox}[colback=blue!5, colframe=blue!60]
Important information inside a colored box.
\end{tcolorbox}
```

Common options:

| Option            | Description                |
| ----------------- | -------------------------- |
| `colback`         | Background color           |
| `colframe`        | Border color               |
| `title`           | Title displayed at the top |
| `sharp corners`   | Removes rounded corners    |
| `rounded corners` | Enables rounded corners    |
| `boxrule`         | Border thickness           |


Example with title:

```latex
\begin{tcolorbox}[title=Definition]
A definition or highlighted explanation.
\end{tcolorbox}
```

### Styled Information Boxes

Boxes can be styled for specific purposes such as notes, warnings, or examples.

Example:

```latex
\begin{tcolorbox}[title=Note, colback=yellow!10, colframe=yellow!50!black]
This box contains an important note.
\end{tcolorbox}
```

Example warning box:

```latex
\begin{tcolorbox}[title=Warning, colback=red!5, colframe=red!75!black]
Be careful when using this method.
\end{tcolorbox}
```

### Breakable Boxes

Large boxes can span multiple pages using the `breakable` option.

```latex
\begin{tcolorbox}[breakable]
Long content that may continue across pages.
\end{tcolorbox}
```

### Creating Custom Box Environments

Reusable box styles can be defined with `\newtcolorbox`.

Example:

```latex
\newtcolorbox{examplebox}{
colback=green!5,
colframe=green!60!black,
title=Example
}
```

Usage:

```latex
\begin{examplebox}
This is an example box used throughout the document.
\end{examplebox}
```

This allows consistent formatting for recurring elements.

### Code Blocks with tcolorbox

`tcolorbox` integrates well with code environments such as `listings`.

Example:

```latex
\begin{tcolorbox}[title=Code Example]
    \begin{verbatim}
        print("Hello World")
    \end{verbatim}
\end{tcolorbox}
```

This is useful for visually separating code snippets from the surrounding text.

## BibTeX

Create a `.bib` file. We also need the `apacite` package.

- **Format**: `\bibliographystyle{plain}` has to be put in the preamble of the document.

- **Include in the Document**: `\bibliography{ref.bib}` has to be put in the preamble of the document.

- **Creating a reference**: This can be written manually, but often they are directly available online by the 
sources databases.

```bib 
@inproceedings{djk,
  author={Noto, M. and Sato, H.},
  booktitle={Smc 2000 conference proceedings. 2000 ieee international conference on systems, man and cybernetics. 'cybernetics evolving to systems, humans, organizations, and their complex interactions' (cat. no.0}, 
  title={A method for the shortest path search by extended Dijkstra algorithm}, 
  year={2000},
  volume={3},
  number={},
  pages={2316-2320 vol.3},
  keywords={Search problems;Navigation;Search methods;Costs;Road transportation;Communication networks;Explosives;Hardware;Genetic mutations},
  doi={10.1109/ICSMC.2000.886462}
}
```

- **Citing**: I can reference my sources `\cite{djk}`.

### Citation of Refereces Markers

- `@inproceedings`: papers.
- `@misc`: general or undefined sources.
- `@software`: libraries, tools or software in general.
- `@online`: git repos, websites, web-documentation, etc.


