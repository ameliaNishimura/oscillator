/* FEM Quantum Harmonic Oscillator
 * Author: Amelia Nishimura
 * 
 * Generates approximations of the energy levels and wavefunctions of the quantum
 * harmonic oscillator using finite element analysis (FEM).
 */
#include <stdio.h>
#include "geometry.h"

/** Main function.
 *  @param argc Number of command line arguments.
 *  @param argv Array of pointers to character strings containing arguments.
 *  @return 0 if successfully run, 1 if not.
 */
int main(int argc, char** argv) {

  struct Geometry* test_g = makeGeometry(2, 10);
  printGeometry(test_g);
  
  return 0;
}
