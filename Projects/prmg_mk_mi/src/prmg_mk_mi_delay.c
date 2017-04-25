 /**********************************************************************************************************************
*                                        (c) COPYRIGHT by PAO Inteltech.                                             *
*                                               All rights reserved.                                                  *
***********************************************************************************************************************
* Module      : bky_arm_delay.c
* Description : ������� ������ � ���������� � �������
* Author      : Konstantin Shiluaev
******************************************************************************
******************************************************************************
* Module's Description Record:
* ============================
* $State: Debug$
* $Revision: 0.0.1 $
* $Date: 2015/03/02 10:40:51 $
******************************************************************************/
//  #include "stm32f4xx_conf.h"
#include "stm32f4xx.h"

//#include "stdint.h"
#include "prmg_mk_mi_delay.h"


//�������
#define timer_05sec_delay_24      0x00B71B00   //12 000 000[�����]   = 0.5   [������]  ��� �������  TIM_CLK1 = 24[���]  | Systimer[HCLK] = 24 [���]
#define timer_0125sec_delay_96    0x00B71B00   //12000000[�����]   = 0.125 [������]  ��� �������  Systimer[HCLK] = 96 [���]

//������������
#define timer_1ms_delay_24        0x00005DC0   //24000 �����       = 1 [��]  ��� ������� TIM_CLK1 = 24[���]  | Systimer[HCLK] = 24 [���]
#define timer_1ms_delay_96        0x00017700   //96000 �����       = 1 [��]  ��� ������� Systimer[HCLK] = 96 [���]
//������������
#define  timer_1mks_delay_21      0x00000015

#define timer_1mks_delay_24       0x00000018   //24    ����        = 1 [���] ��� ������� TIM_CLK1 = 24[���]   | Systimer[HCLK] = 24 [���]
#define timer_10mks_delay_24      0x000000F0   //240   �����       = 10 [���] ��� ������� TIM_CLK1 = 24[���]  | Systimer[HCLK] = 24 [���]
#define timer_100mks_delay_24     0x00000960   //2400  �����       = 100[���] ��� ������� TIM_CLK1 = 24[���]  | Systimer[HCLK] = 24 [���]
 
#define timer_1mks_delay_96       0x00000060;  //96    �����       1 [���] ��� ������� Systimer[HCLK] = 96 [���]


//------------------------------------------------------------------------------------------------------------------
/* CTRL TICKINT Mask */
//static uint8_t  delay_fac_us = 1;
//static uint16_t delay_fac_ms = 1;
static FlagStatus  Status;
uint32_t _delay=0UL;


/*****************************************************************************/
/*  PRIVATE FUNCTIONS                                                        */
/*****************************************************************************/
static  void SysTick_CLKSourceConfig(unsigned int SysTick_CLKSource);   //������ ���� ������
static  void SysTick_SetReload(unsigned int Reload);                    //������ ���� ������
static  void SysTick_CounterCmd(unsigned int SysTick_Counter);          //������ ���� ������ 
static  FlagStatus SysTick_GetFlagStatus(unsigned char SysTick_FLAG);   //������ ���� ������ 



#define CTRL_TICKINT_Set      ((unsigned int)0x00000002)
#define CTRL_TICKINT_Reset    ((unsigned int)0xFFFFFFFD)


#define IS_SYSTICK_CLK_SOURCE(SOURCE) (((SOURCE) == SysTick_CLKSource_HCLK) || \
                                       ((SOURCE) == SysTick_CLKSource_HCLK_Div8))

/* SysTick counter state */
#define SysTick_Counter_Disable        ((unsigned int)0xFFFFFFFE)
#define SysTick_Counter_Enable         ((unsigned int)0x00000001)
#define SysTick_Counter_Clear          ((unsigned int)0x00000000)

#define IS_SYSTICK_COUNTER(COUNTER) (((COUNTER) == SysTick_Counter_Disable) || \
                                     ((COUNTER) == SysTick_Counter_Enable)  || \
                                     ((COUNTER) == SysTick_Counter_Clear))

/* SysTick Flag */
#define SysTick_FLAG_COUNT             ((unsigned int)0x00000010)
#define SysTick_FLAG_SKEW              ((unsigned int)0x0000001E)
#define SysTick_FLAG_NOREF             ((unsigned int)0x0000001F)

#define IS_SYSTICK_FLAG(FLAG) (((FLAG) == SysTick_FLAG_COUNT) || \
                               ((FLAG) == SysTick_FLAG_SKEW)  || \
                               ((FLAG) == SysTick_FLAG_NOREF))

#define IS_SYSTICK_RELOAD(RELOAD) (((RELOAD) > 0) && ((RELOAD) <= 0xFFFFFF))

//-------------------------------------------------------------------------------------------------------------------





///////////////////������ � ��������� ��������////////////////////
/**************************************************************************************************
Parameters:         void sys_timer_start_en_irq(uint8_t second)
Remarks:            �������� ��������� ������ � ���������� ����������
***************************************************************************************************/
void sys_timer_start_en_irq()
{
    //�������� ������
    SysTick->CTRL=0x00000007;  //CLKSOURCE = HCLK =96|24|8|  [���]  � ����������� �� �������������.
                               //TICKINT=1 Enable  //���������� ���������
	                             //ENABLE =1
}

/**************************************************************************************************
Parameters:         void sys_timer_start_dis_irq(uint16_t  millisecond)
Remarks:            �������� ��������� ������ ��� ����������
***************************************************************************************************/
void sys_timer_start_dis_irq()
{
    SysTick->CTRL=0x00000005;  //CLKSOURCE = HCLK =96|24|8|  [���]  � ����������� �� �������������.
                               //TICKINT=0 Enable  //���������� ���������
	                             //ENABLE =1
}

/**************************************************************************************************
Parameters:         void sys_timer_stop ()
Remarks:            ������������� ��������� ������
***************************************************************************************************/
void sys_timer_stop ()
{
    SysTick->CTRL=0x00000004;//~SysTick_CTRL_ENABLE_Msk;
}


/**************************************************************************************************
Parameters:         void sys_timer_get_tick ()
Remarks:            ���������� �������� �������� ���� �� ��������
***************************************************************************************************/
unsigned int sys_timer_get_tick(void)
{
	return  SysTick->VAL;
}	


/**************************************************************************************************
Parameters:         void sys_timer_second_delay ()
Remarks:            ���������� �������� �������� ���� �� ��������
***************************************************************************************************/
void sys_timer_second_delay (unsigned short second)
{
	   	   second=second*2;   //��� 24 [���]
        //second=second*8;   //��� 96 [���]
	      while(second!=0)
        {  	       
          //����� ������� �������� 1 [��]      ��� //������� 24 [���]
					  sys_timer_delay_ticks(timer_05sec_delay_24);
					//����� ������� �������� 1 [��]      ��� //������� 96 [���]  
					//sys_timer_delay_ticks(timer_0125sec_delay_96); 
				second--;
				}
	    
	
}	



/**************************************************************************************************
Parameters:         void sys_timer_millisecond_delay ()
Remarks:            ���������� �������� �������� ���� �� ��������
***************************************************************************************************/
void sys_timer_millisecond_delay (unsigned short millisecond)
{
	      while(millisecond!=0)
        {  	       
					//����� ������� �������� 1 [��]      ��� //������� 24 [���]
					 sys_timer_delay_ticks(timer_1ms_delay_24);
					//����� ������� �������� 1 [��]      ��� //������� 96 [���]  
					//sys_timer_delay_ticks(timer_05sec_delay_96);
					millisecond--; 
				}
	
}	

/**************************************************************************************************
Parameters:         void sys_timer_microsecond_delay ()
Remarks:            ���������� �������� �������� ���� �� ��������
* 									���� ������� �������� ����������� � ����������� 10 ��� 
* 									�� ���� �� ������ �������� 1 �� �������� ���  * 10 = 10 ��� 
* 									������������� 
										2 = 20 [���]                                ��� CPU =168 [���]  ���������� ������� 2 [���]
*               		3 = 30 [���]
										4 = 40 [���] 
										68 = 680 [���] 
										100 * 10 = 1000 [���] 

***************************************************************************************************/
void sys_timer_microsecond_delay (unsigned short microsecond)
{
	        while(microsecond!=0)
          {  	       
         	//����� ������� �������� 1 [��]      ��� //������� 24 [���]
					//sys_timer_delay_ticks(timer_100mks_delay_24);
					 // sys_timer_delay_ticks(timer_1mks_delay_24);
					   sys_timer_delay_ticks (timer_1mks_delay_21);
					//����� ������� �������� 1 [��]      ��� //������� 96 [���]  
					//sys_timer_delay_ticks(timer_05sec_delay_96); 
				 	 microsecond--; 
			 	  }

}	

/*******************************************************************************
* Function Name  : SysTick_GetCounter
* Description    : Gets SysTick counter value.
* Input          : None
* Output         : None
* Return         : SysTick current value
*******************************************************************************/
unsigned int sys_timer_getcounter(void)
{
  return(SysTick->VAL);
}



/*******************************************************************************
* Function Name  : SysTick_SetReload
* Description    : Sets SysTick Reload value.
* Input          : - Reload: SysTick Reload new value.
*                    This parameter must be a number between 1 and 0xFFFFFF.
* Output         : None
* Return         : None
*******************************************************************************/
static  void SysTick_SetReload(unsigned int Reload)
{
  /* Check the parameters */
  //assert_param(IS_SYSTICK_RELOAD(Reload));

  SysTick->LOAD = Reload;
}


/*******************************************************************************
* Function Name  : SysTick_CounterCmd
* Description    : Enables or disables the SysTick counter.
* Input          : - SysTick_Counter: new state of the SysTick counter.
*                    This parameter can be one of the following values:
*                       - SysTick_Counter_Disable: Disable counter
*                       - SysTick_Counter_Enable: Enable counter
*                       - SysTick_Counter_Clear: Clear counter value to 0
* Output         : None
* Return         : None
*******************************************************************************/
static  void SysTick_CounterCmd(unsigned int SysTick_Counter)
{
  // Check the parameters 
  //assert_param(IS_SYSTICK_COUNTER(SysTick_Counter));

	switch(SysTick_Counter)
	{
		case SysTick_Counter_Enable:
		//SysTick->CTRL |= SysTick_Counter_Enable;
		//SysTick->CTRL=0x00000005;	//��� ������� ��������� �� CLK 96 [���]
    SysTick->CTRL=0x00000001;   //��� Cortex M4 HCLK 21 ���		
		break;
		
		
		case SysTick_Counter_Disable:
		SysTick->CTRL &= SysTick_Counter_Disable;	
		break;
		
		
		
		case SysTick_Counter_Clear:
    SysTick->VAL = SysTick_Counter_Clear;
    break;
		
		
		default:
		break;	
	}		
	

}

/*******************************************************************************
* Function Name  : SysTick_ITConfig
* Description    : Enables or disables the SysTick Interrupt.
* Input          : - NewState: new state of the SysTick Interrupt.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/

/*
static  void SysTick_ITConfig(FunctionalState NewState)
{
  // Check the parameters
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    SysTick->CTRL |= CTRL_TICKINT_Set;
  }
  else
  {
    SysTick->CTRL &= CTRL_TICKINT_Reset;
  }
}
*/


/*******************************************************************************
* Function Name  : SysTick_GetFlagStatus
* Description    : Checks whether the specified SysTick flag is set or not.
* Input          : - SysTick_FLAG: specifies the flag to check.
*                    This parameter can be one of the following values:
*                       - SysTick_FLAG_COUNT
*                       - SysTick_FLAG_SKEW
*                       - SysTick_FLAG_NOREF
* Output         : None
* Return         : None
*******************************************************************************/
static  FlagStatus SysTick_GetFlagStatus(unsigned char SysTick_FLAG)
{
  unsigned int statusreg = 0;
	
  FlagStatus bitstatus = RESET;

  // Check the parameters 
  //assert_param(IS_SYSTICK_FLAG(SysTick_FLAG));

  // Get the SysTick register index 
 // tmp = SysTick_FLAG >> 3;

  //if (tmp == 2) // The flag to check is in CTRL register 
  //{
    statusreg = SysTick->CTRL;
  //}
  //else          // The flag to check is in CALIB register 
  //{
  //  statusreg = SysTick->CALIB;
  //}

  if ((statusreg & ((unsigned int)1 << SysTick_FLAG)) != (unsigned int)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
 return bitstatus;
}








/////////////////////////////////////������ � �������� 1///////////////////////////////

/**************************************************************************************************
Parameters: void timer1_millisecond_delay(uint16_t  millisecond);       
Remarks:    ������� �������� ������������[1-1000  ��]    1000 ��  = 1 [���]         
***************************************************************************************************/

/**************************************************************************************************
Parameters: void timer1_microsecond_delay(uint16_t  microsecond);       
Remarks:    ������� �������� ������������[1-1000 ���]    1000 ��c = 1 [��]           
***************************************************************************************************/







/*******************************************************************************
* Function Name  : delay_systimers_ticks
* Description    : ������� ���������� �������� � ����� ���������� ������� � ����������� �� ������� HCLK �� ����������.
* Input          : ������ 24 ��������� ������������ �������� ����� 0x00FFFFFF [16 777 215]
* Output         : 
* Return         : 
* Attention		   : 
*******************************************************************************/  
void sys_timer_delay_ticks(unsigned int ticks)
{    
    
    if (ticks > 0x00ffffff)
    {
        ticks = 0x00ffffff;
    }
     
		SysTick_SetReload(ticks);
    SysTick_CounterCmd(SysTick_Counter_Clear);
    SysTick_CounterCmd(SysTick_Counter_Enable);
    do
    {
        Status = SysTick_GetFlagStatus(SysTick_FLAG_COUNT);
    }while (Status != SET);
    SysTick_CounterCmd(SysTick_Counter_Disable);
	  SysTick_CounterCmd(SysTick_Counter_Clear);
}



/**************************************************************************************************
Parameters:  void while_delay(uint32_t  counter);       
Remarks:    //�������� � ������� ������� ��� ������ ��������� (�����)  c������ ����� 1 while                                         
																				//while						 [24 ���]            -  ��������� *4     [96 ���]    					��������� *7	[168 ���]
 																					//1    =    	   ~1 ���      -          		 280 [��]								           ~ 160  [��]
																					//10   =    	   ~3 ���      -
																					//100  =    	   ~20 ���     -          														  				 ~ 2.5  [���]	
																					//500  =  	     ~80 ���     -               20   [���]    
																					//800  =  	     ~140 ���    -
																					//1000 =  	     ~170 ���    -               42.5 [���]                        ~  24 [���]    +
***************************************************************************************************/
void while_delay(uint32_t  counter)
{
	
	      while(counter!=0)
        {  	       
					counter--; 
				}
	
}	


/**************************************************************************************************
Parameters: void timer1_microsecond_delay(uint16_t  microsecond);       
Remarks:    ������� �������� ������������[1-1000 ���]    1000 ��c = 1 [��]           
***************************************************************************************************/
void Delay_akimov(uint32_t time, char type)
{
  switch (type)
  {
  case 'n':
    time = (uint32_t)((time * 168)/100);//_core_freq/1E7;
    while (time != 0)
      {
        time--;
      }
    break;
  case 'u':
    time = (uint32_t)((time * 168)/10);//_core_freq/1E6;
    while (time != 0)
      {
        time--;
      }
    break;
  case 'm':
    _delay = time;
    while (_delay != 0);
    break;
  case 's':
    _delay = time * 1000;
    while (_delay != 0);
    break;
  default:
    _delay = time;
    while (_delay != 0);
    break;
  }

}









/////////////////////////////////////������ � �������� 2///////////////////////////////
/**************************************************************************************************
Parameters:        
Remarks:            
***************************************************************************************************/




/**************************************************************************************************
Parameters:        
Remarks:            
***************************************************************************************************/
/////////////////////////////////////������ � �������� 3///////////////////////////////















