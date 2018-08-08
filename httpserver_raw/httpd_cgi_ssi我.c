#include "lwip/debug.h"
#include "httpd.h"
#include "lwip/tcp.h"
#include "fs.h"
#include "config.h"
//#include "led.h"
//#include "pcf8574.h"
//#include "adc.h"
//#include "rtc.h"
//#include "lcd.h"
#include <string.h>
#include <stdlib.h>
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F4&F7������
//http ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/8/5
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//*******************************************************************************
//�޸���Ϣ
//��Ϊ��Ҫ��TQ2440�İ汾
////////////////////////////////////////////////////////////////////////////////// 	   
 

#define NUM_CONFIG_CGI_URIS	2  //CGI��URI����
#define NUM_CONFIG_SSI_TAGS	4  //SSI��TAG����
//����LED��BEEP��CGI handler
const char* LEDS_CGI_Handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);
const char* BEEP_CGI_Handler(int iIndex,int iNumParams,char *pcParam[],char *pcValue[]);
int flag1=0;
int flag2=0;
static const char *ppcTAGs[]=  //SSI��Tag
{
	"h", //ʱ��
	"y", //����
	"w",//����ֵ
	"c"//Cpuռ����
	//"L"//lwip print
	
};

static const tCGI ppcURLs[]= //cgi����
{
	{"/leds.cgi",LEDS_CGI_Handler},
	{"/beep.cgi",BEEP_CGI_Handler},
};


//�ҵ�led��������
//��web�ͻ��������������ʱ��,ʹ�ô˺�����CGI handler����
static int FindCGIParameter(const char *pcToFind,char *pcParam[],int iNumParams)
{
	int iLoop;
	for(iLoop = 0;iLoop < iNumParams;iLoop ++ )
	{
		if(strcmp(pcToFind,pcParam[iLoop]) == 0)
		{
			return (iLoop); //����iLOOP
		}
	}
	return (-1);
}
//SSIHandler����Ҫ�õ��Ĵ��������cpuռ���ʶ���ֵ�ĺ���
void CPU_Handler(char *pcInsert)
{
	if(OSCPUUsage<100)
		*pcInsert = (char)(OSCPUUsage/100 +0x30);
	else
		*pcInsert = (char)(' ' +0x30);
	*(pcInsert+1) = (char)(OSCPUUsage/10 +0x30);
	*(pcInsert+2) = (char)(OSCPUUsage%10 +0x30);
}
//SSIHandler����Ҫ�õ��Ĵ������������ֵ�ĺ���
void Temperate_Handler(char *pcInsert)
{
    
    char Digit1=0, Digit2=0, Digit3=0, Digit4=0; 
    U32 ADCVal = 0;        

    //��ȡADC��ֵ
	ADCVal =ReadAdc(2); //��ȡADC1_CH2�ĵ�ѹֵ
	printf("ADCVal:%d",ADCVal);		
    //ת��Ϊ��ѹ ADCVval * 0.8mv
    ADCVal = (U32)(ADCVal * 0.8);  
    Digit1= ADCVal/1000;
    Digit2= (ADCVal-(Digit1*1000))/100 ;
    Digit3= (ADCVal-((Digit1*1000)+(Digit2*100)))/10;
    Digit4= ADCVal -((Digit1*1000)+(Digit2*100)+ (Digit3*10));
        
    //׼����ӵ�html�е�����
    *pcInsert       = (char)(Digit1+0x30);
    *(pcInsert + 1) = (char)(Digit2+0x30);
    *(pcInsert + 2) = (char)(Digit3+0x30);
    *(pcInsert + 3) = (char)(Digit4+0x30);
}
//SSIHandler����Ҫ�õ��Ĵ���RTCʱ��ĺ���
void RTCTime_Handler(char *pcInsert)
{
	int rHour, rMinute, rSecond;
	rHour = FROM_BCD(rBCDHOUR & 0x3f);
	rMinute = FROM_BCD(rBCDMIN & 0x7f);
	rSecond = FROM_BCD(rBCDSEC & 0x7f);
	*pcInsert = 	(char)((rHour /10) + 0x30);
	*(pcInsert+1) = (char)((rHour%10) + 0x30);
	*(pcInsert+2) = ':';
	*(pcInsert+3) = (char)((rMinute /10) + 0x30);
	*(pcInsert+4) = (char)((rMinute %10) + 0x30);
	*(pcInsert+5) = ':';
	*(pcInsert+6) = (char)((rSecond /10) + 0x30);
	*(pcInsert+7) = (char)((rSecond %10) + 0x30);
}

//SSIHandler����Ҫ�õ��Ĵ���RTC���ڵĺ���
void RTCdate_Handler(char *pcInsert)
{
	int rYear, rMonth, rDay, rDayOfWeek ;
	if (rBCDYEAR == 0x99)
		rYear = 1999;
	else
		rDayOfWeek = rBCDDATE - 1;
		rYear = (2000 + rBCDYEAR);
	rMonth = FROM_BCD(rBCDMON & 0x1f);
	rDay = FROM_BCD(rBCDDAY & 0x03f);
	*pcInsert = '2';
	*(pcInsert+1) = '0';
	*(pcInsert+2) = (char)((rYear /10)%10 + 0x30);
	*(pcInsert+3) = (char)((rYear %10) + 0x30);
	*(pcInsert+4) = '-';
	*(pcInsert+5) = (char)((rMonth /10)%10 + 0x30);
	*(pcInsert+6) = (char)((rMonth %10) + 0x30);
	*(pcInsert+7) = '-';
	*(pcInsert+8) = (char)((rDay /10)%10 + 0x30);
	*(pcInsert+9) = (char)((rDay %10) + 0x30);
	*(pcInsert+10) = ' ';
	*(pcInsert+11) = 'w';
	*(pcInsert+12) = 'e';
	*(pcInsert+13) = 'e';
	*(pcInsert+14) = 'k';
	*(pcInsert+15) = ':';
	*(pcInsert+16) = (char)(rDayOfWeek%10 + 0x30);
	
}
//SSI��Handler���
static u16_t SSIHandler(int iIndex,char *pcInsert,int iInsertLen)
{
	switch(iIndex)
	{
		case 0: 
			RTCTime_Handler(pcInsert);
			//Temperate_Handler(pcInsert);
				break;
		case 1:
			RTCdate_Handler(pcInsert);
			//RTCTime_Handler(pcInsert);
				break;
		case 2:
			Temperate_Handler(pcInsert);
			//RTCdate_Handler(pcInsert);
				break;
		case 3:
		    CPU_Handler(pcInsert);
				break;
	}
	return strlen(pcInsert);
}

//CGI LED���ƾ��
const char* LEDS_CGI_Handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
	int i=0;  //ע������Լ���GET�Ĳ����Ķ�����ѡ��iֵ��Χ
	iIndex = FindCGIParameter("LED1",pcParam,iNumParams);  //�ҵ�led��������
	//ֻ��һ��CGI��� iIndex=0
	if (iIndex != -1)
	{
		rGPBDAT = 0x1E0;  //�ر�LED��
		for (i=0; i<iNumParams; i++) //���CGI����
		{
		  if (strcmp(pcParam[i] , "LED1")==0)  //������"led" ���ڿ���LED1�Ƶ�
		  {
			  if (strcmp(pcValue[i], "LED1ON") == 0)  //�ı�LED1״̬
				  {LED_Display(1);
				  flag1=1;
				  }
				  
			else if(strcmp(pcValue[i],"LED1OFF") == 0)
				{rGPBDAT = 0x1E0; //�ر�LED
				flag1=0;
				}
		  }
		}
	 }
	if(flag1==0&&flag2==0)      return "/TQ2440_LED_ON_BEEP_ON.shtml";    //LED1��,BEEP��
	else if(flag1==0&&flag2==1) return "/TQ2440_LED_ON_BEEP_OFF.shtml";	  //LED1��,BEEP��
	else if(flag1==1&&flag2==1) return "/TQ2440_LED_OFF_BEEP_OFF.shtml";  //LED1��,BEEP��
	else return "/TQ2440_LED_OFF_BEEP_ON.shtml";   						  //LED1��,BEEP��					
}

//BEEP��CGI���ƾ��
const char *BEEP_CGI_Handler(int iIndex,int iNumParams,char *pcParam[],char *pcValue[])
{
	int i=0;
	iIndex = FindCGIParameter("BEEP",pcParam,iNumParams);  //�ҵ�BEEP��������
	printf("--------------in----------------");
	if(iIndex != -1) //�ҵ�BEEP������
	{
		for(i = 0;i < iNumParams;i++)
		{
			if(strcmp(pcParam[i],"BEEP") == 0)  //����CGI����
			{
				if(strcmp(pcValue[i], "BEEPON") == 0) //��BEEP
				{
				    printf("--------------in----------------");
					Beep(256, 2000);
					Beep(288, 2000);
					Beep(320, 2000);
					Beep(256, 2000);
					flag2=1;
				}
				else if(strcmp(pcValue[i],"BEEPOFF") == 0) //�ر�BEEP
			        flag2=0;
			}
		}
	}
	if(flag1==0&&flag2==0)      return "/TQ2440_LED_ON_BEEP_ON.shtml";    //LED1��,BEEP��
	else if(flag1==0&&flag2==1) return "/TQ2440_LED_ON_BEEP_OFF.shtml";	  //LED1��,BEEP��
	else if(flag1==1&&flag2==1) return "/TQ2440_LED_OFF_BEEP_OFF.shtml";  //LED1��,BEEP��
	else return "/TQ2440_LED_OFF_BEEP_ON.shtml";   							//LED1��,BEEP��		
}

//SSI�����ʼ��
void httpd_ssi_init(void)
{  
	//����SSI���
	http_set_ssi_handler(SSIHandler,ppcTAGs,NUM_CONFIG_SSI_TAGS);
}

//CGI�����ʼ��
void httpd_cgi_init(void)
{
  //����CGI���
  http_set_cgi_handlers(ppcURLs, NUM_CONFIG_CGI_URIS);

}


