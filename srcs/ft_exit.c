# include "../include/minishell.h"

int	ft_exit(t_all *all)
{
	free(all->tab);
	return(2);
}
