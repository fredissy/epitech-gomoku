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
//printf("%d;%d;", player, nbre);
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
//s'occupe des prises sur le plateau. en vire si certaines sont d�tect�es
// en fonction de la position jou�e (coord)

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
	tabs[0] = buildchaine(jeu->coup, 1, 0, coord, player, 5, 0); //droite
	tabs[1] = buildchaine(jeu->coup, 1, 1, coord, player, 5, 0); //bas droite
	tabs[2] = buildchaine(jeu->coup, 0, 1, coord, player, 5, 0); //bas
	tabs[3] = buildchaine(jeu->coup, -1, 1, coord, player, 5, 0); //bas gauche
	tabs[4] = buildchaine(jeu->coup, -1, 0, coord, player, 5, 0); //gauche
	tabs[5] = buildchaine(jeu->coup, -1, -1, coord, player, 5, 0); //haut gauche
	tabs[6] = buildchaine(jeu->coup, 0, -1, coord, player, 5, 0); //haut
	tabs[7] = buildchaine(jeu->coup, 1, -1, coord, player, 5, 0); //haut droite
	tabs[8] = 0;
	while(i<8)
	{
	  if(do_prend_paire(tabs[i]))
	  	enlevepaire(jeu, coord, i, player);
	  i++;
    }
	i=0;
	while(i<8)
	  free(tabs[i++]);
}
/* Sens:
**
** 5  6  7
**   \|/
** 4 -+- 0
**   /|\
** 3  2  1
*/
void enlevepaire(t_noeud *jeu, t_coord coord, int sens, char player)
{
	int x = 0;
	int y = 0;
	if(sens==0||sens==1||sens==7)
		x=1;
	if(sens==1||sens==2||sens==3)
		y=1;
	if(sens==3||sens==4||sens==5)
		x=-1;
	if(sens==5||sens==6||sens==7)
		y=-1;
	removecoup(jeu, generatecoord(coord.x+x, coord.y+y));
	removecoup(jeu, generatecoord(coord.x+2*x, coord.y+2*y));
	printf("Deux pions perdus pour le joueur %d! (%d;%d) (%d;%d)\n", (!player)+1, coord.x+x, coord.y+y, coord.x+2*x, coord.y+2*y);
	jeu->paires[!player]++;
}
