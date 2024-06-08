###################################################
# Author: Dheeraj Vittal Shenoy
# Filename: monte_carlo_pi.py
# Date: 08-01-2023
# Approximate value of the constant PI using Monte-Carlo methods
###################################################

import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import matplotlib.artist as artist
import numpy as np
import random as rand

class MonteCarloPi:
    """
    Class for handling the simulation
    """
    def __init__(self, iteration = 1000,
                 animate = False):
        self.iteration = iteration
        self.r = 1
        self.point_inside_circle = 0
        self.do_animation = animate
        self.fig, self.ax = plt.subplots(nrows=2, ncols=1)
        self.fig.suptitle("Monte Carlo method for approximating the value of PI")
        self.monte_carlo_pi()
    
    # check whether the random point generated is within the circle
    def IsPointInsideCircle(self, x, y):
        if x**2 + y**2 <= self.r**2:
            self.point_inside_circle += 1

    # return the approximation for PI
    def GetPI(self):
        return 4 * self.point_inside_circle / self.iteration

    def monte_carlo_pi(self):

        self.ax[0].set_aspect("equal")
        self.ax[0].set_xlim([-1.5, 1.5])
        self.ax[0].set_ylim([-1.5, 1.5])

        self.ax[1].set_ylim([0, 4])
        self.ax[1].set_xlim([0, self.iteration])
        self.ax[1].axhline(np.pi, linestyle='dashed')
        self.ax[1].grid()
        

        self.ax[0].grid()
        circle = plt.Circle((0, 0), self.r, alpha = 0.5, fill = True, linewidth = 3)
        square = plt.Rectangle((-1, -1), width = 2, height = 2,
                               color='red',
                               alpha = 0.5,
                               fill = False,
                               linewidth = 3)
        self.ax[0].add_artist(circle)
        self.ax[0].add_artist(square)

        if not self.do_animation:
            for i in range(self.iteration):
                x = rand.uniform(-1, 1)
                y = rand.uniform(-1, 1)
                self.IsPointInsideCircle(x, y)
                self.ax[0].plot(x, y, '.b')
        else:
            self.animate()
    
    def _animate_init_func(self):
        self.data_point, = self.ax[0].plot([], [])
        self.pi_text = self.fig.text(0.1, 0.75, 'PI = ')
        self.N_text = self.fig.text(0.8, 0.75, 'N = ')
        
        self.calc_pi_point = self.ax[1].plot([], [])
        return self.data_point, self.pi_text, self.calc_pi_point

    def _animate_helper(self, i):
        x = rand.uniform(-1, 1)
        y = rand.uniform(-1, 1)
        self.IsPointInsideCircle(x, y)
        self.data_point = self.ax[0].plot(x, y, '.g', alpha = 0.5, ms = 1.5)
        pi = self.GetPI()
        self.ax[1].plot(i, pi, '.b')
        self.pi_text.set_text('PI = ' + str(round(pi, 3)))
        self.N_text.set_text('N = ' + str(i))
        return self.data_point,
        

    def animate(self):
        anim = FuncAnimation(self.fig,
                             self._animate_helper,
                             init_func=self._animate_init_func,
                             frames = self.iteration,
                             interval = 10,
                             repeat = False)
        # anim.save('animation.mp4')
        plt.show()

if __name__ == "__main__":
    MonteCarloPi(300, animate = True)
