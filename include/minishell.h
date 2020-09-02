#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "error.h"

int		inter;
int		quit;
int		ret;

typedef struct		s_all
{
	char	**argv;
	int	fct;
	char	*tab;
	char	*pwd;
	char	**env;
	char	ret;
	size_t	nb_env;
}			t_all;

/*
** --MAIN--
*/

int			main(int argc, char **argv, char** env);
void			ft_prompt(t_all *all, char *tmp, char *str);

/*
** --PARSING--
*/

int			ft_minishell(t_all *all, char *str);
void			ft_nbfct(t_all *all, char *tab);
int			ft_ptrfct(t_all *all);
int			ft_loop(char *tab, t_all *all);

/*
** --INIT--
*/

void			ft_initenv(t_all *all, char **env);
char			**tab_env(char **env, size_t *nb_env);

/*
** --FONCTIONS--
*/

int			ft_echo(t_all *all);
int			ft_pwd(t_all *all);
int			ft_cd(t_all *all);
int			ft_exit(t_all *all);
int			ft_env(t_all *all);
int			ft_export(t_all *all);
int			ft_unset(t_all *all);

/*
** --REPLACE--
*/

char			*ft_replace(char *tab, t_all *all);
char			*ft_isinenv(char *tab, t_all *all);
char		 	*ft_newtab(char *tab, char *env);


/*
** --PIPE--
*/

int			ft_pipe(char *tab, t_all *all);


/*
** --REDIRECTION--
*/

int 		ft_redirection(char *tab, t_all *all);
int			ft_create_file(char *tab);


/*
** --SPLITSLASH
*/

char		**ft_splitslash(const char *str, char c);

#endif
