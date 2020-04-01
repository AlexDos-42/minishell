# include "../include/minishell.h"

void	ft_cd(t_all *all)
{
	int j;
	char *tmp;

	j = ft_strlen(all->tab);
	if (all->tab[j - 1] == '\n')
		all->tab[j - 1] = '\0';
	
	tmp = ft_strtrim(all->tab, " ");
	free(all->tab);
	all->tab = tmp;
	if (all->tab[0] == '~')
	{
		chdir("/home");
		all->pwd = getcwd(all->pwd, 510);
	}
	else if (chdir(all->tab) == 0)
		all->pwd = getcwd(all->pwd, 510);
	else
		ft_printf("nope\n");
}
