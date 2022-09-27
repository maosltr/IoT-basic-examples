import csv
import random
import time
import os

os.remove('../logs/swc1_log.csv')
os.remove('../logs/swc3_log.csv')
column_name = ["time", "cpu load"]

with open('../logs/swc1_log.csv', 'a') as f:
    writer = csv.writer(f)
    writer.writerow(column_name)
    f.close()

with open('../logs/swc3_log.csv', 'a') as f:
    writer = csv.writer(f)
    writer.writerow(column_name)
    f.close()

x1 = 0
y1 = 0
x3 = 0
y3 = 0
missing_samples = 0

while True:  
    with open('../logs/swc1_log.csv', 'a') as f:
        writer = csv.writer(f)  
        writer.writerow([x1, y1])
        x1 += 1
        y1 += 1

    with open('../logs/swc3_log.csv', 'a') as f:
        writer = csv.writer(f)  
        missing_samples = missing_samples + random.randint(0,1)
        writer.writerow([x3, y3 - missing_samples])
        x3 += 1
        y3 += 1

    time.sleep(1)