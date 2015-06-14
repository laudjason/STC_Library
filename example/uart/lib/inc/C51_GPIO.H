/******************************************************************
*    			STC-51��/STC-51 library file
*
*�ļ���/file    : c51_gpio.h
*
*����/function  : C51��GPIO�����ļ�
*
*Э��/licence   : GPL��Դ/open GPL
*
*����/author    : J.H.Chen
*
*ʱ��/time      : 2015-06-10
*
*˵��/other     : none
******************************************************************/
#ifndef __C51_GPIO_H
#define __C51_GPIO_H

#include "stdint.h"
#include "sys_type.h"


typedef enum
{ GPIO_Mode_PullUp = 0x00,      //����˫���
  GPIO_Mode_FLOATING = 0x02,    //��������,����
  GPIO_Mode_Out_OD = 0x04,      //��©���
  GPIO_Mode_Out_PP = 0x08,      //�������
}GPIOMode_TypeDef;

#define IS_GPIOMode_Type(GPIOMode)  ((GPIOMode==GPIO_Mode_PullUp) || (GPIOMode==GPIO_Mode_FLOATING) || \
																	   (GPIOMode==GPIO_Mode_Out_OD) || (GPIOMode==GPIO_Mode_Out_PP))

typedef enum
{ GPIO_P0 = 0x01,      //P0
  GPIO_P1 = 0x02,      //P1
  GPIO_P2 = 0x04,      //P2
  GPIO_P3 = 0x08,      //P3
	GPIO_P4 = 0x10,      //P4
  GPIO_P5 = 0x20,      //P5
}GPIO_TypeDef;

#define IS_GPIO_TYPE(GPIO_Type)  ((GPIO_Type==GPIO_P0) || (GPIO_Type==GPIO_P1) || \
																	(GPIO_Type==GPIO_P2) || (GPIO_Type==GPIO_P3) || \
																	(GPIO_Type==GPIO_P4) || (GPIO_Type==GPIO_P5))

typedef enum
{ Bit_RESET = 0,
  Bit_SET
}BitAction;


#define BIT(n)        (0x0001<<n)

#define	GPIO_Pin_0		0x01	//IO���� Px.0
#define	GPIO_Pin_1		0x02	//IO���� Px.1
#define	GPIO_Pin_2		0x04	//IO���� Px.2
#define	GPIO_Pin_3		0x08	//IO���� Px.3
#define	GPIO_Pin_4		0x10	//IO���� Px.4
#define	GPIO_Pin_5		0x20	//IO���� Px.5
#define	GPIO_Pin_6		0x40	//IO���� Px.6
#define	GPIO_Pin_7		0x80	//IO���� Px.7
#define	GPIO_Pin_All	0xFF	//IO��������

typedef struct
{
  uint8 GPIO_Pin;     //GPIO��        

  GPIOMode_TypeDef GPIO_Mode;  //GPIOģʽ
	
}GPIO_InitTypeDef;


#define GPIO_Write_Pin_reg(Px,GPIO_Pin,val)   {if((val) == Bit_RESET) \
																							Px &= ~(GPIO_Pin); \
																						else                 \
																							Px |= (GPIO_Pin);} 

#define GPIO_Read_Pin_reg(Px,GPIO_Pin)    ((Px & GPIO_Pin)?Bit_SET:Bit_RESET)
																						
																						
																						
#ifdef  LIB_GPIO_USE																						
void GPIO_Init(GPIO_TypeDef GPIO, GPIO_InitTypeDef* GPIO_InitStruct); //GPIO��ʼ��
#endif

#define GPIO_Write_Pin(Px,GPIO_Pin,val)  GPIO_Write_Pin_reg(Px,GPIO_Pin,val)  //GPIO����д,��д������,ע��PxΪsfr�����P1~P5
																							
#define GPIO_Read_Pin(Px,GPIO_Pin)   GPIO_Read_Pin_reg(Px,GPIO_Pin)           //GPIO���Ŷ�,ֻ��������,����״̬����,ע��PxΪsfr�����P1~P5


#endif