#include "game.h"
t_dimensions getdimensions(t_noeud *gamestate)
{
  t_dimensions	dim;
  t_coup	*coup;
  signed int	xmin=DIM;
  signed int	xmax=-1;
  signed int  	ymin=DIM;
  signed int	ymax=-1;

  coup=gamestate->coup;
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


void	displaymoves(t_coup *coup)
{
  printf("> ");
  while(coup)
    {
      printf("(%d;%d|%d)",coup->x, coup->y, coup->player);
      coup=coup->next;
    }
  printf("\n");
}

void	ajoutecoup(t_noeud *parent, t_coord coord, int player)
{
  t_coup	*prev;
  t_coup	*cur;
  t_coup	*newcoup;
  prev = parent->coup;
  while(prev)
    {
      cur=prev;
      prev=prev->next;
    }
  newcoup = malloc(1*sizeof(t_coup));
  newcoup->x = coord.x;
  newcoup->y = coord.y;
  newcoup->player = player;
  newcoup->next = 0;
  if(parent->coup)
    cur->next=newcoup;
  else
    parent->coup=newcoup;
}

void	avance(t_dimensions *dim, t_coord *initial, int rang)
{
  int	i;
  i = 0;

   while(i<rang)
    while(initial->y <= dim->maxtop+dim->height && i < rang)
      while(initial->x <= dim->maxleft+dim->width && i < rang)
	{
	  (initial->x)++;
	  i++;
	  if(initial->x==dim->maxleft+dim->width)
	    {
	      initial->x=dim->maxleft;
	      initial->y++;
	    }
	}
}
//donne le nbre de cases occupees avant celle en nouv
//                       .-------------------------'
int	avant(t_coord *nouv, t_coup *orig)
{
  int	nbre;
  nbre = 0;
  while(orig)
    {
      if(orig->y < nouv->y) //si sur une ligne avant
	nbre++;
      if(orig->y == nouv->y && orig->x <= nouv->x) //si sur la meme ligne, avant en x
	nbre++;
      orig=orig->next;
    }
  return nbre;
}

int	occupee(t_coup *orig, t_coord coord)
{
  while(orig)
    {
      //      printf("[%d;%d](%d;%d)\n", orig->x, orig->y, coord.x, coord.y);
      if(orig->x == coord.x && orig->y == coord.y)
	{
	  //	  printf("retour:%d\n",orig->player);
	  return(orig->player);
	}
      orig=orig->next;
    }
  return (NOPLAYER);
}

t_coord	saisie(signed char player)
{
  t_coord saisie;
  int	x = DIM + 1;
  int	y = DIM + 1;

  while(x<0 || x>DIM)
    {
      printf("joueur %d coord x? ", player+1);
      scanf("%d", &x);
    }
  while(y<0 || y>DIM)
    {
      printf("joueur %d coord y? ", player+1);
      scanf("%d", &y);
    }
  saisie.x = x;
  saisie.y = y;
  return(saisie);
}
