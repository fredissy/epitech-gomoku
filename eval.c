#include "game.h"

int evalnode(t_noeud *gamestate, char player, t_args args)
{
//  t_tab	*tab;
  int	x;
  int	y;
  int	bestscore=0;
  int	score=0;
  t_dimensions	dim;
  t_coup	*coup;
//  player=gamestate->player;
  if(gamestate==0)
    return (0);
  coup=gamestate->coup;
  dim=getdimensions(gamestate);
//  tab=generatetable(gamestate->coup);
  x=dim.maxleft;
  y=dim.maxtop;
  while(coup)
    {
		if(coup->player==player)
		{
			score = evalcase(coup, coup->x, coup->y, player);
      		if(score==0)
      		return(0);
      		bestscore = MAX(score, bestscore);
		}
		coup = coup->next;
    }

//  if(args.debug==FULL_DEBUG)
//    {
	//	displaymoves(gamestate->coup);
	//	printf("eval=>%d(P%d)\n", bestscore, player+1);
//    }
  gamestate->value=bestscore;
  //free(tab);
  return(bestscore);
}

//evalue la case, tab=tableau representant le jeu,
//x et y coordonnees de la case a inspecter.
int	evalcase(t_coup *coups, int x, int y, char player)
{
  int	score=0;
  int tmpscore=0;
  t_coord coord;
  coord.x=x;
  coord.y=y;
  if(occupee(coups, coord)== NOPLAYER)
    return (0);
  if(x<=DIM-6 && x>=0)
  {
	 tmpscore = eval_line(coups, coord, 1, 0, player);
	 //if(tmpscore==0)
	 //	return (0);
     score = MAX(score, tmpscore);
  }

  if(y<=DIM-6 && y>=0 && x<=DIM-6 && x>=0)
  {
	 tmpscore = eval_line(coups, coord, 1, 1, player);
	 //if(tmpscore==0)
	 //	return (0);
     score = MAX(score, tmpscore);
  }

  if(y<=DIM-6 && y>=0)
  {
    tmpscore=eval_line(coups, coord, 0, 1, player);
    //if(tmpscore==0)
	//	return (0);
	score = MAX(score, tmpscore);
  }
  if(y<=DIM-6 && y>=0 && x>=5 && x<=DIM)
  {
    tmpscore=eval_line(coups, coord, -1, 1, player);
    //if(tmpscore==0)
	//  	return (0);
	score = MAX(score, tmpscore);
  }

  if(x>=5 && x<=DIM)
  {
 	tmpscore=eval_line(coups, coord, -1, 0, player);
    //if(tmpscore==0)
	//	return (0);
	score = MAX(score, tmpscore);
  }

  if(x>=5 && x<=DIM && y>=5 && y<=DIM)
  {
    tmpscore=eval_line(coups, coord, -1, -1, player);
    //if(tmpscore==0)
	//	return (0);
	score = MAX(score, tmpscore);
  }

  if(y>=5 && y<=DIM)
  {
	tmpscore=eval_line(coups, coord, 0, -1, player);
	//if(tmpscore==0)
	//	return (0);
	score = MAX(score, tmpscore);
  }

  if(x<=DIM-6 && x>=0 && y>=5 && y<=DIM)
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

int gameended(t_noeud *gamestate)
{
  return(gamestate->value>=5);
}
