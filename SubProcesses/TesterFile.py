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
        Deptharray, RGBarray, CaptureDuration = cm.Capture()
        Xpos = Ypos = Zpos = 1
        TimeStamp = datetime.datetime.now().strftime(p.dateformatting)

        # Structure of the JSON file containing capture information
        dict = {"Xpos": Xpos,
                "YPos": Ypos,
                "ZPos": Zpos,
                "RGBarray": RGBarray,
                "Deptharray": Deptharray,
                "TimeStamp": TimeStamp,
                "CaptureDuraction": CaptureDuration
                }
        return dict


printString = ("[0] capture image\n[1] show capture\n[2] show depthmap")
print(printString)
select = int(input())
if select == 0:
        cm.initCamera()
        dict = CaptureImage()
        jh.saveDict2Json(dict)
if select == 1:
        dv.showCapture()

if select == 2:
        dv.showDepthmap()

        
        exit()


# Choose action


