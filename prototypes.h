//eval-verifs
int gameended(t_noeud *gamestate, char player);
int	evalnode(t_noeud *gamestate, char player, t_args args);
int	evalcase_align(t_coup *coups, t_coord, char player);
int	eval_line(t_coup *coups, t_coord coord, signed int xm, signed int ym, char player);
int	saisie_ok(t_coup *coups, t_coord saisie, signed char player, int flag);
int	checkdoubletrois(t_coup *coups, t_coord saisie, signed char player);
int	is_doubletrois(char *chaine, signed char player);
int blocks_ennemy(t_coup *coups, t_coord coord, char player);
int does_block_ennemy(char *chaine);
int get_maxalign_coup(t_coup *tocheck, t_noeud *gamestate, char player);
int get_maxalign_coord(t_coord coord, t_noeud *gamestate, char player);
int checkstring_for_victory(char *chaine);
int does_fill_hole(char *chaine);
int	fills_hole(t_coup *coups, t_coord coord, char player);
int	prise_paire_adversaire(t_coup *coups, t_coord coord, char player);
int do_prend_paire(char *chaine);


//infos
int			occupee2(t_coup *orig, t_coord coord);
int			x(t_noeud *noeud);
int			y(t_noeud *noeud);
int			occupee(t_coup *orig, t_coord coord);
void		displaymoves(t_coup *coup);
char		occupant(t_coup *cellule);
int			nbpions(t_noeud *gamepos);
t_dimensions	getdimensions(t_noeud *gamestate);
int			Value(t_noeud *noeud);
char		*buildchaine(t_coup *coups, int dx, int dy, t_coord coord, signed char player, int size, int decalage);
int			dans(t_coup *orig, t_coord coord, signed char player);
t_coord		generatecoord(int x, int y);


//minmax
t_coord	MinMax(t_noeud *gamepos, int depth, char player, t_args args);
t_noeud *MaxMove(t_noeud *gamepos, int depth, char player, int alpha, int beta, t_args args);
t_noeud *MinMove(t_noeud *gamepos, int depth, char player, int alpha, int beta, t_args args);
t_noeud	*GenerateMove(t_noeud *parent, int numerocas, int depth);
//t_noeud	**GenerateMoves(t_noeud *gamepos, int depth);

//nettoyage memoire
void	removearbre(t_noeud *racine);
void	removearbrecontent(t_noeud *racine);


//gestion des coups
void	ajoutecoup(t_noeud *parent, t_coord, int player);
void	removecoup(t_noeud *parent, t_coord coord);
t_coup *duplicate(t_coup *src);
t_coup *copycoup(t_coup *src);
void	delcoups(t_coup *todelete);

//jeu en lui meme
void	gameloop_1p();
void	gameloop_2p();
void	avance(t_dimensions *dim, t_coord *initial, int rang);
t_args	arguments(int ac, char **av);
t_coord	saisie(signed char player, t_coup *coups);
int		deal_keywords(t_coup *coups, char player, char *buffer);
void	dealprises(t_noeud *jeu, t_coord coord, char player);
void	enlevepaire(t_noeud *jeu, t_coord coord, int sens, char player);

//affichages
void showgrid(t_noeud *gamestate);
void printchaine(char *chaine, int len);
void showhint(t_coup *coups, signed char player);
void infoprises(t_noeud *jeu);

