import scipy.signal as signal
import matplotlib.pyplot as plt

import urllib2
import StringIO
import csv
import numpy as np
from datetime import datetime
 

#response = urllib2.urlopen('http://lobo.satlantic.com/cgi-data/nph-data.cgi?min_date='
#                           +startdate+'&max_date='+enddate+'&y=temperature')

response = open('Data.csv', 'rb')
 
data = StringIO.StringIO(response.read())
 
r = csv.DictReader(data)
data.seek(0)


time = []
volt = []

for row in r:
	time.append(row['time'])
	volt.append(row['volt'])



volt = np.array(volt)
volt = volt.astype(np.float)

N = 4
Wn = .015
B, A = signal.butter(N, Wn, output = 'ba')

voltf = signal.filtfilt(B,A, volt)

fig = plt.figure()
ax1 = fig.add_subplot(211)
plt.plot(time, volt, 'b-')
plt.plot(time, voltf, 'r')
plt.show()
'''
temp = np.array(temp)
temp = temp.astype(np.float) #...of floats
 
# First, design the Buterworth filter
N  = 2    # Filter order
Wn = 0.01 # Cutoff frequency
B, A = signal.butter(N, Wn, output='ba')
 
# Second, apply the filter
tempf = signal.filtfilt(B,A, temp)
for i in tempf:
	print i
 
# Make plots
fig = plt.figure()
#ax1 = fig.add_subplot(211)
plt.plot(date,temp, 'b-')
plt.plot(date,tempf, 'r-',linewidth=2)
plt.ylabel("Temperature (oC)")
plt.xlabel("Date");
plt.legend(['Original','Filtered'])
plt.title("Temperature from LOBO (Halifax, Canada)")
#ax1.axes.get_xaxis().set_visible(False)
 
plt.show()'''