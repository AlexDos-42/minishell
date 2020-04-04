# include "../include/minishell.h"

int	ft_exit(t_all *all)
{
	(void)all;
	free(all->tab);
	exit(0);
	return(2);
}
