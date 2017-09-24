#include <msp430f5529.h>
#include "system_init.h"

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long


int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  
  return 0;
}
