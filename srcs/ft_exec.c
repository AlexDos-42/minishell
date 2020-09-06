#include "../include/minishell.h"

char		*isexec(char *tab)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(tab);
	if (!ft_strncmp(tab, "sh", 2) ||
		(!ft_strncmp(tab, "./", 2) && tab[i + 2] != ' '))
	{
		i += 2;
		while (tab[i] == ' ' && tab[i] != '\0')
			i++;
	}
	while (tab[j - 1] == ' ')
		j--;
	tab = ft_substr(tab, i, j - i);
	return (tab);
}

int			ft_exec(t_all *all, char *tab)
{
	pid_t	pid;
	int		status;
	pid_t	wpid;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (ft_strlen(tab) && tab[ft_strlen(tab) - 1] == '\n')
			tab[ft_strlen(tab) - 1] = '\0';
		tab = isexec(tab);
		if (execve(tab, all->argv, all->env) == -1)
		{
			ft_printf("error %s\n", strerror(errno));
			exit(0);
		}
	}
	else
	{
		wpid = wait(&status);
		while (wpid != pid)
			wpid = wait(&status);
	}
	return (0);
}
