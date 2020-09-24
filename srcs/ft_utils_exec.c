/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:35:47 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/24 10:35:49 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			ft_errorexec(char *tab)
{
	struct stat		stats;

	if (stat(tab, &stats) == -1)
	{
		ft_printf("minishell: %s: %s\n", tab, strerror(errno));
		g_ret = 127;
		return (g_ret);
	}
	if (S_ISREG(stats.st_mode) == 0)
	{
		ft_printf("minishell: %s: Is a directory\n", tab);
		g_ret = 126;
		return (g_ret);
	}
	else if ((stats.st_mode & S_IXUSR) == 0)
	{
		ft_printf("minishell: %s: Permission denied\n", tab);
		g_ret = 126;
		return (g_ret);
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
				if (!ft_strncmp(&tab[ft_strlen(tmp) + 1], dp->d_name,
				ft_strlen(tab) - ft_strlen(tmp) - 1) && (ft_strlen(tab)
				- ft_strlen(tmp) - 1) == ft_strlen(dp->d_name))
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
			exit(g_ret);
		i = -1;
		while (arg[++i])
			arg[i] = ft_suprguy(arg[i]);
		if ((tab = ft_exist(all, arg[0], -1)) != NULL)
			;
		else if ((tab = ft_haspath(all, arg[0], ft_strlen(arg[0]))) != NULL)
			;
		else if (ft_strchr(arg[0], '/') && (i = ft_errorexec(arg[0])))
			exit(i);
		if (execve(tab, arg, all->env) == -1)
		{
			ft_printf("minishell: %s: command not found\n", arg[0]);
			exit(127);
		}
	}
	wait(&status);
	g_ret = WEXITSTATUS(status);
	return (0);
}
