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

char		**ft_nbnewenv(char **tabnewenv, int j, int i)
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
					return (tabnewenv);
				break ;
			}
			else if (tabnewenv[i][j] == '=')
			{
				i++;
				break ;
			}
	}
	return (tabnewenv);
}

char		**ft_newenvbis(t_all *all, int i, int eg, char **tab)
{
	int				j;

	while (tab && tab[++eg])
		tab[eg] = ft_suprguy(tab[eg]);
	while (!(eg = 0) && tab && tab[i])
	{
		if (!tab[i][0] && (g_ret = 1))
			ft_printf("minishell: export: `': not a valid identifier\n");
		j = -1;
		while (tab[i][++j])
			if (tab[i][j] == '=')
				eg = 1;
		if (eg == 0 || ft_isenvexist(all, tab[i]) || dble(tab, i))
		{
			if (tab[i][0] && dble_ext(tab, i) && !isenvexist_ext(all, tab[i]))
				put_export(eg, all, j, tab[i]);
			if (eg == 0 && (j = -1))
				while (tab[i][++j] && eg == 0)
					eg = isexporterror(tab[i], j);
			tab = ft_freetab(tab, i);
		}
		else
			i++;
	}
	return (tab);
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

	if ((tabnewenv = ft_newenv(all, 0, -1)) == NULL ||
		(tabnewenv = ft_nbnewenv(tabnewenv, 0, 0)) == NULL)
		return (0);
	while (tabnewenv && tabnewenv[nb_newenv])
		nb_newenv++;
	if (!(new_env = malloc((all->nb_env + nb_newenv + 1) * sizeof(char*))))
		return (g_ret = 127);
	while (++i < all->nb_env)
		new_env[i] = ft_strdup(all->env[i]);
	while (++j < nb_newenv)
	{
		new_env[i + j] = ft_strdup(tabnewenv[j]);
		ft_suprext(all, tabnewenv[j], 0, 0);
	}
	new_env[i + j] = 0;
	all->nb_env += nb_newenv;
	ft_freexec(tabnewenv);
	ft_freexec(all->env);
	all->env = new_env;
	return (0);
}

int			ft_export(t_all *all)
{
	g_ret = 0;
	if (!all->tab[0])
	{
		export_solo(all, -1, 0, NULL);
		free(all->tab);
	}
	else
		ft_exportinit(all, -1, -1, 0);
	return (0);
}
