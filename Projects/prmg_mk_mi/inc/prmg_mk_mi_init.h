/**********************************************************************************************************************
*                                        (c) COPYRIGHT by AO NPK Pelengator.                                             *
*                                               All rights reserved.                                                  *
***********************************************************************************************************************
* Module      : bky_arm_init.h
* Description :
* Author      : Konstantin Shiluaev
******************************************************************************
******************************************************************************
* Module's Description Record:
* ============================
* $State: Debug$
* $Revision: 0.0.0 $
* $Date: 2015/01/14 10:40:51 $
******************************************************************************/
#ifndef __TIS10_AS_INIT_H
#define __TIS10_AS_INIT_H

#ifdef __cplusplus
extern "C" {
#endif


//����� ����������� CPU 1986��91�
   
//�������� ������� RISC ����	
 //   #define RISC_DSP_8MHz   1
 //     #define RISC_DSP_24MHZ  1
 //   #define RISC_DSP_96MHz  1

/*����������� ���������� �������*/
//������� �������� ������� ��� ��������� ������ ��� ������������� � DSP ����� ������ �� ������ ������ 16 ��������� ������.
//  #define SYSTIMER_24_BIT                  1
//#define SYSTIMER_16_BIT                  1
 
	
	
	//��� ���������� ������
  //#define SYSTIMER_MICROSECOND           1   //������������
  //#define SYSTIMER_MILLISECOND           1   //������������
  //  #define SYSTIMER_SECOND                1   //�������
 




//////��������� ������� �������������

//��������� ������� �������������.
  void    Init_ARM(void);


//������ �������
#ifdef __cplusplus
}
#endif










#endif /*__SYSTEM_MDR32F9Qx_H */

