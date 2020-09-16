/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:59:28 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/08 17:59:29 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void			ft_messerror(t_all *all, int j, int i)
{
	char			*messerror;

	messerror = ft_substr(all->tab, j, i);
	messerror = ft_strjoin("minishell: unset: « ", messerror, 2);
	messerror = ft_strjoin(messerror, " » : invalid parameter name", 1);
	ft_printf("%s\n", messerror);
	free(messerror);
}

int				ft_error(t_all *all, int j)
{
	int				i;
	int				k;

	k = 0;
	i = 0;
	ret = 1;
	while (all->tab[j + i] != '=')
		i++;
	if (!all->tab[j + i + 1] || all->tab[j + i + 1] == ' ')
		ft_messerror(all, j, i + 1);
	else
	{
		ft_printf("test\n");
		while (all->tab[j + k] && all->tab[j + k + 1] != ' ')
			k++;
		ft_messerror(all, j, k + 1);
	}
	return (0);
}

void			ft_suprenv(t_all *all, int j, unsigned int p, int o)
{
	unsigned int	i;
	unsigned int	k;
	char			**new_tab;

	while (all->env[p] && p < all->nb_env - 1)
	{
		o = -1;
		while (all->env[p][++o] && (all->env[p][o] == all->tab[j + o]))
			if (all->env[p][o + 1] == '=')
			{
				i = 0;
				k = 0;
				new_tab = ft_calloc(sizeof(char*), all->nb_env--);
				while (k < all->nb_env)
				{
					if (i != p)
						new_tab[k++] = ft_strdup(all->env[i]);
					free(all->env[i++]);
				}
				free(all->env);
				all->env = new_tab;
				return ;
			}
		p++;
	}
}

int				ft_unset(t_all *all)
{
	int				i;
	int				err;
	int				j;

	i = -1;
	err = 0;
	j = 0;
	ret = 0;
	while (all->tab && all->tab[++i])
	{
		if (all->tab[i] == '=')
			err = 1;
		if ((all->tab[i + 1] == ' ' || !all->tab[i + 1]))
		{
			if (err == 1)
				err = ft_error(all, j);
			else
				ft_suprenv(all, j, 0, 0);
			j = i + 2;
		}
	}
	free(all->tab);
	return (0);
}
