import numpy as np
import matplotlib.pyplot as plt
import sys

for input in sys.argv[1:]:
  data = np.loadtxt(input, delimiter=';')

  data = data * 1000

  hist, bins = np.histogram(data, bins=50)
  plt.plot(bins[1:], hist, label=input)

  print(input)
  print("mean+-std: " + str(np.mean(data)) + "+-" + str(np.std(data)) + "nJ")
  print("median: " + str(np.median(data)) + "nJ")
  print()

plt.ylabel("Density")
plt.xlabel("Energy in nJ")

plt.title("Instruction Comparison")
plt.legend()
plt.grid()
plt.show() 
