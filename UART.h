#ifndef __UART
#define __UART
#define send2uart(x) while((UCA1STAT&0x01)==1);UCA1TXBUF=x
#include <msp430f5529.h>
void uart_init()
{
  P4SEL = BIT5+BIT4;                        // P3.4,5 = USCI_A0 TXD/RXD
  UCA1CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCA1CTL1 |= UCSSEL_2;                     // SMCLK
  UCA1BR0 = 0x41; // 
  UCA1BR1 = 0x03; // 
  UCA1MCTL = 0x00; // 8MHz 115200 modulation
  //  UCA1BR0 = 0x2C;                              // 1MHz 9600 (see User's Guide)
  //  UCA1BR1 = 0x0A;                              // 1MHz 9600
  //  UCA1MCTL = 0x00;   // Modln UCBRSx=0, UCBRFx=0,
  // over sampling
  UCA1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UCA1IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
}

// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
  switch(__even_in_range(UCA1IV,4))
  {
  case 0:break;                             // Vector 0 - no interrupt
  case 2:                                   // Vector 2 - RXIFG
    while (!(UCA1IFG&UCTXIFG));             // USCI_A0 TX buffer ready?
    UCA1TXBUF = UCA1RXBUF;                  // TX -> RXed character
    break;
  case 4:break;                             // Vector 4 - TXIFG
  default: break;
  }
}


void send_number_to_char(unsigned int a)
{
  uchar b[]="25";
  signed char i;
  for(i=1;i>-1;i--)
  {
    b[i]=a%10+'0';
    a/=10;
  }
  for(i=0;i<1;i++)
  {
    if(b[i]=='0')
      b[i]=' ';
    else
      break;
  }
  for(int j=0;j<2;j++){
    send2uart(b[j]); 
  }
  
}
#endif