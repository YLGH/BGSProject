import numpy as np
import matplotlib.pyplot as plt
from obspy.core import read
import random
singlechannel = read('http://examples.obspy.org/COP.BHZ.DK.2009.050')

plt.ion()
plt.show()
#ax.set_autoscale_on(False);
plt.ylim([-5000,5000])


count = 0;
i = 0;
while True:
	if(i == 200):
		break;
	y = singlechannel[0].data[i];
	#y = random.uniform(-2500,2500);
	plt.scatter(i, y, marker = '.', linestyle = '--')
	plt.draw()


	count+=1;
	if(i % 20 == 0):
		plt.clf()
		plt.xlim([i, i+5])
		plt.scatter(i, -4500, marker = ".");
		plt.scatter(i, 4500, marker = ".");
		count = 0;
	else:
		plt.xlim([i-count, i+5]);

	i+=1;


