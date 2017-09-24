//MCLK=SMCLK=25MHz ACLK=32.786KHz
#ifndef __clock
#define __clock
#include <msp430f5529.h>
#define CPU_F ((double)16000000) 
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))
//ϵͳʱ������Ϊ25MHz
void init_Clock(){
  P1DIR |= BIT0;//LED������
  //  P1SEL |= BIT0;              //���Կ�ACLK��Ƶ��
  P2DIR |= BIT2;
  P2SEL |= BIT2;             //SMCLK
  P7DIR |= BIT7;
  P7SEL |= BIT7;             //MCLK
  
  
  
  P5SEL |= BIT2+BIT3;
  UCSCTL6 &= ~XT2OFF;          //��XT2
  /*********************�Ĵ������ò���******************************/
  __bis_SR_register(SCG0);
  UCSCTL0 = DCO0+DCO1+DCO2+DCO3+DCO4;
  UCSCTL1 = DCORSEL_4;                    //DCOƵ�ʷ�Χ��28.2MHZ����
  UCSCTL2 = FLLD_4 + 1;                   //D=16��N=1
  UCSCTL3 = SELREF_5 + FLLREFDIV_3;       //n=8,FLLREFCLKʱ��ԴΪXT2CLK��DCOCLK=D*(N+1)*(FLLREFCLK/n);DCOCLKDIV=(N+1)*(FLLREFCLK/n);
  UCSCTL4 = SELA_4 + SELS_3 +SELM_3;      //ACLK��ʱ��ԴΪDCOCLKDIV,MCLK\SMCLK��ʱ��ԴΪDCOCLK
  UCSCTL5 = DIVA_5 +DIVS_1;               //ACLK��DCOCLKDIV��32��Ƶ�õ���SMCLK��DCOCLK��2��Ƶ�õ�
  //����MCLK:16MHZ,SMCLK:8MHZ,ACLK:32KHZ
  
  __bic_SR_register(SCG0);                //Enable the FLL control loop
  /******************************************************************/
  __delay_cycles(8192);
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG); //Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;       //Clear fault flags
  }while (SFRIFG1&OFIFG);
  
}
#endif