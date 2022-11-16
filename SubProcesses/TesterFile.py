import jsonHandler as jh
import random
import datetime
import numpy as np
import camerModule as cm
import parameters as p
import DataVisualisation as dv
import Compressor as comp


def CaptureImage():

        #Deptharray, RGBarray, CaptureDuration = cm.CaptureBurst(5,mode=0)
        Deptharray, RGBarray = cm.Capture()
        CaptureDuration = 0
        Xpos = Ypos = Zpos = 1
        TimeStamp = datetime.datetime.now().strftime(p.dateformatting)

        # Structure of the JSON file containing capture information
        dict = {"Xpos": Xpos,
                "YPos": Ypos,
                "ZPos": Zpos,
                "RGBarray": RGBarray.tolist(),
                "Deptharray": Deptharray.tolist(),
                "TimeStamp": TimeStamp,
                "CaptureDuraction": CaptureDuration
                }
        return dict

cm.initCamera()
dict = CaptureImage()

jh.saveDict2Json(dict)
exit()
# Choose action


