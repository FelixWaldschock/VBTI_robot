# © Felix Waldschock - Q4 2022

import numpy as np
import matplotlib.pyplot as plt
import camerModule as cM
import pyrealsense2 as rs
import cv2

# Create a pipeline
pipe = rs.pipeline()
profile = pipe.start()
try:
    for i in range(0, 100):
        frames = pipe.wait_for_frames()
        for f in frames:
            print(f.profile)
finally:
    pipe.stop()
