#include <msp430f5529.h>
#include "system_init.h"

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

unsigned char disp0[]={0x80+0,0x80+1,0x80+2,0x80+3,0x80+4,0};
unsigned char disp1[]={0x80+5,0x80+6,0x80+7,0x80+8,0x80+9,':',0};
unsigned char disp2[]={0x80+10,0x80+11,0x80+12,0x80+13,':',0};
unsigned char disp3[]={0x80+14,0x80+15,0x80+16,':',0};

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  system_init();
  PrintString(3*8,0,disp0);
  PrintString(0*8,2,disp1);
  PrintString(0*8,4,disp2); 
  PrintString(0*8,6,disp3);
    
  
  while(1)
  {
 
  }
}
