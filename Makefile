##
## Makefile for  in
##
## Made by frederic lenois
## Login   <lenois_f@epita.fr>
##
## Started on  Fri Nov  9 15:45:22 2001 frederic lenois
##

SRC 	= game.c eval.c utils.c tree.c menage.c generate.c saisie.c

NAME 	= egomoku
OBJ 	= $(SRC:.c=.o)
CFLAGS	= -Wall
$(NAME) : $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean :
	rm -f $(OBJ) *~ \#*

fclean :
	rm -f $(NAME)