#include <msp430f5529.h>

void init_TimerA0(){
  //定时器TA0初始化，连续计数模式
  TA0CTL = TASSEL_2 + MC_2 + TACLR+ID_3;// SMCLK, contmode, clear TAR
  TA0CCTL1 = CCIE;// CCR2 interrupt enabled
  TA0CCR1 = 50000;//5000/25MHz=5000Hz 0.2ms
  //TA0CCTL2 = CCIE;// CCR2 interrupt enabled
  //TA0CCR2 = 1000000;//50000/25MHz=500Hz 2ms
}



#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void)
{
  static long i;
  switch(TA0IV)
  {
  case 2://TA1CCR1_CCIFG
    TA0CCR1 += 20000;
    if(i==50)
      i++;
    //1s
    
    break;
  case 4:// TA1CCR2_CCIFG 
    break;
  case TA1IV_TAIFG://TA1IFG 
    break;
  default:
    break;
  }
}
