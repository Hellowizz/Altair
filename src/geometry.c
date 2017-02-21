#include "geometry.h"

Vector2D Vector(Point2D A, Point2D B) {
    return VectorXY(B.x - A.x, B.y - A.y);
}

Point2D point_plus_vector(Point2D O, Vector2D v) {
    return pointXY(O.x + v.x, O.y + v.y);
}

int is_zero(float x) {
    return x > -EPSILON && x < EPSILON;
}
