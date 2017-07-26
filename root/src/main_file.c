/************************************************************************/
//
//  <FileName: main_file.c>
//
//  <FileDesc: ESS Main File>
//
//  <Version: 1.1.3>
//
/************************************************************************/
#if defined __CCS_RUN__
#include <stdio.h>
#include <string.h>
#include <math.h>
#endif

#define MAIN_FILE_C_

#include "type.h"
#include "functions.h"
#include "constants.h"
#include "global_data.h"



/************************************************************/
//
//  <FunctionName: main>
//
//  <Full Name: Main System Function>
//
//  <Description: This function is the program entry. It
//   initializes program data and the results files before
//   beginning the periodic process. At the completion of
//   the periodic process, it makes calls to close the
//   results files before exiting the program.>
//
/************************************************************/
void main(void)
/************************************************************/
{
    U16 i;

    /***********************************************/
    /*              Initialize Data                */
    /***********************************************/
    DataInit();

    /***********************************************/
    /*      Initialize Results and Draw Files      */
    /***********************************************/
    ResultsFilesInit();

    /***********************************************/
    /*  Perform Frame Processing up to Final Frame */
    /***********************************************/
    for (i = 0; i < FINAL_FRAME; i++) {
        FrameProcess();
    }

    /***********************************************/
    /*         Close Results and Draw Files        */
    /***********************************************/
    CloseResultsFiles();

    return;
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: FrameProcess>
//
//  <Full Name: Frame Processing Function>
//
//  <Description: This function performs the frame process.
//   It increments the frame counter, updates previous frame
//   and initializes current frame data before peforming the
//   periodic processing, which is done via calls to the main
//   retrieve, calculation, and results functions.>
//
/************************************************************/
void FrameProcess(void)
/************************************************************/
{
    U16 i;
    U16 j;

    /***********************************************/
    /*             Update Frame Number             */
    /***********************************************/
    // <#10. Increment the Current Frame Number.>
    u16FrameNumber++;

    /***********************************************/
    /*        Update Previous Frame Data           */
    /***********************************************/
    TriangleDataStructure.u32RtrvdTriLeg1LastFrame = TriangleDataStructure.u32RtrvdTriLeg1;
    TriangleDataStructure.u32RtrvdTriLeg2LastFrame = TriangleDataStructure.u32RtrvdTriLeg2;
    CubeDataStructure.u32RtrvdCubeLengthLastFrame  = CubeDataStructure.u32RtrvdCubeLength;
    CubeDataStructure.u32RtrvdCubeHeightLastFrame  = CubeDataStructure.u32RtrvdCubeHeight;
    CubeDataStructure.u32RtrvdCubeWidthLastFrame   = CubeDataStructure.u32RtrvdCubeWidth;

    /***********************************************/
    /*     Write Current Frame to Stderr Window    */
    /***********************************************/
    // <#70. Call WriteFrameToStdout (no parameters).>
    WriteFrameToStdout();

    /***********************************************/
    /*      Reset Current Frame Error Counters     */
    /***********************************************/
    RtrvProcessResult          = 0;
    RtrvErrCurrentFrameCounter = 0;
    CalcErrCurrentFrameCounter = 0;

    /***********************************************/
    /*       Clear Current Frame Error Arrays      */
    /***********************************************/
    for (i = 0; i < MAX_FRAME_ERR; i++) {
        for (j = 0; j < RTRV_ERR_RCD_LENGTH; j++) {
            RtrvErrCurrentFrame[i][j] = 0;
        }
        for (j = 0; j < CALC_ERR_RCD_LENGTH; j++) {
            CalcErrCurrentFrame[i][j] = 0;
        }
    }

    /***********************************************/
    /*    Reset Current Frame Data Status Arrays   */
    /***********************************************/
    for (i = 0; i < RTRV_DATA_SIZE; i++) {
        RtrvDataErrorArray[i]       = YES;
        ShapeDataSetArray[i]        = DATA_NOT_SET;
        RtrvWordParityErrorArray[i] = NO;
        ShapeDataZeroArray[i]       = NO;
        ShapeDataLimitedArray[i]    = NO;
        ShapeDataPrevFrameArray[i]  = NO;
    }

    /***********************************************/
    /*           If AUTO_INPUT is Defined          */
    /***********************************************/
#ifdef __AUTO_INPUT__
    SetRetrieveData();
#endif

    /***********************************************/
    /*           Perform Retrieve Function         */
    /***********************************************/
    RtrvDataMain();

    /***********************************************/
    /*         Perform Calculation Function        */
    /***********************************************/
    CalcDataMain();

    /***********************************************/
    /*            Perform Results Function         */
    /***********************************************/
    ResultsDataMain();

}
/************************************************************/



/************************************************************/
//
//  <FunctionName: DataInit>
//
//  <Full Name: Data Initialization Function>
//
//  <Description: This function initializes program data on
//   the first frame of processing. It also clears the values
//   at each address of all data areas the program writes to.>
//
/************************************************************/
void DataInit(void)
/************************************************************/
{
    U32 i;
    U32 j;
    volatile U32 *ClearAddrsBuffer;

    /***********************************************/
    /*           Initialize Frame Number           */
    /***********************************************/
    u16FrameNumber = 0;

    /***********************************************/
    /*            Initialize Shape Data            */
    /***********************************************/
    TriangleDataStructure.u32RtrvdTriLeg1 = 0;
    TriangleDataStructure.u32RtrvdTriLeg2 = 0;
    CubeDataStructure.u32RtrvdCubeLength  = 0;
    CubeDataStructure.u32RtrvdCubeHeight  = 0;
    CubeDataStructure.u32RtrvdCubeWidth   = 0;

    /***********************************************/
    /*    Initialize Previous Frame Shape Data     */
    /***********************************************/
    TriangleDataStructure.u32RtrvdTriLeg1LastFrame = TriangleDataStructure.u32RtrvdTriLeg1;
    TriangleDataStructure.u32RtrvdTriLeg2LastFrame = TriangleDataStructure.u32RtrvdTriLeg2;
    CubeDataStructure.u32RtrvdCubeLengthLastFrame  = CubeDataStructure.u32RtrvdCubeLength;
    CubeDataStructure.u32RtrvdCubeHeightLastFrame  = CubeDataStructure.u32RtrvdCubeHeight;
    CubeDataStructure.u32RtrvdCubeWidthLastFrame   = CubeDataStructure.u32RtrvdCubeWidth;

    /***********************************************/
    /* Initialize Shape Data Set to Default Array  */
    /***********************************************/
    for (i = 0; i < RTRV_DATA_SIZE; i++) {
        ShapeDataDefaultArray[i] = YES;
    }

    /***********************************************/
    /*            Initialize Data Areas            */
    /***********************************************/
    ClearAddrsBuffer = (U32 *) RTRV_DATA_HD_ADRS;
    j = 0;
    for (i = RTRV_DATA_HD_ADRS; i <= CALCULATED_DATA_END_ADRS; j++){
        ClearAddrsBuffer[j] = 0x00000000;
        i+=0x0000004;
    }
}
/************************************************************/


/************************************************************************/
