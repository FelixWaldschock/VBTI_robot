class Image:
    RGB = [[], [], []]      # 3D array of RGB values
    depthMap = [[], []]     # 2D array of depth values
    name = None             # String with name
    outputPath = None

    def __init__(self, name, outputPath):
        self.name = name
        self.outputPath = outputPath

    def load(self):
        # Load RGB and depthMap from file
        return [self.RGB, self.depthMap]

    def getRGB(self):
        return self.RGB

    def getDepthMap(self):
        return self.depthMap

    def getName(self):
        return self.name

    def getOutputPath(self):
        return self.outputPath

    def setRGB(self, RGB):
        self.RGB = RGB

    def setDepthMap(self, depthMap):
        self.depthMap = depthMap

    def setName(self, name):
        self.name = name

    def setOutputPath(self, outputPath):
        self.outputPath = outputPath + os.path.sep + self.name

    def saveImage(self):
        # Save RGB and depthMap to file
        # ...
