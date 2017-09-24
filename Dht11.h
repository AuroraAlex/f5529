#include <msp430f5529.h>
#include "system_int.h"

#define DHT11_OUTPUT   P8DIR|=BIT1
#define DHT11_INPUT   P8DIR&=~BIT1
#define DHT11_H   P8OUT|=BIT1
#define DHT11_L   P8OUT&=~BIT1
#define DHT11_IN   (P8IN&BIT1)
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

uchar start_DHT11(void);
uchar DHT11_ReadChar(void);
void dht11(void);
uchar DHT11T_Data_H, DHT11T_Data_L, DHT11RH_Data_H, DHT11RH_Data_L,CheckData_temp;


uchar start_DHT11(void)
{
  uchar TData_H_temp,TData_L_temp,RHData_H_temp,RHData_L_temp,checktemp;
  uchar  presence,flag;
  uint count;
  DHT11_OUTPUT;
  DHT11_L;    //拉低18ms以上
  delay_ms(20);
  DHT11_H;
  DHT11_INPUT;
  delay_us(40);
  presence=DHT11_IN;
  if(!presence)
  {
    count=2;
    while((!DHT11_IN)&&count++);//等待低电平
    count=2;
    while((DHT11_IN)&&count++);//等待高电平
    RHData_H_temp = DHT11_ReadChar(); 
    RHData_L_temp = DHT11_ReadChar(); 
    TData_H_temp = DHT11_ReadChar(); 
    TData_L_temp = DHT11_ReadChar(); 
    CheckData_temp = DHT11_ReadChar(); 
    DHT11_OUTPUT;
    DHT11_H;
    checktemp = (RHData_H_temp + RHData_L_temp + TData_H_temp + TData_L_temp); 
    if (checktemp == CheckData_temp) { 
      DHT11RH_Data_H = RHData_H_temp; 
      DHT11RH_Data_L = RHData_L_temp; 
      DHT11T_Data_H = TData_H_temp; 
      DHT11T_Data_L = TData_L_temp; 
      flag=1; 
    }
  }
  //P1OUT |=BIT0;
  return flag;
}




uchar DHT11_ReadChar(void)
{
  unsigned char dat; 
  unsigned int count;     //计数防止死等 
  unsigned char i;
  for(i=0;i<8;i++) 
  { 
    count=2; 
    while((!DHT11_IN)&&count++);     //等待50us低电平结束 
    delay_us(40); //40us 
    dat <<= 1;        //50us低电平+28us高电平表示'0'
    if(DHT11_IN)    //50us低电平+70us高电平表示'1'
      dat |= 1;
    count=2; 
    while((DHT11_IN)&&count++); 
    if(count==1)      //超时则跳出for循环 
      break; 
  } 
  return dat;   
}




void dht11()
{
  char c[40];
  uchar o;
  o=start_DHT11();
  P1OUT |=BIT1;
  delay_ms(300);
  P1OUT &=~BIT1;
  delay_ms(300);
  if (o)
  {
    //Display_Dht11();
    send_number_to_char(DHT11T_Data_H);
    send2uart(' ');
    send_number_to_char(DHT11RH_Data_H);
    send2uart(' ');
    
  }
}


void Display_Dht11(){
  print_number(11*8,2,DHT11T_Data_H);
  print_number(14*8,2,DHT11RH_Data_H);
}

