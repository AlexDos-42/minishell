# include "../include/minishell.h"

int	ft_cd(t_all *all)
{
	char *tmp;

	tmp = ft_strtrim(all->tab, " ");
	free(all->tab);
	all->tab = tmp;
	if (!all->tab[0] || all->tab[0] == '~')
	{
		chdir("/home/alesanto");
		all->pwd = getcwd(all->pwd, 510);
	}
	else if (chdir(all->tab) == 0)
		all->pwd = getcwd(all->pwd, 510);
	else
		ft_printf("cd: aucun fichier ou dossier de ce type: %s\n", all->tab);
	free(all->tab);
	return(0);
}
