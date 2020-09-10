# include "../include/minishell.h"

int	ft_ispipe(char *tab)
{
	int p;
	int i;

	i = -1;
	p = 0;
	while(tab[++i])
		p += ischarset(tab, i, '|')? 1 : 0;
	return (p);
}

void	ft_pipefork(char **tab, int p, int k, t_all *all)
{
    int     pipefd[2];
    int   child_right;
    int   child_left;

    if (pipe(pipefd) == -1)
		exit(0);
	if (!(child_left = fork()))
    {
        dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	    ft_loop(tab[p], all);
		exit(0);
    }
	if (!(child_right = fork()))
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[1]);
		if (--p != 0)
           	ft_pipefork(tab, p, k + 1, all);
		else 
			ft_loop(tab[p], all);
		exit(0);
	}
    close(pipefd[1]);
    close(pipefd[0]);
	while (wait(NULL) > 0);
}

void	istabpipe(char *tab)
{
	int i;
	

	i = 0;
	while (tab[i] == ' ')
		i++;
	if (!ft_strncmp(&tab[i], "echo ", 5) || (!ft_strncmp(&tab[i], "exit", 4)))
		;
	else if (!ft_strncmp(&tab[i], "pwd ", 4))
	{
		while(tab[i + 4] == ' ')
			i++;
		if (tab[i + 4])
			ft_printf("pwd: too many arguments\n");
	}
	else if (!ft_strncmp(&tab[i], "env ", 4))
	{
		while(tab[i + 4] == ' ')
			i++;
		if (tab[i + 4])
			ft_printf("env: %s:\n", tab);
	}
	else if (!ft_strncmp(&tab[i], "cd ", 3))
	{
		int j;
		char *tmp;
		int k;

		j = 0;
		k = 0;
		while (tab[i + 3] == ' ')
			i++;
		while (tab[i + 3 + j + k])
		{
			j += k;
			k = 0;
			j++;
			while (tab[i + 3 + j + k] == ' ')
				k++;
		}
		if (j)
		{
			tmp = ft_substr(tab, i + 3, j);
			if ((ft_strlen(tmp) == 1 && (tmp[0] != '.' || tmp[0] != '~')) ||
				(ft_strlen(tmp) == 2 && tmp[0] != '.' && tmp[1] != '.')
				|| chdir(tmp) != 0)
				ft_printf("cd: %s: %s\n", strerror(errno), tmp);
			free(tmp);
		}
	} 
	else if (!ft_strncmp(&tab[i], "export ", 7))
	{
		int j;
		int k;
		char *tmp;

		while (tab[i + 7])
		{
			k = 0;
			j = 0;
			while(tab[i + 7] == ' ')
				i++;
			if (tab[i + 7] == '=')
				k = 1;
			while(tab[i + 7 + j] && tab[i + 7 + j] != ' ')	
				j++;
			if (k == 1)
			{
				tmp = ft_substr(tab, i + 7, j);
				ft_printf("minishell: export: « %s » : identifiant non valable\n", tmp);
				free(tmp);
			}
			i += j;
		}
	}
	else if (!ft_strncmp(&tab[i], "unset ", 6))
	{
		int j;
		int k;
		char *tmp;

		while(tab[i + 6])
		{
			k = 0;
			j = 0;
			while(tab[i + 6] == ' ')
				i++;
			while(tab[i + 6 + j] && tab[i + 6 + j] != ' ')
			{
				if (tab[i + 6 + j] == '=')
					k = 1;	
				j++;
			}
			if (k == 1)
			{
				tmp = ft_substr(tab, i + 6, j);
				ft_printf("minishell: unset: « %s » : identifiant non valable\n", tmp);
				free(tmp);
			}
			i += j;
		}		
	}
	// else
	// 	ft_exec(all, tab);
}

int		ft_pipe(char *tab, t_all *all)
{
	int i;
	int p;
	char **tabpipe;

	(void)all;
	i = -1;
	p = 0;
	while(tab[++i])
		p += ischarset(tab, i, '|') ? 1 : 0;
	if (p)
	{
		tabpipe = ft_splitslash(tab, '|');
		ft_pipefork(tabpipe, p, 0, all);
		i = -1;
		while(tabpipe[++i])
		{
			istabpipe(tabpipe[i]);
			free(tabpipe[i]);
		}
		free(tabpipe);
	}
	return(0);
}
