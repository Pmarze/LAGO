#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mar 2022

@author: Pablo Martinez
"""

from re import M
from statistics import mean
import sys
from turtle import color
from typing import List
import numpy as np
import matplotlib.pyplot as plt
from paa01 import paaFile
import time 
from ROOT import *

def Discrim(Lista,tl,n):                # Function to select the correct pulses
    a = np.amin(Lista)
    pulse_i = 0                         # ubication of the first pulse
    pulse_j = 0                         # ubication of the second pulse
    pulse = 0                           # temporal index
    first = 0                           # determine whether it is the first or second pulse
    len0 = len(Lista)
    while(pulse < len0):
        if Lista[pulse] <= tl and first == 0:
            pulse_i = pulse
            pulse = pulse + n           # skip first pulse points
            first = 1                   # Detect the first pulse
        elif Lista[pulse] <= tl and first == 1:     # Second pulse detected
            pulse_j = pulse
            if Lista[pulse_i]<Lista[pulse_j]:       # Ensure that the first pulse detected is the most energetic
                return (pulse_j-pulse_i)*8/1000     # return time distance in micro seconds
            else:
                return -1
        else:
            pulse += 1
    return -1                           # No second pulse detected

def Graph(Axisx,Axisy,puls_name):       # Function to graph pulses
    plt.plot(Axisx, Axisy,'.')
    ax = plt.gca()
    ax.set_title(str(puls_name))
    plt.show()

###################################################################################################

if( len(sys.argv) < 2 ):
    print("No filename given")
    sys.exit()

Data1 = sys.argv[1]             # Configuration file with threshold and .paa name files
Data2 = sys.argv[2]             # Name of the output file
f_names = []                    # List only with .paa names

f1 = open(Data1, "r")
lines = f1.readlines()
for line in lines:
    a = line.replace("\n","")
    f_names.append(a)

succes = []                     # List of valid pulses
thres = float(f_names[0])       # Threshold to use in analysis

f_names.pop(0)                  # Only names in the list
iter = 0
total_time = 0
edge = "################################################################################\n"

###################################################################################################

for name in f_names:
    f_i = time.time()           # Time of analysis
    print(edge)
    DataFile = paaFile(name)
    if iter == 0:
        print( DataFile.paaGetTextHeader(0) )
        print( DataFile.paaGetTextHeader(4) )
        print(edge)
        iter = 1
    print( "file: " + name +"\n")
    print( DataFile.paaGetTextHeader(1) )
    print( DataFile.paaGetTextHeader(2) )    
    print( DataFile.paaGetTextHeader(3) )

    ps = DataFile.paaGetPulseSize()
    pc = DataFile.paaGetPulseCount()
    tl = DataFile.paaGetThresholdLevel()

    print("Points per pulse: ", ps, ", Pulses in this file: ", pc, ", threshold level: ", tl)
    print()

    pulse_data_t = list(range( ps ))

    count = 0                      # pulses per file
    for pulse in range(0, pc):
        pulse_data_v = DataFile.paaGetPulseRP(pulse)
        Discr = Discrim(pulse_data_v, thres, 20)
        if Discr > 0:
            count += 1
            succes.append(Discr)
    
    f_e = time.time()
    tm = f_e-f_i
    total_time = tm + total_time

    print("accepted pulses: ", count, ", time of analysis: ", round(tm,2), "s\n")

###################################################################################################

s_i = time.time()           # Time of second analysis
f2 = open(Data2, "a")
for pulse in succes:        # File with data obtained
    f2.write(str(pulse)+"\n")
f2.close()

h1 = TH1F("A*exp(-1/\\tau)+B", "Muon decay time", 20, 0.24, 10)     # Histogram with the pulses obtained

for value in succes:
    h1.Fill(value)

f0 = TF1("f1","[0]*exp(-x/[1])+[2]",0,10)           # Equation to fit
f0.SetParameters(1,2,5)
f0.SetParNames("A","\\tau","B")
f0.SetLineColor(kAzure-3)

h1.SetFillColor(38)
h1.GetXaxis().SetTitle("\\mu seconds")
h1.GetYaxis().SetTitle("pulse count")
h1.GetYaxis().SetNdivisions(6)
h1.GetXaxis().SetNdivisions(10)
h1.SetLineColor(kCyan-6)
h1.SetFillStyle(3018) 
h1.Fit("f1")

gStyle.GetName()
gStyle.SetOptFit(1)
gStyle.SetOptStat(73)

s_f = time.time()

print("\n time of second analysis: ", round(s_f-s_i,2),"s, total time: ",round(total_time,2) ,"s\n")

input()