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
	while (j != 0 && tab[j - 1] == ' ')
		j--;
    tab = ft_substr(tab, i, j - i);
    return (tab);
}

char **ft_allpath(t_all *all)
{
    char *tmp;
    char **path;
    int     i;

    i = 0;
    path = NULL;
    while (all->env[i])
    {
        if (!ft_strncmp(all->env[i], "PATH", 4))
        {
            tmp = ft_strdup(&all->env[i][5]);
            path = ft_split(tmp, ':');
            free(tmp);
            break;
        }
        i++;
    }
    return (path);
}

void ft_free(char **tab)
{
    int i;

    i = -1;
    while(tab[++i])
        free(tab[i]);
    free(tab);
}

char *ft_exist(t_all *all, char *tab)
{
    DIR             *dir;
    struct dirent    *dp;
    char **path;
    int i;

    i = 0;
    if ((path = ft_allpath(all)) != NULL)
    {
        while(path[i])
        {
            dir = opendir(path[i]);
            while ((dp = readdir(dir)) != NULL)
            {
                if (!ft_strncmp(tab, dp->d_name, ft_strlen(tab))
                && ft_strlen(tab) == ft_strlen(dp->d_name))
                {
                    char *tmp = ft_strjoin(path[i], "/", 0);
                    tab = ft_strjoin(tmp, tab, 3);
                    ft_free(path);
                    closedir(dir);
                    return(tab);
                }
            }
            closedir(dir);
            i++;
        }
        ft_free(path);
    }
    return(tab);
}

int			ft_exec(t_all *all, char *tab)
{
	pid_t	pid;
	int		status;
    char    **arg;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (ft_strlen(tab) && tab[ft_strlen(tab) - 1] == '\n')
			tab[ft_strlen(tab) - 1] = '\0';
		tab = isexec(tab);
        arg = ft_split(tab, ' ');
        if (!arg[0])
            exit(0);
        arg[0] = ft_exist(all, arg[0]);
        if (execve(arg[0], arg, all->env) == -1)
		{
			ft_printf("error %s\n", strerror(errno));
			exit(127);
		}
    }
    wait(&status);
    ret = WEXITSTATUS(status);    
	return (0);
}
