#!/bin/bash

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
	cd source/
	qmake
	make
	make clean && rm Makefile
	mv G-Slider ../
elif [[ "$OSTYPE" == "darwin"* ]]; then
	cd source/
	qmake
	make
	make clean && rm Makefile
	mv G-Slider.app ../
fi
