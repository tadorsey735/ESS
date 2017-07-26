/************************************************************************/
//
//  <FileName: global_data.h>
//
//  <FileDesc: ESS Global Data Definition File>
//
//  <Version: 1.1.4>
//
/************************************************************************/
#if defined __CCS_RUN__
#include <stdio.h>
#include <string.h>
#endif

#include "constants.h"

#if !defined(GLOBAL_DATA_H_)
#define GLOBAL_DATA_H_

/*======================================================================*/
/* Shape Data Structures                                                */
/*======================================================================*/

typedef struct CUBE_DATA_STRUCT {
    U32   u32RtrvdCubeLength;                  // Current Frame Cube Length
    U32   u32RtrvdCubeHeight;                  // Current Frame Cube Height
    U32   u32RtrvdCubeWidth;                   // Current Frame Cube Width
    U32   u32RtrvdCubeLengthLastFrame;         // Last Frame Cube Length
    U32   u32RtrvdCubeHeightLastFrame;         // Last Frame Cube Height
    U32   u32RtrvdCubeWidthLastFrame;          // Last Frame Cube Width
    U32   u32CalculatedCubeVolume;             // Calculated Cube Volume
} CUBE_DATA_STRUCT;

typedef struct TRIANGLE_DATA_STRUCT {
    U32   u32RtrvdTriLeg1;                     // Current Frame Right Triangle Leg 1
    U32   u32RtrvdTriLeg2;                     // Current Frame Right Triangle Leg 2
    U32   u32RtrvdTriLeg1LastFrame;            // Last Frame Right Triangle Leg 1
    U32   u32RtrvdTriLeg2LastFrame;            // Last Frame Right Triangle Leg 2
    F32   f32CalculatedTriArea;                // Calculated Right Triangle Area
    F64   f64CalculatedTriHypo;                // Calculated Right Triangle Hypotenuse
} TRIANGLE_DATA_STRUCT;

typedef enum tag_ENUM_ERROR_TYPE{
        ENUM_RTRV_ERROR,
        ENUM_CALC_ERROR,
        ENUM_MISC_ERROR
} ENUM_ERROR_TYPE;


#if defined(MAIN_FILE_C_)

U16  u16FrameNumber;

CUBE_DATA_STRUCT CubeDataStructure;
TRIANGLE_DATA_STRUCT TriangleDataStructure;

// Error Type for Error Snapshot
ENUM_ERROR_TYPE GenumErrorType = ENUM_MISC_ERROR;

// Current Frame Error Arrays
U32 RtrvErrCurrentFrame[MAX_FRAME_ERR][RTRV_ERR_RCD_LENGTH]; // Allow up to ten retrieve errors to be reported per frame
U32 CalcErrCurrentFrame[MAX_FRAME_ERR][CALC_ERR_RCD_LENGTH]; // Allow up to ten calculation errors to be reported per frame

//Current Frame Error Counters
U8  RtrvProcessResult;
U16 RtrvErrCurrentFrameCounter;
U16 CalcErrCurrentFrameCounter;

// All Data Successfully Retrieved Flag
BOOL AllDataRetrievedFlag;

// Current Frame Retrieve Error Record and Retrieved Data Set Arrays
/*                                               TRI_LEG1,  TRI_LEG2,  CUBE_LNG,  CUBE_HGT,   CUBE_WDT      */
BOOL RtrvDataErrorArray[RTRV_DATA_SIZE]       = {     0,        0,         0,          0,          0      } ;   // Current Frame Retrieve Error Array
U8   ShapeDataSetArray[RTRV_DATA_SIZE]        = {     0,        0,         0,          0,          0      } ;   // Current Frame Data Set Array
BOOL RtrvWordParityErrorArray[RTRV_DATA_SIZE] = {     0,        0,         0,          0,          0      } ;   // Current Frame Retrieved Word Parity Error
BOOL ShapeDataZeroArray[RTRV_DATA_SIZE]       = {     0,        0,         0,          0,          0      } ;   // Current Frame Retrieved Data Zero Array (Use Previous Value)
BOOL ShapeDataLimitedArray[RTRV_DATA_SIZE]    = {     0,        0,         0,          0,          0      } ;   // Current Frame Retrieved Data Limited to Maximum Value
BOOL ShapeDataDefaultArray[RTRV_DATA_SIZE]    = {     0,        0,         0,          0,          0      } ;   // Data Set to Default Value
BOOL ShapeDataPrevFrameArray[RTRV_DATA_SIZE]  = {     0,        0,         0,          0,          0      } ;   // Data Set to Previous Frame Value

#else

extern U16  u16FrameNumber;

extern CUBE_DATA_STRUCT CubeDataStructure;
extern TRIANGLE_DATA_STRUCT TriangleDataStructure;

// Error Type for Error Snapshot
extern ENUM_ERROR_TYPE GenumErrorType;

// Current Frame Error Arrays
extern U32 RtrvErrCurrentFrame[MAX_FRAME_ERR][RTRV_ERR_RCD_LENGTH]; // Allow up to ten retrieve errors to be reported per frame
extern U32 CalcErrCurrentFrame[MAX_FRAME_ERR][CALC_ERR_RCD_LENGTH]; // Allow up to ten calculation errors to be reported per frame

//Current Frame Error Counters
extern U8  RtrvProcessResult;
extern U16 RtrvErrCurrentFrameCounter;
extern U16 CalcErrCurrentFrameCounter;

// Current Frame Retrieve Data Flags
extern BOOL AllDataRetrievedFlag;

// Current Frame Retrieve Error Record and Retrieved Data Set Arrays
extern BOOL RtrvDataErrorArray[RTRV_DATA_SIZE];       // Current Frame Retrieve Error Array
extern U8   ShapeDataSetArray[RTRV_DATA_SIZE];        // Current Frame Data Set Array
extern BOOL RtrvWordParityErrorArray[RTRV_DATA_SIZE]; // Current Frame Retrieved Word Parity Error
extern BOOL ShapeDataZeroArray[RTRV_DATA_SIZE];       // Current Frame Retrieved Data Zero Array (Use Previous Value)
extern BOOL ShapeDataLimitedArray[RTRV_DATA_SIZE];    // Current Frame Retrieved Data Limited
extern BOOL ShapeDataDefaultArray[RTRV_DATA_SIZE];    // Data Set to Default Value
extern BOOL ShapeDataPrevFrameArray[RTRV_DATA_SIZE];  // Data Set to Previous Frame Value

#endif

#if defined(DRAW_FILE_C_)

//#pragma DATA_SECTION(u16DrawTriArea, "DrawTriArea")
U16  u16DrawTriArea[DRAW_ROW_SIZE][DRAW_COL_SIZE];

//#pragma DATA_SECTION(u16DrawCubeArea, "DrawCubeArea")
U16 u16DrawCubeArea[DRAW_ROW_SIZE][DRAW_COL_SIZE];

#else

extern U16 u16DrawTriArea[DRAW_ROW_SIZE][DRAW_COL_SIZE];
extern U16 u16DrawCubeArea[DRAW_ROW_SIZE][DRAW_COL_SIZE];

#endif

#endif

/************************************************************************/

