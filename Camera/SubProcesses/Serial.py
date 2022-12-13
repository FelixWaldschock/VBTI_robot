import serial
import time

# Serial communication code

def initSerial():
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.reset_input_buffer()
    return ser

def serialSend(serial, contentString):
    serial.reset_input_buffer()
    serial.write(contentString.encode("utf-8"))
    time.sleep(1)
    line = serial.readline().decode('utf-8').rstrip()
    return line

def serialRead(serial):
    line = serial.readline().decode('utf-8').rstrip()
    return line


def send_values(X_end, Z_end):
    X = int(0)
    Y = int(0)  
    Z = int(0)

    X_step = 20
    Z_step = 20

    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.reset_input_buffer()
    while X <= X_end:
        for Z in range(0, Z_end+1, Z_step):
            Finalstring1 = "Sent by Rpi:        " + str(X) + "," + str(Y) + "," + str(Z) 
            Finalstring2 = str(X) + "," + str(Y) + "," + str(Z)
            print(Finalstring1)
            ser.write(Finalstring2.encode("utf-8"))
            time.sleep(1)
            line = ser.readline().decode('utf-8').rstrip()
            line2 = "Robot at location:  " + line
            print(line2)

        # Increment X by X_step
        X += X_step
        if X <= X_end:
            for Z in range(Z_end, -1, -Z_step):
                Finalstring1 = "Sent by Rpi:        " + str(X) + "," + str(Y) + "," + str(Z)             
                Finalstring2 = str(X) + "," + str(Y) + "," + str(Z)
                print(Finalstring1)
                ser.write(Finalstring2.encode("utf-8"))
                time.sleep(1)
                line = ser.readline().decode('utf-8').rstrip()
                line2 = "Robot at location:  " + line
                print(line2)

            # Increment X by 20
            X += X_step
