/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:57:49 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/08 17:57:51 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_exitret(char **tab)
{
	long long int i;

	i = ft_atoi(tab[0]);
	// if (i < LONG_MIN || i > LONG_MAX)
	// {
	// 	ft_printf("minishell: exit: %s: numeric argument required\n", tab[0]);
	// 	i = 2;
	// }
	// else
	i = i % 256;
	ft_freexec(tab);
	return (ret = i);
}

int		ft_cleanexit(char *tab)
{
	int		i;
	char	**new;
	char	*tmp;

	i = 0;
	tmp = ft_strtrim(tab, " ");
	free(tab);
	if (!(tmp[0]))
	{
		free(tmp);
		return (0);
	}
	new = ft_splitspace(tmp, ' ');
	free(tmp);
	new[0] = ft_suprguy(new[0]);
	while (new[0][i] == ' ' || new[0][i] == '\t' || new[0][i] == '\f' || new[0][i] == '\r')
		i++;
	if (new[0][i] == '-' || new[0][i] == '+')
		i++;
	while (new[0][i])
	{
		if (new[0][i] != '1' && new[0][i] != '2' &&
		new[0][i] != '3' && new[0][i] != '4' &&new[0][i] != '5'
		&& new[0][i] != '6' && new[0][i] != '7' &&
		new[0][i] != '8' && new[0][i] != '9' && new[0][i] != '0')
		{
			while (new[0][i] && ((new[0][i] == ' ' || new[0][i] == '\t') &&
					(!new[0][i + 1] || new[0][i + 1] == ' ' || new[0][i + 1] == '\t')))
					i++;
			if (new[0][i])
			{
				ft_printf("minishell: exit: %s: numeric argument required\n", new[0]);
				ft_freexec(new);
				return(2);
			}
		}
		else
			i++;
	}
	if (new[1])
	{
		ft_printf("minishell: exit: too many arguments\n");
		ft_freexec(new);
		return(1);
	}
	return(ft_exitret(new));
}

int		ft_exit(t_all *all)
{
	ret = ft_cleanexit(all->tab);
	//ft_printf("ret %d\n", ret);
	return (2);
}
