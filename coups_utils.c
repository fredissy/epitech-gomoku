#include "game.h"

void	ajoutecoup(t_noeud *parent, t_coord coord, int player)
{
  t_coup	*prev = 0;
  t_coup	*cur;
  t_coup	*newcoup;

  if(parent)
    prev = parent->coup;
  while(prev)
    {
      cur=prev;
      prev=prev->next;
    }
  newcoup = malloc(sizeof(t_coup));
  newcoup->x = coord.x;
  newcoup->y = coord.y;
  newcoup->player = player;
  newcoup->next = 0;
  if(parent->coup)
    cur->next=newcoup;
  else
    parent->coup=newcoup;

}

t_coup *copycoup(t_coup *src)
{
	t_coup *nouv;
	nouv = malloc(sizeof(t_coup));
	nouv->x = src->x;
	nouv->y = src->y;
	nouv->player = src->player;
	return(nouv);
}

void removecoup(t_noeud *parent, t_coord coord)
{
	t_coup *prev;
	t_coup *cur;

	prev=parent->coup;
	cur = prev->next;
	while(cur)
	{
		if(cur->x==coord.x && cur->y==coord.y)
		{
			prev->next = cur->next;
			free(cur);
			cur=prev;
		}
		cur=cur->next;
		prev = prev->next;
	}
	//exit(1);
}



t_coup *duplicate(t_coup *src)
{
	t_coup *first;
	t_coup *cur;

	if(src)
		first = copycoup(src);
	else
		return(0);

	cur = first;
	src = src->next;
	while(src)
	{
		cur->next = copycoup(src);
		cur = cur->next;
		src = src->next;
	}
	return(first);
}
