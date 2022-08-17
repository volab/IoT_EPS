



class Plug():

    def __init__(self, color):
        self.stateInMemory = '?'
        self.statePhysical = '?'
        self.color = color
        self.onOffCount = -1
        self.nextSwitch = '?'
        self.stateCheckAllowed = 0
        # check is allowed only after received 2 states phy and memory state
        # so when stateCheckAllowed is equal to 2


