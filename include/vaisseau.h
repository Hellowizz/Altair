#ifndef VAISSEAU_H_
#define VAISSEAU_H_

#include "vector2D.h"
#include "point2D.h"

typedef struct {
    Point2D position;
    Vector2D direction;
    Vector2D vitesse;
    Vector2D acceleration;
    float angle;
    int avance, tourne;
} Vaisseau;

void dessin_vaisseau(Vaisseau* v);
void make_vaisseau(Point2D pos, Vaisseau* h);
void update_acceleration(Vaisseau* h);
void update_vitesse(Vaisseau* h);
void update_position(Vaisseau* h);
void update_rotation(Vaisseau* h);
void update_vaisseau(Vaisseau* h);


#endif