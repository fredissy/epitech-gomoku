#include "game.h"

void printchaine(char *chaine, int len)
{
	int i = 0;
	while(i<len)
		printf("%c",chaine[i++]);
	//printf(" ");
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

void showgrid(t_noeud *gamestate)
{
	int x=0;
	int y=0;
	char player;
	t_dimensions dim;

	dim = getdimensions(gamestate);
	printf("   ");
	while(x<dim.maxleft+dim.width)
	{
		if(x<10)
		  printf("%d ", x);
		else
		  printf("%d",x);
		x++;
	}
	printf("\n--+");
	for(x=0;x<dim.maxleft+dim.width;x++)
	  printf("-+");
	printf("\n");

	while(y<dim.maxtop+dim.height)
	{
	  if(y<10)
	    printf(" %d", y);
	  else
	    printf("%d", y);
      printf("|");
	  x=0;
	  while(x<dim.maxleft+dim.width)
	  {
        player=dans(gamestate->coup, generatecoord(x, y), PLAYER1);
        if(player==MOI)
			printf("o|");
		if(player==ADVERSAIRE)
			printf("x|");
		if(player==PERSONNE)
			printf("_|");
		x++;
	  }
	  printf("\n");
	  y++;
	}
}
