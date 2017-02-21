#include <stdlib.h>
#include <stdio.h>
#include "terrain.h"
#include "checkpoint.h"
#include "point2D.h"

GLuint loadImage(char* image)
{
    SDL_Surface* myTexture = IMG_Load(image);
    if (myTexture == NULL)
    {
        fprintf(stderr, "Impossible d'afficher l'image. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    GLuint textures;
    glGenTextures(1, &textures);

    glBindTexture(GL_TEXTURE_2D, textures);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    GLenum format;
    switch(myTexture->format->BytesPerPixel)
    {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_BGRA;
            break;
        default:
            fprintf(stderr, "Format des pixels de l’image non pris en charge\n");
            exit(-1);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, myTexture->w, myTexture->h, 0, format, GL_UNSIGNED_BYTE, myTexture->pixels);

    SDL_FreeSurface(myTexture);
    glBindTexture(GL_TEXTURE_2D, 0);

    return textures;
}

void DessinTerrain(GLuint texture) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex2f(-400, 400);
        glTexCoord2f(1,0); glVertex2f(400, 400.);
        glTexCoord2f(1,1); glVertex2f(400, -400.);
        glTexCoord2f(0,1); glVertex2f(-400, -400.);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

liste_checkpoint* remplir_liste_checkpoint(char *nomfichier)
{
    FILE* fichier = fopen(nomfichier, "r");

    liste_checkpoint *checkpoints = NULL;
    int  c = EOF;

    if (fichier != NULL)
    {
        int i = 0, j = 0;
        do
        {
            c = fgetc(fichier);
            if (c == '1')
            {
                Checkpoint check;
                initialiser_checkpoint(&check, ((i)*10)-400, ((j)*10)-400);

                if (checkpoints == NULL){
                    checkpoints = creer_liste_checkpoint(check, 1);
                }else{
                    ajouter_checkpoint(checkpoints, check);
                }
            } 
            if (c == '\n')
            {
                j++;
                i=0;
            }
            i++;            
        } while (c != EOF);

        fclose(fichier);
    }
    else
    {
        // On affiche un message d'erreur si on veut
        fprintf(stderr, "Problème de lecture de fichier\n");
        return NULL;
    }
    return checkpoints;
}


