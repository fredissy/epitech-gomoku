#include "game.h"
t_dimensions getdimensions(t_noeud *gamestate)
{
  t_dimensions	dim;
  t_coup	*coup;
  signed int	xmin=DIM;
  signed int	xmax=-1;
  signed int  	ymin=DIM;
  signed int	ymax=-1;

  coup=gamestate->coup->next;
/*   while(coup) */
/*     { */
/*       if(coup) */
/* 	{ */
/* 	  xmin=coup->x; */
/* 	  xmax=coup->x; */
/* 	  ymin=coup->y; */
/* 	  ymax=coup->y; */
/* 	} */
/*       coup=coup->next; */
/*     } */
  while(coup)
    {
      xmin=MIN(coup->x,xmin);
      ymin=MIN(coup->y,ymin);
      xmax=MAX(coup->x,xmax);
      ymax=MAX(coup->y,ymax);
      coup=coup->next;
    }
  dim.maxleft=xmin;
  dim.width=xmax-xmin+1;
  dim.maxtop=ymin;
  dim.height=ymax-ymin+1;

  //on elargit un peu la fenetre en largeur...
  if(dim.maxleft-EXTRA<0)
    dim.maxleft=0;
  else
    dim.maxleft=dim.maxleft-EXTRA;
  if(dim.maxleft+dim.width+2*EXTRA>DIM)
    dim.width=DIM-dim.maxleft;
  else
    dim.width=dim.width+2*EXTRA;
  //... puis en hauteur
  if(dim.maxtop-EXTRA<0)
    dim.maxtop=0;
  else
    dim.maxtop=dim.maxtop-EXTRA;
  if(dim.maxtop+dim.height+2*EXTRA>DIM)
    dim.height=DIM-dim.maxtop;
  else
    dim.height=dim.height+2*EXTRA;
  //   printf("DIM:x=%d, y=%d, width=%d, height=%d\n", dim.maxleft, dim.maxtop, dim.width, dim.height);
  return(dim);

}

int	nbpions(t_noeud *gamepos)
{
  int		nbre;
  t_coup	*coup;

  nbre=0;
  coup=gamepos->coup;
  while(coup)
    {
      //      printf("[%d;%d]", coup->x, coup->y);
      coup=coup->next;
      nbre++;
    }
  //  printf("=>%d\n", nbre);
  return (nbre);
}

char occupant(t_coup *coup)
{
  //  printf("occ(%d,%d):%d\n", cellule->x, cellule->y, cellule->player);
  return(coup->player);
}


int	Value(t_noeud *noeud)
{
  if(noeud==0)
    return (0);
  else
    return(noeud->value);
}

int x(t_noeud *noeud)
{
  if(noeud==0)
    return (0);
  else
    return(noeud->x);
}

int y(t_noeud *noeud)
{
  if(noeud==0)
    return (0);
  else
    return(noeud->y);
}

void	avance(t_dimensions *dim, t_coord *initial)
{
	    (initial->x)++;
	     if(initial->x==dim->maxleft+dim->width)
	     {
	        initial->x=dim->maxleft;
	        initial->y++;
	     }
 }

int	occupee(t_coup *orig, t_coord coord)
{
  if(coord.x==DIM+1 || coord.y ==DIM+1)
    return (PLAYER1);
  while(orig)
    {
      if(orig->x == coord.x && orig->y == coord.y)
	    return(orig->player);
      orig=orig->next;
    }
  return (NOPLAYER);
}

//pareil que occupee'1', mais precise si dehors ou non
int	occupee2(t_coup *orig, t_coord coord)
{
  if(coord.x==DIM+1 || coord.y ==DIM+1)
    return (PLAYER1);
  if(coord.x>DIM||coord.y>DIM||coord.x<0||coord.y<0)
	  return(DEHORS);
  while(orig)
    {
      if(orig->x == coord.x && orig->y == coord.y)
	    return(orig->player);
      orig=orig->next;
    }
  return (NOPLAYER);
}


t_coord generatecoord(int x, int y)
{
	t_coord ret;
	ret.x=x;
	ret.y=y;
	return(ret);
}
int nbvoisins(t_noeud *jeu, t_coord coord)
{
	int x, y;
	t_coup *coup;
	x = coord.x;
	y = coord.y;
	coup = jeu->coup->next;
	while(coup)
	{
		if((coup->x == x-2 ||coup->x == x+2||coup->x==x) &&
		   (coup->y == y-2 ||coup->y == y+2||coup->y==y) &&
		   !(coup->x == x && coup->y == y))
			   return (1);
		if(((coup->x >= x-1 && coup->x <= x+1) &&
		   (coup->y >= y-1 && coup->y <= y+1)) && !(coup->x == x && coup->y == y))
			return (1);
		coup = coup->next;
	}
	return(0);
}
/*
int nbvoisins(t_noeud *jeu, t_coord coord)
{
	int x, y;
	int nbre=0;
	for(y=coord.y-2;y<coord.y+2;y++)
	  for(x=coord.y-2; x<coord.x+2;x++)
	  {printf(".");
	    if(occupee(jeu->coup, generatecoord(x,y)) != NOPLAYER && (x||y))
	      {
			printf("%d %d occupee\n", x, y);
		    nbre++;
	      }
	  }
	  printf("/");
	return (nbre);
}*/
