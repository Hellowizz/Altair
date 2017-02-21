#ifndef CHECKPOINT_H_
#define CHECKPOINT_H_

#include "point2D.h"
#include "vaisseau.h"

typedef struct {
    Point2D position;
    int boolean; 	// 1 si le vaisseau ne l'a pas pris et 0 si le vaisseau est dejà passé dessus
} Checkpoint;

typedef struct liste_checkpoint
{
	int num;
	Checkpoint checkpoint;
	struct liste_checkpoint *suivant;

} liste_checkpoint;

void initialiser_checkpoint(Checkpoint* c, int x, int y);

liste_checkpoint* initialiser_liste_checkpoint();

liste_checkpoint* creer_liste_checkpoint(Checkpoint c, int numero);

void ajouter_checkpoint(liste_checkpoint *checkpoints, Checkpoint c);

int meme_point(int x1, int y1, int x2, int y2);

void passage_checkpoint(liste_checkpoint *checkpoints, Vaisseau v);

int check_checkpoint(liste_checkpoint *checkpoints);

void cercle(int nb_segments, int full);

void dessin_checkpoint(liste_checkpoint *checkpoints);

#endif
