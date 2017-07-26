# ESS (Experior Sample Soure)

## Overview
This program is designed to simulate ARINC429 data reception and processing. Originally written for demonstrating the test tool suite developed at Digital Flight to aid with DO-178 certification.

## Data Receiving Simulation
Data reception from the bus (typically buffered via FPGA in the real world) is simulated by populating a defined memory area (see root/def/constants.h) with data words at the beginning of each frame frame's processing. The expected input data is silly to keep things simple. (The program expects two words for the legs of a right triangle and length, and three words for the width and height dimensions of a hyperrectangle. Since the hyperrectangle is expected to be a cube, the program will record an error if the 3 dimensions of the hyperrectangle are not equal.)

Similar to ARINC429 conventions, the 8 least significant bits of the U32 received words are reserved to label the data contained in the word (the least significant byte designates the shape type and the next byte identifies the shape dimension type). The most significant bit is reserved for parity. The Endians here are little, yet fierce.

## Output
At the end of each frame, after data is retrieved and processed, the program writes relevant data to the console (and txt files as well when the __CSS_RUN__ flag is declared).

## Error processing
There are several error types potentially thrown. All error codes are defined in the root/def/constants.h file. In the case of an error, the program logs the instance in a defined memory area, sets affected data using defaults or previous frame values, then notes the occurence in the results output.

## TO(RE)DO
The program was originally configured to compile and run in <a href="http://processors.wiki.ti.com/index.php/Download_CCS">Code Composer Studio 2.3</a> IDE, which is [sadly] no longer available and backwards compatibility has been lost. I will probably update this repo with makefile in the near future.