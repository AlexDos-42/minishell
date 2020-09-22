/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:56:51 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/08 17:56:53 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			isexec(char *tab)
{
	int				j;
	char			*tmp;
	char			*new;

	new = ft_strdup(tab);
	tmp = ft_strtrim(new, " ");
	free(new);
	tmp = ft_suprguy(tmp);
	j = ft_strlen(tmp) - 1;
	if (j > 0)
	{
		if (tmp[j] == 'h' && tmp[j - 1] == 's' && tmp[j - 2] == '.')
		{
			if ((ft_strncmp(tmp, "./", 2) && tmp[2] != ' ')
			&& ft_strncmp(tmp, "sh", 2) && ft_strncmp(tmp, "../", 3)
			&& ft_strncmp(tmp, "/", 1))
			{
				ft_printf("minishell: %s: command not found\n", tab);
				free(tmp);
				ret = 127;
				return (1);
			}
		}
	}
	free(tmp);
	return (0);
}

char		**ft_allpath(t_all *all)
{
	char			*tmp;
	char			**path;
	int				i;

	i = 0;
	path = NULL;
	while (all->env[i])
	{
		if (!ft_strncmp(all->env[i], "PATH", 4))
		{
			tmp = ft_strdup(&all->env[i][5]);
			path = ft_split(tmp, ':');
			free(tmp);
			break ;
		}
		i++;
	}
	return (path);
}

void		ft_freexec(char **tab)
{
	int				i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

char		*ft_exist(t_all *all, char *tab, int i)
{
	DIR				*dir;
	struct dirent	*dp;
	char			**path;
	char			*tmp;

	if ((path = ft_allpath(all)) != NULL)
	{
		while (path[++i])
		{
			if ((dir = opendir(path[i])) != NULL)
			{
				while ((dp = readdir(dir)) != NULL)
					if (!ft_strncmp(tab, dp->d_name, ft_strlen(tab))
					&& ft_strlen(tab) == ft_strlen(dp->d_name))
					{
						tmp = ft_strjoin(path[i], "/", 0);
						tab = ft_strjoin(tmp, tab, 1);
						ft_freexec(path);
						closedir(dir);
						return (tab);
					}
				closedir(dir);
			}
		}
		ft_freexec(path);
	}
	return (NULL);
}

int			ft_errorexec(char *tab)
{
	struct stat		stats;

	if (stat(tab, &stats) == -1)
	{
		ft_printf("minishell: %s: %s\n", tab, strerror(errno));
		ret = 127;
		return (ret);
	}
	if (S_ISREG(stats.st_mode) == 0)
	{
		ft_printf("minishell: %s: Is a directory\n", tab);
		ret = 126;
		return (ret);
	}
	else if ((stats.st_mode & S_IXUSR) == 0)
	{
		ft_printf("minishell: %s: Permission denied\n",tab);
		ret = 126;
		return (ret);
	}
	return (0);
}

char		*ft_haspath(t_all *all, char *tab, int i)
{
	DIR				*dir;
	struct dirent	*dp;
	char			*tmp;

	(void)all;
	if (tab[0] == '/')
	{
		while (tab[i] != '/')
			i--;
		tmp = ft_substr(tab, 0, i);
		i = -1;
		if (tmp && (dir = opendir(tmp)) != NULL)
		{
			while ((dp = readdir(dir)) != NULL)
				if (!ft_strncmp(&tab[ft_strlen(tmp) + 1], dp->d_name, ft_strlen(tab) - ft_strlen(tmp) - 1)
					&& (ft_strlen(tab) - ft_strlen(tmp) - 1) == ft_strlen(dp->d_name))
				{
					closedir(dir);
					return (tab);
				}
			closedir(dir);
		}
		free(tmp);
	}
	return (NULL);
}

int			ft_exec(t_all *all, char *tab)
{
	pid_t			pid;
	int				status;
	char			**arg;
	int				i;

	i = 0;
	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (ft_strlen(tab) && tab[ft_strlen(tab) - 1] == '\n')
			tab[ft_strlen(tab) - 1] = '\0';
		if (isexec(tab))
			exit(127);
		arg = ft_splitspace(tab, ' ');
		if (!arg[0])
			exit(0);
		i = -1;
		while(arg[++i])
			arg[i] = ft_suprguy(arg[i]);
		if ((tab = ft_exist(all, arg[0], -1)) != NULL)
			;
		else if ((tab = ft_haspath(all, arg[0], ft_strlen(arg[0]))) != NULL)
			;
		else if ((i = ft_errorexec(arg[0])))
			exit(i);
		i = execve(tab, arg, all->env);
		if (i == -1)
		{
			ft_printf("minishell: %s: command not found\n", arg[0]);
			exit(127);
		}
	}
	wait(&status);
	ret = WEXITSTATUS(status);
	return (0);
}
