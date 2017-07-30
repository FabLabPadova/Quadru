from GhostClient import GhostClient
from GhostEntity import GhostEntity
from GhostPart import TypePartGhost
import time

def startSend():
    try:
        gh = GhostClient()
    except:
        print("No connection established.")
    with open('logquadru.txt', 'r') as f:
        lines = f.readlines()

    for l in lines:
        l = l.replace('\ufeff', '')
        gh.parsingLine(l)
        print(gh.send_all())

def setLegTry():
    try:
        gh = GhostClient()
    except:
        print("No connection established.")
        exit(1)

    print(gh.set_leg(0, TypePartGhost.FEMUR, 1362))
    print(gh.set_leg(0, TypePartGhost.TIBIA, 1205))
    time.sleep(1)
    print(gh.set_leg(0, TypePartGhost.FEMUR, 1386))
    print(gh.set_leg(0, TypePartGhost.TIBIA, 1166))
    time.sleep(1)

startSend()
#setLegTry()
