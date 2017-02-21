#include "vaisseau.h"
#include "vector2D.h"
#include "point2D.h"
#include "checkpoint.h"
#include <math.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#define PI 3.1415926

void dessin_vaisseau(Vaisseau* v)
{
    glColor3f(.85, .85, .85);
    glPushMatrix();
        glScalef(15, 15, 0);
        glBegin(GL_POLYGON);
            glVertex2f(0.5, 0);
            glVertex2f(-0.5, 0);
            glVertex2f(-0.6, -2.75);
            glVertex2f(0.6, -2.75);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex2f(0.5,  0);
            glVertex2f(-0.5, 0);
            glVertex2f(0, 0.75);
        glEnd();
        glColor3f(.3, .3, .3);
        glBegin(GL_POLYGON);
            glVertex2f(0.29, 0.325);
            glVertex2f(-0.29, 0.325);
            glVertex2f(0, 0.75);
        glEnd();
        glColor3f(.85, .85, .85);
        glBegin(GL_POLYGON);
            glVertex2f(0, -.55);
            glVertex2f(-1.5, -2.15);
            glVertex2f(-1.5, -2.55);
            glVertex2f(1.5, -2.55);
            glVertex2f(1.5, -2.15);
        glEnd();
        glColor3f(.7, .7, .7);
        glBegin(GL_POLYGON);
            glVertex2f(-.1, -.75);
            glVertex2f(.1, -.75);
            glVertex2f(.1, -2.75);
            glVertex2f(-.1, -2.75);
        glEnd();
        glTranslatef(-0.2, -0.4, 0);
        glScalef(.2, .2, 1);
        glColor3f(.3, .3, .3);
        glBegin(GL_POLYGON);
            cercle(30, 1);
        glEnd();
        glScalef(5, 5, 1);
        glTranslatef(0.4, 0, 0);
        glScalef(.2, .2, 1);
        glBegin(GL_POLYGON);
            cercle(30, 1);
        glEnd();
        glScalef(5, 5, 1);
        glTranslatef(-0.2, 0.4, 0);
        glBegin(GL_POLYGON);
            glVertex2f(-0.2, -0.3);
            glVertex2f(0.2, -0.3);
            glVertex2f(0.2, -0.5);
            glVertex2f(-0.2, -0.5);
        glEnd();
        if (v->avance == 1) glColor3f(1, .3, .3);
        else glColor3f(0, .5, 0);
        glBegin(GL_POLYGON);
            glVertex2f(-0.80, -2.25);
            glVertex2f(-1.25, -2.25);
            glVertex2f(-1.25, -2.40);
            glVertex2f(-0.80, -2.40);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex2f(0.80, -2.25);
            glVertex2f(1.25, -2.25);
            glVertex2f(1.25, -2.40);
            glVertex2f(0.80, -2.40);
        glEnd();
        if (v->avance == 1)
        {
            glColor3f(1, 1, 0);
            glBegin(GL_POLYGON);
                glVertex2f(-0.35, -2.9);
                glVertex2f(0.35, -2.9);
                glVertex2f(0, -3.75);
            glEnd();
            glColor3f(1, .3, .3);
            glBegin(GL_POLYGON);
                glVertex2f(-0.9, -2.7);
                glVertex2f(-1.15, -2.7);
                glVertex2f(-1.025, -3.2);
            glEnd();
            glBegin(GL_POLYGON);
                glVertex2f(0.9, -2.7);
                glVertex2f(1.15, -2.7);
                glVertex2f(1.025, -3.2);
            glEnd();
        }
    glPopMatrix();
}

void make_vaisseau(Point2D pos, Vaisseau* h)
{
	h->position = pos;
	h->angle = 0;
	h->direction = VectorXY(0.,1.);
	h->acceleration = VectorXY(0,0);
	h->vitesse = VectorXY(0,0);
	h->tourne = 0;
}

/* PARTIE PHYSIQUE */

void update_acceleration(Vaisseau* h)
{
	if (h->avance == 1)
	{
		h->acceleration = MultVector(h->direction, 0.1);
	}
	else
	{
		h->acceleration = VectorXY(0,0.);
	}
	return;
}

void update_vitesse(Vaisseau* h)
{
	h->vitesse = AddVectors(h->vitesse, h->acceleration);
	h->vitesse = SubVectors(h->vitesse, DivVector(h->vitesse, 50.));
	return;
}

void update_position(Vaisseau* h)
{
	h->position.x += h->vitesse.x;
	h->position.y += h->vitesse.y;
	return;
}

void update_rotation(Vaisseau* h)
{
	if (h->tourne != 0)
	{
		h->angle = h->angle - (h->tourne * 5);
		h->angle = h->angle;
		h->direction.x = -sin((PI*h->angle)/180);
		h->direction.y = cos((PI*h->angle)/180);
	}
	return;
}

void update_vaisseau(Vaisseau* h)
{
	update_rotation(h);
	update_acceleration(h);
	update_vitesse(h);
	update_position(h);
	return;
}