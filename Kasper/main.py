from GhostClient import GhostClient
import time

gh = GhostClient()
with open('logquadru.txt', 'r') as f:
    lines = f.readlines()

while True:
    for l in lines:
        l = l.replace('\ufeff', '')
        gh.parsingLine(l)
        print(gh.sendAll())
        time.sleep(0.10)
