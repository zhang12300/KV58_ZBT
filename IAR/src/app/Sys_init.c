#include "include.h"
#include <stdio.h>
void ClockGate_init()
{
  SIM_SCGC5 |=
    (SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK
     | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK);    //开全部端口时钟
}

void System_init(void)
{
  DisableInterrupts;
  ClockGate_init();
  SYSMPU->CESR &= ~SYSMPU_CESR_VLD_MASK;
  
  EnableInterrupts;  
}
