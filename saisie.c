#include "game.h"

t_coord	saisie(signed char player, t_coup *coups)
{
  t_coord saisie;
  saisie.x = DIM + 1;
  saisie.y = DIM + 1;
  while(!saisie_ok(coups, saisie, player))
    {
      printf("joueur %d coord x? ", player+1);
      scanf("%d", &saisie.x);
      printf("joueur %d coord y? ", player+1);
      scanf("%d", &saisie.y);
    }
  return (saisie);
}

//valide la saisie du joueur
int saisie_ok(t_coup *coups, t_coord saisie, signed char player)
{
	if(saisie.x<0 || saisie.x>DIM || saisie.y<0 || saisie.y>DIM)
		return (0);
	if(occupee(coups, saisie) != -1)
		return (0);
	if(checkdoubletrois(coups, saisie, player))
		return(0);
	return (1);
}

// on verifie si les coordonnées saisies par le joueur correspondent
// à une situation de double trois, vérifiant les cases autour.
int			checkdoubletrois(t_coup *coups, t_coord saisie, signed char player)
{
	char	*tabs[8];
	int		nbre = 0;
	int		i=0;

	tabs[0] = buildchaine(coups, 1, 0, saisie, player); //droite
	tabs[1] = buildchaine(coups, 1, 1, saisie, player); //bas droite
	tabs[2] = buildchaine(coups, 0, 1, saisie, player); //bas
	tabs[3] = buildchaine(coups, -1, 1, saisie, player); //bas gauche
	tabs[4] = buildchaine(coups, -1, 0, saisie, player); //gauche
	tabs[5] = buildchaine(coups, -1, -1, saisie, player); //haut gauche
	tabs[6] = buildchaine(coups, 0, -1, saisie, player); //haut
	tabs[7] = buildchaine(coups, 1, -1, saisie, player); //haut droite
	tabs[8] = 0;
	while(i<8)
		nbre+=is_doubletrois(tabs[i++], player);
	if(nbre>1)
		printf("/!\\ Double trois interdit!\n");
	i=0;
	while(i<8)
		free(tabs[i++]);
	return(nbre>1);
}

/* dit si une chaine est une situation de double trois ou non
** on utilise pour cela deux modeles de chaine. le joueur joue
** dans la 2eme case des modeles. voir buildchaine pour la
** construction de la chaine de comparaison
*/
int		is_doubletrois(char *chaine, signed char player)
{
	char modele1[5]={PERSONNE,PERSONNE,MOI,MOI,PERSONNE};
	char modele2[5]={PERSONNE,PERSONNE,PERSONNE,MOI,MOI};

	if(!strncmp((char*)&modele1, chaine, 5))
		return(1);
	if(!strncmp((char*)&modele2, chaine, 5))
		return (1);
	return(0);
}

/* Construit et renvoie une chaine
** pour la recherche des doubles trois
*/
char		*buildchaine(t_coup *coups, int dx, int dy, t_coord coord, signed char player)
{
	char	*chaine;
	int		i = 0;

	coord.x-=dx;
	coord.y-=dy;
	chaine = malloc(4*sizeof(char));
	while(i<5)
	{
		chaine[i] = dans(coups, coord, player);
		coord.x+=dx;
		coord.y+=dy;
		i++;
	}
	chaine[5]=0;
	return (chaine);
}

int	dans(t_coup *orig, t_coord coord, signed char player)
{
	while(orig)
	{
		if(orig->x == coord.x && orig->y == coord.y)
		{
			if(orig->player==player)
	    		return (MOI);
	    	else
	    		return (ADVERSAIRE);
		}
	    orig=orig->next;
    }
  return (PERSONNE);
}
