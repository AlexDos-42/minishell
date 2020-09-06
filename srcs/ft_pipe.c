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

int	ft_pipefork(char **tab, int p, int k, t_all *all)
{
    int     pipefd[2];
    int   child_right;
    int   child_left;

    if (pipe(pipefd) == -1)
		exit(0);
	child_left = fork();
    if (child_left == 0)
    {
        dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	    ft_loop(tab[p], all);
		exit(0);
    }
	p--;
	child_right = fork();
    	if (child_right == 0)
		{
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			close(pipefd[1]);
			if (p != 0)
            	ft_pipefork(tab, p, k + 1, all);
			else 
				ft_loop(tab[p], all);
			exit(0);
		}
    close(pipefd[1]);
    close(pipefd[0]);
	while (wait(NULL) > 0);
    return (0);
}

// char	**istabpipe(t_all *all, char **tab)
// {
// 	int		i;

// 	(void)all;
// 	i = 0;
// 	while (tab[i] != ' ' && tab[i] != '\n')
// 		i++;
// 	if (!ft_strncmp(tab, "echo", 4) || (!ft_strncmp(tab, "pwd", 3))
// 		|| (!ft_strncmp(tab, "cd", 2)) || (!ft_strncmp(tab, "exit", 4))
// 		|| (!ft_strncmp(tab, "env", 3)) || (!ft_strncmp(tab, "export", 6))
// 		|| (!ft_strncmp(tab, "unset", 5)) || (!ft_strncmp(tab, "sh", 2) ||
// 		(!ft_strncmp(tab, "./", 2) && tab[i + 2] != ' '))
// 		;
// 	else
// 		;
// 	return (tab);

// }

int	ft_pipe(char *tab, t_all *all)
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
		//tabpipe = istabpipe(all, tabpipe);
		p = ft_pipefork(tabpipe, p, 0, all);
		i = -1;
		while(tabpipe[++i])
			free(tabpipe[i]);
		free(tabpipe);
	}
	return(p);
}

