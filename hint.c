#include "game.h"

void showhint(t_coup *coups, signed char player)
{
	t_noeud noeud;
	t_coord hint;
	t_args args;
	args.debug = 0;

	noeud.x = coups->x;
	noeud.y = coups->y;
	noeud.player = !player;

	noeud.coup = duplicate(coups);
	hint = MinMax(&noeud, MAXDEPTH, !player, args);
	printf("(%d;%d)\n", hint.x, hint.y);
	delcoups(noeud.coup);
}


void delcoups(t_coup *todelete)
{
	t_coup *suivant;
	if(todelete)
	{
		suivant=todelete->next;
		free(todelete);
		delcoups(suivant);
	}
}
