import numpy as np
import matplotlib.pyplot as plt
from matplotlib import animation
from itertools import combinations
from Particle import Particle
from scipy.stats import maxwell

class Simulator:
    """A class for a simple hard-circle molecular dynamics simulation.

    The simulation is carried out on a square domain: 0 <= x < 1, 0 <= y < 1.

    """

    def __init__(self, n, radius=0.01, styles=None):
        """Initialize the simulation with n Particles with radii radius.

        radius can be a single value or a sequence with n values.

        Any key-value pairs passed in the styles dictionary will be passed
        as arguments to Matplotlib's Circle patch constructor when drawing
        the Particles.

        """

        self.init_particles(n, radius, styles)
        self.particles[25].circle.set_facecolor('black')

    def init_particles(self, n, radius, styles=None):
        """Initialize the n Particles of the simulation.

        Positions and velocities are chosen randomly; radius can be a single
        value or a sequence with n values.

        """

        try:
            iterator = iter(radius)
            assert n == len(radius)
        except TypeError:
            # r isn't iterable: turn it into a generator that returns the
            # same value n times.
            def r_gen(n, radius):
                for i in range(n):
                    yield radius
            radius = r_gen(n, radius)

        self.n = n
        self.vs = np.empty(shape=(self.n,))
        self.v = 0
        self.dv = 0.01
        self.particles = []
        for i, rad in enumerate(radius):
            # Try to find a random initial position for this particle.
            while True:
                # Choose x, y so that the Particle is entirely inside the
                # domain of the simulation.
                x, y = rad + (1 - 2*rad) * np.random.random(2)
                # Choose a random velocity (within some reasonable range of
                # values) for the Particle.
                vr = 0.5 * np.random.random() + 0.05
                vphi = 2*np.pi * np.random.random()
                vx, vy = vr * np.cos(vphi), vr * np.sin(vphi)
                particle = Particle(x, y, vx, vy, rad, styles)
                # Check that the Particle doesn't overlap one that's already
                # been placed.
                for p2 in self.particles:
                    if p2.overlaps(particle):
                        break
                else:
                    self.particles.append(particle)
                    break

    def handle_collisions(self):
        """Detect and handle any collisions between the Particles.

        When two Particles collide, they do so elastically: their velocities
        change such that both energy and momentum are conserved.

        """

        def change_velocities(p1, p2):
            """
            Particles p1 and p2 have collided elastically: update their
            velocities.

            """

            m1, m2 = p1.radius**2, p2.radius**2
            M = m1 + m2
            r1, r2 = p1.r, p2.r
            d = np.linalg.norm(r1 - r2)**2
            v1, v2 = p1.v, p2.v
            u1 = v1 - 2*m2 / M * np.dot(v1-v2, r1-r2) / d * (r1 - r2)
            u2 = v2 - 2*m1 / M * np.dot(v2-v1, r2-r1) / d * (r2 - r1)
            p1.v = u1
            p2.v = u2

        # We're going to need a sequence of all of the pairs of particles when
        # we are detecting collisions. combinations generates pairs of indexes
        # into the self.particles list of Particles on the fly.
        pairs = combinations(range(self.n), 2)
        for i,j in pairs:
            if self.particles[i].overlaps(self.particles[j]):
                change_velocities(self.particles[i], self.particles[j])

    def advance_animation(self, dt):
        """Advance the animation by dt, returning the updated Circles list."""

        for i, p in enumerate(self.particles):
            p.advance(dt)
            self.circles[i].center = p.r
        self.handle_collisions()
        return self.circles

    def advance(self, dt):
        """Advance the animation by dt."""
        for i, p in enumerate(self.particles):
            p.advance(dt)
        self.handle_collisions()

    def init(self):
        """Initialize the Matplotlib animation."""

        self.circles = []
        self.hist, self.histbins, self.histpatches = self.ax[1].hist(self.vs,
                                                                     bins=30,
                                                                     density=True,
                                                                     color='blue',
                                                                     edgecolor='black',
                                                                     alpha=0.7)
        for particle in self.particles:
            self.circles.append(particle.draw(self.ax[0]))
        return self.circles

    def animate(self, i):
        """The function passed to Matplotlib's FuncAnimation routine."""
        self.advance_animation(0.01)
        self.__get_velocity_histrogram()
        self.maxwell_curve = self.ax[1].plot(self.maxwell_x_range,
                                             self.pdf_fitted,
                                             'r-',
                                             label='Maxwell-Boltzmann Fit')
        hist, _ = np.histogram(self.vs, bins=self.histbins)
        for patch, h in zip(self.histpatches, hist):
            patch.set_height(h)

        self.patch_list = self.circles + list(self.histpatches) + self.maxwell_curve
        return self.patch_list

    def do_animation(self, save=False):
        """Set up and carry out the animation of the molecular dynamics.

        To save the animation as a MP4 movie, set save=True.
        """

        self.fig, self.ax = plt.subplots(nrows=1, ncols=2)
        self.ax[1].set_title("MB Distribution")
        self.ax[1].set_xlim(0, 2)
        self.ax[1].set_ylim(0, 10)
        for s in ['top','bottom','left','right']:
            self.ax[0].spines[s].set_linewidth(2)
        self.ax[0].set_aspect('equal', 'box')
        self.ax[0].set_xlim(0, 1)
        self.ax[0].set_ylim(0, 1)
        self.ax[0].xaxis.set_ticks([])
        self.ax[0].yaxis.set_ticks([])
        anim = animation.FuncAnimation(self.fig, self.animate, init_func=self.init,
                               frames=800, interval=2, blit=True)

        if save:
            Writer = animation.writers['ffmpeg']
            writer = Writer(fps=100, bitrate=1800)
            anim.save('collision.mp4', writer=writer)
        else:
            plt.show()

    def __get_velocity_histrogram(self):

        for i, p in enumerate(self.particles):
            v = np.sqrt(p.v[0]**2 + p.v[1]**2)
            self.vs[i] = v

        self.maxwell_x_range = np.linspace(0, max(self.vs), 100)
        # self.mb_cdf = maxwell.cdf(self.maxwell_x_range)
        self.params = maxwell.fit(self.vs, floc=0)
        self.pdf_fitted = maxwell.pdf(self.maxwell_x_range, *self.params)
