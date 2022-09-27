
#from random import random
import random
#import numpy as np
import matplotlib.pyplot as plt
import shutil

import pandas as pd
import csv

plt.axis([0, 50, 0, 50])
plt.xlabel('time (s)')
plt.ylabel('number of samples')

for i in range(50):
    #y = np.random.random()
    #a = i
    #b = 2*i
    #c = 3*i
    #d = 4*i
    #plt.scatter(i, y)
    #plt.scatter(i, a, color="blue")
    #plt.scatter(i, b, color="red")

    ## copy log data
    shutil.copyfile("../logs/swc1_log.csv", "temp/swc1.csv")
    shutil.copyfile("../logs/swc3_log.csv", "temp/swc3.csv")

    ## SWC1
    swc1 = pd.read_csv("temp/swc1.csv")
    plt.scatter(swc1["time"], swc1["cpu load"], color="green")

    ## SWC3
    swc3 = pd.read_csv("temp/swc3.csv")
    plt.scatter(swc3["time"], swc3["cpu load"], color="red")

    plt.pause(1)

plt.show()
