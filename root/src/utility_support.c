/************************************************************************/
//
//  <FileName: utility_support.c>
//
//  <FileDesc: ESS Utility File>
//
//  <Version: 1.1.3>
//
/************************************************************************/
#if defined __CCS_RUN__
#include <stdio.h>
#include <math.h>
#include <string.h>
#endif

#define UTILITY_SUPPORT_C_

#include "type.h"
#include "functions.h"
#include "constants.h"
#include "global_data.h"

/*-----------------------------------------*/
//  File Scope Data                        //
/*-----------------------------------------*/

#ifdef __CCS_RUN__
// Results File Pointers
FILE *fp1 = NULL;
FILE *fp2 = NULL;

// Results File Name
const CHAR ResultsFileName[16] = "ResultsFile.txt";
const CHAR DrawFileName[18]    = "DrawShapeFile.txt";
#endif



/************************************************************/
//
//  <FunctionName: u32ConvertToAsciiString>
//
//  <Full Name: Convert U32 Value to ASCII String>
//
//  <Description: This function converts an input U32 value
//   into an output ASCII character string. The character
//   string is output left-justified with a NULL placed after
//   the final character.>
//
/************************************************************/
void u32ConvertToAsciiString(
    U32 u32InputDataValue,            // Input: U32 Value to convert to ASCII Characters
    CHAR *OutputAsciiString)          // Output: ASCII Character Array for Input U32 Value
/************************************************************/
{
    U8   u8CharTotal;
    U8   u8CharBuffer;
    S16  i;
    U32  u32NumberMangler;

    // Initialize Output ASCII Character Array to NULL
    for (i = 0; i < U32_MAX_DISPLAY_DIGITS; i++){
        OutputAsciiString[i] = ASCII_SPACE;
    }

    // Initialize Character Buffer
    u8CharBuffer = STRING_NULL;

    // Determine Number of Characters for output string
    u32NumberMangler = u32InputDataValue;
    for (u8CharTotal = 0; u32NumberMangler != 0; u8CharTotal++) {
        u32NumberMangler /= 10;
    }

    // Set the Output ASCII Character Array for Input Integer
    u32NumberMangler = u32InputDataValue;
    for (i = u8CharTotal - 1; i >= 0; i--) {
        u8CharBuffer = (U8) ((u32NumberMangler % 10) + ASCII_ZERO);
        OutputAsciiString[i] = (CHAR) u8CharBuffer;  // Set the least significant digit in the highest index (right justified)
        u32NumberMangler /= 10;
        u8CharBuffer = STRING_NULL;
    }

    // Set NULL character to last element of output string
    OutputAsciiString[u8CharTotal] = STRING_NULL;
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: F32ConvertToAsciiString>
//
//  <Full Name: Convert F32 Value to ASCII String>
//
//  <Description: This function converts an input F32 value
//   into an output ASCII character string. The F32 value is
//   is rounded to the nearest 10^-4 digit and converted into
//   a string with 4 decimal places. The character string is
//   output left-justified with a NULL placed after the 4th
//   decimal place character.>
//
/************************************************************/
void f32ConvertToAsciiString(
    F32 f32InputDataValue,            // Input: F32 Value to convert to ASCII Characters
    CHAR *OutputAsciiString)          // Output: ASCII Character Array for Input F32 Value
/************************************************************/
{
    U8  u8CharBuffer;
    U8  u8CharTotal;
    U16 i;
    S16 j;
    F32 f32InDataBuffer;
    F32 f32DecDataBuffer;
    F32 f32CharCntBuffer;
    F32 f32DecimalDigits;
    U32 u32NonDecDataBuffer;
    U32 u32DecDataBuffer;



    // Initialize Character Buffer
    u8CharBuffer = STRING_NULL;

    // Round input data
    f32InDataBuffer = f32InputDataValue + 0.00005;

    // Find total character count of output array, add
    // extra space for zero character before decimal point
    // if rounded input data is less than 1 and greater
    // than -1
    f32CharCntBuffer = f32InDataBuffer;
    for (u8CharTotal = 0; f32CharCntBuffer >= 1.0; u8CharTotal++) {
        f32CharCntBuffer /= 10.0;
    }
    if ( ( f32InDataBuffer < 1 ) && ( f32InDataBuffer > -1 ) ) {
        u8CharTotal +=1;
    }
    else {
    }
    u8CharTotal += F32_MAX_DISPLAY_DEC_DIGITS + 1;

    // Initialize output array
    for (i = 0; i < u8CharTotal; i++){
            OutputAsciiString[i] = ASCII_SPACE;
    }

    // Extract non-decimal digits from input value
    u32NonDecDataBuffer = (U32)f32InDataBuffer;

    // Extract decimal digits from input value
    f32DecDataBuffer = f32InDataBuffer - (F32)u32NonDecDataBuffer;
    f32DecimalDigits = f32DecDataBuffer * 10000.0;
    u32DecDataBuffer = (U32)f32DecimalDigits;

    // Set decimal digits to output string
    for (i = u8CharTotal - 1; i >= (u8CharTotal - F32_MAX_DISPLAY_DEC_DIGITS); i--) {
        u8CharBuffer = (U8)((u32DecDataBuffer % 10) + ASCII_ZERO);
        OutputAsciiString[i] = (CHAR)u8CharBuffer;
        u32DecDataBuffer /= 10;
        u8CharBuffer = STRING_NULL;
    }

    // Set decimal point to output string
    OutputAsciiString[i] = ASCII_PERIOD;
    i--;

    // Set non-decimal digits to output string
    for (j = i; j > -1; j--) {
        u8CharBuffer = (U8)((u32NonDecDataBuffer % 10) + ASCII_ZERO);
        OutputAsciiString[j] = (CHAR)u8CharBuffer;
        u32NonDecDataBuffer /= 10;
        u8CharBuffer = STRING_NULL;
    }

    // Set NULL character to last element of output string
    OutputAsciiString[u8CharTotal] = STRING_NULL;
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: f64ConvertToAsciiString>
//
//  <Full Name: Convert F64 Value to ASCII String>
//
//  <Description: This function converts an input F64 value
//   into an output ASCII character string. The F64 value is
//   is rounded to the nearest 10^-7 digit and converted into
//   a string with 7 decimal places. The character string is
//   output left-justified with a NULL placed after the 7th
//   decimal place character.>
//
/************************************************************/
void f64ConvertToAsciiString(
    F64 f64InputDataValue,            // Input: F64 Value to convert to ASCII Characters
    CHAR *OutputAsciiString)          // Output: ASCII Character Array for Input F64 Value
/************************************************************/
{
    U8  u8CharBuffer;
    U8  u8CharTotal;
    U8  u8NonDecCharCnt;
    S16 i;
    S16 j;
    F64 f64DecimalDigits;
    F64 f64DecDataBuffer;
    F64 f64CharCntBuffer;
    F64 f64NonDecBuffer1;
    F64 f64NonDecBuffer2;
    U32 u32DecDataBuffer;
    U32 u32DecNumberMangler;
    U32 u32NonDecBuffer1;
    U32 u32NonDecBuffer2;
    U32 u32NonDecCharCntBuffer;


    // Initialize Character Buffer
    u8CharBuffer = STRING_NULL;

    f64DecDataBuffer = f64InputDataValue + 0.00000005;

    // Find total character count of output array, add
    // extra space for zero character before decimal point
    // if rounded input data is less than 1 and greater
    // than -1.
    f64CharCntBuffer = f64DecDataBuffer;
    for (u8CharTotal = 0; f64CharCntBuffer >= 1.0; u8CharTotal++) {
        f64CharCntBuffer /= 10.0;
    }
    if ( ( f64DecDataBuffer < 1 ) && ( f64DecDataBuffer > -1 ) ) {
        u8CharTotal +=1;
    }
    else {
    }
    u8CharTotal += F64_MAX_DISPLAY_DEC_DIGITS + 1;

    for (i = 0; i < u8CharTotal; i++){
            OutputAsciiString[i] = ASCII_SPACE;
    }

    // Retrieve Decimal Characters
    if ( f64DecDataBuffer > (F64)U32_MAX_VALUE ) {
        f64NonDecBuffer1 = f64DecDataBuffer / 100000000.0;
        u32NonDecBuffer1 = (U32)f64NonDecBuffer1;
        f64NonDecBuffer2 = f64DecDataBuffer - ((F64)u32NonDecBuffer1 * 100000000.0);
        u32NonDecBuffer2 = (U32)f64NonDecBuffer2;

        u32NonDecCharCntBuffer = u32NonDecBuffer1;
        for (u8NonDecCharCnt = 0; u32NonDecCharCntBuffer != 0; u8NonDecCharCnt++) {
            u32NonDecCharCntBuffer /= 10;
        }

        while (f64DecDataBuffer > (F64)U32_MAX_VALUE) {
            f64DecDataBuffer = f64DecDataBuffer - (F64)U32_MAX_VALUE;
        }
        u32DecDataBuffer = (U32)f64DecDataBuffer;
        f64DecDataBuffer = f64DecDataBuffer - (F64)u32DecDataBuffer;
        f64DecimalDigits = f64DecDataBuffer * 10000000.0;
        u32DecNumberMangler = (U32)f64DecimalDigits;

        for (i = u8CharTotal - 1; i >= (u8CharTotal - F64_MAX_DISPLAY_DEC_DIGITS); i--) {
            u8CharBuffer = (U8)((u32DecNumberMangler % 10) + ASCII_ZERO);
            OutputAsciiString[i] = (CHAR)u8CharBuffer;    // Set the least significant digit in the highest index
            u32DecNumberMangler /= 10;
            u8CharBuffer = STRING_NULL;
        }

        OutputAsciiString[i] = ASCII_PERIOD;
        i--;

        // Set first six non-decimal digits to output string
        for (j = i; j >= u8NonDecCharCnt; j--) {
            u8CharBuffer = (U8)((u32NonDecBuffer2 % 10) + ASCII_ZERO);
            OutputAsciiString[j] = (CHAR)u8CharBuffer;    // Set the least significant digit in the highest index
            u32NonDecBuffer1 /= 10;
            u8CharBuffer = 0x00;
        }

        // Set remaining non-decimal digits to output string
        for (i = j; i > -1; i--) {
            u8CharBuffer = (U8)((u32NonDecBuffer1 % 10) + ASCII_ZERO);
            OutputAsciiString[i] = (CHAR)u8CharBuffer;    // Set the least significant digit in the highest index
            u32NonDecBuffer2 /= 10;
            u8CharBuffer = STRING_NULL;
        }

        OutputAsciiString[u8CharTotal] = STRING_NULL;
    }
    else {
        // Extract non-decimal digits from input value
        u32NonDecBuffer1 = (U32)f64DecDataBuffer;

        // Extract decimal digits from input value
        f64DecDataBuffer = f64DecDataBuffer - (F64)u32NonDecBuffer1;
        f64DecimalDigits = f64DecDataBuffer * 10000000.0;
        u32DecNumberMangler = (U32)f64DecimalDigits;

        for (i = u8CharTotal - 1; i >= (u8CharTotal - F64_MAX_DISPLAY_DEC_DIGITS); i--) {
            u8CharBuffer = (U8)((u32DecNumberMangler % 10) + ASCII_ZERO);
            OutputAsciiString[i] = (CHAR)u8CharBuffer;    // Set the least significant digit in the highest index
            u32DecNumberMangler /= 10;
            u8CharBuffer = STRING_NULL;
        }

        OutputAsciiString[i] = ASCII_PERIOD;
        i--;

        for (j = i; j > -1; j--) {
            u8CharBuffer = (U8)((u32NonDecBuffer1 % 10) + ASCII_ZERO);
            OutputAsciiString[j] = (CHAR)u8CharBuffer;    // Set the least significant digit in the highest index
            u32NonDecBuffer1 /= 10;
            u8CharBuffer = STRING_NULL;
        }

        OutputAsciiString[u8CharTotal] = STRING_NULL;
    }
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: ConvertAdrsValToAsciiString>
//
//  <Full Name: Convert 32 bit Address Value to ASCII String>
//
//  <Description: This function converts an input value into
//   hexadecimal ASCII characters with a leading "0x". The
//   input value shows all 32 bits of the input value and the
//   characters are placed in the input/output string starting
//   at the input Start Index parameter.>
//
/************************************************************/
void ConvertAdrsValToAsciiString(
    U32 u32InputAdrsValue,            // Input: U32 Value to convert to ASCII Characters
    CHAR *OutputAsciiString,          // I/O: ASCII Character Array for Input U32 Value
    U8 StartIndex)                    // Input: Index to Start Writing Hex Address Value
/************************************************************/
{
    U8  u8CharBuffer;
    U8  u8PlaceHolder;
    U16 i;

    u8PlaceHolder = 28;
    for (i = StartIndex; i < (StartIndex+8); i++) {
        u8CharBuffer = ((u32InputAdrsValue >> u8PlaceHolder) & 0x0000000F);
        if ( u8CharBuffer > 9 ) {
            OutputAsciiString[i] = (CHAR) (u8CharBuffer + 0x37);
        }
        else {
            OutputAsciiString[i] = (CHAR) (u8CharBuffer + ASCII_ZERO);
        }
        u8PlaceHolder -= 4;
    }
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: SetErrorDataToMemory>
//
//  <Full Name: Save Error Data to Error Area>
//
//  <Description: This function sets error data to memory.
//   Retrieve error data is saved in a separate area than
//   calculation error data.>
//
/************************************************************/
void SetErrorDataToMemory(
    U32 *u32ErrorArray,               // Input: Error Array to set to Error Area
    U16 u16ErrorArrayLength)          // Input: Length of Error Array
/************************************************************/
{
    U16 i;
    U16 AddressOffset;
    volatile U32 *ErrorDataPointer;

    // If the input
    if ( GenumErrorType == ENUM_RTRV_ERROR ) {
        AddressOffset = RtrvErrCurrentFrameCounter * ERROR_RECORD_RSVRD_SPACE;
        ErrorDataPointer = (U32 *)(RTRV_ERROR_DATA_HD_ADRS + AddressOffset);
    }
    else if ( GenumErrorType == ENUM_CALC_ERROR ) {
        AddressOffset = CalcErrCurrentFrameCounter * ERROR_RECORD_RSVRD_SPACE;
        ErrorDataPointer = (U32 *) (CALC_ERROR_DATA_HD_ADRS + AddressOffset);
    }

    for (i = 0; i < u16ErrorArrayLength; i++) {
        ErrorDataPointer[i] = u32ErrorArray[i];
    }

    // Reset GenumErrorType variable to Miscellaneous
    GenumErrorType = ENUM_MISC_ERROR;
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: SetRetrieveData>
//
//  <Full Name: Set Retrieve Data>
//
//  <Description: This function populates the retrieve data
//   area with pre-defined words for the current frame if
//   called during periodic processing.>
//
/************************************************************/
void SetRetrieveData(void)
/************************************************************/
{
    volatile U32 *SetDataWords;

    // Set Shape Data Words in Retrieve Data Area
    // according to current Frame Number
    SetDataWords = (U32*)RTRV_DATA_HD_ADRS;

    switch (u16FrameNumber){
        case 1:
            SetDataWords[0] = 0x80000008;
            SetDataWords[1] = 0x80002918;
            SetDataWords[2] = 0x80010A2A;
            SetDataWords[3] = 0x7000473A;
            SetDataWords[4] = 0x80009F4A;
            break;
        case 2:
            SetDataWords[0] = 0x80005308;
            SetDataWords[1] = 0x80002918;
            SetDataWords[2] = 0x80010A2A;
            SetDataWords[3] = 0x8000473B;
            SetDataWords[4] = 0x80009F4A;
            break;
        case 3:
            SetDataWords[0] = 0x80001418;
            SetDataWords[1] = 0x80002918;
            SetDataWords[2] = 0x80F0FF2A;
            SetDataWords[3] = 0x8000473A;
            SetDataWords[4] = 0x80009F4A;
            break;
        case 4:
            SetDataWords[0] = 0x80005308;
            SetDataWords[1] = 0x80002918;
            SetDataWords[2] = 0x80010A2A;
            SetDataWords[3] = 0x8000473A;
            SetDataWords[4] = 0x80009F4A;
            break;
        case 5:
            SetDataWords[0] = 0x80005308;
            SetDataWords[1] = 0x80002918;
            SetDataWords[2] = 0x8000012A;
            SetDataWords[3] = 0x8000033A;
            SetDataWords[4] = 0x80009F4A;
            break;
        case 6:
            SetDataWords[0] = 0x80005308;
            SetDataWords[1] = 0x80002918;
            SetDataWords[2] = 0x80010A2A;
            SetDataWords[3] = 0x80FFFF3A;
            SetDataWords[4] = 0x80009F4A;
            break;
        case 7:
            SetDataWords[0] = 0x80005308;
            SetDataWords[1] = 0x80002918;
            SetDataWords[2] = 0x80010A2A;
            SetDataWords[3] = 0x8000473A;
            SetDataWords[4] = 0x80009F5A;
            break;
        case 8:
            SetDataWords[0] = 0x80005308;
            SetDataWords[1] = 0x80002918;
            SetDataWords[2] = 0x80010A2A;
            SetDataWords[3] = 0x8000473A;
            SetDataWords[4] = 0x8000004A;
            break;
        case 9:
            SetDataWords[0] = 0x80000008;
            SetDataWords[1] = 0x80000018;
            SetDataWords[2] = 0x8000002A;
            SetDataWords[3] = 0x8000003A;
            SetDataWords[4] = 0x8000004A;
            break;
        case 10:
            SetDataWords[0] = 0x80000000;
            SetDataWords[1] = 0x80000000;
            SetDataWords[2] = 0x80000000;
            SetDataWords[3] = 0x80000000;
            SetDataWords[4] = 0x80000000;
            break;
        case 11:
            SetDataWords[0] = 0x80000008;
            SetDataWords[1] = 0x80000018;
            SetDataWords[2] = 0x8000002A;
            SetDataWords[3] = 0x8000003A;
            SetDataWords[4] = 0x8000004A;
            break;
        case 12:
            SetDataWords[0] = 0x80001008;
            SetDataWords[1] = 0x80000218;
            SetDataWords[2] = 0x8000132A;
            SetDataWords[3] = 0x8803613A;
            SetDataWords[4] = 0x8990124A;
            break;
        case 13:
            SetDataWords[0] = 0x80000008;
            SetDataWords[1] = 0x80000018;
            SetDataWords[2] = 0x8000002A;
            SetDataWords[3] = 0x8000003A;
            SetDataWords[4] = 0x8000004A;
            break;
        case 14:
            SetDataWords[0] = 0x8005AB08;
            SetDataWords[1] = 0x80007218;
            SetDataWords[2] = 0x8000832A;
            SetDataWords[3] = 0x8126FF3A;
            SetDataWords[4] = 0x8056124A;
            break;
        case 15:
            SetDataWords[0] = 0x80235108;
            SetDataWords[1] = 0x80022218;
            SetDataWords[2] = 0x8002342A;
            SetDataWords[3] = 0x80124F3A;
            SetDataWords[4] = 0x80008F4A;
            break;
        case 16:
            SetDataWords[0] = 0x80021008;
            SetDataWords[1] = 0x80030218;
            SetDataWords[2] = 0x8099132A;
            SetDataWords[3] = 0x80010F3A;
            SetDataWords[4] = 0x8060124A;
            break;
        case 17:
            SetDataWords[0] = 0x80041008;
            SetDataWords[1] = 0x80020208;
            SetDataWords[2] = 0x8000132A;
            SetDataWords[3] = 0x80023F3A;
            SetDataWords[4] = 0x8000524A;
            break;
        case 18:
            SetDataWords[0] = 0x80138808;  // Max Value
            SetDataWords[1] = 0x80138818;  // Max Value
            SetDataWords[2] = 0x8111702A;  // Max Value
            SetDataWords[3] = 0x8111703A;  // Max Value
            SetDataWords[4] = 0x8111704A;  // Max Value
            break;
        case 19:
            SetDataWords[0] = 0x80331008;
            SetDataWords[1] = 0x80022218;
            SetDataWords[2] = 0x8005332A;
            SetDataWords[3] = 0x80130F3A;
            SetDataWords[4] = 0x8022624A;
            break;
        case 20:
            SetDataWords[0] = 0x80000008;  // No Data for Leg 1
            SetDataWords[1] = 0x70000218;  // Parity Failure for Leg 2 Word
            SetDataWords[2] = 0x8FFFF42A;  // Very High Data Value for Length Word
            SetDataWords[3] = 0x8000043B;  // Undefined Label Type Word (no Height Word)
            SetDataWords[4] = 0x8000047A;  // Undefined Subtype for Cube Label Word
            break;
        case 21:
            SetDataWords[0] = 0x80000008;
            SetDataWords[1] = 0x80000018;
            SetDataWords[2] = 0x8000002A;
            SetDataWords[3] = 0x8000003A;
            SetDataWords[4] = 0x8000004A;
            break;
        case 22:
            SetDataWords[0] = 0x80001008;
            SetDataWords[1] = 0x80000218;
            SetDataWords[2] = 0x8000132A;
            SetDataWords[3] = 0x8803613A;
            SetDataWords[4] = 0x8990124A;
            break;
        case 23:
            SetDataWords[0] = 0x80000008;
            SetDataWords[1] = 0x80000018;
            SetDataWords[2] = 0x8000002A;
            SetDataWords[3] = 0x8000003A;
            SetDataWords[4] = 0x8000004A;
            break;
        case 24:
            SetDataWords[0] = 0x8005AB08;
            SetDataWords[1] = 0x80007218;
            SetDataWords[2] = 0x8000832A;
            SetDataWords[3] = 0x8126FF3A;
            SetDataWords[4] = 0x8056124A;
            break;
        case 25:
            SetDataWords[0] = 0x80235108;
            SetDataWords[1] = 0x80022218;
            SetDataWords[2] = 0x8002342A;
            SetDataWords[3] = 0x80124F3A;
            SetDataWords[4] = 0x80008F4A;
            break;
        case 26:
            SetDataWords[0] = 0x80021008;
            SetDataWords[1] = 0x80030218;
            SetDataWords[2] = 0x8099132A;
            SetDataWords[3] = 0x80010F3A;
            SetDataWords[4] = 0x8060124A;
            break;
        case 27:
            SetDataWords[0] = 0x80041008;
            SetDataWords[1] = 0x80020208;
            SetDataWords[2] = 0x8000132A;
            SetDataWords[3] = 0x80023F3A;
            SetDataWords[4] = 0x8000524A;
            break;
        case 28:
            SetDataWords[0] = 0x80138808;  // Max Value
            SetDataWords[1] = 0x80138818;  // Max Value
            SetDataWords[2] = 0x8111702A;  // Max Value
            SetDataWords[3] = 0x8111703A;  // Max Value
            SetDataWords[4] = 0x8111704A;  // Max Value
            break;
        case 29:
            SetDataWords[0] = 0x80331008;
            SetDataWords[1] = 0x80022218;
            SetDataWords[2] = 0x8005332A;
            SetDataWords[3] = 0x80130F3A;
            SetDataWords[4] = 0x8022624A;
            break;
        case 30:
            SetDataWords[0] = 0x80000008;  // No Data for Leg 1
            SetDataWords[1] = 0x70000218;  // Parity Failure for Leg 2 Word
            SetDataWords[2] = 0x8FFFF42A;  // Very High Data Value for Length Word
            SetDataWords[3] = 0x8000043B;  // Undefined Label Type Word (no Height Word)
            SetDataWords[4] = 0x8000047A;  // Undefined Subtype for Cube Label Word
            break;
        default:
            SetDataWords[0] = 0xFFFFFFFF;
            SetDataWords[1] = 0xFFFFFFFF;
            SetDataWords[2] = 0xFFFFFFFF;
            SetDataWords[3] = 0xFFFFFFFF;
            SetDataWords[4] = 0xFFFFFFFF;
            break;
    }
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: ResultsFilesIni>
//
//  <Full Name: Initialize Results Files>
//
//  <Description: This function initializes both the results
//   and draw files written to during program processing.
//   A message indicating whether or not each file is
//   successfully initialized is written to the CCS Stdout
//   window.>
//
/************************************************************/
void ResultsFilesInit(void)
/************************************************************/
{
#ifdef __CCS_RUN__
    fp1 = fopen( ResultsFileName, "w" );
    setvbuf( fp1, NULL, _IONBF, 0 );

    if ( fp1 == NULL ) {
        fprintf( stderr, "Cannot Open Results File\n" );
    }
    else {
        fprintf( stderr, "Results File Opened\n" );
    }

    fp2 = fopen( DrawFileName, "w" );
    setvbuf( fp2, NULL, _IONBF, 0 );

    if ( fp2 == NULL ) {
        fprintf( stderr, "Cannot Open Draw File\n" );
    }
    else {
        fprintf( stderr, "Draw File Opened\n" );
    }
#endif
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: WriteFrameToStdout>
//
//  <Full Name: Writes Current Frame to Stdout>
//
//  <Description: This function is used to indicate in the CCS
//   Stdout window the current frame being processed by the
//   program.>
//
/************************************************************/
void WriteFrameToStdout(void)
/************************************************************/
{
#ifdef __CCS_RUN__
    const CHAR CurrentFramePreamble[17] = "Processing Frame ";
    CHAR CurrentFramePrint[20];
    U16 i;

    for (i = 0; i < 17; i++) {
        CurrentFramePrint[i] = CurrentFramePreamble[i];
    }
    if (u16FrameNumber < 10) {
        CurrentFramePrint[17] = ASCII_SPACE;
        CurrentFramePrint[18] = (CHAR)(u16FrameNumber + ASCII_ZERO);
    }
    else {
        CurrentFramePrint[17] = (CHAR)((u16FrameNumber / 10) + ASCII_ZERO);
        CurrentFramePrint[18] = (CHAR)((u16FrameNumber % 10) + ASCII_ZERO);
    }
    CurrentFramePrint[19] = STRING_NULL;

    fprintf( stderr, CurrentFramePrint );
    fprintf( stderr, "\n" );
#endif
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: WriteProcessingResultsStderr>
//
//  <Full Name: Writes Processing Current Results to Stdout>
//
//  <Description: This function is used to indicate in the CCS
//   Stdout window the program is processing final results
//   after periodic processing is complete.>
//
/************************************************************/
void WriteProcessingResultsStdout(void)
/************************************************************/
{
#ifdef __CCS_RUN__
    const CHAR ProcessingResults[25] = "Processing Final Results";

    fprintf( stderr, ProcessingResults );
    fprintf( stderr, "\n" );
#endif
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: CloseResultsFile>
//
//  <Full Name: Close Results File>
//
//  <Description: This function closes both the results
//   and draw files written to during program processing.
//   A message indicating whether or not each file is
//   successfully initialized is written to the CCS Stdout
//   window.>
//
/************************************************************/
void CloseResultsFiles(void)
/************************************************************/
{
#ifdef __CCS_RUN__
    fclose( fp1 );
    fprintf( stderr, "Results File Closed\n" );

    fclose( fp2 );
    fprintf( stderr, "Draw File Closed\n" );
    fprintf( stderr, "Program Processing Complete\n" );
#endif
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: PrintToResultsFile>
//
//  <Full Name: Print String to Results File>
//
//  <Description: This function prints the input string to
//   the results file. Before printing the string, it performs
//   the number of carriage returns indicated by the input
//   number of carriage returns.>
//
/************************************************************/
void PrintToResultsFile(
    U8 CarriageReturnNumber,    // Input: Carriage Return From Last Statement
    CHAR *StringToPrint)        // Input: String to Print
/************************************************************/
{
#ifdef __CCS_RUN__
    U16 i;

    for (i = 0; i < CarriageReturnNumber; i++) {
        fprintf( fp1, "\n" );
    }

    fprintf( fp1, StringToPrint );
#endif
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: PrintToDrawFile>
//
//  <Full Name: Print String to Draw File>
//
//  <Description: This function prints the input string to
//   the results file. Before printing the string, it performs
//   the number of carriage returns indicated by the input
//   number of carriage returns.>
//
/************************************************************/
void PrintToDrawFile(
    U8 CarriageReturnNumber,    // Input: Carriage Return From Last Statement
    CHAR *StringToPrint)        // Input: String to Print
/************************************************************/
{
#ifdef __CCS_RUN__
    U16 i;

    for (i = 0; i < CarriageReturnNumber; i++) {
        fprintf( fp2, "\n" );
    }

    fprintf( fp2, StringToPrint );
#endif
}
/************************************************************/

