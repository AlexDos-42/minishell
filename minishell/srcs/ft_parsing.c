#include "../include/minishell.h"

int		ft_ptrfct(t_all *all)
{
	int		(*fonc[8])(t_all *);
	int		i;

	i = 0;
	if (all->fct != 0)
	{
		fonc[1] = ft_echo;
		fonc[2] = ft_pwd;
		fonc[3] = ft_cd;
		fonc[4] = ft_exit;
		fonc[5] = ft_env;
		fonc[6] = ft_export;
		fonc[7] = ft_unset;
		i = fonc[all->fct](all);
		all->fct = 0;
	}
	else
		free(all->tab);
	if (all->fdin >= 0)
	{
		dup2(all->fdout, 1);
		close(all->fdout);;
	}
	return (i);
}

int ft_realbuiltin(char *tab, char *str, int i)
{
	int j;

	j = 0;
	while(tab[j] && ((tab[j] == '\"' && tab[j + 1] == '\"') || (tab[j] == '\''  && tab[j + 1] == '\'')))
		j += 2;
	if (j % 2 != 0)
		j--;
	if (!ft_strncmp(&tab[j], str, i) && (tab[j + ft_strlen(str)] == ' ' || !ft_strncmp(tab, "exit", i)))
		return (1);
	if (tab[j] == '\"' && (!ft_strncmp(&tab[j + 1], str, i)) && tab[j + ft_strlen(str) + 1] == '\"')
		return (1);
	if (tab[j] == '\'' && (!ft_strncmp(&tab[j + 1], str, i)) && tab[j + ft_strlen(str) + 1] == '\'')
		return (1);
	return (0);
}

void	ft_nbfct(t_all *all, char *tab)
{
	int		i;

	i = 0;
	while (tab[i] && tab[i] != ' ' && tab[i] != '\n')
		i++;
	if (ft_realbuiltin(tab, "echo", 4))
		all->fct = 1;
	else if (ft_realbuiltin(tab, "pwd", 3))
		all->fct = 2;
	else if (ft_realbuiltin(tab, "cd", 2))
		all->fct = 3;
	else if (ft_realbuiltin(tab, "exit", 4))
		all->fct = 4;
	else if (ft_realbuiltin(tab, "env", 3))
		all->fct = 5;
	else if (ft_realbuiltin(tab, "export", 6))
		all->fct = 6;
	else if (ft_realbuiltin(tab, "unset", 5))
		all->fct = 7;
	else
		ft_exec(all, tab);
	while (tab[i] == ' ')
		i++;
	all->tab = ft_substr(tab, i, ft_strlen(&tab[i]));
}


int		ft_loop(char *tab, t_all *all)
{
	int		i;

	i = 0;
	tab = ft_redirection(tab, all);
	while (tab && tab[i] == ' ')
		i++;
	ft_nbfct(all, &tab[i]);
	if (ft_strlen(all->tab) && all->tab[ft_strlen(all->tab) - 1] == '\n')
		all->tab[ft_strlen(all->tab) - 1] = '\0';
	return(ft_ptrfct(all));
}

int		ft_minishell(t_all *all, char *str)
{
	int		k;
	char	**tab;
	int		stop;

	stop = 0;
	tab = ft_splitslash(str, ';');
	k = -1;
	while (tab && tab[++k])
	{
		if ((tab[k] = ft_replace(tab[k], all)))
		{
			if (ft_ispipe(tab[k]))
				ft_pipe(tab[k], all);
			else if ((stop = ft_loop(tab[k], all)))
			{
				while (tab && tab[k])
					free(tab[k++]);
				break ;
			}
		}
		free(tab[k]);
	}
	if (tab)
		free(tab);
	return (stop);
}
