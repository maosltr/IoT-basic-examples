
#from random import random
import random
#import numpy as np
import matplotlib.pyplot as plt
import shutil

import pandas as pd
import csv

init = 0
plt.xlabel('time (s)')
plt.ylabel('number of samples')



for i in range(100):
    #y = np.random.random()
    #a = i
    #b = 2*i
    #c = 3*i
    #d = 4*i
    #plt.scatter(i, y)
    #plt.scatter(i, a, color="blue")
    #plt.scatter(i, b, color="red") 

    ## copy log data
    shutil.copyfile("../application/logs/node1_log.csv", "temp/node1_log.csv")
    shutil.copyfile("../application/logs/node2_log.csv", "temp/node2_log.csv")
    shutil.copyfile("../application/logs/node3_log.csv", "temp/node3_log.csv")
    shutil.copyfile("../application/logs/node4_log.csv", "temp/node4_log.csv")

    ## node1
    node1 = pd.read_csv("temp/node1_log.csv")

    # init the plot range 
    if init == 0:
        plt.axis([node1["ts"][1],node1["ts"][1]+50, 0, 50])
        init == 1
    plt.scatter(node1["ts"], node1["counter"], color="green")


    ## node2
    node2 = pd.read_csv("temp/node1_log.csv")
    #plt.scatter(node2["ts"], node2["counter"], color="yellow")
    ## node3
    node3 = pd.read_csv("temp/node3_log.csv")
    plt.scatter(node3["ts"], node3["counter"], color="blue")
    ## node4
    node4 = pd.read_csv("temp/node4_log.csv")
    plt.scatter(node4["ts"], node4["counter"], color="red")

    plt.pause(1)

plt.show()
