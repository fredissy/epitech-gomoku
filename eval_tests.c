#include "game.h"

int get_maxalign_coup(t_coup *tocheck, t_noeud *gamestate, char player)
{

	t_coord coord;
	coord.x=tocheck->x;
	coord.y=tocheck->y;
	return(get_maxalign_coord(coord, gamestate, player));
}

int get_maxalign_coord(t_coord coord, t_noeud *gamestate, char player)
{
	t_coup *coups;
	char	*tabs[8];
	int		nbre = 0;
	int		bestnbre=0;
	int		i=0;
	coups = gamestate->coup;
	tabs[0] = buildchaine(coups, 1, 0, coord, player, 5, 0); //droite
	tabs[1] = buildchaine(coups, 1, 1, coord, player, 5, 0); //bas droite
	tabs[2] = buildchaine(coups, 0, 1, coord, player, 5, 0); //bas
	tabs[3] = buildchaine(coups, -1, 1, coord, player, 5, 0); //bas gauche
	tabs[4] = buildchaine(coups, -1, 0, coord, player, 5, 0); //gauche
	tabs[5] = buildchaine(coups, -1, -1, coord, player, 5, 0); //haut gauche
	tabs[6] = buildchaine(coups, 0, -1, coord, player, 5, 0); //haut
	tabs[7] = buildchaine(coups, 1, -1, coord, player, 5, 0); //haut droite
	tabs[8] = 0;

	while(i<8)
	{
		nbre = checkstring_for_victory(tabs[i++]);
		bestnbre=MAX(nbre, bestnbre);
	}
	i=0;
//	printf("Pour (%d;%d), maxalign_coord=%d\n", coord.x, coord.y, bestnbre);
	while(i<8)
		free(tabs[i++]);
    return(bestnbre);
}

// x: adv
// ?: coup a jouer
// o: nous
// -: case vide
// on verifie si on se trouve dans : ?xxx-
// on ne joue pas si ?xxxo

int blocks_ennemy(t_coup *coups, t_coord coord, char player)
{
	char	*tabs[8];
	int		nbre = 0;
	int		i=0;
	tabs[0] = buildchaine(coups, 1, 0, coord, player, 7, 0); //droite
	tabs[1] = buildchaine(coups, 1, 1, coord, player, 7, 0); //bas droite
	tabs[2] = buildchaine(coups, 0, 1, coord, player, 7, 0); //bas
	tabs[3] = buildchaine(coups, -1, 1, coord, player, 7, 0); //bas gauche
	tabs[4] = buildchaine(coups, -1, 0, coord, player, 7, 0); //gauche
	tabs[5] = buildchaine(coups, -1, -1, coord, player, 7, 0); //haut gauche
	tabs[6] = buildchaine(coups, 0, -1, coord, player, 7, 0); //haut
	tabs[7] = buildchaine(coups, 1, -1, coord, player, 7, 0); //haut droite
	tabs[8] = 0;

	while(i<8)
	  nbre+=does_block_ennemy(tabs[i++]);
	i=0;
	while(i<8)
		free(tabs[i++]);
//		return(nbre);
	if(nbre)
    {
//  	  printf("ennemy blocked!:");displaymoves(coups);
	  return(1);
    }
	return (0);
}

int does_block_ennemy(char *chaine)
{
	char modele1[4]={MOI, ADVERSAIRE, ADVERSAIRE, ADVERSAIRE};
	char modele2[5]={MOI, ADVERSAIRE, ADVERSAIRE, ADVERSAIRE, MOI};
	char modele3[6]={MOI, ADVERSAIRE, ADVERSAIRE, ADVERSAIRE, ADVERSAIRE, MOI};
	if(!strncmp((char*)&modele2, chaine, 5))
		return(0);
	if(!strncmp((char*)&modele3, chaine, 6))
		return(2);
	if(!strncmp((char*)&modele1, chaine, 4))
		return(1);
	return(0);
}

int	fills_hole(t_coup *coups, t_coord coord, char player)
{
	char *tabs[8];
	int nbre = 0;
	int i = 0;
	tabs[0] = buildchaine(coups, 1, 0, coord, player, 4, 1); //droite
	tabs[1] = buildchaine(coups, 1, 1, coord, player, 4, 1); //bas droite
	tabs[2] = buildchaine(coups, 0, 1, coord, player, 4, 1); //bas
	tabs[3] = buildchaine(coups, -1, 1, coord, player, 4, 1); //bas gauche
	tabs[4] = buildchaine(coups, -1, 0, coord, player, 4, 1); //gauche
	tabs[5] = buildchaine(coups, -1, -1, coord, player, 4, 1); //haut gauche
	tabs[6] = buildchaine(coups, 0, -1, coord, player, 4, 1); //haut
	tabs[7] = buildchaine(coups, 1, -1, coord, player, 4, 1); //haut droite
	tabs[8] = 0;
	while(i<8)
	  nbre+=does_fill_hole(tabs[i++]);
	i=0;
	while(i<8)
	  free(tabs[i++]);
	return(nbre);
}
// on voit si le coup a jouer correspond a: x?xx
int does_fill_hole(char *chaine)
{
	char modele[4]={ADVERSAIRE, MOI, ADVERSAIRE, ADVERSAIRE};
	return (!strncmp((char*)&modele, chaine, 4));
}
