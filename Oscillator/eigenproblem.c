/** eigenproblem.c
 *
 */

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_math.h>
#include <string.h>
#include "eigenproblem.h"
#include "geometry.h"
#include "gauss.h"

/** Sets up the matrices A and B for the eigenvalue problem 
 *
 * @param A LHS matrix.
 * @param B RHS matrix.
 */
int setupProblem(struct Geometry* g, gsl_matrix* A, gsl_matrix* B) {
  
  int i_el = 0;    // Element iteration tracker
  int i_gauss = 0; // Gauss point iteration tracker
  int order = 0;
  double x_start, x_mid, x_end, x_jacobian; // Local coordinates
  
  double* points;
  double* weights;
  double pt, wt;
  double x_global;  // Global coordinate
  double* poly = (double*) malloc(2*sizeof(double));
  double* dpoly = (double*) malloc(2*sizeof(double));

  int i, j;
  double x_f, x_p;
  
  
  /* Prompt user for order, get Gauss values */
  printf("Please enter even number between 2-14 for Gauss order: ");
  scanf("%2d", &order);
  points = (double*) malloc(order * sizeof(double));
  weights = (double*) malloc(order * sizeof(double));
  gauss(order, points, weights);

  /* Loop to set up matrices A and B in the generalized eigenvalue problem Ax=eBx */
  for (i_el = 0; i_el < g->n_elem; i_el++) {

    /* Set local coordinates within current element i_el */
    x_start    = (i_el * g->elem_size) + g->x_min;
    x_end      = ((i_el + 1) * g->elem_size) + g->x_min;
    x_mid      = (x_end + x_start) / 2.;
    x_jacobian = (x_end - x_start) / 2.;

    /* Loop over Gaussian points*weights for sum */
    for (i_gauss = 0; i_gauss < order; i_gauss++) {

      pt         = *(points + i_gauss);
      wt         = *(weights + i_gauss);
      x_global   = x_mid + (x_jacobian * pt);

      /* Get values of linear interpolation polynomial at pt */
      poly[0]     = (1.0 - pt)/2.0;
      poly[1]     = (1.0 + pt)/2.0;

      /* Get values of derivatives of interpolation polynomials at pt */
      dpoly[0]    = -1.0/(2.0 * x_jacobian);
      dpoly[1]    = 1.0/(2.0 * x_jacobian);

      /* Loop to perform FEM calculations */
      for (i = 0; i < 2; i++) {
	for (j = 0; j < 2; j++) {
	  x_p = wt * x_jacobian * poly[i] * poly[j];
	  x_f = (wt * x_jacobian * dpoly[i] * dpoly[j]) + (x_p * x_global * x_global);
	  
	  *(gsl_matrix_ptr(A, i + i_el, j + i_el)) += x_f;
	  *(gsl_matrix_ptr(B, i + i_el, j + i_el)) += x_p;
			    
	} // End of j loop
      } // End of i loop
    } // End of loop over Gauss points (i_gauss)   
  } // End of loop over elements (i_el)

  return 0;
} /* setupProblem() */


/** Solve the generalized eigenvalue equation and save the wavefunction data
 *
 *
 */
int solveProblem() {

  int i, n_lev;
  struct Geometry* g = makeGeometry();
  gsl_matrix* A = gsl_matrix_calloc(g->n_elem + 1, g->n_elem + 1);
  gsl_matrix* B = gsl_matrix_calloc(g->n_elem + 1, g->n_elem + 1); 
  setupProblem(g, A, B);
  gsl_vector* e_vals = gsl_vector_calloc(g->n_elem + 1);
  gsl_vector_complex* e_cvals = gsl_vector_complex_calloc(g->n_elem + 1);
  gsl_matrix_complex* e_vecs = gsl_matrix_complex_calloc(g->n_elem + 1,g->n_elem + 1);
  gsl_eigen_genv_workspace* g_eigen = gsl_eigen_genv_alloc(g->n_elem + 1);
  char* filename = (char*) malloc(24*sizeof(char));
  FILE *output;
  
  /* Apply Dirichlet Boundary Conditions */
  for (i = 0; i < g->n_elem + 1; i++) {
    gsl_matrix_set(A, 0, i, 0.0);
    gsl_matrix_set(A, g->n_elem, i, 0.0);
    gsl_matrix_set(A, i, 0, 0.0);
    gsl_matrix_set(A, i, g->n_elem, 0.0);

    gsl_matrix_set(B, 0, i, 0.0);
    gsl_matrix_set(B, g->n_elem, i, 0.0);
    gsl_matrix_set(B, i, 0, 0.0);
    gsl_matrix_set(B, i, g->n_elem, 0.0);
  }

  gsl_matrix_set(A, 0, 0, 1000000.0);
  gsl_matrix_set(A, g->n_elem, g->n_elem, 2000000.0);

  gsl_matrix_set(B, 0, 0, 1.0);
  gsl_matrix_set(B, g->n_elem, g->n_elem, 1.0);

  printf("conditions applied\n");
  
  /* Generate eigenvalues and eigenvectors */
  gsl_eigen_genv(A, B, e_cvals, e_vals, e_vecs, g_eigen);
  gsl_eigen_genv_free(g_eigen);

  /* Sort eigenvalues and eigenvectors in ascending order */
  gsl_eigen_genv_sort(e_cvals, e_vals, e_vecs, GSL_EIGEN_SORT_ABS_ASC);

  /* Print out first 10 eigenvalues */
  printf("Eigenvalues: \n");
  for (i = 0; i < 10; i++) {
    printf("\t%2.6f\n", GSL_REAL(gsl_vector_complex_get(e_cvals, i)) /
	   gsl_vector_get(e_vals, i));
  }

  /* Write solutions to file */
  for (n_lev = 1; n_lev < 6; n_lev++) {

    sprintf(filename, "wave%d.dat", n_lev);
    output = fopen(filename, "w+");

    for (i = 0; i < g->n_elem + 1; i++) {
      fprintf(output, "%f\t%f\n", g->x_min+(i * g->elem_size),
	      fabs(GSL_REAL(gsl_matrix_complex_get(e_vecs, i, n_lev-1))));
    }

    fclose(output);
  }
  
  return 0;
}
