import json
import datetime
import os

sep = os.path.sep

path = "Files" + sep


def createJson(dict):
    JsonFile = json.dumps(dict, indent=4)
    return JsonFile


def saveJson(dict):
    fileName = path + datetime.datetime.now().strftime("%Y-%m-%d %H-%M-%S") + ".json"
    with open(fileName, 'w') as f:
        json.dump(dict, f, indent=4)
    f.close()
