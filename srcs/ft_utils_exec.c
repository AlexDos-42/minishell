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

char		*ft_ret(char *tab, int p)
{
	char	*new;
	int		i;
	char	*c_ret;

	(void)p;
	i = 0;
	while (tab[i] != '$')
		i++;
	new = ft_substr(tab, 0, i);
	c_ret = ft_itoa(g_ret);
	new = ft_strjoin(new, c_ret, 1);
	free(c_ret);
	if (tab[i + 2])
		new = ft_strjoin(new, &tab[i + 2], 1);
	free(tab);
	return (new);
}

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

char		*ft_haspath(char *tab, int i, char *tmp)
{
	DIR				*dir;
	struct dirent	*dp;

	if (tab[0] == '/' || tab[0] == '.')
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
					free(tmp);
					closedir(dir);
					return (tab);
				}
			closedir(dir);
		}
		free(tmp);
	}
	return (NULL);
}

void		ft_exec_bis(t_all *all, char *tab, int i, char **arg)
{
	i = -1;
	while (arg[++i])
		arg[i] = ft_suprguy(arg[i]);
	if ((tab = ft_exist(all, arg[0], -1)) != NULL)
		;
	else if ((tab = ft_haspath(arg[0], ft_strlen(arg[0]), NULL)) != NULL)
		i = i;
	if (ft_strchr(arg[0], '/') && (i = ft_errorexec(arg[0])))
		exit(i);
	if (execve(tab, arg, all->env) == -1)
	{
		ft_printf("minishell: %s: command not found\n", arg[0]);
		ft_freexec(arg);
		exit(127);
	}
	ft_freexec(arg);
}

int			ft_exec(t_all *all, char *tab)
{
	pid_t			pid;
	int				status;
	char			**arg;
	int				i;

	i = 0;
	status = 0;
	if ((pid = fork()) == 0)
	{
		if (ft_strlen(tab) && tab[ft_strlen(tab) - 1] == '\n')
			tab[ft_strlen(tab) - 1] = '\0';
		if (isexec(tab))
			exit(127);
		arg = ft_splitspace(tab, ' ');
		if (!arg[0])
			exit(g_ret);
		ft_exec_bis(all, tab, i, arg);
	}
	wait(&status);
	g_ret = WEXITSTATUS(status);
	while (wait(NULL) > 0)
		;
	if (g_inter == 2)
		return (-1);
	return (0);
}
