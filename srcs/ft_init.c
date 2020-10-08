/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:58:15 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/08 17:58:17 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int				dble_ext(char **tab, int i)
{
	int		j;
	int		k;

	j = 1;
	k = 0;
	while (tab[i][k])
		k++;
	while (tab && tab[i + j])
	{
		if (!ft_strncmp(tab[i], tab[i + j], k) &&
		ft_strlen(tab[i + j]) == ft_strlen(tab[i]))
			return (0);
		j++;
	}
	return (1);
}

int				dble(char **tab, int i)
{
	int		j;
	int		k;

	j = 1;
	k = 0;
	while (tab[i][k] != '=')
		k++;
	while (tab && tab[i + j])
	{
		if (!ft_strncmp(tab[i], tab[i + j], k) && tab[i + j][k] == '=')
			return (1);
		j++;
	}
	return (0);
}

static void		ft_remplace(t_all *all)
{
	int		i;

	i = 0;
	while (all->env[i] && ft_strncmp(all->env[i], "PWD=", 4))
		i++;
	if (all->env[i] && !ft_strncmp(all->env[i], "PWD=", 4))
	{
		free(all->env[i]);
		all->env[i] = ft_strdup(all->pwd);
		all->env[i] = ft_strjoin("PWD=", all->env[i], 2);
	}
}

void			tab_env(char **env, t_all *all)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	all->env = ft_calloc(sizeof(char*), (i + 1));
	all->env[i] = NULL;
	i = 0;
	while (env[i])
	{
		all->env[i] = ft_strdup(env[i]);
		i++;
	}
	all->nb_env = i;
}

void			ft_initenv(t_all *all, char **env)
{
	g_inter = 0;
	g_quit = 0;
	g_pipe = 0;
	all->ext = ft_calloc(1, 1);
	all->pwd = getcwd(NULL, 0);
	tab_env(env, all);
	ft_remplace(all);
}
