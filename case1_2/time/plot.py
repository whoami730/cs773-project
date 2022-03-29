import numpy as np
import matplotlib.pyplot as plt
import sys

data = np.loadtxt(sys.argv[1], delimiter=';')
d1,d2 = data[::2], data[1::2]
print(f"Case 1 : {np.mean(d1)*1000} +- {np.std(d1)*1000} ; {np.median(d1)*1000}")
hist, bins = np.histogram(d1*1000, bins=50)
plt.plot(bins[1:], hist, label='case1')
print(f"Case 2 : {np.mean(d2)*1000} +- {np.std(d2)*1000} ; {np.median(d2)*1000}")
hist, bins = np.histogram(d2*1000, bins=50)
plt.plot(bins[1:], hist, label='case2')
# print(f"Case 3 : {np.mean(d3)*1000} +- {np.std(d3)*1000} ; {np.median(d3)*1000}")
# hist, bins = np.histogram(d3*1000, bins=50)
# plt.plot(bins[1:], hist, label='case3')

plt.ylabel('Density')
plt.xlabel('Time')

# plt.title('Different types of accesses')
plt.legend()
plt.grid()
plt.show()
