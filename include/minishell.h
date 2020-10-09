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
int			g_pipe;

typedef struct		s_all
{
	char			**argv;
	int				fct;
	char			*tab;
	char			*pwd;
	char			**env;
	char			**ext;
	int				nb_ext;
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
void				ft_prompt(t_all *all, char *tmp, char *str, int i);

/*
** --PARSING--
*/

int					ft_minishell(t_all *all, char *str, int stop, int k);
void				ft_nbfct(t_all *all, char *tab);
int					ft_ptrfct(t_all *all);
int					ft_loop(char *tab, t_all *all);

/*
** --INIT--
*/

void				ft_initenv(t_all *all, char **env);
void				tab_env(char **env, t_all *all);

/*
** --FONCTIONS--
*/

int					ft_echo(t_all *all);
int					ft_pwd(t_all *all);
int					ft_cd(t_all *all);
int					ft_exit(t_all *all);
int					ft_env(t_all *all);
int					ft_export(t_all *all);
char				**ft_freetab(char **tabnewenv, int i);
int					isexporterror(char *tab, int j);
int					ft_isenvexist(t_all *all, char *tab);
int					isenvexist_ext(t_all *all, char *tab);
void				put_export(int eg, t_all *all, int j, char *tab);
int					ft_isenvexist_ext(t_all *all, char *tab);
char				**ft_exporterreur(char **str, int j);
int					ft_unset(t_all *all);
void				export_solo(t_all *all, int i, int eg, char *tmp);
int					dble(char **tab, int i);
int					dble_ext(char **tab, int i);
int					iserrorput(char *tab, int j);

/*
** --REPLACE--
*/

char				*ft_replace(char *tab, t_all *all, int i, int j);
char				*ft_isinenv(char *tab, t_all *all);
char				*ft_newtab(char *tab, char *env, int i);
void				ft_suprext(t_all *all, char *new, int p, int o);
int					combien(char *new, int l, int *k);

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
char				*suprredir(char *tab, int i, int j, char *tmp);
char				*if_or_else(char *new, char *tab, int l, int k);
char				*join_first(char *new, char *tab);
char				*join_tmp(char *new, int l, char *tab);

/*
** --SPLITSLASH--
*/

char				**ft_splitslash(const char *str, char *c);
int					ischarset(const char *str, int is, char *c);
int					isguillemet(int is, const char *str);
char				**ft_splitspace(const char *str, char c);
char				*ft_splitbuiltin(const char *str, char c);
int					isguillemet(int is, const char *str);
char				*ft_suprguy(char *tab);

/*
** --EXECUTION--
*/

int					ft_exec(t_all *all, char *tab);
int					isexec(char *tab);
char				**ft_allpath(t_all *all);
char				*ft_exist(t_all *all, char *tab, int i);
void				ft_freexec(char **tab);
char				*ft_strtrimslash(char const *str, char const *set);
void				istabpipe_suite3(char **new, t_all *all, int i);
void				ft_create_file(t_all *all, char **tab, char **redir, int i);
char				*ft_redirection(char *tab, t_all *all);
int					redirspace(char **redir);
char				*ft_join(char **redir, char **new, t_all *all);
int					redirerror_bis(char **redir);
char				**ft_realsplit(char *tab, char **new, char **redir, int k);
char				**ft_addarg(char **tmp);
char				**ft_allredir(char *tab);
int					redirerror(char **tab, char **redir);
char				**ft_allredir(char *tab);
char				**ft_all_redir_bis(char *tab, char **new, int i, int j);
char				*ft_ret(char *tab, int p);
int					is_two_pipe(char *tab);
int					ft_pipeinit(char *tab, t_all *all, int i, int p);

#endif
