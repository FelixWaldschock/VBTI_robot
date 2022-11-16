import numpy as np
import json


# Encode using numpy arrays
# def encode(array):

#     output = np.empty((0, 2))

#     flattened = array.reshape(-1, arr.shape[-1])
#     current_value = flattened[0]
#     current_frequency = 1

#     for pixel in flattened:
#         if np.equal(pixel, current_value).all():
#             current_frequency += 1
#         else:
#             np.append(
#                 output, [[current_frequency, current_value]], axis=0)
#             current_value = pixel
#             current_frequency = 1


# Encode Using Python Lists
def encodeRGB(array):
    # Redundancy compression
    # Encode a numpy array to a lossless compressed list of frequencies+values
    # The array is assumed to be a 2D array of pixels (height, width, 3)
    # The output is a list of (repeat, value) tuples
    # The repeat is the number of times the value is repeated
    # The value is a list of [R, G, B] values

    # Convert the array to a list of values
    values = array.reshape(-1, 3).tolist()
    output = []

    # Initialize the current value and repeat
    current_value = values[0]
    current_repeat = 1

    for value in values[1:]:
        # If the value is the same as the current value, increment the repeat
        if value == current_value:
            current_repeat += 1
        # Otherwise, add the current value and repeat to the output list
        else:
            output.append((current_repeat, current_value))
            current_value = value
            current_repeat = 1

    # Add the last value and repeat to the output list
    output.append((current_repeat, current_value))

    output = np.array(output)

    # Return the output list
    return output


def decodeRGB(input, height, width):
    # Redundancy compression
    # Decode a list of frequencies+values to a numpy array
    # The input is a list of (repeat, value) tuples
    # The value is a list of [R, G, B] values
    # The repeat is the number of times the value is repeated
    # The output is a 2D array of pixels (height, width, 3)

    # Initialize the output list
    output = []

    for repeat, value in input:
        # Add the value to the output list the number of times specified by the repeat
        output += [value] * repeat

    # Convert the output list to a numpy array
    output = np.array(output)

    # Reshape the array to the original shape
    output = output.reshape(height, width, 3)

    return output


def encodeDepth(array):
    output = []
    return output


"""
inputFile = open("SubProcesses/Files/2022-11-11_12-07-30.json", "r").read()

# parse json to dict
inputDict = json.loads(inputFile)
arr = np.array(inputDict["RGBarray"])


encoded = encodeRGB(arr)
decoded = decodeRGB(encoded, arr.shape[0], arr.shape[1])  # 720, 1280

print("Is decoded == arr?", np.equal(decoded, arr).all())
print(f'Original array size: {arr.shape}')
print(f'Encoded array size: {len(encoded)}')
"""
# print(encoded)
