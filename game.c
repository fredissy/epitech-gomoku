#include "game.h"

int		main(int ac, char **av)
{
  t_args	args;
  args = arguments(ac, av);
  if(args.players==DEUXJOUEURS)
    gameloop_2p(args);
  else
    gameloop_1p(args);
  return (0);
}

void		gameloop_1p(t_args args)
{
  int		gagne = 0;
  t_noeud	*jeu;
  t_coord	toplay;
  jeu = malloc(sizeof(t_noeud));
  jeu->coup=0;
  jeu->player = PLAYER1;
  jeu->paires[0] = 0;
  jeu->paires[1] = 0;
  ajoutecoup(jeu, generatecoord(-1, -1), DEHORS);
  while(!gagne)
    {
      toplay=saisie(PLAYER1, jeu->coup);
      ajoutecoup(jeu, toplay, PLAYER1);
      dealprises(jeu, toplay, PLAYER1);
	  gagne=gameended(jeu);
	  if(!gagne)
	  {
		  toplay = MinMax(jeu, MAXDEPTH, PLAYER1, args);
		  if(args.debug==RUN_DEBUG||args.debug==FULL_DEBUG)
			printf("ordi joue sur:(%d;%d)\n",toplay.x, toplay.y);
		  ajoutecoup(jeu, toplay, PLAYER2);
		  dealprises(jeu, toplay, PLAYER2);
		  if(args.debug==FULL_DEBUG)
			displaymoves(jeu->coup);
		  showgrid(jeu);
		  infoprises(jeu);
		  gagne=gameended(jeu);
		}
	}
}

void	gameloop_2p(t_args args)
{
  int		gagne = 0;
  t_noeud	*jeu;
  t_coord	toplay;
  jeu = malloc(sizeof(t_noeud));
  jeu->coup=0;
  jeu->player = PLAYER1;
  jeu->paires[0] = 0;
  jeu->paires[1] = 0;
  ajoutecoup(jeu, generatecoord(-1, -1), DEHORS);
  while(!gagne)
    {
      toplay=saisie(PLAYER1, jeu->coup);
      ajoutecoup(jeu, toplay, PLAYER1);
      dealprises(jeu, toplay, PLAYER1);
      showgrid(jeu);
      infoprises(jeu);
      gagne = gameended(jeu);
      if(!gagne)
      {
		  if(args.debug==FULL_DEBUG)
			displaymoves(jeu->coup);
		  toplay = saisie(PLAYER2, jeu->coup);
		  ajoutecoup(jeu, toplay, PLAYER2);
		  dealprises(jeu, toplay, PLAYER2);
		  showgrid(jeu);
		  infoprises(jeu);
		  gagne = gameended(jeu);
		  if(args.debug==FULL_DEBUG)
			displaymoves(jeu->coup);
		}
	}
}

t_args arguments(int ac, char **av)
{
  t_args	args;
  int	opt;
  args.players=0;
  args.debug=0;
  while((opt = getopt(ac, av, "dDm")) != -1)
    {
      args.players = (opt=='m'?args.players+DEUXJOUEURS:args.players);
      args.debug=(opt=='d'?args.debug+RUN_DEBUG:args.debug);
      args.debug=(opt=='D'?FULL_DEBUG:args.debug);
    }
  if(args.players==DEUXJOUEURS)
    printf("2-player mode\n");
  if(args.debug==RUN_DEBUG)
    printf("Running display mode\n");
  if(args.debug==FULL_DEBUG)
    printf("Running FULL debug mode\n");
  return(args);
}
