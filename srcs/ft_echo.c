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

	i = 0;
	str = ft_suprguy(str);
	while (str[i])
			write(fd, &str[i++], 1);
	free(str);
}

int			ft_echo(t_all *all)
{
	char *tmp;
	char **new;
	int i;

	i = -1;
	if (!ft_strncmp(all->tab, "-n", 2))
	{
		tmp = ft_strtrimslash(all->tab + 2, " ");
		new = ft_splitspace(tmp, ' ');
		free(tmp);
		while (new[++i])
		{
			ft_putstr_echo(new[i], 1);
			if (new[i + 1])
				write(1, " ", 1);
		}
		free(new);
	}
	else
	{
		tmp = ft_strtrimslash(all->tab, " ");
		new = ft_splitspace(tmp, ' ');
		free(tmp);
		while (new[++i])
		{
			ft_putstr_echo(new[i], 1);
			if (new[i + 1])
				write(1, " ", 1);
		}
		write(1, "\n", 1);
		free(new);
	}
	free(all->tab);
	return (ret = 0);
}
