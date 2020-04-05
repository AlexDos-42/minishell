# include "../include/minishell.h"

int	ft_echo(t_all *all)
{
	char *tmp;

	if (!ft_strncmp(all->tab, "-n", 2))
	{
		tmp = ft_strtrim(all->tab + 2, " ");
		ft_putstr_fd(tmp, 1);
		free(tmp);
	}
	else
	{
		tmp = ft_strtrim(all->tab, " ");
		ft_putstr_fd(tmp, 1);
		write(1, "\n", 1);
		free(tmp);
	}
	free(all->tab);
	return(0);
}
