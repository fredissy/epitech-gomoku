#include "game.h"

t_noeud*GenerateMove(t_noeud *parent, int numerocas, int nbcas, int depth, t_dimensions dim)
{
  t_noeud	*fils;
  t_coup	*newcoup;
  t_coup	*prev;
  t_coup	*orig;
  t_coord	coord;
  int		i = 0;
  int		x;
  int		y;
  //si on est arrivé au bout...
  if(numerocas>=nbcas)
    return(FINI);
  x = dim.maxleft;
  y = dim.maxtop;
  coord.x = x;
  coord.y = y;
  //  if(occupee(parent->coup, coord) != -1)
  //  i--;

  while(i<numerocas)
    {
      //printf("boucle %d sur %d\n",i, numerocas);
      avance(&dim, &coord);
      if(occupee(parent->coup, coord) != -1)
        i--;
      i++;
    }
  //printf("---\ngen:%d %d:\n", coord.x, coord.y);
  //si les coordonnées générées n'ont pas de voisins dans les 2 cases autour...
  if (!nbvoisins(parent, coord))
    {
//      printf("(%d;%d)", coord.x, coord.y);
      return(NULL);
    }
  //printf("=>ok\n");
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

  newcoup=malloc(sizeof(t_coup));
  newcoup->x=coord.x;
  newcoup->y=coord.y;
  newcoup->player=!parent->player;
  newcoup->next=0;
  prev->next=newcoup;
  fils->paires[0]=parent->paires[0];
  fils->paires[1]=parent->paires[1];
  fils->deep=depth;
  fils->x=coord.x;
  fils->y=coord.y;
  //fils->fils = 0;
  //printf("gen:%d %d:\n", coord.x, coord.y);
  return(fils);

}
