import sys
import telnetlib
from GhostEntity import GhostEntity
import json
from queue import *

class GhostClient(GhostEntity):

    HOST = "192.168.1.247"

    def __init__(self):
        GhostEntity.__init__(self)
        self.tn = telnetlib.Telnet(self.HOST, '80')


    def send_all(self):
        send_json = self.__json_dumps(self.toDict())
        try:
            self.tn.write((send_json + "$").encode('ascii'))
        except:
            print("No send to host.")
        return send_json

    def set_leg(self, n_leg, type, value, send=True):
        new_leg = self.__json_dumps(super(GhostClient, self).set_leg(n_leg, type, value))
        if send:
            try:
                self.tn.write(( new_leg + "$").encode('ascii'))
            except:
                print("No send to host.")
        return new_leg

    @staticmethod
    def __json_dumps(dict):
        return json.dumps(dict, separators=(',',':'))
