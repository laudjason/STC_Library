/******************************************************************
*    			STC-51��/STC-51 library file
*
*�ļ���/file    : c51_uart.h
*
*����/function  : C51��uart����
*
*Э��/licence   : GPL��Դ/open GPL
*
*����/author    : J.H.Chen
*
*ʱ��/time      : 2015-06-12
*
*˵��/other     : 
******************************************************************/
#ifndef __C51_UART_H
#define __C51_UART_H

#include "stdint.h"

#ifndef EOF
#define EOF  ((int)-1)
#endif



#define BUF_SIZE    64


typedef struct
{
	unsigned char sndIndex;   //�����ַ�ָ��
	unsigned char sndCount;   //���ͼ�����
	char sndBuf[BUF_SIZE];    //���ͻ�����

    unsigned char readIndex;  //���ַ�ָ��
	unsigned char revCount;	  //���ռ�����
	unsigned char byteWaitRead;  //�ȴ��û������ַ�����
	char revBuf[BUF_SIZE];    //���ջ�����
}serialObj_Def;


void UartInit(uint32 baudrate);

void UartwriteChar(char ch);

void UartwriteStr(char *str, unsigned char num);

bool UARTgetStr(char *str, unsigned char num);

unsigned char UARTgetByteNum();

int UartgetChar();	


#endif