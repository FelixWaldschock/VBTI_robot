# © Felix Waldschock - Q4 2022

import numpy as np
import matplotlib.pyplot as plt
<<<<<<< HEAD
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
=======
import pyrealsense2 as rs

with rs.Service():
    dev = rs.Device()

    dev.wait_for_frame()
    plt.imshow(dev.colour)
    plt.show()
>>>>>>> a6d337acfd5b9e66bbae3ba9ea25d5ee089b0a4e
