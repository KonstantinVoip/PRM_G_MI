 /**********************************************************************************************************************
*                                        (c) COPYRIGHT by AO NPK Pelengator..                                             *
*                                               All rights reserved.                                                  *
***********************************************************************************************************************
* Module      : bky_arm_init.c
* Description : �������� ��� ������������ �������� ������� ����������� ������������ � ����
                ��������������� ����� 2 ���������� ����������, 2 ������� �����������.
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


//����� �����������
GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure; 


//��� GPIO

#define Open_LED_GPIO_CLK								RCC_AHB1Periph_GPIOB
#define Open_LED_GPIO								  	GPIOB


//��� USART3
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

//������� ��� ��������� RISC
//static void risc_Uart_1_Config(void);
//static void risc_Uart_2_Config(void);
  static void risc_Uart_3_Config(void);   //��� ���������� ����� STM32F



//static void risc_AdcConfig(void);
//static void risc_Rtc_and_BkpConfig(void);
//static void risc_Timer1Config(void);
//static void risc_ExternalBusConfig(void);

/**************************************************************************************************
Syntax:             Init_ARM(void)
Parameters:         none
Remarks:            ��������� ������� �������������
Return Value:       none
***************************************************************************************************/
void Init_ARM()
{
	   /*Main Initialization Function*/
     // ClockConfig();  	//������������� ������� ������ CPU 1986��91�
      PortsConfig();  	//������������� ������ 1986��91�
    /*��������� �������������*/
     // SysTimerConfig(); //������������� ���������� ������� ARM ����

    /*������������� ������������ ������  RISC ����*/
     // risc_Uart_1_Config();
     // risc_Uart_2_Config();
	      risc_Uart_3_Config();
	 
																	 //UART1 and UART2 config
    //risc_Timer1Config();         //Risc Timer1
    //risc_AdcConfig();            //���
    //risc_Rtc_and_BkpConfig();    //Real_Time_clock_and_BKP
    //risc_ExternalBusConfig();     //������������ ������� ��������� ����

    /*������������� ������������ ������  DSP ����*/


}


/**************************************************************************************************
Syntax:             void ClockConfig()
Parameters:         none
Remarks:            ���������� ��������� ��������� ������� ����� ������������ ���� RST_CLK.
                    ��� ��������� ������� ��������������� ����������� �� ������� HSI ����������.
                    ������ �������� �������� ������������� ��� ���� ������������ ������ ����� RST_CLK ���������.
                    ��� ������ ������ � ������ ������������ ������ ���������� �������� ��� �������� �������
                    � �������� PER_CLOCK. ��������� ����������� ����������� (UART, CAN, USB, �������)
                    ����� �������� �� �������� �������� �� ������� ������������� ����, �� ����� � ���������������
                    ��������� (UART_CLOCK, CAN_CLOCK, USB_CLOCK, TIM_CLOCK) ����� ���� ������ �� �������� ������.
Return Value:       none
***************************************************************************************************/
void ClockConfig()
{




}


/**************************************************************************************************
Syntax:             void PortsConfig()
Parameters:         �������� ������ �� 1901��1T
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

	
	
	
 ///////////////////////////////////////////PORT_� CONFIG ��� UART3////////////////////////////////////////////////////////////
	  RCC_AHB1PeriphClockCmd(Open_USART_TX_GPIO_CLK,ENABLE);
    RCC_AHB1PeriphClockCmd(Open_USART_RX_GPIO_CLK,ENABLE);
 
  //��� UART3	
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
Parameters:         ������������� ���������� ������� ARM ����
Remarks:            ��������� ������ � ��� 24 ���� ������������ ����� ����� ������� �� ����� ���� ���������.
Return Value:       none
***************************************************************************************************/
void SysTimerConfig()
{



}


/**************************************************************************************************
Syntax:             static void risc_Uart_3_Config()
Parameters:         ���������������� UART3
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









