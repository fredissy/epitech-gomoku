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
  player=gamestate->player;

  if(gamestate==0)
    return (0);
  coup=gamestate->coup;
  dim=getdimensions(gamestate);
//  tab=generatetable(gamestate->coup);
  x=dim.maxleft;
  y=dim.maxtop;

  while(coup)
    {
      score = evalcase(gamestate->coup, coup->x, coup->y, player);
      bestscore = MAX(score, bestscore);
      coup = coup->next;
    }
  if(args.debug==FULL_DEBUG)
    {
		displaymoves(gamestate->coup);
		printf("=>%d(P%d)\n", bestscore, player+1);
    }
  gamestate->value=bestscore;
  //free(tab);
  return(bestscore);
}

//evalue la case, tab=tableau representant le jeu,
//x et y coordonnees de la case a inspecter.
int	evalcase(t_coup *coups, int x, int y, char player)
{
  int	score=0;
  t_coord coord;
  coord.x=x;
  coord.y=y;
  if(occupee(coups, coord)== NOPLAYER)
    return (0);
  if(x<=DIM-6 && x>=0)
    score = MAX(score, eval_line(coups, coord, 1, 0, player));
  if(y<=DIM-6 && y>=0 && x<=DIM-6 && x>=0)
    score = MAX(score, eval_line(coups, coord, 1, 1, player));
  if(y<=DIM-6 && y>=0)
    score = MAX(score, eval_line(coups, coord, 0, 1, player));
  if(y<=DIM-6 && y>=0 && x>=5 && x<=DIM)
    score = MAX(score, eval_line(coups, coord, -1, 1, player));
  if(x>=5 && x<=DIM)
    score = MAX(score, eval_line(coups, coord, -1, 0, player));
  if(x>=5 && x<=DIM && y>=5 && y<=DIM)
    score = MAX(score, eval_line(coups, coord, -1, -1, player));
  if(y>=5 && y<=DIM)
    score = MAX(score, eval_line(coups, coord, 0, -1, player));
  if(x<=DIM-6 && x>=0 && y>=5 && y<=DIM)
    score = MAX(score, eval_line(coups, coord, 1, -1, player));
  return(score);
}

//principe: on remplit un tableau de 6 chars avec les 6 cases a analyser,
// et on compte le score possible avec cette position, enfin on le renvoie.
int	eval_line(t_coup *coups, t_coord coord, signed int xm, signed int ym, char player)
{
  char	cells[6];
  int	i=0;
  char	player_2;
  int	score;

  if(player==PLAYER1)
    player_2=PLAYER2;
  else
    player_2=PLAYER1;
  //on construit la ligne a inspecter
  for(i=0;i<6;i++)
  {
//  cells[i]=(&tab->t[x+(xm*i)][y+(ym*i)])->player;
	cells[i] =occupee(coups, coord);
	coord.x+=xm;
	coord.y+=ym;
  }
  i=1;
  score=1;
  while(cells[i]==player && i<6)
    {
      score++;
      i++;
    }
  //  printf(" (%d) ", score);
  while(i<6)
    {
      if(cells[i]==player_2)
	score=0;
      i++;
    }
  //   printf(" => %d\n", score);
  return(score);
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
