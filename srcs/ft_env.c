/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:56:34 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/08 17:56:37 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_env(t_all *all)
{
	unsigned int	i;
	char			*tmp;

	i = -1;
	tmp = ft_strtrim(all->tab, " ");
	if (tmp[0])
	{
		ft_printf("env: «%s»: Aucun fichier ou dossier de ce type\n", all->tab);
		ret = 127;
	}
	else
	{
		while (++i < all->nb_env)
		{
			ft_putstr_fd(all->env[i], 1);
			write(1, "\n", 1);
		}
		ret = 0;
	}
	free(tmp);
	free(all->tab);
	return (ret);
}
