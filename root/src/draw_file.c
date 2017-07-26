/************************************************************************/
//
//  <FileName: draw_file.c>
//
//  <FileDesc: ESS Draw File>
//
//  <Version: 1.1.4>
//
/************************************************************************/
#if defined __CCS_RUN__
#include <stdio.h>
#include <string.h>
#endif

#define DRAW_FILE_C_

#include "type.h"
#include "functions.h"
#include "constants.h"
#include "global_data.h"
#include "result_strings.h"



/************************************************************/
//
//  <FunctionName: InitDraw>
//
//  <FullName: Inititalize Draw Area Function>
//
//  <Description: This function initializes either the
//   triangle or cube draw area in memory, depending on the
//   shape input. The draw area is set based upon two pairs of
//   X and Y coordinates sent in to function. For either draw
//   area, the background is set to cyan and the border to
//   black.>
//
/************************************************************/
void InitDraw(
    U16 u16DrwX1,           // Input: 1st x-coordinate
    U16 u16DrwY1,           // Input: 1st y-coordinate
    U16 u16DrwX2,           // Input: 2nd x-coordinate
    U16 u16DrwY2,           // Input: 2nd y-coordinate
    U16 u16Shape )          // Input: Shape area for drawing
/************************************************************/
{
    register U16 *u16DrawPtr;
    U16 i;
    U16 j;

    // Set background of draw area to cyan
    for (i = (u16DrwY1 + 1); i < u16DrwY2; i++) {
        if ( u16Shape == SHAPE_TRIANGLE ) {
            u16DrawPtr = u16DrawTriArea[i];
        }
        else {
            u16DrawPtr = u16DrawCubeArea[i];
        }
        for (j = (u16DrwX1 + 1); j < u16DrwX2; j++) {
            u16DrawPtr[j] = CYAN;
        }
    }

    // Set border of draw area to black
    for (i = u16DrwX1; i <= u16DrwX2; i++) {
        if ( u16Shape == SHAPE_TRIANGLE ) {
            u16DrawPtr = u16DrawTriArea[u16DrwY1];
        }
        else {
            u16DrawPtr = u16DrawCubeArea[u16DrwY1];
        }
        u16DrawPtr[i] = BLACK;
        if ( u16Shape == SHAPE_TRIANGLE ) {
            u16DrawPtr = u16DrawTriArea[u16DrwY2];
        }
        else {
            u16DrawPtr = u16DrawCubeArea[u16DrwY2];
        }
        u16DrawPtr[i] = BLACK;
    }

    for (i = u16DrwY1; i <= u16DrwY2; i++) {
        if ( u16Shape == SHAPE_TRIANGLE ) {
            u16DrawPtr = u16DrawTriArea[i];
        }
        else {
            u16DrawPtr = u16DrawCubeArea[i];
        }
        u16DrawPtr[u16DrwX1] = BLACK;
        if ( u16Shape == SHAPE_TRIANGLE ) {
            u16DrawPtr = u16DrawTriArea[i];
        }
        else {
            u16DrawPtr = u16DrawCubeArea[i];
        }
        u16DrawPtr[u16DrwX2] = BLACK;
    }
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: DrawTriangle>
//
//  <Full Name: Main Draw Triangle Function>
//
//  <Description: This function draws a triangle based upon
//   the global leg 1, leg 2 and hypotenuse values. If applicable,
//   these values are first resized to best fit the maximum size
//   of the triangle draw area. Appropriate X and Y coordinates
//   are then calculated to set a draw area specific to triangle
//   dimensions and function calls are made to initialize this
//   draw area and draw the triangle to memory. Lastly, the same
//   draw area and triangle are drawn to the draw results file.>
//
/************************************************************/
void DrawTriangle(void)
/************************************************************/
{
    CHAR CharBfr[2];
    U32 u32TriLeg1Buffer;
    U32 u32TriLeg2Buffer;
    U32 u32TriLeg1Half;
    U32 u32TriLeg2Half;
    U16 u16X1;
    U16 u16X2;
    U16 u16Y1;
    U16 u16Y2;
    U16 u16DrwX1Crnr;
    U16 u16DrwY1Crnr;
    U16 u16DrwX2Crnr;
    U16 u16DrwY2Crnr;
    U16 i;
    U16 j;

    u32TriLeg1Buffer = TriangleDataStructure.u32RtrvdTriLeg1;
    u32TriLeg2Buffer = TriangleDataStructure.u32RtrvdTriLeg2;
    // Adjust triangle leg 1 and leg 2 values for draw area
    while ( ((u32TriLeg1Buffer * 2) < (DRAW_ROW_SIZE - (DSPL_OFFSET * 2))) && ((u32TriLeg2Buffer * 2) < (DRAW_COL_SIZE - (DSPL_OFFSET * 2))) ) {
        u32TriLeg1Buffer *= 2;
        u32TriLeg2Buffer *= 2;
    }
    while ( u32TriLeg1Buffer > (DRAW_ROW_SIZE - (DSPL_OFFSET * 2)) || u32TriLeg2Buffer > (DRAW_COL_SIZE - (DSPL_OFFSET * 2)) ) {
        u32TriLeg1Buffer /= 2;
        u32TriLeg2Buffer /= 2;
    }

    // Ensure leg 1 and leg 2 values are set to at least a value of one
    if ( u32TriLeg1Buffer < 1 ) {
        u32TriLeg1Buffer = 1;
    }
    else if ( u32TriLeg2Buffer < 1 ) {
        u32TriLeg2Buffer = 1;
    }
    else {
    }

    u32TriLeg1Half = u32TriLeg1Buffer / 2;
    u32TriLeg2Half = u32TriLeg2Buffer / 2;

    u16X1 = X_GRAPH_HALF - u32TriLeg2Half;
    u16X2 = u16X1 + u32TriLeg2Buffer;
    u16Y1 = Y_GRAPH_HALF - u32TriLeg1Half;
    u16Y2 = u16Y1 + u32TriLeg1Buffer;

    // Set corners for drawing area
    u16DrwX1Crnr = u16X1 - DSPL_OFFSET;
    u16DrwY1Crnr = u16Y1 - DSPL_OFFSET;
    u16DrwX2Crnr = u16X2 + DSPL_OFFSET;
    u16DrwY2Crnr = u16Y2 + DSPL_OFFSET;

    // Call InitDraw function to initialize triangle drawing area
    InitDraw( u16DrwX1Crnr, u16DrwY1Crnr, u16DrwX2Crnr, u16DrwY2Crnr, SHAPE_TRIANGLE );

    // Draw triangle to memory
    DrawLine( (S16)u16X1, (S16)u16Y1, (S16)u16X1, (S16)u16Y2, RED, SHAPE_TRIANGLE );
    DrawLine( (S16)u16X1, (S16)u16Y2, (S16)u16X2, (S16)u16Y2, RED, SHAPE_TRIANGLE );
    DrawLine( (S16)u16X1, (S16)u16Y1, (S16)u16X2, (S16)u16Y2, RED, SHAPE_TRIANGLE );

    // Print triangle draw area to results file
    PrintToDrawFile( 2, (CHAR * ) DrawShapeHeaderArray );
    PrintToDrawFile( 1, (CHAR * ) TriDrawDataHeader );
    PrintToDrawFile( 1, (CHAR * ) DrawShapeHeaderArray );
    for (i = u16DrwY1Crnr; i <= u16DrwY2Crnr; i++) {
        for (j = u16DrwX1Crnr; j <= u16DrwX2Crnr; j++) {
            if ( u16DrawTriArea[i][j] == BLACK ) {
                CharBfr[0] = 0x23;
            }
            else if ( u16DrawTriArea[i][j] == CYAN ) {
                CharBfr[0] = 0x20;
            }
            else {
                CharBfr[0] = 0x2E;
            }
            CharBfr[1] = '\0';
            if ( j == u16DrwX1Crnr ) {
                PrintToDrawFile( 1, CharBfr );
            }
            else {
                PrintToDrawFile( 0, CharBfr );
            }
        }
    }
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: DrawCube>
//
//  <Full Name: Main Draw Cube Function>
//
//  <Description: This function draws a cube based upon the
//   global height, length and width values. If applicable,
//   these values are first resized to best fit the maximum
//   size of the cube draw area. Appropriate X and Y
//   coordinates are then calculated to set a draw area
//   specific to cube dimensions and function calls are made
//   to initialize this draw area and draw the cube to memory.
//   Lastly, the same draw area and cube are drawn to the
//   draw results file.>
//
/************************************************************/
void DrawCube(void)
/************************************************************/
{
    CHAR CharBfr[2];
    U32 u32CubeLengthBuffer;
    U32 u32CubeHeightBuffer;
    F64 f64CubeWidthBuffer;
    U32 u32CubeWidthHgtBuffer;
    U32 u32CubeWidthLngBuffer;
    U32 u32CubeLengthHalf;
    U32 u32CubeHeightHalf;
    U16 u16X1;
    U16 u16X2;
    U16 u16Y1;
    U16 u16Y2;
    U16 u16X1Wdt;
    U16 u16X2Wdt;
    U16 u16Y1Wdt;
    U16 u16Y2Wdt;
    U16 u16DrwX1Crnr;
    U16 u16DrwY1Crnr;
    U16 u16DrwX2Crnr;
    U16 u16DrwY2Crnr;
    U16 i;
    U16 j;

    u32CubeLengthBuffer = CubeDataStructure.u32RtrvdCubeLength;
    u32CubeHeightBuffer = CubeDataStructure.u32RtrvdCubeHeight;
    // Set width dimension variables, ensuring that a minimum
    // value of one is used
    if ( CubeDataStructure.u32RtrvdCubeWidth > 1 ) {
       f64CubeWidthBuffer  = ((F64)(CubeDataStructure.u32RtrvdCubeWidth * 2)) / 3;
       u32CubeWidthHgtBuffer = (U32)((f64CubeWidthBuffer * SIN_30_DEG) + 0.5);
       u32CubeWidthLngBuffer = (U32)((f64CubeWidthBuffer * COS_30_DEG) + 0.5);
    }
    else {
       u32CubeWidthHgtBuffer = 1;
       u32CubeWidthLngBuffer = 1;
    }

    // Adjust cube length and height values (after compensating for
    // width in both dimensions) for draw area
    while ( (((u32CubeHeightBuffer + u32CubeWidthHgtBuffer) * 2) < (DRAW_ROW_SIZE - (DSPL_OFFSET * 2))) && (((u32CubeLengthBuffer + u32CubeWidthLngBuffer) * 2) < (DRAW_COL_SIZE - (DSPL_OFFSET * 2))) ) {
        u32CubeHeightBuffer *= 2;
        u32CubeLengthBuffer *= 2;
        u32CubeWidthHgtBuffer *= 2;
        u32CubeWidthLngBuffer *= 2;
    }
    while ( (u32CubeHeightBuffer + u32CubeWidthHgtBuffer) > (DRAW_ROW_SIZE - (DSPL_OFFSET * 2)) || (u32CubeLengthBuffer + u32CubeWidthLngBuffer) > (DRAW_COL_SIZE - (DSPL_OFFSET * 2)) ) {
        u32CubeHeightBuffer /= 2;
        u32CubeLengthBuffer /= 2;
        u32CubeWidthHgtBuffer /= 2;
        u32CubeWidthLngBuffer /= 2;
    }

    // Ensure dimensions are set to at least a value of one
    if ( u32CubeHeightBuffer < 1 ) {
        u32CubeHeightBuffer = 1;
    }
    else if ( u32CubeLengthBuffer < 1 ) {
        u32CubeLengthBuffer = 1;
    }
    else if ( u32CubeWidthHgtBuffer < 1 ) {
        u32CubeWidthHgtBuffer = 1;
    }
    else if ( u32CubeWidthLngBuffer < 1 ) {
        u32CubeWidthLngBuffer = 1;
    }
    else {
    }

    u32CubeHeightHalf = (u32CubeHeightBuffer + u32CubeWidthHgtBuffer) / 2;
    u32CubeLengthHalf = (u32CubeLengthBuffer + u32CubeWidthLngBuffer) / 2;

    // Set X and Y coordinates for length and height
    // These are used with buffers for width length and
    // width height to draw third dimension (width)
    u16X1 = X_GRAPH_HALF - u32CubeLengthHalf;
    u16X2 = u16X1 + u32CubeLengthBuffer;
    u16Y1 = Y_GRAPH_HALF - u32CubeHeightHalf;
    u16Y2 = u16Y1 + u32CubeHeightBuffer;

    // Set X and Y coordinates for third dimension (width)
    u16X1Wdt = u16X1 + u32CubeWidthLngBuffer;
    u16X2Wdt = u16X2 + u32CubeWidthLngBuffer;
    u16Y1Wdt = u16Y1 + u32CubeWidthHgtBuffer;
    u16Y2Wdt = u16Y2 + u32CubeWidthHgtBuffer;

    // Set corners for drawing area
    u16DrwX1Crnr = u16X1 - DSPL_OFFSET;
    u16DrwY1Crnr = u16Y1 - DSPL_OFFSET;
    u16DrwX2Crnr = u16X2Wdt + DSPL_OFFSET;
    u16DrwY2Crnr = u16Y2Wdt + DSPL_OFFSET;

    // Call InitDraw function to initialize cube drawing area
    InitDraw( u16DrwX1Crnr, u16DrwY1Crnr, u16DrwX2Crnr, u16DrwY2Crnr, SHAPE_CUBE );

    // Draw third dimension (width) of cube to memory
    DrawLine( (S16)u16X1, (S16)u16Y1, (S16)u16X1Wdt, (S16)u16Y1Wdt, MAGENTA, SHAPE_CUBE );
    DrawLine( (S16)u16X2, (S16)u16Y1, (S16)u16X2Wdt, (S16)u16Y1Wdt, MAGENTA, SHAPE_CUBE );
    DrawLine( (S16)u16X1Wdt, (S16)u16Y1Wdt, (S16)u16X2Wdt, (S16)u16Y1Wdt, MAGENTA, SHAPE_CUBE );
    DrawLine( (S16)u16X1, (S16)u16Y2, (S16)u16X1Wdt, (S16)u16Y2Wdt, MAGENTA, SHAPE_CUBE );
    DrawLine( (S16)u16X2, (S16)u16Y2, (S16)u16X2Wdt, (S16)u16Y2Wdt, MAGENTA, SHAPE_CUBE );
    DrawLine( (S16)u16X1Wdt, (S16)u16Y2Wdt, (S16)u16X2Wdt, (S16)u16Y2Wdt, MAGENTA, SHAPE_CUBE );
    DrawLine( (S16)u16X1Wdt, (S16)u16Y1Wdt, (S16)u16X1Wdt, (S16)u16Y2Wdt, MAGENTA, SHAPE_CUBE );
    DrawLine( (S16)u16X2Wdt, (S16)u16Y1Wdt, (S16)u16X2Wdt, (S16)u16Y2Wdt, MAGENTA, SHAPE_CUBE );

    // Draw length and height (square) of cube to memory.
    // Length is drawn in GREEN, height in DARK_GREEN
    DrawLine( (S16)u16X1, (S16)u16Y1, (S16)u16X1, (S16)u16Y2, DARK_GREEN, SHAPE_CUBE );
    DrawLine( (S16)u16X2, (S16)u16Y1, (S16)u16X2, (S16)u16Y2, DARK_GREEN, SHAPE_CUBE );
    DrawLine( (S16)u16X1, (S16)u16Y1, (S16)u16X2, (S16)u16Y1, GREEN, SHAPE_CUBE );
    DrawLine( (S16)u16X1, (S16)u16Y2, (S16)u16X2, (S16)u16Y2, GREEN, SHAPE_CUBE );


    // Print cube draw area to results file
    PrintToDrawFile( 2, (CHAR * ) DrawShapeHeaderArray );
    PrintToDrawFile( 1, (CHAR * ) CubeDrawDataHeader );
    PrintToDrawFile( 1, (CHAR * ) DrawShapeHeaderArray );
    for (i = u16DrwY1Crnr; i <= u16DrwY2Crnr; i++) {
        for (j = u16DrwX1Crnr; j <= u16DrwX2Crnr; j++) {
            if ( u16DrawCubeArea[i][j] == BLACK ) {
                CharBfr[0] = 0x23;
            }
            else if ( u16DrawCubeArea[i][j] == CYAN ) {
                CharBfr[0] = 0x20;
            }
            else if ( u16DrawCubeArea[i][j] == MAGENTA ) {
                CharBfr[0] = 0x2E;
            }
            else if ( u16DrawCubeArea[i][j] == GREEN ) {
                CharBfr[0] = 0x2D;
            }
            else if ( u16DrawCubeArea[i][j] == DARK_GREEN ) {
                CharBfr[0] = 0x7C;
            }
            else {
                CharBfr[0] = 0x3F;
            }
            CharBfr[1] = '\0';
            if ( j == u16DrwX1Crnr ) {
                PrintToDrawFile( 1, CharBfr );
            }
            else {
                PrintToDrawFile( 0, CharBfr );
            }
        }
    }
}
/************************************************************/



/************************************************************/
//
//  <FunctionName: DrawLine>
//
//  <Full Name: Draw Line Function>
//
//  <Description: This function draws a line between specified
//  input coordinates and of specified input color to either
//  the triangle or cube memory area, depending on the shape
//  input value.>
//
/************************************************************/
void DrawLine(
    S16 s16X1,           // Input: 1st x-coordinate
    S16 s16Y1,           // Input: 1st y-coordinate
    S16 s16X2,           // Input: 2nd x-coordinate
    S16 s16Y2,           // Input: 2nd y-coordinate
    U16 u16Color,        // Input: Line Color
    U16 u16Shape)        // Input: Shape for Drawing
/************************************************************/
{
    register U16 *u16DrawPtr;
    U32 i;
    S16 s16TmpX;
    S16 s16TmpY;
    S16 s16SlopeXSign;
    S16 s16SlopeYSign;
    S16 s16AbsX;
    S16 s16AbsY;
    F64 f64AbsX;
    F64 f64AbsY;
    F64 f64Slope;


    s16AbsX = s16X2 - s16X1;
    if ( s16AbsX < 0 ) {
        s16AbsX *= -1.0;
        s16SlopeXSign = -1;
    }
    else {
        s16SlopeXSign = 1;
    }

    s16AbsY = s16Y2 - s16Y1;
    if ( s16AbsY < 0 ) {
        s16AbsY *= -1.0;
        s16SlopeYSign = -1;
    }
    else {
        s16SlopeYSign = 1;
    }

    f64AbsX = (F64)s16AbsX;
    f64AbsY = (F64)s16AbsY;

    // Slope is LTE 45 degrees
    if ( s16AbsX >= s16AbsY ) {
        f64Slope = (F64)s16SlopeXSign * (f64AbsY/f64AbsX);

        for (i = 0; i <= s16AbsX; i++) {
            s16TmpX = s16X1 + (s16SlopeXSign * i);
            s16TmpY = (S16)(s16Y1 + ((F64)i * f64Slope + 0.5));
            if ( u16Shape == SHAPE_TRIANGLE ) {
                u16DrawPtr = u16DrawTriArea[s16TmpY];
            }
            else {
                u16DrawPtr = u16DrawCubeArea[s16TmpY];
            }
            u16DrawPtr[s16TmpX] = u16Color;
        }
    }
    // Slope is GT 45 degrees
    else {
        f64Slope = (F64)s16SlopeYSign * (f64AbsX/f64AbsY);

        for (i = 0; i <= s16AbsY; i++) {
            s16TmpX = (S16)(s16X1 + ((F64)i * f64Slope + 0.5));
            s16TmpY = s16Y1 + (s16SlopeYSign * i);
            if ( u16Shape == SHAPE_TRIANGLE ) {
                u16DrawPtr = u16DrawTriArea[s16TmpY];
            }
            else {
                u16DrawPtr = u16DrawCubeArea[s16TmpY];
            }
            u16DrawPtr[s16TmpX] = u16Color;
        }
    }
}
/************************************************************/


/********DRAW_FILE CONCLUDED*********************************************/
