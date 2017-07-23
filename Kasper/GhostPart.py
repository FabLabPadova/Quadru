from enum import Enum

class TypePartGhost(Enum):

    FEMUR = 0
    TIBIA = 1
    ROTATION = 2

    @staticmethod
    def listValid():
        return (TypePartGhost.FEMUR, TypePartGhost.TIBIA, TypePartGhost.ROTATION)

class GhostPart:

    MAXVALUE = 2200
    MINVALUE = 800

    def __init__(self, type, value = round((MAXVALUE + MINVALUE)/2)):
        if self.MINVALUE > self.MAXVALUE:
            raise ValueError('MINVALUE('+str(self.MINVALUE)+') AND MAXVALUE('+str(self.MAXVALUE)+') have invalid values.')
        if type not in TypePartGhost.listValid():
            raise ValueError('type = '+str(type)+' is invalid for GhostPart')
        if not isinstance(value, int) or  value < self.MINVALUE or value > self.MAXVALUE:
            raise ValueError('value = '+str(value)+' is invalid for GhostPart')
        self.type = type
        self.value = value

    def set_value(self, new_value):
        if not GhostPart.is_number(new_value):
            raise ValueError('new_value is not a number.')
        new_value = int(new_value)
        if new_value not in range(self.MINVALUE, self.MAXVALUE+1):
            raise ValueError('new_value is not in range.')
        self.value = new_value

    @staticmethod
    def is_number(s):
        try:
            int(s)
            return True
        except ValueError:
            return False
