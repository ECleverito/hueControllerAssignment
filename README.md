# hueControllerAssignment
Command line monitor of 'brightness' and 'on' states of lights on a Phillips hue bridge.

This program is currently supported on linux-based systems, with a minimum required CMake version 3.16.3.

The Poco C++ libraries are used for HTTP requests and JSON parsing. They can be installed on a linux-based system using the following instructions:

  $git clone -b master https://github.com/pocoproject/poco.git
  
  From within the Poco source tree:
  
  $./configure
  $sudo make -s -j4 install
  
  Ensure that the Poco headers and libraries have been installed to the following locations, respectively:
  
  -/usr/local/include/Poco/
  -/usr/local/lib/

CMakeLists.txt file references shared object (.so) libs, so please install as such.
  
After installation, clone this repository.

Within the source tree, perform the following commands:

  $mkdir cmake-build
  $cd cmake-build
  $cmake ..
  $make
  
The binary "runHueController" will now be available in the /bin folder of cmake-build.
