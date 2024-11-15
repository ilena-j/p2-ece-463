# script to run experiments for report graph #1
import numpy as np
from matplotlib import pyplot as plt
import subprocess

# array indices -- bimodal command
M_INDEX = 2
N_INDEX = 3
TRACE_INDEX = 4

args = ["./sim", "gshare", "0", "0", "filename"]

args[TRACE_INDEX] = "traces/gcc_trace.txt"

colors = [  'crimson', 
            'orangered',
            'orange',
            'gold',
            'greenyellow',
            'forestgreen',
            'mediumaquamarine',
            'turquoise',
            'deepskyblue',
            'mediumblue',
            'mediumslateblue',
            'darkviolet',
            'fuchsia',
            'deeppink'
        ]
for i in range (0, 14):
    m = i + 7
    args[M_INDEX] = str(m)
    ns = []
    rates = []

    for n in range (m+1):
        args[N_INDEX] = str(n)
        output = subprocess.run(args, stdout=subprocess.PIPE)
        
        ns.append(n)
        rates.append(float(output.stdout))

    print("M = ", m, ": min = ", min(rates), " at N = ", rates.index(min(rates)))
    plt.plot(ns, rates, '.-', color=colors[i], label=('M='+str(m)))

plt.xlabel('N')
plt.ylabel('Misprediction Rate (%)')
plt.show()