##
## Makefile for  in
##
## Made by frederic lenois
## Login   <lenois_f@epita.fr>
##
## Started on  Fri Nov  9 15:45:22 2001 frederic lenois
##

SRC 	= disp.c \
	  tree.c \
	  game.c \
	  eval.c \
	  eval_tests.c \
	  utils.c \
	  menage.c \
	  generate.c \
	  saisie.c \
	  hint.c \
	  prises.c \
	  coups_utils.c \

NAME 	= egomoku
OBJ 	= $(SRC:.c=.o)
CFLAGS	= -Wall
$(NAME) : $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean :
	rm -f $(OBJ) *~ \#*

fclean :
	rm -f $(NAME)
	
save :
	tar -cvzf ../gomoku-`date +%d%m-%Hh%M`.tgz Makefile *.c *.h
