/************************************************************************/
//
//  <FileName: retrieve_file.c>
//
//  <FileDesc: ESS Retrieve File>
//
//  <Version: 1.1.3>
//
/************************************************************************/
#if defined __CCS_RUN__
#include <stdio.h>
#include <string.h>
#endif

#define RETRIEVE_FILE_C_

#include "type.h"
#include "functions.h"
#include "constants.h"
#include "global_data.h"

// Shape Data Not Set Error Code Array
const U32 ShapeDataNotSetErrorArray[RTRV_DATA_SIZE] = { ERR_CODE_LEG1_NOTSET,
                                                        ERR_CODE_LEG2_NOTSET,
                                                        ERR_CODE_LNG_NOTSET,
                                                        ERR_CODE_HGT_NOTSET,
                                                        ERR_CODE_WDT_NOTSET  };

/************************************************************/
//
//  <FunctionName: RtrvDataMain>
//
//  <Full Name: Main Retrieve Data Function>
//
//  <Description: This function retrieves and unpackages
//   input shape data words from the Input Data Area. Data
//   is processed via calls to RtrvDataProcess function.>
//
/************************************************************/
void RtrvDataMain(void)
/************************************************************/
{
    BOOL ProcessDataResult;
    U8  RtrvWordSubTypeBfr;
    U16 i;
    U32 rtrvDataBfr;
    volatile U32 *rtrvDataIn;
    volatile U32 *SaveRtrvData;

    // Set Retrieve Data Pointer to Input Data Area Head Address
    rtrvDataIn = (U32 *)RTRV_DATA_HD_ADRS;

    // Set Retrieved Word Snapshot Data Area Pointer According
    // Current Frame
    SaveRtrvData = (U32 *) (RTRVD_DATA_WORD_HD_ADRS + ((u16FrameNumber - 1) * RTRVD_DATA_WORD_RSVRD_SPACE));

    // Process Retrieved Words from Input Data Area
    for (i = 0; i < RTRV_DATA_SIZE; i++) {

        // Retrieve Word from Input Data Area
        rtrvDataBfr = rtrvDataIn[i];

        // Save Retrieved Shape Data Word to Retrieved Data Word Area
        SaveRtrvData[i] = rtrvDataBfr;

        // Process Retrieved Shape Data Word
        ProcessDataResult = RtrvDataProcess( rtrvDataBfr );

        // Set Error Flag For Retrieved Word Type (use word subtype
        // as index)
        RtrvWordSubTypeBfr = (U8) ((rtrvDataBfr & SHAPE_SUBTYPE_MASK) >> SHAPE_SUBTYPE_BIT_PLACE);
        RtrvDataErrorArray[RtrvWordSubTypeBfr] = ProcessDataResult;
        RtrvProcessResult += ProcessDataResult;
    }

    // Check that all shape data was set, record error for any shape data
    // not set this frame
    AllDataRetrievedFlag = YES;
    for (i = 0; i < RTRV_DATA_SIZE; i++) {
        if ( ShapeDataSetArray[i] == DATA_NOT_SET ){
            AllDataRetrievedFlag = NO;
            rtrvDataBfr = rtrvDataIn[i];
            RtrvErrRcdFunc( ShapeDataNotSetErrorArray[i], rtrvDataBfr );
        }
    }

    // Clear Retrieve Data Area after retrieving all data words
    for (i = 0; i < RTRV_DATA_SIZE; i++) {
        rtrvDataIn[i] = 0x00000000;
    }
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: RtrvDataProcess>
//
//  <Full Name: Retrieve Data Processing Function>
//
//  <Description: This function processes unpackaged shape
//   word data retrieved from the Input Data Area and handles
//   any retrieved data errors appropriately.>
//
/************************************************************/
BOOL RtrvDataProcess(
    U32 rtrvdWord)       // Input Retrieved Word
/************************************************************/
{
    U8 shapeType;                    // Shape Type Label
    U8 shapeSub;                     // Subtype Label
    U8 MultipleDataBuffer;           // Same Data Retrieve Counter
    U32 shapeData;                   // Shape Data
    BOOL shapePrty;                  // Parity Bit
    BOOL ErrorFlag;

    /***************************************************/
    /*              Unpack Retrieved Word              */
    /***************************************************/
    shapeType  = (U8)   ((rtrvdWord & SHAPE_TYPE_MASK)    >> SHAPE_TYPE_BIT_PLACE) ;
    shapeSub   = (U8)   ((rtrvdWord & SHAPE_SUBTYPE_MASK) >> SHAPE_SUBTYPE_BIT_PLACE);
    shapeData  = (U32)  ((rtrvdWord & SHAPE_DATA_MASK)    >> SHAPE_DATA_BIT_PLACE);
    shapePrty  = (BOOL) ((rtrvdWord & SHAPE_PRTY_MASK)    >> SHAPE_PRTY_BIT_PLACE);

    ErrorFlag = NO;

    /****************************************************/
    /* Check If Shape Data Already Retrieved This Frame */
    /****************************************************/
    if ( ShapeDataSetArray[shapeSub] != DATA_NOT_SET ) {
        if ( ( ( shapeType == SHAPE_TRIANGLE ) && ( ( shapeSub == TRI_LEG1 ) || ( shapeSub == TRI_LEG2 ) ) ) ||
             ( ( shapeType == SHAPE_CUBE     ) && ( ( shapeSub == CUBE_LNG ) || ( shapeSub == CUBE_HGT ) || ( shapeSub == CUBE_WDT ) ) ) ) {
            MultipleDataBuffer = ShapeDataSetArray[shapeSub];
            MultipleDataBuffer++;
            ShapeDataSetArray[shapeSub] = MultipleDataBuffer;
            RtrvErrRcdFunc( ERR_CODE_SUB_SET, rtrvdWord );
            RtrvProcessResult++;
            ErrorFlag = NO;
            return ErrorFlag;
        }
        else {
        }
    }
    else {
    }

    /*********************************************/
    /*             Parity Check                  */
    /*********************************************/
    if ( shapePrty == PRTY_NG ) {
        RtrvWordParityErrorArray[shapeSub] = YES;
        RtrvErrRcdFunc( ERR_CODE_PRTY, rtrvdWord );
        ErrorFlag = YES;
        return ErrorFlag;
    }
    else {
        RtrvWordParityErrorArray[shapeSub] = NO;
    }

    /***********************************************/
    /* Process Retrieved Word if Word Type Not Yet */
    /* Retrieved This RAME and Parity is Correct   */
    /***********************************************/
    switch ( shapeType ) {
        /*********************************************/
        /* Process Data from Retrieved Triangle Word */
        /*********************************************/
        case SHAPE_TRIANGLE:
            switch ( shapeSub ) {
                /*******************************************/
                /*       Process Triangle Leg 1 Word       */
                /*******************************************/
                case TRI_LEG1:
                    TriangleDataStructure.u32RtrvdTriLeg1 = shapeData;
                    ShapeDataSetArray[shapeSub] = DATA_SET;
                    ErrorFlag = NO;
                    if ( ( ShapeDataDefaultArray[shapeSub] == YES ) && ( shapeData > ZERO ) ) {
                        ShapeDataDefaultArray[shapeSub] = NO;
                    }
                    else {
                    }
                    break;
                /*******************************************/
                /*       Process Triangle Leg 1 Word       */
                /*******************************************/
                case TRI_LEG2:
                    TriangleDataStructure.u32RtrvdTriLeg2 = shapeData;
                    ShapeDataSetArray[shapeSub] = DATA_SET;
                    ErrorFlag = NO;
                    if ( ( ShapeDataDefaultArray[shapeSub] == YES ) && ( shapeData > ZERO ) ) {
                        ShapeDataDefaultArray[shapeSub] = NO;
                    }
                    else {
                    }
                    break;
                /*******************************************/
                /*  Process Unknown Triange SubType Error  */
                /*******************************************/
                default:
                    RtrvErrRcdFunc( ERR_CODE_TRI, rtrvdWord );
                    ErrorFlag = YES;
                    break;
				}
            break;
        /*********************************************/
        /*        Process Data from Cube Word        */
        /*********************************************/
        case SHAPE_CUBE:
            switch ( shapeSub ) {
                /*******************************************/
                /*         Process Cube Length Word        */
                /*******************************************/
                case CUBE_LNG:
                    CubeDataStructure.u32RtrvdCubeLength = shapeData;
                    ShapeDataSetArray[shapeSub] = DATA_SET;
                    ErrorFlag = NO;
                    if ( ( ShapeDataDefaultArray[shapeSub] == YES ) && ( shapeData > ZERO ) ) {
                        ShapeDataDefaultArray[shapeSub] = NO;
                    }
                    else {
                    }
                    break;
                /*******************************************/
                /*         Process Cube Height Word        */
                /*******************************************/
                case CUBE_HGT:
                    CubeDataStructure.u32RtrvdCubeHeight = shapeData;
                    ShapeDataSetArray[shapeSub] = DATA_SET;
                    ErrorFlag = NO;
                    if ( ( ShapeDataDefaultArray[shapeSub] == YES ) && ( shapeData > ZERO ) ) {
                        ShapeDataDefaultArray[shapeSub] = NO;
                    }
                    else {
                    }
                    break;
                /*******************************************/
                /*         Process Cube Width Word         */
                /*******************************************/
                case CUBE_WDT:
                    CubeDataStructure.u32RtrvdCubeWidth = shapeData;
                    ShapeDataSetArray[shapeSub] = DATA_SET;
                    ErrorFlag = NO;
                    if ( ( ShapeDataDefaultArray[shapeSub] == YES ) && ( shapeData > ZERO ) ) {
                        ShapeDataDefaultArray[shapeSub] = NO;
                    }
                    else {
                    }
                    break;
                /*******************************************/
                /*    Process Unknown Cube SubType Error   */
                /*******************************************/
                default:
                    ErrorFlag = YES;
                    RtrvErrRcdFunc( ERR_CODE_CUBE, rtrvdWord );
                    break;
				}
                break;
        /*********************************************/
        /*      Process Unknown Word Type Error      */
        /*********************************************/
        default:
            ErrorFlag = YES;
            RtrvErrRcdFunc( ERR_CODE_SHAPE, rtrvdWord );
            break;
        }
    return ErrorFlag;
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: RtrvErrRcdFunc>
//
//  <Full Name: Create a Retrieve Error Record>
//
//  <Description: This function prepares an array of error
//   information to be set to memory in the case that an
//   error is detected during data retrieval.>
//
/************************************************************/
void RtrvErrRcdFunc(
    U8  u8ProcessErrorCode,     // Input: Retrieve Error Code
    U32 u32RetrievedWord)       // Input: Retrieved Shape Word
/************************************************************/
{
    U16 i;
    U32 SaveErrorInMemoryBuffer[RTRV_ERR_RCD_LENGTH];

    /***************************************************************/
    /*        Set Current Frame Retrieve Error Record Array        */
    /***************************************************************/
    /* Row: Determined by Current Frame Retrieve Error Counter     */
    /*                                                             */
    /* Column 0: Frame Number                                      */
    /* Column 1: Error Code                                        */
    /* Column 2: Retrieved Word Containing Error                   */
    /*                                                             */
    /* Note: All recorded data is converted to U32 before          */
    /* stored in the Current Frame Retrieve Error Record           */
    /* Array. Each set row of the array is saved to the            */
    /* Retrieve Error Data Area. All data is cleared from          */
    /* the array as part of the periodic processing.               */
    /***************************************************************/
    RtrvErrCurrentFrame[RtrvErrCurrentFrameCounter][0] = (U32) u16FrameNumber;
    RtrvErrCurrentFrame[RtrvErrCurrentFrameCounter][1] = (U32) u8ProcessErrorCode;
    RtrvErrCurrentFrame[RtrvErrCurrentFrameCounter][2] =       u32RetrievedWord;

    /***************************************************************/
    /*          Set Retrieve Error Information to Memory           */
    /***************************************************************/
    for (i = 0; i < RTRV_ERR_RCD_LENGTH; i++){
        SaveErrorInMemoryBuffer[i] = RtrvErrCurrentFrame[RtrvErrCurrentFrameCounter][i];
    }
    GenumErrorType = ENUM_RTRV_ERROR;
    SetErrorDataToMemory( (U32 *)SaveErrorInMemoryBuffer, RTRV_ERR_RCD_LENGTH );

    /***************************************************************/
    /*        Increment Current Frame Retrieve Error Counter       */
    /***************************************************************/
    RtrvErrCurrentFrameCounter++;
}
/************************************************************/


/************************************************************************/
