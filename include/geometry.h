#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "vector2D.h"
#include "point2D.h"

#define PI 3.14

#define EPSILON 0.0005
#define CLAMP(x, min, max) MAX(min, MIN(max, x))

Vector2D vector(Point2D A, Point2D B);
Point2D point_plus_vector(Point2D O, Vector2D v);

int is_zero(float x);

#endif
