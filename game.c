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
/*   int		x; */
/*   int		y; */
  int		gagne = 0;
  t_noeud	*jeu;
  t_coord	toplay;
  jeu = malloc(sizeof(t_noeud));
  while(!gagne)
    {
      toplay=saisie(PLAYER1);
      ajoutecoup(jeu, toplay, PLAYER1);
      jeu->player = PLAYER1;
      if(evalnode(jeu, PLAYER1)==5)
	printf("Joueur 1 a gagne!\n");
      toplay = MinMax(jeu, MAXDEPTH, PLAYER1);
      if(args.debug==RUN_DEBUG)
	printf("ordi joue sur:(%d;%d)\n",toplay.x, toplay.y);
      ajoutecoup(jeu, toplay, PLAYER2);
      if(args.debug==RUN_DEBUG)
	displaymoves(jeu->coup);
      if(evalnode(jeu, PLAYER2)==5)
	printf("Joueur 2 a gagne!\n");
      gagne = gameended(jeu);
      }
}

void	gameloop_2p(t_args args)
{
  int		gagne = 0;
  t_noeud	*jeu;
  t_coord	toplay;
  jeu = malloc(sizeof(t_noeud));
  while(!gagne)
    {
      toplay=saisie(PLAYER1);
      ajoutecoup(jeu, toplay, PLAYER1);
      if(evalnode(jeu, PLAYER1)==5)
	printf("Joueur 1 a gagne!\n");
      jeu->player = PLAYER1;
      toplay = saisie(PLAYER2);
      ajoutecoup(jeu, toplay, PLAYER2);
      if(args.debug==RUN_DEBUG)
	displaymoves(jeu->coup);
      if(evalnode(jeu, PLAYER2)==5)
	printf("Joueur 2 a gagne!\n");

      gagne = gameended(jeu);
    }
}

t_args arguments(int ac, char **av)
{
  t_args	args;
  int	opt;
  args.players=0;
  args.debug=0;
  while((opt = getopt(ac, av, "dm")) != -1)
    {
      args.players = (opt=='m'?args.players+DEUXJOUEURS:args.players);
      args.debug=(opt=='d'?args.debug+RUN_DEBUG:args.debug);
    }
  if(args.players==DEUXJOUEURS)
    printf("2-player mode\n");
  if(args.debug)
    printf("Running debug mode\n");
  return(args);
}
