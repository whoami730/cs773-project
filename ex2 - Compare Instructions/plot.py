import numpy as np
import matplotlib.pyplot as plt
import sys

for input in sys.argv[1:]:
  data = np.loadtxt(input, delimiter=';')

  print(f"{input} : {np.mean(data)*1000} + {np.std(data)*1000} nJ")

  hist, bins = np.histogram(data, bins=50)
  plt.plot(bins[1:], hist, label=input)

plt.ylabel("Density")
plt.xlabel("Energy in uJ")

plt.title("Instruction Comparison")
plt.legend()
plt.grid()
plt.show() 
