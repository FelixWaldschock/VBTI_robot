import numpy as np


def averageFilter(arr):
    numOfArrays = len(arr)
    shape = np.shape(arr[0])
    filteredArray = np.zeros(shape)
    for i in range(shape[0]):
        for j in range(shape[1]):
            avg = 0
            for k in range(numOfArrays):
                avg += arr[k][i][j]
            avg = avg / numOfArrays
            filteredArray[i][j] = avg
    return filteredArray
