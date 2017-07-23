from GhostPart import GhostPart
from GhostPart import TypePartGhost

class GhostLeg:

    def __init__(self):
        self.parts = self.listCompose()

    @staticmethod
    def listCompose():
        return (GhostPart(TypePartGhost.FEMUR), GhostPart(TypePartGhost.TIBIA), GhostPart(TypePartGhost.ROTATION))