#include "game.h"

t_noeud	**GenerateMoves(t_noeud *gamepos, int depth)
{
  t_dimensions	dim;
  t_noeud	**moves;
  int		nbcas;
  int		current=0;

  dim = getdimensions(gamepos);
  nbcas = dim.width * dim.height - nbpions(gamepos);
  if((moves = malloc(nbcas*sizeof(t_noeud *)))==NULL)
    {
      printf("Could not malloc(1) !\n");
      exit(1);
    }

  while(current < nbcas)
    {
      moves[current]=GenerateMove(gamepos, current, depth);
      //      printf("D:%d(%d/%d)   ", depth,current, nbcas);
      //      displaymoves(moves[current]->coup);
      //      printf("---\n");
      current++;
    }

 //   printf("(%d)%d moves\n", depth, nbcas);
  moves[nbcas]=0;
  gamepos->fils=moves;
  return(moves);

}

/* on calcule le nombre de cas possibles, contenus dans une fenetre mobile
** ensuite on va generer toutes les situations possibles en ajoutant un pion
** sur une nouvelle case a chaque fois.
*/

t_noeud*GenerateMove(t_noeud *parent, int numerocas, int depth)
{
  t_noeud	*fils;
  t_dimensions	dim;
  t_coup	*newcoup;
  t_coup	*prev;
  t_coup	*orig;
  t_coord	coord;
  //  int		i = 0;
  int		x;
  int		y;

  dim = getdimensions(parent);
  if((fils = malloc(sizeof(t_noeud))) == NULL)
    {
      printf("Could not malloc(2)\n");
      exit(1);
    }
  fils->value=0;
  fils->player=!parent->player;
  orig=parent->coup;
  if(orig)
    {
      prev=(t_coup*)malloc(sizeof(t_coup));
      prev->x=orig->x;
      prev->y=orig->y;
      prev->player=orig->player;
      prev->next=0;
      fils->coup=prev;
      orig=orig->next;
    }
  while(orig)
    {
      if((newcoup=(t_coup*)malloc(sizeof(t_coup)))==NULL)
	{
	  printf("Could not malloc(3)!\n");
	  exit(1);
	}
      newcoup->x = orig->x;
      newcoup->y = orig->y;
      newcoup->player=orig->player;
      newcoup->next=0;
      prev->next=newcoup;
      prev=newcoup;
      orig=orig->next;
    }
  x = dim.maxleft;
  y = dim.maxtop;
  coord.x = x;
  coord.y = y;

  avance(&dim, &coord, numerocas);
  avance(&dim, &coord, avant(&coord, parent->coup));
  //  printf("%d %d\n", coord.x, coord.y);
  while(occupee(parent->coup, coord) != -1)
    {
      avance(&dim, &coord, 1);
      //      printf("%d %d\n", coord.x, coord.y);
    }
  newcoup=malloc(sizeof(t_coup));
  newcoup->x=coord.x;
  newcoup->y=coord.y;
  newcoup->player=!parent->player;
  newcoup->next=0;
  prev->next=newcoup;
  fils->deep=depth;
  fils->x=x;
  fils->y=y;
  fils->fils=0;
  return(fils);
}
