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

void		ft_open(t_all *all)
{
	if (all->fdin >= 0)
	{	
		all->fdoutc = dup(1);
		close(1);
		dup2(all->fdin, 1);
	}
	if (all->fdout >= 0)
	{	
		all->fdinc = dup(0);
		close(0);
		dup2(all->fdout, 0);
	}
}

void		ft_close(t_all *all)
{
	if (all->fdin >= 0)
	{
		dup2(all->fdoutc, 1);
		close(all->fdoutc);
	}
	if (all->fdout >= 0)
	{
		dup2(all->fdinc, 0);
		close(all->fdinc);
	}
}

char	*ft_create_file(t_all *all, char **tab, char **redir, int i)
{
	// ft_printf("tab %s\n", tab[i]);
	// ft_printf("tab %s\n", tab[i + 1]);
	if (redir[i][0] == '>' && redir[1] && redir[i][1] == '>')
	 	all->fdin = open(tab[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (redir[i][0] == '>')
		all->fdin = open(tab[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (redir[i][0] == '<')
		all->fdout = open(tab[i + 1], O_RDONLY);
	ft_open(all);
	if (redir[i][0] == '>')
		if (redir[i + 1])
			if (redir[++i][0] == '>')
			{
				ft_close(all);
				ft_create_file(all, tab, redir, i);
			}
	return (NULL);
}

char	**ft_allredir(char *tab)
{
	int 	i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	while(tab[i])
	{
		if (tab[i] == '>' || tab[i] == '<')
		{
			if (tab[i + 1] && tab[i + 1] == '>')
				i++;
			j++;
		}
		i++;
	}
	if (j == 0)
		return (NULL);
	new = ft_calloc(j + 1, sizeof(char *));
	j = 0;
	i = 0;
	while(tab[i])
	{
		if (tab[i] == '>' || tab[i] == '<')
		{
			if (tab[i + 1] && tab[i + 1] == '>')
			{
				new[j++] = ft_strdup(">>");
				i++;
			}
			else
				new[j++] = ft_strdup(">");
		}
		else if (tab[i] == '<')
			new[j++] = ft_strdup("<");
		i++;
	}
	new[j] = NULL;
	return (new);
}


char		*ft_redirection(char *tab, t_all *all)
{
	int		i;
	char	**redir;
	char	**new;
	char	*tmp;

	i = -1;
	redir = ft_allredir(tab);
	all->fdin = -5;
	all->fdout = -5;
	if (redir != NULL)
	{
		new = ft_splitslash(tab, "><");
		while (new[++i])
		{
			tmp = ft_strtrimslash(new[i], " ");
			free(new[i]);
			tmp = ft_suprguy(tmp);
			if (tmp[ft_strlen(tmp) - 1] == '\n')	
				new[i] = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
			else
				new[i] = ft_strdup(tmp);
			free(tmp);
		}
		i = 0;
		tmp = ft_strdup(new[0]);
		ft_create_file(all, new, redir, i);
		ft_freexec(redir);
		ft_freexec(new);
		return (tmp);
	}
	return (ft_strdup(tab));
}
