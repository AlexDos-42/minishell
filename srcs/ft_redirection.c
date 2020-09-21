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

char	*ft_get_file(char *tmp)
{
	char	*name;
	int		j;

	j = 0;
	while (tmp[j])
		j++;
	if (tmp[j] == '\n')
		j--;
	name = ft_substr(tmp, 0, j);
	name[j - 1] = '\0';
	return (name);
}

char	*ft_create_file(t_all *all, char **tab, char *redir, int i)
{
	// ft_printf("tab %s\n", tab[i]);
	// ft_printf("tab %s\n", tab[i + 1]);
	if (redir[0] == '>' && redir[1] && redir[1] == '>')
	 	all->fdin = open(tab[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (redir[0] == '>')
		all->fdin = open(tab[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (redir[0] == '<')
		all->fdin = open(tab[i + 1], O_WRONLY, 0);
	if (all->fdin >= 0)
	{	
			all->fdout = dup(1);
			close(1);
			dup2(all->fdin, 1);
	}
	ft_loop(tab[i], all);
		// if (all->fdout >= 0)
		// {	
		// 	all->fdin = dup(0);
		// 	close(0);
		// 	dup2(all->fdout, 1);
		// }
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


int		ft_redirection(char *tab, t_all *all)
{
	int		i;
	char	**redir;
	char	**new;
	char	*tmp;

	i = -1;
	redir = ft_allredir(tab);
	all->fdin = -5;
	if (redir != NULL)
	{
		new = ft_splitslash(tab, '>');
		
		while (new[++i])
		{
			tmp = ft_strtrimslash(new[i], " ");
			free(new[i]);
			new[i] = ft_suprguy(tmp);
		}
		i = 0;
		while (redir[i])
		{
			ft_create_file(all, new, redir[i], i);
			i++;
		}
		ft_freexec(redir);
		ft_freexec(new);
		return (1);
	}
	return (0);
}
