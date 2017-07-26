/************************************************************************/
//
//  <FileName: result_strings.h>
//
//  <FileDesc: ESS Result Strings Definition File>
//
//  <Version: 1.1.4>
//
/************************************************************************/
#if defined __CCS_RUN__
#include <stdio.h>
#include <string.h>
#endif

#if !defined(RESULT_STRINGS_H_)
#define RESULT_STRINGS_H_


#if defined(RESULTS_FILE_C_)
/*-------------------------------------------------*/
/* Results File Header Text                        */
/*-------------------------------------------------*/
#define RSLTS_FILE_HDR_STRING_COUNT    ( 8)
static CHAR ResultsFileHeader[8][73] = {  "************************************************************************",
                                          "************************************************************************",
                                          "**                                                                    **",
                                          "**                       DFS Sample Program                           **",
                                          "**                          Results File                              **",
                                          "**                                                                    **",
                                          "************************************************************************",
                                          "************************************************************************" };

static CHAR DrawFileHeader[8][73]    = {  "************************************************************************",
                                          "************************************************************************",
                                          "**                                                                    **",
                                          "**                       DFS Sample Program                           **",
                                          "**                        Shape Draw File                             **",
                                          "**                                                                    **",
                                          "************************************************************************",
                                          "************************************************************************" };

/*-------------------------------------------------*/
/* Program Information Strings                     */
/*-------------------------------------------------*/
#define NO_OF_FRAME_STRING_LNG      (35)
#define NO_OF_FRAME_INSERT_INDEX    (26)
const CHAR NumberOfFrames[35] = "Program is set to run for ## Frames";

const CHAR AutoPopulateMsg[27] = "Input shape data is preset";

#define CUBE_LNG_RANGE_STRING_LNG   (28)
const CHAR LengthMaxValMsg[28] = "Cube Length Maximum Value: ";
const CHAR LengthMinValMsg[28] = "Cube Length Minimum Value: ";

#define CUBE_HGT_RANGE_STRING_LNG   (28)
const CHAR HeightMaxValMsg[28] = "Cube Height Maximum Value: ";
const CHAR HeightMinValMsg[28] = "Cube Height Minimum Value: ";

#define CUBE_WDT_RANGE_STRING_LNG   (27)
const CHAR WidthMaxValMsg[27]  = "Cube Width Maximum Value: ";
const CHAR WidthMinValMsg[27]  = "Cube Width Minimum Value: ";

#define TRI_RANGE_STRING_LNG        (31)
const CHAR Leg1MaxValMsg[31]   = "Triangle Leg 1 Maximum Value: ";
const CHAR Leg1MinValMsg[31]   = "Triangle Leg 1 Minimum Value: ";
const CHAR Leg2MaxValMsg[31]   = "Triangle Leg 2 Maximum Value: ";
const CHAR Leg2MinValMsg[31]   = "Triangle Leg 2 Minimum Value: ";


/*-------------------------------------------------*/
/* Current Frame Header Information                */
/*-------------------------------------------------*/
const CHAR CurrentFrameDivider[73]     = "========================================================================";
const CHAR FrameResultsArray[35]       = "                             Frame ";
const CHAR RtrvResultsHeaderArray1[34] = "     Retrieve Data Results       ";
const CHAR RtrvResultsHeaderArray2[34] = "---------------------------------";
const CHAR TriResultsHeaderArray1[34]  = "          Triangle Data          ";
const CHAR TriResultsHeaderArray2[34]  = "---------------------------------";
const CHAR CubeResultsHeaderArray1[34] = "            Cube Data            ";
const CHAR CubeResultsHeaderArray2[34] = "---------------------------------";


/*-------------------------------------------------*/
/* Current Frame Retrieve Error Strings            */
/*-------------------------------------------------*/
const CHAR NoRetrieveErrorDetected[42]       = "All Retrieved Shape Data Words Recognized";
const CHAR OneRetrieveErrorDetected[25]      = "One Retrieve Word Error:";
const CHAR MulipleRetrieveErrorsDetected[31] = "Multiple Retrieve Word Errors:";
const CHAR AllExpectedWordsRetrieved[53]     = "All Shape Data Values Successfully Extracted and Set";
const CHAR NotAllExpectedWordsRetrieved[54]  = "Errors Occurred during Shape Data Extraction/Setting:";

#define PARITY_ERROR_LENGTH          (54)
#define SHAPE_LABEL_ERROR_LENGTH     (56)
#define TRI_TYPE_ERROR_LENGTH        (61)
#define CUBE_TYPE_ERROR_LENGTH       (57)
#define ERROR_VALUE_INDEX_PLACE      (21)
const CHAR ShapeWordParityError[PARITY_ERROR_LENGTH]     = "  - Retrieved Word 0x******** Contained a Parity Error";
const CHAR ShapeWordLabelError[SHAPE_LABEL_ERROR_LENGTH] = "  - Retrieved Word 0x******** Shape Label Not Recognized";
const CHAR TriDataSubtypeError[TRI_TYPE_ERROR_LENGTH]    = "  - Retrieved Word 0x******** Triangle Subtype Not Recognized";
const CHAR CubeDataSubtypeError[CUBE_TYPE_ERROR_LENGTH]  = "  - Retrieved Word 0x******** Cube Subtype Not Recognized";

#define TRILEG1_WORD_STRING_LENGTH   (37)
#define TRILEG2_WORD_STRING_LENGTH   (37)
#define CUBELNG_WORD_STRING_LENGTH   (34)
#define CUBEHGT_WORD_STRING_LENGTH   (34)
#define CUBEWDT_WORD_STRING_LENGTH   (34)
const U16  ExpexcetedDataWordLength[RTRV_DATA_SIZE] = { TRILEG1_WORD_STRING_LENGTH, TRILEG2_WORD_STRING_LENGTH, CUBELNG_WORD_STRING_LENGTH, CUBEHGT_WORD_STRING_LENGTH, CUBEWDT_WORD_STRING_LENGTH };
const CHAR ExpectedDataWords[RTRV_DATA_SIZE][38]    = { "  - Triangle Leg 1 Expected Word Data",
                                                        "  - Triangle Leg 2 Expected Word Data",
                                                        "  - Cube Length Expected Word Data",
                                                        "  - Cube Height Expected Word Data",
                                                        "  - Cube Width Expected Word Data "    };

#define TRILEG1_RTRV_ZERO_VALUE   (54)
#define TRILEG2_RTRV_ZERO_VALUE   (54)
#define CUBELNG_RTRV_ZERO_VALUE   (50)
#define CUBEHGT_RTRV_ZERO_VALUE   (50)
#define CUBEWDT_RTRV_ZERO_VALUE   (49)
const U16  RtrvDataZeroMsgLength[RTRV_DATA_SIZE] = { TRILEG1_RTRV_ZERO_VALUE, TRILEG2_RTRV_ZERO_VALUE, CUBELNG_RTRV_ZERO_VALUE, CUBEHGT_RTRV_ZERO_VALUE, CUBEWDT_RTRV_ZERO_VALUE };
const CHAR RtrvDataZeroMsg[RTRV_DATA_SIZE][55]   = { "  - No Data for Triangle Leg 1 (Retrieved Value Zero)",
                                                     "  - No Data for Triangle Leg 2 (Retrieved Value Zero)",
                                                     "  - No Data for Cube Length (Retrieved Value Zero)",
                                                     "  - No Data for Cube Height (Retrieved Value Zero)",
                                                     "  - No Data for Cube Width (Retrieved Value Zero)"     };

#define NO_DATA_RETRIEVED_STRING_LENGTH    (31)
const CHAR NoValueRtrvd[NO_DATA_RETRIEVED_STRING_LENGTH]           = " Not Retrieved in Current Frame";
const CHAR ParityErrorCause[23]                                    = " due to a Parity Error";

#define EXTRA_DATA_RETRIEVED_STRING_LENGTH (42)
const CHAR MultipleValuesRtrvd[EXTRA_DATA_RETRIEVED_STRING_LENGTH] = " Retrieved Multiple Times in Current Frame";


/*-------------------------------------------------*/
/* Current Frame Triangle Results Strings          */
/*-------------------------------------------------*/
#define TRI_LEG1_PREAMBLE_CHAR_NO          (39)
const CHAR RetrievedTriLeg1Preamble[TRI_LEG1_PREAMBLE_CHAR_NO ] = "Retrieved Right Triangle Leg 1 Value: ";

#define TRI_LEG2_PREAMBLE_CHAR_NO          (39)
const CHAR RetrievedTriLeg2Preamble[TRI_LEG2_PREAMBLE_CHAR_NO]  = "Retrieved Right Triangle Leg 2 Value: ";

#define TRI_AREA_PREAMBLE_CHAR_NO          (26)
const CHAR CalculatedTriAreaPreamble[TRI_AREA_PREAMBLE_CHAR_NO] = "Calculated Triangle Area: ";

#define TRI_HYPO_PREAMBLE_CHAR_NO          (32)
const CHAR CalculatedTriHypoPreamble[TRI_HYPO_PREAMBLE_CHAR_NO] = "Calculated Triangle Hypotenuse: ";


/*-------------------------------------------------*/
/* Current Frame Cube Results Strings              */
/*-------------------------------------------------*/
#define CUBE_LENGTH_PREAMBLE_CHAR_NO          (24)
const CHAR RetrievedCubeLengthPreamble[CUBE_LENGTH_PREAMBLE_CHAR_NO]   = "Retrieved Cube Length: ";

#define CUBE_HEIGHT_PREAMBLE_CHAR_NO          (24)
const CHAR RetrievedCubeHeightPreamble[CUBE_HEIGHT_PREAMBLE_CHAR_NO]   = "Retrieved Cube Height: ";

#define CUBE_WIDTH_PREAMBLE_CHAR_NO           (24)
const CHAR RetrievedCubeWidthPreamble[CUBE_WIDTH_PREAMBLE_CHAR_NO]     = "Retrieved Cube Width:  ";

#define CUBE_VOLUME_PREAMBLE_CHAR_NO          (24)
const CHAR CalculatedCubeVolumePreamble[CUBE_VOLUME_PREAMBLE_CHAR_NO]  = "Calculated Cube Volume: ";

const CHAR FirstRtrvValueUsed[34]      = " (Set with First Retrieved Value)";
const CHAR DataValueDefaulted[26]      = " (Set with Default Value)";
const CHAR PreviousFrameDataUsed[33]   = " (Set with Previous Frame Value)";
const CHAR RetrievedValueLimited[17]   = " (Value Limited)";

/*-------------------------------------------------*/
/* Current Frame Calculation Error Strings         */
/*-------------------------------------------------*/
const CHAR NoCalculationErrorsDetected[32] = "No Calculation Errors This Frame";
const CHAR OneCalErrorDetected[33]         = "One Calculation Error This Frame:";
const CHAR MulipleCalcErrorsDetected[39]   = "Multiple Calculation Errors This Frame:";

const CHAR NoDataMessage[30]               = " Value Was Not Set This Frame";
const CHAR DataLimitedMessage[71]          = " Retrieved Data Exceeded Maximum Value - Value Limited for Calculation";
const CHAR ValueNotCalculatedMessage[37]   = " Therefore Not Calculated This Frame";

#endif

#if defined(DRAW_FILE_C_)

/*-----------------------------------------*/
//  Draw File Strings                      //
/*-----------------------------------------*/
const CHAR CurrentFrameDrawDivider[73] = "========================================================================";
const CHAR CurrentFrameArray[35]       = "                             Frame ";
const CHAR TriDrawDataHeader[22]       = " Drawn Triangle Data:";
const CHAR DrawShapeHeaderArray[34]    = "---------------------------------";
const CHAR CubeDrawDataHeader[18]      = " Drawn Cube Data:";


#endif

#endif


/************************************************************************/



