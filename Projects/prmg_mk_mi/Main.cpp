 /**********************************************************************************************************************
*                                        (c) COPYRIGHT by AO NPK Pelengator.                                             *
*                                               All rights reserved.                                                  *
***********************************************************************************************************************
* Module      : Main.c
* Description : Main Initialization File for STM32F405RGT6
* Author      : Konstantin Shiluaev
******************************************************************************
******************************************************************************
* Module's Description Record:
* ============================
* $State: Debug$
* $Revision: 0.0.0 $
* $Date: 2016/01/14 10:40:51 $
******************************************************************************/

//prmg_mk_mi

//#include <stdio.h>


//Внешние инклуды от STM
#include "stm32f4xx.h"
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "system_stm32f4xx.h"

#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>



//Файлы Конфигурации FreeRTOS
#include "mpu_wrappers.h"
#include "portmacro.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "StackMacros.h"
#include "deprecated_definitions.h"
#include "portable.h"
#include "StackMacros.h"


//Файлы с Описание минимальных Примитовов FreeRTOS
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
#include "croutine.h"
#include "event_groups.h"
#include "list.h"


//Локальные Include файлы.


//#include "prmg_mk_mi_isr.h"
#include "prmg_mk_mi_init.h"
//#include "prmg_mk_mi_delay.h"



//#include "stdint.h"
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}

void vApplicationIdleHook( void )
{
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	task.  It is essential that code added to this hook function never attempts
	to block in any way (for example, call xQueueReceive() with a block time
	specified, or call vTaskDelay()).  If the application makes use of the
	vTaskDelete() API function (as this demo application does) then it is also
	important that vApplicationIdleHook() is permitted to return to its calling
	function, because it is the responsibility of the idle task to clean up
	memory allocated by the kernel to any task that has since been deleted. */
}

void vApplicationMallocFailedHook( void )
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created.  It is also called by various parts of the
	demo application.  If heap_1.c or heap_2.c are used, then the size of the
	heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	to query the size of free heap space that remains (although it does not
	provide information on how the remaining heap might be fragmented). */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}


void vApplicationTickHook( void )
{
	
	

}	


/*Функция работает*/
__asm void my_strcpy(const char *src, char *dst)
{
loop
      LDRB  r2, [r0], #1
      STRB  r2, [r1], #1
      CMP   r2, #0
      BNE   loop
      BX    lr
}



void prvEnableVFP_skd( void )
{
register uint32_t r0         __ASM("r0");
	__asm
	{
			
	}	
}


/*
void vTaskLED1(void *pvParameters) {
        for (;;) {
                GPIO_SetBits(GPIOD, GPIO_Pin_12);
                vTaskDelay(500);
                GPIO_ResetBits(GPIOD, GPIO_Pin_12);
                vTaskDelay(500);
        }
}


void vTaskLED2(void *pvParameters) {
        for (;;) {
                GPIO_SetBits(GPIOD, GPIO_Pin_14);
                vTaskDelay(321);
                GPIO_ResetBits(GPIOD, GPIO_Pin_14);
                vTaskDelay(321);
        }
}
*/


/* Task to be created. */
void vTaskCode( void * pvParameters )
{
    /* The parameter value is expected to be 1 as 1 is passed in the
    pvParameters value in the call to xTaskCreate() below. 
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );*/

    for( ;; )
    {
       /* Task code goes here. */
       GPIO_SetBits(GPIOD, GPIO_Pin_12);
       vTaskDelay(500);
       GPIO_ResetBits(GPIOD, GPIO_Pin_12);
       vTaskDelay(500);
		}
}


/* Task to be created. */
void vTaskCode_1( void * pvParameters )
{
    /* The parameter value is expected to be 1 as 1 is passed in the
    pvParameters value in the call to xTaskCreate() below. 
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );*/

    for( ;; )
    {
       /* Task code goes here. */
       GPIO_SetBits(GPIOD, GPIO_Pin_14);
       vTaskDelay(321);
       GPIO_ResetBits(GPIOD, GPIO_Pin_14);
       vTaskDelay(321);
		}
}







int main()
{
   BaseType_t xReturned;
   TaskHandle_t xHandle = NULL;
	
	 BaseType_t xReturned_1;
   TaskHandle_t xHandle_1 = NULL; 
	
	 
	
	//Нужно добавить аппаратно  инициализация вроде работает нормально зажигаем два led
		GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(GPIOD, &GPIO_InitStructure);	

	
	
   
	   /* Create the task, storing the handle. */
   
  //first task
	xReturned = xTaskCreate(
                    vTaskCode_1,       // Function that implements the task. 
                    "NAME",          // Text name for the task. 
                    512,      // Stack size in words, not bytes. 
                    ( void * ) 1,    // Parameter passed into the task. 
                    tskIDLE_PRIORITY,// Priority at which the task is created. 
                    &xHandle );      // Used to pass out the created task's handle.
	 

  //second task
	xReturned_1 = xTaskCreate(
                    vTaskCode,       // Function that implements the task. 
                    "NAME",          // Text name for the task. 
                    512,      // Stack size in words, not bytes. 
                    ( void * ) 2,    // Parameter passed into the task. 
                    tskIDLE_PRIORITY,// Priority at which the task is created. 
                    &xHandle_1 );      // Used to pass out the created task's handle.







										
	//  if( xReturned == pdPASS )
  //  {
        // The task was created.  Use the task's handle to delete the task. 
       // vTaskDelete( xHandle );
    //} 
	  vTaskStartScheduler();
	
	
  //  GPIO_SetBits(GPIOD, GPIO_Pin_14); 
	//  GPIO_ResetBits(GPIOD, GPIO_Pin_14);
	
  //  GPIO_SetBits(GPIOD, GPIO_Pin_12); 
	//  GPIO_ResetBits(GPIOD, GPIO_Pin_12);
}  














/*Видимо Обработчик Ошибок */
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the source file ID, the source line number
*                : and (if USE_ASSERT_INFO == 2) expression text where
*                : the assert_param error has occurred.
* Input          : file_id - pointer to the source file name
*                : line - assert_param error line source number
*                : expr - expression text
* Output         : None
* Return         : None
*******************************************************************************/
#if (USE_ASSERT_INFO == 1)
void assert_failed(uint32_t file_id, uint32_t line)
{
  /* User can add his own implementation to report the source file ID and line number.
     Ex: printf("Wrong parameters value: file Id %d on line %d\r\n", file_id, line) */


  printf("Wrong parameters value: file Id %d on line %d\r\n", file_id, line);
  /* Infinite loop */
  while (1)
  {
  }
}
#elif (USE_ASSERT_INFO == 2)
void assert_failed(uint32_t file_id, uint32_t line, const uint8_t* expr)
{
  /* User can add his own implementation to report the source file ID, line number and
     expression text.
     Ex: printf("Wrong parameters value (%s): file Id %d on line %d\r\n", expr, file_id, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_ASSERT_INFO */
