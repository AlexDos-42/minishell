/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:58:49 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/08 17:58:51 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <signal.h>

void	ft_clean(t_all *all, char *tmp, char *str)
{
	int i;

	i = -1;
	while (all->env[++i])
		free(all->env[i]);
	free(tmp);
	free(all->env);
	free(str);
	free(all->pwd);
	if (all->nb_ext)
		ft_freexec(all->ext);
	else
		free(all->ext);
	exit(g_ret);
}

char	*remalloc_str(char *str)
{
	free(str);
	str = malloc(sizeof(char) * 1);
	str[0] = '\0';
	g_ret = 130;
	g_inter = 0;
	return (str);
}

void	ft_prompt(t_all *all, char *tmp, char *str, int i)
{
	while (1)
	{
		if ((i = read(0, tmp, 10)) == 0 && !tmp[0] && !str[0])
			ft_clean(all, tmp, str);
		tmp[i] = '\0';
		if (g_inter == 2)
			str = remalloc_str(str);
		str = ft_strjoin(str, tmp, 1);
		if (ft_strnstr(str, "\n", ft_strlen(str)))
		{
			if (str[0] != '\n')
				if (ft_minishell(all, str, 0, -1) == -1)
					ft_clean(all, tmp, str);
			free(str);
			str = malloc(sizeof(char) * 1);
			str[0] = '\0';
			write(2, "\e[93mminishell \e[92m$>\e[0m\e[97m", 31);
		}
		free(tmp);
		tmp = ft_calloc(sizeof(char), 11);
	}
}

void	ctrl(int signal)
{
	int status;

	status = 0;
	if (status == 0 && signal == 3)
		write(0, "\b\b  \b\b", 6);
	while (wait(&status) > 0)
		;
	if (signal == SIGINT)
	{
		g_inter = 2;
		g_ret = 130;
		wait(&status);
		write(1, "\n", 1);
		if (status == 0)
			write(2, "\e[93mminishell \e[92m$>\e[0m\e[97m", 31);
	}
	else if (status == 131)
	{
		g_inter = 1;
		g_ret = 131;
		wait(&status);
		write(1, "^\\Quit (core dumped)\n", 21);
	}
}

int		main(int argc, char **argv, char **env)
{
	t_all		all;
	char		*tmp;
	char		*str;

	all.argv = argv;
	ft_zero(&all);
	signal(SIGINT, ctrl);
	signal(SIGQUIT, ctrl);
	if (argc == 1)
	{
		ft_initenv(&all, env);
		tmp = ft_calloc(sizeof(char), 11);
		str = ft_calloc(sizeof(char), 1);
		write(2, "\e[93mminishell \e[92m$>\e[0m\e[97m", 31);
		ft_prompt(&all, tmp, str, 0);
	}
	else
		write(2, "Minishell: error: too many arguments\n", 37);
	return (0);
}
