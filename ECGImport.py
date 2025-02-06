# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

from matplotlib import pyplot as plt
import numpy as np
import csv
import scipy as sp


t = []
v = []

with open('LabII_2.3.csv','r') as data:                  #Opens the CSV file
    v_data = csv.reader(data, delimiter = ',')        #Reads the CSV file and stores in matrix
    
    for row in v_data:
        t.append(float(row[0]))
        v.append(float(row[1]))
        
#t = np.arange(0,len(v)/16000,1/16000)        
len(v)
len(t)

plt.close('all')
plt.subplot(2,1,1)
plt.plot(t,v)
plt.xlabel('Time (s)')
plt.ylabel('Voltage (v)')
plt.xlim(0,5)

#Create frequency domain representation of signal
fs = 1000           #Sampling frequency of signal
f = np.linspace(0,fs,len(v))

V = sp.fft.fft(v)
VdB = 20*np.log10(abs(V))

plt.subplot(2,1,2)
plt.plot(f,VdB)
plt.xlabel('Frequency (Hz)')
plt.ylabel('Amplitude (dB)')






