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
