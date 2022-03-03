import numpy as np
import matplotlib.pyplot as plt
import sys

data = np.loadtxt(sys.argv[1], delimiter=';')
d1,d2 = data[::2], data[1::2]
print(f"Miss : {np.mean(d1)*1000} +- {np.std(d1)*1000} ; {np.median(d1)*1000}")
hist, bins = np.histogram(data[::2], bins=50)
plt.plot(bins[1:], hist, label='miss')
print(f"Hit : {np.mean(d2)*1000} +- {np.std(d2)*1000} ; {np.median(d2)*1000}")
hist, bins = np.histogram(data[1::2], bins=50)
plt.plot(bins[1:], hist, label='hit')

plt.legend()
plt.grid()
plt.show()
