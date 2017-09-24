#include <msp430f5529.h>
#include "clock.h"
#include "cog12864.h"
#include "UART.h"
#include "Timer.h"
void Close_led();
void Open_led();

void system_init(){
  init_Clock();
  Close_led();
  LCD_init();
  init_TimerA0();
  uart_init();
}

void Close_led(){
  P2DIR|=BIT0;
  P2OUT|=BIT0;
}

void Open_led(){
  P2DIR|=BIT0;
  P2OUT&=~BIT0;
}