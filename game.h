#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//dans la liste chain�e des positions
#define NOPLAYER -1
#define PLAYER1 0
#define PLAYER2 1
#define DEHORS -2

//pour les arguments
#define UNJOUEUR 0
#define DEUXJOUEURS 1
#define RUN_DEBUG 1
#define FULL_DEBUG 2

//mot cl� pour l'aide
#define HINT_KEYWORD "hint"

//taille du damier
#define DIM 15

//profondeur de rechercher
#define MAXDEPTH 2

//expansion a chaque fois
#define EXTRA 1

//nbre de paires (==pions/2) � prendre
#define NBPAIRES 5

//max ou min de deux valeurs
#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))

//pour les comparaisons
#define MOI '1'
#define ADVERSAIRE '2'
#define PERSONNE '0'

#include "structs.h"
#include "prototypes.h"
