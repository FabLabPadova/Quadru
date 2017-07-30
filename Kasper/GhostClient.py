import sys
import telnetlib
from GhostEntity import GhostEntity
import json

class GhostClient(GhostEntity):

    HOST = "192.168.1.247"

    def __init__(self):
        GhostEntity.__init__(self)
        self.tn = telnetlib.Telnet(self.HOST, '80')


    def sendAll(self):
        send_json = json.dumps(self.toDict(), separators=(',',':'))
        try:
            self.tn.write((send_json + "$").encode('ascii'))
        except:
            print("No send to host.")
        return send_json
