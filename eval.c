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
  while(coup)
    {
		if(coup->player==player)
		{
			coord.x=coup->x;
			coord.y=coup->y;
			score = evalcase_align(gamestate->coup, coord, player);
      		if(score==0)
      			return(0);
      		bestscore = MAX(score, bestscore);
		}
		coup = coup->next;
    }
 // printf("align maxi=%d\n", bestscore);
  coord.x=gamestate->x;
  coord.y=gamestate->y;
  if(blocks_ennemy(gamestate->coup, coord, player))
    score=10;
  bestscore = MAX(score, bestscore);
  //printf("MAXALIGN=%d\n", get_maxalign(gamestate->coup, gamestate));
  if(get_maxalign(gamestate->coup, gamestate) == 5)
  	score=20;
  gamestate->value=bestscore;
  return(bestscore);
}

int	evalcase_align(t_coup *coups, t_coord coord, char player)
{
  int	score=0;
  int tmpscore=0;

  //t_coord coord;
  //coord.x=x;
  //coord.y=y;
  if(occupee(coups, coord)== NOPLAYER)
    return (0);
  if(coord.x<=DIM-6 && coord.x>=0)
  {
	 tmpscore = eval_line(coups, coord, 1, 0, player);
	 //if(tmpscore==0)
	 //	return (0);
     score = MAX(score, tmpscore);
  }

  if(coord.y<=DIM-6 && coord.y>=0 && coord.x<=DIM-6 && coord.x>=0)
  {
	 tmpscore = eval_line(coups, coord, 1, 1, player);
	 //if(tmpscore==0)
	 //	return (0);
     score = MAX(score, tmpscore);
  }

  if(coord.y<=DIM-6 && coord.y>=0)
  {
    tmpscore=eval_line(coups, coord, 0, 1, player);
    //if(tmpscore==0)
	//	return (0);
	score = MAX(score, tmpscore);
  }
  if(coord.y<=DIM-6 && coord.y>=0 && coord.x>=5 && coord.x<=DIM)
  {
    tmpscore=eval_line(coups, coord, -1, 1, player);
    //if(tmpscore==0)
	//  	return (0);
	score = MAX(score, tmpscore);
  }

  if(coord.x>=5 && coord.x<=DIM)
  {
 	tmpscore=eval_line(coups, coord, -1, 0, player);
    //if(tmpscore==0)
	//	return (0);
	score = MAX(score, tmpscore);
  }

  if(coord.x>=5 && coord.x<=DIM && coord.y>=5 && coord.y<=DIM)
  {
    tmpscore=eval_line(coups, coord, -1, -1, player);
    //if(tmpscore==0)
	//	return (0);
	score = MAX(score, tmpscore);
  }

  if(coord.y>=5 && coord.y<=DIM)
  {
	tmpscore=eval_line(coups, coord, 0, -1, player);
	//if(tmpscore==0)
	//	return (0);
	score = MAX(score, tmpscore);
  }

  if(coord.x<=DIM-6 && coord.x>=0 && coord.y>=5 && coord.y<=DIM)
  {
	tmpscore=eval_line(coups, coord, 1, -1, player);
	//if(tmpscore==0)
	//	return (0);
	score = MAX(score, tmpscore);
  }
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
//  if(nbfree+score>=5)
//  	printf("(%d;%d) %d ",backup.x, backup.y, score);
  if(nbfree+score>=5)
	return(score);
  else
  	return (0);
}

//t_tab *generatetable(t_coup *first)
//{
 // t_tab	*table;
  //int	x=0;
//  int	y=0;
//
//  table = malloc(sizeof(t_tab));
//  while(y<DIM)
//    {
//      x=0;
//      while(x<DIM)
//	{
//	  table->t[x][y].player=NOPLAYER;
//	  table->t[x][y].x=x;
//	  table->t[x][y].y=y;
//	  x++;
//	}
//      y++;
//    }
//  while(first)
//    {
//      table->t[first->x][first->y].player=first->player;
//      first=first->next;
//    }
//  return (table);
//}

int blocks_ennemy(t_coup *coups, t_coord coord, char player)
{
	char	*tabs[8];
	int		nbre = 0;
	int		i=0;
	tabs[0] = buildchaine2(coups, 1, 0, coord, player, 6); //droite
	tabs[1] = buildchaine2(coups, 1, 1, coord, player, 6); //bas droite
	tabs[2] = buildchaine2(coups, 0, 1, coord, player, 6); //bas
	tabs[3] = buildchaine2(coups, -1, 1, coord, player, 6); //bas gauche
	tabs[4] = buildchaine2(coups, -1, 0, coord, player, 6); //gauche
	tabs[5] = buildchaine2(coups, -1, -1, coord, player, 6); //haut gauche
	tabs[6] = buildchaine2(coups, 0, -1, coord, player, 6); //haut
	tabs[7] = buildchaine2(coups, 1, -1, coord, player, 6); //haut droite
	tabs[8] = 0;

	while(i<8)
	{
//		printf("%s ", tabs[i]);
		nbre+=does_block_ennemy(tabs[i++], player);
	}
//	printf("\n");
	i=0;
	while(i<8)
		free(tabs[i++]);
	if(nbre)
{
	printf("ennemy blocked!:");displaymoves(coups);
	return(1);
}
	return (0);
}

int does_block_ennemy(char *chaine, signed char player)
{
	//definir les situations sous forme de chaine, et les comparer à chaine
	//un peu comme la vérif du double 3
	char modele1[4]={MOI, ADVERSAIRE, ADVERSAIRE, ADVERSAIRE};
	char modele2[5]={MOI, ADVERSAIRE, ADVERSAIRE, ADVERSAIRE, MOI};
	if(!strncmp((char*)&modele2, chaine, 5))
		return(0);
	if(!strncmp((char*)&modele1, chaine, 4))
		return(1);
	return(0);
}

char		*buildchaine2(t_coup *coups, int dx, int dy, t_coord coord, signed char player, int size)
{
	char	*chaine;
	int		i = 0;

	chaine = malloc((size-1)*sizeof(char));
	while(i<size)
	{
		chaine[i] = dans(coups, coord, player);
		coord.x+=dx;
		coord.y+=dy;
		i++;
	}
	chaine[size]=0;
	return (chaine);
}


int gameended(t_noeud *gamestate)
{
	t_coup *coup;
	int	nbalign=0;
	coup = gamestate->coup;
	while(coup && nbalign <5)
	{
		nbalign=get_maxalign(coup, gamestate);
		coup = coup->next;
	}
	return(nbalign==5);
}

int get_maxalign(t_coup *tocheck, t_noeud *gamestate)
{
	t_coup *coups;
	t_coord coord;
	char	*tabs[8];
	int		nbre = 0;
	int		bestnbre=0;
	int		i=0;
	coord.x=gamestate->x;
	coord.y=gamestate->y;
	coups = gamestate->coup;

	tabs[0] = buildchaine2(coups, 1, 0, coord, PLAYER1, 5); //droite
	tabs[1] = buildchaine2(coups, 1, 1, coord, PLAYER1, 5); //bas droite
	tabs[2] = buildchaine2(coups, 0, 1, coord, PLAYER1, 5); //bas
	tabs[3] = buildchaine2(coups, -1, 1, coord, PLAYER1, 5); //bas gauche
	tabs[4] = buildchaine2(coups, -1, 0, coord, PLAYER1, 5); //gauche
	tabs[5] = buildchaine2(coups, -1, -1, coord, PLAYER1, 5); //haut gauche
	tabs[6] = buildchaine2(coups, 0, -1, coord, PLAYER1, 5); //haut
	tabs[7] = buildchaine2(coups, 1, -1, coord, PLAYER1, 5); //haut droite
	tabs[8] = 0;

	while(i<8)
	{
		nbre = checkstring_for_victory(tabs[i++]);
		bestnbre=MAX(nbre, bestnbre);
	}
	i=0;
	while(i<8)
		free(tabs[i++]);
//	if(nbre)
      return(bestnbre);
}


int checkstring_for_victory(char *chaine)
{
	int i=0;
	while(chaine[i]==chaine[0])
	  i++;
	return (i);
}
