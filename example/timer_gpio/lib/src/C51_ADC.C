/******************************************************************
*    			STC-51��/STC-51 library file
*
*�ļ���/file    : C51_ADC.C
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
#include "C51_Lib.h"

#ifdef PROJECT_USE_AD
/******************************************************
 * FunctionName : GetADC_Result
 * Description  : ��ȡADC��ֵ
 * Parameters   : Channel--ͨ��  ADC_Speed--�����ٶ�
 * Returns      : ADCת�����
******************************************************/
uint16 GetADC_Result(uint8 Channel, uint8 ADC_Speed)
{
	uint8 m1,m0,ASF,a;
	m1 = P1M1;
	m0 = P1M0;
	ASF = P1ASF;

	if(Channel >= ADC_CHANNEL_0 && Channel <= ADC_CHANNEL_7)
	{
		P1M1 |=	(0x01 << Channel);
		P1M0 &=	~(0x01 << Channel);
		P1ASF |= (0x01 << Channel); 
		ADC_CONTR = ADC_POWER | (ADC_Speed<<5) | Channel;
		ADC_CONTR |= ADC_START;
		for(a = 100; a > 0; a--);
		while(!(ADC_CONTR & ADC_FLAG));
		ADC_CONTR &= ~ADC_FLAG; 
		ADC_CONTR &= ~ADC_POWER;

		P1M1 = m1;
		P1M0 = m0;
		P1ASF = ASF;

		return ((uint16)ADC_RES << 2 | ADC_RESL);
	}
	
	return 0;	
}

#endif