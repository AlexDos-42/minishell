/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 16:59:53 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/16 16:59:55 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <limits.h>

int			g_inter;
int			g_quit;
int			g_ret;

typedef struct		s_all
{
	char			**argv;
	int				fct;
	char			*tab;
	char			*pwd;
	char			**env;
	int				ret;
	size_t			nb_env;
	int				fdin;
	int				fdout;
	int				fdinc;
	int				fdoutc;
}					t_all;

/*
** --MAIN--
*/

int					main(int argc, char **argv, char **env);
void				ft_prompt(t_all *all, char *tmp, char *str);

/*
** --PARSING--
*/

int					ft_minishell(t_all *all, char *str);
void				ft_nbfct(t_all *all, char *tab);
int					ft_ptrfct(t_all *all);
int					ft_loop(char *tab, t_all *all);

/*
** --INIT--
*/

void				ft_initenv(t_all *all, char **env);
char				**tab_env(char **env, size_t *nb_env);

/*
** --FONCTIONS--
*/

int					ft_echo(t_all *all);
int					ft_pwd(t_all *all);
int					ft_cd(t_all *all);
int					ft_exit(t_all *all);
int					ft_env(t_all *all);
int					ft_export(t_all *all);
char				*ft_suprguy(char *tabnewenv);
int					ft_unset(t_all *all);

/*
** --REPLACE--
*/

char				*ft_replace(char *tab, t_all *all, int i, int j);
char				*ft_isinenv(char *tab, t_all *all);
char				*ft_newtab(char *tab, char *env, int i);

/*
** --PIPE--
*/

int					ft_pipe(char *tab, t_all *all);
int					ft_ispipe(char *tab);
void				istabpipe(char *tab, t_all *all);

/*
** --REDIRECTION--
*/

char				*ft_redirection(char *tab, t_all *all);

/*
** --SPLITSLASH--
*/

char				**ft_splitslash(const char *str, char *c);
int					ischarset(const char *str, int is, char *c);
int					isguillemet(int is, const char *str);
char				**ft_splitspace(const char *str, char c);
char				*ft_splitbuiltin(const char *str, char c);
int					isguillemet(int is, const char *str);

/*
** --EXECUTION--
*/

int					ft_exec(t_all *all, char *tab);
int					isexec(char *tab);
char				**ft_allpath(t_all *all);
char				*ft_exist(t_all *all, char *tab, int i);
void				ft_freexec(char **tab);
char				*ft_strtrimslash(char const *str, char const *set);
void				istabpipe_suite3(char *tab, t_all *all, int i);

#endif
