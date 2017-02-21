#ifndef ASTEROIDES_H_
#define ASTEROIDES_H_

#include "point2D.h"
#include "vaisseau.h"

typedef struct {
    Point2D position;
    Vector2D vitesse;
} Asteroide;

typedef struct liste_asteroide
{
	Asteroide asteroide;
	int numero;
	struct liste_asteroide *suivant;
} liste_asteroide;

void initialiser_asteroide(Asteroide* asteroide, int x, int y);

liste_asteroide* initialiser_liste_asteroide();

liste_asteroide* creer_liste_asteroide(Asteroide asteroide, int nb);

void ajouter_asteroide(liste_asteroide *asteroides, Asteroide asteroide);

void bouger_asteroides(liste_asteroide *asteroides);

liste_asteroide* creation_asteroides_par_niveau(int niveau);

void creation_vitesse_aleatoire_asteroide(Asteroide *asteroide);

int collision(liste_asteroide *asteroides, Vaisseau v); //teste s'il y a une collision entre le vaisseau et un astéroide

void dessin_asteroides(liste_asteroide *asteroides);

#endif
