/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 14:36:23 by edouvier          #+#    #+#             */
/*   Updated: 2020/10/13 14:36:26 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			is_two_pipe(char *tab)
{
	int		i;
	int		j;

	i = -1;
	while (tab[++i])
		if (tab[i] == '|')
		{
			j = 1;
			while (tab[i + j] == ' ')
				j++;
			if (tab[i + j] == '|')
			{
				g_ret = 1;
				ft_printf("minishell: syntax error");
				ft_printf(" near unexpected token `|'\n");
				return (0);
			}
		}
	return (1);
}

char		*if_or_else(char *new, char *tab, int l, int k)
{
	if (new[l + k])
		new = join_tmp(new, l, tab);
	else if (!new[l + k])
		new = join_first(new, tab);
	return (new);
}
