#include "game.h"

t_coord	  MinMax(t_noeud *gamepos, int depth, char player, t_args args)
{
  t_noeud *i;
  t_coord toplay;
  i=MaxMove(gamepos, depth, player, 1000, 1000, args);
  toplay.x=x(i);
  toplay.y=y(i);
//  printf("   "); displaymoves(i->coup);
  //  removearbrecontent(i);
  return(toplay);
}

t_noeud		*MaxMove(t_noeud *gamepos, int depth, char player, int alpha, int beta, t_args args)
{
  t_noeud	*bestmove;
//  t_noeud	**moves;
  t_noeud   *move;
  t_dimensions dim;
  int		i=0;
  int		nbcas;


  if(/*gameended(gamepos)||*/depth==0)
    {
	//  printf("DEPTH=0 %d\n", PLAYER2);
      evalnode(gamepos, !player, args);
      //evalnode(gamepos, PLAYER2, args);
      return(gamepos);
    }
  else
    {
	  if((bestmove = malloc(sizeof(t_noeud)))==NULL)
	  {
		  printf("Could not malloc (4)\n");

	  }
	  t_noeud	*curmove;
	  dim = getdimensions(gamepos);
  	  nbcas = dim.width * dim.height - nbpions(gamepos);
      while(i<nbcas)
      {
	    move = GenerateMove(gamepos, i, depth - 1);
	    //displaymoves(gamepos->coup);

	    curmove = MinMove(move, depth - 1, !player, alpha, beta, args);
//	    printf("minmove ok\n");
//	    displaymoves(curmove->coup);
	    if(depth==MAXDEPTH && args.debug==FULL_DEBUG)
	      {
	        printf("MAX(%d/%d):%d\n--\n", i, nbcas, Value(curmove));
	    //    displaymoves(curmove->coup);

	      }
	    if(i==0)
	      {
			bcopy(move, bestmove, sizeof(t_noeud));
	        bestmove->value = Value(curmove);
	        gamepos->value = Value(curmove);
	   //     alpha = Value(curmove);
	   //     if(depth==MAXDEPTH)
	   //     beta = Value(curmove);
	      }
	    if(Value(curmove)>Value(bestmove))
	      {
//			bestmove->x=move->x;
//			bestmove->y=move->y;
			bcopy(move, bestmove, sizeof(t_noeud));
	        bestmove->value = Value(curmove);
	        gamepos->value = Value(curmove);
	      //  alpha = Value(curmove);
	      }
//	  if(alpha>beta)
//	    return (bestmove);
	    free(move);

	  i++;
	}
	//free(curmove);
      return (bestmove);
    }
}

t_noeud		*MinMove(t_noeud *gamepos, int depth, char player, int alpha, int beta, t_args args)
{
  t_noeud	*bestmove;
  t_noeud *move;
  t_dimensions dim;
  int		i = 0;
  int nbcas;
  if(/*gameended(gamepos)||*/depth==0)
    {
      evalnode(gamepos, player, args);
      //evalnode(gamepos, PLAYER2, args);
      return(gamepos);
    }
  else
    {
	  if((bestmove = malloc(sizeof(t_noeud)))==NULL)
	  {
	  	  printf("Could not malloc (4)\n");
	  }
t_noeud	*curmove;
	  dim = getdimensions(gamepos);
	  nbcas = dim.width * dim.height - nbpions(gamepos);
      while(i<nbcas)
	{
		move = GenerateMove(gamepos, i, depth - 1);
//		displaymoves(move->coup);

    	curmove = MaxMove(move, depth - 1, !player, alpha, beta, args);
	    if(depth==MAXDEPTH && args.debug==FULL_DEBUG)
	    {
	      printf("min(%d;%d):%d ", i,nbcas,Value(curmove));
	      displaymoves(curmove->coup);
	    }
	    if(i==0)
	      {
   			bcopy(move, bestmove, sizeof(t_noeud));
	        gamepos->value=Value(curmove);
	        bestmove->value = Value(curmove);
	    //  beta=Value(curmove);
	    }
	  if((30-Value(curmove))<(30-Value(bestmove)))
	    {
			bcopy(move, bestmove, sizeof(t_noeud));
	        bestmove->value = Value(curmove);
	        gamepos->value = Value(curmove);
	        //  beta=Value(curmove);
	    }
//	  if(alpha>beta)
//	    return(bestmove);
      free(move);

	  i++;
	}
	//free(curmove);
      return (bestmove);
    }
}
