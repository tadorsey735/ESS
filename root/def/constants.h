/************************************************************************/
//
//  <FileName: constants.h>
//
//  <FileDesc: ESS Global Constants File>
//
//  <Version: 1.1.4>
//
/************************************************************************/
#if defined __CCS_RUN__
#include <stdio.h>
#include <string.h>


// LLT Revision Tag
// "$Revision$"

#endif

#if !defined(CONSTANTS_H_)
#define CONSTANTS_H_


/*======================================================================*/
/* General Constants                                                    */
/*======================================================================*/
#define ZERO                    (0)
#define ONE                     (1)
#define NO                      (0)
#define YES                     (1)
#define DATA_NOT_SET            (0)   // Input Data set in Current Frame
#define DATA_SET                (1)   // Input Data has NOT been set in Current Frame
#define PRTY_NG                 (0)   // Parity Failure
#define PRTY_GOOD               (1)   // Expected Parity
#define U32_MAX_VALUE  (0xFFFFFFFF)   // Maximum value for U32 variable


/*======================================================================*/
/* Total Frames                                                         */
/*======================================================================*/

#define FIRST_FRAME   ( 1)
#define FINAL_FRAME   (10)


/*======================================================================*/
/* Retrieve Word Constants                                              */
/*======================================================================*/
#define SHAPE_TYPE_MASK         (0x0000000F)   // Shape Type Label Bit Mask
#define SHAPE_SUBTYPE_MASK      (0x000000F0)   // Shape Subtype Label Bit Mask
#define SHAPE_DATA_MASK         (0x0FFFFF00)   // Shape Data Bit Mask
#define SHAPE_PRTY_MASK         (0x80000000)   // Parity Bit Mask

#define SHAPE_TYPE_BIT_PLACE            ( 0)   // Shape Type Label Bit Position
#define SHAPE_SUBTYPE_BIT_PLACE         ( 4)   // Shape Subtype Label Bit Position
#define SHAPE_DATA_BIT_PLACE            ( 8)   // Shape Data Bit Position
#define SHAPE_PRTY_BIT_PLACE            (31)   // Parity Bit Position

#define SHAPE_TRIANGLE                (0x08)   // Triangle Input Word Type Label
#define TRI_LEG1                      (0x00)   // Triangle Leg1 Subtype Label
#define TRI_LEG2                      (0x01)   // Triangle Leg2 Subtype Label

#define SHAPE_CUBE                    (0x0A)   // Cube Input Word Type Label
#define CUBE_LNG                      (0x02)   // Cube Length Subtype Label
#define CUBE_HGT                      (0x03)   // Cube Height Subtype Label
#define CUBE_WDT                      (0x04)   // Cube Width Subtype Label


/*======================================================================*/
/* Data Areas                                                           */
/*======================================================================*/
#define RTRV_DATA_SIZE                       ( 5)   // Number of Words to Retrieve
#define RTRV_DATA_HD_ADRS            (0x68000000)   // Head Address of Input Data Area
#define RTRV_DATA_WORD1_ADRS         (0x68000000)   // Address for Word 1 of Input Data Area
#define RTRV_DATA_WORD2_ADRS         (0x68000004)   // Address for Word 2 of Input Data Area
#define RTRV_DATA_WORD3_ADRS         (0x68000008)   // Address for Word 3 of Input Data Area
#define RTRV_DATA_WORD4_ADRS         (0x6800000C)   // Address for Word 4 of Input Data Area
#define RTRV_DATA_WORD5_ADRS         (0x68000010)   // Address for Word 5 of Input Data Area

#define RTRVD_DATA_WORD_HD_ADRS      (0x68001000)   // Head Address of Retrieved Data Word Area
#define RTRVD_DATA_WORD_END_ADRS     (0x68001FFC)   // Last Address of Retrieved Data Word Area
#define RTRVD_DATA_WORD_RSVRD_SPACE  (0x00000014)   // Reserve 5 addresses for current frame retrieved words

// Reserve 3 addresses for every error snapshot:
// First Address:  Frame Number
// Second Address: Error Code
// Third Address:  Associated Data
#define ERROR_RECORD_RSVRD_SPACE     (0x0000000C)

// Retrieve Error Data Area
#define RTRV_ERROR_DATA_HD_ADRS      (0x68002000)   // Head Address of Retrieve Error Data Area
#define RTRV_ERROR_DATA_END_ADRS     (0x68002FFC)   // Last Address of Retrieve Error Data Area

// Calculation Error Data Area
#define CALC_ERROR_DATA_HD_ADRS      (0x68003000)   // Head Address of Calculation Error Data Area
#define CALC_ERROR_DATA_END_ADRS     (0x68003FFC)   // Last Address of Calculation Error Data Area

// Results Error Data Area
#define RSLT_ERROR_DATA_HD_ADRS      (0x68004000)   // Head Address of Results Error Data Area
#define RSLT_ERROR_DATA_END_ADRS     (0x68004FFC)   // Last Address of Results Error Data Area

// Calculated Data Area Address
#define CALCULATED_DATA_HD_ADRS      (0x68005000)   // Head Address for Calculated Data Area
#define CALCULATED_DATA_END_ADRS     (0x68005FFC)   // Last Address for Calculated Data Area

#define CALCULATED_DATA_RSVRD_SPACE  (0x00000018)   // Reserve 5 addresses for current frame calculated data
#define CALCULATED_DATA_ADRS_NO              ( 6)   // Addresses needed to save current frame calculated data

#define FRAME_CALCD_INDEX                    ( 0)   // Index for the Frame Number Data Save Calculated In
#define TRI_AREA_SAVE_INDEX1                 ( 1)   // Index for upper bits of saved Triangle Area Value in Calculated Data Area
#define TRI_AREA_SAVE_INDEX2                 ( 2)   // Index for lower bits of saved Triangle Area Value in Calculated Data Area
#define TRI_HYPO_SAVE_INDEX1                 ( 3)   // Index for upper bits of saved Triangle Hypotenuse Value in Calculated Data Area
#define TRI_HYPO_SAVE_INDEX2                 ( 4)   // Index for lower bits of saved Triangle Hypotenuse Value in Calculated Data Area
#define CUBE_VOL_SAVE_INDEX                  ( 5)   // Index of saved Cube Volume Value in Calculated Data Area

/*======================================================================*/
/* Status Word Bit Positions                                            */
/*======================================================================*/
#define STATUS_SHAPETYPE_BITPOS    ( 0)
#define STATUS_SUBTYPE_BITPOS      ( 4)
#define STATUS_MULTIPLE_BITPOS     ( 8)
#define STATUS_PRTY_BITPOS         (16)
#define STATUS_RECOG_SHAPE_BITPOS  (17)
#define STATUS_RECOG_DIM_BITPOS    (18)



/*======================================================================*/
/* Received Data Maximum Values                                         */
/*======================================================================*/
#define TRI_LEG1_MIN_VALUE        (  10)
#define TRI_LEG2_MIN_VALUE        (  10)
#define CUBE_LNG_MIN_VALUE        (  10)
#define CUBE_HGT_MIN_VALUE        (  10)
#define CUBE_WDT_MIN_VALUE        (  10)

#if defined __CCS_RUN__
    #define TRI_LEG1_MAX_VALUE    (1000)
    #define TRI_LEG2_MAX_VALUE    (1000)
#else
    #define TRI_LEG1_MAX_VALUE    ( 194)
    #define TRI_LEG2_MAX_VALUE    ( 194)
#endif
#define CUBE_LNG_MAX_VALUE        (1000)
#define CUBE_HGT_MAX_VALUE        (1000)
#define CUBE_WDT_MAX_VALUE        (1000)

#define TRI_LEG1_DEFAULT_VALUE    (  10)
#define TRI_LEG2_DEFAULT_VALUE    (  10)
#define CUBE_LNG_DEFAULT_VALUE    (  10)
#define CUBE_HGT_DEFAULT_VALUE    (  10)
#define CUBE_WDT_DEFAULT_VALUE    (  10)


/*======================================================================*/
/* Error Codes                                                          */
/*======================================================================*/
// Retrieve Data Error Codes
#define ERR_CODE_PRTY                 (0x01)   // Retrieved Word Parity Error
#define ERR_CODE_SUB_SET              (0x02)   // Multiple Retrieved Words for Same Data Subtype
#define ERR_CODE_SHAPE                (0x03)   // Retrieved Word Label Not Recognized
#define ERR_CODE_TRI                  (0x04)   // Retrieved Triangle Word Subtype Not Recognized
#define ERR_CODE_CUBE                 (0x05)   // Retrieved Cube Word Subtype Not Recognized
#define ERR_CODE_LEG1_NOTSET          (0x06)   // Triangle Leg 1 Data Not Set in Current Frame (Retrieve Error)
#define ERR_CODE_LEG2_NOTSET          (0x07)   // Triangle Leg 2 Data Not Set in Current Frame (Retrieve Error)
#define ERR_CODE_LNG_NOTSET           (0x08)   // Cube Length Data Not Set in Current Frame (Retrieve Error)
#define ERR_CODE_HGT_NOTSET           (0x09)   // Cube Height Data Not Set in Current Frame (Retrieve Error)
#define ERR_CODE_WDT_NOTSET           (0x0A)   // Cube Width Data Not Set in Current Frame (Retrieve Error)

#define RTRV_ERROR_CODE_INDEX           ( 1)   // Index for Retrieve Error Code in Current Frame Retrieve Error Array
#define RTRV_ERROR_DATA_INDEX           ( 2)   // Index for Retrieve Data of Error in Current Frame Retrieve Error Array

// Calculation Data Error Codes
#define ERR_CODE_LEG1_DEFAULT         (0x11)   // Current Frame Triangle Leg 1 Data is zero (Use Default Setting)
#define ERR_CODE_LEG2_DEFAULT         (0x12)   // Current Frame Triangle Leg 2 Data is zero (Use Default Setting)
#define ERR_CODE_LNG_DEFAULT          (0x13)   // Current Frame Cube Length Data is zero (Use Default Setting)
#define ERR_CODE_HGT_DEFAULT          (0x14)   // Current Frame Cube Height Data is zero (Use Default Setting)
#define ERR_CODE_WDT_DEFAULT          (0x15)   // Current Frame Cube Width Data is zero (Use Default Setting)
#define ERR_CODE_LEG1_NO_DATA         (0x16)   // Current Frame Triangle Leg 1 Data is zero (Use Previous Frame Value)
#define ERR_CODE_LEG2_NO_DATA         (0x17)   // Current Frame Triangle Leg 2 Data is zero (Use Previous Frame Value)
#define ERR_CODE_LNG_NO_DATA          (0x18)   // Current Frame Cube Length Data is zero (Use Previous Frame Value)
#define ERR_CODE_HGT_NO_DATA          (0x19)   // Current Frame Cube Height Data is zero (Use Previous Frame Value)
#define ERR_CODE_WDT_NO_DATA          (0x1A)   // Current Frame Cube Width Data is zero (Use Previous Frame Value)
#define ERR_CODE_LEG1_TOO_BIG         (0x1B)   // Current Frame Triangle Leg 1 Value was Limited to Max Value
#define ERR_CODE_LEG2_TOO_BIG         (0x1C)   // Current Frame Triangle Leg 2 Value was Limited to Max Value
#define ERR_CODE_LNG_TOO_BIG          (0x1D)   // Current Frame Cube Length was Limited to Max Value
#define ERR_CODE_HGT_TOO_BIG          (0x1E)   // Current Frame Cube Height was Limited to Max Value
#define ERR_CODE_WDT_TOO_BIG          (0x1F)   // Current Frame Cube Width was Limited to Max Value
#define ERR_CODE_LEG1_TOO_SMALL       (0x21)   // Current Frame Triangle Leg 1 Value was Limited to Min Value
#define ERR_CODE_LEG2_TOO_SMALL       (0x22)   // Current Frame Triangle Leg 2 Value was Limited to Min Value
#define ERR_CODE_LNG_TOO_SMALL        (0x23)   // Current Frame Cube Length was Limited to Min Value
#define ERR_CODE_HGT_TOO_SMALL        (0x24)   // Current Frame Cube Height was Limited to Min Value
#define ERR_CODE_WDT_TOO_SMALL        (0x25)   // Current Frame Cube Width was Limited to Min Value


/*======================================================================*/
/* Various Array Constants                                              */
/*======================================================================*/
#define SET_ARRAY_SIZE                  ( 5)   // Size of the Input Parity Check Array
#define MAX_FRAME_ERR                   (20)   // Max Amount of Retrieve Errors / Max Amount of Calculation Errors
#define RTRV_ERR_RCD_LENGTH             ( 3)   // Size of Retrieve Error Snapshot Array
#define RTRV_ERROR_TYPE               (0xFA)   // Code For Data to Be Set to Calculation Error Area
#define CALC_ERR_RCD_LENGTH             ( 3)   // Size of Calculation Error Snapshot Array
#define CALC_ERROR_TYPE               (0xFB)   // Code For Data to Be Set to Calculation Error Area


/*======================================================================*/
/* Result String Constants                                              */
/*======================================================================*/
#define U32_MAX_DISPLAY_DIGITS          (12)   // Integer Character String Maximum Characters
#define F32_MAX_DISPLAY_DEC_DIGITS      ( 4)   // Floating Point 32 Bit Value Maximum Decimal Places Converted to Characters
#define F32_MAX_DISPLAY_NON_DEC_DIGITS  ( 3)   // Floating Point 32 Bit Value Maximum Ten Spots
#define F64_MAX_DISPLAY_DEC_DIGITS      ( 7)   // Floating Point 64 Bit Value Maximum Decimal Places Converted to Characters
#define F64_MAX_DISPLAY_NON_DEC_DIGITS  ( 3)   // Floating Point 64 Bit Value Maximum Ten Spots

#define NO_CARRIAGE_RETURN              ( 0)
#define ONE_CARRIAGE_RETURN             ( 1)
#define TWO_CARRIAGE_RETURN             ( 2)
#define THREE_CARRIAGE_RETURN           ( 3)
#define FOUR_CARRIAGE_RETURN            ( 4)

#define STRING_NULL                   (0x00)
#define ASCII_SPACE                   (0x20)
#define ASCII_CLOSE_PRTHS             (0x29)
#define ASCII_PERIOD                  (0x2E)
#define ASCII_ZERO                    (0x30)


/*======================================================================*/
/* Draw Constants                                                       */
/*======================================================================*/

#define DRAW_ROW_SIZE                  (100)
#define DRAW_COL_SIZE                  (100)
#define X_GRAPH_HALF                   ( 50)
#define Y_GRAPH_HALF                   ( 50)
#define DSPL_OFFSET                    ( 10)
#define SIN_30_DEG                     (0.5)
#define COS_30_DEG               (0.8660254)


/*======================================================================*/
/* Color                                                                */
/*======================================================================*/
#define BLACK                                                 (0x0000)
#define WHITE                                                 (0x0777)
#define RED                                                   (0x0700)
#define BLUE                                                  (0x0007)
#define DIM_BLUE                                              (0x0001)
#define GREEN                                                 (0x0070)
#define DARK_GREEN                                            (0x0010)
#define CYAN                                                  (0x0077)
#define YELLOW                                                (0x0770)
#define MAGENTA                                               (0x0707)
#define GRAY                                                  (0x0444)
#define LIGHT_GRAY                                            (0x0555)
#define DARK_GRAY                                             (0x0222)
#define SKY_BLUE                                              (0x0016)
#define BROWN                                                 (0x0430)


#endif

/************************************************************************/
