from flask import Flask, request
import serial
import time
import CameraModule as CM

# connect controllino to raspberry pi twice to reset the controllino
ser_lift_carriage  = serial.Serial('/dev/ttyACM1', 115200)
ser_lift_carriage.reset_input_buffer()
time.sleep(1)
ser_camera_mount = serial.Serial('/dev/ttyACM0', 115200)
ser_camera_mount.reset_input_buffer()
time.sleep(1)
ser_lift_carriage  = serial.Serial('/dev/ttyACM1', 115200)
ser_lift_carriage.reset_input_buffer()
time.sleep(1)
ser_camera_mount = serial.Serial('/dev/ttyACM0', 115200)
ser_camera_mount.reset_input_buffer()
time.sleep(1)


# Flask app code
app = Flask(__name__)

@app.route('/')
def index():
    return '''
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
                        <label>Select an mode:
                            <select name="options">
                            <option value="1">1. one row</option>
                            <option value="2">2. two rows</option>
                            <option value="3">3. Go to a desired position</option>
                            <option value="4">4. Demo mode</option>
                        </select>
                        <label>Length of row [cm]: <input type="number" name="x" /></label>
                        <label>Step horizontal direction [cm]: <input type="number" name="x_step" /></label>
                        <label>Heigth of row [cm]: <input type="number" name="z" /></label>
                        <label>Step vertical direction [cm]: <input type="number" name="z_step" /></label>
                        <label>Starting angle [degree]: <input type="number" name="phi" /></label>
                        <input type="submit" value="Submit" />
                    </div>
                </form>
            </body>
        </html>
    '''

@app.route('/', methods=['POST'])
def save_xz():
    # Extract x and z values from form data
    x = request.form['x']
    x_step = request.form['x_step']
    z = request.form['z']
    z_step = request.form['z_step']
    phi = request.form['phi']
    options = request.form['options']
        
    options = int(options)
    x = int(x)
    x_step = int(x_step)
    z = int(z)
    z_step = int(z_step)
    phi = int(phi)

    send_values_cameramount(phi)
    send_values_lift(x,x_step,z, z_step,options,phi)
    return index()

def print_values(X,Z,phi):
    position_lift_carriage = "Sent by Rpi (x,z):" + str(X) + ","  + str(Z)
    position_lift_carriage2 = str(X) + "," + str(Z)
    print(position_lift_carriage)
    ser_lift_carriage.write(position_lift_carriage2.encode("utf-8"))
    handshake = ser_lift_carriage.read()
    print(handshake)
    time.sleep(1)
    CM.main(X,Z,phi)


# Serial communication code
def send_values_cameramount(phi):
    wakeUpcamera_mount = "0"
    ser_camera_mount.write(wakeUpcamera_mount.encode("utf-8"))
    time.sleep(1)
    position_camera_mount = str(phi)
    position_camera_mount2 = "Sent by Rpi(phi): " + str(phi)
    print(position_camera_mount2)
    ser_camera_mount.write(position_camera_mount.encode("utf-8"))
    handshake = ser_camera_mount.read()
    print(handshake)
    
def send_values_lift(X_end,X_step, Z_end,Z_step,options,phi):
    X = int(0)
    Z = int(0)
    if Z_end > 290:
        Z_end = 290
        
    if options == 1:
        for X in range(0,X_end+1,X_step):
            for Z in range(0, Z_end+1, Z_step):
                print_values(X,Z,phi)
            Z = 0
            print_values(X,Z,phi)
            time.sleep(1)
            CM.main(X,Z,phi)

    if options == 2:
        for X in range(0,X_end+1,X_step):
            for Z in range(0, Z_end+1, Z_step):
                print_values(X,Z,phi)
            Z = 0
            if X < X_end:
                print_values(X,Z,phi)    
        send_values_cameramount(-180)
        phi += 180

        for X in range(X_end,-1,-X_step):
            for Z in range(0, Z_end+1, Z_step):
                print_values(X,Z,phi)
            Z = 0
            print_values(X,Z,phi)
        send_values_cameramount(180)
        phi -= 180

    elif options == 3:
        print_values(X_step,Z_step,phi)

    elif options == 4:
        while True:
            for X in range(0,X_end+1,X_step):
                for Z in range(0, Z_end+1, Z_step):
                    print_values(X,Z,phi)
                Z = 0
                if X < X_end:
                    print_values(X,Z,phi)        
            send_values_cameramount(-180)
            phi += 180

            for X in range(X_end,-1,-X_step):
                for Z in range(0, Z_end+1, Z_step):
                    print_values(X,Z,phi)               
                Z = 0
                if 0 < X:
                    print_values(X,Z,phi)
            send_values_cameramount(180)
            phi -= 180


if __name__ == '__main__':
    app.run(debug=True, host='192.168.137.150')



