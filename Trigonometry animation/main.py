import matplotlib.pyplot as plt
import numpy as np
from matplotlib.lines import Line2D
from matplotlib.animation import FuncAnimation

r = 1
N = 10

fig, ax = plt.subplots()

# Set the aspect ratio of the plot to be equal
ax.set_aspect('equal', adjustable='box')

# Plot the circle
circle = plt.Circle((0, 0), radius=r, edgecolor='b', facecolor='none')
ax.add_patch(circle)

mini_points = []

def bisect_circle(num_lines):
    # Create a figure and axis
    # Calculate the angles for the lines
    angles = np.linspace(0, 2 * np.pi, num_lines, endpoint=False)
    
    lines = []

    # Plot the lines
    for angle in angles:
        x = np.cos(angle)
        y = np.sin(angle)
        line = Line2D([0, x], [0, y], color='gray')
        lines.append(line)
        ax.add_artist(line)

    # Set the limits of the plot
    ax.set_xlim([-1.5, 1.5])
    ax.set_ylim([-1.5, 1.5])

    # Set the aspect ratio of the plot to be equal
    ax.set_aspect('equal', adjustable='box')

def init_points_on_lines(N):
    for i in range(int(N/2)):
        p = plt.Circle((r, 0), radius=0.025, facecolor='blue')
        ax.add_artist(p)
        mini_points.append(p)

_x = r
_y = 0
angles = np.linspace(0, 2 * np.pi, N, endpoint=False)

def animate_point_on_circle(i):
    global _x, _y
    x = r * np.cos(i)
    y = r * np.sin(i)
    point.set_center(xy=(x, y))

    for j in range(int(N/2)):
        _x = y * np.cos(angles[j])
        _y = y * np.sin(angles[j])
        mini_points[j].set_center(xy=(_x, _y))

    return [mini_points, point]

init_points_on_lines(N)
bisect_circle(N)

point = plt.Circle((r, 0), radius=0.05, edgecolor='k', facecolor='red')
ax.add_patch(point)

t = np.linspace(0, 2 * np.pi, 200)
anim = FuncAnimation(fig, func=animate_point_on_circle, frames=t, interval=1)
plt.show()
