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
struct Geometry* makeGeometry(int range, int n_elem) {
  struct Geometry* g;
  struct Geometry tmp;

  g = (struct Geometry*) malloc(sizeof(struct Geometry));

  tmp.x_min = -range;
  tmp.x_max = range;
  tmp.n_elem = n_elem;
  tmp.elem_size = (2. * range) / n_elem;
  
  *g = tmp;

  return g;
}
  
/** Prints out the fields of a Geometry struct
 * @param g Pointer to Geometry struct.
 */
void printGeometry(struct Geometry* g) {
  printf("x_min: %d x_max: %d n_elem: %d elem_size: %2.6f\n",
	 g->x_min, g->x_max, g->n_elem, g->elem_size);
}
