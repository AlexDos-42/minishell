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

void	ft_putstr_echo(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
	free(str);
}

void	ft_echo_bis(char *tmp, char **new, int i)
{
	free(tmp);
	while (new[++i] && !ft_strncmp(new[i], "-n", 2) && ft_strlen(new[i]) == 2)
		free(new[i]);
	while (new[i])
	{
		ft_putstr_echo(new[i], 1);
		if (new[i + 1])
			write(1, " ", 1);
		++i;
	}
	free(new);
}

void	ft_echo_cond(char *tmp, char **new, int i)
{
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

int		ft_echo(t_all *all)
{
	char	*tmp;
	char	**new;
	int		i;

	i = -1;
	tmp = ft_strtrimslash(all->tab, " ");
	new = ft_splitspace(tmp, ' ');
	while (new[++i])
		new[i] = ft_suprguy(new[i]);
	i = -1;
	if (new[0] && !ft_strncmp(new[0], "-n", 2) && ft_strlen(new[0]) == 2)
		ft_echo_bis(tmp, new, i);
	else
		ft_echo_cond(tmp, new, i);
	free(all->tab);
	return (g_ret = 0);
}
