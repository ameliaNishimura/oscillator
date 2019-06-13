/**
 * geometry.h
 *
 * @author: Amelia Nishimura
 * Struct to store dimensions of region for FEM
 */

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

struct Geometry {
  int x_min;    
  int x_max;    
  int n_elem;   
  double elem_size;
  // Add ndegfreedom later?
};

// Function prototypes
struct Geometry *makeGeometry();
void printGeometry(struct Geometry* g);

#endif /* GEOMETRY_H_ */
