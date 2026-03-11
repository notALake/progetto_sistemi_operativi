#include"./headers/interrupts.h"

void interrupt()
{
  //calculates Interrupt Exception Code
  //see Table 1: Interrupt Line and Device Class Mapping
  //in specs
  int IntlineNo = 0;
  switch(getCAUSE() & CAUSE_EXCCODE_MASK)
  {
    case IL_CPUTIMER:
      IntlineNo=1;
      break;

    case IL_TIMER:
      IntlineNo=2;
      break;

    case IL_DISK:
      IntlineNo=3;
      break;

    case IL_FLASH:
      IntlineNo=4;
      break;

    case IL_ETHERNET:
      IntlineNo=5;
      break;

    case IL_PRINTER:
      IntlineNo=6;
      break;

    case IL_TERMINAL:
      IntlineNo=7;
      break;

    default:
      //imòossibile
  }

  
}
