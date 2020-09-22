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

int	ft_ispipe(char *tab)
{
	int p;
	int i;

	i = -1;
	p = 0;
	while (tab[++i])
		p += ischarset(tab, i, "|") && !isguillemet(i, tab) ? 1 : 0;
	return (p);
}

void	ft_pipefork(char **tab, int p, int k, t_all *all)
{
	int		pipefd[2];
	int		child_right;
	int		child_left;

	if (pipe(pipefd) == -1)
		exit(0);
	if (!(child_left = fork()))
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		ft_loop(tab[p], all);
		exit(0);
	}
	if (!(child_right = fork()))
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[1]);
		if (--p != 0)
			ft_pipefork(tab, p, k + 1, all);
		else
			ft_loop(tab[p], all);
		exit(0);
	}
	close(pipefd[1]);
	close(pipefd[0]);
	while (wait(NULL) > 0)
		;
}

int		ft_pipe(char *tab, t_all *all)
{
	int		i;
	int		p;
	char	**tabpipe;

	(void)all;
	i = -1;
	p = 0;
	while(tab[++i] && (tab[i] == ' ' || tab[i] == '|'))
		if (tab[i] == '|')
		{
			ret = 1;
			ft_printf("minishell: syntax error near unexpected token `|'\n");
			return(0);
		}
	while (tab[++i])
		p += ischarset(tab, i, "|") && tab[i - 1] != '|' && !isguillemet(i, tab) ? 1 : 0;
	if (p)
	{
		tabpipe = ft_splitslash(tab, "|");
		ft_pipefork(tabpipe, p, 0, all);
		i = -1;
		if (tabpipe[0] && !tabpipe[1])
			ret = 1;
		while (tabpipe[++i])
		{
			if (tabpipe[i + 1])
				istabpipe(tabpipe[i], all);
			free(tabpipe[i]);
		}
		free(tabpipe);
	}
	return (0);
}
