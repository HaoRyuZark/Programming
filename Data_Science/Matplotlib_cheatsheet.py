import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import animation

##################################################################################################

# Random Data Setup

X_data = np.random.random(50) * 100
Y_data = np.random.random(50) * 100

##################################################################################################

# Figure and Ax

fig, ax = plt.subplots() # fig is the whole and the ax is the axis. you can also do 

fig, (ax1, ax2, ax3) = plt.subplots(1, 3) # one row three columns

fig, axs = plt.subplots(3, 3)

axs[0, 0].scatter() # accessing the first plot

##################################################################################################

# Scatter Plot

# Customization options: color, marker, size (s), alpha (transparency), cmap (color map)
# needs X and Y

plt.scatter(X_data, Y_data, color='blue', marker='o', s=50, alpha=0.7)
plt.title("Scatter Plot Example")
plt.xlabel("X Axis")
plt.ylabel("Y Axis")
plt.show()

##################################################################################################

# Line Plot

# Customization options: linestyle ('-', '--', ':'), color, linewidth, marker

years = [200 + i for i in range(50)]
weights = np.random.random(50) * 50

plt.plot(years, weights, color='red', linestyle='--', linewidth=2, marker='o')
plt.title("Line Plot Example")
plt.xlabel("Years")
plt.ylabel("Weights")
plt.show()

##################################################################################################

# Bar Plot

# Customization options: color, width, edgecolor, orientation (barh for horizontal)
x = ['C++', 'Rust', 'C', 'Py', 'Java', 'Bash']
y = [20, 30, 40, 10, 30, 5]

plt.bar(x, y, color='green', edgecolor='black')
plt.title("Bar Chart Example")
plt.show()

##################################################################################################

# Histogram

# Customization options: bins, color, cumulative, density, alpha
ages = np.random.normal(20, 1.5, 1000)  # mean, standard deviation, samples

plt.hist(ages, bins=20, color='purple', alpha=0.7, cumulative=True)
plt.title("Histogram Example")
plt.xlabel("Age")
plt.ylabel("Frequency")
plt.show()

##################################################################################################

# Pie Chart

# Customization options: labels, autopct (percentages), colors, explode
plt.pie(y, labels=x, autopct='%1.1f%%', startangle=90)
plt.title("Pie Chart Example")
plt.show()

##################################################################################################

# Boxplot

# Customization options: notch, vert (vertical/horizontal), patch_artist (colors)
plt.boxplot(ages, notch=True, patch_artist=True)
plt.title("Boxplot Example")
plt.show()

##################################################################################################

# Legend
# Customization options: location (loc), fontsize, title, shadow, frameon

plt.plot(years, np.random.random(50)*100, label="Experiment A")
plt.plot(years, np.random.random(50)*100, label="Experiment B")
plt.title("Legend Example")
plt.xlabel("Years")
plt.ylabel("Values")
plt.legend(loc="upper right", fontsize=10, title="Experiments", shadow=True)
plt.show()

##################################################################################################

# Multiple Plots with Labels

plt.plot(years, np.random.random(50)*100, label="Line 1")
plt.plot(years, np.random.random(50)*50, label="Line 2")
plt.title("Multiple Line Example")
plt.xlabel("Years")
plt.ylabel("Values")
plt.legend()
plt.show()

##################################################################################################

# Plot Styling

# Customization options: plt.style.use("style_name")
# Common styles: 'seaborn', 'ggplot', 'fivethirtyeight', 'classic'

plt.style.use("seaborn-v0_8")
plt.plot(years, np.random.random(50)*100, label="Styled Line")
plt.title("Styled Plot Example")
plt.legend()
plt.show()

##################################################################################################

# Multiple Figures

# Each figure can contain its own independent plot
plt.figure(1)
plt.plot(years, np.random.random(50)*100, color='blue')
plt.title("Figure 1")

plt.figure(2)
plt.bar(x, y, color='orange')
plt.title("Figure 2")
plt.show()

##################################################################################################

# Subplots

# Customization options: rows, cols, figsize, sharex, sharey
fig, axs = plt.subplots(2, 2, figsize=(8, 6))
axs[0, 0].plot(years, np.random.random(50)*100)
axs[0, 0].set_title("Line Plot")

axs[0, 1].bar(x, y)
axs[0, 1].set_title("Bar Chart")

axs[1, 0].hist(ages, bins=10)
axs[1, 0].set_title("Histogram")

axs[1, 1].scatter(X_data, Y_data)
axs[1, 1].set_title("Scatter Plot")

plt.tight_layout()
plt.show()

# Mosaic

fig, axd = plt.subplot_mosaic([['upleft', 'right'],
                               ['lowleft', 'right']], layout='constrained')
axd['upleft'].set_title('upleft')
axd['lowleft'].set_title('lowleft')
axd['right'].set_title('right')

##################################################################################################

# Exporting Plots

# Common formats: PNG, JPG, PDF, SVG
# Options: dpi, bbox_inches

plt.plot(years, weights, label="Export Example")
plt.title("Exporting Plot Example")
plt.legend()
plt.savefig("exported_plot.png", dpi=300, bbox_inches="tight")
plt.show()

##################################################################################################

# Plot Customization (titles and labels demo)

plt.plot(years, np.random.random(50)*100)
plt.title("Title Example")
plt.xlabel("Year")
plt.ylabel("Dollar")
plt.show()

##################################################################################################

# 3D Scatter Plot

# Customization options: marker, color, cmap, size (s), alpha
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
x = np.random.random(100)
y = np.random.random(100)
z = np.random.random(100)


ax.scatter(x, y, c=z, cmap='viridis', s=50, alpha=0.7)
ax.set_title("3D Scatter Plot")
plt.show()


##################################################################################################

# 3D Surface Plot

# Customization options: cmap, edgecolor, linewidth, alpha
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')


X = np.linspace(-5, 5, 100)
Y = np.linspace(-5, 5, 100)
X, Y = np.meshgrid(X, Y)
Z = np.sin(np.sqrt(X**2 + Y**2))


ax.plot_surface(X, Y, Z, cmap='plasma', edgecolor='none', alpha=0.9)
ax.set_title("3D Surface Plot")
plt.show()


##################################################################################################

# 3D Wireframe Plot

# Customization options: color, linewidth, rstride, cstride
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')


ax.plot_wireframe(X, Y, Z, color='black', linewidth=0.5)
ax.set_title("3D Wireframe Plot")
plt.show()


##################################################################################################

# 3D Contour Plot

# Customization options: levels, cmap, offset, alpha
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')


ax.contour3D(X, Y, Z, 50, cmap='inferno')
ax.set_title("3D Contour Plot")
plt.show()


##################################################################################################

# Animating a 2D Line Plot

fig, ax = plt.subplots()
x = np.linspace(0, 2*np.pi, 200)
y = np.sin(x)
line, = ax.plot(x, y)


# Animation function

def animate(i):
    line.set_ydata(np.sin(x + i/10.0)) # shift sine wave
    return line,


ani = animation.FuncAnimation(fig, animate, frames=100, interval=50, blit=True)
plt.title("Animated Sine Wave")
plt.show()


##################################################################################################

# Animating a 3D Rotating Surface

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
surf = ax.plot_surface(X, Y, Z, cmap='viridis')

##################################################################################################

# Seaborn

import seaborn as sb

# Seaborn provides built in datasets
print(sb.get_dataset_names())

# Load a built in dataset based on US State car crash percentages
crash_df = sb.load_dataset('car_crashes')

data = pd.DataFrame(X,Y)

##################################################################################################

# Distribution Plots

# Histogram
# Customization: bins, kde=boolean, 
sb.displot(X)

# Joint Plot 
# Customization: kind='graph type'
sb.jointplot(x='labelx', y='labely', data=data, kind='hex')

# KDE Plot
sb.kdeplot(Y)

# Pair Plot plots relationships across the entire data frames numerical values
# Only with numerical data
sb.pairplot(data)

# Load data on tips
tips_df = sb.load_dataset('tips')

sb.pairplot(data.select_dtypes(['number']), hue="pclass")

# With hue you can pass in a categorical column and the charts will be colorized
# You can use color maps from Matplotlib to define what colors to use
# sns.pairplot(tips_df, hue='sex', palette='Blues')

# Rug Plot 
# Single col plot
sb.rugplot(X)

##################################################################################################

# Styling 

# Style of 
sb.set_style('white')

# Figure size
plt.figure(figsize=(8,4))

# Change size of lables, lines and other elements to best fit
# how you will present your data (paper, talk, poster)
sb.set_context('paper', font_scale=1.4)

sb.jointplot(x='speeding', y='alcohol', data=data, kind='reg')

# Get rid of spines
# You can turn of specific spines with right=True, left=True
# bottom=True, top=True
sb.despine(left=False, bottom=False)

##################################################################################################

# Categorical Plots 

# Bar Plot 

# Aggregate categorical data based on a function (mean is the default)
# Estimate total bill amount based on sex
# With estimator you can define functions to use other than the mean like those
# provided by NumPy : median, std, var, cov or make your own functions
sb.barplot(x='sex',y='total_bill',data=tips_df, estimator=np.median)

# Counter Plot

# A count plot is like a bar plot, but the estimator is counting 
# the number of occurances
sb.countplot(x='sex',data=tips_df)

# Box Plot

plt.figure(figsize=(14,9))
sb.set_style('darkgrid')

# A box plot allows you to compare different variables
# The box shows the quartiles of the data. The bar in the middle is the median and
# the box extends 1 standard deviation from the median
# The whiskers extend to all the other data aside from the points that are considered
# to be outliers
# Hue can add another category being sex
# We see men spend way more on Friday versus less than women on Saturday
sb.boxplot(x='day',y='total_bill',data=tips_df, hue='sex')
# Moves legend to the best position
plt.legend(loc=0)

# Strip Plot

plt.figure(figsize=(8,5))

# The strip plot draws a scatter plot representing all data points where one
# variable is categorical. It is often used to show all observations with 
# a box plot that represents the average distribution
# Jitter spreads data points out so that they aren't stacked on top of each other
# Hue breaks data into men and women
# Dodge separates the men and women data
sb.stripplot(x='day',y='total_bill',data=tips_df, jitter=True, 
              hue='sex', dodge=True)

##################################################################################################

# Pair Grid 

plt.figure(figsize=(8,6))
sb.set_context('paper', font_scale=1.4)

iris = sb.load_dataset("iris")

# You can create a grid of different plots with complete control over what is displayed
# Create the empty grid system using the provided data
# Colorize based on species
# iris_g = sns.PairGrid(iris, hue="species")

# Put a scatter plot across the upper, lower and diagonal
# iris_g.map(plt.scatter)

# Put a histogram on the diagonal 
# iris_g.map_diag(plt.hist)
# And a scatter plot every place else 
# iris_g.map_offdiag(plt.scatter)

# Have different plots in upper, lower and diagonal
# iris_g.map_upper(plt.scatter)
# iris_g.map_lower(sns.kdeplot)

# You can define define variables for x & y for a custom grid
iris_g = sb.PairGrid(iris, hue="species",
                      x_vars=["sepal_length", "sepal_width"],
                      y_vars=["petal_length", "petal_width"])

iris_g.map(plt.scatter)

# Add a legend last
iris_g.add_legend()

##################################################################################################

# Matrix Plots 

# Heat maps 

plt.figure(figsize=(8,6))
sb.set_context('paper', font_scale=1.4)

# To create a heatmap with data you must have data set up as a matrix where variables
# are on the columns and rows

# Correlation tells you how influential a variable is on the result
# So we see that n previous accident is heavily correlated with accidents, while the
# insurance premium is not
crash_mx = crash_df.corr()

# Create the heatmap, add annotations and a color map
sb.heatmap(crash_mx, annot=True, cmap='Blues')

plt.figure(figsize=(8,6))
sb.set_context('paper', font_scale=1.4)

# We can create a matrix with an index of month, columns representing years
# and the number of passengers for each
# We see that flights have increased over time and that most people travel in
# July and August
flights = sb.load_dataset("flights")
flights = flights.pivot_table(index='month', columns='year', values='passengers')

# You can separate data with lines
sb.heatmap(flights, cmap='Blues', linecolor='white', linewidth=1)

# Cluster Map 

# A Cluster map is a hierarchically clustered heatmap
# The distance between points is calculated, the closest are joined, and this
# continues for the next closest (It compares columns / rows of the heatmap)
# This is data on iris flowers with data on petal lengths

plt.figure(figsize=(8,6))
sb.set_context('paper', font_scale=1.4)

iris = sb.load_dataset("iris")
# Return values for species
# species = iris.pop("species")
# sns.clustermap(iris)

# With our flights data we can see that years have been reoriented to place
# like data closer together
# You can see clusters of data for July & August for the years 59 & 60
# standard_scale normalizes the data to focus on the clustering
sb.clustermap(flights,cmap="Blues", standard_scale=1)


#####################################################################################

# Regression Plots 

# lmplot combines regression plots with facet grid
tips_df = sb.load_dataset('tips')
tips_df.head()

plt.figure(figsize=(8,6))
sb.set_context('paper', font_scale=1.4)

plt.figure(figsize=(8,6))

# We can plot a regression plot studying whether total bill effects the tip
# hue is used to show separation based off of categorical data
# We see that males tend to tip slightly more
# Define different markers for men and women
# You can effect the scatter plot by passing in a dictionary for styling of markers
sb.lmplot(x='total_bill', y='tip', hue='sex', data=tips_df, 
          scatter_kws={'s': 100, 'linewidth': 0.5, 'edgecolor': 'w'})

