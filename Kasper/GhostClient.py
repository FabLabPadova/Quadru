import sys
import telnetlib
from GhostEntity import GhostEntity
import json
import socket
from queue import *

class GhostClient(GhostEntity):

    HOST = '192.168.1.247'
    PORT = 80

    def __init__(self):
        GhostEntity.__init__(self)
        self.tn = telnetlib.Telnet(self.HOST, self.PORT)


    def send_all(self):
        return self.__send_packet(self.toDict())

    def set_leg(self, n_leg, type, value, send=True):
        new_leg = super(GhostClient, self).set_leg(n_leg, type, value)
        if send:
            self.__send_packet(new_leg)
        return self.__json_dumps(new_leg)

    @staticmethod
    def __json_dumps(dict):
        return json.dumps(dict, separators=(',',':'))

    def __send_packet(self, dict_param):
        if not isinstance(dict_param, dict):
            raise ValueError('dict_param is not a dictionary')
        send_json = self.__json_dumps(dict_param)
        try:
            self.tn.write((send_json + "$").encode('ascii'))
        except:
            print("No send to host.")
        return send_json
