#include "game.h"

int evalnode(t_noeud *gamestate, char player, t_args args)
{
	int i;
  int	score=0;
  t_coup	*coup;
  t_coord coord;
  if(gamestate==0)
    return (0);
  coup=gamestate->coup;
  while(coup)
  {
	  coord.x=coup->x;
	  coord.y=coup->y;
	  if(coup->player ==player)
	  {
	      printf(" (%d;%d)", coord.x, coord.y);
		  i=evalcase_align(gamestate->coup, coord, player);
		  score+=2*i; //on aligne des pions, 2 points par pion aligné
		  printf("%d:", i);
		  score+=10*(fills_hole(gamestate->coup, coord, player)); //on remplit un xOxx adverse, 10x par remplissage
	//	  printf("%d:", score);
		  score+=30*(blocks_ennemy(gamestate->coup, coord, player));//on bloque une evolution vers un XXXX adverse, 10 points par blocage
	//	  printf("%d:", score);
		  score+=20*(prise_paire_adversaire(gamestate->coup, coord, player));//on prend une paire a l'adversaire, 15 points par prise
	//	  printf("%d:", score);
		  if(gamestate->paires[1] ==4)
		  	score-=100*(prise_paire_adversaire(gamestate->coup, coord, !player));//il nous reste 1 paire a prendre avant de mourir, donc -100
		  else
		    score-=30*(prise_paire_adversaire(gamestate->coup, coord, !player));//on se fait manger une paire, pas intéressant donc -15 points
	//	  printf("%d|", score);
		  //score-=100*(get_maxalign_coord(coord, gamestate, !player) == 5);//l'adversaire aligne 5 pions => -80 pour cette position
	  }
	  coup = coup->next;
  }
  printf(" ");
  score+=100*(get_maxalign_coord(coord, gamestate, player) == 5);//on réussit à aligner 5 pions => victoire, +100 points
  gamestate->value=/*best*/score;
//  printf(" %d %d => %d\n", coord.x, coord.y, score);
  return(score);
}

int	evalcase_align(t_coup *coups, t_coord coord, char player)
{
  int	score=0;
  int 	tmp;
  if(occupee(coups, coord)== NOPLAYER)
    return (0);
  if(coord.x<=DIM-6 && coord.x>=0)
  {
	 tmp = eval_line(coups, coord, 1, 0, player);
  	 score=MAX(score,tmp);
  }
  if(coord.y<=DIM-6 && coord.y>=0 && coord.x<=DIM-6 && coord.x>=0)
  {
 	tmp = eval_line(coups, coord, 1, 1, player);
 	score=MAX(score,tmp);
  }
  if(coord.y<=DIM-6 && coord.y>=0)
  {
	tmp = eval_line(coups, coord, 0, 1, player);
	score=MAX(score,tmp);
  }
  if(coord.y<=DIM-6 && coord.y>=0 && coord.x>=5 && coord.x<=DIM)
  {
	tmp = eval_line(coups, coord, -1, 1, player);
	score=MAX(score,tmp);
  }
  if(coord.x>=5 && coord.x<=DIM)
  {
    tmp = eval_line(coups, coord, -1, 0, player);
	score=MAX(score,tmp);
  }
  if(coord.x>=5 && coord.x<=DIM && coord.y>=5 && coord.y<=DIM)
  {
    tmp = eval_line(coups, coord, -1, -1, player);
	score=MAX(score,tmp);
  }
  if(coord.y>=5 && coord.y<=DIM)
  {
	tmp= eval_line(coups, coord, 0, -1, player);
	score=MAX(score,tmp);
  }
  if(coord.x<=DIM-5 && coord.x>=0 && coord.y>=5 && coord.y<=DIM)
  {
	tmp = eval_line(coups, coord, 1, -1, player);
	score=MAX(score,tmp);
  }
  return(score);
}

int	eval_line(t_coup *coups, t_coord coord, signed int xm, signed int ym, char player)
{
	char	player_2;
	int		i=0;
	int		x;
	int		y;
	int		space=0;

	if(player==PLAYER1)
	  player_2=PLAYER2;
	else
      player_2=PLAYER1;

    x = coord.x;
    y = coord.y;
i=0;
    while((occupee2(coups, generatecoord(x,y)) == player) && i<5 )
    {
		x+=xm;
		y+=ym;
		i++;
	}
	while(space+i<5 && (occupee2(coups, generatecoord(x,y)) == NOPLAYER))
	{
	    x+=xm;
		y+=ym;
		space++;
	}
    x = coord.x;
    y = coord.y;
	i--;
	while(i<5 && (occupee2(coups, generatecoord(x,y))==player))
	{
		x-=xm;
		y-=ym;
		i++;
	}

	while(space+i<5 && (occupee2(coups, generatecoord(x,y)) == NOPLAYER))
	{
	    x-=xm;
		y-=ym;
		space++;
	}
if(space+i>=5)
return(i);
else
return(0);

}
// principe: on remplit un tableau de 6 chars avec les 6 cases a analyser,
// on compte le score possible avec cette position, enfin on le renvoie.
/*
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
  while(i<10 && (cells[i]!=player_2 && cells[i]!=DEHORS))
    {
		nbfree++;
		i++;
    }
  if(nbfree+score>=5)
	return(score);
  else
  	return (0);
}
*/

//on renvoie 0 si aucun gagnant, 1 pour player1, et 2 pour player2
int gameended(t_noeud *gamestate, char player)
{
	t_coup *coup;
	int	nbalign=0;
	coup = gamestate->coup;
	while(coup)
	{
		nbalign=get_maxalign_coup(coup, gamestate, player);
		if(nbalign==5)
		  return (player+1);
		coup = coup->next;
	}
	if(gamestate->paires[0] == NBPAIRES)
		return (1);
	if(gamestate->paires[1] == NBPAIRES)
		return (2);
return(0);
}

int checkstring_for_victory(char *chaine)
{
	int i=0;
	while(chaine[i]==chaine[0])
	  i++;
	return (i);
}
