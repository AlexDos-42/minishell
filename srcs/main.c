# include "../include/minishell.h"
# include <stdio.h>

void	ft_echo(t_all *all)
{
	int j;
	char *tmp;

	j = ft_strlen(all->tab);
	if (!ft_strncmp(all->tab, "-n", 2) && all->tab[2] == ' ')
	{
		if (all->tab[j - 1] == '\n')
			all->tab[j - 1] = '\0';
		tmp = ft_strtrim(all->tab + 2, " ");
		ft_putstr_fd(tmp, 1);
		free(tmp);
	}
	else
	{
		ft_putstr_fd(all->tab, 1);
		if (all->tab[j - 1] != '\n')
			write(1, "\n", 1);
	}
	free(all->tab);
}

void	ft_ptrfct(t_all *all)
{
	void		(*fonc[7])(t_all *);

	if (all->fct != 0)
	{
		fonc[1] = ft_echo;
		fonc[all->fct](all);
		all->fct = 0;
	}
}

void	ft_nbfct(t_all *all, char *tab)
{
	int i;

	i = 0;
	while (tab[i] != ' ' && tab[i] != '\n')
		i++;
	if (!ft_strncmp(tab, "echo", 4) && tab[4] == ' ')
		all->fct = 1;
	while (tab[i] == ' ')
		i++;
	all->tab = ft_substr(tab, i, ft_strlen(tab) - i);
}

void	ft_minishell(t_all *all, char *str)
{
	int i;
	int k;
	char **tab;
	
	tab = ft_split(str, ';');
	k = 0;
	while (tab[k])
	{
		i = 0;
		while (tab[k][i] == ' ')
			i++;
		ft_nbfct(all, &tab[k][i]);
		free(tab[k]);
		ft_ptrfct(all);
		k++;
	}
	free(tab);
}

int	main(int argc, char **argv, char **env)
{
	t_all		all;
	int		i;
	char		*tmp;
	char		*str;

	(void)argv;
	(void)env;
	ft_memset(&all, 0, sizeof(t_all));
	if (argc == 1)
	{
		tmp = malloc(sizeof(char) * 11);
		str = malloc(sizeof(char) * 1);
		write(1, "minishell $>", 12);
		while (1)
		{
			i = read(0, tmp, 10);
			tmp[i] = '\0';
			str = ft_strjoin(str, tmp, 1);
			if (ft_strnstr(str, "\n", ft_strlen(str)))
			{
				ft_minishell(&all, str);
				free(str);
				str = NULL;
				str = malloc(sizeof(char) * 1);
				str[0] = '\0';
				write(1, "minishell $>", 12);
			}
		}
	}
	return (0);

}
