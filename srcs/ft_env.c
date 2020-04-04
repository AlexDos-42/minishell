# include "../include/minishell.h"

int	ft_env(t_all *all)
{
	unsigned int i;

	i = -1;
	while (++i < all->nb_env)
	{
		ft_putstr_fd(all->env[i], 1);
		write(1, "\n", 1);
	}
	return(0);
}
