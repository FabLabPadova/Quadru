from GhostLeg import GhostLeg

class GhostEntity:

    numberLegs = 4

    def __init__(self):
        self.legs = []
        for i in range(self.numberLegs):
            self.legs.append(GhostLeg())

    def parsingLine(self, line, separator=','):
        if separator == '':
            raise ValueError('Separator is invalid.')
        list_values = line.split(separator)
        if len(list_values) == 0:
            raise IndexError('list_values is empty.')
        i = 0
        for nl in range(len(self.legs)):
            if i >= len(list_values):
                raise IndexError('list_values is too short for parsing.')
            for np in range(len(self.legs[nl].parts)):
                # check if value is a number
                list_values[i] = list_values[i].strip()
                self.legs[nl].parts[np].set_value(int(list_values[i]))
                i = i + 1

    def toDict(self):
        root = {}
        root['nl'] = len(self.legs)
        root['legs'] = []
        for nl in range(len(self.legs)):
            root['legs'].append({'np' : 0, 'index' : nl, 'parts' : []})
            root['legs'][nl]['np'] = len(self.legs[nl].parts)
            for np in range(len(self.legs[nl].parts)):
                root['legs'][nl]['parts'].append({'type' : int(self.legs[nl].parts[np].type.value), 'value' : self.legs[nl].parts[np].value})
        return root

    def set_leg(self, n_leg, type, value):
        root = {}
        if (n_leg not in range(len(self.legs))):
            raise IndexError('n_leg is not in range.')
        root['index'] = n_leg
        root['np'] = 1
        root['parts'] = []
        was_found = False
        for j in range(len(self.legs[n_leg].parts)):
            if self.legs[n_leg].parts[j].type == type:
                self.legs[n_leg].parts[j].set_value(value)
                root['parts'].append({'value' : self.legs[n_leg].parts[j].value, 'type' : int(self.legs[n_leg].parts[j].type.value), 'index' : j})
                was_found = True
                break
        if not was_found:
            raise ValueError('In leg number '+str(n_leg)+' was not found type '+str(type)+'.')
        return root




