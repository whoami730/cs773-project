import numpy as np
import matplotlib.pyplot as plt
import sys

data = np.loadtxt(sys.argv[1], delimiter=';')
hist, bins = np.histogram(data[::2], bins=50)
plt.plot(bins[1:], hist, label='miss')

hist, bins = np.histogram(data[1::2], bins=50)
plt.plot(bins[1:], hist, label='hit')

plt.legend()
plt.grid()
plt.show()
