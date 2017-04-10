/**********************************************************************************************************************
*                                        (c) COPYRIGHT by AO NPK PELENGATOR.                                          *
*                                               All rights reserved.                                                  *
***********************************************************************************************************************
* Module      : bky_arm_delay.h
* Description : ������ � ���������� 1986��91�
* Author      : Konstantin Shiluaev
******************************************************************************
******************************************************************************
* Module's Description Record:
* ============================
* $State: Debug$
* $Revision: 0.0.0 $
* $Date: 2015/03/02 10:40:51 $
******************************************************************************/
#ifndef __TIS10_AS_DELAY_H
#define __TIS10_AS_DELAY_H

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif


    /*
    *   0x00249EFF =  2 399 999  �����[������������_������]  �������_hclk = 96 [���]     =  96 000 000 [��]
    * ,����� 1 ���������� = 0,024[���] =  24[��]     =0.024*100    =   2.4[������].
    *
    *   0x00249EFF =  2 399 999  �����[������������_������]  �������_hclk = 24 [���]  =   24 000 000 [��]
    * ,����� 1 ���������� = 0,1[���] =  100[��]      =0.1*100    =   10 [������].
    *
    *  0x00249EFF =  2 399 999  �����[������������_������]  �������_hclk = 8 [���]   =   8 000 000 [��]
    * ,����� 1 ���������� = 0,299[���] = 299[��]   =0.299*100  =    30 [������].
    *
    *  0x00249EFF =  2 399 999  �����[������������_������]  �������_hclk = 40 000 [��]  ��������� LSI
    * ,����� = 59,999[���].
    *
    *  -----------------------------------------------------------------------------------------------------
    *  ��� ���� ����� � ��� ������� ��������� ������� ��� DSP � RISC ���������� ������������ ������ = 0xFFFF = 65535
    *  0xFFFF = 65535 �����[������������_������]  �������_hclk = 24 [���] = 24 000 000 [��]
    *  ����� 1 ���������� = 0.002730625 [c] = 2.730625 [��] //24 [���]
    *                       0.008191875 [c] = 8.191875 [��] //8  [���]
    *                       0.000682656 [c] = 0.68265  [��] //96 [���]
   


    *  //�������������� ����� ���������� 1[��] � 1 ���
    *  ��� ���� ����� � ��� ������� ��������� ������� ��� DSP � RISC ���������� ������������ ������ = 0x5DC0 = 24000
    *  �������_hclk = 24 [���] = 24 000 000 [��]
    *
    *         ����� 1 ���������� = 0.001 [c] =    1 [��] //24 [���]
    *  ��� ���� ����� � ��� ������� ��������� ������� ��� DSP � RISC ���������� ������������ ������ = 0x0018 = 24
    *         ����� 1 ���������� = 0.000001 [c] = 1 [���] //24 [���]
    *
    *  ��������(delay):
    *
    *
    *  ��������������� ������� ��� ��������: �����[�] = [������������ �����] /[�������]
    *  �������� =  16 777 215 �����   = 0.699 [������]  ��� 24 [���]
    *
    *  ��������������� ������� ��� ��������: �����[�] = [������������ �����] /[�������]
    *  �������� =  65535 �����   = 0.002730625 [������]  ��� 24 [���]
    *              24000 �����   = 0.001 [������]  =1 [��] ��� 24 [���]
    */

 /////////////////////////////////////������ � ��������/////////////////////////////////////////////
/*����������� ����� ���������� ��������� ����� <-> ������� ���������� ������� SYSTICK*/
// SYS->STRVR     <<<->>>   SysTick->LOAD
// SYS->STCSR     <<<->>>   SysTick->CTRL
// SYS->STCVR     <<<->>>   SysTick->VAL   ������� �������� ���������� �������





/*��� 24 ��������� ������ ����������*/
//������� ������ ������� ����� �������� � ������� ������� �� �������� ���� ��������.
//��� ������� 8  ���   1[c��]    =(0x7A1200)8000000 [ticks] ,1[��]  = 0x1F40 (8000) [ticks] , 1[���] =0x0008(8) [ticks]
//��� ������� 24 ���   0.5[c��]  =(0xB71B00)12000000[ticks] ,1[��]  = 0x5DC0 (24000)[ticks] , 1[���] =0x0018(24)[ticks]




//��� ������� 96 ���   0.125[c��]=(0xB71B00)12000000[ticks] ,1[��]  = 0x17700(96000)[ticks] , 1[���] =0x0060(96)[ticks]

//����������� �������.                /*���������� ����������*/
//��� ������� 24  ���   1[���] = 0.5[���]  * (2);
//��� ������� 96  ���   1[���] = 0.125[���]* (8);



 ///////////////////////////������ ���������� �������/////////////////////////////////
 /*
 ����� ������ ���������� ������� ��������������� ��� ������������� �� ������ ������� ��� �������������
 ������ � bky_arm_delay.h  																			//#define SYSTIMER_MICROSECOND           1   //������������
																									//#define SYSTIMER_MILLISECOND           1   //������������
																									//#define SYSTIMER_SECOND                1   //�������
 � ����������� �� ��������� ������� ���������� ������������ ������� ��������������� �� HCLK=CPUC3 �.� �������� �
 �������� ���������� � ������� ������ �������� �� ������� 24 ��� ����� ���� �� ��������� ���������� �� ����������
 ������� ���� ���������� ������������� 1 ������������ =1 ���������;1 ������������ = 1 ���������� ; 0.5 ������ =1 ���������.
  */
 //


//������� ������ � �������� ���������������
/*������� �������� _������� */
void Delay_akimov(uint32_t time, char type);

/*������� �������� � ���������� while */
void while_delay(uint32_t  counter);
/*������� �������� ���������� ������� � ����� 0-16 777 215  ��� ������� 24 ��� 96 ��� */
void sys_timer_delay_ticks(unsigned int ticks);                   //



//������� ������ � ��������� �������� (SYSTIMER)
/*����� �������� ������� � ���������� ����������*/
void sys_timer_start_en_irq(void);
/*����� �������� ������� ��� ��������� ����������*/
void sys_timer_start_dis_irq(void);
/*��������� ���������� �������*/
void sys_timer_stop(void);  


/*������� ����� ������� ���*/
unsigned int sys_timer_get_tick(void);
/*������� �������� �������[1-60 ���]*/
void sys_timer_second_delay (unsigned short second);


/*������� �������� ������������[1-1000 ���]*/
void sys_timer_millisecond_delay (unsigned short millisecond);


/*������� �������� ������������[1-1000 ���]
* ���� ������� �������� ����������� � ����������� 10 ��� 
* �� ���� �� ������ �������� 1 �� �������� ���  * 10 = 10 ��� 
* ������������� 2 * 10 = 20 	  ��� 
*               3 * 10= 30 	    ���
                4 * 10= 40      ��� 
                68* 10 = 680    ��� 
                100 * 10 = 1000 ��� 
*/
void sys_timer_microsecond_delay (unsigned short microsecond);

/*���� ������� ���������� ����� �� ��������*/
unsigned int sys_timer_getCounter(void);                         




///////////////////////////������ c 16 ��������� ��������_1  /////////////////////////

///////////////////////////������ c 16 ��������� ��������_2 /////////////////////////

///////////////////////////������ c 16 ��������� ��������_3 /////////////////////////
//������ ������ � ��� ����� ������ �������������










 //������ �������
#ifdef __cplusplus
}
#endif




#endif //BKY_ARM_DELAY_H






