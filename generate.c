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
  gamepos->fils=moves;
  while(current < nbcas)
    {
      moves[current]=GenerateMove(gamepos, current, depth);
      //            printf("D:%d(%d/%d)", depth,current, nbcas);
      //            displaymoves(moves[current]->coup);
      //            printf("---\n");
      current++;
    }
 //   printf("(%d)%d moves\n", depth, nbcas);
  moves[nbcas]=0;
  return(moves);

}
/* on calcule le nombre de cas possibles, contenus dans une fenetre mobile
** ensuite on va generer toutes les situations possibles en ajoutant un pion
** sur une nouvelle case a chaque fois.
*/

//place un pion sur la numerocas case suivante
/* t_noeud	*GenerateMove(t_noeud *parent, int numerocas, int depth) */
/* { */
/*   t_noeud	*fils; */
/*   t_dimensions	dim; */
/*   t_coup	*newcoup; */
/*   t_coup	*prev; */
/*   t_coup	*orig; */
/*   int		flag; */
/*   //  int		i = 0; */
/*   int		x; */
/*   int		y; */

/*   if((fils = malloc(sizeof(t_noeud))) == NULL) */
/*     { */
/*       printf("Could not malloc(2)\n"); */
/*       exit(1); */
/*     } */
/*   fils->value=0; */
/*   fils->player=!parent->player; */
/*   orig=parent->coup; */
/*   //copie du premier pion de la liste */
/*   if(orig) */
/*     { */
/*       prev=(t_coup*)malloc(sizeof(t_coup)); */
/*       prev->x=orig->x; */
/*       prev->y=orig->y; */
/*       prev->player=orig->player; */
/*       prev->next=0; */
/*       fils->coup=prev; */
/*       orig=orig->next; */
/*     } */
/*   //on recopie les suivants */
/*   while(orig) */
/*     { */
/*       if((newcoup=(t_coup*)malloc(sizeof(t_coup)))==NULL) */
/* 	{ */
/* 	  printf("Could not malloc(3)!\n"); */
/* 	  exit(1); */
/* 	} */
/*       newcoup->x = orig->x; */
/*       newcoup->y = orig->y; */
/*       newcoup->player=orig->player; */
/*       newcoup->next=0; */
/*       prev->next=newcoup; */
/*       prev=newcoup; */
/*       orig=orig->next; */
/*     } */
/*   //on trouve les coordonnes du point suivant dans l'ideal */
/*   //s'il n'y avait pas d'autre pions sur le jeu */
/*   dim = getdimensions(parent); */
/*   //  printf("dimensions:%d*%d, %d;%d\n", dim.width, dim.height, dim.maxleft, dim.maxtop); */
/*   if(numerocas==0) */
/*     { */
/*       x=dim.maxleft; */
/*       y=dim.maxtop; */
/*       //      printf("x=%d, y=%d\n", x, y); */
/*     } */
/*   else */
/*     { */
/*       //      printf("x=%d+(%d%%%d)", dim.maxleft, numerocas, dim.width); */
/*       x = dim.maxleft + (numerocas%dim.width); */
/*       printf("x=%d; ", x); */
/*       //      printf("y=%d+(%d/%d)", dim.maxtop, numerocas, dim.width); */
/*       y = dim.maxtop + (numerocas/dim.width); */
/*       printf("y=%d\n", y); */
/*     } */
/*   //pour chaque pion deja present on regarde s'il est 'avant' */
/*   //le nouveau. si oui, on avance le nouveau pion d'un cran. */
/*   orig=parent->coup; */
/*   while(orig) */
/*     { */
/*       //sur une ligne precedente */
/*       if(orig->y < y) */
/* 	{ */
/* 	  printf("a(%d<%d):%d,%d=>",orig->y,y,x,y); */
/* 	  if(x==dim.width+dim.maxleft-1) */
/* 	    { */
/* 	      x=dim.maxleft; */
/* 	      y++; */
/* 	    } */
/* 	  else */
/* 	    x++; */
/* 	  printf("%d;%d",x,y); */
/* 	  flag=1; */
/* 	} */
/* 	  //a gauche sur la meme ligne */
/* 	  if(orig->y == y && orig->x <= x) */
/* 	    { */
/* 	      printf("b:%d;%d=>",x,y); */
/* 	      if(x==dim.width+dim.maxleft-1) */
/* 		{ */
/* 		  x=dim.maxleft; */
/* 		  y++; */
/* 		} */
/* 	      else */
/* 		x++; */
/* 	      printf("%d;%d",x,y); */
/* 	    } */
/* 	  orig=orig->next; */
/* 	  //      else */
/*       //	flag=0; */
/*     } */
/*   printf("\n"); */
/*   newcoup = malloc(sizeof(t_coup)); */
/*   newcoup->x = x; */
/*   newcoup->y = y; */
/*   newcoup->player = !parent->player; */
/*   newcoup->next = 0; */
/*   prev->next = newcoup; */
/*   fils->deep = depth; */
/*   fils->x=x; */
/*   fils->y=y; */
/*   fils->fils=0; */
/*   return(fils); */
/* } */
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
