The FTTimer library implements a common interface for stopwatch and
time-tracking functionality that supports multiple applications and platforms. 


# Overview
Provides stopwatch type controls for multiple streams

## References
* https://mesonbuild.com/ - meson build system documentation

# Supported Systems
* Ubuntu 22.04

# Organization
The top-level directory of this repository contains this README file along with 

# Building Software
A meson build is a multi-step process. 

## Configuration
Before compiling software, the directory where the bild will occur must be 
specified using the meson --reconfigure command
* meson --reconfigure <builddir>

## Compilation
By default, meson uses the ninja build system which can either be referenced
within meson or directly from the command line. To build with meson you can
simply use the following command:

* meson compile -C <builddir>

If using ninja directly, this translates to the following command:
* ninja -C <builddir> 

## Unit tests
This software package has been built from the ground up with integrated
testing based on the gtest suite. Unit tests can be run through the meson
environment using the following command:

* meson test

