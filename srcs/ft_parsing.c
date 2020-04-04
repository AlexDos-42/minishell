# include "../include/minishell.h"

int	ft_ptrfct(t_all *all)
{
	int		(*fonc[8])(t_all *);

	int i;

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
//	else
//		execve(tab, *tab, all->env);

	return(i);
}

void	ft_nbfct(t_all *all, char *tab)
{
	int i;

	i = 0;
	while (tab[i] != ' ' && tab[i] != '\n')
		i++;
	if (!ft_strncmp(tab, "echo", 4) && tab[4] == ' ')
		all->fct = 1;
	else if (!ft_strncmp(tab, "pwd", 3))
		all->fct = 2;
	else if (!ft_strncmp(tab, "cd", 2))
		all->fct = 3;
	else if (!ft_strncmp(tab, "exit", 4))
		all->fct = 4;
	else if (!ft_strncmp(tab, "env", 3))
		all->fct = 5;
	else if (!ft_strncmp(tab, "export", 6))
		all->fct = 6;
	else if (!ft_strncmp(tab, "unset", 5))
		all->fct = 7;
	while (tab[i] == ' ')
		i++;
	all->tab = ft_substr(tab, i, ft_strlen(tab) - i);
}

void	ft_minishell(t_all *all, char *str)
{
	int i;
	int k;
	char **tab;
	int stop;
	
	stop = 0;
	tab = ft_split(str, ';');
	k = 0;
	while (tab && tab[k])
	{
		i = 0;
		while (tab[k][i] == ' ')
			i++;
		ft_nbfct(all, &tab[k][i]);
		free(tab[k]);
		if (all->tab[ft_strlen(all->tab) -1] == '\n')
			all->tab[ft_strlen(all->tab) -1] = '\0';
		if ((stop = ft_ptrfct(all)))
			break ;

		k++;
	}
	if(tab)
		free(tab);
	if (stop == 2)
		exit(0);
}
