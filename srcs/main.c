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
