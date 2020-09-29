/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 16:41:57 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/16 16:42:00 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			ft_nbnewenv(char **tabnewenv, int j, int k, int i)
{
	g_ret = 0;
	while (tabnewenv && tabnewenv[i])
	{
		j = -1;
		if (isexporterror(tabnewenv[i], 0))
			if ((tabnewenv = ft_exporterreur(tabnewenv, i)) == NULL)
				return (0);
		while (tabnewenv[i] && tabnewenv[i][++j])
			if (isexporterror(tabnewenv[i], j))
			{
				if ((tabnewenv = ft_exporterreur(tabnewenv, i)) == NULL)
					return (0);
				j = -1;
			}
			else if (tabnewenv[i][j] == '=')
			{
				i++;
				j = -1;
			}
	}
	while (tabnewenv && tabnewenv[k])
		k++;
	return (k);
}

int			dble(char **tab, int i)
{
	int				j;
	int				k;

	j = 1;
	k = 0;
	while (tab[i][k] != '=')
		k++;
	while (tab && tab[i + j])
	{
		if (!ft_strncmp(tab[i], tab[i + j], k))
			return (1);
		j++;
	}
	return (0);
}

char		**ft_newenvbis(t_all *all, int i, int eg, char **tabnewenv)
{
	int				j;

	while (tabnewenv && tabnewenv[++i])
		tabnewenv[i] = ft_suprguy(tabnewenv[i]);
	i = 0;
	while (tabnewenv && tabnewenv[i])
	{
		if (!tabnewenv[i][0])
			ft_printf("minishell: export: `': not a valid identifier\n");
		j = -1;
		eg = 0;
		while (tabnewenv[i][++j])
			if (tabnewenv[i][j] == '=')
				eg = 1;
		if (eg == 0 || ft_isenvexist(all, tabnewenv[i]) || dble(tabnewenv, i))
		{
			if (eg == 0 && (j = -1))
				while (tabnewenv[i][++j] && eg == 0)
					eg = isexporterror(tabnewenv[i], j);
			tabnewenv = ft_freetab(tabnewenv, i);
		}
		else
			i++;
	}
	return (tabnewenv);
}

char		**ft_newenv(t_all *all, int i, int eg)
{
	char			**tabnewenv;
	char			*tmp;

	tmp = ft_strtrimslash(all->tab, " ");
	free(all->tab);
	tabnewenv = ft_splitspace(tmp, ' ');
	free(tmp);
	return (ft_newenvbis(all, i, eg, tabnewenv));
}

int			ft_exportinit(t_all *all, unsigned int i, int j, int nb_newenv)
{
	char			**tabnewenv;
	char			**new_env;

	if ((tabnewenv = ft_newenv(all, -1, 0)) == NULL ||
		!(nb_newenv = ft_nbnewenv(tabnewenv, 0, 0, 0)))
		return (0);
	if (!(new_env = malloc((all->nb_env + nb_newenv + 1) * sizeof(char*))))
		return (g_ret = 127);
	while (i < all->nb_env)
	{
		new_env[i + j] = ft_strdup(all->env[i]);
		free(all->env[i++]);
	}
	while (j < nb_newenv)
	{
			new_env[i + j] = ft_strdup(tabnewenv[j]);
			j++;
	}
	new_env[i + j] = 0;
	all->nb_env += nb_newenv;
	ft_freexec(tabnewenv);
	free(all->env);
	all->env = new_env;
	return (0);
}

int			ft_export(t_all *all)
{
	if (!all->tab[0])
		export_solo(all);
	else
		ft_exportinit(all, 0, 0, 0);
	return (0);
}
