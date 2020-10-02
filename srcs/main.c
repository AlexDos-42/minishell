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

void	ft_prompt(t_all *all, char *tmp, char *str)
{
	int			i;

	while (1)
	{
		if ((i = read(0, tmp, 10)) == 0)
			exit(0);
		tmp[i] = '\0';
		str = ft_strjoin(str, tmp, 1);
		if (ft_strnstr(str, "\n", ft_strlen(str)))
		{
			if (str[0] != '\n')
				if (ft_minishell(all, str) == 2)
				{
					i = -1;
					while (all->env[++i])
						free(all->env[i]);
					free(all->env);
					free(str);
					exit(g_ret);
				}
			free(str);
			str = malloc(sizeof(char) * 1);
			str[0] = '\0';
			write(1, "minishell $>", 12);
		}
	}
}

void	ctrl(int signal)
{
	int status;

	status = 0;
	while (wait(&status) > 0)
		;
	if (signal == SIGINT)
	{
		g_ret = 130;
		write(1, "\n", 1);
		if (status == 0)
			write(1, "minishell $>", 12);
	}
	else if (status == 131)
	{
		g_inter = 1;
		g_ret = 131;
		wait(&status);
		write(1, "Quit (core dumped)\n", 19);
	}
}

void	ft_zero(t_all *all)
{
	ft_memset(all, 0, sizeof(t_all));
	g_ret = 0;
	g_inter = 0;
	g_quit = 0;
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
		write(1, "minishell $>", 12);
		ft_prompt(&all, tmp, str);
	}
	return (0);
}
