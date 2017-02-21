#include <stdlib.h>
#include <time.h>

#include "asteroides.h"
#include "checkpoint.h"
#include "terrain.h"

void initialiser_asteroide(Asteroide* asteroide, int x, int y)
{
	asteroide->position.x = x;
	asteroide->position.y = y;

	asteroide->vitesse.x = 0;
	asteroide->vitesse.y = 0;
}

liste_asteroide* initialiser_liste_asteroide()
{
	liste_asteroide *asteroides = (liste_asteroide *) (malloc(sizeof(liste_asteroide)));

	return asteroides;
}

liste_asteroide* creer_liste_asteroide(Asteroide asteroide, int nb)
{
	liste_asteroide *asteroides = initialiser_liste_asteroide();

	asteroides->asteroide = asteroide;
	asteroides->numero = nb;
	asteroides->suivant = NULL;

	return asteroides;
}

void ajouter_asteroide(liste_asteroide *asteroides, Asteroide asteroide)
{
	int nb;

	while(asteroides->suivant != NULL){
		asteroides = asteroides->suivant;
	}
	nb = asteroides->numero;

	liste_asteroide *liste = creer_liste_asteroide(asteroide, nb+1);
	asteroides->suivant = liste;
}

void bouger_asteroides(liste_asteroide *asteroides)
{
	while(asteroides != NULL){
		asteroides->asteroide.position.x += asteroides->asteroide.vitesse.x;
		asteroides->asteroide.position.y += asteroides->asteroide.vitesse.y;

			//Gestion des bords
		if (asteroides->asteroide.position.x > 400)
		{
			asteroides->asteroide.position.x -= 800;
			creation_vitesse_aleatoire_asteroide(&(asteroides->asteroide));
		}
		if (asteroides->asteroide.position.x < -400)
		{
			asteroides->asteroide.position.x += 800;
			creation_vitesse_aleatoire_asteroide(&(asteroides->asteroide));
		}
		if (asteroides->asteroide.position.y > 400)
		{
			asteroides->asteroide.position.y -= 800;
			creation_vitesse_aleatoire_asteroide(&(asteroides->asteroide));
		}
		if (asteroides->asteroide.position.y < -400)
		{
			asteroides->asteroide.position.y += 800;
			creation_vitesse_aleatoire_asteroide(&(asteroides->asteroide));
		}

		asteroides = asteroides->suivant;
	}
}

liste_asteroide* creation_asteroides_par_niveau(int niveau)
{
	liste_asteroide *liste_d_asteroides = NULL;

	if(niveau == 1){
		// 3 asteroides

		Asteroide as1;
		initialiser_asteroide(&as1, 300, 380);
		creation_vitesse_aleatoire_asteroide(&as1);
		liste_d_asteroides = creer_liste_asteroide(as1, 1);
		liste_asteroide *asteroides = liste_d_asteroides;

		Asteroide as2;
		initialiser_asteroide(&as2, 100, -300);
		creation_vitesse_aleatoire_asteroide(&as2);
		asteroides->suivant = creer_liste_asteroide(as2, 2);
		asteroides = asteroides->suivant;

		Asteroide as3;
		initialiser_asteroide(&as3, 250, 150);
		creation_vitesse_aleatoire_asteroide(&as3);
		asteroides->suivant =  creer_liste_asteroide(as3, 3);
		
	}
	else if(niveau == 2){
		// 5 asteroides

		Asteroide as1;
		initialiser_asteroide(&as1, 300, 380);
		creation_vitesse_aleatoire_asteroide(&as1);
		liste_d_asteroides = creer_liste_asteroide(as1, 1);
		liste_asteroide *asteroides = liste_d_asteroides;

		Asteroide as2;
		initialiser_asteroide(&as2, 100, -300);
		creation_vitesse_aleatoire_asteroide(&as2);
		asteroides->suivant = creer_liste_asteroide(as2, 2);
		asteroides = asteroides->suivant;

		Asteroide as3;
		initialiser_asteroide(&as3, 250, 150);
		creation_vitesse_aleatoire_asteroide(&as3);
		asteroides->suivant =  creer_liste_asteroide(as3, 3);
		asteroides = asteroides->suivant;

		Asteroide as4;
		initialiser_asteroide(&as4, -350, -100);
		creation_vitesse_aleatoire_asteroide(&as4);
		asteroides->suivant =  creer_liste_asteroide(as4, 4);
		asteroides = asteroides->suivant;

		Asteroide as5;
		initialiser_asteroide(&as5, 120, -50);
		creation_vitesse_aleatoire_asteroide(&as5);
		asteroides->suivant =  creer_liste_asteroide(as5, 5);
	}
	else if(niveau == 3){
		// 8 asteroides

		Asteroide as1;
		initialiser_asteroide(&as1, 300, 380);
		creation_vitesse_aleatoire_asteroide(&as1);
		liste_d_asteroides = creer_liste_asteroide(as1, 1);
		liste_asteroide *asteroides = liste_d_asteroides;

		Asteroide as2;
		initialiser_asteroide(&as2, 100, -300);
		creation_vitesse_aleatoire_asteroide(&as2);
		asteroides->suivant = creer_liste_asteroide(as2, 2);
		asteroides = asteroides->suivant;

		Asteroide as3;
		initialiser_asteroide(&as3, 250, 150);
		creation_vitesse_aleatoire_asteroide(&as3);
		asteroides->suivant =  creer_liste_asteroide(as3, 3);
		asteroides = asteroides->suivant;

		Asteroide as4;
		initialiser_asteroide(&as4, -350, -100);
		creation_vitesse_aleatoire_asteroide(&as4);
		asteroides->suivant =  creer_liste_asteroide(as4, 4);
		asteroides = asteroides->suivant;

		Asteroide as5;
		initialiser_asteroide(&as5, 120, -50);
		creation_vitesse_aleatoire_asteroide(&as5);
		asteroides->suivant =  creer_liste_asteroide(as5, 5);
		asteroides = asteroides->suivant;

		Asteroide as6;
		initialiser_asteroide(&as6, -30, 200);
		creation_vitesse_aleatoire_asteroide(&as6);
		asteroides->suivant =  creer_liste_asteroide(as6, 6);
		asteroides = asteroides->suivant;

		Asteroide as7;
		initialiser_asteroide(&as7, -50, -270);
		creation_vitesse_aleatoire_asteroide(&as7);
		asteroides->suivant =  creer_liste_asteroide(as7, 7);
		asteroides = asteroides->suivant;

		Asteroide as8;
		initialiser_asteroide(&as8, -100, -40);
		creation_vitesse_aleatoire_asteroide(&as8);
		asteroides->suivant =  creer_liste_asteroide(as8, 8);
	}

	return liste_d_asteroides;
}

void creation_vitesse_aleatoire_asteroide(Asteroide *asteroide)
{
	int x = 0, y = 0;
	srand(time(NULL)); // initialisation de rand
	x = rand()%(5-(-5)) -5;;
	y = rand()%(5-(-5)) -5;;

	if(x != 0 && y != 0){
		asteroide->vitesse.x = x;
		asteroide->vitesse.y = y;
	}else{
		asteroide->vitesse.x = 1;
		asteroide->vitesse.y = 1;
	}
}

int collision(liste_asteroide *asteroides, Vaisseau v)
{
	while(asteroides != NULL){
		if(meme_point(v.position.x, v.position.y, asteroides->asteroide.position.x, asteroides->asteroide.position.y)){
			printf("!!!!!!!!!!!! COLLISION !!!!!!!!!!!!\nVotre vaisseau a cessé de fonctionner\n");
			return 1;
		}else{
			asteroides = asteroides->suivant;
		}
	}
	return 0;
}

void dessin_asteroides(liste_asteroide *asteroides)
{
	while(asteroides != NULL){
		if(asteroides->asteroide.position.x < 400 && asteroides->asteroide.position.x > -400 && asteroides->asteroide.position.y < 400 && asteroides->asteroide.position.y > -400){
			int rand1 = (rand() % (100 + 1));
    		float frand1 = rand1/100.0;

			glPushMatrix();
				glColor3f(1,frand1,0);
				glTranslatef(asteroides->asteroide.position.x, asteroides->asteroide.position.y, 0);
				glScalef(40, 40, 1);
				cercle(30, 1);
			glPopMatrix();
		}
		asteroides = asteroides->suivant;
	}
}