# Import standard libaries
import sys
import os
import time
import numpy as np
import cv2
import pandas as pd
import pyrealsense2 as rs
import serial

# Import custom libraries
from SubProcesses import webinterface as web
from SubProcesses import cameraModule as cM

# init camera
cM.initCamera()

# start process
if __name__ == '__main__':

    # start webinterface
    web.start_webinterface()

    # wait for webinterface inputs
    print("Waiting for webinterface inputs...")
    while True:
        if web.x != 0 and web.z != 0:
            break
        time.sleep(0.1)

    # start moving path
    print("Starting moving path...")

    ### Needs to be implemented
    # send values to arduino
    # wait for handshake with arduino
    # wait for robot to finish moving (maybe with gyro integration)


    # take pictures
    print("Taking pictures...")
    RGB, DEPTH, DUR = cM.capture()
    X,Y,Z = 1
#    X,Y,Z = # get positions from arduino // encoders

    # save pictures
    cm.saveCapture(RGB, DEPTH, DUR, X, Y, Z, "test")

