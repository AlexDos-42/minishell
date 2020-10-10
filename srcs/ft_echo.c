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

int		ft_echo_bis(char **new, int i)
{
	int j;

	while (new[++i] && !ft_strncmp(new[i], "-n", 2))
	{
		j = 1;
		while (new[i][j] && new[i][j] == 'n')
			j++;
		if (i == 0 && new[0][j])
			return (0);
		if (!new[i][j])
			free(new[i]);
		else
			break ;
	}
	while (new[i])
	{
		ft_putstr_echo(new[i], 1);
		if (new[i + 1])
			write(1, " ", 1);
		++i;
	}
	free(new);
	return (1);
}

void	ft_echo_cond(char **new, int i)
{
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
	free(tmp);
	while (new[++i])
	{
		if (new[i][0] == '~' && !new[i][1])
		{	
			free(new[i]);
			new[i] = ft_strdup("/home/user42");
		}
		new[i] = ft_suprguy(new[i]);
	}
	i = -1;
	if (new[0] && !ft_strncmp(new[0], "-n", 2))
		if (ft_echo_bis(new, i))
		{
			free(all->tab);
			return (g_ret = 0);
		}
	i = -1;
	ft_echo_cond(new, i);
	free(all->tab);
	return (g_ret = 0);
}

int		isenvexist_ext(t_all *all, char *tab)
{
	int		p;
	int		o;

	p = -1;
	while (all->nb_ext && all->ext[++p] && p < all->nb_ext)
	{
		o = -1;
		while (all->ext[p][++o] && (all->ext[p][o] == tab[o]))
			if (!all->ext[p][o + 1] && !tab[o + 1])
				return (1);
	}
	p = -1;
	while (all->env[++p])
	{
		o = 0;
		while (all->env[p][o] && (all->env[p][o] == tab[o]))
		{
			if (all->env[p][o + 1] == '=' && !tab[o + 1])
				return (1);
			o++;
		}
	}
	return (0);
}
