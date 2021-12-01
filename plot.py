import numpy as np
import matplotlib.pyplot as plt
from sys import exit

msd = np.loadtxt("msdx.dat");
t = msd[1:,0]
x = msd[1:,1]
msd = np.loadtxt("msdy.dat");
y = msd[1:,1]

Dx = (x[-1] - x[0] )/(t[-1] - t[0])
Dx/=2
Dy = (y[-1] - y[0] )/(t[-1] - t[0])
Dy/=2

plt.scatter(t,x)
plt.scatter(t,y)
#plt.yscale('log')
#plt.xscale('log')
plt.title("Dx = {:1.4f}  Dy = {:1.4f}".format(Dx,Dy))
plt.show()
