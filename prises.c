#include "game.h"

int	prise_paire_adversaire(t_coup *coups, t_coord coord, char player)
{

	char	*tabs[8];
	int		nbre = 0;
	int		i=0;
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
	  nbre+=do_prend_paire(tabs[i++]);
	i=0;
	while(i<8)
		free(tabs[i++]);
	//if(nbre)
  //  {
	//  printf("prise paire adverse!")
	//  return(1);
  //  }
	//return (0);
	return(nbre);
}

int do_prend_paire(char *chaine)
{
	char modele[4]={MOI, ADVERSAIRE, ADVERSAIRE, MOI};
	if(!strncmp((char*)modele, chaine, 4))
		return(1);
	else
		return (0);
}


/************************************************************/


// x: adv
// ?: coup a jouer
// o: nous
// -: case vide
// on verifie si on se trouve dans : ?xxx-
// on ne joue pas si ?xxxo

void	dealprises(t_noeud *jeu, t_coord coord, char player)
{
	char	*tabs[8];
	int		i=0;

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
	  if(do_prend_paire(tabs[i])
	  	enlevepaire(jeu, coord, i);
	  i++;
    }
	i=0;
	while(i<8)
	  free(tabs[i++]);
}

void enlevepaire(t_noeud *jeu, t_coord, coord, int sens)
{
	int x;
	int y;
