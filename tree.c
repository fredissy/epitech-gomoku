#include "game.h"

t_coord	  MinMax(t_noeud *gamepos, int depth, char player, t_args args)
{
  t_noeud *i;
  t_coord toplay;

  i=MaxMove(gamepos, depth, player, 1000, 1000, args);
  toplay.x=x(i);
  toplay.y=y(i);
  //  removearbrecontent(i);
  return(toplay);
}

t_noeud		*MaxMove(t_noeud *gamepos, int depth, char player, int alpha, int beta, t_args args)
{
  t_noeud	*bestmove;
  t_noeud	**moves;

  int		i=0;
  if(gameended(gamepos)||depth==0)
    {
      evalnode(gamepos, player, args);
      return(gamepos);
    }
  else
    {
      bestmove=0;
      moves=GenerateMoves(gamepos, depth - 1);
      while(moves[i])
	{
	  t_noeud	*curmove;
	  curmove = MinMove(moves[i], depth - 1, !player, alpha, beta, args);	
	  if(depth==MAXDEPTH && args.debug==FULL_DEBUG)
	    {
	      printf("MAX:%d:%d\n", i, Value(curmove));
	      displaymoves(curmove->coup);
	    }
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
	  if(alpha>beta)
	    return (bestmove);
	  i++;
	}
      return (bestmove);
    }
}

t_noeud		*MinMove(t_noeud *gamepos, int depth, char player, int alpha, int beta, t_args args)
{
  t_noeud	*bestmove;
  t_noeud	*curmove;
  t_noeud	**moves;
  int		i = 0;

  if(gameended(gamepos)||depth==0)
    {
      evalnode(gamepos, player, args);
      return(gamepos);
    }
  else
    {
      bestmove=0;
      moves=GenerateMoves(gamepos, depth -1);
      while(moves[i])
	{
	  curmove = MaxMove(moves[i], depth - 1, !player, alpha, beta, args);
	  if(depth==MAXDEPTH && args.debug==FULL_DEBUG)
	    {
	      printf("depth=%dmin:%d:%d\n",depth, Value(curmove), Value(bestmove));
	      displaymoves(curmove->coup);
	    }
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