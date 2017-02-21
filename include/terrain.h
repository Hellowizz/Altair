#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL_image.h>

#include "checkpoint.h"

#define WIDTH 800
#define HEIGHT 800

GLuint loadImage(char* image);
void DessinTerrain(GLuint texture);
liste_checkpoint* remplir_liste_checkpoint(char *nomfichier);
/* int remplir_liste_checkpoint(char *nomfichier, liste_checkpoint* checkpoints); */

#endif