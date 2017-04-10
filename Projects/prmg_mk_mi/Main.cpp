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


//Внешние инклуды
#include "stm32f4xx.h"

#include "prmg_mk_mi_isr.h"
#include "prmg_mk_mi_init.h"
#include "prmg_mk_mi_delay.h"


//#include "stdint.h"



#define CK_DELAY						      2
#define CS_DELAY						      2
#define LOAD_DELAY						    5
#define DELAY_POWER_ON_OFF				30




int main()
{
  Init_ARM(); 
	Init_NVIC();
	
	
	
	
	
	while(1)
	{
       // Delay_akimov(CS_DELAY,'u');
		   // Delay_akimov(CK_DELAY,'u');
       // Delay_akimov(LOAD_DELAY,'u');
  		  // GPIO_ResetBits(GPIOB , GPIO_Pin_0);                //работает пин
		     //Delay_akimov(CS_DELAY,'u');                      //1 [мкс]
		     //Delay_akimov(CK_DELAY,'u');                      //1 [мкс]
				//Delay_akimov(LOAD_DELAY,'u');                    	//2 [мкс]
		     //sys_timer_microsecond_delay(2);
		     
		     //GPIO_SetBits(GPIOB , GPIO_Pin_0);                  //работает пин
		      //while_delay(100); 
		     //  Delay_akimov(CS_DELAY,'u');
		     USART_SendData(USART3, 0xFFAA);  
         while_delay(10000);
            
		     //Delay_akimov(DELAY_POWER_ON_OFF,'u');
	}	//end while	
	
	

}  //end Main














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
