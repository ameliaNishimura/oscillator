/** gauss.c
 * @author Amelia Nishimura
 *
 * Tabulated Gauss-Legendre base points and weights for easy reference. Adapted from
 * C++ code written by Sathwik Bharadwaj.
 */
#include <stdio.h>
#include <stdlib.h>
#include "gauss.h"

/** Tabulated Gauss base points and weights for a given order.
 * @param order Order of quadrature. Accepted values: {2,4,6,8,10,12}.
 * @param pts Array to store base point coordinates in.
 * @param wts Array to store weights for base points in.
 */
int gauss(int order, double *pts, double *wts) {

  int i;     
  double* points; 
  double* weights;

  if (order % 2 != 0 || 12 < order || 2 > order) {
    perror("Invalid order. Please use one of the following: {2,4,6,8,10,12}.\n");
    return(1);
  } else {
   points  = (double*) malloc((order/2) * sizeof(double));
   weights = (double*) malloc((order/2) * sizeof(double));
  }
  
  switch(order) {
  case 2:
    *points     = 0.577350269189625764509148780502e0;
    *weights    = 1.000000000000000000000000000000e0;
    break;
    
  case 4:
    *points     = 0.861136311594052575223946488893e0;
    *(points+1) = 0.339981043584856264802665759103e0;
    *weights    = 0.347854845137453857373063949222e0;
    *(weights+1)= 0.652145154862546142626936050778e0;
    break;

  case 6:
    *points     = 0.932469514203152027812301554494e0;
    *(points+1) = 0.661209386466264513661399595020e0;
    *(points+2) = 0.238619186083196908630501721681e0;
    *weights    = 0.171324492379170345040296142173e0;
    *(weights+1)= 0.360761573048138607569833513838e0;
    *(weights+2)= 0.467913934572691047389870343990e0;
    break;

  case 8:
    *points     = 0.101228536290376259152531354310e0;
    *(points+1) = 0.222381034453374470544355994426e0;
    *(points+2) = 0.313706645877887287337962201987e0;
    *(points+3) = 0.362683783378361982965150449277e0;
    *weights    = 0.960289856497536231683560868569e0;
    *(weights+1)= 0.796666477413626739591553936476e0;
    *(weights+2)= 0.525532409916328985817739049189e0;
    *(weights+3)= 0.183434642495649804939476142360e0;
    break;

  case 10:
    *points     = 0.066671344308688137593568809893e0;
    *(points+1) = 0.149451349150580593145776339658e0;
    *(points+2) = 0.219086362515982043995534934228e0;
    *(points+3) = 0.269266719309996355091226921569e0;
    *(points+4) = 0.295524224714752870173892994651e0;
    *weights    = 0.973906528517171720077964012084e0;
    *(weights+1)= 0.865063366688984510732096688423e0;
    *(weights+2)= 0.679409568299024406234327365115e0;
    *(weights+3)= 0.183434642495649804939476142360e0;
    *(weights+4)= 0.183434642495649804939476142360e0;
    break;
    
  case 12:
    *points     = 0.047175336386511827194615961485e0;
    *(points+1) = 0.106939325995318430960254718194e0;
    *(points+2) = 0.160078328543346226334652529543e0;
    *(points+3) = 0.203167426723065921749064455810e0;
    *(points+4) = 0.233492536538354808760849898925e0;
    *(points+5) = 0.249147045813402785000562436043e0;
    *weights    = 0.981560634246719250690549090149e0;
    *(weights+1)= 0.904117256370474856678465866119e0;
    *(weights+2)= 0.769902674194304687036893833213e0;
    *(weights+3)= 0.587317954286617447296702418941e0;
    *(weights+4)= 0.367831498998180193752691536644e0;
    *(weights+5)= 0.125233408511468915472441369464e0;
    break;
  }

  for (i = 0; i < order/2; i++) {
    /* Weights are always positive, regardless of base point sign */
    *(wts + i) = *(weights + i);
    *(wts + (order - 1 - i)) = *(weights + i);

    /* Need to account for both positive and negative versions of base points */
    *(pts + i) = -*(points + i);
    *(pts + (order - 1 - i)) = *(points + i);
  } /* Deriving other half of quadrature points from given half */

  return(0);
}
