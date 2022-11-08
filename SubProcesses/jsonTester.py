import jsonCreater as jc
import random
import datetime

# create Pos
Xpos = random.randint(0, 100)
Ypos = random.randint(0, 100)
Zpos = random.randint(0, 100)
RGBarray = [random.randint(0, 255), random.randint(
    0, 255), random.randint(0, 255)]
Deptharray = [random.randint(0, 255), random.randint(
    0, 255), random.randint(0, 255)]
TimeStamp = datetime.datetime.now().strftime("%Y-%m-%d %H-%M-%S")

dict = {"Xpos": Xpos,
        "YPos": Ypos,
        "ZPos": Zpos,
        "RGBarray": RGBarray,
        "Deptharray": Deptharray,
        "TimeStamp": TimeStamp
        }
print(jc.createJson(dict))
jc.saveJson(dict)
