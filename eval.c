#include "game.h"

int evalnode(t_noeud *gamestate, char player, t_args args)
{

  int	score=0;
  t_coup	*coup;
  t_coord coord;
  if(gamestate==0)
    return (0);
  coup=gamestate->coup;
  while(coup)
  {//Faire un test comme quoi on n'évalue pas si le joueur du coup n'est pas notre player
	  coord.x=coup->x;
	  coord.y=coup->y;
	  if(coup->player ==player)
	  {
		  score+=2*evalcase_align(gamestate->coup, coord, player); //on aligne des pions, 2 points par pion aligné
		  score+=10*(fills_hole(gamestate->coup, coord, player)); //on remplit un xOxx adverse, 10x par remplissage
		  score+=10*(blocks_ennemy(gamestate->coup, coord, player));//on bloque une evolution vers un XXXX adverse, 10 points par blocage
		  score+=15*(prise_paire_adversaire(gamestate->coup, coord, player));//on prend une paire a l'adversaire, 15 points par prise
		  score-=15*(prise_paire_adversaire(gamestate->coup, coord, !player));//on se fait manger une paire, pas intéressant donc -15 points
		  score+=100*(get_maxalign_coord(coord, gamestate) == 5);//on réussit à aligner 5 pions => victoire, +100 points
		  gamestate->value=/*best*/score;
	  }
	  coup = coup->next;
  }
//  printf(" %d %d => %d\n", coord.x, coord.y, score);
  return(score);
}

int	evalcase_align(t_coup *coups, t_coord coord, char player)
{
  int	score=0;

  if(occupee(coups, coord)== NOPLAYER)
    return (0);
  if(coord.x<=DIM-6 && coord.x>=0)
  	 score=MAX(score,eval_line(coups, coord, 1, 0, player));
  if(coord.y<=DIM-6 && coord.y>=0 && coord.x<=DIM-6 && coord.x>=0)
  	score=MAX(score,eval_line(coups, coord, 1, 1, player));
  if(coord.y<=DIM-6 && coord.y>=0)
  	score=MAX(score,eval_line(coups, coord, 0, 1, player));
  if(coord.y<=DIM-6 && coord.y>=0 && coord.x>=5 && coord.x<=DIM)
	score=MAX(score,eval_line(coups, coord, -1, 1, player));
  if(coord.x>=5 && coord.x<=DIM)
    score=MAX(score,eval_line(coups, coord, -1, 0, player));
  if(coord.x>=5 && coord.x<=DIM && coord.y>=5 && coord.y<=DIM)
    score=MAX(score,eval_line(coups, coord, -1, -1, player));
  if(coord.y>=5 && coord.y<=DIM)
	score=MAX(score,eval_line(coups, coord, 0, -1, player));
  if(coord.x<=DIM-6 && coord.x>=0 && coord.y>=5 && coord.y<=DIM)
	score=MAX(score,eval_line(coups, coord, 1, -1, player));
  return(score);
}

// principe: on remplit un tableau de 6 chars avec les 6 cases a analyser,
// on compte le score possible avec cette position, enfin on le renvoie.
int	eval_line(t_coup *coups, t_coord coord, signed int xm, signed int ym, char player)
{
  char	cells[9];
  int	i=0;
  int	nbfree=0;
  char	player_2;
  int	score;
  //t_coord backup;

  //si la case d'origine n'appartient pas au joueur, ca ne vaut rien
  if(occupee(coups, coord)!=player)
    return(0);

//  backup=coord;
  if(player==PLAYER1)
    player_2=PLAYER2;
  else
    player_2=PLAYER1;

  //on construit la ligne a inspecter
  coord.x-=4*xm;
  coord.y-=4*ym;
  for(i=0;i<10;i++)
  {
	cells[i] =occupee2(coups, coord);
	coord.x+=xm;
	coord.y+=ym;
  }

  i=0;
  score=0;
  while(cells[i]!=player && i<10)
  {
	nbfree++;
	if(cells[i]==player_2||cells[i]==DEHORS)
		nbfree=0;
  	i++;
  }
  while(cells[i]==player && i<10)
    {
      score++;
      i++;
    }
  while(i<10 && cells[i]!=player_2)
    {
		nbfree++;
		i++;
    }
  if(nbfree+score>=5)
	return(score);
  else
  	return (0);
}

int gameended(t_noeud *gamestate)
{
	t_coup *coup;
	int	nbalign=0;
	coup = gamestate->coup;
	while(coup)
	{
		nbalign=get_maxalign_coup(coup, gamestate);
		if(nbalign==5)
		  return (1);
		coup = coup->next;
	}
	return(nbalign==5);
}

int checkstring_for_victory(char *chaine)
{
	int i=0;
	while(chaine[i]==chaine[0])
	  i++;
	return (i);
}
