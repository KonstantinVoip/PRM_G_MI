  /**********************************************************************************************************************
*                                        (c) COPYRIGHT by AO NPK PELENGATOR.                                           *
*                                               All rights reserved.                                                   *
***********************************************************************************************************************
* Module      : bky_arm_isr.h
* Description : Interrupt Service Rotens Description
* Author      : Konstantin Shiluaev
******************************************************************************
******************************************************************************
* Module's Description Record:
* ============================
* $State: Debug$
* $Revision: 0.0.0 $
* $Date: 2015/01/14 10:40:51 $
******************************************************************************/
#ifndef __TIS_AS_ISR_H
#define __TIS_AS_ISR_H

//#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//Инициализация Обрабочика Прерываний NVIC
void Init_NVIC(void);


//Сами функции обработчкик прерываний	
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
//void SVC_Handler(void);
void DebugMon_Handler(void);
//void PendSV_Handler(void);
//void SysTick_Handler(void);
void USART1_IRQHANDLER(void);
void USART3_IRQHANDLER(void);


	
	
//Другие функции
#ifdef __cplusplus
}

#endif
#endif //endif __TIS_AS_ISR_H
