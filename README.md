# CMPT 365 Final Project "Spatio-Temporal Images"
#### By Alex Nguyen and Jacob Jensen


This is our final project on building spatio-temporal images for examining the effects of
transitions on videos, mainly cuts and wipes.

This code is written primarily for linux, and requires the OpenCV library, so in order to run it
download the current [OpenCV library](ttps://opencv.org) as well as [CMake](https://cmake.org/) and it should compile just fine.

For runtime, there are two options: command line arguments, or open up the program, and follow the instructions. The order for command line arguments are:
(Path to File) (Width) (Height) (Type of STI) (Start Frame) (Length of STI in frames) (Output file)

For the type of STI either write 0 for the Copy style STI or 1 for Histogram style

OutputFile is optional.
