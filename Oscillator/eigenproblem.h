/** eigenproblem.h
 *
 */

#ifndef EIGENPROBLEM_H_
#define EIGENPROBLEM_H_

#include <gsl/gsl_matrix.h>

int setupProblem(gsl_matrix* A, gsl_matrix* B);

#endif /* EIGENPROBLEM_H_ */
