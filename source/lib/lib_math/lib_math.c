////*****************************************////
//  Name : lib_math.c
//  Data : 2020/09
//  Version : 0.0
////*****************************************////

#include "lib_math.h"

//void lib_math_init(void)
//{
//
//}

uint32 math_exp(uint32 ulBase, uint32 ulTimes)
{
	uint32 ulTimeCnt;
	uint32 ulData;

	ulData = 1;

	for(ulTimeCnt = 0; ulTimeCnt < ulTimes; ulTimeCnt++)
	{
		ulData = ulData * ulBase;
	}

	return ulData;
}
#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
void Queue_Push(CcQueue *qb,uint8 data)
{
//	DisableIRQ(PWM1_COMMON_SM_0_IRQN);
//	DisableIRQ(Reserved68_IRQn);
    if (Queue_Full(qb) == 1)
    {
 //  	EnableIRQ(PWM1_COMMON_SM_0_IRQN);
 //   	EnableIRQ(Reserved68_IRQn);
    	return;
    }

    qb->rear = (qb->rear +1) % BuffSize;
    qb->Buff[qb->rear] = data;

//    EnableIRQ(PWM1_COMMON_SM_0_IRQN);
 //   EnableIRQ(Reserved68_IRQn);
}
#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
int32 Queue_Pop(CcQueue* qb)
{

//	DisableIRQ(LPUART1_SERIAL_RX_TX_IRQN);
/*
	if (Queue_Empty(qb) == 1)
    {
		EnableIRQ(LPUART1_SERIAL_RX_TX_IRQN);
		return -1;
    }
*/
    qb->front = (qb->front + 1) % BuffSize;
    int32 element = qb->Buff[qb->front];

//    EnableIRQ(LPUART1_SERIAL_RX_TX_IRQN);
    return element;
}
#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
int32 Queue_Full(CcQueue* qb)
{

	return( (qb->rear + 1) % BuffSize == qb->front);
}
#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
int32 Queue_Empty(CcQueue* qb)
{

	return(qb->rear  == qb->front);
}
#if defined(RAM_FUNC_ENABLE) && (RAM_FUNC_ENABLE == 1)
__RAMFUNC(RAM_FUNC_BLOCK)
#endif
int32 Queue_GetSize(CcQueue* qb)
{

//	DisableIRQ(LPUART1_SERIAL_RX_TX_IRQN);

	if (qb->rear >= qb->front)
    {
//		EnableIRQ(LPUART1_SERIAL_RX_TX_IRQN);
		return (qb->rear - qb->front);
    }
    else
    {
//    	EnableIRQ(LPUART1_SERIAL_RX_TX_IRQN);
    	return (BuffSize + qb->rear - qb->front);
    }

}

int32 Queue_GetRear(CcQueue* qb)
{
    return qb->rear;
}

int32 Queue_GetFront(CcQueue* qb)
{
    return qb->front;
}
