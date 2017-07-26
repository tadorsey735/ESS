/************************************************************************/
//
//  <FileName: results_file.c>
//
//  <FileDesc: ESS Results File>
//
//  <Version: 1.1.3>
//
/************************************************************************/
#if defined __CCS_RUN__
#include <stdio.h>
#include <string.h>
#endif

#define RESULTS_FILE_C_

#include "type.h"
#include "functions.h"
#include "constants.h"
#include "global_data.h"
#include "result_strings.h"



/************************************************************/
//
//  <FunctionName: ResultsDataMain>
//
//  <Full Name: Results Generation Main Function>
//
//  <Description: This is the main function for initializing
//   results reports for each frame during periodic processing.
//   On the first frame, function calls are made to report out
//   program header and setting information.>
//
/************************************************************/
void ResultsDataMain(void)
/************************************************************/
{
    // Write Results File Header Information if first frame
    if ( u16FrameNumber == FIRST_FRAME ) {
        WriteResultsFileHeader();
        WriteProgramDetails();
    }

    // Write Current Frame Results Header Information
    WriteCurrentFrameHeader();

    // Write Retrieved Data Results
    WriteRetrievedDataSummary();

    // Write Cube Results
    WriteCubeResults();

    // Write Triangle Results
    WriteTriangleResults();

    // Draw Cube Results
    DrawCube();

    // Draw Triangle Results
    DrawTriangle();

}
/************************************************************/



/************************************************************/
//
//  <FunctionName: WriteResultsFileHeader>
//
//  <Full Name: Current Frame Results Header>
//
//  <Description: This function generates the program header
//   information to be printed at the top of the results file.>
//
/************************************************************/
void WriteResultsFileHeader(void)
/************************************************************/
{
    U16 i;

    for (i = 0; i < RSLTS_FILE_HDR_STRING_COUNT; i++) {
        if ( i == NO_CARRIAGE_RETURN ) {
            PrintToResultsFile( NO_CARRIAGE_RETURN, (CHAR * ) ResultsFileHeader[i] );
            PrintToDrawFile( NO_CARRIAGE_RETURN, (CHAR * ) DrawFileHeader[i] );
        }
        else {
            PrintToResultsFile( ONE_CARRIAGE_RETURN, (CHAR * ) ResultsFileHeader[i] );
            PrintToDrawFile( ONE_CARRIAGE_RETURN, (CHAR * ) DrawFileHeader[i] );
        }
    }
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: WriteProgramDetails>
//
//  <Full Name: Write Program Details Function>
//
//  <Description: This function prepares strings to be written
//   to the results file before frame by frame results reports.
//   Program settings such as amount of frames program is set
//   to run for, whether auto-population of retrieve data is
//   is enabled, and minimum and maximum values for expected
//   shape data is addressed.>
//
/************************************************************/
void WriteProgramDetails(void)
/************************************************************/
{
    U16  i;
    U32  TotalFrameCountBuffer;
    CHAR pu8CharBuffer1[100];
    CHAR pu8CharBuffer2[100];

    // Print FINAL_FRAME setting
    TotalFrameCountBuffer = FINAL_FRAME;
    for (i = 0; i < NO_OF_FRAME_STRING_LNG; i++) {
        pu8CharBuffer1[i] = NumberOfFrames[i];
    }
    if ( TotalFrameCountBuffer < 10 ) {
        pu8CharBuffer1[NO_OF_FRAME_INSERT_INDEX]   = ASCII_SPACE;
        pu8CharBuffer1[NO_OF_FRAME_INSERT_INDEX+1] = TotalFrameCountBuffer + ASCII_ZERO;
    }
    else {
        pu8CharBuffer1[NO_OF_FRAME_INSERT_INDEX]   = (TotalFrameCountBuffer / 10) + ASCII_ZERO;
        pu8CharBuffer1[NO_OF_FRAME_INSERT_INDEX+1] = (TotalFrameCountBuffer % 10) + ASCII_ZERO;
    }
    pu8CharBuffer1[NO_OF_FRAME_STRING_LNG] = STRING_NULL;
    PrintToResultsFile( TWO_CARRIAGE_RETURN, pu8CharBuffer1 );

    #ifdef __AUTO_INPUT__
        PrintToResultsFile( TWO_CARRIAGE_RETURN, (CHAR * ) AutoPopulateMsg );
    #endif

    // Minimum and Maximum Cube Length
    for (i = 0; i < CUBE_LNG_RANGE_STRING_LNG; i++) {
        pu8CharBuffer1[i] = LengthMinValMsg[i];
    }
    pu8CharBuffer1[CUBE_LNG_RANGE_STRING_LNG] = STRING_NULL;
    PrintToResultsFile( TWO_CARRIAGE_RETURN, pu8CharBuffer1 );
    u32ConvertToAsciiString( CUBE_LNG_MIN_VALUE, (CHAR * ) pu8CharBuffer2 );
    PrintToResultsFile( NO_CARRIAGE_RETURN, pu8CharBuffer2 );

    for (i = 0; i < CUBE_LNG_RANGE_STRING_LNG; i++) {
        pu8CharBuffer1[i] = LengthMaxValMsg[i];
    }
    pu8CharBuffer1[CUBE_LNG_RANGE_STRING_LNG] = STRING_NULL;
    PrintToResultsFile( ONE_CARRIAGE_RETURN, pu8CharBuffer1 );
    u32ConvertToAsciiString( CUBE_LNG_MAX_VALUE, (CHAR * ) pu8CharBuffer2 );
    PrintToResultsFile( NO_CARRIAGE_RETURN, pu8CharBuffer2 );

    // Minimum and Maximum Cube Height
    for (i = 0; i < CUBE_HGT_RANGE_STRING_LNG; i++) {
        pu8CharBuffer1[i] = HeightMinValMsg[i];
    }
    pu8CharBuffer1[CUBE_HGT_RANGE_STRING_LNG] = STRING_NULL;
    PrintToResultsFile( TWO_CARRIAGE_RETURN, pu8CharBuffer1 );
    u32ConvertToAsciiString( CUBE_HGT_MIN_VALUE, (CHAR * ) pu8CharBuffer2 );
    PrintToResultsFile( NO_CARRIAGE_RETURN, pu8CharBuffer2 );

    for (i = 0; i < CUBE_HGT_RANGE_STRING_LNG; i++) {
        pu8CharBuffer1[i] = HeightMaxValMsg[i];
    }
    pu8CharBuffer1[CUBE_HGT_RANGE_STRING_LNG] = STRING_NULL;
    PrintToResultsFile( ONE_CARRIAGE_RETURN, pu8CharBuffer1 );
    u32ConvertToAsciiString( CUBE_HGT_MAX_VALUE, (CHAR * ) pu8CharBuffer2 );
    PrintToResultsFile( NO_CARRIAGE_RETURN, pu8CharBuffer2 );

    // Minimum and Maximum Cube Width
    for (i = 0; i < CUBE_WDT_RANGE_STRING_LNG; i++) {
        pu8CharBuffer1[i] = WidthMinValMsg[i];
    }
    pu8CharBuffer1[CUBE_WDT_RANGE_STRING_LNG] = STRING_NULL;
    PrintToResultsFile( TWO_CARRIAGE_RETURN, pu8CharBuffer1 );
    u32ConvertToAsciiString( CUBE_WDT_MIN_VALUE, (CHAR * ) pu8CharBuffer2 );
    PrintToResultsFile( NO_CARRIAGE_RETURN, pu8CharBuffer2 );

    for (i = 0; i < CUBE_WDT_RANGE_STRING_LNG; i++) {
        pu8CharBuffer1[i] = WidthMaxValMsg[i];
    }
    pu8CharBuffer1[CUBE_WDT_RANGE_STRING_LNG] = STRING_NULL;
    PrintToResultsFile( ONE_CARRIAGE_RETURN, pu8CharBuffer1 );
    u32ConvertToAsciiString( CUBE_WDT_MAX_VALUE, (CHAR * ) pu8CharBuffer2 );
    PrintToResultsFile( NO_CARRIAGE_RETURN, pu8CharBuffer2 );

    // Minimum and Maximum Triangle Leg 1
    for (i = 0; i < TRI_RANGE_STRING_LNG; i++) {
        pu8CharBuffer1[i] = Leg1MinValMsg[i];
    }
    pu8CharBuffer1[TRI_RANGE_STRING_LNG] = STRING_NULL;
    PrintToResultsFile( TWO_CARRIAGE_RETURN, pu8CharBuffer1 );
    u32ConvertToAsciiString( TRI_LEG1_MIN_VALUE, (CHAR * ) pu8CharBuffer2 );
    PrintToResultsFile( NO_CARRIAGE_RETURN, pu8CharBuffer2 );

    for (i = 0; i < TRI_RANGE_STRING_LNG; i++) {
        pu8CharBuffer1[i] = Leg1MaxValMsg[i];
    }
    pu8CharBuffer1[TRI_RANGE_STRING_LNG] = STRING_NULL;
    PrintToResultsFile( ONE_CARRIAGE_RETURN, pu8CharBuffer1 );
    u32ConvertToAsciiString( TRI_LEG1_MAX_VALUE, (CHAR * ) pu8CharBuffer2 );
    PrintToResultsFile( NO_CARRIAGE_RETURN, pu8CharBuffer2 );

    // Minimum and Maximum Triangle Leg 2
    for (i = 0; i < TRI_RANGE_STRING_LNG; i++) {
        pu8CharBuffer1[i] = Leg2MinValMsg[i];
    }
    pu8CharBuffer1[TRI_RANGE_STRING_LNG] = STRING_NULL;
    PrintToResultsFile( TWO_CARRIAGE_RETURN, pu8CharBuffer1 );
    u32ConvertToAsciiString( TRI_LEG2_MIN_VALUE, (CHAR * ) pu8CharBuffer2 );
    PrintToResultsFile( NO_CARRIAGE_RETURN, pu8CharBuffer2 );

    for (i = 0; i < TRI_RANGE_STRING_LNG; i++) {
        pu8CharBuffer1[i] = Leg2MaxValMsg[i];
    }
    pu8CharBuffer1[TRI_RANGE_STRING_LNG] = STRING_NULL;
    PrintToResultsFile( ONE_CARRIAGE_RETURN, pu8CharBuffer1 );
    u32ConvertToAsciiString( TRI_LEG2_MAX_VALUE, (CHAR * ) pu8CharBuffer2 );
    PrintToResultsFile( NO_CARRIAGE_RETURN, pu8CharBuffer2 );
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: WriteCurrentFrameHeader>
//
//  <Full Name: Current Frame Results Header>
//
//  <Description: This function prepares header strings for
//   the current frame results being to be reported.>
//
/************************************************************/
void WriteCurrentFrameHeader(void)
/************************************************************/
{
    CHAR FrameNumberCharacterArray[10];

    u32ConvertToAsciiString( (U32)u16FrameNumber, (CHAR * ) FrameNumberCharacterArray );

    PrintToResultsFile( TWO_CARRIAGE_RETURN, (CHAR * ) CurrentFrameDivider );
    PrintToResultsFile( ONE_CARRIAGE_RETURN, (CHAR * ) FrameResultsArray );
    PrintToResultsFile( NO_CARRIAGE_RETURN,  (CHAR * ) FrameNumberCharacterArray );
    PrintToResultsFile( ONE_CARRIAGE_RETURN, (CHAR * ) CurrentFrameDivider );

    PrintToDrawFile( FOUR_CARRIAGE_RETURN, (CHAR * ) CurrentFrameDivider );
    PrintToDrawFile( ONE_CARRIAGE_RETURN,  (CHAR * ) FrameResultsArray );
    PrintToDrawFile( NO_CARRIAGE_RETURN,   (CHAR * ) FrameNumberCharacterArray );
    PrintToDrawFile( ONE_CARRIAGE_RETURN,  (CHAR * ) CurrentFrameDivider );

}
/************************************************************/



/************************************************************/
//
//  <FunctionName: WriteRetrievedDataSummary>
//
//  <Full Name: Writes Header for Results File>
//
//  <Description: This function generates results file
//   information for the current frame's retrieval process,
//   indicating which shape data was successfully retrieved.>
//
/************************************************************/
void WriteRetrievedDataSummary(void)
/************************************************************/
{
    CHAR CharBuffer[100];
    U16  i;
    U16  j;
    U16  k;
    U16  StringLength;

    // Write Retrieve Reults Header
    PrintToResultsFile( ONE_CARRIAGE_RETURN, (CHAR * ) RtrvResultsHeaderArray2 );
    PrintToResultsFile( ONE_CARRIAGE_RETURN, (CHAR * ) RtrvResultsHeaderArray1 );
    PrintToResultsFile( ONE_CARRIAGE_RETURN, (CHAR * ) RtrvResultsHeaderArray2 );

    // Write Out Any Retrieve Errors
    WriteRetrieveError();

    // Report any expected Shape Data not retrieved or set
    // in the current frame
    if ( AllDataRetrievedFlag == NO ) {
        PrintToResultsFile( TWO_CARRIAGE_RETURN, (CHAR * ) NotAllExpectedWordsRetrieved );
        for (i = 0; i < RTRV_DATA_SIZE; i++) {
            // Check for any expected shape dimensions that
            // were not set from retrieved words this frame
            if ( ShapeDataSetArray[i] == DATA_NOT_SET ) {
                StringLength = ExpexcetedDataWordLength[i];
                for (j = 0; j < StringLength; j++) {
                    CharBuffer[j] = ExpectedDataWords[i][j];
                }
                for (k = 0; k < NO_DATA_RETRIEVED_STRING_LENGTH; k++) {
                    CharBuffer[j++] = NoValueRtrvd[k];
                }
                CharBuffer[j] = STRING_NULL;
                PrintToResultsFile( ONE_CARRIAGE_RETURN, CharBuffer );
                // Indicate if a parity error prevented the
                // expected shape data from being set
                if ( RtrvWordParityErrorArray[i] == YES ) {
                    PrintToResultsFile( NO_CARRIAGE_RETURN, (CHAR * ) ParityErrorCause );
                }
                else {
                }
            }
            // Check for any shape words that contained a
            // zero value for a shape dimension when retrieved
            // this frame
            else if ( ShapeDataZeroArray[i] == YES ) {
                StringLength = RtrvDataZeroMsgLength[i];
                for (j = 0; j < StringLength; j++) {
                    CharBuffer[j] = RtrvDataZeroMsg[i][j];
                }
                CharBuffer[j] = STRING_NULL;
                PrintToResultsFile( ONE_CARRIAGE_RETURN, CharBuffer );
            }
            else {
            }
        }
    }
    else {
        PrintToResultsFile( TWO_CARRIAGE_RETURN, (CHAR * ) AllExpectedWordsRetrieved );
    }
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: WriteRetrieveError>
//
//  <Full Name: Writes Any Retrieve Errors>
//
//  <Description: This function reports any retrieve errors
//   processed in the current frame.>
//
/************************************************************/
void WriteRetrieveError(void)
/************************************************************/
{
    CHAR CharBuffer[100];
    U16  i;
    U16  j;
    U16  k;
    U16  StringLength;
    U8   WordTypeBuffer;
    U8   WordTypeRcvdMultiple[RTRV_DATA_SIZE];

    // Initialize Error Array for Multiple Words containing the same Shape Data
    for (i = 0; i < RTRV_DATA_SIZE; i++) {
        WordTypeRcvdMultiple[i] = ZERO;
    }

    // Indicate if Retrieve Errors Were Detected This Frame.
    if ( RtrvProcessResult == ONE ) {
        PrintToResultsFile( ONE_CARRIAGE_RETURN, (CHAR * ) OneRetrieveErrorDetected );
    }
    else if ( RtrvProcessResult > ONE ) {
        PrintToResultsFile( ONE_CARRIAGE_RETURN, (CHAR * ) MulipleRetrieveErrorsDetected );
    }
    else {
        PrintToResultsFile( ONE_CARRIAGE_RETURN, (CHAR * ) NoRetrieveErrorDetected );
    }

    // Write Out Retrieve Errors
    for (i = 0; i < RtrvProcessResult; i++) {
        // Clear Character Buffer
        for (j = 0; j < 100; j++) {
            CharBuffer[j] = STRING_NULL;
        }
        // If Parity Error was Detected
        if ( RtrvErrCurrentFrame[i][RTRV_ERROR_CODE_INDEX] == ERR_CODE_PRTY ) {
            for (j = 0; j < PARITY_ERROR_LENGTH; j++) {
                CharBuffer[j] = ShapeWordParityError[j];
            }
            CharBuffer[PARITY_ERROR_LENGTH] = STRING_NULL;
            ConvertAdrsValToAsciiString( RtrvErrCurrentFrame[i][RTRV_ERROR_DATA_INDEX], (CHAR * ) CharBuffer, ERROR_VALUE_INDEX_PLACE );
            PrintToResultsFile( ONE_CARRIAGE_RETURN, CharBuffer );
        }
        // If Triangle Subtype Not Recognized
        else if ( RtrvErrCurrentFrame[i][RTRV_ERROR_CODE_INDEX] == ERR_CODE_TRI ) {
            for (j = 0; j < TRI_TYPE_ERROR_LENGTH; j++) {
                CharBuffer[j] = TriDataSubtypeError[j];
            }
            CharBuffer[TRI_TYPE_ERROR_LENGTH] = STRING_NULL;
            ConvertAdrsValToAsciiString( RtrvErrCurrentFrame[i][RTRV_ERROR_DATA_INDEX], (CHAR * ) CharBuffer, ERROR_VALUE_INDEX_PLACE );
            PrintToResultsFile( ONE_CARRIAGE_RETURN, CharBuffer );
        }
        // If Cube Subtype Not Recognized
        else if ( RtrvErrCurrentFrame[i][RTRV_ERROR_CODE_INDEX] == ERR_CODE_CUBE ) {
            for (j = 0; j < CUBE_TYPE_ERROR_LENGTH; j++) {
                CharBuffer[j] = CubeDataSubtypeError[j];
            }
            CharBuffer[CUBE_TYPE_ERROR_LENGTH] = STRING_NULL;
            ConvertAdrsValToAsciiString( RtrvErrCurrentFrame[i][RTRV_ERROR_DATA_INDEX], (CHAR * ) CharBuffer, ERROR_VALUE_INDEX_PLACE );
            PrintToResultsFile( ONE_CARRIAGE_RETURN, CharBuffer );
        }
        // If Shape Label Was Not Recognized
        else if ( RtrvErrCurrentFrame[i][RTRV_ERROR_CODE_INDEX] == ERR_CODE_SHAPE ) {
            for (j = 0; j < SHAPE_LABEL_ERROR_LENGTH; j++) {
                CharBuffer[j] = ShapeWordLabelError[j];
            }
            CharBuffer[SHAPE_LABEL_ERROR_LENGTH] = STRING_NULL;
            ConvertAdrsValToAsciiString( RtrvErrCurrentFrame[i][RTRV_ERROR_DATA_INDEX], (CHAR * ) CharBuffer, ERROR_VALUE_INDEX_PLACE );
            PrintToResultsFile( ONE_CARRIAGE_RETURN, CharBuffer );
        }
        // Else if Same Shape Data Word was Retrieved Multiple Times
        else if ( RtrvErrCurrentFrame[i][RTRV_ERROR_CODE_INDEX] == ERR_CODE_SUB_SET ) {
            WordTypeBuffer = (U8) ((RtrvErrCurrentFrame[i][RTRV_ERROR_DATA_INDEX] & SHAPE_SUBTYPE_MASK) >> SHAPE_SUBTYPE_BIT_PLACE);
            WordTypeRcvdMultiple[WordTypeBuffer]+=1;
        }
        else {
        }
    }

    // If the Same Data Was Retrieved From Multiple Words
    for (i = 0; i < RTRV_DATA_SIZE; i++) {
        if ( WordTypeRcvdMultiple[i] != ZERO ) {
            StringLength = ExpexcetedDataWordLength[i];
            for (j = 0; j < StringLength; j++) {
                CharBuffer[j] = ExpectedDataWords[i][j];
            }
            for (k = 0; k < EXTRA_DATA_RETRIEVED_STRING_LENGTH; k++) {
                CharBuffer[j++] = MultipleValuesRtrvd[k];
            }
            CharBuffer[j] = STRING_NULL;
            PrintToResultsFile( ONE_CARRIAGE_RETURN, CharBuffer );
        }
    }
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: WriteCubeResults>
//
//  <Full Name: Write Cube Processing Results>
//
//  <Description: This function generates information concerning
//   retrieved cube dimensions and cube volume calculation in
//   the current frame.>
//
/************************************************************/
void WriteCubeResults(void)
/************************************************************/
{
    U16  i;
    CHAR pu8CharBuffer1[100];
    CHAR pu8CharBuffer2[100];

    // Initialize Character Buffers to NULL
    for (i = 0; i < 100; i++) {
        pu8CharBuffer1[i] = STRING_NULL;
        pu8CharBuffer2[i] = STRING_NULL;
    }

    // Write Cube Data Header
    PrintToResultsFile( TWO_CARRIAGE_RETURN, (CHAR * ) CubeResultsHeaderArray2 );
    PrintToResultsFile( ONE_CARRIAGE_RETURN, (CHAR * ) CubeResultsHeaderArray1 );
    PrintToResultsFile( ONE_CARRIAGE_RETURN, (CHAR * ) CubeResultsHeaderArray2 );

    // Print Cube Length Data
    for (i = 0; i < CUBE_LENGTH_PREAMBLE_CHAR_NO; i++) {
        pu8CharBuffer1[i] = RetrievedCubeLengthPreamble[i];
    }
    pu8CharBuffer1[i] = STRING_NULL;
    PrintToResultsFile( ONE_CARRIAGE_RETURN, pu8CharBuffer1 );
    u32ConvertToAsciiString( CubeDataStructure.u32RtrvdCubeLength, (CHAR * ) pu8CharBuffer2 );
    PrintToResultsFile( NO_CARRIAGE_RETURN, pu8CharBuffer2 );

    // Indicate if Cube Length Data set with Default or
    // a Previous Frame Value, or if retrieved data had
    // to be limited as it was outside of allowed range.
    // If multiple data retrieved for Length this frame,
    // indicate that first retrieved and legitimate value
    // used to set the data.
    if ( ShapeDataSetArray[CUBE_LNG] > DATA_SET ) {
        PrintToResultsFile( NO_CARRIAGE_RETURN, (CHAR * ) FirstRtrvValueUsed );
    }
    else if ( ShapeDataDefaultArray [CUBE_LNG] == YES ) {
        PrintToResultsFile( NO_CARRIAGE_RETURN, (CHAR * ) DataValueDefaulted );
    }
    else if ( ShapeDataPrevFrameArray[CUBE_LNG] == YES ) {
        PrintToResultsFile( NO_CARRIAGE_RETURN, (CHAR * ) PreviousFrameDataUsed );
    }
    else if ( ShapeDataLimitedArray[CUBE_LNG] == YES ) {
        PrintToResultsFile( NO_CARRIAGE_RETURN, (CHAR * ) RetrievedValueLimited );
    }
    else {
    }

    // Print Cube Height Data
    for (i = 0; i < CUBE_HEIGHT_PREAMBLE_CHAR_NO; i++) {
        pu8CharBuffer1[i] = RetrievedCubeHeightPreamble[i];
    }
    pu8CharBuffer1[i] = STRING_NULL;
    PrintToResultsFile( ONE_CARRIAGE_RETURN, pu8CharBuffer1 );
    u32ConvertToAsciiString( CubeDataStructure.u32RtrvdCubeHeight, (CHAR * ) pu8CharBuffer2 );
    PrintToResultsFile( NO_CARRIAGE_RETURN, pu8CharBuffer2 );

    // Indicate if Cube Height Data set with Default or
    // a Previous Frame Value, or if retrieved data had
    // to be limited as it was outside of allowed range.
    // If multiple data retrieved for Height this frame,
    // indicate that first retrieved and legitimate value
    // used to set the data.
    if ( ShapeDataSetArray[CUBE_HGT] > DATA_SET ) {
        PrintToResultsFile( NO_CARRIAGE_RETURN, (CHAR * ) FirstRtrvValueUsed );
    }
    else if ( ShapeDataDefaultArray [CUBE_HGT] == YES ) {
        PrintToResultsFile( NO_CARRIAGE_RETURN, (CHAR * ) DataValueDefaulted );
    }
    else if ( ShapeDataPrevFrameArray[CUBE_HGT] == YES ) {
        PrintToResultsFile( NO_CARRIAGE_RETURN, (CHAR * ) PreviousFrameDataUsed );
    }
    else if ( ShapeDataLimitedArray[CUBE_HGT] == YES ) {
        PrintToResultsFile( NO_CARRIAGE_RETURN, (CHAR * ) RetrievedValueLimited );
    }
    else {
    }

    // Print Cube Width Data
    for (i = 0; i < CUBE_WIDTH_PREAMBLE_CHAR_NO; i++) {
        pu8CharBuffer1[i] = RetrievedCubeWidthPreamble[i];
    }
    pu8CharBuffer1[i] = STRING_NULL;
    PrintToResultsFile( ONE_CARRIAGE_RETURN, pu8CharBuffer1 );
    u32ConvertToAsciiString( CubeDataStructure.u32RtrvdCubeWidth, (CHAR * ) pu8CharBuffer2 );
    PrintToResultsFile( NO_CARRIAGE_RETURN, pu8CharBuffer2 );

    // Indicate if Cube Width Data set with Default or
    // a Previous Frame Value, or if retrieved data had
    // to be limited as it was outside of allowed range.
    // If multiple data retrieved for Width this frame,
    // indicate that first retrieved and legitimate value
    // used to set the data.
    if ( ShapeDataSetArray[CUBE_WDT] > DATA_SET ) {
        PrintToResultsFile( NO_CARRIAGE_RETURN, (CHAR * ) FirstRtrvValueUsed );
    }
    else if ( ShapeDataDefaultArray [CUBE_WDT] == YES ) {
        PrintToResultsFile( NO_CARRIAGE_RETURN, (CHAR * ) DataValueDefaulted );
    }
    else if ( ShapeDataPrevFrameArray[CUBE_WDT] == YES ) {
        PrintToResultsFile( NO_CARRIAGE_RETURN, (CHAR * ) PreviousFrameDataUsed );
    }
    else if ( ShapeDataLimitedArray[CUBE_WDT] == YES ) {
        PrintToResultsFile( NO_CARRIAGE_RETURN, (CHAR * ) RetrievedValueLimited );
    }
    else {
    }

    // Write Calculated Cube Volume Data
    for (i = 0; i < CUBE_VOLUME_PREAMBLE_CHAR_NO; i++) {
        pu8CharBuffer1[i] = CalculatedCubeVolumePreamble[i];
    }
    pu8CharBuffer1[i] = STRING_NULL;
    PrintToResultsFile( ONE_CARRIAGE_RETURN, pu8CharBuffer1 );
    u32ConvertToAsciiString( CubeDataStructure.u32CalculatedCubeVolume, (CHAR * ) pu8CharBuffer2 );
    PrintToResultsFile( NO_CARRIAGE_RETURN, pu8CharBuffer2 );
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: WriteTriangleResults>
//
//  <Full Name: Write Triangle Processing Results>
//
//  <Description: This function generates information concerning
//   retrieved triangle dimensions and triangle data calculation
//   in the current frame.>
//
/************************************************************/
void WriteTriangleResults(void)
/************************************************************/
{
    U16  i;
    CHAR pu8CharBuffer1[100];
    CHAR pu8CharBuffer2[100];

    // Initialize Character Buffers to NULL
    for (i = 0; i < 100; i++) {
        pu8CharBuffer1[i] = STRING_NULL;
        pu8CharBuffer2[i] = STRING_NULL;
    }


    // Write Triangle Data Header
    PrintToResultsFile( TWO_CARRIAGE_RETURN, (CHAR * ) TriResultsHeaderArray2 );
    PrintToResultsFile( ONE_CARRIAGE_RETURN,   (CHAR * ) TriResultsHeaderArray1 );
    PrintToResultsFile( ONE_CARRIAGE_RETURN,   (CHAR * ) TriResultsHeaderArray2 );

    // Print Leg 1 Retrieved Data
    for (i = 0; i < TRI_LEG1_PREAMBLE_CHAR_NO; i++) {
        pu8CharBuffer1[i] = RetrievedTriLeg1Preamble[i];
    }
    pu8CharBuffer1[TRI_LEG1_PREAMBLE_CHAR_NO] = STRING_NULL;
    PrintToResultsFile( ONE_CARRIAGE_RETURN, pu8CharBuffer1 );
    u32ConvertToAsciiString( TriangleDataStructure.u32RtrvdTriLeg1, (CHAR * ) pu8CharBuffer2 );
    PrintToResultsFile( NO_CARRIAGE_RETURN, pu8CharBuffer2 );

    // Indicate if Leg 1 Data set with Default or a Previous
    // Frame Value, or if retrieved data had to be limited as
    // it was outside of allowed range. If multiple data
    // retrieved for Length this frame, indicate that first
    // retrieved and legitimate value used to set the data.
    if ( ShapeDataSetArray[TRI_LEG1] > DATA_SET ) {
        PrintToResultsFile( NO_CARRIAGE_RETURN, (CHAR * ) FirstRtrvValueUsed );
    }
    else if ( ShapeDataDefaultArray [TRI_LEG1] == YES ) {
        PrintToResultsFile( NO_CARRIAGE_RETURN, (CHAR * ) DataValueDefaulted );
    }
    else if ( ShapeDataPrevFrameArray[TRI_LEG1] == YES ) {
        PrintToResultsFile( NO_CARRIAGE_RETURN, (CHAR * ) PreviousFrameDataUsed );
    }
    else if ( ShapeDataLimitedArray[TRI_LEG1] == YES ) {
        PrintToResultsFile( NO_CARRIAGE_RETURN, (CHAR * ) RetrievedValueLimited );
    }
    else {
    }

    // Print Leg 2 Retrieved Data
    for (i = 0; i < TRI_LEG2_PREAMBLE_CHAR_NO; i++) {
        pu8CharBuffer1[i] = RetrievedTriLeg2Preamble[i];
    }
    pu8CharBuffer1[TRI_LEG2_PREAMBLE_CHAR_NO] = STRING_NULL;
    PrintToResultsFile( ONE_CARRIAGE_RETURN, pu8CharBuffer1 );
    u32ConvertToAsciiString( TriangleDataStructure.u32RtrvdTriLeg2, (CHAR * ) pu8CharBuffer2 );
    PrintToResultsFile( NO_CARRIAGE_RETURN, pu8CharBuffer2 );

    // Indicate if Leg 2 Data set with Default or a Previous
    // Frame Value, or if retrieved data had to be limited as
    // it was outside of allowed range. If multiple data
    // retrieved for Length this frame, indicate that first
    // retrieved and legitimate value used to set the data.
    if ( ShapeDataSetArray[TRI_LEG2] > DATA_SET ) {
        PrintToResultsFile( NO_CARRIAGE_RETURN, (CHAR * ) FirstRtrvValueUsed );
    }
    else if ( ShapeDataDefaultArray [TRI_LEG2] == YES ) {
        PrintToResultsFile( NO_CARRIAGE_RETURN, (CHAR * ) DataValueDefaulted );
    }
    else if ( ShapeDataPrevFrameArray[TRI_LEG2] == YES ) {
        PrintToResultsFile( NO_CARRIAGE_RETURN, (CHAR * ) PreviousFrameDataUsed );
    }
    else if ( ShapeDataLimitedArray[TRI_LEG2] == YES ) {
        PrintToResultsFile( NO_CARRIAGE_RETURN, (CHAR * ) RetrievedValueLimited );
    }
    else {
    }

    // Print Calculated Triangle Area
    for (i = 0; i < TRI_AREA_PREAMBLE_CHAR_NO; i++) {
        pu8CharBuffer1[i] = CalculatedTriAreaPreamble[i];
    }
    pu8CharBuffer1[TRI_AREA_PREAMBLE_CHAR_NO] = STRING_NULL;
    PrintToResultsFile( ONE_CARRIAGE_RETURN, pu8CharBuffer1 );
    f32ConvertToAsciiString( TriangleDataStructure.f32CalculatedTriArea, (CHAR * ) pu8CharBuffer2 );
    PrintToResultsFile( NO_CARRIAGE_RETURN, pu8CharBuffer2 );

    // Print Calculated Triangle Hypotenuse
    for (i = 0; i < TRI_HYPO_PREAMBLE_CHAR_NO; i++) {
        pu8CharBuffer1[i] = CalculatedTriHypoPreamble[i];
    }
    pu8CharBuffer1[TRI_HYPO_PREAMBLE_CHAR_NO] = STRING_NULL;
    PrintToResultsFile( ONE_CARRIAGE_RETURN, pu8CharBuffer1 );
    f64ConvertToAsciiString( TriangleDataStructure.f64CalculatedTriHypo, (CHAR * ) pu8CharBuffer2 );
    PrintToResultsFile( NO_CARRIAGE_RETURN, pu8CharBuffer2 );
}
/************************************************************/

/************************************************************************/

