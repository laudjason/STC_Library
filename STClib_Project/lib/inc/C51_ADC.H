/******************************************************************
*    			STC-51��/STC-51 library file
*
*�ļ���/file    : C51_ADC.h
*
*����/function  : C51��ADC�ļ�/adc file
*
*Э��/licence   : GPL��Դ/open GPL
*
*����/author    : J.H.Chen
*
*ʱ��/time      : 2015-05-28
*
*˵��/other     : ����ADC����
******************************************************************/
#ifndef __C51_ADC_H
#define __C51_ADC_H

#include "stdint.h"
#include "sys_type.h"


#define ADC_POWER  0X80
#define ADC_FLAG   0X10
#define ADC_START  0X08

#define ADC_CHANNEL_0   0
#define ADC_CHANNEL_1   1
#define ADC_CHANNEL_2   2
#define ADC_CHANNEL_3   3
#define ADC_CHANNEL_4   4
#define ADC_CHANNEL_5   5
#define ADC_CHANNEL_6   6
#define ADC_CHANNEL_7   7

#define ADC_SPEED_540CLOCK		0
#define ADC_SPEED_360CLOCK		1
#define ADC_SPEED_180CLOCK		2
#define ADC_SPEED_90CLOCK		  3


#ifdef LIB_ADC_USE
//��ȡADCת�����
uint16 GetADC_Result(uint8 Channel, uint8 ADC_Speed);
#endif

#endif