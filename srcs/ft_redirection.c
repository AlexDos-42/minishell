/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:59:03 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/08 17:59:04 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_open(t_all *all, int j)
{
	if (all->fdin >= 0 && j == 1)
	{
		all->fdoutc = dup(1);
		close(1);
		dup2(all->fdin, 1);
	}
	if (all->fdout >= 0 && j == 2)
	{
		all->fdinc = dup(0);
		close(0);
		dup2(all->fdout, 0);
	}
}

void	ft_close(t_all *all, int i)
{
	if (all->fdin >= 0 && i == 1)
	{
		dup2(all->fdoutc, 1);
		close(all->fdoutc);
		all->fdin = -5;
	}
	if (all->fdout >= 0 && i == 2)
	{
		dup2(all->fdinc, 0);
		close(all->fdinc);
		all->fdout = -5;
	}
}

void	ft_new_redir(char **redir, int i, char **tab, t_all *all)
{
	int j;

	j = 0;
	if (redir[i][0] == '>')
		if (redir[i + 1])
			while (redir[i + ++j])
				if (redir[i + j][0] == '>')
				{
					ft_close(all, 1);
					ft_create_file(all, tab, redir, i + j);
					break ;
				}
	if (redir[i][0] == '<')
		if (redir[i + 1])
			while (redir[i + ++j])
				if (redir[i + j][0] == '<')
				{
					ft_close(all, 2);
					ft_create_file(all, tab, redir, i + j);
					break ;
				}
	if (g_quit == 1)
		ft_close(all, 1);
}

void	ft_create_file(t_all *all, char **tab, char **redir, int i)
{
	int		j;

	j = 0;
	if (redir[i][0] == '>' && redir[i][1] && redir[i][1] == '>' && (j = 1))
		all->fdin = open(tab[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (redir[i][0] == '>' && (j = 1))
		all->fdin = open(tab[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (redir[i][0] == '<' && (j = 2))
		all->fdout = open(tab[i + 1], O_RDONLY);
	ft_open(all, j);
	ft_new_redir(redir, i, tab, all);
	g_quit = 0;
}

char	**ft_all_redir_bis(char *tab, char **new, int i, int j)
{
	int		k;
	int		l;

	while (tab[i])
	{
		if ((tab[i] == '>' || tab[i] == '<') && !isguillemet(i, tab))
		{
			l = 0;
			k = 0;
			while (tab[i + k] && (tab[i + k] == '>' || tab[i + k] == '<'))
				k++;
			while (tab[i + k + l] && tab[i + k + l] == ' ')
				l++;
			if (tab[i + k + l] == '>' || tab[i + k + l] == '<')
				k += l + 1;
			new[j++] = ft_substr(tab, i, k);
			i = i + k;
			while (tab[i] && (tab[i] == ' ' || tab[i] == '>' || tab[i] == '<'))
				i++;
		}
		else
			i++;
	}
	new[j] = NULL;
	return (new);
}
