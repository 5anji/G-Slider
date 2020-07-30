#!/bin/bash

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
	sudo apt update -y
	sudo apt upgrade -y
	sudo apt install qt5-default build-essential -y
	cd source/
	qmake
	make
	make clean && rm Makefile
	mv G-Slider ../
elif [[ "$OSTYPE" == "darwin"* ]]; then
	brew install qt5
	brew install postgresql
	cd source/
	qmake
	make
	make clean && rm Makefile
	mv G-Slider.app ../
fi