#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//dans la liste chainée des positions
#define NOPLAYER -1
#define PLAYER1 0
#define PLAYER2 1
#define DEHORS -2

//pour les arguments
#define UNJOUEUR 0
#define DEUXJOUEURS 1
#define RUN_DEBUG 1
#define FULL_DEBUG 2

//params generaux du jeux
#define FREE 0
#define DIM 19
#define MAXDEPTH 1
#define EXTRA 2

//max ou min de deux valeurs
#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))

//pour les comparaisons
#define MOI '1'
#define ADVERSAIRE '2'
#define PERSONNE '0'

typedef struct s_coup
{
  signed char	player;		        //joueur present
  int		x;
  int		y;
  struct s_coup	*next;
} t_coup;

//typedef struct s_tab
//{
//  t_coup	t[DIM][DIM];
//} t_tab;

typedef struct s_noeud
{
  signed char	 player; // joueur jouant a ce tour la
  int			 value;	//valeur de l'evaluation
  t_coup		 *coup;	//etat du jeu a ce noeud
  struct s_noeud **fils; //liens vers tous les noeuds en dessous
  int			 x;		//coordonee x coup joue
  int			 y;		//coordonee x coup joue
  int			 deep;	//profondeur du noeud, 0=> tout en bas
} t_noeud;

typedef struct s_dimensions	//structure pour enregistrer
{				//la dimension de la fenetre
  int	maxleft;		//de jeu, ainsi que sa
  int	width;			//position
  int	maxtop;
  int	height;
} t_dimensions;

typedef struct s_coord		//systeme de coordonnees
{
  int	x;			//coordonnee x
  int	y;			//coordonnee y
} t_coord;

typedef struct s_args		//contient l'analyse des args
{
  int	players;		// 1 ou 2 joueurs
  int	debug;			//lancement en mode debug
} t_args;

typedef struct s_score
{
	int ownalign;
	int advalign;
} t_score;

int	gameended(t_noeud *gamestate);
int	evalnode(t_noeud *gamestate, char player, t_args args);
char	occupant(t_coup *cellule);
int	nbpions(t_noeud *gamepos);
t_coord	MinMax(t_noeud *gamepos, int depth, char player, t_args args);
t_noeud *MaxMove(t_noeud *gamepos, int depth, char player, int alpha, int beta, t_args args);
t_noeud *MinMove(t_noeud *gamepos, int depth, char player, int alpha, int beta, t_args args);

t_noeud	*GenerateMove(t_noeud *parent, int numerocas, int depth);
t_noeud	**GenerateMoves(t_noeud *gamepos, int depth);
t_dimensions	getdimensions(t_noeud *gamestate);
int		Value(t_noeud *noeud);
//t_tab	*generatetable(t_coup *first);
int		evalcase_align(t_coup *coups, t_coord, char player);
int	eval_line(t_coup *coups, t_coord coord, signed int xm, signed int ym, char player);
void	displaymoves(t_coup *coup);
int		x(t_noeud *noeud);
int		y(t_noeud *noeud);
void	removearbre(t_noeud *racine);
void	removearbrecontent(t_noeud *racine);
void	ajoutecoup(t_noeud *parent, t_coord, int player);
void	gameloop_1p();
void	gameloop_2p();
void	avance(t_dimensions *dim, t_coord *initial, int rang);
int		avant(t_coord *nouv, t_coup *orig);
int		occupee(t_coup *orig, t_coord coord);
t_args	arguments(int ac, char **av);
t_coord	saisie(signed char player, t_coup *coups);
int		saisie_ok(t_coup *coups, t_coord saisie, signed char player);
char	*buildchaine(t_coup *coups, int dx, int dy, t_coord coord, signed char player, int size, int decalage);
//char	*buildchaine2(t_coup *coups, int dx, int dy, t_coord coord, signed char player, int size);
int		dans(t_coup *orig, t_coord coord, signed char player);
int		checkdoubletrois(t_coup *coups, t_coord saisie, signed char player);
int		is_doubletrois(char *chaine, signed char player);
t_coord	generatecoord(int x, int y);
int	occupee2(t_coup *orig, t_coord coord);
int blocks_ennemy(t_coup *coups, t_coord coord, char player);
int does_block_ennemy(char *chaine, signed char player);
int get_maxalign_coup(t_coup *tocheck, t_noeud *gamestate);
int get_maxalign_coord(t_coord coord, t_noeud *gamestate);
int checkstring_for_victory(char *chaine);
