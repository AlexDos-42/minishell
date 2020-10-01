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

int				ft_error(char *tmp)
{
	tmp = ft_strjoin("minishell: unset: `", tmp, 2);
	tmp = ft_strjoin(tmp, "': not a valid identifier", 1);
	ft_printf("%s\n", tmp);
	free(tmp);
	g_ret = 1;
	return (0);
}

void			ft_suprenv(t_all *all, char *new, unsigned int p, int o)
{
	unsigned int	i;
	unsigned int	k;
	char			**new_tab;

	while (all->env[p] && p < all->nb_env && ((o = -1) == -1))
	{
		while (all->env[p][++o] && (all->env[p][o] == new[o]))
			if (all->env[p][o + 1] == '=' && !(k = 0))
			{
				i = 0;
				new_tab = ft_calloc(sizeof(char*), all->nb_env--);
				while (k < all->nb_env)
				{
					if (i != p)
						new_tab[k++] = ft_strdup(all->env[i]);
					i++;
				}
				ft_freexec(all->env);
				all->env = new_tab;
				free(new);
				return ;
			}
		p++;
	}
	free(new);
}

int				ft_unset(t_all *all)
{
	int				i;
	int				j;
	char			*tmp;
	char			**new;

	i = -1;
	tmp = ft_strtrimslash(all->tab, " ");
	new = ft_splitspace(tmp, ' ');
	free(tmp);
	while (new[++i])
	{
		new[i] = ft_suprguy(new[i]);
		if (!new[i][0])
			ft_printf("minishell: unset: `': not a valid identifier\n");
		j = 0;
		while (new[i][j] && new[i][j] != '=' && new[i][j] != ' ')
			j++;
		if (new[i][j])
			ft_error(new[i]);
		else
			ft_suprenv(all, new[i], 0, 0);
	}
	free(all->tab);
	free(new);
	return (0);
}

int				ft_pipe(char *tab, t_all *all)
{
	int		i;

	i = -1;
	while (tab[++i] && (tab[i] == ' ' || tab[i] == '|'))
		if (tab[i] == '|')
		{
			g_ret = 1;
			ft_printf("minishell: syntax error near unexpected token `|'\n");
			return (0);
		}
	if (is_two_pipe(tab) == 0)
		return (0);
	return (ft_pipeinit(tab, all, i, 0));
}
