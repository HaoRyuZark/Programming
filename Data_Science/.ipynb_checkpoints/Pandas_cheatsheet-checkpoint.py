import pandas as pd
import numpy as np

# ======================
#  Reading Data
# ======================
df = pd.read_csv("data.csv", delimiter="\t")   # Example: reading CSV with tab delimiter
# df = pd.read_excel("data.xlsx")
# df = pd.read_json("data.json")

# Save Data
df.to_csv("new_file.csv", index=False)
# df.to_excel("new_file.xlsx", index=False)

# ======================
# Inspect Data
# ======================
print(df.head())        # first 5 rows
print(df.tail(3))       # last 3 rows
print(df.shape)         # (rows, cols)
print(df.info())        # dtypes + non-nulls
print(df.describe())    # summary stats
print(df.columns)       # column names
print(df.index)         # index info

# ======================
# Selecting Data
# ======================
print(df["Name"])                   # one column
print(df[["Name", "Type 1"]])       # multiple columns
print(df.iloc[0])                   # first row
print(df.iloc[0, 1])                # row 0, col 1
print(df.loc[0, "Name"])            # row 0, col "Name"
print(df[1:4])                      # rows 1 to 3

# ======================
# Iteration
# ======================
for index, row in df.iterrows():
    print(index, row["Name"], row["Type 1"])

# ======================
# Filtering (Boolean Indexing)
# ======================
print(df[df["Type 1"] == "Fire"])                     # all Fire type
print(df[df["HP"] > 100])                             # HP > 100
print(df[(df["Type 1"] == "Fire") & (df["HP"] > 100)])  # multiple conditions
print(df[df["Type 1"].isin(["Grass", "Water"])])      # isin
print(df[df["Name"].str.contains("Mega")])            # string contains
print(df[~df["Name"].str.contains("Mega")])           # not contains
print(df[df["Attack"].between(50, 100)])              # between
print(df[df["Type 2"].isnull()])                      # isnull
print(df[df["Type 2"].notnull()])                     # notnull

# ======================
#  Sorting
# ======================
print(df.sort_values("Name", ascending=True))
print(df.sort_values(["Type 1", "HP"], ascending=[1, 0]))

# ======================
#  Creating & Modifying Columns
# ======================
df["Total Attack"] = df["Attack"] + df["Sp. Atk"]
df["Total"] = df.iloc[:, 4:10].sum(axis=1)   # sum across cols
df = df.drop(columns=["Total Attack"])
df["Name Length"] = df["Name"].apply(len)
df["Type 1"] = df["Type 1"].replace("Fire", "🔥 Fire")
df = df.rename(columns={"Type 1": "Primary Type"})

# ======================
#  GroupBy & Aggregations
# ======================
print(df.groupby("Primary Type").mean(numeric_only=True))
print(df.groupby("Primary Type")["Name"].count())
print(df.groupby("Primary Type").agg({
    "Attack": ["mean", "max"],
    "Defense": "median"
}))
print(df.groupby(["Primary Type", "Type 2"]).size())

# ======================
#  Conditional Changes
# ======================
df["Legendary Label"] = np.where(df["Legendary"] == True, "Legendary", "Normal")

def label(row):
    if row["Attack"] > 100:
        return "Strong"
    return "Weak"

df["Strength"] = df.apply(label, axis=1)

df.loc[df["Primary Type"] == "🔥 Fire", "Primary Type"] = "Fire"
df.loc[df["HP"] < 50, "Category"] = "Low HP"

# ======================
#  Cleaning
# ======================
print(df.dropna())              # drop rows with NaN
print(df.fillna(0))             # fill NaN with 0
print(df.drop_duplicates())     # drop duplicate rows

# ======================
#  Export
# ======================
df.to_csv("output.csv", index=False)
df.to_excel("output.xlsx", index=False)
df.to_json("output.json", orient="records")

