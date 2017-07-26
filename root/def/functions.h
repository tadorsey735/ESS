/************************************************************************/
//
//  <FileName: functions.h>
//
//  <FileDesc: ESS Function Definitions File>
//
//  <Version: 1.1.4>
//
/************************************************************************/
#if defined __CCS_RUN__
#include <stdio.h>
#include <string.h>
#endif

#include "type.h"
#include "global_data.h"

#if !defined(FUNCTIONS_H_)
#define FUNCTIONS_H_



/*======================================================================*/
/* Global Functions                                                     */
/*======================================================================*/

extern far void main();

void FrameProcess();

void DataInit();

void RtrvDataMain();

void CalcDataMain();

void ResultsDataMain();


/*======================================================================*/
/*  Retrieve Functions                                                  */
/*======================================================================*/

BOOL RtrvDataProcess(
    U32);                       // Input Retrieved Word

void RtrvErrRcdFunc(
    U8,                         // Input: Retrieve Error Code
    U32);                       // Input: Retrieved Shape Word


/*======================================================================*/
/*  Calculation Functions                                               */
/*======================================================================*/

U32 SetShapeData(
     U8,                      // Input: Shape Data SubType
     U32);                    // Input: Shape Data Value

U32 CalcValueLimit(
    U8,                       // Input: Shape Dimension
    U32);                     // Input: Shape Value

U32 ShapeDataAboveMaxCheck(
    U32,                      // Input: Shape Data Value
    U32);                     // Input: Maximum Shape Data Value

U32 ShapeDataBelowMinCheck(
    U32,                      // Input: Shape Data Value
    U32);                     // Input: Minimum Shape Data Value

F32 CalcTriangleArea(
    U32,                      // Input: Triangle Leg 1
    U32);                     // Input: Triangle Leg 2

F64 CalcTriangleHypo(
    U32,                      // Input: Triangle Leg 1
    U32);                     // Input: Triangle Leg 2

U32 CalcCubeVol(
    U32,                      // Input: Cube Length
    U32,                      // Input: Cube Height
    U32);                     // Input: Cube Width

void SetCalcDataToMemory(void);

void CalcErrRcdFunc(
    U8,                       // Input: Calculation Error Code
    U32);                     // Input: Shape Data


/*======================================================================*/
/*  Results Functions                                                   */
/*======================================================================*/

void WriteResultsFileHeader(void);

void WriteProgramDetails(void);

void WriteCurrentFrameHeader(void);

void WriteRetrievedDataSummary(void);

void WriteRetrieveError(void);

void WriteTriangleResults(void);

void WriteCubeResults(void);

/*======================================================================*/
/*  Utility Functions                                                   */
/*======================================================================*/

void u32ConvertToAsciiString(
    U32,            // Input: U32 Value to convert to ASCII Characters
    CHAR *);        // Output: ASCII Character Array for Input U32 Value

void f32ConvertToAsciiString(
    F32,            // Input: F32 Value to convert to ASCII Characters
    CHAR *);        // Output: ASCII Character Array for Input F32 Value

void f64ConvertToAsciiString(
    F64,            // Input: F64 Value to convert to ASCII Characters
    CHAR *);        // Output: ASCII Character Array for Input F64 Value

void ConvertAdrsValToAsciiString(
    U32,                  // Input: U32 Value to convert to ASCII Characters
    CHAR *,               // I/O: ASCII Character Array for Input U32 Value
    U8 StartIndex);       // Index to Start Writing Hex Address Value

void SetErrorDataToMemory(
    U32 *,          // Input: Error Array to set to Error Area
    U16);           // Input: Length of Error Array

void SetRetrieveData(void);

void ResultsFilesInit(void);

void WriteFrameToStdout(void);

void WriteProcessingResultsStdout(void);

void CloseResultsFiles(void);

void PrintToResultsFile(
    U8,                   // Input: Number of Carriage Returns
    CHAR *);              // Input: String to Print

void PrintToDrawFile(
    U8,                   // Input: Number of Carriage Returns
    CHAR *);              // Input: String to Print


/*======================================================================*/
/*  Draw Functions                                                      */
/*======================================================================*/

void InitDraw(
    U16,
    U16,
    U16,
    U16,
    U16);

void DrawTriangle(void);

void DrawCube(void);

void DrawLine (
    S16,
    S16,
    S16,
    S16,
    U16,
    U16);

#endif

/************************************************************************/

