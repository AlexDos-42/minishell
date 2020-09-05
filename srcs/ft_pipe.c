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
	    ft_loop(tab[k + 1], all);
		exit(0);
    }
	if (p != k + 1)
            ft_pipefork(tab, p, k + 1, all);
	else 
	{
		child_right = fork();
    	if (child_right == 0)
		{
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			close(pipefd[1]);
			ft_loop(tab[k], all);
			exit(0);
		}
	}
    close(pipefd[1]);
    close(pipefd[0]);
	wait(NULL);
    return (0);
}

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
		p = ft_pipefork(tabpipe, p, 0, all);
		i = -1;
		while(tabpipe[++i])
			free(tabpipe[i]);
		free(tabpipe);
	}
	return(p);
}

