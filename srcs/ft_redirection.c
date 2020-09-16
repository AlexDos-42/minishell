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
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (tmp[i] == ' ')
		i++;
	while (tmp[i + j])
	{
		j++;
		k = 0;
		while (tmp[i + j + k] && tmp[i + j + k] == ' ')
			k++;
		if (tmp[i + j + k])
			j += k;
		else
			break ;
	}
	name = ft_substr(tmp, i, j - 1);
	name[j - 1] = '\0';
	return (name);
}

char	*ft_create_file(t_all *all, char *tab, int fd, char *file, int *i)
{
	char **tmp;
	if (tab[*i] == '>' && tab[(*i) + 1] == '>')
	{
		tmp = ft_splitslash(tab, '>');
		file = ft_get_file(tmp[2]);
	 	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0666);
		all->fdin = fd;
		all->fdout = dup(1);
		close(1);
		dup2(fd, 1);
	}
	else if (tab[*i] == '>')
	{
		tmp = ft_splitslash(tab, '>');
		if ((file = ft_get_file(tmp[1])) != 0)
			fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		all->fdin = fd;
		all->fdout = dup(1);
		close(1);
		dup2(fd, 1);
	}
	else if (tab[*i] == '<')
	{
		file = ft_get_file(&tab[(*i) + 1]);
		dup2((fd = open(file, O_WRONLY)), 0);
	}
	if (file)
		free(file);
	return (tmp[0]);
}

char	*ft_redirection(char *tab, t_all *all)
{
	(void)all;
	char	*file;
	int		fd;
	int		i;
	char	*tmp;

	fd = 0;
	file = 0;
	i = 0;
	all->fdin = -5;
	while (tab[i])
	{
		if ((ft_strchr("><", tab[i])))
		{
			tmp = ft_create_file(all, tab, fd, file, &i);
			return (tmp);
		}
		i++;
	}
	return (tab);
}
