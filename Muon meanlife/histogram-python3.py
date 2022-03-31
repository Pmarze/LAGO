"""
Created on Mar 2022

@author: Pablo Martinez
"""

from ROOT import *
import sys

if( len(sys.argv) < 2 ):
    print("No filename given")
    sys.exit()

Data1 = sys.argv[1]                     # Data file to analyze

datos=[]
f = open(Data1, "r")

lines = f.readlines()
for line in lines:
    a=line.replace("\n","")
    datos.append(float(a))

h1 = TH1F("A*exp(-1/\\tau)+B", "Muon decay time", 20, 0.24, 10)
for pulse in datos:
    h1.Fill(pulse)

f1 = TF1("f1","[0]*exp(-x/[1])+[2]",0,10);

f1.SetParameters(1,2,5)
f1.SetParNames("A","\\tau","B")
h1.SetFillColor(38)
h1.GetXaxis().SetTitle("\\mu seconds")
h1.GetYaxis().SetTitle("pulse count")
h1.GetYaxis().SetNdivisions(6)
h1.GetXaxis().SetNdivisions(10)
h1.SetLineColor(kCyan-6)
h1.SetFillStyle(3018) 
f1.SetLineColor(kAzure-3)
h1.Fit("f1")

gStyle.GetName()
gStyle.SetOptFit(1)
gStyle.SetOptStat(73)
#si = h1.FindObject("stats")
#si.SetX1NDC(6)
#c1 = TCanvas()

#h1.Draw()
input()