/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 16:42:31 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/16 16:42:32 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int g_retpipe;

int		ft_ispipe(char *tab)
{
	int		p;
	int		i;

	i = -1;
	p = 0;
	while (tab[++i])
		p += ischarset(tab, i, "|") && !isguillemet(i, tab) ? 1 : 0;
	return (p);
}

void	ft_pipefork_bis(char **tab, int p, t_all *all, int *pipefd)
{
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	ft_loop(tab[p], all);
	exit(g_ret);
}

void	ft_pipefork_bis_first(char **tab, int p, t_all *all, int *pipefd)
{
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	exit(ft_loop(tab[p], all));
}

void	ft_pipefork(char **tab, int p, int k, t_all *all)
{
	int		pipefd[2];
	int		child_right;
	int		child_left;
	int		child_leftfirst;

	child_leftfirst = 0;
	if (pipe(pipefd) == -1)
		exit(0);
	if (p != k && !(child_left = fork()))
		ft_pipefork_bis(tab, p, all, pipefd);
	if (p == k && !(child_leftfirst = fork()))
		ft_pipefork_bis_first(tab, p, all, pipefd);
	if (!(child_right = fork()))
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		if (--p != 0)
			ft_pipefork(tab, p, k, all);
		else
		{
			ft_loop(tab[p], all);
			exit(g_ret);
		}
		exit(g_ret);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	if (wait(&child_leftfirst))
		g_ret = WEXITSTATUS(child_leftfirst);
	while (wait(NULL) > 0)
		;
}

int		ft_pipeinit(char *tab, t_all *all, int i, int p)
{
	char	**tabpipe;
	char	*tmp;

	while (tab[++i])
		p += ischarset(tab, i, "|") && tab[i - 1] != '|' &&
		!isguillemet(i, tab) ? 1 : 0;
	if (p)
	{
		tabpipe = ft_splitslash(tab, "|");
		tmp = ft_strtrimslash(tabpipe[1], " ");
		if (tabpipe[0] && (!tmp[0] || tmp[0] == '\n'))
			g_ret = 1;
		free(tmp);
		ft_pipefork(tabpipe, p, p, all);
		i = -1;
		while (tabpipe[++i])
		{
			g_pipe = 0;
			if (tabpipe[i + 1])
				istabpipe(tabpipe[i], all);
		}
		ft_freexec(tabpipe);
	}
	return (0);
}
