#include "./headers/exceptions.h"

void exceptionHandler()
{
  unsigned int cause = getCAUSE();
  unsigned int causeCode = cause && CAUSE_EXCCODE_MASK;

  if(CAUSE_IS_INT(cause))
  {
    //interruptHandler();
  }
  else
  {
    switch(causeCode)
    {
      case 8:
        //SYSCALL
        break;
      
      case 11:
        //SYSCALL
        break;
      
      case 24:
        //TLB
        break;
      
      case 25:
        //TLB
        break;
      
      case 26:
        //TLB
        break;
      
      case 27:
        //TLB
        break;
      
      case 28:
        //TLB
        break;
      
      default:
        //Program Trap
        break;
    }
  }

}
