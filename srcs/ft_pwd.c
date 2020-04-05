# include "../include/minishell.h"

int	ft_pwd(t_all *all)
{
	char *tmp;

	tmp = ft_strtrim(all->tab, " ");
	if (tmp[0])
		ft_printf("pwd: too many arguments\n");
	else
	{	
		ft_putstr_fd(all->pwd, 1);
		write(1, "\n", 1);
	}
	free(all->tab);
	free(tmp);
	return(0);
}
