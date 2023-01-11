from flask import Flask, request
import serial
import time

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
                            <option value="1">Bottom to top, top to bottom</option>
                            <option value="2">Bottom to top</option>
                            <option value="3">Go to a desired position</option>
                        </select>
                        <label>Length of row: <input type="number" name="x" /></label>
                        <label>Step horizontal direction: <input type="number" name="x_step" /></label>
                        <label>Heigth of row: <input type="number" name="z" /></label>
                        <label>Step vertical direction: <input type="number" name="z_step" /></label>
                        <label>Angle: <input type="number" name="phi" /></label>
                        <label>length of camera mounth: <input type="number" name="r" /></label>
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
    r = request.form['r']
    options = request.form['options']

    # Convert x and z values to integers
    options = int(options)
    x = int(x)
    x_step = int(x_step)
    z = int(z)
    z_step = int(z_step)
    phi = int(phi)
    r = int(r)
    #send_values_cameramount(phi,r)
    # Call send_values() function and pass x and z values as arguments
    send_values_lift(x,x_step,z, z_step,options)

    return 'x: {}, z: {}'.format(x, z)

# Serial communication code
#def send_values_cameramount(phi,r):
#    ser_camera_mount = serial.Serial('/dev/ttyACM1', 115200)
#    ser_camera_mount.reset_input_buffer()
#    wakeUp = "0,0"
#    ser_camera_mount.write(wakeUp.encode("utf-8"))
#    time.sleep(1)
#    position_camera_mount = str(phi) + "," + str(r)
#    position_camera_mount2 = "Sent by Rpi(phi,r): " + str(phi) + "," + str(r)
#    print(position_camera_mount2)
#    ser_camera_mount.write(position_camera_mount.encode("utf-8"))
#    handshake = ser_camera_mount.read()
#    #handshake2 = "handshake from cameramount:  " + handshake
#    print(handshake)
    
def send_values_lift(X_end,X_step, Z_end,Z_step,options):
    X = int(0)
    Z = int(0)
    
    ser_lift_carriage  = serial.Serial('/dev/ttyACM0', 115200)
    ser_lift_carriage.reset_input_buffer()
    wakeUp = "0,0"
    ser_lift_carriage.write(wakeUp.encode("utf-8"))
    time.sleep(1)

    if options == 1: 
        while X <= X_end:
            for Z in range(0, Z_end+1, Z_step):
                position_lift_carriage = "Sent by Rpi (x,z):" + str(X) + "," + str(Z) 
                position_lift_carriage2 = str(X) + "," + str(Z)
                print(position_lift_carriage)
                ser_lift_carriage.write(position_lift_carriage2.encode("utf-8"))
                handshake = ser_lift_carriage.read()
                print(handshake)
                time.sleep(2)
            X += X_step
            time.sleep(2)            


            if X <= X_end:
                for Z in range(Z_end, -1, -Z_step):
                    position_lift_carriage = "Sent by Rpi (x,z):" + str(X)  + "," + str(Z)             
                    position_lift_carriage2 = str(X) +  "," + str(Z)
                    print(position_lift_carriage)
                    ser_lift_carriage.write(position_lift_carriage2.encode("utf-8"))
                    handshake = ser_lift_carriage.read()
                    print(handshake)
                    time.sleep(2)

                time.sleep(2)
                X += X_step

    elif options == 2:
        for X in range(0,X_end+1,X_step):
            for Z in range(0, Z_end+1, Z_step):
                position_lift_carriage = "Sent by Rpi (x,z):" + str(X) + ","  + str(Z) 
                position_lift_carriage2 = str(X) + "," + str(Z)
                print(position_lift_carriage)
                ser_lift_carriage.write(position_lift_carriage2.encode("utf-8"))
                handshake = ser_lift_carriage.read()
                print(handshake)
                time.sleep(2)

    elif options == 3:
                position_lift_carriage = "Sent by Rpi (x,z):" + str(X) + ","  + str(Z) 
                position_lift_carriage2 = str(X) + "," + str(Z)
                print(position_lift_carriage)
                ser_lift_carriage.write(position_lift_carriage2.encode("utf-8"))
                handshake = ser_lift_carriage.read()
                print(handshake)
                time.sleep(2)

if __name__ == '__main__':
    app.run(debug=True, host='192.168.137.18')



