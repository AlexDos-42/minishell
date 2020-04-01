# include "../include/minishell.h"

void	ft_pwd(t_all *all)
{
	ft_putstr_fd(all->pwd, 1);
	write(1, "\n", 1);
}
