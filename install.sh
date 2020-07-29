#!/bin/bash

sudo apt update -y
sudo apt upgrade -y
sudo apt install qt5-default build-essential -y
cd source/
qmake
make
make clean && rm Makefile
mv G-Slider ../

