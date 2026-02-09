import pandas as pd
import numpy as np

##################################################################################################

#  READING DATA

# Creating a series
l = [i for i in range(0, 100)]
serie = pd.Series(l)  # customization possible (dtype, name, index)

# Creating a DataFrame 
df_1 = pd.DataFrame({"Name": ["A", "B", "X"], "Aman": [1, 2, 3]})

df = pd.read_csv("data.csv", delimiter="\t")   # tab-delimited CSV
df = pd.read_excel("data.xlsx")
df = pd.read_parquet("data.parquet")
df = pd.read_html("https://example.com/table.html")[0]  # first table from webpage
df = pd.read_html("https://example.com/table.html", match="target") # table containing "target"
df = pd.read_json("data.json")
# df = pd.read_sql("SELECT * FROM table", con=connection)

# Save Data
df.to_csv("new_file.csv", index=False)
# df.to_excel("new_file.xlsx", index=False)


##################################################################################################

# Data Cleaning 

df = pd.read_csv("data.csv")

# Remove leading/trailing whitespace from column names
df.columns = df.columns.str.strip()

# Remove unnamed columns
df = df.locate[:, ~df.columns.str.contains("unnamed", case=False)]

# Remove NaN rows
df = df.dropna()

# Remove duplicate rows
df = df.drop_duplicates()

# Remove Column with name "Unwanted"
df = df.drop(columns=["Unwanted"], errors="ignore")

# Strip 

#df["Last_Name"] = df["Last_Name"].str.lstrip("...")
#df["Last_Name"] = df["Last_Name"].str.lstrip("/")
#df["Last_Name"] = df["Last_Name"].str.rstrip("_")
df["Last_Name"] = df["Last_Name"].str.strip("123._/")

# Formating Phone Numbers 

#df["Phone_Number"] = df["Phone_Number"].str.replace('[^a-zA-Z0-9]','') get rid of invalid characters

#df["Phone_Number"].apply(lambda x: x[0:3] + '-' + x[3:6] + '-' + x[6:10]) formating

#df["Phone_Number"] = df["Phone_Number"].apply(lambda x: str(x)) convert to string

#df["Phone_Number"] = df["Phone_Number"].apply(lambda x: x[0:3] + '-' + x[3:6] + '-' + x[6:10])

df["Phone_Number"] = df["Phone_Number"].str.replace('nan--','')
df["Phone_Number"] = df["Phone_Number"].str.replace('Na--','')

# There are multiple ways to do data cleaning, this is covers the most common ones.
 
##################################################################################################

# Axis Parameter
# axis=0 : operate on rows (default)
# axis=1 : operate on columns

##################################################################################################

# loc and iloc

# loc[index] returns the entry with the index of 2
# iloc[index] returns the entry at index 2

# if sort the data the associated indexes ramain the same, thus iloc is like indexing an array and 
# loc like using the index as id

##################################################################################################

# MODIFIYING COLUMNS 

new_names = ['a', 'b', 'c']

df.columns = [s for s in df.columns.str.strip()]  # remove whitespace from column name
df.columns = df.columns.str.lower()          # type: ignore     # convert column names to lowercase
df.columns = df.columns.droplevel()               # drop multiindex level from columns


df = df.locate[:, ~df.columns.str.contains("unnamed", case=False)]  # remove unnamed columns
df = df.locate[:, ~df.columns.duplicated()]  # remove duplicated columns

df.columns = new_names # renaming all

df.rename(columns={"OldName": "NewName"}, inplace=True)  # rename columns

df["FareBin"] = pd.qcut(df["Fare"], 4, labels=False, duplicates="drop")  # binning into quartiles
df["AgeGroup"] = pd.cut(df["Age"], bins=[0, 12, 20, 40, 60, 80], labels=["Child", "Teen", "Adult", "Mid-Age", "Senior"])  # custom bins

# split columns 
df["Stree_Addr"], df["State"], df["Zip"] = df["Address"].str.split(",", 2, expand=True) # split up to two comas. This creates three new columns but the 
# original is not removed, to do that we have to drop it afterwards

df.reset_index(drop=True) # reset the indexes after droping rows

##################################################################################################

# INSPECT DATA

print(df.head())         # first 5 rows 
print(df.tail(3))        # last 3 rows
print(df.shape)          # (rows, columns) 
print(df.info())         # summary info
print(df.describe())     # statistical summary
print(df.columns)        # column names 
print(df.index)          # index info 
print(df.sample(5))      # random sample of rows
print(df.nunique())      # number of unique values per column
print(df.memory_usage()) # memory usage

##################################################################################################

# SELECTING DATA

print(df["Name"])                  # single column           
print(df[["Name", "Type 1"]])      # multiple columns
print(df.iloc[0])                  # first row by position
print(df.loc[0])                   # first row by label  
print(df.iloc[0, 1])               # specific cell by position
print(df.loc[0, "Name"])           # specific cell by label
print(df[1:4])                     # rows by position slice 
print(df.at[0, "Name"])            # fast scalar getter
print(df.iat[0, 1])                # fast scalar getter


##################################################################################################

# ITERATION

for index, row in df.iterrows():                        # iterate rows
    print(index, row["Name"], row["Type 1"])

for chunk in pd.read_csv("data.csv", chunksize=1000):   # iterate in chunks
    print(chunk.shape)


##################################################################################################

# FILTERING

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


##################################################################################################

# SORTING

print(df.sort_values("Name", ascending=True))
print(df.sort_values(["Primary Type", "HP"], ascending=False))
print(df.sort_index())   # sort by index

##################################################################################################

# ADDING & REMOVING COLUMNS

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

##################################################################################################

# DELETE ROWS

df.drop(index=0)                        # drop by index label
df.drop("0", axis=0, inplace=True )     # drop by index position
df.drop(index=df[df["HP"] < 50].index)  # drop
df = df[df["HP"] >= 50]                      # filter rows

##################################################################################################

# GROUPBY & AGGREGATIONS

print(df.groupby("Primary Type").mean(numeric_only=True)) # mean stats by Primary Type
print(df.groupby("Primary Type")["Name"].count()) # count of names by Primary Type

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

##################################################################################################

# CONDITIONAL CHANGES

df["Legendary Label"] = np.where(df["Legendary"], "Legendary", "Normal")

def label(row):
    return "Strong" if row["Attack"] > 100 else "Weak"

df["Strength"] = df.apply(label, axis=1)

df.loc[df["Primary Type"] == "🔥 Fire", "Primary Type"] = "Fire"
df.loc[df["HP"] < 50, "Category"] = "Low HP"

##################################################################################################

# ADVANCED CLEANING

df.dropna()                 # drop rows with any NaN 
df.fillna(0)                # fill NaN with 0
df.drop_duplicates()        # remove duplicate rows

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


##################################################################################################

# DATA RESHAPING (PIVOT, MELT, MERGE, JOIN)

# Pivot / Unpivot
pivot = df.pivot_table(values="Attack", index="Primary Type", columns="Legendary", aggfunc="mean")
melted = df.melt(id_vars=["Name"], var_name="Stat", value_name="Value")

# Concatenate
df_concat = pd.concat([df, df_1], axis=0, ignore_index=True)

# Merge & Join
merged = df.merge(df_1, on="Name", how="left")
joined = df.join(df_1.set_index("Name"), on="Name", how="inner")

##################################################################################################

# WINDOW FUNCTIONS

df["Rolling_Hp"] = df["HP"].rolling(3).mean()
df["Expanding_Attack"] = df["Attack"].expanding().sum()
df["Rank"] = df["Attack"].rank()

##################################################################################################

# TIME SERIES

# Ensure datetime type
df["Date"] = pd.to_datetime(df["Date"], errors="coerce")

df = df.set_index("Date")
df.resample("M").mean()        # monthly resample
#df["DayOfWeek"] = df.index.day_name()

##################################################################################################

# EXPORTING DATA

df.to_csv("output.csv", index=False)
df.to_excel("output.xlsx", index=False)
df.to_json("output.json", orient="records")
df.to_parquet("output.parquet")

