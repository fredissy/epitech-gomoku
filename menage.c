#include "game.h"

/*
** Fonctions d'effacement de l'arbre
** supprime recursivement tout l'arbre
** utiliser removearbre en passant le
** noeud d'origine en parametre..
*/

void removearbre(t_noeud *racine)
{
  //  removearbrecontent(racine);

  //  free(racine);
}

void removearbrecontent(t_noeud *racine)
{
  //  int i=0;
  t_coup *coups;
  t_coup *suivant;
  
  coups = racine->coup;
  suivant = coups->next;
  while(suivant)
    {
      //          printf("r\n");
      free(coups);
      coups = suivant;
      suivant = suivant->next;
    }
  free(coups);
  //  printf("r -> ok\n");
  //  if(racine->fils)
  //    {
  //  printf("enleve les fils\n");
  //  while(racine->fils[i])
  //{
  //  printf("enleve le fils %d\n", i);
  //  removearbre(racine->fils[i]);
  //  i++;
  //}
  //}
  //  free(racine);
}
