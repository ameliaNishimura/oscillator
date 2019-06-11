/** geometry.c
 *  @author Amelia Nishimura
 */
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

  *e = tmp;

  return e;
}
  
