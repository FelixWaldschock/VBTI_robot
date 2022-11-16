import os
import pyrealsense2 as rs
import numpy as np

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


def CaptureBurst(num, mode):  # mode = 0 for depth, mode = 1 for Both
    starttime = os.cpu_count()
    pipe.start(cfg)
    depth_frame = []
    color_frame = []
    if (mode == 0):
        for _ in range(num):
            frameset = pipe.wait_for_frames()
            depth_frame.append(frameset.get_depth_frame())
        color_frame = frameset.get_color_frame()
        print("Capture in Mode 0 complete")
    elif (mode == 1):
        for _ in range(num):
            frameset = pipe.wait_for_frames()
            depth_frame = frameset.get_depth_frame()
            color_frame = frameset.get_color_frame()

    else:
        (print("Error: Burst mode not defined"))

    stopCamera()
    stoptime = os.cpu_count()
    captureDuration = stoptime - starttime
    print("Capture Duration: ", captureDuration)
    #return np.asanyarray(depth_frame.get_data()), np.asanyarray(color_frame.get_data()), captureDuration
    return depth_frame, color_frame, captureDuration

def Capture():
    pipe.start(cfg)
    frameset = pipe.wait_for_frames()
    depth_frame = frameset.get_depth_frame()
    color_frame = frameset.get_color_frame()
    stopCamera()
    return np.asanyarray(depth_frame.get_data()), np.asanyarray(color_frame.get_data())
