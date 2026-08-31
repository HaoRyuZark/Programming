# Matplotlib

A plotting library for Python, built on top of NumPy. We use the interface `matplotlib.pyplot`, a MATLAB-style stateful API.

## Import

```python
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D          # required for 3D plots
from matplotlib import animation, colors, cm
```

---

## Key Concepts

Matplotlib's object hierarchy has three core layers:

- **Figure**: the top-level container that holds everything. A single figure can contain one or more Axes.

- **Axes**: the actual plot area — the region where data is drawn. A Figure can have multiple Axes objects arranged in a grid or freely positioned.

- **Axis**: the number-line-like objects (x-axis, y-axis) attached to an Axes. Controls ticks, labels, limits, and scale.

### Two Interfaces

**pyplot (implicit / stateful)**: tracks a "current figure" and "current axes" automatically. Fine for quick scripts and interactive use.

```python
plt.plot([1, 2, 3], [4, 5, 6])
plt.title("Quick Plot")
plt.show()
```

**Object-Oriented (explicit)**: preferred for anything complex. You hold references to `Figure` and `Axes` objects and call methods on them directly.

```python
fig, ax = plt.subplots()
ax.plot([1, 2, 3], [4, 5, 6])
ax.set_title("OO Plot")
plt.show()
```

> For this reference, **OO-style** method names are listed (e.g., `ax.plot()`). The equivalent pyplot shortcut is always `plt.plot()`.

---

## Figure & Axes Creation

- `plt.figure(num=None, figsize=None, dpi=None, facecolor=None, edgecolor=None, tight_layout=False, layout=None)`: creates a new Figure or activates an existing one.
  - `num`: integer or string label for the figure. If a figure with this label already exists, it is made current.
  - `figsize`: tuple `(width, height)` in inches. Default is `[6.4, 4.8]`.
  - `dpi`: dots per inch (resolution). Default is `100`.
  - `facecolor`: background colour of the figure.
  - `layout`: `'tight'`, `'constrained'`, or `'compressed'` — automatic spacing algorithm.

- `plt.subplots(nrows=1, ncols=1, sharex=False, sharey=False, squeeze=True, figsize=None, dpi=None, subplot_kw=None, gridspec_kw=None, **fig_kw)`: creates a Figure and a grid 
of Axes in one call. The recommended way to start any plot.
  - `nrows`, `ncols`: number of rows and columns in the Axes grid.
  - `sharex` / `sharey`: if `True` (or `'all'`, `'row'`, `'col'`), the axes share limits and ticks along that dimension.
  - `squeeze`: if `True`, extra dimensions are removed — a single Axes is returned as a scalar, one row/column as a 1D array.
  - `figsize`: overall figure size as `(width, height)` inches.
  - `subplot_kw`: dict of keyword arguments passed to each `add_subplot()` call.
  - `gridspec_kw`: dict of keyword arguments passed to the underlying `GridSpec`.

- `plt.subplot_mosaic(mosaic, sharex=False, sharey=False, figsize=None, layout=None, **fig_kw)`: creates a figure with a custom layout defined by an ASCII art string or a nested list. 
Each unique label becomes a named Axes accessible by key.
  - `mosaic`: list of lists or a multi-line string — each unique character/string becomes an Axes label.
  - `layout`: `'constrained'` is recommended for mosaic layouts.

```python
# Single axes
fig, ax = plt.subplots()

# 2×2 grid
fig, axs = plt.subplots(2, 2, figsize=(10, 8))
axs[0, 0].set_title("Top Left")
axs[1, 1].set_title("Bottom Right")

# Row of 3 with shared y-axis
fig, (ax1, ax2, ax3) = plt.subplots(1, 3, sharey=True, figsize=(12, 4))

# Mosaic layout — 'left' spans two rows, 'right_top' and 'right_bot' stack
fig, axd = plt.subplot_mosaic(
    [["left", "right_top"],
     ["left", "right_bot"]],
    layout="constrained",
    figsize=(9, 5)
)
axd["left"].set_title("Left (tall)")
axd["right_top"].set_title("Right Top")

# Standalone figure, then add axes manually
fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111)          # 1 row, 1 col, 1st subplot
```

---

## Line Plot

`ax.plot(x, y, fmt='', color=None, linestyle=None, linewidth=None, marker=None, markersize=None, alpha=None, label=None)`: plots y versus x as lines and/or markers.
    - `x`, `y`: array-like data. If `x` is omitted, it defaults to `0..N-1`.
    - `fmt`: format string `"[marker][line][color]"` — e.g., `'o-r'` for circle markers, solid red line.
    - `color` (or `c`): line colour — named string, hex `'#rrggbb'`, or RGB tuple.
    - `linestyle` (or `ls`): `'-'` solid, `'--'` dashed, `'-.'` dash-dot, `':'` dotted, `'None'` no line.
    - `linewidth` (or `lw`): line thickness in points.
    - `marker`: marker style — `'o'`, `'s'`, `'^'`, `'*'`, `'+'`, `'x'`, `'D'`, etc.
    - `markersize` (or `ms`): marker size in points.
    - `markerfacecolor` (or `mfc`): fill colour of the marker.
    - `markeredgecolor` (or `mec`): edge colour of the marker.
    - `alpha`: transparency in `[0, 1]`. `0` = fully transparent, `1` = fully opaque.
    - `label`: string shown in the legend if `ax.legend()` is called.
    - `zorder`: drawing order (higher values are drawn on top).

```python
x = np.linspace(0, 2 * np.pi, 200)

fig, ax = plt.subplots(figsize=(8, 4))

ax.plot(x, np.sin(x), color='steelblue', linewidth=2, label='sin(x)')
ax.plot(x, np.cos(x), color='tomato', linestyle='--', linewidth=2, label='cos(x)')
ax.plot(x[::20], np.sin(x[::20]), 'ko', markersize=6, label='samples')

ax.set_title("Sine and Cosine")
ax.set_xlabel("x (radians)")
ax.set_ylabel("Amplitude")
ax.legend()
plt.tight_layout()
plt.show()
```

### Fill Between

`ax.fill_between(x, y1, y2=0, where=None, alpha=0.3, color=None, label=None)`: fills the area between two horizontal curves.
    - `x`: the x coordinates.
    - `y1`, `y2`: lower and upper boundaries. `y2` defaults to zero.
    - `where`: boolean array — fill only where `where` is `True`.

```python
fig, ax = plt.subplots()
ax.plot(x, np.sin(x))
ax.fill_between(x, np.sin(x), 0, alpha=0.25, color='steelblue', label='area')
ax.fill_between(x, np.sin(x), np.cos(x),
                where=(np.sin(x) > np.cos(x)),
                alpha=0.3, color='green', label='sin > cos')
ax.legend()
plt.show()
```

### Step Plot

`ax.step(x, y, where='pre', **kwargs)`: draws a step (staircase) function instead of interpolating between points.
  - `where`: `'pre'` the step is at the left edge of each interval; `'post'` at the right edge; `'mid'` centred.

```python
ax.step(x, np.round(np.sin(x), 1), where='mid', color='purple')
```

---

## Scatter Plot

`ax.scatter(x, y, s=None, c=None, marker='o', cmap=None, norm=None, alpha=None, edgecolors=None, linewidths=None, label=None)`: creates a scatter plot.

- `x`, `y`: data coordinates.
- `s`: marker size(s) in points². Scalar or array-like (one size per point).
- `c`: colour(s). Scalar colour, list of colours, or array of values mapped through `cmap`.
- `marker`: marker shape.
- `cmap`: colormap name (used when `c` is an array of numeric values).
- `norm`: normalisation instance for mapping `c` values to colours.
- `alpha`: transparency.
- `edgecolors`: colour(s) of marker edges. Use `'none'` to remove edges.
- `linewidths`: width of marker edges.
- `vmin`, `vmax`: min/max values for colormap normalisation.

```python
N = 200
x = np.random.randn(N)
y = np.random.randn(N)
sizes  = np.random.uniform(20, 200, N)
colors = np.random.rand(N)

fig, ax = plt.subplots()
sc = ax.scatter(x, y, s=sizes, c=colors, cmap='viridis',
                alpha=0.7, edgecolors='grey', linewidths=0.5)
plt.colorbar(sc, ax=ax, label='Value')
ax.set_title("Bubble Scatter Plot")
plt.show()
```

---

## Bar Plot

`ax.bar(x, height, width=0.8, bottom=0, color=None, edgecolor=None, linewidth=None, align='center', label=None)`: makes a vertical bar plot.
    - `x`: x-coordinates of the bars. Can be strings for categorical data.
    - `height`: heights of the bars.
    - `width`: width of each bar (default `0.8`).
    - `bottom`: y-coordinate(s) for the bottom of each bar — useful for stacked bars.
    - `color`: bar fill colour(s).
    - `edgecolor`: bar edge colour.
    - `align`: `'center'` (default) or `'edge'` — alignment relative to `x`.

`ax.barh(y, width, height=0.8, left=0, **kwargs)`: horizontal bar plot. Parameters mirror `bar()` but transposed.

```python
categories = ['Python', 'C++', 'Rust', 'Go', 'Java']
values1 = [45, 30, 20, 25, 35]
values2 = [10, 20, 15, 30, 25]
x = np.arange(len(categories))
width = 0.35

fig, axs = plt.subplots(1, 2, figsize=(12, 4))

# Grouped bars
axs[0].bar(x - width/2, values1, width, label='2023', color='steelblue', edgecolor='black')
axs[0].bar(x + width/2, values2, width, label='2024', color='tomato', edgecolor='black')
axs[0].set_xticks(x)
axs[0].set_xticklabels(categories)
axs[0].legend()
axs[0].set_title("Grouped Bar Chart")

# Stacked bars
axs[1].bar(categories, values1, label='2023', color='steelblue')
axs[1].bar(categories, values2, bottom=values1, label='2024', color='tomato')
axs[1].legend()
axs[1].set_title("Stacked Bar Chart")

plt.tight_layout()
plt.show()
```

---

## Histogram

`ax.hist(x, bins=10, range=None, density=False, cumulative=False, histtype='bar', color=None, edgecolor=None, alpha=None, label=None)`: computes and plots a histogram.
    - `x`: data. Can be a list of arrays for multiple datasets.
    - `bins`: number of equal-width bins (int) or explicit bin edges (array-like). Also accepts strings like `'auto'`, `'fd'`, `'sturges'`.
    - `range`: `(min, max)` tuple — only data within this range is used.
    - `density`: if `True`, normalises so that the area under the histogram equals 1 (probability density).
    - `cumulative`: if `True`, plots the cumulative distribution.
    - `histtype`: `'bar'` (default), `'barstacked'`, `'step'` (unfilled step curve), `'stepfilled'`.
    - `orientation`: `'vertical'` (default) or `'horizontal'`.
    - `rwidth`: relative width of the bars as a fraction of the bin width.

```python
rng = np.random.default_rng(0)
data_a = rng.normal(60, 10, 500)
data_b = rng.normal(80, 8, 500)

fig, axs = plt.subplots(1, 2, figsize=(12, 4))

axs[0].hist(data_a, bins=30, color='steelblue', edgecolor='white', alpha=0.8)
axs[0].axvline(data_a.mean(), color='red', linestyle='--', linewidth=1.5, label=f'mean={data_a.mean():.1f}')
axs[0].set_title("Histogram with Mean Line")
axs[0].legend()

# Overlapping histograms
axs[1].hist(data_a, bins=30, alpha=0.6, label='Group A', density=True)
axs[1].hist(data_b, bins=30, alpha=0.6, label='Group B', density=True)
axs[1].set_title("Overlapping Density Histograms")
axs[1].legend()

plt.tight_layout()
plt.show()
```

---

## Pie Chart

`ax.pie(x, labels=None, autopct=None, explode=None, colors=None, startangle=0, shadow=False, radius=1, counterclock=True, pctdistance=0.6, labeldistance=1.1, wedgeprops=None, textprops=None)`: plots a 
pie chart.
    - `x`: array-like of wedge sizes. Values are normalised automatically.
    - `labels`: sequence of strings labelling each wedge.
    - `autopct`: format string or function for labelling percentages inside wedges — e.g., `'%1.1f%%'`.
    - `explode`: array-like of offsets — how far to "explode" each wedge out from the centre.
    - `startangle`: starting angle in degrees, measured counterclockwise from the x-axis.
    - `shadow`: if `True`, draws a shadow beneath the pie.
    - `wedgeprops`: dict of properties for the wedge patches — e.g., `{'linewidth': 1, 'edgecolor': 'white'}`.
    - `pctdistance`: fraction of the radius at which percentage labels are drawn.
    - `labeldistance`: fraction of the radius at which labels are drawn.

```python
sizes  = [35, 25, 20, 15, 5]
labels = ['Python', 'JavaScript', 'Java', 'C++', 'Other']
explode = [0.05, 0, 0, 0, 0]

fig, ax = plt.subplots(figsize=(6, 6))
ax.pie(sizes, labels=labels, explode=explode, autopct='%1.1f%%',
       startangle=90, shadow=True,
       wedgeprops={'linewidth': 1.5, 'edgecolor': 'white'})
ax.set_title("Language Popularity")
plt.show()
```

---

## Box Plot

`ax.boxplot(x, notch=False, vert=True, patch_artist=False, showfliers=True, showmeans=False, meanline=False, labels=None, widths=0.5, flierprops=None, medianprops=None, boxprops=None, whiskerprops=None)`: 
draws a box-and-whisker plot.
    - `x`: array-like or list of array-likes — one box per element.
    - `notch`: if `True`, draws notched boxes to show the confidence interval around the median.
    - `vert`: if `False`, draws horizontal boxes.
    - `patch_artist`: if `True`, fills boxes with colour (required for setting box colour).
    - `showfliers`: if `False`, outlier points are hidden.
    - `showmeans`: if `True`, marks the mean value.
    - `whis`: length of the whiskers as a multiple of the IQR (default `1.5`), or as `[5, 95]` percentile range.
    - `labels`: tick labels for each dataset.
    - `widths`: width of each box.

```python
rng = np.random.default_rng(1)
data = [rng.normal(mu, 1.5, 60) for mu in [20, 25, 22, 28]]

fig, ax = plt.subplots(figsize=(7, 5))
bp = ax.boxplot(data, patch_artist=True, notch=True,
                labels=['Q1', 'Q2', 'Q3', 'Q4'])

colors = ['steelblue', 'tomato', 'seagreen', 'orchid']
for patch, color in zip(bp['boxes'], colors):
    patch.set_facecolor(color)

ax.set_title("Quarterly Distribution")
ax.set_ylabel("Value")
plt.show()
```

### Violin Plot

`ax.violinplot(dataset, positions=None, vert=True, widths=0.5, showmeans=False, showmedians=True, showextrema=True, points=100, bw_method=None)`: draws a violin plot, combines a box plot with a kernel 
density estimate.
    - `dataset`: array-like or list of arrays.
    - `positions`: positions of the violins on the axis (default `range(1, N+1)`).
    - `widths`: width(s) of each violin.
    - `showmeans` / `showmedians` / `showextrema`: toggle summary statistics markers.
    - `bw_method`: bandwidth estimation method for the KDE — `'scott'`, `'silverman'`, or a scalar.

```python
fig, ax = plt.subplots()
ax.violinplot(data, positions=[1, 2, 3, 4], showmedians=True)
ax.set_title("Violin Plot")
plt.show()
```

---

## Heatmap (imshow)

`ax.imshow(X, cmap=None, norm=None, aspect='equal', interpolation='antialiased', alpha=None, vmin=None, vmax=None, origin='upper', extent=None)`: displays data as an 
image (2D array heatmap).

- `X`: 2D array-like `(M, N)` — or `(M, N, 3)` RGB / `(M, N, 4)` RGBA.
- `cmap`: colormap name (ignored for RGB input).
- `aspect`: `'equal'` (square pixels), `'auto'` (stretch to fill), or a float aspect ratio.
- `interpolation`: resampling method — `'nearest'`, `'bilinear'`, `'bicubic'`, `'antialiased'`, etc.
- `vmin`, `vmax`: data range for colormap normalisation.
- `origin`: `'upper'` — row 0 at the top (image convention); `'lower'` — row 0 at the bottom (Cartesian convention).
- `extent`: `[left, right, bottom, top]` — sets the bounding box in data coordinates.

```python
data = np.random.rand(8, 8)

fig, ax = plt.subplots(figsize=(6, 5))
im = ax.imshow(data, cmap='YlOrRd', aspect='auto', vmin=0, vmax=1)
plt.colorbar(im, ax=ax, label='Value')

# Annotate cells
for i in range(data.shape[0]):
    for j in range(data.shape[1]):
        ax.text(j, i, f'{data[i, j]:.2f}', ha='center', va='center', fontsize=8)

ax.set_title("Annotated Heatmap")
plt.tight_layout()
plt.show()
```

---

## Contour Plots

`ax.contour(X, Y, Z, levels=None, cmap=None, colors=None, linewidths=None, linestyles=None)`: draws contour lines.

`ax.contourf(X, Y, Z, levels=None, cmap=None, alpha=None)`: draws filled contour regions.

- `X`, `Y`: 2D coordinate arrays (from `np.meshgrid`). Can be omitted — defaults to integer indices.
- `Z`: 2D array of values.
- `levels`: number of contour levels (int) or explicit level values (array-like).
- `cmap`: colormap for filling.
- `colors`: single colour or list of colours for contour lines (overrides `cmap`).

`ax.clabel(cs, levels=None, fmt='%1.1f', inline=True, fontsize=8)`: adds labels to contour lines from a `ContourSet` `cs`.

```python
X = np.linspace(-3, 3, 100)
Y = np.linspace(-3, 3, 100)
X, Y = np.meshgrid(X, Y)
Z = np.sin(X) * np.cos(Y)

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 4))

# Filled contour
cf = ax1.contourf(X, Y, Z, levels=20, cmap='RdBu_r')
plt.colorbar(cf, ax=ax1)
ax1.set_title("Filled Contour")

# Line contour with labels
cs = ax2.contour(X, Y, Z, levels=10, cmap='RdBu_r')
ax2.clabel(cs, inline=True, fontsize=8)
ax2.set_title("Contour Lines")

plt.tight_layout()
plt.show()
```

---

## Stack Plot

`ax.stackplot(x, *args, labels=None, colors=None, alpha=None, baseline='zero')`: draws a stacked area plot.

- `x`: 1D x-coordinates.
- `*args`: one or more 1D arrays, stacked on top of one another.
- `baseline`: `'zero'` (default), `'sym'` (symmetric around zero), `'wiggle'` (minimises slope), `'weighted_wiggle'`.

```python
minutes = np.arange(0, 60)
p1 = np.abs(np.random.randn(60)) + 1
p2 = np.abs(np.random.randn(60)) + 1
p3 = np.abs(np.random.randn(60)) + 1

fig, ax = plt.subplots(figsize=(10, 4))
ax.stackplot(minutes, p1, p2, p3,
             labels=['Player 1', 'Player 2', 'Player 3'],
             colors=['#4878D0', '#EE854A', '#6ACC65'],
             alpha=0.85)
ax.legend(loc='upper left')
ax.set_title("Time Distribution (Stacked Area)")
ax.set_xlabel("Minutes")
plt.show()
```

---

## Stem Plot

`ax.stem(x, y, linefmt='C0-', markerfmt='C0o', basefmt='C3-', use_line_collection=True, bottom=0)`: draws vertical lines from a baseline to each data point, with a marker at the tip.

```python
x = np.linspace(0.1, 2 * np.pi, 41)
fig, ax = plt.subplots()
ax.stem(x, np.cos(x), linefmt='grey', markerfmt='D', bottom=0)
ax.set_title("Stem Plot")
plt.show()
```

---

## Error Bars

`ax.errorbar(x, y, yerr=None, xerr=None, fmt='', capsize=5, ecolor=None, elinewidth=None, barsabove=False, **kwargs)`: plots points with attached error bars.

- `yerr` / `xerr`: scalar (symmetric), shape `(N,)` (symmetric per point), or shape `(2, N)` `[lower, upper]` (asymmetric).
- `fmt`: format string for the data points (same as `plot()`).
- `capsize`: length of the error bar caps in points.
- `ecolor`: colour of the error bars (defaults to line colour).

```python
x    = np.arange(1, 6)
y    = np.array([2.5, 3.8, 4.1, 3.3, 5.0])
yerr = np.array([0.3, 0.5, 0.4, 0.6, 0.2])

fig, ax = plt.subplots()
ax.errorbar(x, y, yerr=yerr, fmt='o-', capsize=5, color='steelblue',
            ecolor='black', elinewidth=1.5)
ax.set_title("Error Bar Plot")
plt.show()
```

---

## Axis Configuration

### Labels & Title

- `ax.set_title(label, fontsize=None, fontweight=None, pad=6, loc='center')`: sets the plot title.
  - `pad`: spacing between the title and the plot in points.
  - `loc`: `'left'`, `'center'`, or `'right'`.

- `ax.set_xlabel(xlabel, fontsize=None, labelpad=4)`: sets the x-axis label.
- `ax.set_ylabel(ylabel, fontsize=None, labelpad=4)`: sets the y-axis label.

- `fig.suptitle(t, fontsize=None, fontweight=None, y=None)`: adds a centred super-title spanning all subplots in the figure.

```python
ax.set_title("My Plot", fontsize=14, fontweight='bold')
ax.set_xlabel("Time (s)", fontsize=12)
ax.set_ylabel("Amplitude", fontsize=12)
fig.suptitle("Figure Title", fontsize=16, fontweight='bold')
```

### Limits & Range

- `ax.set_xlim(left=None, right=None)` / `ax.set_ylim(bottom=None, top=None)`: sets axis limits.
- `ax.axis([xmin, xmax, ymin, ymax])`: sets all four limits at once. Also accepts `'equal'`, `'tight'`, `'off'`, etc.

```python
ax.set_xlim(0, 10)
ax.set_ylim(-1, 1)
ax.axis('equal')        # equal aspect ratio
ax.axis('off')          # hide axes entirely
```

### Ticks

- `ax.set_xticks(ticks, labels=None, minor=False)`: sets tick positions (and optionally labels) on the x-axis.
- `ax.set_yticks(ticks, labels=None, minor=False)`: same for y-axis.
- `ax.set_xticklabels(labels, rotation=None, fontsize=None, ha='center')`: sets custom text labels for existing x ticks.
- `ax.tick_params(axis='both', which='major', direction='out', length=4, width=1, color='black', labelsize=10, rotation=0, pad=4)`: configures tick appearance.
  - `axis`: `'x'`, `'y'`, or `'both'`.
  - `which`: `'major'`, `'minor'`, or `'both'`.
  - `direction`: `'in'`, `'out'`, or `'inout'`.
  - `labelrotation`: rotation angle for tick labels.
  - `top`, `bottom`, `left`, `right`: booleans to show/hide ticks on each side.
- `ax.minorticks_on()` / `ax.minorticks_off()`: toggles minor ticks.

```python
ax.set_xticks([0, np.pi/2, np.pi, 3*np.pi/2, 2*np.pi])
ax.set_xticklabels(['0', 'π/2', 'π', '3π/2', '2π'])
ax.tick_params(axis='x', rotation=45, labelsize=10)
ax.tick_params(axis='both', which='major', direction='in', length=6)
ax.minorticks_on()
```

### Scale

- `ax.set_xscale(value)` / `ax.set_yscale(value)`: sets the scale of the axis.
  - `value`: `'linear'` (default), `'log'` (base 10), `'symlog'` (symmetric log — handles negative values), `'logit'`.

```python
ax.set_xscale('log')
ax.set_yscale('symlog', linthresh=0.01)  # linear between -0.01 and 0.01
```

### Grid

- `ax.grid(visible=True, which='major', axis='both', color=None, linestyle='--', linewidth=0.8, alpha=None)`: shows or hides the grid.
  - `which`: `'major'`, `'minor'`, or `'both'`.
  - `axis`: `'x'`, `'y'`, or `'both'`.

```python
ax.grid(True, which='major', color='grey', linestyle='--', linewidth=0.5, alpha=0.7)
ax.grid(True, which='minor', color='lightgrey', linestyle=':', linewidth=0.4)
```

### Reference Lines

- `ax.axhline(y=0, xmin=0, xmax=1, **kwargs)`: draws a horizontal line spanning the full axes width.
- `ax.axvline(x=0, ymin=0, ymax=1, **kwargs)`: draws a vertical line spanning the full axes height.
- `ax.axhspan(ymin, ymax, xmin=0, xmax=1, **kwargs)`: draws a horizontal shaded band.
- `ax.axvspan(xmin, xmax, ymin=0, ymax=1, **kwargs)`: draws a vertical shaded band.

```python
ax.axhline(0, color='black', linewidth=0.8)          # x-axis line
ax.axvline(np.pi, color='red', linestyle='--')        # vertical marker
ax.axhspan(0.8, 1.0, color='yellow', alpha=0.3)       # highlight band
```

### Twin Axes

- `ax.twinx()`: creates a second y-axis sharing the same x-axis. Returns a new Axes.
- `ax.twiny()`: creates a second x-axis sharing the same y-axis.

```python
fig, ax1 = plt.subplots()
ax2 = ax1.twinx()

ax1.plot(x, np.sin(x), 'b-', label='sin')
ax2.plot(x, np.exp(x / 5), 'r-', label='exp')
ax1.set_ylabel("sin(x)", color='blue')
ax2.set_ylabel("exp(x/5)", color='red')
```

---

## Legend

`ax.legend(handles=None, labels=None, loc='best', bbox_to_anchor=None, ncols=1, title=None, fontsize=None, frameon=True, framealpha=0.8, shadow=False, fancybox=True, 
borderpad=0.4, labelspacing=0.5, handlelength=2.0)`: places a legend on the Axes.

- `handles`: list of `Artist` objects to include (auto-detected from `label=` if omitted).
- `labels`: list of strings (auto-detected from `label=` if omitted).
- `loc`: position string or code — `'best'`, `'upper right'`, `'upper left'`, `'lower left'`, `'lower right'`, `'right'`, `'center left'`, `'center right'`, `'lower center'`, `'upper center'`, `'center'`.
- `bbox_to_anchor`: tuple `(x, y)` or `(x, y, width, height)` — places the legend at an arbitrary position relative to the Axes.
- `ncols`: number of legend columns.
- `title`: legend title string.
- `frameon`: if `False`, removes the legend box border.

```python
ax.plot(x, np.sin(x), label='sin(x)')
ax.plot(x, np.cos(x), label='cos(x)')
ax.legend(loc='upper right', title='Functions', fontsize=10, shadow=True)

# Legend outside the plot
ax.legend(bbox_to_anchor=(1.05, 1), loc='upper left', borderaxespad=0)

# Manual handles
from matplotlib.lines import Line2D
handles = [Line2D([0], [0], color='blue', label='Manual A'),
           Line2D([0], [0], color='red',  label='Manual B')]
ax.legend(handles=handles)
```

---

## Annotations & Text

- `ax.text(x, y, s, fontsize=None, ha='left', va='baseline', color=None, rotation=None, bbox=None, transform=None)`: adds text at a data-coordinate position.
  - `ha`: horizontal alignment — `'left'`, `'center'`, `'right'`.
  - `va`: vertical alignment — `'top'`, `'center'`, `'bottom'`, `'baseline'`.
  - `bbox`: dict — draws a box around the text, e.g., `{'boxstyle': 'round', 'facecolor': 'wheat', 'alpha': 0.5}`.
  - `transform`: use `ax.transAxes` for axes-fraction coordinates instead of data coordinates.

- `ax.annotate(text, xy, xytext=None, xycoords='data', textcoords='data', arrowprops=None, ha='left', va='center', fontsize=None)`: adds a text annotation with an optional 
arrow pointing to a data point.
  - `xy`: the point being annotated (the tip of the arrow).
  - `xytext`: the position of the text.
  - `xycoords` / `textcoords`: coordinate system — `'data'`, `'axes fraction'`, `'figure fraction'`.
  - `arrowprops`: dict — e.g., `{'arrowstyle': '->', 'color': 'black'}`. Arrow styles: `'->'`, `'<-'`, `'<->'`, `'fancy'`, `'wedge'`, `'simple'`.

```python
fig, ax = plt.subplots()
ax.plot([1, 2, 3, 4], [1, 4, 2, 3], 'o-')

# Simple text at data coordinates
ax.text(2, 4.1, 'Peak', ha='center', fontsize=10,
        bbox={'boxstyle': 'round', 'facecolor': 'lightyellow', 'alpha': 0.8})

# Annotation with arrow
ax.annotate('Minimum', xy=(3, 2), xytext=(3.5, 1.2),
            arrowprops={'arrowstyle': '->', 'color': 'red'},
            fontsize=10, color='red')

# Text in axes-fraction coordinates (top-left corner)
ax.text(0.02, 0.97, 'Note: values are illustrative',
        transform=ax.transAxes, va='top', fontsize=8, color='grey')
```

---

## Colorbar

`plt.colorbar(mappable, ax=None, cax=None, label='', orientation='vertical', shrink=1.0, pad=0.05, fraction=0.15, aspect=20, extend='neither', ticks=None, format=None)`: adds a 
colorbar to the figure.

- `mappable`: the `ScalarMappable` object (return value of `imshow`, `scatter`, `contourf`, etc.) to which the colorbar applies.
- `ax`: the Axes to which the colorbar is attached (shrinks that Axes to make room).
- `cax`: an existing Axes to draw the colorbar in (full control over position).
- `label`: label string for the colorbar axis.
- `orientation`: `'vertical'` or `'horizontal'`.
- `shrink`: fraction by which to shrink the colorbar.
- `extend`: `'neither'`, `'both'`, `'min'`, `'max'` — adds pointed ends for out-of-range values.
- `ticks`: explicit tick locations.

```python
fig, ax = plt.subplots()
im = ax.imshow(np.random.rand(10, 10), cmap='plasma')
cbar = plt.colorbar(im, ax=ax, label='Intensity', shrink=0.8, extend='both')
cbar.set_ticks([0, 0.25, 0.5, 0.75, 1.0])
```

---

## Colormaps

Matplotlib provides hundreds of named colormaps, organised by category:


| Category | Examples |
|---|---|
| **Perceptually uniform** | `viridis`, `plasma`, `inferno`, `magma`, `cividis` |
| **Sequential** | `Blues`, `Greens`, `Oranges`, `Reds`, `YlOrRd`, `BuPu` |
| **Diverging** | `RdBu`, `coolwarm`, `seismic`, `bwr`, `PiYG` |
| **Cyclic** | `twilight`, `hsv` |
| **Qualitative** | `tab10`, `tab20`, `Set1`, `Set2`, `Pastel1`, `Paired` |
| **Miscellaneous** | `jet`, `rainbow`, `terrain`, `ocean`, `hot`, `cool` |


> Append `_r` to any name to get the reversed version — e.g., `'viridis_r'`.

```python
import matplotlib as mpl

# Get a colormap object
cmap = mpl.colormaps['viridis']

# Sample colours from a colormap
c = cmap(0.5)           # returns RGBA tuple for the midpoint

# List all registered colormaps
print(list(mpl.colormaps))

# Use a colormap for a scatter plot
sc = ax.scatter(x, y, c=z, cmap='plasma', vmin=0, vmax=1)
```

---

## Colors

Matplotlib accepts colour specifications in several formats:


| Format | Example | Description |
|---|---|---|
| Named colour | `'red'`, `'steelblue'`, `'tomato'` | CSS / X11 named colours |
| Short colour code | `'r'`, `'g'`, `'b'`, `'c'`, `'m'`, `'y'`, `'k'`, `'w'` | Single-character shortcuts |
| Hex string | `'#1f77b4'`, `'#ff7f0e'` | 6-digit hex RGB |
| Hex with alpha | `'#1f77b480'` | 8-digit hex RGBA |
| RGB tuple | `(0.1, 0.4, 0.8)` | Floats in `[0, 1]` |
| RGBA tuple | `(0.1, 0.4, 0.8, 0.5)` | Float alpha |
| Greyscale string | `'0.75'` | Float in `[0, 1]` as a string |
| CN cycle alias | `'C0'`, `'C1'`, … `'C9'` | Colours from the default property cycle |


---

## Markers & Linestyles Reference

### Marker Symbols


| Code | Shape | Code | Shape |
|---|---|---|---|
| `'.'` | Point | `'o'` | Circle |
| `','` | Pixel | `'v'` | Triangle down |
| `'^'` | Triangle up | `'<'` | Triangle left |
| `'>'` | Triangle right | `'s'` | Square |
| `'p'` | Pentagon | `'*'` | Star |
| `'h'` | Hexagon 1 | `'H'` | Hexagon 2 |
| `'+'` | Plus | `'x'` | Cross |
| `'D'` | Diamond | `'d'` | Thin diamond |
| `'|'` | Vertical line | `'_'` | Horizontal line |
| `'P'` | Plus (filled) | `'X'` | Cross (filled) |


### Line Styles

| Code | Style |
|---|---|
| `'-'` | Solid line |
| `'--'` | Dashed line |
| `'-.'` | Dash-dot line |
| `':'` | Dotted line |
| `'None'` or `''` | No line |


### Format String Shorthand

The `fmt` parameter for `plot()` is `"[marker][line][color]"`:

```python
ax.plot(x, y, 'o--r')   # circle markers, dashed red line
ax.plot(x, y, 's:b')    # square markers, dotted blue line
ax.plot(x, y, 'D-g')    # diamond markers, solid green line
```

---

## Plot Styling

### Built-in Styles

- `plt.style.use(style)`: applies a predefined style sheet globally. Can accept a list of styles (applied left-to-right).
- `plt.style.context(style)`: context manager — applies a style temporarily within a `with` block.
- `print(plt.style.available)`: lists all available style names.

Common styles: `'seaborn-v0_8'`, `'ggplot'`, `'fivethirtyeight'`, `'bmh'`, `'dark_background'`, `'grayscale'`, `'classic'`, `'tableau-colorblind10'`.

```python
print(plt.style.available)

plt.style.use('seaborn-v0_8')

# Temporary style — doesn't affect code outside the block
with plt.style.context('dark_background'):
    fig, ax = plt.subplots()
    ax.plot(x, np.sin(x))
    plt.show()
```

### rcParams

`rcParams` is a dictionary that controls all default plot properties. Changes persist for the lifetime of the Python session.

- `plt.rcParams[key] = value`: sets a single default.
- `plt.rc(group, **kwargs)`: sets multiple defaults for a group at once.
- `plt.rcdefaults()`: restores all defaults.
- `plt.rc_context(rc=None, fname=None)`: temporarily changes rcParams within a `with` block.

```python
# Common rcParam keys
plt.rcParams['figure.figsize']    = [10, 6]
plt.rcParams['font.size']         = 12
plt.rcParams['font.family']       = 'DejaVu Sans'
plt.rcParams['axes.titlesize']    = 14
plt.rcParams['axes.labelsize']    = 12
plt.rcParams['lines.linewidth']   = 2
plt.rcParams['lines.markersize']  = 8
plt.rcParams['xtick.labelsize']   = 10
plt.rcParams['ytick.labelsize']   = 10
plt.rcParams['legend.fontsize']   = 10
plt.rcParams['axes.grid']         = True
plt.rcParams['grid.alpha']        = 0.4

# Shorthand group setter
plt.rc('axes', titlesize=14, labelsize=12, grid=True)
plt.rc('lines', linewidth=2, markersize=8)

# Temporary context
with plt.rc_context({'axes.facecolor': 'lightyellow', 'grid.color': 'grey'}):
    fig, ax = plt.subplots()
    ax.plot(x, np.sin(x))
    plt.show()
```

---

## Subplots & Layout

### `plt.subplots` Grid

```python
fig, axs = plt.subplots(2, 3, figsize=(14, 8), sharex=True, sharey=True)

for i, ax in enumerate(axs.flat):
    ax.plot(np.random.randn(50).cumsum())
    ax.set_title(f"Subplot {i+1}")

plt.tight_layout()
plt.show()
```

### GridSpec

`matplotlib.gridspec.GridSpec(nrows, ncols, figure=None, wspace=None, hspace=None, width_ratios=None, height_ratios=None)`: fine-grained control over subplot layout;
supports unequal row/column sizes and spanning.

- `wspace` / `hspace`: width and height spacing between subplots as a fraction of the average Axes size.
- `width_ratios` / `height_ratios`: list of relative widths/heights for each column/row.

```python
import matplotlib.gridspec as gridspec

fig = plt.figure(figsize=(10, 6))
gs  = gridspec.GridSpec(2, 3, width_ratios=[2, 1, 1], hspace=0.4, wspace=0.3)

ax1 = fig.add_subplot(gs[0, :])      # first row, all columns
ax2 = fig.add_subplot(gs[1, 0])
ax3 = fig.add_subplot(gs[1, 1:])     # second row, last two columns

ax1.set_title("Wide Top")
ax2.set_title("Bottom Left")
ax3.set_title("Bottom Right (wider)")
plt.show()
```

### Inset Axes

```python
from mpl_toolkits.axes_grid1.inset_locator import inset_axes

fig, ax = plt.subplots(figsize=(7, 5))
ax.plot(x, np.sin(x))

# Small inset axes in the upper right corner
axins = inset_axes(ax, width='35%', height='35%', loc='upper right')
axins.plot(x[:50], np.sin(x[:50]), 'r')
axins.set_title("Inset", fontsize=8)
plt.show()
```

### Spacing

- `plt.tight_layout(pad=1.08, h_pad=None, w_pad=None, rect=None)`: automatically adjusts subplot parameters to prevent overlap.
  - `pad`: padding between figure edge and subplot edges.
  - `rect`: normalised figure coordinates `[left, bottom, right, top]` in which the subplots fit.

- `plt.subplots_adjust(left=None, bottom=None, right=None, top=None, wspace=None, hspace=None)`: manual control over subplot spacing.

```python
plt.tight_layout(pad=2.0)

plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.1,
                    wspace=0.3, hspace=0.4)
```

---

## Multiple Figures

```python
# Create separate figures
fig1, ax1 = plt.subplots()
ax1.plot([1, 2, 3], [1, 4, 9])
ax1.set_title("Figure 1")

fig2, ax2 = plt.subplots()
ax2.bar(['A', 'B', 'C'], [10, 20, 15])
ax2.set_title("Figure 2")

plt.show()   # shows all open figures

# Get current figure / axes
fig = plt.gcf()
ax  = plt.gca()

# Close figures
plt.close(fig1)       # close specific figure
plt.close('all')      # close all open figures
```

---

## 3D Plots

All 3D plots require an `Axes3D`;obtained via `projection='3d'`. 

> For scatter plots, we can just set another array for the z-coordinate without more setup.

```python
from mpl_toolkits.mplot3d import Axes3D   # noqa: F401 (registers the projection)

fig = plt.figure(figsize=(8, 6))
ax  = fig.add_subplot(111, projection='3d')

# Or with subplots
fig, ax = plt.subplots(subplot_kw={'projection': '3d'})
```

### 3D Scatter

`ax.scatter(xs, ys, zs, zdir='z', s=20, c=None, depthshade=True, **kwargs)`

- `depthshade`: if `True`, shades markers based on depth for a 3D appearance.

```python
N = 100
xs, ys, zs = np.random.randn(3, N)
ax.scatter(xs, ys, zs, c=zs, cmap='viridis', s=40, depthshade=True)
ax.set_xlabel('X'); ax.set_ylabel('Y'); ax.set_zlabel('Z')
```

### 3D Surface

`ax.plot_surface(X, Y, Z, cmap=None, rstride=1, cstride=1, linewidth=0, antialiased=True, alpha=None)`: draws a surface plot.

- `rstride` / `cstride`: row and column downsampling stride. Increase to speed up rendering for large arrays.
- `linewidth`: width of the mesh lines on the surface.

```python
x = np.linspace(-3, 3, 60)
y = np.linspace(-3, 3, 60)
X, Y = np.meshgrid(x, y)
Z    = np.sin(np.sqrt(X**2 + Y**2))

fig, ax = plt.subplots(subplot_kw={'projection': '3d'}, figsize=(8, 6))
surf = ax.plot_surface(X, Y, Z, cmap='plasma', linewidth=0, antialiased=True, alpha=0.9)
plt.colorbar(surf, ax=ax, shrink=0.6, label='Z value')
ax.set_title("3D Surface")
plt.show()
```

### 3D Wireframe

`ax.plot_wireframe(X, Y, Z, rstride=1, cstride=1, color=None, linewidth=1)`: draws the surface as a mesh of lines only.

```python
ax.plot_wireframe(X, Y, Z, rstride=3, cstride=3, color='navy', linewidth=0.5)
```

### 3D Contour

`ax.contour3D(X, Y, Z, levels, cmap=None)` / `ax.contourf3D(...)`: draws 3D contour lines or filled contours.

```python
ax.contour3D(X, Y, Z, 30, cmap='inferno')
```

### 3D Bar

`ax.bar3d(x, y, z, dx, dy, dz, color=None, alpha=None)`: draws 3D bars anchored at `(x, y, z)` with sizes `(dx, dy, dz)`.

```python
xpos = np.arange(4)
ypos = np.arange(4)
xpos, ypos = np.meshgrid(xpos, ypos)
xpos = xpos.flatten()
ypos = ypos.flatten()
zpos = np.zeros_like(xpos)
dz = np.random.rand(16) * 5

ax.bar3d(xpos, ypos, zpos, 0.8, 0.8, dz, cmap='viridis')
```

### Viewing Angle

`ax.view_init(elev=None, azim=None, roll=None)`: sets the camera elevation and azimuth angles.

```python
ax.view_init(elev=30, azim=135)   # 30° elevation, 135° azimuth
```

---

## Animation

`matplotlib.animation.FuncAnimation(fig, func, frames=None, init_func=None, interval=200, blit=False, repeat=True, repeat_delay=0)`: creates an animation by repeatedly calling `func`.

- `fig`: the Figure object.
- `func`: callable `func(frame, *fargs)` — updates the artists and returns an iterable of modified artists (required when `blit=True`).
- `frames`: iterable, integer, or `None` — determines what is passed to `func`. If an integer, frames `0..N-1` are passed.
- `init_func`: function that draws the initial frame (called once before animation starts).
- `interval`: delay between frames in milliseconds.
- `blit`: if `True`, only re-draws changed artists (faster). Requires `func` to return an iterable of artists.

```python
fig, ax = plt.subplots()
x = np.linspace(0, 2 * np.pi, 200)
line, = ax.plot(x, np.sin(x))
ax.set_ylim(-1.2, 1.2)

def update(frame):
    line.set_ydata(np.sin(x + frame / 20))
    return (line,)

ani = animation.FuncAnimation(fig, update, frames=120,
                               interval=40, blit=True)

# Save to file (requires ffmpeg or Pillow)
ani.save('animation.gif', writer='pillow', fps=25)
ani.save('animation.mp4', writer='ffmpeg', fps=25, dpi=150)

plt.show()
```

---

## Exporting & Saving

`plt.savefig(fname, dpi=None, format=None, bbox_inches=None, transparent=False, pad_inches=0.1, facecolor='auto', edgecolor='auto', metadata=None)`: saves the current figure.

- `fname`: file path — the extension determines the format (`png`, `pdf`, `svg`, `eps`, `jpg`, `tiff`).
- `dpi`: output resolution in dots per inch. Use `300` for print quality.
- `format`: explicit format string — overrides file extension.
- `bbox_inches`: `'tight'` crops the figure to the tightest bounding box around all elements. Recommended to avoid clipping labels.
- `transparent`: if `True`, the figure and axes backgrounds are transparent (useful for PNGs that overlay other content).
- `pad_inches`: padding around the figure when `bbox_inches='tight'`.
- `facecolor`: figure background colour override.

```python
# Standard high-resolution PNG
fig.savefig("figure.png", dpi=300, bbox_inches='tight')

# Transparent background
fig.savefig("overlay.png", dpi=150, bbox_inches='tight', transparent=True)

# Vector PDF (resolution-independent)
fig.savefig("figure.pdf", bbox_inches='tight')

# SVG for web use
fig.savefig("figure.svg", format='svg', bbox_inches='tight')

# Save all open figures to a single multi-page PDF
from matplotlib.backends.backend_pdf import PdfPages

with PdfPages("all_plots.pdf") as pdf:
    for fig in map(plt.figure, plt.get_fignums()):
        pdf.savefig(fig, bbox_inches='tight')
```

---

## Showing & Managing Plots

- `plt.show()`: displays all open figure windows. Blocks execution until they are closed (in non-interactive environments).
- `plt.close(fig=None)`: closes the specified figure. Passing `'all'` closes every open figure.
- `plt.draw()`: re-draws the current figure without blocking.
- `plt.ion()` / `plt.ioff()`: enables / disables interactive mode (plots update automatically after each command).

```python
plt.show()
plt.close('all')

plt.ion()          # turn on interactive mode
ax.plot(x, y)      # updates display immediately
plt.ioff()         # turn off interactive mode
```

---

## Seaborn Integration

Seaborn is a higher-level statistical plotting library built on top of Matplotlib. All Seaborn plots return or operate on Matplotlib `Axes` objects, so full Matplotlib 
customisation is available after calling Seaborn functions.

```python
import seaborn as sns

# Set Seaborn theme and context
sns.set_theme(style='whitegrid', palette='tab10')
sns.set_context('paper', font_scale=1.2)   # 'paper', 'notebook', 'talk', 'poster'

tips = sns.load_dataset('tips')

# Combine Seaborn plot with Matplotlib customisation
fig, ax = plt.subplots(figsize=(8, 5))
sns.scatterplot(data=tips, x='total_bill', y='tip', hue='sex',
                size='size', sizes=(20, 200), alpha=0.7, ax=ax)
ax.set_title("Tips vs Total Bill")
ax.axline((0, 0), slope=0.2, color='grey', linestyle='--', label='20% tip')
ax.legend(title='Sex')
plt.tight_layout()
plt.show()
```

---

## Quick Reference: Common Patterns

```python
# ── Minimal one-liner ─────────────────────────────────────────────────────────
plt.plot(x, y); plt.show()

# ── Standard template ─────────────────────────────────────────────────────────
fig, ax = plt.subplots(figsize=(8, 5))
ax.plot(x, y, color='steelblue', linewidth=2, label='Data')
ax.set_title("Title",  fontsize=14)
ax.set_xlabel("X Label"); ax.set_ylabel("Y Label")
ax.legend(); ax.grid(True, alpha=0.4)
plt.tight_layout(); plt.savefig("out.png", dpi=150, bbox_inches='tight')
plt.show()

# ── Side-by-side comparison ───────────────────────────────────────────────────
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 4))
ax1.hist(data_a, bins=30, alpha=0.7); ax1.set_title("Distribution A")
ax2.hist(data_b, bins=30, alpha=0.7); ax2.set_title("Distribution B")
plt.tight_layout(); plt.show()

# ── Scatter with colorbar ─────────────────────────────────────────────────────
fig, ax = plt.subplots()
sc = ax.scatter(x, y, c=z, cmap='viridis', alpha=0.8, edgecolors='none')
plt.colorbar(sc, ax=ax, label='z')
plt.show()

# ── Annotate a specific point ─────────────────────────────────────────────────
idx = np.argmax(y)
ax.annotate(f'max={y[idx]:.2f}', xy=(x[idx], y[idx]),
            xytext=(x[idx]+0.5, y[idx]-0.2),
            arrowprops={'arrowstyle': '->'})

# ── Log scale with minor grid ─────────────────────────────────────────────────
ax.set_yscale('log')
ax.yaxis.set_minor_locator(plt.LogLocator(subs='all'))
ax.grid(True, which='both', alpha=0.3)

# ── Reuse style across a project ──────────────────────────────────────────────
plt.rcParams.update({
    'figure.figsize':  [8, 5],
    'font.size':       12,
    'axes.grid':       True,
    'grid.alpha':      0.4,
    'lines.linewidth': 2,
})
```

--- 

## Interactive Plots 

We can also animate our plots with interactive parameters using the API provided by this library.


```py 
import numpy as np
from matplotlib import pyplot as plt
from numpy.polynomial import Polynomial

# ---------------------------------------------------- 

def get_target_function():
    return Polynomial((1, 2, -1, -2))


def get_data(sigma=0, N=5):
    np.random.seed(3)
    p = Polynomial((1, 2, -1, -2))
    x = np.sort(np.random.random_sample(size=N) * 2 - 1)
    noise = np.random.standard_normal(len(x))
    return x, p(x) + noise * sigma

def phi4(x):
    return np.array([x, x**2, x**3, x**4])

def get_final_g(x, w):
    return w[0] + w[1]* x

def lin_reg(X, lamb):
    n_samples, m_features = X.shape
    ones = np.ones(n_samples)
    X_t = np.column_stack((ones, X))
    Z = X_t.T @ X_t
    return np.linalg.inv(Z + lamb * np.eye(Z.shape[0])) @ X_t.T @ y 

# ---------------------------------------------------- 

X, y = get_data(N=6, sigma=.2)

from ipywidgets import interact
import ipywidgets as widgets
@interact(lamb=widgets.FloatSlider(min=0,max=1.5,step=0.1,value=0))
def showPlot(lamb):
    
    X_t = np.array([phi4(x) for x in X])
    w = lin_reg(X_t, lamb)
    y_plot = [get_final_g(x, w) for x in X]

    plt.scatter(X, y)
    plt.plot(X, y_plot, color="red")
    plt.grid()
    plt.xlabel("x")
    plt.ylabel("y")
    plt.ylim(-1, 2)
    plt.title("Title")

```
