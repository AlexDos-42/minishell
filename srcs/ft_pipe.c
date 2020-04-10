# include "../include/minishell.h"

char *ft_child(char **tab, int p, int i, int *pfd)
{
	int pid;
	char *tmp;

	if (i < p)
	{
		if ((pid = fork()) < 0)
		{
			ft_printf("fork failed\n");
			exit(0);
		}
		if (pid == 0)
		{
			close(pfd[1]);
			dup2(pfd[0], 0);
			close(pfd[0]);
			ft_printf("testchild\n");
			return(tab[i]);
		}
		else
		{
			close(pfd[0]);
			dup2(pfd[1], 1);
			close(pfd[1]);
			ft_printf("testdad\n");
			ft_child(tab, p, ++i, pfd);
		}
	}
	tmp = tab[i];
	free(tab);
	return (tmp);
}

void	ft_pipefork(char **tab, int p, int k, t_all *all)
{
    int     pdes[2];
    int     status;
    pid_t   child_right;
    pid_t   child_left;

    pipe(pdes);
    if (!(child_left = fork()))
    {
        close(pdes[READ_END]);
        dup2(pdes[WRITE_END], STDOUT_FILENO);
	ft_loop(tab[k], all);
        exit(0);
    }
    if (!(child_right = fork()))
    {
        close(pdes[WRITE_END]);
        dup2(pdes[READ_END], STDIN_FILENO);
        if (p != k)
            ft_pipefork(tab, p, k + 1, all);
        else
	{
		ft_loop(tab[k], all);
        	exit(0);
	}
    }
    close(pdes[WRITE_END]);
    close(pdes[READ_END]);
    wait(NULL);
    waitpid(child_right, &status, 0);
    return ;
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
		p += tab[i] == '|' ? 1 : 0;
	if (p)
	{
		tabpipe = ft_split(tab, '|');
		ft_pipefork(tabpipe, p, 0, all);
	}
	return(p);
}

