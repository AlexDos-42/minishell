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

int		ft_exitret(char *tab)
{
	long long int i;

	i = ft_atoi(tab) % 256;
	free(tab);
	return (ret = i);
}

int		ft_cleanexit(char *tab)
{
	char	*tmp;
	int		i;
	char	**new;

	i = 0;
	tmp = ft_strtrim(tab, " ");
	tmp = ft_suprguy(tmp);
	while (tmp[i] == ' ' || tmp[i] == '\t' || tmp[i] == '\f' || tmp[i] == '\r')
		i++;
	if (tmp[i] == '-' || tmp[i] == '+')
		i++;
	while (tmp[i])
	{
		if (tmp[i] != '1' && tmp[i] != '2' &&
		tmp[i] != '3' && tmp[i] != '4' && tmp[i] != '5'
		&& tmp[i] != '6' && tmp[i] != '7' &&
		tmp[i] != '8' && tmp[i] != '9' && tmp[i] != '0')
		{
			if (tmp[i] != ' ' && tmp[i] != '\t')
			{
				new = ft_splitspace(tab, ' ');
				new[0] = ft_suprguy(new[0]);
				ft_printf("minishell: exit: %s: numeric argument required\n", new[0]);
				ft_freexec(new);
				free(tab);
				free(tmp);
				return(2);
			}
			else
			{
				while (tmp[i] && ((tmp[i] == ' ' || tmp[i] == '\t') &&
					(!tmp[i + 1] || tmp[i + 1] == ' ' || tmp[i + 1] == '\t')))
					i++;
				if (tmp[i])
				{
					ft_printf("minishell: exit: too many arguments\n", tmp);
					free(tmp);
					free(tab);
					return(2);
				}
			}
		}
		else
			i++;
	}
	free(tab);
	return(ft_exitret(tmp));
}

int		ft_exit(t_all *all)
{
	ret = ft_cleanexit(all->tab);
	//ft_printf("ret %d\n", ret);
	return (2);
}
