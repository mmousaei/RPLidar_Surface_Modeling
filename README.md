# RPLidar Surface Modeling

Carnegie Mellon University - RadPiper Post Processing Software
RPLidar Surface Modeling

## Getting Started

Please make sure that you have successfully installed the following dependencies before trying to run this package.
### Dependencies:
---------------------

* [Boost](https://www.boost.org/) - Boost C++ Libraries (V >= 1.43)
* [CMake](https://cmake.org/) - CMake open-source, cross-platform (V >= 2.6)
* [OpenCV](https://opencv.org/) - Open Source Computer Vision Library (V >= 3.2)
* [GnuPlot](http://www.gnuplot.info/) - gnuplot portable command-line driven graphing utility (V >= 5.3)

#### Installing dependencies:

To install Boost, run the following command:

```
sudo apt-get update
sudo apt-get install libboost-all-dev
```

To install Cmake, run the following command:

```
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install cmake
```

To install gnuplot, run the following command:

```
sudo apt-get update
sudo apt-get install gnuplot-x11
```

To install OpenCV, run the following command:

```
cd dependencies
sudo bash install_opencv.sh
```


### Building this package
---------------------
Run the following to build the library:

```
    mkdir build
    cd build
    cmake ..
    make
```

To run the main code:

```
    ./main
```

## Author

* **Mohammadreza Mousaei** - [mmousaei](https://github.com/mmousaei)

## License

This project is licensed under the Carnegie Mellon University License

## Acknowledgments

* Lawrence Papincak (csvreader class)
