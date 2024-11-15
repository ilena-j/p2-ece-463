# script to run experiments for report graph #1
import numpy as np
from matplotlib import pyplot as plt
import subprocess

# array indices -- bimodal command
M_INDEX = 2
TRACE_INDEX = 3

args = ["./sim", "bimodal", "0", "filename"]

args[TRACE_INDEX] = "traces/perl_trace.txt"

ms = []
rates = []
for i in range (0, 14):
    m = i + 7
    args[M_INDEX] = str(m)
    output = subprocess.run(args, stdout=subprocess.PIPE)
    ms.append(m)
    rates.append(float(output.stdout))

plt.plot(ms, rates, '.-', color='orchid')
plt.xlabel('M')
plt.ylabel('Misprediction Rate (%)')
plt.show()