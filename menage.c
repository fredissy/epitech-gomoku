#include "game.h"

/*
** Fonctions d'effacement de l'arbre
** supprime recursivement tout l'arbre
** utiliser removearbre en passant le
** noeud d'origine en parametre..
*/

void removearbrecontent(t_noeud *racine)
{
  int i=0;
  t_coup *coups;
  t_coup *suivant;
  //   printf("debut D=%d %d\n", racine->deep, racine);

  coups = racine->coup;
   //printf("coups ok...\n");
  if(coups)
    suivant = coups->next;
  else
    suivant = 0;
   //printf("suivant ok...%d\n", suivant); 
  while(suivant)
    {
      //printf("r\n");
      free(coups);
      coups = suivant;
      suivant = suivant->next;
    }
  //printf("boucle finie\n");
  free(coups);
  //printf("free coupok %d\n", racine->fils);

  if(racine->fils)
    {
      //printf("enleve les fils D=%d:\n",racine->deep);
      while(racine->fils[i])
	{
 	  //printf("enleve le fils %d parent D=%d\n", i, racine->deep);
	  removearbrecontent(racine->fils[i]);
	  //printf("free...%d %d %d\n", i, racine->deep, racine->fils);
	  //	  free(racine->fils[i]);
	  //printf("fils %d enleve ok\n", i);
	  i++;
	}
      //printf("free racine->fils\n");
      //      free(racine->fils);
    }
  //  else
    //printf("pas de fils!\n");
  //  free(racine);
  //printf("end removecontent\n");
}
