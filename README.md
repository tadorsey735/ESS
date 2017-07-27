
# Experior Sample Source (ESS)

This program is designed to simulate ARINC429 data reception and processing.


## Simulating Data Reception
Data reception from the bus (typically buffered via FPGA in the real world) is simulated by populating a reserved memory area as defined in root/def/constants.h. Expected input data is packed into u32 words. The program expects two inputs for the legs of a right triangle and three inputs for the length, width and height dimensions of a hyperrectangle. The program expects the hyperrectangle to be a cube, so an error will be recorded if the 3 dimensions of the hyperrectangle are not equal.

Similar to ARINC429 conventions, the LSByte of the received words is used as a label (the last four bits designate the shape type and the other preceding bits identifying the shape dimension type). The MSBit is reserved for parity. The Endians on this island are little.


## Periodic Output
At the end of each frame, after data has been retrieved and processed, the program writes relevant data to the console. If the __CSS_RUN__ flag is declared, results will also be written out to two text files, DrawShapeFile.txt and ResultsFile.txt.


## Error Processing
There are several error types potentially thrown. All error codes are defined in the root/def/constants.h file. In the case of an error, the program logs the instance in a defined memory area, sets affected data using defaults or previous frame values, then notes the occurence in the results output.


## TO(RE)DO
The program was originally configured to compile and run in <a href="http://processors.wiki.ti.com/index.php/Download_CCS">Code Composer Studio</a> 2.3 IDE, which is [sadly] no longer available and backwards compatibility has been lost. I will probably update this repo with Makefile in the near future.
