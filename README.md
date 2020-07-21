# G Slider

<b>G Slider</b> - simple application, that will create a slideshow inside.

This is my first project made in Qt. I decided to use here <i>CMake</i>, instead of <i>QMake</i>.


## Features

* <i>Browse</i> button - creates path to folder where are the images. Accepts only <i>.jpg</i> and <i>.png </i>files.

* <i>Select...</i> button - set period, that will automatically change images. In alpha doesn't work last option. Also, to stop the timer click on <i>Select...</i> again.

* Window resizing adaptation

* Full-Screen mode by double-clicking

* Custom period of image changing

* <i>Image scaling</i>, also aligned to the center.

* Support for more data types (without .gif)

* <i>Shuffle</i> button

# Downloading & installing

## Ubuntu

1. Firstly install dependencies: 

```sh
sudo apt update && sudo apt install git cmake extra-cmake-modules qt5-default build-essential -y
```

2. Clone the repository:

```sh
git clone https://github.com/5anji/G-Slider
```

3. Enter the path:

```sh
cd G-Slider/
```

4. Build:

```sh
cmake CMakeLists.txt
make
```

5. Run:

```sh
./Slideshow
```