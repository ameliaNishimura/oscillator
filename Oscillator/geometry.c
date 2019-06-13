/** geometry.c
 *  @author Amelia Nishimura
 */
#include <stdio.h>
#include <stdlib.h>
#include "geometry.h"

/** Allocates a Geometry struct and fills in its fields.
 * @param range Range to each side of x-axis to evaluate. 
 * @param n_elem Number of elements to evaluate.
 * @return Pointer to newly allocated Geometry struct on the heap.
 */
struct Geometry* makeGeometry() {

  int range;
  int n_elem;
  struct Geometry* g;

  printf("Please enter range as >5 -> [-5,5]: ");
  scanf("%d", &range);

  printf("Please enter number of elements to evaluate: ");
  scanf("%d", &n_elem);
  

  g = (struct Geometry*) malloc(sizeof(struct Geometry));

  g->x_min = -range;
  g->x_max = range;
  g->n_elem = n_elem;
  g->elem_size = (2. * range) / n_elem;

  return g;
}
  
/** Prints out the fields of a Geometry struct
 * @param g Pointer to Geometry struct.
 */
void printGeometry(struct Geometry* g) {
  printf("x_min: %d x_max: %d n_elem: %d elem_size: %2.6f\n",
	 g->x_min, g->x_max, g->n_elem, g->elem_size);
}
