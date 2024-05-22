import time
import numpy as np
import json


# Encode Using Python Lists
def encode(array):
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

    # output = np.array(output, dtype=object)

    # Return the output list
    return output


def decode(input):
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

    return output


def decode_rgb(input, height, width):
    output = decode(input)
    # Reshape the array to the original shape
    output = output.reshape(height, width, 3)

    return output


def decode_depth(input, height, width):
    output = decode(input)
    # Reshape the array to the original shape
    output = output.reshape(height, width)

    return output


# arr = np.array([[[1, 2, 3], [4, 5, 6], [4, 5, 6]],
#                [[4, 5, 6], [4, 5, 6], [7, 8, 9]]])
inputFile = open("SubProcesses/Files/2022-11-11_12-07-30.json", "r").read()

# parse json to dict
inputDict = json.loads(inputFile)
arr = np.array(inputDict["RGBarray"])


# Start timer
start_time = time.time()
encoded = encode(arr)
duration = time.time() - start_time
print("Encode time: ", duration)

start_time = time.time()
decoded = decode_rgb(encoded, arr.shape[0], arr.shape[1])  # 720, 1280
duration = time.time() - start_time
print("Decode time: ", duration)

print("Is decoded == arr?", np.equal(decoded, arr).all())
print(f'Original array size: {arr.shape}')
print(f'Encoded array size: {len(encoded)}')
rate = len(encoded) / (arr.shape[0] * arr.shape[1])

print(rate*100)


# Output:
print(encoded)
# print(encoded)
