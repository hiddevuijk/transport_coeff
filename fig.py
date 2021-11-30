import numpy as np
import matplotlib.pyplot as plt
from sys import exit

msd = np.loadtxt("msd.dat");
t = msd[1:,0]
y = msd[1:,1]

D = (y[-1] - y[0] )/(t[-1] - t[0])
D/=2

plt.loglog(t,y)
plt.title(D)
plt.show()
