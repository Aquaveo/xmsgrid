[![Build Status](https://travis-ci.org/Aquaveo/xmsgrid.svg?branch=master)](https://travis-ci.org/Aquaveo/xmsgrid)
[![Build status](https://ci.appveyor.com/api/projects/status/tkgmhrs31cc4l3ph?svg=true)](https://ci.appveyor.com/project/Aquaveo/xmsgrid)

XMSGrid
========
Grid library for XMS products

Prerequisites
--------------
In order to build this library, you must first have a few things installed.
1. [Conan](https://conan.io)
2. [CMake](https://cmake.org)

Building
--------
Once you have cloned the repository, navigate to the `build` directory. All
of the following commands will be run from that directory unless otherwise 
noted.

1. Get External Libraries
```
    conan install .. 
``` 

2. Configure CMake
```
    cmake ..
```

3. Build 
```
    make
```

Documentation
-------------

See: [xmsgrid documentation](https://aquaveo.github.io/xmsgrid/)
