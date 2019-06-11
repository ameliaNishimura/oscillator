/**
 * geometry.h
 *
 * @author: Amelia Nishimura
 * Struct to store dimensions of region for FEM
 */

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

struct Geometry {
  int xmin;  // Lower limit of evaluation
  int xmax;  // Upper limit of evaluation
  int nelem; // Number of elements to generate
  // Add ndegfreedom later?
};

// Function prototypes
struct Geometry *defGeometry(int range, int nelem);

#endif /* GEOMETRY_H_ */
