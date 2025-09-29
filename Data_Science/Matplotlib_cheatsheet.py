import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import animation

# --------------------------------------------------
# Random Data Setup
# --------------------------------------------------
X_data = np.random.random(50) * 100
Y_data = np.random.random(50) * 100

# --------------------------------------------------
# Scatter Plot
# Customization options: color, marker, size (s), alpha (transparency), cmap (color map)
# --------------------------------------------------
plt.scatter(X_data, Y_data, color='blue', marker='o', s=50, alpha=0.7)
plt.title("Scatter Plot Example")
plt.xlabel("X Axis")
plt.ylabel("Y Axis")
plt.show()

# --------------------------------------------------
# Line Plot
# Customization options: linestyle ('-', '--', ':'), color, linewidth, marker
# --------------------------------------------------
years = [200 + i for i in range(50)]
weights = np.random.random(50) * 50

plt.plot(years, weights, color='red', linestyle='--', linewidth=2, marker='o')
plt.title("Line Plot Example")
plt.xlabel("Years")
plt.ylabel("Weights")
plt.show()

# --------------------------------------------------
# Bar Plot
# Customization options: color, width, edgecolor, orientation (barh for horizontal)
# --------------------------------------------------
x = ['C++', 'Rust', 'C', 'Py', 'Java', 'Bash']
y = [20, 30, 40, 10, 30, 5]

plt.bar(x, y, color='green', edgecolor='black')
plt.title("Bar Chart Example")
plt.show()

# --------------------------------------------------
# Histogram
# Customization options: bins, color, cumulative, density, alpha
# --------------------------------------------------
ages = np.random.normal(20, 1.5, 1000)  # mean, standard deviation, samples

plt.hist(ages, bins=20, color='purple', alpha=0.7)
plt.title("Histogram Example")
plt.xlabel("Age")
plt.ylabel("Frequency")
plt.show()

# --------------------------------------------------
# Pie Chart
# Customization options: labels, autopct (percentages), colors, explode
# --------------------------------------------------
plt.pie(y, labels=x, autopct='%1.1f%%', startangle=90)
plt.title("Pie Chart Example")
plt.show()

# --------------------------------------------------
# Boxplot
# Customization options: notch, vert (vertical/horizontal), patch_artist (colors)
# --------------------------------------------------
plt.boxplot(ages, notch=True, patch_artist=True)
plt.title("Boxplot Example")
plt.show()

# --------------------------------------------------
# Legend
# Customization options: location (loc), fontsize, title, shadow, frameon
# --------------------------------------------------
plt.plot(years, np.random.random(50)*100, label="Experiment A")
plt.plot(years, np.random.random(50)*100, label="Experiment B")
plt.title("Legend Example")
plt.xlabel("Years")
plt.ylabel("Values")
plt.legend(loc="upper right", fontsize=10, title="Experiments", shadow=True)
plt.show()

# --------------------------------------------------
# Multiple Plots with Labels
# --------------------------------------------------
plt.plot(years, np.random.random(50)*100, label="Line 1")
plt.plot(years, np.random.random(50)*50, label="Line 2")
plt.title("Multiple Line Example")
plt.xlabel("Years")
plt.ylabel("Values")
plt.legend()
plt.show()

# --------------------------------------------------
# Plot Styling
# Customization options: plt.style.use("style_name")
# Common styles: 'seaborn', 'ggplot', 'fivethirtyeight', 'classic'
# --------------------------------------------------
plt.style.use("seaborn-v0_8")
plt.plot(years, np.random.random(50)*100, label="Styled Line")
plt.title("Styled Plot Example")
plt.legend()
plt.show()

# --------------------------------------------------
# Multiple Figures
# Each figure can contain its own independent plot
# --------------------------------------------------
plt.figure(1)
plt.plot(years, np.random.random(50)*100, color='blue')
plt.title("Figure 1")

plt.figure(2)
plt.bar(x, y, color='orange')
plt.title("Figure 2")
plt.show()

# --------------------------------------------------
# Subplots
# Customization options: rows, cols, figsize, sharex, sharey
# --------------------------------------------------
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

# --------------------------------------------------
# Exporting Plots
# Common formats: PNG, JPG, PDF, SVG
# Options: dpi, bbox_inches
# --------------------------------------------------
plt.plot(years, weights, label="Export Example")
plt.title("Exporting Plot Example")
plt.legend()
plt.savefig("exported_plot.png", dpi=300, bbox_inches="tight")
plt.show()

# --------------------------------------------------
# Plot Customization (titles and labels demo)
# --------------------------------------------------
plt.plot(years, np.random.random(50)*100)
plt.title("Title Example")
plt.xlabel("Year")
plt.ylabel("Dollar")
plt.show()

# --------------------------------------------------
# 3D Scatter Plot
# Customization options: marker, color, cmap, size (s), alpha
# --------------------------------------------------
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
x = np.random.random(100)
y = np.random.random(100)
z = np.random.random(100)


ax.scatter(x, y, c=z, cmap='viridis', s=50, alpha=0.7)
ax.set_title("3D Scatter Plot")
plt.show()


# --------------------------------------------------
# 3D Surface Plot
# Customization options: cmap, edgecolor, linewidth, alpha
# --------------------------------------------------
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')


X = np.linspace(-5, 5, 100)
Y = np.linspace(-5, 5, 100)
X, Y = np.meshgrid(X, Y)
Z = np.sin(np.sqrt(X**2 + Y**2))


ax.plot_surface(X, Y, Z, cmap='plasma', edgecolor='none', alpha=0.9)
ax.set_title("3D Surface Plot")
plt.show()


# --------------------------------------------------
# 3D Wireframe Plot
# Customization options: color, linewidth, rstride, cstride
# --------------------------------------------------
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')


ax.plot_wireframe(X, Y, Z, color='black', linewidth=0.5)
ax.set_title("3D Wireframe Plot")
plt.show()


# --------------------------------------------------
# 3D Contour Plot
# Customization options: levels, cmap, offset, alpha
# --------------------------------------------------
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')


ax.contour3D(X, Y, Z, 50, cmap='inferno')
ax.set_title("3D Contour Plot")
plt.show()


# --------------------------------------------------
# Animating a 2D Line Plot
# --------------------------------------------------
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


# --------------------------------------------------
# Animating a 3D Rotating Surface
# --------------------------------------------------
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
surf = ax.plot_surface(X, Y, Z, cmap='viridis')


