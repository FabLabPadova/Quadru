from GhostEntity import GhostEntity
from GhostPart import GhostPart
from GhostPart import TypePartGhost
from GhostLeg import GhostLeg
import unittest2
from random import randint

class TestGhostEntity(unittest2.TestCase):

    def testPartsValueRange(self):
        GhostPart.MINVALUE = 500
        GhostPart.MAXVALUE = 400
        isValidValue = True
        try:
            gp1 = GhostPart(TypePartGhost.FEMUR)
        except:
            isValidValue = False
        self.assertTrue(not(isValidValue))
        GhostPart.MINVALUE = 800
        GhostPart.MAXVALUE = 2200

    def testPartsDefault(self):
        gp = GhostPart(TypePartGhost.FEMUR)
        self.assertTrue(gp.value == round((GhostPart.MAXVALUE + GhostPart.MINVALUE) / 2))
        gp = GhostPart(TypePartGhost.TIBIA)
        self.assertTrue(gp.value == round((GhostPart.MAXVALUE + GhostPart.MINVALUE) / 2))
        gp = GhostPart(TypePartGhost.ROTATION)
        self.assertTrue(gp.value == round((GhostPart.MAXVALUE + GhostPart.MINVALUE) / 2))

    def testPartsValues(self):
        value = randint(GhostPart.MINVALUE, GhostPart.MAXVALUE)
        gp = GhostPart(TypePartGhost.FEMUR, value)
        self.assertTrue(gp.value == value)

        isValidValue = True
        try:
            value = GhostPart.MAXVALUE+1
            gp1 = GhostPart(TypePartGhost.FEMUR, value)

            value = GhostPart.MINVALUE-1
            gp2 = GhostPart(TypePartGhost.FEMUR, value)
        except:
            isValidValue = False

        self.assertTrue(not(isValidValue))

    def testLegsElements(self):
        leg = GhostLeg()
        for i in range(len(leg.parts)):
            self.assertTrue(leg.parts[i].type == GhostLeg.listCompose()[i].type)

    def testGhostEntity(self):
        isValidValue = True
        try:
            gh = GhostEntity()
        except:
            isValidValue = False
        self.assertTrue(isValidValue)

    def testGhostValues(self):
        GhostPart.MINVALUE = 800
        GhostPart.MAXVALUE = 2200
        gh = GhostEntity()
        gh.set_leg(1, TypePartGhost.FEMUR, 1700)
        self.assertTrue(gh.legs[1].parts[0].value == 1700)

        is_valid = True
        try:
            gh.set_leg(1, TypePartGhost.FEMUR, 1)
        except:
            is_valid = False
        is_valid2 = True
        try:
            gh.set_leg(1, 'sss', 1500)
        except:
            is_valid2 = False
        self.assertTrue(not(is_valid))
        self.assertTrue(not (is_valid2))


    def testAssignStringGood(self):
        gh = GhostEntity()
        GhostPart.MINVALUE = 800
        GhostPart.MAXVALUE = 2200
        line = '1350,1382,800,1638,1795,800,1596,1877,800,1290,1265,800'
        isValidParsing = True
        try:
            gh.parsingLine(line)
        except:
            isValidParsing = False
        self.assertTrue(isValidParsing)

    def testAssignStringBadInteger(self):
        gh = GhostEntity()
        GhostPart.MINVALUE = 800
        GhostPart.MAXVALUE = 2200
        line = '1350,1382, 800,1638,1795,800, 1596,1877,800,1290,1265'
        isValidParsing = True
        try:
            gh.parsingLine(line)
        except:
            isValidParsing = False
        self.assertTrue(not(isValidParsing))

    def testAssignStringBadString(self):
        gh = GhostEntity()
        GhostPart.MINVALUE = 800
        GhostPart.MAXVALUE = 2200
        line = '1350,1382, 800,1638,1795,800, 1a596,1877,800,1290,1265, 800 '
        isValidParsing = True
        try:
            gh.parsingLine(line)
        except:
            isValidParsing = False
        self.assertTrue(not(isValidParsing))


if __name__ == '__main__':
    unittest2.main()