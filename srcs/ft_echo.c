/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:59:15 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/08 17:59:16 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		ft_putstr_echo(char *str, int fd)
{
	int i;
	int q;

	if (!str || !*str || fd < 0)
		return ;
	i = 0;
	q = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			if (str[i + 1])
			{
				write(fd, &str[i + 1], 1);
				i += 2;
			}
			else
				i++;
		}
		else if ((str[i] && str[i] != '\"' && str[i] != '\'') || (str[i] &&
		((str[i] == '\"' && q == 2) || (str[i] == '\'' && q == 1))))
			write(fd, &str[i++], 1);
	}
}

int			ft_echo(t_all *all)
{
	char *tmp;
	char **new;
	int i;

	i = -1;
	if (!ft_strncmp(all->tab, "-n", 2))
	{
		tmp = ft_strtrim(all->tab + 2, " ");
		new = ft_splitspace(tmp, ' ');
		free(tmp);
		while (new[++i])
		{
			new[i] = ft_suprguy(new[i]);
			ft_putstr_echo(new[i], 1);
			free(new[i]);
			if (new[i + 1])
				write(1, " ", 1);
		}
		free(new);
	}
	else
	{
		tmp = ft_strtrim(all->tab, " ");
		new = ft_splitspace(tmp, ' ');
		free(tmp);
		while (new[++i])
		{
			new[i] = ft_suprguy(new[i]);
			ft_putstr_echo(new[i], 1);
			free(new[i]);
			if (new[i + 1])
				write(1, " ", 1);
		}
		write(1, "\n", 1);
		free(new);
	}
	free(all->tab);
	return (ret = 0);
}
