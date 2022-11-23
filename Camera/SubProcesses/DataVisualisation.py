import matplotlib.pyplot as plt
import numpy as np
import os
import json
import jsonHandler as jh

sep = os.sep
filepath = "Files" + sep


def loadCaptures():
    return os.listdir(filepath)


def loadFile():
    files = loadCaptures()
    for i in range(len(files)):
        print("[" + str(i) + "] " + str(files[i]))
    print("Select files -> type index:")
    index = int(input())
    print(files[index])
    with open(filepath + files[index], 'r') as f:
        jsonFile = json.load(f)
    return jsonFile


def showCapture():
    data = loadFile()
    data = jh.Json2Dict(data)
    rgb = np.array(data["RGBarray"])
    depth = np.array(data["Deptharray"])
    print("Data loaded successfully\nStart visualisation")
    plt.figure()
    plt.subplot(1, 2, 1)
    plt.title("RGB image")
    plt.imshow(rgb)
    plt.subplot(1, 2, 2)
    plt.title("Depthmap")
    plt.imshow(depth,cmap='viridis')
    plt.show()
    print(rgb.max())
    return

def showRGB(dict):

    return


def showDepthmap():
    data = loadFile()
    data = jh.Json2Dict(data)
    depth = np.array(data["Deptharray"])
    print("Data loaded successfully\nStart visualisation")
    depth1d = np.reshape(depth, (1,-1))
    plt.figure()
    plt.hist(depth1d[0], bins=100)
    plt.show()
    return
