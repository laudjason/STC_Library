/******************************************************************
*    			STC-51��/STC-51 library file
*
*�ļ���/file    : c51_eeprom.c
*
*����/function  : C51��eeprom����
*
*Э��/licence   : GPL��Դ/open GPL
*
*����/author    : J.H.Chen
*
*ʱ��/time      : 2015-06-12
*
*˵��/other     : 
******************************************************************/
#include "C51_Lib.h"
#include <intrins.h>

#ifdef LIB_EEPROM_USE
/******************************************************
 * FunctionName : DisableEEPROM
 * Description  : ��ֹ����EEPROM
 * Parameters   : none
 * Returns      : none
******************************************************/
void	EEPROM_Disable(void)
{
	IAP_CONTR = 0;			//��ֹIAP/IAP����
	IAP_CMD   = 0;			//ȥ��IAP/IAP����
	IAP_TRIG  = 0;			//��ֹIAP/IAP�����󴥷�
	IAP_ADDRH = 0xff;		//��0��ַ���ֽ�
	IAP_ADDRL = 0xff;		//��0��ַ���ֽڣ�ָ���EEPROM������ֹ�����
}


/******************************************************
 * FunctionName : EEPROM_read
 * Description  : EEPROM��������
 * Parameters   : addr--Ҫ��ȡ��ַ  buf--�洢������
                  num--��ȡ�ֽ���
 * Returns      : none
******************************************************/
void EEPROM_read(uint16 addr, uint8 *buf, uint16 num)
{
	EA = 0;	
	IAP_CONTR = ENABLE_IAP;	 //����EEP����
	IAP_CMD = EEPROM_READ;	 //�ɶ�
	do
	{
		IAP_ADDRH = addr / 256;		//�͵�ַ���ֽڣ���ַ��Ҫ�ı�ʱ���������͵�ַ��
		IAP_ADDRL = addr % 256;		//�͵�ַ���ֽ�
		IAP_TRIG = 0X5A;
		IAP_TRIG = 0XA5;						
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		*buf = IAP_DATA;
		addr++;
		buf++;
	}while(--num);

	EEPROM_Disable();
	EA = 1;	
}


/******************************************************
 * FunctionName : EEPROM_read
 * Description  : EEPROM��������
 * Parameters   : addr--Ҫд��ĵ�ַ  buf--�洢������
                  num--д���ֽ���
 * Returns      : none
******************************************************/
void EEPROM_write(uint16 addr,uint8 *buf,uint16 num)
{
	EA = 0;	

	IAP_CONTR = ENABLE_IAP;	 //����EEP����
	IAP_CMD = EEPROM_WRITE;	 //��д
	do
	{
		IAP_ADDRH = addr / 256;		//�͵�ַ���ֽ�
		IAP_ADDRL = addr % 256;		//�͵�ַ���ֽ�
		IAP_DATA  = *buf;			//�����ݵ�IAP_DATA
		IAP_TRIG = 0X5A;
		IAP_TRIG = 0XA5;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		addr++;
		buf++;
	}while(--num);

	EEPROM_Disable();
	EA = 1;		
}



/******************************************************
 * FunctionName : EEPROM_SectorErase
 * Description  : EEPROM��������
 * Parameters   : addr--Ҫ�����ĵ�ַ
 * Returns      : none
******************************************************/
void EEPROM_SectorErase(uint16 addr)
{
	EA = 0;	
	
	IAP_CONTR = ENABLE_IAP;	 //����EEP����
	IAP_CMD = EEPROM_ERASE;	 //�ɶ�
	IAP_ADDRL = addr;
	IAP_ADDRH = addr>>8;
	IAP_TRIG = 0X5A;
	IAP_TRIG = 0XA5;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	EEPROM_Disable();
	EA = 1;	
}
#endif