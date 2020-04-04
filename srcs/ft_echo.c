# include "../include/minishell.h"

int	ft_echo(t_all *all)
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
		tmp = ft_strtrim(all->tab, " ");
		ft_putstr_fd(tmp, 1);
		if (all->tab[j - 1] != '\n')
			write(1, "\n", 1);
		free(tmp);
	}
	free(all->tab);
	return(0);
}
