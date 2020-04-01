# include "../include/minishell.h"

void	ft_env(t_all *all)
{
	int i;

	i = -1;
	while (all->env[++i])
	{
		ft_putstr_fd(all->env[i], 1);
		write(1, "\n", 1);
	}
}
