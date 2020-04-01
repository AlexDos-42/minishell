# include "../include/minishell.h"
# include <stdio.h>

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

void	ft_exit(t_all *all)
{
	(void)all;
	exit(0);
}

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
		printf("nope\n");
}

void	ft_pwd(t_all *all)
{
	ft_putstr_fd(all->pwd, 1);
	write(1, "\n", 1);
}

void	ft_echo(t_all *all)
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
}

void	ft_ptrfct(t_all *all)
{
	void		(*fonc[7])(t_all *);

	if (all->fct != 0)
	{
		fonc[1] = ft_echo;
		fonc[2] = ft_pwd;
		fonc[3] = ft_cd;
		fonc[4] = ft_exit;
		fonc[5] = ft_env;
		fonc[all->fct](all);
		all->fct = 0;
	}
}

void	ft_nbfct(t_all *all, char *tab)
{
	int i;

	i = 0;
	while (tab[i] != ' ' && tab[i] != '\n')
		i++;
	if (!ft_strncmp(tab, "echo", 4) && tab[4] == ' ')
		all->fct = 1;
	else if (!ft_strncmp(tab, "pwd", 3))
		all->fct = 2;
	else if (!ft_strncmp(tab, "cd", 2))
		all->fct = 3;
	else if (!ft_strncmp(tab, "exit", 4))
		all->fct = 4;
	else if (!ft_strncmp(tab, "env", 3))
		all->fct = 5;
	while (tab[i] == ' ')
		i++;
	all->tab = ft_substr(tab, i, ft_strlen(tab) - i);
}

void	ft_minishell(t_all *all, char *str)
{
	int i;
	int k;
	char **tab;
	
	tab = ft_split(str, ';');
	k = 0;
	while (tab[k])
	{
		i = 0;
		while (tab[k][i] == ' ')
			i++;
		ft_nbfct(all, &tab[k][i]);
		free(tab[k]);
		ft_ptrfct(all);
		k++;
	}
	free(tab);
}

void	ft_prompt(t_all *all, char *tmp, char *str)
{
	int		i;


	while (1)
	{
		i = read(0, tmp, 10);
		tmp[i] = '\0';
		str = ft_strjoin(str, tmp, 1);
		if (ft_strnstr(str, "\n", ft_strlen(str)))
		{
			ft_minishell(all, str);
			free(str);
			str = NULL;
			str = malloc(sizeof(char) * 1);
			str[0] = '\0';
			write(1, "minishell $>", 12);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_all		all;
	char		*tmp;
	char		*str;

	(void)argv;
	ft_memset(&all, 0, sizeof(t_all));
	if (argc == 1)
	{
		ft_initenv(&all, env);
		tmp = ft_calloc(sizeof(char), 11);
		str = ft_calloc(sizeof(char), 1);
		write(1, "minishell $>", 12);
		ft_prompt(&all, tmp, str);
	}
	return (0);

}
