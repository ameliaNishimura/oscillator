/** eigenproblem.h
 *
 */

#ifndef EIGENPROBLEM_H_
#define EIGENPROBLEM_H_

#include <gsl/gsl_matrix.h>
#include "geometry.h"

int setupProblem(struct Geometry* g, gsl_matrix* A, gsl_matrix* B);
int solveProblem();

#endif /* EIGENPROBLEM_H_ */
