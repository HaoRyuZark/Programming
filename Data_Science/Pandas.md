# Pandas

Library for working with tabular data, which uses numpy under the hood, this means that all of the numpy 
functionality like broadcasting, indexing, etc. are also valid pandas syntax.

## Import

```python
import pandas as pd
import numpy as np
```

---

## Pandas Data Structures

Pandas has two primary data structures: **Series** (1D) and **DataFrame** (2D).

### Series

A one-dimensional labeled array (label + data) that can hold any data type. 

#### Attributes

- `s.index`: the index (row labels) of the Series.
- `s.values`: the underlying NumPy array of values.
- `s.dtype`: data type of the elements.
- `s.name`: name of the Series.
- `s.shape`: tuple with the shape (n,).
- `s.size`: total number of elements.
- `s.is_unique`: `True` if all values are unique.

```python
s = pd.Series([10, 20, 30, 40], index=["a", "b", "c", "d"], name="scores")

print(s.index)     # Index(['a', 'b', 'c', 'd'], dtype='object')
print(s.values)    # [10 20 30 40]
print(s.dtype)     # int64
print(s.name)      # scores
print(s.shape)     # (4,)
print(s.size)      # 4

# Access elements
print(s["b"])      # 20 — by label
print(s[1])        # 20 — by position
print(s[["a","c"]]) # multiple labels
```

### DataFrame

A two-dimensional labeled data structure — essentially a table with rows and columns, each column being a Series sharing the same index.

- `pd.DataFrame(data=None, index=None, columns=None, dtype=None, copy=None)`: creates a DataFrame object
    - `data`: object (dict, list, ndarray, etc.) containing the data.
    - `index`: default normal array-index, but it can be modified to be letters or other **labels**.
    - `columns`: column labels set at the insertion order.
    - `dtype`: numerical data type.
    - `copy`: Flag for copying data from the input.

#### Attributes

- `df.index`: row labels.
- `df.columns`: column labels.
- `df.values`: the underlying 2D NumPy array.
- `df.dtypes`: data type of each column.
- `df.shape`: tuple `(rows, columns)`.
- `df.size`: total number of elements.
- `df.ndim`: number of dimensions (always 2).
- `df.empty`: `True` if the DataFrame has no items.

```python
df = pd.DataFrame({
    "Name":   ["Alice", "Bob", "Carol"],
    "Age":    [30, 25, 35],
    "Score":  [95.5, 87.2, 92.0]
})

print(df.index)     # RangeIndex(start=0, stop=3, step=1)
print(df.columns)   # Index(['Name', 'Age', 'Score'], dtype='object')
print(df.dtypes)
print(df.shape)     # (3, 3)
print(df.ndim)      # 2
```

### Axis

- `axis=0`: acts along rows (default for most operations).
- `axis=1`: acts along columns.

```python
df.sum(axis=0)  # sum of each column
df.sum(axis=1)  # sum of each row
```

---

## Creating Series & DataFrames

- `pd.Series(data, index=None, dtype=None, name=None)`: creates a 1D labeled array.
  - `data`: array-like, dict, or scalar value.
  - `index`: labels for the data. Defaults to `RangeIndex`.
  - `dtype`: forced data type.
  - `name`: name assigned to the Series.

- `pd.DataFrame(data, index=None, columns=None, dtype=None)`: creates a 2D labeled table.
  - `data`: dict of lists, list of dicts, 2D NumPy array, or another DataFrame.
  - `index`: row labels.
  - `columns`: column labels (used to select or reorder columns when `data` is a dict).
  - `dtype`: forced data type for all columns.

```python
# Series
s1 = pd.Series([1, 2, 3])                                          # default index 0,1,2
s2 = pd.Series({"a": 10, "b": 20, "c": 30})                        # from dict
s3 = pd.Series(5, index=range(4), name="const")                    # scalar broadcast

# DataFrame from dict of lists
df1 = pd.DataFrame({"Name": ["Alice", "Bob"], "Age": [30, 25]})

# DataFrame from list of dicts
df2 = pd.DataFrame([{"Name": "Alice", "Age": 30}, {"Name": "Bob", "Age": 25}])

# DataFrame from NumPy array
df3 = pd.DataFrame(np.arange(9).reshape(3, 3), columns=["A", "B", "C"])

# DataFrame from another DataFrame (copy)
df4 = pd.DataFrame(df1)
```

---

## Reading Data

- `pd.read_csv(filepath, sep=',', header='infer', index_col=None, usecols=None, dtype=None, nrows=None, skiprows=None, na_values=None, parse_dates=False, encoding='utf-8')`: reads a CSV file into a DataFrame.
  - `filepath`: path to the file or URL.
  - `sep`: delimiter character (use `\t` for TSV files).
  - `header`: row number to use as column names (default `'infer'`).
  - `index_col`: column(s) to use as the row index.
  - `usecols`: list of column names or indices to read — avoids loading unwanted columns.
  - `dtype`: dict mapping column names to data types.
  - `nrows`: number of rows to read — useful for sampling large files.
  - `skiprows`: number of rows or list of row indices to skip.
  - `na_values`: additional strings to recognize as NaN.
  - `parse_dates`: list of columns to parse as datetime.

- `pd.read_excel(io, sheet_name=0, header=0, index_col=None, usecols=None, dtype=None)`: reads an Excel file.
  - `io`: path or URL to the Excel file.
  - `sheet_name`: sheet name, index, or list. Use `None` to read all sheets as a dict.
  - `header`: row number to use as column names.
  - `usecols`: columns to read (e.g., `"A:C"` or a list of names).

- `pd.read_parquet(path, engine='auto', columns=None)`: reads a Parquet file (efficient columnar format).
  - `path`: path to the file.
  - `columns`: list of columns to load.

- `pd.read_json(path_or_buf, orient=None, dtype=True, lines=False)`: reads a JSON file or string.
  - `path_or_buf`: path, URL, or JSON string.
  - `orient`: format of the JSON — `'records'`, `'split'`, `'index'`, `'columns'`, `'values'`.
  - `lines`: if `True`, reads a JSON Lines file (one JSON object per line).

- `pd.read_html(io, match='.+', header=None, index_col=None)`: reads HTML tables from a URL or file.
  - `io`: URL, file path, or HTML string.
  - `match`: string or regex — only returns tables containing this pattern.
  - Returns a **list** of DataFrames (one per table found).

- `pd.read_sql(sql, con, index_col=None, parse_dates=None)`: reads SQL query result into a DataFrame.
  - `sql`: SQL query string or table name.
  - `con`: database connection object (e.g., SQLAlchemy engine).

```python
df = pd.read_csv("data.csv")
df = pd.read_csv("data.csv", sep="\t", usecols=["Name", "Age"], nrows=100)
df = pd.read_csv("data.csv", dtype={"Age": "int32"}, parse_dates=["Date"])

df = pd.read_excel("data.xlsx", sheet_name="Sheet1")
df = pd.read_excel("data.xlsx", sheet_name=None)    # dict of all sheets

df = pd.read_parquet("data.parquet", columns=["Name", "Score"])

df = pd.read_json("data.json", orient="records")

tables = pd.read_html("https://example.com/table.html")
df = tables[0]                                          # first table
df = pd.read_html("https://example.com", match="Revenue")[0]  # table containing "Revenue"
```

---

## Writing & Exporting Data

- `df.to_csv(path_or_buf, sep=',', index=True, header=True, columns=None, encoding='utf-8')`: writes a DataFrame to a CSV file.
  - `path_or_buf`: file path or buffer. If `None`, returns a string.
  - `sep`: field delimiter.
  - `index`: if `False`, the row index is not written.
  - `header`: if `False`, column names are not written.
  - `columns`: list of columns to write.

- `df.to_excel(excel_writer, sheet_name='Sheet1', index=True, header=True, startrow=0, startcol=0)`: writes to an Excel file.
  - `excel_writer`: path or ExcelWriter object (use ExcelWriter to write multiple sheets).
  - `sheet_name`: name of the target sheet.

- `df.to_json(path_or_buf, orient=None, lines=False, indent=None)`: writes to a JSON file.
  - `orient`: output format — `'records'`, `'split'`, `'index'`, `'columns'`, `'values'`.
  - `lines`: if `True`, writes one JSON object per line.

- `df.to_parquet(path, engine='auto', index=True, compression='snappy')`: writes to a Parquet file.
  - `path`: output file path.
  - `compression`: `'snappy'`, `'gzip'`, `'brotli'`, or `None`.

- `df.to_sql(name, con, schema=None, if_exists='fail', index=True, chunksize=None)`: writes to a SQL table.
  - `name`: SQL table name.
  - `con`: SQLAlchemy connection.
  - `if_exists`: action if the table already exists — `'fail'`, `'replace'`, `'append'`.

```python
df.to_csv("output.csv", index=False)
df.to_csv("output.tsv", sep="\t", index=False)

df.to_excel("output.xlsx", sheet_name="Results", index=False)

# Multiple sheets
with pd.ExcelWriter("output.xlsx") as writer:
    df.to_excel(writer, sheet_name="Data", index=False)
    df.describe().to_excel(writer, sheet_name="Stats")

df.to_json("output.json", orient="records", indent=2)
df.to_parquet("output.parquet", compression="gzip")
```

---

## Inspecting Data

- `df.head(n=5)`: returns the first `n` rows.
  - `n`: number of rows to return.

- `df.tail(n=5)`: returns the last `n` rows.
  - `n`: number of rows to return.

- `df.sample(n=None, frac=None, replace=False, random_state=None)`: returns a random sample of rows.
  - `n`: number of rows to sample.
  - `frac`: fraction of rows to sample (e.g., `0.1` for 10%).
  - `replace`: whether sampling is with replacement.
  - `random_state`: seed for reproducibility.

- `df.info(verbose=True, memory_usage=True)`: prints a concise summary of the DataFrame (column names, dtypes, non-null counts, memory usage).
  - `verbose`: if `True`, shows full column list.
  - `memory_usage`: includes memory usage in the output.

- `df.describe(percentiles=None, include=None, exclude=None)`: generates descriptive statistics.
  - `percentiles`: list of percentiles to include (default `[0.25, 0.5, 0.75]`).
  - `include`: dtypes to include — `'all'` to include object columns.
  - `exclude`: dtypes to exclude.

- `df.nunique(axis=0, dropna=True)`: counts unique values per column (or row).
  - `axis`: `0` for columns, `1` for rows.
  - `dropna`: if `True`, NaN values are not counted.

- `df.value_counts(subset=None, normalize=False, sort=True, dropna=True)`: counts occurrences of unique rows (or use on a Series for value frequency).
  - `subset`: columns to consider.
  - `normalize`: if `True`, returns relative frequencies instead of counts.

- `df.memory_usage(index=True, deep=False)`: returns memory usage per column in bytes.
  - `deep`: if `True`, introspects object dtypes for actual memory usage.

```python
print(df.head())             # first 5 rows
print(df.tail(3))            # last 3 rows
print(df.sample(5, random_state=42))  # 5 random rows

print(df.info())             # dtype, non-null count, memory
print(df.describe())         # count, mean, std, min, percentiles, max
print(df.describe(include="all"))  # also includes object columns

print(df.columns.tolist())   # list of column names
print(df.index)              # index info
print(df.shape)              # (rows, cols)
print(df.dtypes)             # dtype per column
print(df.nunique())          # unique values per column
print(df["Name"].value_counts())  # frequency of each value in a column
print(df.memory_usage(deep=True))
```

---

## Selecting Data

### `loc` and `iloc`

- `df.loc[row_label, col_label]`: label-based selection. Accepts labels for row and columns in the format `[row_labels, col_labels]`, slices, boolean arrays, and callables. The stop in a slice is **inclusive**.
  - `row_label`: row index label, slice, or list of labels.
  - `col_label`: column name, slice, or list of column names.

- `df.iloc[row_pos, col_pos]`: position-based selection. Accepts integers, slices, and lists of integers. The stop in a slice is **exclusive**.
  - `row_pos`: integer position, slice, or list.
  - `col_pos`: integer position, slice, or list.

- `df.at[row_label, col_label]`: fast scalar access by label (single cell).

- `df.iat[row_pos, col_pos]`: fast scalar access by position (single cell).

> **Key difference**: if you sort the DataFrame, the original index labels stay with their rows. `loc` uses those labels as keys, while `iloc` always uses the physical row position regardless of the index.

```python
df = pd.DataFrame({
    "Name":  ["Alice", "Bob", "Carol", "Dave"],
    "Age":   [30, 25, 35, 28],
    "Score": [95.5, 87.2, 92.0, 78.4]
}, index=["a", "b", "c", "d"])

# loc — by label
print(df.loc["a"])                        # row with label "a"
print(df.loc["a":"c"])                    # rows a to c (inclusive)
print(df.loc["a", "Name"])               # single cell by label
print(df.loc[["a", "c"], ["Name", "Score"]])  # subset

# iloc — by position
print(df.iloc[0])                         # first row
print(df.iloc[0:2])                       # rows 0 and 1
print(df.iloc[0, 1])                      # cell at row 0, col 1
print(df.iloc[:, 0:2])                    # all rows, first two columns
print(df.iloc[[0, 2], [0, 2]])            # rows 0&2, cols 0&2

# Fast scalar access
print(df.at["a", "Score"])               # 95.5
print(df.iat[0, 2])                      # 95.5

# Selecting columns
print(df["Name"])                         # single column → Series
print(df[["Name", "Score"]])             # multiple columns → DataFrame
```

### Iterating 

You can use the following syntax at the cost of performance for iterating over the data: 

```python 

for index, row in df.iterrows():
    print(index)
    print(row)
    print("\n")

```

---

## Boolean Indexing & Filtering

- `df[condition]`: returns rows where `condition` is `True`. The condition must be a boolean Series with the same index.

- `df.query(expr, inplace=False)`: filters rows using a query string expression.
  - `expr`: string expression (e.g., `"Age > 25 and Score > 90"`). Use backticks for column names with spaces.
  - `inplace`: if `True`, modifies the DataFrame in place.

- `s.isin(values)`: returns a boolean Series indicating whether each element is in `values`.
  - `values`: list, set, or Series of values to check against.

- `s.between(left, right, inclusive='both')`: returns a boolean Series for values within a range.
  - `left`, `right`: lower and upper bounds.
  - `inclusive`: which bounds are included — `'both'`, `'neither'`, `'left'`, `'right'`.

- `s.str.contains(pat, case=True, na=False, regex=True)`: returns boolean Series where each element contains the pattern.
  - `pat`: substring or regex pattern.
  - `case`: if `False`, case-insensitive match.
  - `na`: value to use for missing entries.
  - `regex`: if `True`, `pat` is treated as a regular expression.

- `df.isnull()` / `df.isna()`: returns a boolean DataFrame with `True` where values are NaN.

- `df.notnull()` / `df.notna()`: returns a boolean DataFrame with `True` where values are not NaN.

```python
# Single condition
print(df[df["Age"] > 25])

# Multiple conditions — use & (and), | (or), ~ (not), with parentheses
print(df[(df["Age"] > 25) & (df["Score"] > 90)])
print(df[(df["Age"] < 25) | (df["Score"] > 90)])
print(df[~df["Name"].str.contains("Alice")])

# isin
print(df[df["Name"].isin(["Alice", "Carol"])])

# between
print(df[df["Score"].between(85, 95)])

# query syntax (cleaner for complex conditions)
print(df.query("Age > 25 and Score > 90"))
print(df.query("`Score` > 90"))  # backticks for columns with spaces

# Null filtering
print(df[df["Score"].isnull()])
print(df[df["Score"].notnull()])
```

---

## Sorting

- `df.sort_values(by, axis=0, ascending=True, inplace=False, na_position='last', kind='quicksort')`: sorts by one or more columns.
  - `by`: column name or list of column names to sort by.
  - `axis`: `0` to sort rows by column values, `1` to sort columns by row values.
  - `ascending`: `True` for ascending, `False` for descending. Can be a list matching `by`.
  - `na_position`: `'first'` or `'last'` — where to place NaN values.
  - `kind`: sorting algorithm — `'quicksort'`, `'mergesort'`, `'heapsort'`, `'stable'`.

- `df.sort_index(axis=0, ascending=True, inplace=False)`: sorts by the index.
  - `axis`: `0` to sort row index, `1` to sort column index.

- `s.rank(method='average', ascending=True, na_option='keep')`: assigns ranks to each element.
  - `method`: how to handle ties — `'average'`, `'min'`, `'max'`, `'first'`, `'dense'`.
  - `ascending`: if `False`, highest value gets rank 1.
  - `na_option`: `'keep'` (NaN stays NaN), `'top'`, or `'bottom'`.

```python
df.sort_values("Age")                                  # ascending by Age
df.sort_values("Age", ascending=False)                 # descending
df.sort_values(["Score", "Age"], ascending=[False, True])  # multi-column sort
df.sort_values("Score", na_position="first")           # NaN values first

df.sort_index()                                        # sort by row index
df.sort_index(axis=1)                                  # sort column names alphabetically

df["Rank"] = df["Score"].rank(method="dense", ascending=False)
```

---

## Adding & Modifying Columns

```python
df["Total"] = df["Attack"] + df["Defense"]               # new column from arithmetic
df["Total"] = df.iloc[:, 2:5].sum(axis=1)                # row-wise sum of a range

df["Category"] = "Standard"                              # constant fill

df["Name_len"] = df["Name"].apply(len)                   # apply a function

# assign() — returns a new DataFrame, chaining friendly
df = df.assign(
    Ratio=lambda x: x["Attack"] / x["Defense"],
    Flag=lambda x: x["Score"] > 90
)

# pd.cut — bin continuous values into intervals with custom edges
df["AgeGroup"] = pd.cut(
    df["Age"],
    bins=[0, 12, 20, 40, 60, 80],
    labels=["Child", "Teen", "Adult", "Mid-Age", "Senior"]
)

# pd.qcut — bin into quantile-based buckets (equal-frequency bins)
df["ScoreBin"] = pd.qcut(df["Score"], q=4, labels=False, duplicates="drop")

# Rename columns
df.rename(columns={"OldName": "NewName", "A": "B"}, inplace=True)
df.columns = ["col1", "col2", "col3"]                    # rename all at once
df.columns = df.columns.str.lower().str.replace(" ", "_")  # normalize names

# Reorder columns
df = df[["Name", "Score", "Age"]]
df = df[["Name"] + [c for c in df.columns if c != "Name"]]  # Name first

# Split a column into multiple
df[["Street", "City", "Zip"]] = df["Address"].str.split(",", expand=True)

# Map values
df["Gender"] = df["Gender"].map({"M": "Male", "F": "Female"})
```

---

## Removing Columns & Rows

- `df.drop(labels=None, axis=0, index=None, columns=None, inplace=False, errors='raise')`: removes rows or columns.
  - `labels`: index label(s) or column name(s) to drop.
  - `axis`: `0` for rows, `1` for columns.
  - `columns`: shortcut to drop columns without specifying `axis=1`.
  - `index`: shortcut to drop rows without specifying `axis=0`.
  - `inplace`: if `True`, modifies the DataFrame in place.
  - `errors`: `'raise'` (raises error if label not found) or `'ignore'`.

- `df.reset_index(drop=False, inplace=False)`: resets the row index to the default RangeIndex.
  - `drop`: if `True`, the old index is discarded; if `False`, it becomes a column.

```python
df.drop(columns=["Unwanted", "Debug"], errors="ignore")  # remove columns
df.drop(index=0)                                          # remove row with label 0
df.drop(index=[0, 2, 4])                                  # remove multiple rows

# Filter rows (non-destructive)
df = df[df["Score"] >= 50]                                # keep rows where Score >= 50
df = df[~df["Name"].str.contains("Test")]                 # remove rows matching pattern

# Remove by condition on index
df.drop(index=df[df["Score"] < 50].index, inplace=True)

# Remove duplicates
df = df.drop_duplicates()
df = df.drop_duplicates(subset=["Name"])                  # based on specific columns

# Reset index after dropping rows
df = df.reset_index(drop=True)
```

---

## Data Cleaning

- `df.dropna(axis=0, how='any', thresh=None, subset=None, inplace=False)`: removes rows (or columns) with missing values.
  - `axis`: `0` to drop rows, `1` to drop columns.
  - `how`: `'any'` (drop if any NaN) or `'all'` (drop only if all values are NaN).
  - `thresh`: minimum number of non-NaN values required to keep the row/column.
  - `subset`: column(s) to check for NaN when `axis=0`.

- `df.fillna(value=None, method=None, axis=None, inplace=False, limit=None)`: fills missing values.
  - `value`: scalar, dict, Series, or DataFrame used to fill NaN.
  - `method`: `'ffill'` (forward fill) or `'bfill'` (backward fill).
  - `limit`: maximum number of consecutive NaN values to fill.

- `df.replace(to_replace, value=None, inplace=False, regex=False)`: replaces values.
  - `to_replace`: scalar, list, dict, or regex pattern of values to replace.
  - `value`: replacement value. If a dict is passed to `to_replace`, `value` can be omitted.
  - `regex`: if `True`, `to_replace` is interpreted as a regex.

- `df.duplicated(subset=None, keep='first')`: returns a boolean Series indicating duplicate rows.
  - `subset`: column(s) to check for duplicates.
  - `keep`: which occurrence to mark as not-duplicate — `'first'`, `'last'`, or `False` (marks all).

- `df.astype(dtype, errors='raise')`: casts columns to a specified data type.
  - `dtype`: data type or dict mapping column names to target types.
  - `errors`: `'raise'` or `'ignore'`.

- `df.convert_dtypes()`: converts columns to the best possible nullable dtypes automatically (e.g., `Int64` instead of `float64` for integers with NaN).

- `df.clip(lower=None, upper=None, axis=None, inplace=False)`: limits values to a specified range.
  - `lower`: minimum value. Values below this are set to `lower`.
  - `upper`: maximum value. Values above this are set to `upper`.

-  `df["col"].interpolate(method='linear', limit_direction='forward', inplace=False)`: fills NaN values using interpolation.
   - `method`: interpolation method — `'linear'`, `'time'`, `'index'`, etc.
   - `limit_direction`: direction to fill — `'forward'`, `'backward'`, or `'both'`.

```python
# Remove rows with any missing value
df = df.dropna()

# Remove rows where specific columns are NaN
df = df.dropna(subset=["Name", "Age"])

# Drop columns with more than 50% missing
df = df.dropna(axis=1, thresh=int(0.5 * len(df)))

# Fill NaN with a constant
df = df.fillna(0)
df["Age"] = df["Age"].fillna(df["Age"].median())         # fill with median
df["Score"] = df["Score"].fillna(method="ffill")         # forward fill

# Replace values
df = df.replace({"Unknown": np.nan, "N/A": np.nan})
df["Col"] = df["Col"].replace(r"\s+", "_", regex=True)

# Check & remove duplicates
print(df.duplicated().sum())                             # count duplicates
df = df.drop_duplicates()

# Strip whitespace from string columns
df["Name"] = df["Name"].str.strip()

# Remove unnamed columns (common when reading CSVs with an unnamed index column)
df = df.loc[:, ~df.columns.str.contains("^Unnamed")]

# Remove duplicate columns
df = df.loc[:, ~df.columns.duplicated()]

# Type casting
df = df.astype({"Age": "int32", "Score": "float32"})
df = df.convert_dtypes()

# Clip outliers
df["Score"] = df["Score"].clip(lower=0, upper=100)
```

---

## String Operations (`str` Accessor)

The `str` accessor exposes vectorized string methods on a Series of object dtype.

- `s.str.lower()` / `s.str.upper()` / `s.str.title()`: case conversion.
- `s.str.strip(to_strip=None)` / `s.str.lstrip()` / `s.str.rstrip()`: removes leading/trailing characters.
  - `to_strip`: characters to remove (default strips whitespace).
- `s.str.replace(pat, repl, n=-1, case=None, regex=True)`: replaces occurrences of a pattern.
  - `pat`: substring or regex pattern.
  - `repl`: replacement string.
  - `n`: maximum number of replacements per element.
  - `regex`: if `True`, treats `pat` as a regex.
- `s.str.split(pat=None, n=-1, expand=False)`: splits each string.
  - `pat`: delimiter string or regex.
  - `n`: maximum number of splits.
  - `expand`: if `True`, returns a DataFrame with one column per split piece.
- `s.str.contains(pat, case=True, na=False, regex=True)`: boolean mask of matching elements.
- `s.str.startswith(pat)` / `s.str.endswith(pat)`: boolean mask for prefix/suffix matches.
- `s.str.len()`: length of each string element.
- `s.str.get(i)` / `s.str[i]`: returns the element at index `i` of each string.
- `s.str.zfill(width)`: pads with leading zeros up to `width`.
- `s.str.extract(pat, flags=0, expand=True)`: extracts groups from a regex pattern.
  - `pat`: regex pattern with at least one capture group.
  - `expand`: if `True`, returns a DataFrame; if `False`, returns a Series when there is one group.

```python
s = pd.Series(["  Alice Smith ", "BOB jones", "carol O'Brien"])

print(s.str.strip())                           # remove whitespace
print(s.str.lower())                           # lowercase
print(s.str.title())                           # title case
print(s.str.replace(r"\s+", "_", regex=True)) # spaces to underscores
print(s.str.len())                             # character count

# Split name into first and last
names = s.str.strip().str.split(r"\s+", expand=True)
names.columns = ["First", "Last"]

# Pattern matching
print(s.str.contains("bob", case=False))      # case-insensitive match
print(s.str.startswith("  "))                 # starts with whitespace

# Extract with regex groups
df["Year"] = df["Date_str"].str.extract(r"(\d{4})", expand=False)

# Phone number formatting example
df["Phone"] = (df["Phone"]
               .str.replace(r"[^0-9]", "", regex=True)   # keep only digits
               .str.zfill(10))                             # pad to 10 digits
```

---

## Apply & Map

- `df.apply(func, axis=0, raw=False, result_type=None, args=())`: applies a function along an axis.
  - `func`: function to apply. Receives a Series (column or row) and returns a scalar or Series.
  - `axis`: `0` to apply function to each column, `1` to apply to each row.
  - `raw`: if `True`, passes a NumPy array instead of a Series (faster for element-wise ops).

- `s.apply(func, convert_dtype=True, args=())`: applies a function element-wise to a Series.
  - `func`: a callable that takes a scalar and returns a scalar.

- `s.map(arg, na_action=None)`: maps values element-wise using a dict, Series, or function.
  - `arg`: a dict, Series, or function defining the mapping.
  - `na_action`: if `'ignore'`, NaN values are not passed to the function.

- `df.applymap(func)` (deprecated in pandas 2.1+ — use `df.map(func)` instead): applies a function element-wise to every cell in a DataFrame.
  - `func`: a callable that takes a scalar and returns a scalar.

```python
# Apply to rows (axis=1)
def classify(row):
    return "Strong" if row["Score"] > 90 else "Weak"

df["Category"] = df.apply(classify, axis=1)

# Apply to columns (axis=0)
print(df.apply(lambda col: col.max() - col.min(), axis=0))  # range per column

# Series apply
df["Name_len"] = df["Name"].apply(len)
df["Name_upper"] = df["Name"].apply(str.upper)

# map — best for simple value substitution
df["Gender"] = df["Gender"].map({"M": "Male", "F": "Female"})

# Element-wise on entire DataFrame (pandas 2.1+)
df_numeric = df.select_dtypes(include="number")
print(df_numeric.map(lambda x: round(x, 2)))
```

---

## GroupBy & Aggregations

- `df.groupby(by, axis=0, sort=True, dropna=True)`: groups the DataFrame by one or more columns.
  - `by`: column name, list of column names, or a function.
  - `sort`: if `True`, sort group keys.
  - `dropna`: if `True`, groups with NaN keys are excluded.

- `groupby_obj.agg(func)`: aggregates groups using one or more functions.
  - `func`: function, string alias (e.g., `'mean'`), list, or dict mapping column names to aggregations.

- `groupby_obj.transform(func)`: applies a function to each group and returns a result with the **same shape** as the input (useful for group-level normalization).
  - `func`: a function or string alias.

- `groupby_obj.filter(func)`: returns rows from groups where `func` returns `True`.
  - `func`: a function that takes a group DataFrame and returns a boolean.

- `values_counts()`: counts occurrences of unique values in a Series (can be used on groupby objects to count within groups).


```python
# Basic aggregation
print(df.groupby("Category").mean(numeric_only=True))
print(df.groupby("Category")["Score"].count())
print(df.groupby("Category").size())              # number of rows per group

# Multiple aggregations per column
result = df.groupby("Category").agg({
    "Score":  ["mean", "max", "std"],
    "Age":    "median",
    "Name":   "count"
})

# Named aggregations (cleaner column names)
result = df.groupby("Category").agg(
    Score_mean=("Score", "mean"),
    Score_max=("Score", "max"),
    Age_median=("Age", "median"),
    Count=("Name", "count")
)

# Multi-column groupby
print(df.groupby(["Category", "Gender"]).size())

# transform — group-level Z-score (result keeps original shape)
df["Score_zscore"] = df.groupby("Category")["Score"].transform(
    lambda s: (s - s.mean()) / s.std()
)

# filter — keep only groups with more than 10 members
df_filtered = df.groupby("Category").filter(lambda g: len(g) > 10)
```

---

## Merging, Joining & Concatenation

The **join-operations** behave like SQL, while **merge** works like a database join. The **concat** function is more general and can
be used for simple stacking of DataFrames.

- `pd.merge(left, right, how='inner', on=None, left_on=None, right_on=None, left_index=False, right_index=False, suffixes=('_x', '_y'))`: merges two DataFrames 
(SQL-style join).
  - `left`, `right`: DataFrames to merge.
  - `how`: join type — `'inner'`, `'outer'`, `'left'`, `'right'`, `'cross'`.
  - `on`: column(s) to join on (must exist in both DataFrames).
  - `left_on` / `right_on`: column(s) in left/right to join on (when key names differ).
  - `left_index` / `right_index`: if `True`, use the index of the left/right DataFrame as the join key.
  - `suffixes`: suffixes added to overlapping column names.

- `df.join(other, on=None, how='left', lsuffix='', rsuffix='', sort=False)`: joins on the index by default.
  - `other`: DataFrame or list of DataFrames.
  - `on`: column in `df` to use as the join key (joins on `other`'s index).
  - `how`: join type — `'left'`, `'right'`, `'inner'`, `'outer'`.

- `pd.concat(objs, axis=0, join='outer', ignore_index=False, keys=None)`: concatenates along an axis.
  - `objs`: list or dict of DataFrames/Series.
  - `axis`: `0` to stack rows, `1` to stack columns side by side.
  - `join`: `'outer'` (union of columns) or `'inner'` (intersection).
  - `ignore_index`: if `True`, resets the index in the result.
  - `keys`: creates a hierarchical index to track which DataFrame each row came from.

```python
df_a = pd.DataFrame({"id": [1, 2, 3], "Name": ["Alice", "Bob", "Carol"]})
df_b = pd.DataFrame({"id": [2, 3, 4], "Score": [87, 92, 74]})

# Inner join — only matching keys
merged = pd.merge(df_a, df_b, on="id", how="inner")
print(merged)  # rows with id 2 and 3

# Left join — all rows from df_a
merged_left = pd.merge(df_a, df_b, on="id", how="left")

# Join on index
df_a_idx = df_a.set_index("id")
df_b_idx = df_b.set_index("id")
joined = df_a_idx.join(df_b_idx, how="outer")

# Stack DataFrames vertically
df_all = pd.concat([df_a, df_a], ignore_index=True)

# Stack side by side
df_wide = pd.concat([df_a.set_index("id"), df_b.set_index("id")], axis=1)

# Track origin with keys
df_combined = pd.concat([df_a, df_b], keys=["source_a", "source_b"])
```

---

## Reshaping

- `df.pivot_table(values, index, columns, aggfunc='mean', fill_value=None, margins=False)`: creates a spreadsheet-style pivot table.
  - `values`: column(s) to aggregate.
  - `index`: column(s) to use as row labels.
  - `columns`: column(s) to use as column labels.
  - `aggfunc`: aggregation function(s) — e.g., `'mean'`, `'sum'`, `'count'`, or a list.
  - `fill_value`: value to replace NaN in the result.
  - `margins`: if `True`, adds row/column totals.

- `df.pivot(index, columns, values)`: reshapes without aggregation. Requires unique (index, column) pairs.
  - `index`: column to use as row index.
  - `columns`: column whose values become new column names.
  - `values`: column(s) to fill the cells.

- `df.melt(id_vars=None, value_vars=None, var_name='variable', value_name='value')`: unpivots — converts columns to rows (wide → long format).
  - `id_vars`: column(s) to keep as identifier variables.
  - `value_vars`: column(s) to unpivot. If `None`, all columns not in `id_vars` are used.
  - `var_name`: name for the variable column.
  - `value_name`: name for the value column.

- `df.stack(level=-1, dropna=True)`: pivots columns into rows (compresses inner column level into the index).
  - `level`: column level(s) to stack.

- `df.unstack(level=-1, fill_value=None)`: pivots the inner row level into columns (inverse of `stack`).
  - `level`: index level(s) to unstack.

```python
df = pd.DataFrame({
    "Name":     ["Alice", "Bob", "Alice", "Bob"],
    "Subject":  ["Math", "Math", "Science", "Science"],
    "Score":    [90, 80, 85, 78]
})

# Pivot table
pivot = df.pivot_table(values="Score", index="Name", columns="Subject", aggfunc="mean")
print(pivot)
#          Math  Science
# Alice    90.0     85.0
# Bob      80.0     78.0

# Pivot (no aggregation — requires unique pairs)
pivot2 = df.pivot(index="Name", columns="Subject", values="Score")

# Melt — long format
melted = pivot.reset_index().melt(id_vars="Name", var_name="Subject", value_name="Score")
print(melted)

# Stack and unstack
stacked = pivot.stack()       # MultiIndex Series
unstacked = stacked.unstack() # back to pivot
```

---

## Window Functions

- `s.rolling(window, min_periods=None, center=False)`: creates a rolling window view.
  - `window`: size of the window (int for fixed, offset string for time-based).
  - `min_periods`: minimum number of non-NaN observations required to produce a value.
  - `center`: if `True`, the window is centered on the current position.

- `s.expanding(min_periods=1)`: creates an expanding window (grows from start to current row).
  - `min_periods`: minimum number of observations required.

- `s.ewm(alpha=None, span=None, halflife=None, com=None, adjust=True, min_periods=0)`: exponentially weighted window.
  - `span`: defines the decay as $\alpha = \frac{2}{span + 1}$.
  - `alpha`: smoothing factor directly (between 0 and 1).
  - `adjust`: if `True`, uses weighted averages; if `False`, uses recursive formula.

```python
df["HP_roll3"] = df["HP"].rolling(3).mean()            # 3-period moving average
df["HP_roll3_min2"] = df["HP"].rolling(3, min_periods=2).mean()  # allow partials
df["HP_centered"] = df["HP"].rolling(3, center=True).mean()

df["HP_expanding"] = df["HP"].expanding().sum()        # cumulative sum
df["HP_exp"] = df["HP"].ewm(span=3).mean()             # exponential moving average

# Multiple rolling stats
df[["roll_mean", "roll_std"]] = df["HP"].rolling(5).agg(
    roll_mean=("HP", "mean"),
    roll_std=("HP", "std")
).values
```

---

## Time Series

- `pd.to_datetime(arg, format=None, errors='raise', unit=None, utc=False)`: converts argument to datetime.
  - `arg`: string, list, array, or Series.
  - `format`: strftime format string (e.g., `'%Y-%m-%d'`). Parsing is faster when specified.
  - `errors`: `'raise'`, `'coerce'` (invalid becomes NaT), or `'ignore'`.
  - `unit`: unit of numeric timestamps — `'s'`, `'ms'`, `'us'`, `'ns'`.

- `pd.date_range(start=None, end=None, periods=None, freq='D', tz=None)`: generates a fixed-frequency DatetimeIndex.
  - `start` / `end`: start and end of the range.
  - `periods`: number of periods to generate.
  - `freq`: frequency string — `'D'` (day), `'H'` (hour), `'M'` (month end), `'MS'` (month start), `'B'` (business day), `'W'` (week), `'Q'` (quarter end).

- `df.resample(rule, axis=0, closed=None, label=None)`: resamples time-series data to a different frequency (requires DatetimeIndex).
  - `rule`: offset string for the target frequency (e.g., `'M'`, `'W'`, `'Q'`).
  - `closed`: which side of each interval is closed — `'left'` or `'right'`.
  - `label`: which side to use for the interval label.

```python
# Parse dates
df["Date"] = pd.to_datetime(df["Date"], format="%Y-%m-%d")
df["Date"] = pd.to_datetime(df["Date"], errors="coerce")  # invalid → NaT

# Date range
dates = pd.date_range(start="2024-01-01", periods=12, freq="MS")  # monthly
print(dates)

# Set DatetimeIndex and resample
df = df.set_index("Date")
monthly_mean = df.resample("M").mean()
weekly_sum = df.resample("W").sum()
quarterly = df.resample("Q").agg({"Score": "mean", "Age": "count"})

# Extract date components
df["Year"] = df.index.year
df["Month"] = df.index.month
df["DayOfWeek"] = df.index.day_name()
df["Quarter"] = df.index.quarter

# Shift and lag
df["Score_lag1"] = df["Score"].shift(1)   # previous value
df["Score_diff"] = df["Score"].diff(1)    # first difference
```

---

## Conditional Changes

- `np.where(condition, x, y)`: returns `x` where condition is `True`, else `y`. Works on arrays and Series.

- `pd.cut(x, bins, labels=None, right=True, include_lowest=False)`: bins continuous values into discrete intervals.
  - `x`: 1D array-like to bin.
  - `bins`: int (number of equal-width bins) or sequence of bin edges.
  - `labels`: labels for the bins.
  - `right`: if `True`, intervals are closed on the right (default).

- `pd.qcut(x, q, labels=None, duplicates='raise')`: quantile-based binning (equal-frequency bins).
  - `x`: 1D array-like.
  - `q`: int (number of quantiles) or list of quantile boundaries in [0, 1].
  - `duplicates`: `'raise'` or `'drop'` — handles duplicate bin edges.

```python
# np.where
df["Label"] = np.where(df["Score"] > 90, "Excellent", "Average")

# Nested np.where
df["Grade"] = np.where(df["Score"] >= 90, "A",
              np.where(df["Score"] >= 80, "B",
              np.where(df["Score"] >= 70, "C", "F")))

# loc-based conditional assignment
df.loc[df["Score"] > 90, "Category"] = "Top"
df.loc[df["Score"] <= 90, "Category"] = "Normal"

# apply with custom function
def grade(row):
    if row["Score"] >= 90:
        return "A"
    elif row["Score"] >= 80:
        return "B"
    return "C"

df["Grade"] = df.apply(grade, axis=1)

# Cut into equal-width bins
df["ScoreRange"] = pd.cut(df["Score"], bins=[0, 60, 70, 80, 90, 100],
                          labels=["F", "D", "C", "B", "A"])

# Cut into equal-frequency bins
df["ScoreQuartile"] = pd.qcut(df["Score"], q=4, labels=["Q1", "Q2", "Q3", "Q4"],
                               duplicates="drop")
```

---

## MultiIndex

A MultiIndex (hierarchical index) lets you have multiple levels of row or column labels, which is useful for grouped or panel data.

- `pd.MultiIndex.from_tuples(tuples, names=None)`: creates a MultiIndex from a list of tuples.
- `pd.MultiIndex.from_product(iterables, names=None)`: creates a MultiIndex from the Cartesian product of iterables.

```python
# Creating a MultiIndex DataFrame
arrays = [["Alice", "Alice", "Bob", "Bob"],
          ["Math", "Science", "Math", "Science"]]
index = pd.MultiIndex.from_arrays(arrays, names=["Name", "Subject"])
df_multi = pd.DataFrame({"Score": [90, 85, 80, 78]}, index=index)

# Accessing
print(df_multi.loc["Alice"])                     # all rows for Alice
print(df_multi.loc[("Alice", "Math")])           # specific cell
print(df_multi.loc["Alice", "Math"])             # equivalent

# Cross-section
print(df_multi.xs("Math", level="Subject"))      # all Math scores

# Reset MultiIndex to regular columns
df_flat = df_multi.reset_index()

# GroupBy creates a MultiIndex on the result
result = df.groupby(["Category", "Gender"])["Score"].mean()
print(result.unstack())                          # pivot inner level to columns
```

---

## Performance Tips

```python
# Use vectorized operations instead of loops
df["Total"] = df["A"] + df["B"]   # fast
# for i in df.index: df.at[i, "Total"] = df.at[i, "A"] + df.at[i, "B"]  # slow

# Read large files in chunks
for chunk in pd.read_csv("large_file.csv", chunksize=10_000):
    process(chunk)

# Use efficient dtypes to reduce memory
df = df.astype({"Age": "int8", "Score": "float32"})
df = df.convert_dtypes()                         # automatic best dtypes

# Use query() for readable filtering
df.query("Score > 90 and Age < 30")

# Avoid chained indexing (triggers SettingWithCopyWarning)
# Bad:  df[df["A"] > 0]["B"] = 1
# Good: df.loc[df["A"] > 0, "B"] = 1

# Use categorical dtype for low-cardinality string columns
df["Category"] = df["Category"].astype("category")

# Efficient iteration (prefer apply or vectorization over iterrows)
# iterrows() is slow — use vectorized ops or apply when possible
# If you must iterate: itertuples() is faster than iterrows()
for row in df.itertuples():
    print(row.Name, row.Score)
```
