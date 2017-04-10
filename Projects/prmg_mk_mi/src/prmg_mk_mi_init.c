 /**********************************************************************************************************************
*                                        (c) COPYRIGHT by AO NPK Pelengator..                                             *
*                                               All rights reserved.                                                  *
***********************************************************************************************************************
* Module      : bky_arm_init.c
* Description : Описание как формируеться тактовые сигналы соответсвие документации и кода
                Микроконтроллер имеет 2 встроенных генератора, 2 внешних осциллятора.
* Author      : Konstantin Shiluaev
******************************************************************************
******************************************************************************
* Module's Description Record:
* ============================
* $State: Debug$
* $Revision: 0.0.0 $
* $Date: 2015/01/14 10:40:51 $
******************************************************************************/


#include "stm32f4xx.h"
#include "prmg_mk_mi_init.h"


//Общее определение
GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure; 


//Для GPIO

#define Open_LED_GPIO_CLK								RCC_AHB1Periph_GPIOB
#define Open_LED_GPIO								  	GPIOB


//Для USART3
#define Open_USART                        USART3
#define Open_USART_CLK                    RCC_APB1Periph_USART3
	
#define Open_USART_TX_PIN                 GPIO_Pin_10
#define Open_USART_TX_GPIO_PORT           GPIOC
#define Open_USART_TX_GPIO_CLK            RCC_AHB1Periph_GPIOC
#define Open_USART_TX_SOURCE              GPIO_PinSource10
#define Open_USART_TX_AF                  GPIO_AF_USART3
	
	
#define Open_USART_RX_PIN                 GPIO_Pin_11
#define Open_USART_RX_GPIO_PORT           GPIOC
#define Open_USART_RX_GPIO_CLK            RCC_AHB1Periph_GPIOC
#define Open_USART_RX_SOURCE              GPIO_PinSource11
#define Open_USART_RX_AF                  GPIO_AF_USART3
	









/*****************************************************************************/
/*  PRIVATE FUNCTIONS                                                        */
/*****************************************************************************/
static void ClockConfig(void);
static void PortsConfig(void);
//static void SysTimerConfig(void);

//Конфиги для Перефирии RISC
//static void risc_Uart_1_Config(void);
//static void risc_Uart_2_Config(void);
  static void risc_Uart_3_Config(void);   //для отладочной платы STM32F



//static void risc_AdcConfig(void);
//static void risc_Rtc_and_BkpConfig(void);
//static void risc_Timer1Config(void);
//static void risc_ExternalBusConfig(void);

/**************************************************************************************************
Syntax:             Init_ARM(void)
Parameters:         none
Remarks:            Стартовая функция Инициализации
Return Value:       none
***************************************************************************************************/
void Init_ARM()
{
	   /*Main Initialization Function*/
     // ClockConfig();  	//Инициализация главных клоков CPU 1986ВЕ91Т
      PortsConfig();  	//Инициализация Портов 1986ВЕ91Т
    /*Системная Инициализация*/
     // SysTimerConfig(); //Инициализация системного таймера ARM ядра

    /*Инициализация Переферийных блоков  RISC ядра*/
     // risc_Uart_1_Config();
     // risc_Uart_2_Config();
	      risc_Uart_3_Config();
	 
																	 //UART1 and UART2 config
    //risc_Timer1Config();         //Risc Timer1
    //risc_AdcConfig();            //АЦП
    //risc_Rtc_and_BkpConfig();    //Real_Time_clock_and_BKP
    //risc_ExternalBusConfig();     //Конфигурация внешней системной шины

    /*Инициализация Перефирийных блоков  DSP ядра*/


}


/**************************************************************************************************
Syntax:             void ClockConfig()
Parameters:         none
Remarks:            Управление тактовыми частотами ведется через периферийный блок RST_CLK.
                    При включении питания микроконтроллер запускается на частоте HSI генератора.
                    Выдача тактовых сигналов синхронизации для всех периферийных блоков кроме RST_CLK отключена.
                    Для начала работы с нужным периферийным блоком необходимо включить его тактовую частоту
                    в регистре PER_CLOCK. Некоторые контроллеры интерфейсов (UART, CAN, USB, Таймеры)
                    могут работать на частотах отличных от частоты процессорного ядра, по этому в соответствующих
                    регистрах (UART_CLOCK, CAN_CLOCK, USB_CLOCK, TIM_CLOCK) могут быть заданы их скорости работы.
Return Value:       none
***************************************************************************************************/
void ClockConfig()
{




}


/**************************************************************************************************
Syntax:             void PortsConfig()
Parameters:         настройк портов ЦП 1901ВЦ1T
Remarks:            unload the kernel module driver - invoked by rmmod
Return Value:       none
***************************************************************************************************/
void PortsConfig()
{
   //GPIO_InitTypeDef GPIO_InitStructure;
	 ///////////////////////////////////////////PORT_A CONFIG////////////////////////////////////////////////////////////

	
	///////////////////////////////////////////PORT_B CONFIG////////////////////////////////////////////////////////////
  RCC_AHB1PeriphClockCmd(Open_LED_GPIO_CLK, ENABLE);
	// Configure PB0 PB1 PB2 PB3 in output pushpull mode 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(Open_LED_GPIO, &GPIO_InitStructure);

	
	
	
 ///////////////////////////////////////////PORT_С CONFIG для UART3////////////////////////////////////////////////////////////
	  RCC_AHB1PeriphClockCmd(Open_USART_TX_GPIO_CLK,ENABLE);
    RCC_AHB1PeriphClockCmd(Open_USART_RX_GPIO_CLK,ENABLE);
 
  //для UART3	
   RCC_APB1PeriphClockCmd(Open_USART_CLK,ENABLE);
	
	 GPIO_PinAFConfig(Open_USART_TX_GPIO_PORT, Open_USART_TX_SOURCE, Open_USART_TX_AF);
   GPIO_PinAFConfig(Open_USART_RX_GPIO_PORT, Open_USART_RX_SOURCE, Open_USART_RX_AF);
	
	
  /*
  *  Open_USART_TX -> PA9 , Open_USART_RX -PA10
  */
   GPIO_InitStructure.GPIO_Pin = Open_USART_TX_PIN;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_Init(Open_USART_TX_GPIO_PORT, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin = Open_USART_RX_PIN;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_Init(Open_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
}



/**************************************************************************************************
Syntax:             void SysTickConfig()
Parameters:         Инициализация системного таймера ARM ядра
Remarks:            Системный таймер у нас 24 бита максимальное число тиков которое мы можем туда загрузить.
Return Value:       none
***************************************************************************************************/
void SysTimerConfig()
{



}


/**************************************************************************************************
Syntax:             static void risc_Uart_3_Config()
Parameters:         Конфигурирование UART3
Remarks:            
Return Value:       none
***************************************************************************************************/
static void risc_Uart_3_Config()
{

	/*
   		 USARTx configured as follow:
         - BaudRate = 115200 baud  
		 - Word Length = 8 Bits
         - One Stop Bit
         - No parity
         - Hardware flow control disabled (RTS and CTS signals)
         - Receive and transmit    
 */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(Open_USART, &USART_InitStructure);
   
	  /* Enable the Open_USART Transmit interrupt: this interrupt is generated when the 
     Open_USART transmit data register is empty */
  USART_ITConfig(Open_USART,USART_IT_RXNE,ENABLE);
  USART_Cmd(Open_USART, ENABLE); 
	 

}	









