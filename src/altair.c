#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "terrain.h"
#include "vaisseau.h"
#include "checkpoint.h"
#include "asteroides.h"
#include <time.h>
 
#define PI 3.1415926
 
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;
 
void reshape(unsigned int windowWidth, unsigned int windowHeight)
{
    glViewport(0, 0, windowWidth, windowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2);
}
 
void setVideoMode(unsigned int windowWidth, unsigned int windowHeight)
{
    if (NULL == SDL_SetVideoMode(windowWidth, windowHeight, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE))
    {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char** argv)
{
    srand(time(NULL));

    unsigned int windowWidth = WIDTH;
    unsigned int windowHeight = HEIGHT;
 
    if (-1 == SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
 
    setVideoMode(windowWidth, windowHeight);
    reshape(windowWidth, windowHeight);
 
    SDL_WM_SetCaption("ALTAÏR", NULL);

    //rempli la liste des checkpoints

    int matice_aleatoire = rand()%4 + 1;
    char *nomFichier = "matrice.txt";

    switch(matice_aleatoire){
        case 1:
            nomFichier = "matrice.txt";
            break;
        case 2:
            nomFichier = "matrice2.txt";
            break;
        case 3:
            nomFichier = "matrice3.txt";
            break;
        case 4:
            nomFichier = "matrice4.txt";
            break;
    }
    liste_checkpoint *liste;
    liste = remplir_liste_checkpoint(nomFichier);

    // rempli la liste des asteroides

    liste_asteroide *asteroides = NULL;
    asteroides = creation_asteroides_par_niveau(1);

    if(liste == NULL)
    {
        printf("La liste est null\n");
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) // Initialisation de SDL_Mixer
    {
       printf("%s", Mix_GetError());
    }

    Mix_Music *musique;
    musique = Mix_LoadMUS("./musique/musique.mp3");
    Mix_PlayMusic(musique, -1);

    Mix_AllocateChannels(3); // Alloue 2 canaux
    Mix_Volume(1, MIX_MAX_VOLUME*0.8);
    Mix_Volume(2, MIX_MAX_VOLUME*0.2);
    Mix_Chunk *ouverture_sas; // Crée un pointeur pour stocker un .WAV
    ouverture_sas = Mix_LoadWAV("./musique/ouverture_sas.wav"); // Charge un .WAV dans un pointeur
    Mix_Chunk *moteur; // Crée un pointeur pour stocker un .WAV
    moteur = Mix_LoadWAV("./musique/moteur.wav"); // Charge un .WAV dans un pointeur
    Mix_VolumeChunk(ouverture_sas, MIX_MAX_VOLUME/2); 
    Mix_VolumeChunk(moteur, MIX_MAX_VOLUME/2);

    // crée le vaisseau

    Vaisseau* v = (Vaisseau*) malloc(sizeof(Vaisseau));
    make_vaisseau(pointXY(0.,0.), v);

    GLuint texture = loadImage("./images/fond.jpg");
    GLuint accueil = loadImage("./images/accueil.jpg");
    GLuint jouer = loadImage("./images/jouer.jpg");
    GLuint options = loadImage("./images/options.jpg");
    GLuint quitter = loadImage("./images/quitter.jpg");
    GLuint options_magellan31 = loadImage("./images/options_magellan31.jpg");
    GLuint options_altaira = loadImage("./images/options_altaira.jpg");
    GLuint options_sandglassnebulae = loadImage("./images/options_sandglassnebulae.jpg");
    GLuint astronautedudimanche = loadImage("./images/astronautedudimanche.jpg");
    GLuint astronautechevronne = loadImage("./images/astronautechevronne.jpg");
    GLuint felixbaumgartner = loadImage("./images/felixbaumgartner.jpg");
    GLuint well_played = loadImage("./images/well_played.jpg");
    GLuint game_over = loadImage("./images/game_over.jpg");
 
    /* VARIABLES */

    int state_home = 1, state_options = 0, state_difficulty = 0, state_game_over = 0, state_well_played = 0;
    int pos_x = 0, pos_y = 0;
    int level = 1;
 
    /* LOOP */
 
    int loop = 1;
    while (loop)
    {
        Uint32 startTime = SDL_GetTicks();
 
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // glulookat(v->position.x, v->position.y, 0, v->position.x, v->position.y, 2, 0, 1, 0);
 
        /* DESSIN */
        
        if (state_home)
        {
            if (pos_x >= 550 && pos_x <= 750 && pos_y >= 30 && pos_y < 70)
            {
                glPushMatrix();
                    DessinTerrain(jouer);
                glPopMatrix();
            }
            else if (pos_x >= 550 && pos_x <= 750 && pos_y >= 70 && pos_y < 110)
            {
                glPushMatrix();
                    DessinTerrain(options);
                glPopMatrix();
            }
            else if (pos_x > 550 && pos_x <= 750 && pos_y >= 110 && pos_y < 150)
            {
                glPushMatrix();
                    DessinTerrain(quitter);
                glPopMatrix();
            }
            else
            {
                glPushMatrix();
                    DessinTerrain(accueil);
                glPopMatrix();
            }
        }
        else if (state_options)
        {
            if (pos_y < 267)
            {
                glPushMatrix();
                    DessinTerrain(options_magellan31);
                glPopMatrix();
            }
            else if (pos_y >= 267 && pos_y < 534)
            {
                glPushMatrix();
                    DessinTerrain(options_altaira);
                glPopMatrix();
            }
            else
            {
                glPushMatrix();
                    DessinTerrain(options_sandglassnebulae);
                glPopMatrix();
            }
        }
        else if (state_difficulty)
        {
            if (pos_y < 267)
            {
                glPushMatrix();
                    DessinTerrain(astronautedudimanche);
                glPopMatrix();
            }
            else if (pos_y >= 267 && pos_y < 534)
            {
                glPushMatrix();
                    DessinTerrain(astronautechevronne);
                glPopMatrix();
            }
            else
            {
                glPushMatrix();
                    DessinTerrain(felixbaumgartner);
                glPopMatrix();
            }
        }
        else if (state_well_played)
        {
            glPushMatrix();
                DessinTerrain(well_played);
            glPopMatrix();
        }
        else if (state_game_over)
        {
            glPushMatrix();
                DessinTerrain(game_over);
            glPopMatrix();
        }
        else
        {
            glPushMatrix();
            DessinTerrain(texture);
            glPopMatrix();

            // MOUVEMENT DES ASTEROIDES
            dessin_asteroides(asteroides);
            if (collision(asteroides, *v))
            {
                state_game_over = 1;
            }
            bouger_asteroides(asteroides);

            // MOUVEMENT DU VAISSEAU

            update_vaisseau(v);
            glPushMatrix();
                glTranslatef(v->position.x, v->position.y, 0);
                glRotatef(v->angle, 0., 0., 1.);
                dessin_vaisseau(v);
            glPopMatrix();

			passage_checkpoint(liste, *v);
            if(check_checkpoint(liste)){
                state_well_played = 1;
            }
            dessin_checkpoint(liste);
        }

        /* GESTION DES BORDS */

        if (v->position.x > 400) v->position.x -= 800;
        if (v->position.x < -400) v->position.x += 800;
        if (v->position.y > 400) v->position.y -= 800;
        if (v->position.y < -400) v->position.y += 800;

        /* SWAP */
 
        SDL_GL_SwapBuffers();
 
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                loop = 0;
                break;
            }
 
            switch(e.type)
            {
                /* Clic souris */
                case SDL_MOUSEBUTTONDOWN:
                    if (state_home)
                    {
                        if (pos_x >= 550 && pos_x <= 750 && pos_y >= 30 && pos_y < 70)
                        {
                            Mix_PlayChannel(1, ouverture_sas, 0);
                            state_home = 0;
                        }
                        else if (pos_x >= 550 && pos_x <= 750 && pos_y >= 70 && pos_y < 110)
                        {
                            state_home = 0;
                            state_options = 1;
                        }
                        else if (pos_x > 550 && pos_x <= 750 && pos_y >= 110 && pos_y < 150)
                        {
                            loop = 0;
                        }
                    }
                    else if (state_options)
                    {
                        if (pos_y < 267)
                        {
                            texture = loadImage("./images/fond.jpg");
                        }
                        else if (pos_y >= 267 && pos_y < 534)
                        {
                            texture = loadImage("./images/fond3.jpg");              
                        }
                        else if (pos_y >= 534)
                        {
                            texture = loadImage("./images/fond2.jpg");
                        }
                        state_options = 0;
                        state_difficulty = 1;
                    }
                    else if (state_difficulty)
                    {
                        //rempli la liste des asteroides
                        if (pos_y < 267) level = 1;
                        else if (pos_y >= 267 && pos_y < 534) level = 2;
                        else if (pos_y >= 534) level = 3;
                        state_difficulty = 0;
                        asteroides = creation_asteroides_par_niveau(level);
                    }
                    else if (state_well_played)
                    {
                        loop = 0;
                    }
                    else if (state_game_over)
                    {
                        loop = 0;
                    }
                    break;
 
                case SDL_MOUSEBUTTONUP:
                    break;
 
                 /* move the mouse */          
                case SDL_MOUSEMOTION:
                    pos_x = e.button.x;
                    pos_y = e.button.y;
                    break;
 
                /* Touche clavier */
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_q) loop = 0;
                    if (e.key.keysym.sym == SDLK_UP)
                    {
                        v->avance = 1;
                        Mix_PlayChannel(2, moteur, 0);   
                    }
                    if (e.key.keysym.sym == SDLK_LEFT) v->tourne = -1;
                    if (e.key.keysym.sym == SDLK_RIGHT) v->tourne = 1;
                    break;
 
                case SDL_KEYUP:
                    if (e.key.keysym.sym == SDLK_UP)
                    {
                        v->avance = 0;
                        Mix_Pause(2);   
                    }
                    if (e.key.keysym.sym == SDLK_RIGHT) v->tourne = 0;
                    if (e.key.keysym.sym == SDLK_LEFT) v->tourne = 0;
                    break;
               
                /* resize window */
                case SDL_VIDEORESIZE:
                    windowWidth = e.resize.w;
                    windowHeight = e.resize.h;
                    setVideoMode(windowWidth, windowHeight);
                    reshape(windowWidth, windowHeight);
                    break;
      
                default:
                    break;
            }
        }
 
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
 
        if (elapsedTime < FRAMERATE_MILLISECONDS)
        {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }
 
    Mix_FreeMusic(musique);
    Mix_CloseAudio();
    SDL_Quit();
    return EXIT_SUCCESS;
}
