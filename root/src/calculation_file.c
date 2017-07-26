/************************************************************************/
//
//  <FileName: calculation_file.c>
//
//  <FileDesc: ESS Calculation File>
//
//  <Version: 1.1.4>
//
/************************************************************************/
#if defined __CCS_RUN__
#include <stdio.h>
#include <math.h>
#include <string.h>
#else
#include "sqrt_ref.h"
#endif

#define CALCULATION_FILE_C_

#include "type.h"
#include "functions.h"
#include "constants.h"
#include "global_data.h"

// Previous Frame Shape Data Used Array
U32 PreviousFrameShapeDataArray[RTRV_DATA_SIZE];
// Shape Data Min Value Array
const U32 ShapeDataMinValuesArray[RTRV_DATA_SIZE]     = { TRI_LEG1_MIN_VALUE,      TRI_LEG2_MIN_VALUE,      CUBE_LNG_MIN_VALUE,     CUBE_HGT_MIN_VALUE,     CUBE_WDT_MIN_VALUE };
// Shape Data Max Value Array
const U32 ShapeDataMaxValuesArray[RTRV_DATA_SIZE]     = { TRI_LEG1_MAX_VALUE,      TRI_LEG2_MAX_VALUE,      CUBE_LNG_MAX_VALUE,     CUBE_HGT_MAX_VALUE,     CUBE_WDT_MAX_VALUE };
// Shape Data Default Values Array
const U32 ShapeDataDefaultValuesArray[RTRV_DATA_SIZE] = { TRI_LEG1_DEFAULT_VALUE,  TRI_LEG2_DEFAULT_VALUE,  CUBE_LNG_DEFAULT_VALUE, CUBE_HGT_DEFAULT_VALUE, CUBE_WDT_DEFAULT_VALUE };
// Shape Data Defaulted Error Code Array
const U8 ShapeDataDefaultedErrorArray[RTRV_DATA_SIZE] = { ERR_CODE_LEG1_DEFAULT,   ERR_CODE_LEG2_DEFAULT,   ERR_CODE_LNG_DEFAULT,   ERR_CODE_HGT_DEFAULT,   ERR_CODE_WDT_DEFAULT };
// Shape Data Zero Error Code Array
const U8 ShapeDataZeroErrorArray[RTRV_DATA_SIZE]      = { ERR_CODE_LEG1_NO_DATA,   ERR_CODE_LEG2_NO_DATA,   ERR_CODE_LNG_NO_DATA,   ERR_CODE_HGT_NO_DATA,   ERR_CODE_WDT_NO_DATA };
// Shape Data Above Max Error Code Array
const U8 ShapeDataTooBigErrorArray[RTRV_DATA_SIZE]    = { ERR_CODE_LEG1_TOO_BIG,   ERR_CODE_LEG2_TOO_BIG,   ERR_CODE_LNG_TOO_BIG,   ERR_CODE_HGT_TOO_BIG,   ERR_CODE_WDT_TOO_BIG };
// Shape Data Below Min Error Code Array
const U8 ShapeDataTooSmallErrorArray[RTRV_DATA_SIZE]  = { ERR_CODE_LEG1_TOO_SMALL, ERR_CODE_LEG2_TOO_SMALL, ERR_CODE_LNG_TOO_SMALL, ERR_CODE_HGT_TOO_SMALL, ERR_CODE_WDT_TOO_SMALL };



/************************************************************/
//
//  <FunctionName: CalcDataMain>
//
//  <Full Name: Main Calculation Function>
//
//  <Description: This function is the main function for
//   limiting and calculating shape data. Calculated data
//   is set to the appropriate structure by this function
//   unless a calculation error is raised during the
//   routine.>
//
/************************************************************/
void CalcDataMain(void)
/************************************************************/
{
    U32 LclTriLeg1Bfr;
    U32 LclTriLeg2Bfr;
    U32 LclCubeLengthBfr;
    U32 LclCubeHeightBfr;
    U32 LclCubeWidthBfr;

    TRIANGLE_DATA_STRUCT * pstrCalcTriDataPtr;
    CUBE_DATA_STRUCT * pstrCalcCubeDataPtr;

    // Set Previous Frame Value Array
    PreviousFrameShapeDataArray[TRI_LEG1] = TriangleDataStructure.u32RtrvdTriLeg1LastFrame;
    PreviousFrameShapeDataArray[TRI_LEG2] = TriangleDataStructure.u32RtrvdTriLeg2LastFrame;
    PreviousFrameShapeDataArray[CUBE_LNG] = CubeDataStructure.u32RtrvdCubeLengthLastFrame;
    PreviousFrameShapeDataArray[CUBE_HGT] = CubeDataStructure.u32RtrvdCubeHeightLastFrame;
    PreviousFrameShapeDataArray[CUBE_WDT] = CubeDataStructure.u32RtrvdCubeWidthLastFrame;

    /*****************************************************************/
    /*                     Calculate Triangle Data                   */
    /*****************************************************************/
    // Set Calculated Triangle Data Pointer to Triangle Data Structure
    pstrCalcTriDataPtr = &TriangleDataStructure;

    // Determine Triangle Leg 1 to Use
    LclTriLeg1Bfr = SetShapeData( TRI_LEG1, pstrCalcTriDataPtr->u32RtrvdTriLeg1 );
    TriangleDataStructure.u32RtrvdTriLeg1 = CalcValueLimit( TRI_LEG1, LclTriLeg1Bfr );

    // Determine Triangle Leg 2 to Use
    LclTriLeg2Bfr = SetShapeData( TRI_LEG2, pstrCalcTriDataPtr->u32RtrvdTriLeg2 );
    TriangleDataStructure.u32RtrvdTriLeg2 = CalcValueLimit( TRI_LEG2, LclTriLeg2Bfr );

    // Calculate Triangle Area
    pstrCalcTriDataPtr->f32CalculatedTriArea = CalcTriangleArea( pstrCalcTriDataPtr->u32RtrvdTriLeg1, pstrCalcTriDataPtr->u32RtrvdTriLeg2 );

    // Calculate Triangle Hypotenuse
    pstrCalcTriDataPtr->f64CalculatedTriHypo = CalcTriangleHypo( pstrCalcTriDataPtr->u32RtrvdTriLeg1, pstrCalcTriDataPtr->u32RtrvdTriLeg2 );

    /*****************************************************************/
    /*                       Calculate Cube Data                     */
    /*****************************************************************/
    // Set Calculated Cube Data Pointer to Cube Data Structure
    pstrCalcCubeDataPtr = &CubeDataStructure;

    // Determine Cube Length to Use
    LclCubeLengthBfr = SetShapeData( CUBE_LNG, pstrCalcCubeDataPtr->u32RtrvdCubeLength );
    CubeDataStructure.u32RtrvdCubeLength = CalcValueLimit( CUBE_LNG, LclCubeLengthBfr );

    // Determine Cube Height to Use
    LclCubeHeightBfr = SetShapeData( CUBE_HGT, pstrCalcCubeDataPtr->u32RtrvdCubeHeight );
    CubeDataStructure.u32RtrvdCubeHeight = CalcValueLimit( CUBE_HGT, LclCubeHeightBfr );

    // Determine Cube Width to Use
    LclCubeWidthBfr = SetShapeData( CUBE_WDT, pstrCalcCubeDataPtr->u32RtrvdCubeWidth );
    CubeDataStructure.u32RtrvdCubeWidth = CalcValueLimit( CUBE_WDT, LclCubeWidthBfr );

    // Calculate Cube Volume
    pstrCalcCubeDataPtr->u32CalculatedCubeVolume = CalcCubeVol( pstrCalcCubeDataPtr->u32RtrvdCubeLength, pstrCalcCubeDataPtr->u32RtrvdCubeHeight, pstrCalcCubeDataPtr->u32RtrvdCubeWidth );


    /*****************************************************************/
    /*             Set Calculated Data to Memory                     */
    /*****************************************************************/
    // <#100. Call SetCalcDataToMemory (no parameters).>
    SetCalcDataToMemory();
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: SetShapeData>
//
//  <Full Name: Set Shape Data within allowable range.>
//
//  <Description: This function returns the input data with
//   the value limited between minimum and maximum values
//   (inclusive) if necessary.>
//
/************************************************************/
U32 SetShapeData(
     U8   ShapeSubType,                // Input: Shape Data SubType
     U32  InputShapeData)              // Input: Shape Data Value
/************************************************************/
{
    BOOL RetrieveError = NO;
    BOOL ShapeDataZero = NO;
    BOOL ShapeDataDefaulted = NO;
    BOOL ShapeDataDefaultedFromZero = NO;

    // Check Retrieve Error Flag For Shape Data
    if (RtrvDataErrorArray[ShapeSubType] == YES ) {
        RetrieveError = YES;
    }
    // No Shape Data Retrieved
    if ( InputShapeData == ZERO ) {
        ShapeDataZero = YES;
    }
    // Check Default Flag For Shape Data
    if ( ShapeDataDefaultArray[ShapeSubType] == YES ) {
        ShapeDataDefaulted = YES;
    }
    // If Shape Data Zero and Default Value Flag Raised
    ShapeDataDefaultedFromZero = ShapeDataZero && ShapeDataDefaulted;

    // Record Any Applicable Errors and Manage Status Arrays
    if ( ShapeDataDefaultedFromZero ) CalcErrRcdFunc( ShapeDataDefaultedErrorArray[ShapeSubType], InputShapeData );
    else if ( ShapeDataZero ) {
        CalcErrRcdFunc( ShapeDataZeroErrorArray[ShapeSubType], InputShapeData );
        ShapeDataPrevFrameArray[ShapeSubType] = YES;
    }
    else if ( RetrieveError ) ShapeDataPrevFrameArray[ShapeSubType] = YES;

    if ( ShapeDataZero ) ShapeDataZeroArray[ShapeSubType] = YES; else ShapeDataZeroArray[ShapeSubType] = NO;

    // Set All Data Retrieved Flag to NO if Shape Data not Retrieved
    if ( ShapeDataZero ) AllDataRetrievedFlag = NO;

    /************************************************************/
    /* Retrieve Error Flag is Raised or No Shape Data Retrieved */
    /************************************************************/
    if ( ( RetrieveError ) || ( ShapeDataZero ) ) {
       /****************************************/
       /*        Return Default Value          */
       /****************************************/
       if ( ShapeDataDefaultedFromZero ) {
           return ShapeDataDefaultValuesArray[ShapeSubType];
       }
       /****************************************/
       /*      Return Previous Frame Value     */
       /****************************************/
       else {
           return PreviousFrameShapeDataArray[ShapeSubType];
       }
    }
    /**********************************************/
    /* No Retrieve Errors And Shape Data Not Zero */
    /**********************************************/
    else {
        return InputShapeData;
    }
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: CalcValueLimit>
//
//  <Full Name: Limit Shape Data to Allowable Range.>
//
//  <Description: This function returns the input data with
//   the value limited between minimum and maximum values
//   (inclusive) if the data is outside the allowable range.>
//
/************************************************************/
U32 CalcValueLimit(
    U8 u8SubShapeType,      // Input: Shape Dimension (Subtype)
    U32 u32ShapeValue)      // Input: Shape Value
/************************************************************/
{
    U32 DataAboveMaxIndicator;
    U32 DataBelowMinIndicator;

    DataAboveMaxIndicator = ShapeDataAboveMaxCheck( u32ShapeValue, ShapeDataMaxValuesArray[u8SubShapeType] );
    DataBelowMinIndicator = ShapeDataBelowMinCheck( u32ShapeValue, ShapeDataMinValuesArray[u8SubShapeType] );

    /************************************/
    /*     Data Above Maximum Value     */
    /************************************/
    if ( u32ShapeValue != DataAboveMaxIndicator+1 ) {
        CalcErrRcdFunc( ShapeDataTooBigErrorArray[u8SubShapeType], u32ShapeValue );
        ShapeDataLimitedArray[u8SubShapeType] = YES;
        return ShapeDataMaxValuesArray[u8SubShapeType];
    }
    /************************************/
    /*     Data Below Minimum Value     */
    /************************************/
    else if ( u32ShapeValue != DataBelowMinIndicator-1 ) {
        CalcErrRcdFunc( ShapeDataTooSmallErrorArray[u8SubShapeType], u32ShapeValue );
        ShapeDataLimitedArray[u8SubShapeType] = YES;
        return ShapeDataMinValuesArray[u8SubShapeType];
    }
    /************************************/
    /*         Data Within Range        */
    /************************************/
    else {
        ShapeDataLimitedArray[u8SubShapeType] = NO;
        return u32ShapeValue;
    }
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: ShapeDataAboveMaxCheck>
//
//  <Full Name: Shape Data Above Maximum Value Check>
//
//  <Description: This function modifies the Data Out of Range
//   Indicator according to the input Shape Data Value and the
//   input Maximum Shape Data Value.>
//
/************************************************************/
U32 ShapeDataAboveMaxCheck(
    U32 ShapeData,                 // Input: Shape Data Value
    U32 ShapeDataMaxValue)         // Input: Maximum Shape Data Value
/************************************************************/
{
    // Set Return Value to Input Shape Data Value
    U32 LclOutOfRangeIndicatorBuffer = ShapeData;

    // If Input Shape Data Value is maximum U32 value return 0
    if ( ShapeData == 0xFFFFFFFF ){
        LclOutOfRangeIndicatorBuffer = 0;
    }
    // If Input Shape Data Value is GT Input Maximum Shape Data
    // Value, increment return value; otherwise decrement return
    // value
    else {
        LclOutOfRangeIndicatorBuffer > ShapeDataMaxValue ? LclOutOfRangeIndicatorBuffer++ : LclOutOfRangeIndicatorBuffer--;
    }
	return LclOutOfRangeIndicatorBuffer;
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: ShapeDataBelowMinCheck>
//
//  <Full Name: Shape Data Below Minimum Value Check>
//
//  <Description: This function modifies the Data Out of Range
//   Indicator according to the input Shape Data Value and the
//   input Minimum Shape Data Value.>
//
/************************************************************/
U32 ShapeDataBelowMinCheck(
    U32 ShapeData,                 // Input: Shape Data Value
    U32 ShapeDataMinValue)         // Input: Minimum Shape Data Value
/************************************************************/
{
    // Set Return Value to input Shape Data Value
    U32 LclOutOfRangeIndicatorBuffer = ShapeData;

    // If input Shape Data Value is 0, return maximum U32 value
    if ( ShapeData == 0 ){
        LclOutOfRangeIndicatorBuffer = 0xFFFFFFFF;
    }
    // If input Shape Data Value is LT input Minimum Shape Data
    // Value, decrement return value; otherwise increment return
    // value
    else {
        LclOutOfRangeIndicatorBuffer < ShapeDataMinValue ? LclOutOfRangeIndicatorBuffer-- : LclOutOfRangeIndicatorBuffer++;
    }
	return LclOutOfRangeIndicatorBuffer;
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: CalcTriangleArea>
//
//  <Full Name: Calculate Right Triangle Area Function>
//
//  <Description: This function calculates the area of a
//   right triangle with the retrieved triangle leg data.>
//
/************************************************************/
F32 CalcTriangleArea(
    U32 u32InputLeg1,                    // Input: Triangle Leg 1
    U32 u32InputLeg2)                    // Input: Triangle Leg 2
/************************************************************/
{
    F32 f32LegsCombined;
    F32 f32TriAreaReturn;

    // Right Triangle Area = (Leg 1 * Leg 2) / 2
    f32LegsCombined  = (F32) (u32InputLeg1 * u32InputLeg2);
    f32TriAreaReturn = f32LegsCombined / 2;

    return f32TriAreaReturn;
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: CalcTriangleHypo>
//
//  <Full Name: Calculate Right Triangle Hypotenuse Function>
//
//  <Description: This function calculates the hypotenuse of
//   a right triangle with the retrieved triangle leg data.>
//
/************************************************************/
F64 CalcTriangleHypo(
    U32 u32InputLeg1,                    // Input: Triangle Leg 1
    U32 u32InputLeg2)                    // Input: Triangle Leg 2
/************************************************************/
{
    U32 u32InputLeg1Squared;
    U32 u32InputLeg2Squared;
    U32 u32InputLegsSquaredSum;
    F64 f64TriHypoReturn;

    // Hypotenuse of Right Triangle = sqrt(Leg 1^2 + Leg 2^2)
    u32InputLeg1Squared = u32InputLeg1 * u32InputLeg1;
    u32InputLeg2Squared = u32InputLeg2 * u32InputLeg2;

    u32InputLegsSquaredSum = u32InputLeg1Squared + u32InputLeg2Squared;

#ifdef __CCS_RUN__
    f64TriHypoReturn = sqrt( u32InputLegsSquaredSum );
#else
    f64TriHypoReturn = (F64) SqrtRefTbl[u32InputLegsSquaredSum];
#endif

    return f64TriHypoReturn;
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: CalcCubeVol>
//
//  <Full Name: Calculate Cube Volume Function>
//
//  <Description: This function calculates the volume of the
//   retrieved Cube Dimensions.>
//
/************************************************************/
U32 CalcCubeVol(
    U32 u32InputLength,                  // Input: Cube Length
    U32 u32InputHeight,                  // Input: Cube Height
    U32 u32InputWidth)                   // Input: Cube Width
/************************************************************/
{
    U32 u32CubeVolReturn;

    // Cube Volume = Length * Height * Width
    u32CubeVolReturn = u32InputLength * u32InputHeight * u32InputWidth;

    return u32CubeVolReturn;
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: SetCalcDataToMemory>
//
//  <Full Name: Set Calculated Data to Memory>
//
//  <Description: This function sets the calculated Triangle
//   and Cube data to the Calculated Data Area.>
//
/************************************************************/
void SetCalcDataToMemory()
/************************************************************/
{
    U16 i;
    U32 FloatDataBuffer[5];
    U32 SaveDataArrayBuffer[CALCULATED_DATA_ADRS_NO];
    U16 FrameNumberOffset;
    F64 f64CalculatedTriAreaBuffer;
    volatile U32 *CalculatedDataPointer;


    f64CalculatedTriAreaBuffer = (F64)TriangleDataStructure.f32CalculatedTriArea;

    // Set Floating Point Data Buffer
    *(F64 *) (&FloatDataBuffer[0]) = f64CalculatedTriAreaBuffer;
    *(F64 *) (&FloatDataBuffer[2]) = TriangleDataStructure.f64CalculatedTriHypo;
    *(U32 *) (&FloatDataBuffer[4]) = CubeDataStructure.u32CalculatedCubeVolume;

    // Set Calculated Data Array Buffer
    SaveDataArrayBuffer[0] = (U32) u16FrameNumber;                    // Frame Number
    SaveDataArrayBuffer[TRI_AREA_SAVE_INDEX1] = FloatDataBuffer[0];   // F32 (stored as F64) TriangleArea (MSB)
    SaveDataArrayBuffer[TRI_AREA_SAVE_INDEX2] = FloatDataBuffer[1];   // F32 (stored as F64) TriangleArea (LSB)
    SaveDataArrayBuffer[TRI_HYPO_SAVE_INDEX1] = FloatDataBuffer[2];   // F64 Triangle Hypotenuse (MSB)
    SaveDataArrayBuffer[TRI_HYPO_SAVE_INDEX2] = FloatDataBuffer[3];   // F64 Triangle Hypotenuse (LSB)
    SaveDataArrayBuffer[CUBE_VOL_SAVE_INDEX]  = FloatDataBuffer[4];   // U32 Cube Volume

    // Determine Frame Number Address Offset
    FrameNumberOffset = (u16FrameNumber - 1) * CALCULATED_DATA_RSVRD_SPACE;

    // Set calculated data pointer to head of Calculated Data Area
    // and offset according to Frame Number and record data
    CalculatedDataPointer = (U32 *) (CALCULATED_DATA_HD_ADRS + FrameNumberOffset);

    for (i = 0; i < CALCULATED_DATA_ADRS_NO; i++) {
        CalculatedDataPointer[i] = SaveDataArrayBuffer[i];
    }
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: CalcErrRcdFunc>
//
//  <Full Name: Create a Calculation Error Record>
//
//  <Description: This function prepares an array of error
//   information to be set to memory in the case that an
//   error is detected during data calculation.>
//
/************************************************************/
void CalcErrRcdFunc(
    U8  u8CalcErrorCode,            // Input: Calculation Error Code
    U32 u32ShapeData)               // Input: Shape Data (Not used for Cube Calculation)
/************************************************************/
{
    U16 i;
    U32 SaveErrorInMemoryBuffer[CALC_ERR_RCD_LENGTH];

    /***************************************************************/
    /*               Set Calculation Error Record Array            */
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
    CalcErrCurrentFrame[CalcErrCurrentFrameCounter][0] = (U32) u16FrameNumber;
    CalcErrCurrentFrame[CalcErrCurrentFrameCounter][1] = (U32) u8CalcErrorCode;
    CalcErrCurrentFrame[CalcErrCurrentFrameCounter][2] =       u32ShapeData;

    /***************************************************************/
    /*         Transfer Data from Calculation Process Error        */
    /***************************************************************/
    for (i = 0; i < CALC_ERR_RCD_LENGTH; i++){
        SaveErrorInMemoryBuffer[i] = CalcErrCurrentFrame[CalcErrCurrentFrameCounter][i];
    }
    GenumErrorType = ENUM_CALC_ERROR;
    SetErrorDataToMemory( (U32 *)SaveErrorInMemoryBuffer, CALC_ERR_RCD_LENGTH );

    /***************************************************************/
    /*      Increment Current Frame Calculation Error Counter      */
    /***************************************************************/
    CalcErrCurrentFrameCounter++;
}
/************************************************************/


/************************************************************************/
