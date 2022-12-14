import os
import pyrealsense2 as rs
import numpy as np
import time

pipe = None
cfg = None

def initCamera():
    global pipe, cfg
    # Create Pipeline
    pipe = rs.pipeline()
    cfg = rs.config()
    print("Pipeline is created")

    # Find Realsense Device
    print("Searching for Realsense Device")
    selected_device = []

    for d in rs.context().devices:
        selected_device.append(d)
        print("Device found: ", d.get_info(rs.camera_info.name))
    if not selected_device:
        print("No Realsense Device found")
        exit(0)

    # Find RGB and Depth Sensor
    rgb_sensor = depth_sensor = None

    for device in selected_device:
        print("Required sensor for device: ",
              device.get_info(rs.camera_info.name))
        for s in device.sensors:
            if s.get_info(rs.camera_info.name) == 'RGB Camera':
                print(" - RGB sensor found")
                rgb_sensor = s
            if s.get_info(rs.camera_info.name) == 'Stereo Module':
                print(" - Depth sensor found")
                depth_sensor = s

    return True

def stopCamera():
    pipe.stop()
    return True

def Capture():
    starttime = time.time()
    pipe.start(cfg)
    frameset = pipe.wait_for_frames()
    depth_frame = frameset.get_depth_frame()
    color_frame = frameset.get_color_frame()
    stopCamera()
    stoptime = time.time()
    captureDuration = stoptime - starttime
    return np.asanyarray(depth_frame.get_data()).tolist(), np.asanyarray(color_frame.get_data()).tolist(), captureDuration
