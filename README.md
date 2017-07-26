# ESS (Experior Sample Source)

##
## Program Overview
This program is designed to simulate ARINC429 data reception and processing. Written for demonstrating test tool suite (geared towards DO-178 certification) we developed at Digital Flight.

##
## Simulating Data Reception
Data reception from the bus (typically buffered via FPGA in the real world) is simulated by populating a defined memory area (see root/def/constants.h) with data words at the beginning of each frame frame's processing. The expected input data is silly to keep things simple. (The program expects two words for the legs of a right triangle and length, and three words for the width and height dimensions of a hyperrectangle. Since the hyperrectangle is expected to be a cube, the program will record an error if the 3 dimensions of the hyperrectangle are not equal.)

Similar to ARINC429 conventions, the 8 least significant bits of the U32 received words are reserved to label the data contained in the word (the least significant byte designates the shape type and the next byte identifies the shape dimension type). The most significant bit is reserved for parity. The Endians here are little, yet fierce.

##
## Periodic Output
At the end of each frame, after data is retrieved and processed, the program writes relevant data to the console (and txt files as well when the __CSS_RUN__ flag is declared).

##
## Error Processing
There are several error types potentially thrown. All error codes are defined in the root/def/constants.h file. In the case of an error, the program logs the instance in a defined memory area, sets affected data using defaults or previous frame values, then notes the occurence in the results output.

##
## Neat Utilities
One of the design goals in this project is to exclude external C libraries (good practice when all requirements and source code need meticulous, proveable coverage). This is nice because it's a good excuse to reinvent the wheel. One of my favorite challenges in this arena was defining functions to convert f32 and f64 values to strings. You can find those two functions and other fun code in root/src/utilities.c.

##
## TO(RE)DO
The program was originally configured to compile and run in <a href="http://processors.wiki.ti.com/index.php/Download_CCS">Code Composer Studio 2.3</a> IDE, which is [sadly] no longer available and backwards compatibility has been lost. I will probably update this repo with makefile in the near future.
