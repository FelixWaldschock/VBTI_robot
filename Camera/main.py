# © Felix Waldschock - Q4 2022

import numpy as np
import matplotlib.pyplot as plt
import pyrealsense2 as rs

with rs.Service():
    dev = rs.Device()

    dev.wait_for_frame()
    plt.imshow(dev.colour)
    plt.show()