sudo apt update -y
sudo apt upgrade -y
sudo apt install qt5-default build-essential -y
cd G-Slider/
qmake
make
make clean