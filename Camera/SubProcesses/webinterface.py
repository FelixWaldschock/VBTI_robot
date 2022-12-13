from flask import Flask, request
import serial
import time
import os
import socket

# get IP of raspi
#IP = os.system('hostname -I')
IP = '192.168.188.41'

# Flask app code
app = Flask(__name__)

@app.route('/')

def index():
    """return '''
        <html>
            <head>
                <style>
                    label, input {
                        display: block;
                    }

                    div {
                        margin: 0 auto;
                        width: 200px;
                    }
                </style>
            </head>
            <body>
                <form method="POST">
                    <div>
                        <label>x: <input type="number" name="x" /></label>
                        <label>z: <input type="number" name="z" /></label>
                        <input type="submit" value="submit" />
                        <input type="submit" value="CaptureImage" />
                    </div>
                </form>
            </body>
        </html>
    '''"""

@app.route('/', methods=['POST'])

def save_xz():
    # Extract x and z values from form data
    x = request.form['x']
    z = request.form['z']

    # Convert x and z values to integers
    x = int(x)
    z = int(z)

    # Call send_values() function and pass x and z values as arguments
    send_values(x, z)

    return 'x: {}, z: {}'.format(x, z)

# Serial communication code
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

def start_webinterface():
    app.run(debug=True, host=IP)