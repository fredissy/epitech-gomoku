#include "game.h"

int evalnode(t_noeud *gamestate, char player, t_args args)
{
  int	bestscore=0;
  int	score=0;
  t_coup	*coup;
  t_coord coord;
  if(gamestate==0)
    return (0);
  coup=gamestate->coup;
  coord.x=gamestate->x;
  coord.y=gamestate->y;
  score = evalcase_align(gamestate->coup, coord, player);
  bestscore = MAX(score, bestscore);
  if(score==0)
    return(0);
  if(blocks_ennemy(gamestate->coup, coord, player)||fills_hole(gamestate->coup, coord, player))
    score=10;
  bestscore = MAX(score, bestscore);

  if(get_maxalign_coord(coord, gamestate) == 5)
  	score=20;
  bestscore = MAX(score, bestscore);
  gamestate->value=bestscore;

  return(bestscore);
}

int	evalcase_align(t_coup *coups, t_coord coord, char player)
{
  int	score=0;
//  int tmpscore=0;

  if(occupee(coups, coord)== NOPLAYER)
    return (0);
  if(coord.x<=DIM-6 && coord.x>=0)
  	 score=MAX(score,eval_line(coups, coord, 1, 0, player));
  if(coord.y<=DIM-6 && coord.y>=0 && coord.x<=DIM-6 && coord.x>=0)
  	score=MAX(score,eval_line(coups, coord, 1, 1, player));
  if(coord.y<=DIM-6 && coord.y>=0)
  	score=MAX(score,eval_line(coups, coord, 0, 1, player));
  if(coord.y<=DIM-6 && coord.y>=0 && coord.x>=5 && coord.x<=DIM)
	score=MAX(score,eval_line(coups, coord, -1, 1, player));
  if(coord.x>=5 && coord.x<=DIM)
    score=MAX(score,eval_line(coups, coord, -1, 0, player));
  if(coord.x>=5 && coord.x<=DIM && coord.y>=5 && coord.y<=DIM)
    score=MAX(score,eval_line(coups, coord, -1, -1, player));
  if(coord.y>=5 && coord.y<=DIM)
	score=MAX(score,eval_line(coups, coord, 0, -1, player));
  if(coord.x<=DIM-6 && coord.x>=0 && coord.y>=5 && coord.y<=DIM)
	score=MAX(score,eval_line(coups, coord, 1, -1, player));
  return(score);
}

// principe: on remplit un tableau de 6 chars avec les 6 cases a analyser,
// on compte le score possible avec cette position, enfin on le renvoie.
int	eval_line(t_coup *coups, t_coord coord, signed int xm, signed int ym, char player)
{
  char	cells[9];
  int	i=0;
  int	nbfree=0;
  char	player_2;
  int	score;
t_coord backup;
backup=coord;
  if(player==PLAYER1)
    player_2=PLAYER2;
  else
    player_2=PLAYER1;

  //on construit la ligne a inspecter
  coord.x-=4*xm;
  coord.y-=4*ym;
  for(i=0;i<10;i++)
  {
	cells[i] =occupee2(coups, coord);
	coord.x+=xm;
	coord.y+=ym;
  }

  i=0;
  score=0;
  while(cells[i]!=player && i<10)
  {
	nbfree++;
	if(cells[i]==player_2||cells[i]==DEHORS)
		nbfree=0;
  	i++;
  }
  while(cells[i]==player && i<10)
    {
      score++;
      i++;
    }
  while(i<10 && cells[i]!=player_2)
    {
		nbfree++;
		i++;
    }
  if(nbfree+score>=5)
	return(score);
  else
  	return (0);
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
	tabs[0] = buildchaine(coups, 1, 0, coord, player, 6, 0); //droite
	tabs[1] = buildchaine(coups, 1, 1, coord, player, 6, 0); //bas droite
	tabs[2] = buildchaine(coups, 0, 1, coord, player, 6, 0); //bas
	tabs[3] = buildchaine(coups, -1, 1, coord, player, 6, 0); //bas gauche
	tabs[4] = buildchaine(coups, -1, 0, coord, player, 6, 0); //gauche
	tabs[5] = buildchaine(coups, -1, -1, coord, player, 6, 0); //haut gauche
	tabs[6] = buildchaine(coups, 0, -1, coord, player, 6, 0); //haut
	tabs[7] = buildchaine(coups, 1, -1, coord, player, 6, 0); //haut droite
	tabs[8] = 0;

	while(i<8)
	  nbre+=does_block_ennemy(tabs[i++]);
	i=0;
	while(i<8)
		free(tabs[i++]);
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
	if(!strncmp((char*)&modele2, chaine, 5))
		return(0);
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
	if(nbre)
	{
		printf("on remplit un trou ennemi\n");
		return (1);
	}
	return(0);
}
// on voit si le coup a jouer correspond a: x?xx
int does_fill_hole(char *chaine)
{
	char modele[4]={ADVERSAIRE, MOI, ADVERSAIRE, ADVERSAIRE};
	return (!strncmp((char*)&modele, chaine, 4));
}


//pareil que buildchaine, sans décalage au depart
//char		*buildchaine2(t_coup *coups, int dx, int dy, t_coord coord, signed char player, int size)
//{
//	char	*chaine;
//	int		i = 0;
//
//	chaine = malloc((size-1)*sizeof(char));
//	while(i<size)
//	{
//		chaine[i] = dans(coups, coord, player);
//		coord.x+=dx;
//		coord.y+=dy;
//		i++;
//	}
//	chaine[size]=0;
//	return (chaine);
//}


int gameended(t_noeud *gamestate)
{
	t_coup *coup;
	int	nbalign=0;
	coup = gamestate->coup;
	while(coup)
	{
		nbalign=get_maxalign_coup(coup, gamestate);
		if(nbalign==5)
		  return (1);
		coup = coup->next;
	}
	return(nbalign==5);
}

int get_maxalign_coup(t_coup *tocheck, t_noeud *gamestate)
{

	t_coord coord;
	coord.x=tocheck->x;
	coord.y=tocheck->y;
	return(get_maxalign_coord(coord, gamestate));
}

int get_maxalign_coord(t_coord coord, t_noeud *gamestate)
{
	t_coup *coups;
	char	*tabs[8];
	int		nbre = 0;
	int		bestnbre=0;
	int		i=0;
	coups = gamestate->coup;
	tabs[0] = buildchaine(coups, 1, 0, coord, PLAYER1, 5, 0); //droite
	tabs[1] = buildchaine(coups, 1, 1, coord, PLAYER1, 5, 0); //bas droite
	tabs[2] = buildchaine(coups, 0, 1, coord, PLAYER1, 5, 0); //bas
	tabs[3] = buildchaine(coups, -1, 1, coord, PLAYER1, 5, 0); //bas gauche
	tabs[4] = buildchaine(coups, -1, 0, coord, PLAYER1, 5, 0); //gauche
	tabs[5] = buildchaine(coups, -1, -1, coord, PLAYER1, 5, 0); //haut gauche
	tabs[6] = buildchaine(coups, 0, -1, coord, PLAYER1, 5, 0); //haut
	tabs[7] = buildchaine(coups, 1, -1, coord, PLAYER1, 5, 0); //haut droite
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

int checkstring_for_victory(char *chaine)
{
	int i=0;
	while(chaine[i]==chaine[0])
	  i++;
	return (i);
}
