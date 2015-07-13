import matplotlib.pyplot as plt
import numpy as np

x = xrange(0,2000);
y = xrange(0,2000);

plt.plot(x, y, label='linear')
#plt.plot(x, x**2, label='quadratic')
#plt.plot(x, x**3, label='cubic')

plt.xlabel('x label')
plt.ylabel('y label')

plt.title("Simple Plot")

plt.legend()

plt.show()