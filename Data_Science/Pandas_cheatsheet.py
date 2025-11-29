import pandas as pd
import numpy as np

# ======================
# In Pandas we work with Series and DataFrames 
# 
# Series: are 1D labeled column 
# DataFrames: Is a grid of labeled columns 
# ======================

# ======================
#  Reading Data
# ======================

# Creating a series
l = [i for i in range(0, 100)]
serie = pd.Series(l)  # customization possible (dtype, name, index)

# Creating a DataFrame 
df_1 = pd.DataFrame({"Name": ["A", "B", "X"], "Aman": [1, 2, 3]})

df = pd.read_csv("data.csv", delimiter="\t")   # tab-delimited CSV
df = pd.read_excel("data.xlsx")
df = pd.read_json("data.json")
df = pd.read_parquet("data.parquet")
df = pd.read_sql("SELECT * FROM table", con=connection)

# Save Data
df.to_csv("new_file.csv", index=False)
# df.to_excel("new_file.xlsx", index=False)


# ======================
# Inspect Data
# ======================

print(df.head())        
print(df.tail(3))        
print(df.shape)          
print(df.info())        
print(df.describe())    
print(df.columns)       
print(df.index)         
print(df.sample(5))      # random sample of rows
print(df.nunique())      # number of unique values per column
print(df.memory_usage()) # memory usage


# ======================
# Selecting Data
# ======================

print(df["Name"])                   
print(df[["Name", "Type 1"]])       
print(df.iloc[0])                   
print(df.iloc[0, 1])                
print(df.loc[0, "Name"])            
print(df[1:4])                      
print(df.at[0, "Name"])             # fast scalar getter
print(df.iat[0, 1])                 # fast scalar getter


# ======================
# Iteration
# ======================

for index, row in df.iterrows():
    print(index, row["Name"], row["Type 1"])

for chunk in pd.read_csv("data.csv", chunksize=1000):
    print(chunk.shape)


# ======================
# Filtering (Boolean Indexing)
# ======================

print(df[df["Type 1"] == "Fire"])
print(df[df["HP"] > 100])
print(df[(df["Type 1"] == "Fire") & (df["HP"] > 100)])
print(df[df["Type 1"].isin(["Grass", "Water"])])
print(df[df["Name"].str.contains("Mega")])
print(df[~df["Name"].str.contains("Mega")])
print(df[df["Attack"].between(50, 100)])
print(df[df["Type 2"].isnull()])
print(df[df["Type 2"].notnull()])
print(df.query("HP > 100 and `Type 1` == 'Fire'"))   # query syntax


# ======================
# Sorting
# ======================

print(df.sort_values("Name", ascending=True))
print(df.sort_values(["Type 1", "HP"], ascending=[1, 0]))
print(df.sort_index())   # sort by index


# ======================
# Creating & Modifying Columns
# ======================

df["Total Attack"] = df["Attack"] + df["Sp. Atk"]
df["Total"] = df.iloc[:, 4:10].sum(axis=1)
df["Name Length"] = df["Name"].apply(len)
df["Type 1"] = df["Type 1"].replace("Fire", "🔥 Fire")
df = df.rename(columns={"Type 1": "Primary Type"})

# Adding columns with assign()
df = df.assign(Ratio=lambda x: x["Attack"] / x["Defense"])

# Create from conditions
df["Is Strong"] = (df["Attack"] > 100).astype(int)

# Remove columns
df = df.drop(columns=["Total Attack"], errors="ignore")
del df["Ratio"]

# Reorder columns
df = df[["Name", "Primary Type"] + [col for col in df.columns if col not in ["Name", "Primary Type"]]]


# ======================
# GroupBy & Aggregations
# ======================

print(df.groupby("Primary Type").mean(numeric_only=True))
print(df.groupby("Primary Type")["Name"].count())

print(df.groupby("Primary Type").agg({
    "Attack": ["mean", "max"],
    "Defense": "median"
}))

print(df.groupby(["Primary Type", "Type 2"]).size())

# Multi-agg on multiple columns
df.groupby("Primary Type").agg(
    Attack_mean=("Attack", "mean"),
    HP_max=("HP", "max"),
    Count=("Name", "count")
)

# Transform (column remains same length)
df["Attack_zscore"] = df.groupby("Primary Type")["Attack"].transform(
    lambda s: (s - s.mean()) / s.std()
)


# ======================
# Conditional Changes
# ======================

df["Legendary Label"] = np.where(df["Legendary"], "Legendary", "Normal")

def label(row):
    return "Strong" if row["Attack"] > 100 else "Weak"

df["Strength"] = df.apply(label, axis=1)

df.loc[df["Primary Type"] == "🔥 Fire", "Primary Type"] = "Fire"
df.loc[df["HP"] < 50, "Category"] = "Low HP"


# ======================
# Advanced Cleaning
# ======================

df.dropna()                  
df.fillna(0)                 
df.drop_duplicates()         

df["Name"] = df["Name"].str.strip()         # remove whitespace
df["Name"] = df["Name"].str.lower()         # lowercase
df["Name"] = df["Name"].str.replace(r"\s+", "_", regex=True)

df = df.replace({"Unknown": np.nan})         # replace values with NaN
df = df.astype({"HP": "int32"})              # change dtype
df = df.convert_dtypes()                     # automatic dtype optimization

df = df.loc[:, ~df.columns.str.contains("Unnamed")]   # remove unnamed cols
df.columns = df.columns.str.replace(" ", "_")         # clean col names

# Handling outliers
df["Attack_clipped"] = df["Attack"].clip(lower=0, upper=200)

# Missing-value imputation
df["HP"] = df["HP"].fillna(df["HP"].median())


# ======================
# Data Reshaping (Pivot, Melt, Merge, Join)
# ======================

# Pivot / Unpivot
pivot = df.pivot_table(values="Attack", index="Primary Type", columns="Legendary", aggfunc="mean")
melted = df.melt(id_vars=["Name"], var_name="Stat", value_name="Value")

# Concatenate
df_concat = pd.concat([df, df_1], axis=0, ignore_index=True)

# Merge & Join
merged = df.merge(df_1, on="Name", how="left")
joined = df.join(df_1.set_index("Name"), on="Name", how="inner")


# ======================
# Window Functions
# ======================

df["Rolling_Hp"] = df["HP"].rolling(3).mean()
df["Expanding_Attack"] = df["Attack"].expanding().sum()
df["Rank"] = df["Attack"].rank()

# ======================
# Time Series Utilities
# ======================

# Ensure datetime type
df["Date"] = pd.to_datetime(df["Date"], errors="coerce")

df = df.set_index("Date")
df.resample("M").mean()        # monthly resample
df["DayOfWeek"] = df.index.day_name()


# ======================
# Export
# ======================
df.to_csv("output.csv", index=False)
df.to_excel("output.xlsx", index=False)
df.to_json("output.json", orient="records")
df.to_parquet("output.parquet")

