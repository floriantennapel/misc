import numpy as np
import matplotlib.pyplot as plt

houses = [(4, 7), (-4, 0), (7, -6), (-2, 4), (8, -5)]

xs = np.linspace(min([l for l, _ in houses]), max([l for l, _ in houses]), 100000)
ys = np.zeros(len(xs)) 

for i, x in enumerate(xs):
    ys[i] = np.sqrt(sum([(x - x_i)**2 + y_i**2 for x_i, y_i in houses]))


plt.plot(xs, ys)
plt.show()
