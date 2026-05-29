#include "./headers/functions.h"

int findPageIndex(unsigned int pte_entryHI)
{
  int vpn = ENTRYHI_GET_VPN(pte_entryHI);

  if(vpn == (ENTRYHI_VPN_MASK >> VPNSHIFT)) //stack area
    return USERPGTBLSIZE-1;
  else
    return (vpn - FRAMEPOOLSTART) / PAGESIZE - 1;
}
