/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_next.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 16:12:53 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/24 16:12:54 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_minishell_again(char **tab, t_all *all, int k, int stop)
{
	while (tab && tab[++k])
	{
		if ((tab[k] = ft_replace(tab[k], all, -1, -1)))
		{
			if (ft_ispipe(tab[k]))
				ft_pipe(tab[k], all);
			else if ((stop = ft_loop(tab[k], all)))
			{
				while (tab && tab[k])
					free(tab[k++]);
				break ;
			}
		}
		free(tab[k]);
	}
	return (tab);
}

int		ft_minishell(t_all *all, char *str)
{
	int		k;
	char	**tab;
	int		stop;

	stop = 0;
	k = -1;
	while (str[++k] && (str[k] == ';' || str[k] == ' '))
		if (str[k] == ';')
		{
			ft_printf("minishell: syntax error near unexpected token `;'\n");
			g_ret = 1;
			return (stop);
		}
	tab = ft_splitslash(str, ";");
	k = -1;
	ft_minishell_again(tab, all, k, stop);
	if (tab)
		free(tab);
	return (stop);
}
