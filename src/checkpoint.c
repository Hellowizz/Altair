#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL_image.h>

#include "vector2D.h"
#include "checkpoint.h"
#include "terrain.h"

#define PI 3.1415926

void initialiser_checkpoint(Checkpoint* c, int x, int y)
{
	c->position.x = x;
	c->position.y = y;
	c->boolean = 1;
}

liste_checkpoint* initialiser_liste_checkpoint()
{
	liste_checkpoint *checkpoints = (liste_checkpoint *) (malloc(sizeof(liste_checkpoint)));

	return checkpoints;
}

liste_checkpoint* creer_liste_checkpoint(Checkpoint c, int numero){
	liste_checkpoint *checkpoints = initialiser_liste_checkpoint();

	checkpoints->checkpoint = c;
	checkpoints->num = numero;
	checkpoints->suivant = NULL;

	return checkpoints;
}

void ajouter_checkpoint(liste_checkpoint *checkpoints, Checkpoint c){
	int nb = checkpoints->num;

	while(checkpoints->suivant != NULL){
		checkpoints = checkpoints->suivant;
		nb = checkpoints->num;
	}

	liste_checkpoint *liste = creer_liste_checkpoint(c, nb+1);
	checkpoints->suivant = liste;
}

int meme_point(int x1, int y1, int x2, int y2)
{
	int boolean = 0;

	if(x1 > x2-10 && x1 < x2+10){ 
		if(y1 > y2-10 && y1 < y2+10){
			boolean = 1;
		}
	}

	return boolean;
}

void passage_checkpoint(liste_checkpoint *checkpoints, Vaisseau v)
{
	if(checkpoints == NULL){
		return;
	}

	while(checkpoints != NULL){
		if(checkpoints->checkpoint.boolean == 1){
			if(meme_point(v.position.x, v.position.y, checkpoints->checkpoint.position.x, checkpoints->checkpoint.position.y)){
				checkpoints->checkpoint.boolean = 0;
				return;
			}
		} 
		checkpoints = checkpoints->suivant;
	}
}

int check_checkpoint(liste_checkpoint *checkpoints){
	while(checkpoints != NULL){
		if(checkpoints->checkpoint.boolean == 1){
			return 0;
		}else{
			checkpoints = checkpoints->suivant;
		}
	}
	return 1;
}

void cercle(int nb_segments, int full)
{
    int i;
    float angle = (2*PI)/nb_segments;
 
    if (full == 0)
    {
        glBegin(GL_LINE_LOOP);
        for (i = 0; i < nb_segments; i++)
        {
            glVertex2f(cos(i*angle)/2, sin(i*angle)/2);
        }
        glEnd();
    }
    else if (full == 1)
    {
        glBegin(GL_POLYGON);
        for (i = 0; i < nb_segments; i++)
        {
            glVertex2f(cos(i*angle)/2, sin(i*angle)/2);
        }
        glEnd();
    }    
}

void dessin_checkpoint(liste_checkpoint *checkpoints)
{
	while(checkpoints != NULL){

		if(checkpoints->checkpoint.boolean == 1){
			glPushMatrix();
				glColor3f(0,1,1);
				glTranslatef(checkpoints->checkpoint.position.x, checkpoints->checkpoint.position.y, 0);
				glScalef(15, 15, 1);
				cercle(30, 1);
			glPopMatrix();
		}

		

		checkpoints = checkpoints->suivant;
	}
}

