/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_next.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 19:41:08 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/24 19:41:10 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char		*ft_join(char **redir, char *tmp, char **new, t_all *all)
{
	int				i;
	struct stat		stats;

	i = 0;
	while (redir[i])
		i++;
	while (redir[i] && redir[i][0] != '<')
		i--;
	if (new[i] && stat(new[i], &stats) == -1)
	{
		ft_printf("minishell: %s: %s\n", new[i], strerror(errno));
		if (all->fdout >= 0)
		{
			dup2(all->fdinc, 0);
			close(all->fdinc);
		}
		free(tmp);
		g_ret = 1;
		tmp = ft_calloc(1, 1);
	}
	return (tmp);
}

int			redirspace(char **redir)
{
	int		i;
	int		j;

	i = -1;
	while (redir[++i])
	{
		j = -1;
		while (redir[i][++j])
			if (redir[i][j] == ' ')
			{
				if (redir[i][0] && redir[i][1] && redir[i][2] && redir[i][3])
				{
					ft_printf("minishell: syntax error near unexpected token");
					ft_printf("`%c%c'\n", redir[i][0], redir[i][0]);
				}
				else
				{
					ft_printf("minishell: syntax error near unexpected token");
					ft_printf("`%c'\n", redir[i][0]);
				}
				g_ret = 2;
				return (0);
			}
	}
	return (1);
}

char		*ft_redirection(char *tab, t_all *all)
{
	int		i;
	char	**redir;
	char	**new;
	char	*tmp;

	i = 0;
	redir = ft_allredir(tab);
	all->fdin = -5;
	all->fdout = -5;
	if (redir != NULL && !redirspace(redir))
	{
		ft_freexec(redir);
		redir = NULL;
		tab = ft_strdup("");
	}
	else if (redir != NULL)
	{
		new = ft_splitslash(tab, "><");
		new = ft_realsplit(tab, new, redir);
		if (redirerror(new, redir))
		{
			ft_addarg(new);
			while (new[++i])
			{
				tmp = ft_strtrimslash(new[i], " ");
				free(new[i]);
				tmp = ft_suprguy(tmp);
				if (tmp[0] && tmp[ft_strlen(tmp) - 1] == '\n')
					new[i] = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
				else
					new[i] = ft_strdup(tmp);
				free(tmp);
			}
			i = 0;
			tmp = new[0] ? ft_strdup(new[0]) : ft_calloc(1, 1);
			i = 0;
			while (redir[i] && redir[i][0] != '>')
				i++;
			if (redir[i] && redir[i][0] == '>')
				ft_create_file(all, new, redir, i);
			i = 0;
			while (redir[i] && redir[i][0] != '<')
				i++;
			if (redir[i] && redir[i][0] == '<')
				ft_create_file(all, new, redir, i);
			tmp = ft_join(redir, tmp, new, all);
		}
		else
			tmp = ft_calloc(1, 1);
		ft_freexec(redir);
		ft_freexec(new);
		return (tmp);
	}
	else
		tab = ft_strdup(tab);
	return (tab);
}
