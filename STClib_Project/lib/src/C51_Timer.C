/******************************************************************
*    			STC-51��/STC-51 library file
*
*�ļ���/file    : c51_timer.c
*
*����/function  : C51�ⶨʱ���ļ�
*
*Э��/licence   : GPL��Դ/open GPL
*
*����/author    : J.H.Chen
*
*ʱ��/time      : 2015-06-10
*
*˵��/other     : ��ʱ��ʹ�ö�ʱ��0,�����޸Ķ�ʱ��0��ش���
******************************************************************/
#include "C51_Lib.h"

#define TL0_1  0xE0		//��ʱ��ֵ
#define TH0_1  0xB1		//��ʱ��ֵ


static struct
{
	unsigned int base;
  unsigned int cnt;
	unsigned char isOverflow;
	unsigned char isEnable;
}delayType;

static uint16 base;
static timer0_t  *timer_list,*p;
static timer0_t timer_head;
/******************************************************************************
 * FunctionName : timer0init
 * Description  : ��ʱ��0��ʼ��
 * Parameters   : none
 * Returns      : none
 * Other        : 16λ�Զ�����ģʽ  1msʱ��
*******************************************************************************/
void timer0init()
{
	base = 65535-CPU_FAN/12000.0;
	AUXR &= 0x7F;		//12T��ʱ��ģʽ
	TMOD &= 0xF0;		
	TMOD |= 0x01;		
	TL0 = (uint8)(base&0x00FF);		
	TH0 = base>>8;		
	TF0 = 0;		
	TR0 = 1;
	
	timer_head.next = NULL; //����ͷ���洢��Ϣ
	timer_list = &timer_head;
	
	ET0 = 1;
	EA = 1;
}

/******************************************************************************
 * FunctionName : timer0handler
 * Description  : ��ʱ��0�жϴ���, 1msʱ�䶨ʱ��
 * Parameters   : none
 * Returns      : none
 * Other        : none
*******************************************************************************/
static void timer0handler()interrupt VECTOR_TIM0
{
	TL0 = (uint8)(base&0x00FF);		
	TH0 = base>>8;
	
  p = timer_list;
	
	while(p->next != NULL)//��������ͷ
	{
		if(++(p->next->cnt) >= p->next->period)
		{
			p->next->Timer0Func(p->next->timer_arg);
			if(p->next->Timer_Status == Timer_Status_repeat) 
				p->next->cnt = 0;
			else  //���ζ�ʱ����,�����
				p->next = p->next->next;
		}
		p = p->next;
	}
	
	if(delayType.isEnable==1 && ++delayType.cnt >= delayType.base)  
	{
		delayType.isEnable = 0;  //�ر���ʱ��
		delayType.isOverflow = 1; //��λ���λ
	}
	
}


/******************************************************************************
 * FunctionName : delay_ms
 * Description  : ���뼶��ʱ
 * Parameters   : ms - ��ʱʱ�� ms
 * Returns      : ���-1ms
*******************************************************************************/
void delay_ms(uint16 ms)
{
	TR0 = 0;		//��ʱ��0��ʼ��ʱ
	delayType.base = ms;
	delayType.cnt = 0;
	delayType.isOverflow = 0;
	delayType.isEnable = 1;
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	while(delayType.isOverflow == 0);
}


/******************************************************************************
 * FunctionName : timer_disarm
 * Description  : ��ʱ��ȡ�����ܰ�
 * Parameters   : timer--�Ѿ�����Ĺ��ܱ���
 * Returns      : ���-1ms
*******************************************************************************/
void timer_disarm(timer0_t *timer)
{
	p = timer_list;
	while(p->next != NULL)  //��������ͷ
	{
		if(p->next == timer)
		{
			p->next = p->next->next; //�˴�����ָ����,��Ϊnode������ʱ��NEXTָ���Ѿ���NULL
			return;
		}
		p = p->next; //����
	}
}

/******************************************************************************
 * FunctionName : timer_arm
 * Description  : ��ʱ�����ܰ�
 * Parameters   : timer--�Ѿ�����Ĺ��ܱ���   period--��ʱ����,ms
                  Timer_Status--����ģʽ,���ζ�ʱ�����ظ���ʱ
 * Returns      : ���-1ms
*******************************************************************************/
void timer_arm(timer0_t *timer, uint32 period, Timer_Status_Def Timer_Status)
{
	p = timer_list;
	while(p->next != NULL) 
		p = p->next; //����
	
	timer->next = NULL;
	timer->period = period;
	timer->cnt = 0; 
	timer->Timer_Status = Timer_Status;
	
	p->next = timer;
}

/******************************************************************************
 * FunctionName : timer_setfn
 * Description  : ��ʱ�����ܰ󶨶�Ӧ����
 * Parameters   : timer--�Ѿ�����Ĺ��ܱ���   *timerfn--����ָ��
                  timer_arg--����Ԥ�����
 * Returns      : ���-1ms
*******************************************************************************/
void timer_setfn(timer0_t *timer, sysTimer0Func *timerfn, uint8 timer_arg)
{
	timer->Timer0Func = timerfn;
	timer->timer_arg = timer_arg;
}