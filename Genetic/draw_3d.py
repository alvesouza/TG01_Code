import numpy as np
import math
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
x = np.arange(0, 50, 1)
y = np.arange(0, 70, 1)
x, y = np.meshgrid(x, y)
z = np.exp((((x-25)/25)**2) + (((y-35)/35)**2))
fig = plt.figure()
axes = fig.gca(projection ='3d')
axes.plot_surface(x, y, z, alpha = 0.1)

def fun(x, y):
    return math.exp((((x-25)/25)**2) + (((y-35)/35)**2))

n = 10
xs = [i for i in range(n) for _ in range(n)]
ys = list(range(n)) * n
xs = np.arange(30, 50, 1)
ys = np.arange(50, 70, 1)
zs = [fun(x, y) for x,y in zip(xs,ys)]
axes.scatter3D(xs, ys, zs, c=zs, cmap='Greens', alpha = 1);

plt.show()