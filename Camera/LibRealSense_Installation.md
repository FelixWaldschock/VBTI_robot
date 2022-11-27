sudo nano /etc/dphys-swapfile -> swap 100 to 2048

sudo /etc/init.d/dphys-swapfile restart swapon -s

sudo apt update​ && sudo apt upgrade
sudo apt install -y cmake libssl-dev libusb-1.0-0-dev xorg-dev libudev-dev python3-dev libglu1-mesa-dev libvulkan-dev​
git clone -b v2.51.1 https://github.com/IntelRealSense/librealsense.git
cd librealsense​
mkdir build​
cd build​
sudo OpenGL_GL_PREFERENCE=GLVND cmake ../ -DBUILD_PYTHON_BINDINGS:bool=true -DFORCE_RSUSB_BACKEND=true -DPYTHON_EXECUTABLE="$(which python3)"​
make -j4​ // j4 only on Pi4
make install​
