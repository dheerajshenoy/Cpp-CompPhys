import numpy as np
from Simulator import Simulator

if __name__ == '__main__':
    nparticles = 50
    #radii = np.random.random(nparticles)*0.03+0.02
    radii = 0.025
    styles = {'linewidth': 2, 'fill': True}
    sim = Simulator(nparticles, radii, styles)
    sim.do_animation(save=False)
