/** eigenproblem.c
 *
 */

#include "eigenproblem.h"
#include "geometry.h"

int setupProblem(gsl_matrix* A, gsl_matrix* B) {

  struct Geometry* g = makeGeometry();
  printGeometry(g);
  
  printf("noice\n");

  return 0;
}
