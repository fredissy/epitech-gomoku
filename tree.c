#include "game.h"

t_coord	  MinMax(t_noeud *gamepos, int depth, char player)
{
  t_noeud *i;
  t_coord toplay;

  i=MaxMove(gamepos, depth, player, 1000, 1000);
  removearbre(gamepos);
  toplay.x=x(i);
  toplay.y=y(i);
  return(toplay);
}

t_noeud		*MaxMove(t_noeud *gamepos, int depth, char player, int alpha, int beta)
{
  t_noeud	*bestmove;
  t_noeud	**moves;
  int		i=0;
  if(gameended(gamepos)||depth==0)
    {
      evalnode(gamepos, player);
      return(gamepos);
    }
  else
    {
      bestmove=0;
      moves=GenerateMoves(gamepos, depth - 1);
      while(moves[i])
	{
	  t_noeud *curmove;
	  curmove = MinMove(moves[i], depth - 1, !player, alpha, beta);	
	  if(depth==MAXDEPTH)
	    {
	      printf("%d:%d\n", i, Value(curmove));
	      displaymoves(curmove->coup);
	    }
	    //	    printf("[%d] (%d, %d)=>%d\n", i, x(curmove)/*moves[i])*/, y(curmove/*(moves[i]*/), Value(curmove));
	  if(i==0)
	    {
	      bestmove=moves[i];
	      bestmove->value = Value(curmove);
	      gamepos->value = Value(curmove);
	      alpha = Value(curmove);
	      if(depth==MAXDEPTH)
		beta = Value(curmove);
	    }
	  if(Value(curmove)>Value(bestmove))
	    {
	      bestmove=moves[i];
	      bestmove->value = Value(curmove);
	      gamepos->value = Value(curmove);
	      alpha = Value(curmove);
	    }
	  //	  removearbrecontent(curmove);
	  //	  if(depth==MAXDEPTH)
	  // printf("delete ok %d\n", i);
	  if(alpha>beta)
	    return (bestmove);
	  i++;
	}
      return (bestmove);
    }
}

t_noeud		*MinMove(t_noeud *gamepos, int depth, char player, int alpha, int beta)
{
  t_noeud	*bestmove;
  t_noeud	*curmove;
  t_noeud	**moves;
  int		i = 0;

  if(gameended(gamepos)||depth==0)
    {
      evalnode(gamepos, player);
      return(gamepos);
    }
  else
    {
      bestmove=0;
      moves=GenerateMoves(gamepos, depth -1);
      while(moves[i])
	{
	  curmove = MaxMove(moves[i], depth - 1, !player, alpha, beta);
	  if(i==0)
	    {
	      gamepos->value=Value(curmove);
	      bestmove=moves[i];
	      bestmove->value = Value(curmove);
	      beta=Value(curmove);
	    }
	  if(Value(curmove)<Value(bestmove))
	    {
	      bestmove=moves[i];
	      bestmove->value = Value(curmove);
	      gamepos->value = Value(curmove);
	      beta=Value(curmove);
	    }
	  if(alpha>beta)
	    return(bestmove);
	  i++;
	}
      return (bestmove);
    }
}
