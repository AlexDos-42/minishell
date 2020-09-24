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

char			**tab_env(char **env, size_t *nb_env)
{
	size_t	i;
	char	**tmp_env;

	i = 0;
	while (env[i])
		i++;
	if (!(tmp_env = ft_calloc(sizeof(char*), (i + 1))))
		return (NULL);
	tmp_env[i] = NULL;
	i = 0;
	while (env[i])
	{
		if (!(tmp_env[i] = ft_strdup(env[i])))
			return (NULL);
		i++;
	}
	*nb_env = i;
	return (tmp_env);
}

void			ft_initenv(t_all *all, char **env)
{
	g_inter = 0;
	g_quit = 0;
	all->pwd = getcwd(NULL, 0);
	all->env = tab_env(env, &all->nb_env);
	ft_remplace(all);
}
