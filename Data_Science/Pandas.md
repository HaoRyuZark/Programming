# Pandas

Library for working with tabular data, which uses numpy under the hood, this means that all of the NumPy 
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

- `s.index`: the index (row labels) of the Series. Can be seen as the unnamed column.
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

### Indexes

The **index** is the label/identifier  of a row, which by default is an range from 0 to n.

- `df.set_index(label, inplace=False)`: will update the index labels and based on the `inplace=Bool` parameter 
will change the DataFrame or return a copy.

  - `label`: array-lie (column) to be used as the new index.
  - `inplace`: will determine if another Dataframe will be used with the new index.

- `df.reset_index(inplace=False)`: if an index was changed, it resets it to the default integer range.

- `df.sort_index(ascending=True, inplace=False)`: sorts the row indexes.

```python 
df.set_index("email", inplace=True)
df.reset_index(inplace=True)
df.sort_index(ascending=False, inplace=True)
```

> Note that `iloc` uses the real internal index of the array while `loc` uses the index label.

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

- `pd.read_csv(filepath, sep=',', header='infer', index_col=None, usecols=None, dtype=None, nrows=None, skiprows=None, na_values=None, parse_dates=False, format=None, encoding='utf-8')`: 
reads a CSV file into a DataFrame.
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
  - `format`: date format to be used, given a `parse_dates=True` 

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

### CSV

- `df.to_csv(path_or_buf, sep=',', index=True, header=True, columns=None, encoding='utf-8', na_rep='', float_format=None, date_format=None, mode='w', compression='infer', quoting=None, quotechar='"', lineterminator=None, chunksize=None)`: writes a DataFrame to a CSV file.
  - `path_or_buf`: file path or file-like object. If `None`, returns the CSV as a string.
  - `sep`: field delimiter (default `','`). Use `'\t'` for TSV.
  - `index`: if `False`, the row index is not written to the file.
  - `header`: if `False`, column names are omitted. Can also be a list of strings to rename columns on export.
  - `columns`: list of column names to include; omits all others.
  - `na_rep`: string representation of missing values (default `''`).
  - `float_format`: format string for floating-point numbers (e.g., `'%.4f'` for 4 decimal places).
  - `date_format`: strftime format string for datetime columns (e.g., `'%Y-%m-%d'`).
  - `mode`: file open mode — `'w'` (overwrite, default) or `'a'` (append).
  - `compression`: compression to apply — `'infer'` (from file extension), `'gzip'`, `'bz2'`, `'zip'`, `'xz'`, or `None`.
  - `quoting`: controls quoting behaviour — use `csv.QUOTE_ALL`, `csv.QUOTE_MINIMAL`, etc.
  - `quotechar`: character used to quote fields (default `'"'`).
  - `chunksize`: number of rows to write at a time (useful for very large DataFrames).

```python
import csv

df = pd.DataFrame({
    "Name":  ["Alice", "Bob", "Carol"],
    "Age":   [30, 25, 35],
    "Score": [95.5123, 87.2456, 92.0789],
    "Date":  pd.to_datetime(["2024-01-15", "2024-02-20", "2024-03-10"]),
})

# Basic — no index column
df.to_csv("output.csv", index=False)

# Tab-separated with 2 decimal places and custom date format
df.to_csv("output.tsv", sep="\t", index=False,
          float_format="%.2f", date_format="%d/%m/%Y")

# Only specific columns, missing values as "N/A"
df.to_csv("output.csv", columns=["Name", "Score"],
          na_rep="N/A", index=False)

# Rename columns on export
df.to_csv("output.csv", header=["name", "age", "score", "date"], index=False)

# Compressed output (extension is inferred automatically)
df.to_csv("output.csv.gz", index=False, compression="gzip")
df.to_csv("output.csv.zip", index=False, compression="zip")

# Append mode — add rows to an existing file
df.to_csv("log.csv", mode="a", header=False, index=False)

# Return as a string instead of writing to disk
csv_string = df.to_csv(index=False)
print(csv_string)

# Quote all fields to handle embedded commas
df.to_csv("output.csv", index=False, quoting=csv.QUOTE_ALL)
```

### Excel

- `df.to_excel(excel_writer, sheet_name='Sheet1', index=True, header=True, startrow=0, startcol=0, na_rep='', float_format=None, columns=None, freeze_panes=None, engine=None)`: writes a DataFrame to an Excel `.xlsx` file.
  - `excel_writer`: file path string or a `pd.ExcelWriter` object. Use `ExcelWriter` when writing multiple sheets or applying formatting.
  - `sheet_name`: name of the target worksheet (default `'Sheet1'`).
  - `index`: if `False`, the row index is not written.
  - `header`: if `False`, column names are omitted. Can be a list of strings to rename on export.
  - `startrow` / `startcol`: zero-based row and column offset where the data begins — useful for leaving space for titles or other content.
  - `na_rep`: string used for missing values (default `''`).
  - `float_format`: format string for floating-point numbers (e.g., `'%.2f'`).
  - `columns`: subset of columns to write.
  - `freeze_panes`: tuple `(row, col)` — freezes rows above and columns to the left of this cell (e.g., `(1, 0)` freezes the header row).
  - `engine`: underlying engine — `'openpyxl'` (default for `.xlsx`) or `'xlsxwriter'`.

- `pd.ExcelWriter(path, engine=None, mode='w', if_sheet_exists='error', datetime_format=None, date_format=None)`: context manager for writing to a single Excel file, enabling multiple sheets and engine-level formatting.
  - `path`: output file path.
  - `engine`: `'openpyxl'` or `'xlsxwriter'`.
  - `mode`: `'w'` (overwrite) or `'a'` (append sheets to an existing file — requires `openpyxl`).
  - `if_sheet_exists`: behaviour when the target sheet already exists in append mode — `'error'`, `'new'`, `'replace'`, `'overlay'`.
  - `datetime_format` / `date_format`: strftime format strings applied to datetime/date columns.

```python
# Simple single-sheet export
df.to_excel("output.xlsx", sheet_name="Results", index=False)

# Freeze header row and two decimal places
df.to_excel("output.xlsx", index=False, float_format="%.2f",
            freeze_panes=(1, 0))

# Write multiple sheets in one file
with pd.ExcelWriter("report.xlsx") as writer:
    df.to_excel(writer, sheet_name="Data",  index=False)
    df.describe().to_excel(writer, sheet_name="Stats")
    df[df["Score"] > 90].to_excel(writer, sheet_name="Top Scorers", index=False)

# Append a new sheet to an existing workbook (openpyxl required)
with pd.ExcelWriter("report.xlsx", engine="openpyxl",
                    mode="a", if_sheet_exists="replace") as writer:
    df.to_excel(writer, sheet_name="Updated Data", index=False)

# Start data at row 2, col 1 (leave room for a title)
with pd.ExcelWriter("styled.xlsx", engine="openpyxl") as writer:
    df.to_excel(writer, sheet_name="Sheet1", startrow=1, startcol=0, index=False)
    ws = writer.sheets["Sheet1"]
    ws["A1"] = "Monthly Sales Report"   # write a title above the data

# xlsxwriter engine — add a chart
with pd.ExcelWriter("chart.xlsx", engine="xlsxwriter") as writer:
    df.to_excel(writer, sheet_name="Data", index=False)
    workbook  = writer.book
    worksheet = writer.sheets["Data"]

    chart = workbook.add_chart({"type": "column"})
    chart.add_series({
        "name":       "Score",
        "categories": ["Data", 1, 0, len(df), 0],   # Name column
        "values":     ["Data", 1, 2, len(df), 2],   # Score column
    })
    worksheet.insert_chart("E2", chart)

# Custom datetime format
with pd.ExcelWriter("dated.xlsx", datetime_format="DD/MM/YYYY") as writer:
    df.to_excel(writer, index=False)
```

### JSON

- `df.to_json(path_or_buf=None, orient=None, date_format='epoch', double_precision=10, force_ascii=True, date_unit='ms', default_handler=None, lines=False, compression='infer', index=True, indent=None, storage_options=None)`: serialises a DataFrame to JSON.
  - `path_or_buf`: file path or file-like object. If `None`, returns the JSON as a string.
  - `orient`: JSON structure format:
    - `'records'` — `[{col: val, ...}, ...]` — list of row objects (most common, REST-API friendly).
    - `'columns'` — `{col: {index: val, ...}, ...}` — default when `orient` is `None`.
    - `'index'`   — `{index: {col: val, ...}, ...}` — dict of row dicts keyed by index.
    - `'split'`   — `{"columns": [...], "index": [...], "data": [[...]]}` — compact, full round-trip.
    - `'values'`  — `[[val, ...], ...]` — bare 2D array, no labels.
    - `'table'`   — JSON Table Schema format with dtype metadata; perfect for exact round-trips.
  - `date_format`: `'epoch'` (milliseconds since Unix epoch, default) or `'iso'` (ISO 8601 string).
  - `double_precision`: number of decimal places for floating-point values (default 10).
  - `force_ascii`: if `True`, non-ASCII characters are escaped (default `True`). Set to `False` to preserve Unicode.
  - `date_unit`: time unit for epoch timestamps — `'s'`, `'ms'`, `'us'`, `'ns'`.
  - `lines`: if `True`, writes one JSON object per line (JSON Lines / NDJSON format) — requires `orient='records'`.
  - `compression`: `'infer'` (from extension), `'gzip'`, `'bz2'`, `'zip'`, `'xz'`, or `None`.
  - `index`: if `False`, the index is not included in `'split'` and `'table'` formats.
  - `indent`: number of spaces for pretty-printing (default `None` — compact output).

```python
df = pd.DataFrame({
    "Name":  ["Alice", "Bob", "Carol"],
    "Age":   [30, 25, 35],
    "Score": [95.5123, 87.2456, 92.0789],
    "Date":  pd.to_datetime(["2024-01-15", "2024-02-20", "2024-03-10"]),
})

# records — most readable, suits REST APIs
df.to_json("output.json", orient="records", indent=2)
# [
#   {"Name": "Alice", "Age": 30, "Score": 95.5123, "Date": 1705276800000},
#   ...
# ]

# records with ISO dates instead of epoch milliseconds
df.to_json("output.json", orient="records", date_format="iso", indent=2)

# split — lossless round-trip (index + columns + data)
df.to_json("output.json", orient="split", indent=2)

# table — includes full dtype metadata, best for exact round-trips
df.to_json("schema.json", orient="table", indent=2)
df_rt = pd.read_json("schema.json", orient="table")   # dtypes preserved

# index — dict-of-dicts keyed by row index
df.to_json("output.json", orient="index", indent=2)

# values — bare 2D array (no column/index labels)
df.to_json("output.json", orient="values")

# JSON Lines / NDJSON — one object per line, ideal for streaming / log ingestion
df.to_json("output.ndjson", orient="records", lines=True)
# {"Name":"Alice","Age":30,"Score":95.5123,"Date":1705276800000}
# {"Name":"Bob","Age":25,"Score":87.2456,"Date":1708387200000}

# Preserve Unicode characters (e.g., accented names)
df.to_json("output.json", orient="records", force_ascii=False, indent=2)

# Limit float precision
df.to_json("output.json", orient="records", double_precision=2, indent=2)

# Compressed output
df.to_json("output.json.gz", orient="records", compression="gzip")

# Return as a string (no file written)
json_str = df.to_json(orient="records", indent=2)
print(json_str)

# Round-trip: write then read back
df.to_json("round_trip.json", orient="records", date_format="iso")
df_back = pd.read_json("round_trip.json", orient="records")
```

### Other Formats

- `df.to_parquet(path, engine='auto', index=True, compression='snappy')`: writes to a Parquet file.
  - `path`: output file path.
  - `compression`: `'snappy'`, `'gzip'`, `'brotli'`, or `None`.

- `df.to_sql(name, con, schema=None, if_exists='fail', index=True, chunksize=None)`: writes to a SQL table.
  - `name`: SQL table name.
  - `con`: SQLAlchemy connection.
  - `if_exists`: action if the table already exists — `'fail'`, `'replace'`, `'append'`.

```python
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
  - `row_label`: row index label, slice (last index is inclusive), or list of labels.
  - `col_label`: column name, slice, or list of column names.

- `df.iloc[row_pos, col_pos]`: position-based selection. Accepts integers, slices, and lists of integers. The stop in a slice is **exclusive**.
  - `row_pos`: integer position, slice, or list.
  - `col_pos`: integer position, slice, or list.

- `df.at[row_label, col_label]`: fast scalar access by label (single cell).

- `df.iat[row_pos, col_pos]`: fast scalar access by position (single cell).

> **Key difference**: if you sort the DataFrame, the original index labels stay with their rows. `loc` uses those labels as keys, while `iloc` always uses the physical 
row position regardless of the index.

```python
df = pd.DataFrame({
    "Name":  ["Alice", "Bob", "Carol", "Dave"],
    "Age":   [30, 25, 35, 28],
    "Score": [95.5, 87.2, 92.0, 78.4]
}, index=["a", "b", "c", "d"])

# loc — by label
print(df.loc["a"])                            # row with label "a"
print(df.loc["a":"c"])                        # rows a to c (inclusive)
print(df.loc["a", "Name"])                    # single cell by label
print(df.loc[["a", "c"], ["Name", "Score"]])  # subset

# iloc — by position
print(df.iloc[0])                         # first row
print(df.iloc[[0, 1]])                    # first and second row
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

- `df.iterrows()`: iterates over rows as `(index, Series)` pairs. Each row is returned as a Series — dtypes may be upcast to accommodate mixed types. Considerably slower than vectorized operations; avoid on large DataFrames.

- `df.itertuples(index=True, name='Pandas')`: iterates over rows as named tuples. Faster than `iterrows()` and preserves column dtypes.
  - `index`: if `True`, includes the row index as the first field of the tuple.
  - `name`: name of the returned named tuple class. Pass `None` to return plain tuples.

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

- `&` `~` and `|`: these are not bit-wise operators, but they act as `&&`, `^` and `||` in other programming languages. They are use to concatenate filters, due 
to the fact that we can not use the default python Booleans for such condition-concatenation

```python

# Boolean array
filt = df["Age"] > 25

# Single condition
print(df[filt])
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

- `df["new_col"] = list_expr`: adds a column with the specified name using a expression which produces a list (series).

- `s.apply(func, convert_dtype=True, args=())`: applies a function element-wise to each value of a Series.
  - `func`: callable that receives a scalar and returns a scalar or a new Series.
  - `convert_dtype`: if `True`, tries to find a better matching dtype for the result.
  - `args`: extra positional arguments passed to `func` after each element.

- `df.applymap(func)` (deprecated in pandas 2.1+ — use `df.map(func)` instead): applies a function element-wise to every cell in a DataFrame.
  - `func`: callable that receives a scalar and returns a scalar.

- `pd.cut(x, bins, labels=None, right=True, include_lowest=False, duplicates='raise')`: bins continuous values into discrete intervals with fixed-width edges.
  - `x`: 1D array-like to bin.
  - `bins`: int (number of equal-width bins computed from data range) or sequence of bin edges.
  - `labels`: labels for the resulting bins. Length must equal the number of resulting bins. If `False`, returns integer bin indices.
  - `right`: if `True`, intervals are closed on the right — `(a, b]` (default).
  - `include_lowest`: if `True`, the first interval is left-closed — `[a, b]`.
  - `duplicates`: `'raise'` or `'drop'` — how to handle duplicate bin edges.

- `pd.qcut(x, q, labels=None, duplicates='raise')`: quantile-based binning — divides data into equal-frequency bins so that each bin contains approximately the same number of observations.
  - `x`: 1D array-like.
  - `q`: int (number of quantiles) or list of quantile boundaries in [0, 1] (e.g., `[0, 0.25, 0.5, 0.75, 1]`).
  - `labels`: labels for the resulting bins. If `False`, returns integer bin indices.
  - `duplicates`: `'raise'` or `'drop'` — how to handle duplicate bin edges that arise from the data distribution.

- `df.assign(**kwargs)`: adds new columns to a DataFrame and returns a new object — the original is not modified.
  - `**kwargs`: column names as keywords. Values can be scalars, arrays, or callables. Callables receive the current DataFrame as their argument, allowing columns assigned earlier in the same call to be referenced.

- `df.rename(mapper=None, index=None, columns=None, axis=None, inplace=False, errors='ignore')`: renames axis labels.
  - `columns`: dict mapping `{old_name: new_name}` for column labels.
  - `index`: dict mapping `{old_label: new_label}` for row index labels.
  - `axis`: axis targeted by `mapper` — `0` or `'index'` for rows, `1` or `'columns'` for columns.
  - `inplace`: if `True`, modifies in place; otherwise returns a new DataFrame.
  - `errors`: `'raise'` if a label is not found, or `'ignore'` to silently skip missing labels.

```python

# Adding A Column Directly
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

## Adding Rows 

- `df.append(other, ignore_index=False, verify_integrity=False, sort=False)`: appends rows of the other, creating a new object.
  - `other`: a DataFrame or Series/dict-like object, or list of these which  is the data to append. 
  - `ignore_index`: if True, the resulting axis will be labeled 0, 1, …, n - 1
  - `verify_integrity`: if True, raise ValueError on creating index with duplicates.
  - `sort`: Sort columns if the columns of self and other are not aligned.

```python 
# Basic append
df.append({'first': 'Tony'}, ignore_index=True)

# append multiple rows
new_rows = pd.DataFrame([{'first': 'Tony'}, {'first': 'Steve'}])
df = df.append(new_rows, ignore_index=True)
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

- `df.remove_duplicates(subset=None, keep='first', inplace=False)`: removes duplicate rows.
  - `subset`: column(s) to consider for identifying duplicates.
  - `keep`: which occurrence to keep — `'first'`, `'last'`, or `False` (drop all duplicates).

-  `df["col"].str.strip(to_strip=None)`: removes leading and trailing characters from string columns.
   - `to_strip`: characters to remove (default is whitespace).

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

## Aggregate Functions

We can apply this funcions to a DataFrame or Series to get summary statistics:

- `df.describe(percentiles=None, include=None, exclude=None)`: generates descriptive statistics for each of the columns.
  - `percentiles`: list of percentiles to include (default `[0.25, 0.5, 0.75]`).
  - `include`: dtypes to include — `'all'` to include object columns.
  - `exclude`: dtypes to exclude.

- `df.sum(axis=0, skipna=True)`: sum of values.

- `df.mean(axis=0, skipna=True)`: mean of values.

- `df.median(axis=0, skipna=True)`: median of values.

- `df.min(axis=0, skipna=True)`: minimum value.

- `df.max(axis=0, skipna=True)`: maximum value.

- `df.count(axis=0)`: number of non-NaN values.

- `df.nunique(axis=0, dropna=True)`: number of unique values.

- `df.value_counts(subset=None, normalize=False, sort=True, dropna=True)`: counts occurrences of unique rows (or use on a Series for value frequency).
  - `subset`: columns to consider for counting.
  - `normalize`: if `True`, returns relative frequencies.
  - `sort`: if `True`, sorts by counts.
  - `dropna`: if `True`, ignores NaN values.

- `df.corr(method='pearson', min_periods=1)`: pairwise correlation of columns.

```python 
print(df.describe())                     # summary stats for numeric columns
print(df.sum(numeric_only=True))          # sum of numeric columns
print(df.mean(numeric_only=True))         # mean of numeric columns 
print(df["Score"].median())              # median of a single column
print(df.min(numeric_only=True))          # min of numeric columns
print(df.max(numeric_only=True))          # max of numeric columns
print(df.count())                        # count of non-NaN values per column
print(df.nunique())                      # unique values per column
print(df["Category"].value_counts())      # frequency of each category
print(df.corr())                          # pairwise correlation of columns
```

--- 

## GroupBy & Aggregations

GroupBy is a concept from SQL that allows us to perform aggregation on subsets of the data which share a common characteristic. 
For example: grouping a dataset by country and then calculating the avarage income for each country.

- `df.groupby(by, axis=0, sort=True, dropna=True)`: returns a groupBy object which contains the groups formed based on the condition.
  - `by`: column name, list of column names, or a function.
  - `sort`: if `True`, sort group keys.
  - `dropna`: if `True`, groups with NaN keys are excluded.


-  `groupby_obj.get_group(name)`: returns the group corresponding to the given name.

- `groupby_obj.groups`: a dict mapping group names to row indices.

- `groupby_obj.size()`: returns the size of each group.

- `groupby_obj.count()`: counts non-NaN values in each group.

- `groupby_obj.mean()`, `groupby_obj.sum()`, `groupby_obj.min()`, `groupby_obj.max()`, etc.: standard aggregation functions applied to each group.

- `groupby_obj["col"]`: access a specific column within each group.

- `groupby_obj.loc[name]`: access a specific group by name (similar to `get_group` but returns a view if possible).

- `groupby_obj.iloc[name]`: access a specific group by integer position (similar to `get_group` but returns a view if possible).

- `groupby_obj["col"].agg(func)`: applies an aggregation function to a specific column within each group.
  - `func`: function, string alias (e.g., `'mean'`), list, or dict mapping column names to aggregations.
 
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

## Time Series & Dates

### Date Format Codes

These `strftime`/`strptime` format codes are used in `pd.to_datetime(format=...)`, `dt.strftime(...)`, and `pd.read_csv(date_format=...)`.

| Code | Meaning | Example |
|------|---------|---------|
| `%Y` | 4-digit year | `2024` |
| `%y` | 2-digit year | `24` |
| `%m` | Month as zero-padded number | `01` – `12` |
| `%B` | Full month name | `January` |
| `%b` | Abbreviated month name | `Jan` |
| `%d` | Day of month, zero-padded | `01` – `31` |
| `%H` | Hour (24-hour clock), zero-padded | `00` – `23` |
| `%I` | Hour (12-hour clock), zero-padded | `01` – `12` |
| `%p` | AM or PM | `AM`, `PM` |
| `%M` | Minute, zero-padded | `00` – `59` |
| `%S` | Second, zero-padded | `00` – `59` |
| `%f` | Microseconds, zero-padded | `000000` – `999999` |
| `%A` | Full weekday name | `Monday` |
| `%a` | Abbreviated weekday name | `Mon` |
| `%j` | Day of year, zero-padded | `001` – `366` |
| `%W` | Week number of year (Monday as first day) | `00` – `53` |
| `%U` | Week number of year (Sunday as first day) | `00` – `53` |
| `%Z` | Time zone name | `UTC`, `EST` |
| `%z` | UTC offset | `+0000`, `-0500` |
| `%%` | Literal `%` character | `%` |

### Parsing Dates

- `pd.to_datetime(arg, format=None, errors='raise', unit=None, utc=False)`: converts argument to datetime.
  - `arg`: string, list, array, or Series.
  - `format`: strftime format string (e.g., `'%Y-%m-%d'`). Providing it speeds up parsing significantly.
  - `errors`: `'raise'`, `'coerce'` (invalid becomes `NaT`), or `'ignore'`.
  - `unit`: unit for numeric timestamps — `'s'`, `'ms'`, `'us'`, `'ns'`.
  - `utc`: if `True`, returns UTC-localized timestamps.

- `pd.Timestamp(ts_input, tz=None)`: represents a single point in time (a scalar datetime). Equivalent to Python's `datetime` but with pandas integration.
  - `ts_input`: string, datetime, or integer.
  - `tz`: timezone string (e.g., `'UTC'`, `'Europe/Berlin'`).

- `pd.Timedelta(value, unit=None)`: represents a duration (difference between two datetimes).
  - `value`: integer, string (e.g., `'5 days'`), or timedelta object.
  - `unit`: time unit when `value` is numeric — `'D'`, `'h'`, `'m'`, `'s'`, `'ms'`, `'us'`, `'ns'`.

```python
# Parse a column from strings
df["Date"] = pd.to_datetime(df["Date"], format="%Y-%m-%d")
df["Date"] = pd.to_datetime(df["Date"], errors="coerce")   # invalid → NaT

# Mixed formats — let pandas infer each value
df["Date"] = pd.to_datetime(df["Date"], format="mixed")

# Numeric Unix timestamps
df["Date"] = pd.to_datetime(df["timestamp_col"], unit="s")  # seconds since epoch

# Single timestamp
ts = pd.Timestamp("2024-06-15 14:30:00")
ts_tz = pd.Timestamp("2024-01-01", tz="UTC")

# Timedelta arithmetic
delta = pd.Timedelta("3 days 4 hours")
df["Deadline"] = df["Date"] + delta
df["Days_since"] = pd.Timestamp("today") - df["Date"]
```

### Parsing Dates When Reading Files

When reading files, you can instruct pandas to parse date columns directly, avoiding an extra conversion step.

- `pd.read_csv(..., parse_dates=[col], date_format=fmt)`: parses the specified columns as datetime during reading.
  - `parse_dates`: list of column names or indices to parse as dates. Pass a list of lists to combine multiple columns into one datetime column.
  - `date_format`: explicit strftime format string — speeds up parsing and avoids ambiguity (e.g., `'%d/%m/%Y'`).

- `pd.read_excel(..., parse_dates=[col])`: same behaviour for Excel files.

```python
# Basic — let pandas infer the format
df = pd.read_csv("data.csv", parse_dates=["Date"])

# Specify exact format for speed and correctness
df = pd.read_csv("data.csv", parse_dates=["Date"], date_format="%d/%m/%Y")

# Combine two columns (year + month) into one datetime column
df = pd.read_csv("data.csv", parse_dates={"Date": ["Year", "Month"]})

# Read with a datetime index
df = pd.read_csv("data.csv", parse_dates=["Date"], index_col="Date")

# Excel
df = pd.read_excel("data.xlsx", parse_dates=["OrderDate"], date_format="%Y%m%d")
```

### `dt` Accessor — Datetime Properties & Methods

Once a column holds `datetime64` values, the `.dt` accessor exposes all datetime properties and methods vectorized over the entire Series.

#### Properties

- `s.dt.year` / `s.dt.month` / `s.dt.day`: year, month (1–12), day (1–31).
- `s.dt.hour` / `s.dt.minute` / `s.dt.second` / `s.dt.microsecond`: time components.
- `s.dt.date`: Python `date` objects (no time component).
- `s.dt.time`: Python `time` objects (no date component).
- `s.dt.dayofweek` / `s.dt.day_of_week`: integer (Monday=0, Sunday=6).
- `s.dt.day_name(locale=None)`: full weekday name as a string.
- `s.dt.month_name(locale=None)`: full month name as a string.
- `s.dt.dayofyear` / `s.dt.day_of_year`: day number within the year (1–366).
- `s.dt.weekofyear` / `s.dt.isocalendar().week`: ISO week number.
- `s.dt.quarter`: quarter of the year (1–4).
- `s.dt.is_month_start` / `s.dt.is_month_end`: boolean — first or last day of the month.
- `s.dt.is_year_start` / `s.dt.is_year_end`: boolean — first or last day of the year.
- `s.dt.is_leap_year`: boolean — whether the year is a leap year.
- `s.dt.days_in_month`: number of days in the month.
- `s.dt.tz`: timezone info (or `None` if timezone-naive).

#### Methods

- `s.dt.strftime(date_format)`: formats each datetime as a string using a strftime format.
  - `date_format`: format string (e.g., `'%d %B %Y'`).

- `s.dt.normalize()`: sets the time component to midnight (`00:00:00`), preserving the date.

- `s.dt.floor(freq)` / `s.dt.ceil(freq)` / `s.dt.round(freq)`: rounds timestamps down/up/to-nearest to the given frequency.
  - `freq`: offset alias — `'D'`, `'h'`, `'min'`, `'s'`, etc.

- `s.dt.tz_localize(tz, ambiguous='raise', nonexistent='raise')`: localizes a timezone-naive Series to a given timezone.
  - `tz`: timezone string (e.g., `'UTC'`, `'US/Eastern'`).

- `s.dt.tz_convert(tz)`: converts a timezone-aware Series to a different timezone.

- `s.dt.to_period(freq)`: converts timestamps to Period objects (e.g., monthly or quarterly periods).

- `s.dt.total_seconds()`: for Timedelta Series — returns the total duration in seconds as a float.

```python
s = pd.to_datetime(pd.Series(["2024-03-15 08:45:00", "2023-11-01 22:10:30"]))

# Date components
print(s.dt.year)           # [2024, 2023]
print(s.dt.month)          # [3, 11]
print(s.dt.day)            # [15, 1]
print(s.dt.hour)           # [8, 22]
print(s.dt.quarter)        # [1, 4]
print(s.dt.dayofweek)      # [4, 2]  (Friday=4, Wednesday=2)
print(s.dt.day_name())     # ['Friday', 'Wednesday']
print(s.dt.month_name())   # ['March', 'November']
print(s.dt.dayofyear)      # [75, 305]
print(s.dt.days_in_month)  # [31, 30]
print(s.dt.is_month_end)   # [False, False]
print(s.dt.is_leap_year)   # [True, False]

# Format as string
print(s.dt.strftime("%d %B %Y"))  # ['15 March 2024', '01 November 2023']

# Rounding
print(s.dt.floor("h"))     # truncate to hour
print(s.dt.round("D"))     # round to nearest day
print(s.dt.normalize())    # set time to midnight

# Timezone
s_utc = s.dt.tz_localize("UTC")
s_berlin = s_utc.dt.tz_convert("Europe/Berlin")

# Period conversion
print(s.dt.to_period("M"))  # ['2024-03', '2023-11']

# Timedelta total seconds
durations = pd.to_timedelta(["1 days 02:00:00", "0 days 30:00:00"])
print(pd.Series(durations).dt.total_seconds())  # [93600.0, 108000.0]
```

### Generating Date Ranges

- `pd.date_range(start=None, end=None, periods=None, freq='D', tz=None, normalize=False, name=None)`: generates a fixed-frequency `DatetimeIndex`.
  - `start` / `end`: start and end of the range (inclusive by default).
  - `periods`: number of periods to generate (specify two of `start`, `end`, `periods`).
  - `freq`: frequency alias — `'D'` (day), `'h'` (hour), `'min'` (minute), `'MS'` (month start), `'ME'` (month end), `'QS'` (quarter start), `'YS'` (year start), `'B'` (business day), `'W'` (week ending Sunday).
  - `tz`: timezone string.
  - `normalize`: if `True`, normalizes start/end to midnight.

- `pd.period_range(start=None, end=None, periods=None, freq=None, name=None)`: generates a `PeriodIndex` (calendar periods rather than timestamps).

- `pd.timedelta_range(start=None, end=None, periods=None, freq=None)`: generates a `TimedeltaIndex`.

```python
# Daily range
dates = pd.date_range(start="2024-01-01", end="2024-01-31", freq="D")

# Monthly start for 12 months
months = pd.date_range(start="2024-01-01", periods=12, freq="MS")

# Business days only
bdays = pd.date_range(start="2024-01-01", periods=10, freq="B")

# Hourly
hours = pd.date_range(start="2024-01-01 00:00", periods=24, freq="h")

# With timezone
dates_tz = pd.date_range("2024-01-01", periods=5, freq="D", tz="Europe/Berlin")

# Period range (months)
periods = pd.period_range(start="2024-01", periods=6, freq="M")

# Timedelta range
deltas = pd.timedelta_range(start="0 days", periods=5, freq="12h")
```

### Resampling & Frequency Conversion

- `df.resample(rule, closed=None, label=None, origin='start_day')`: groups time-series data into calendar buckets (requires a `DatetimeIndex`).
  - `rule`: target frequency — `'D'`, `'W'`, `'ME'`, `'MS'`, `'QE'`, `'YE'`, etc.
  - `closed`: which end of each interval is closed — `'left'` or `'right'`.
  - `label`: which end to use as the bucket label — `'left'` or `'right'`.
  - `origin`: anchor for the first bin — `'start'`, `'start_day'`, `'epoch'`, or a timestamp.

- `df.asfreq(freq, method=None, fill_value=None)`: converts a time series to a specific frequency without aggregation — inserts NaN (or filled values) for missing timestamps.
  - `method`: fill method for missing entries — `'ffill'` or `'bfill'`.

```python
df = df.set_index("Date")          # DatetimeIndex required

# Downsample — aggregate to lower frequency
monthly_mean  = df.resample("ME").mean()
weekly_sum    = df.resample("W").sum()
quarterly     = df.resample("QE").agg({"Score": "mean", "Count": "sum"})

# Multiple aggregations
result = df["Score"].resample("ME").agg(["mean", "min", "max", "std"])

# Upsample — increase frequency (fills gaps)
daily = df.resample("D").asfreq()              # NaN for missing days
daily_ffill = df.resample("D").ffill()         # forward-fill gaps
daily_interp = df.resample("D").interpolate()  # linear interpolation

# asfreq — simple frequency conversion
df_daily = df.asfreq("D", method="ffill")
```

### Time Offsets & Shifting

```python
from pandas.tseries.offsets import BDay, MonthEnd, YearBegin

# Shift values forward/backward in time
df["Score_lag1"]  = df["Score"].shift(1)    # shift values down by 1 period
df["Score_lead1"] = df["Score"].shift(-1)   # shift values up by 1 period
df["Score_diff"]  = df["Score"].diff(1)     # first difference (value - previous value)
df["Score_pct"]   = df["Score"].pct_change()  # percentage change

# Shift index by a date offset
df_shifted = df.shift(1, freq="ME")         # move all timestamps forward by one month end
df_shifted = df.shift(3, freq=BDay())       # shift by 3 business days

# Date arithmetic with offsets
df["NextMonthEnd"] = df["Date"] + MonthEnd(1)
df["NextYearStart"] = df["Date"] + YearBegin(1)
df["FiveBDays"] = df["Date"] + 5 * BDay()
```

### Filtering & Slicing by Date

```python
df = df.set_index("Date")   # DatetimeIndex enables partial-string indexing

# Partial string indexing — select by year, month, or range
print(df["2024"])                          # all of 2024
print(df["2024-03"])                       # March 2024
print(df["2024-01":"2024-06"])             # Jan–Jun 2024 (inclusive)

# Boolean filtering
print(df[df.index >= "2024-01-01"])
print(df[(df.index >= "2024-01-01") & (df.index < "2024-07-01")])

# loc with timestamps
print(df.loc["2024-03-01":"2024-03-31"])

# between_time — filter by time of day (not date)
print(df.between_time("09:00", "17:00"))

# truncate — keep rows within a date window
print(df.truncate(before="2024-01-01", after="2024-12-31"))
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

- `pd.MultiIndex.from_arrays(arrays, sortorder=None, names=None)`: creates a MultiIndex from multiple 1D arrays, one per level.
  - `arrays`: list of array-like sequences, each representing one level of the index.
  - `names`: list of names for each index level.

- `pd.MultiIndex.from_tuples(tuples, sortorder=None, names=None)`: creates a MultiIndex from a list of tuples, where each tuple represents one entry across all levels.
  - `tuples`: list of tuples, each containing the index values for one row across all levels.
  - `names`: list of names for each index level.

- `pd.MultiIndex.from_product(iterables, sortorder=None, names=None)`: creates a MultiIndex from the Cartesian product of multiple iterables — generates all possible combinations.
  - `iterables`: list of iterables — one per level.
  - `names`: list of names for each index level.

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
