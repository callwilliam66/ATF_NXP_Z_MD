////*****************************************////
//  Name : lib_math_ext.h
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#ifndef _LIB_MATH_EXT_H_
#define _LIB_MATH_EXT_H_

#include "lib.h"

#include "math.h"

#define  MATH_PI      3.14159265358979F // pi

#define  MATH_TWO_PI  (MATH_PI * 2.0F) // 2 * pi

#define  MATH_ONE__SQRT3 0.5773502691896258F  /* 1/sqrt(3) */
#define  MATH_SQRT3__TWO 0.8660254037844386F  /* sqrt(3)/2 */
#define  MATH_ONE__TWO_PI (1.0F / MATH_TWO_PI)  /* 1/(2*pi) */

#define  BuffSize 2048

typedef struct {
    uint8 Buff[BuffSize];
    int32 front;
    int32 rear;
    int32 data_size;
    uint32 checksum;
}CcQueue;

extern CcQueue   Data_Queue;

// extern function
//extern void lib_math_init(void);

extern uint32 math_exp(uint32 ulBase, uint32 ulTimes);

extern void Queue_Push(CcQueue* qb, uint8 data);
extern int32 Queue_Full(CcQueue* qb);
extern int32 Queue_Empty(CcQueue* qb);
extern int32 Queue_Pop(CcQueue* qb);
extern int32 Queue_GetSize(CcQueue* qb);
extern int32 Queue_GetRear(CcQueue* qb);
extern int32 Queue_GetFront(CcQueue* qb);

#define math_abs_macro(data) ((data >= 0) ? data : -data)

#endif // end of file
