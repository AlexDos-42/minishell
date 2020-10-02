/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:35:56 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/24 10:35:58 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		export_solo(t_all *all)
{
	int		i;

	i = -1;
	while (all->env[++i])
	{
		ft_printf("export %s\n", all->env[i]);
	}
	i = -1;
	while (all->ext[++i])
	{
		ft_printf("export %s\n", all->ext[i]);
	}
	free(all->tab);
}

char		**ft_exporterreur(char **str, int j)
{
	int				i;
	char			**new;
	int				k;

	i = 0;
	k = 0;
	while (str && str[i])
		i++;
	if (i != 1)
	{
		new = ft_calloc(i, sizeof(char *));
		i = -1;
		while (str[++i])
			if (i != j)
				new[k++] = ft_strdup(str[i]);
		new[k] = '\0';
	}
	else
		new = NULL;
	ft_freexec(str);
	g_ret = 1;
	return (new);
}

int			ft_isenvexist(t_all *all, char *tab)
{
	unsigned int	p;
	int				o;

	p = 0;
	while (all->env[p] && p < all->nb_env)
	{
		o = 0;
		while (all->env[p][o] && (all->env[p][o] == tab[o]))
		{
			if (all->env[p][o] == '=')
			{
				free(all->env[p]);
				all->env[p] = ft_strdup(tab);
				return (1);
			}
			o++;
		}
		p++;
	}
	return (0);
}

char		**ft_freetab(char **tabnewenv, int i)
{
	int				j;
	int				k;
	char			**new;

	j = 0;
	while (tabnewenv[j])
		j++;
	if (j == 1)
	{
		ft_freexec(tabnewenv);
		return (NULL);
	}
	new = ft_calloc(j, sizeof(char*));
	j = -1;
	k = 0;
	while (tabnewenv[++j])
	{
		if (j != i)
			new[k++] = ft_strdup(tabnewenv[j]);
		new[k] = NULL;
	}
	ft_freexec(tabnewenv);
	return (new);
}

int			isexporterror(char *tab, int j)
{
	if (tab[0] == '0' || tab[0] == '1' || tab[0] == '2'
			|| tab[0] == '3' || tab[0] == '4'
			|| tab[0] == '5' || tab[0] == '6'
			|| tab[0] == '7' || tab[0] == '8' || tab[0] == '9')
	{
		ft_printf("minishell: export: `%s': not a valid identifier\n", tab);
		return (1);
	}
	if (tab[j] == '=' && j == 0)
	{
		ft_printf("minishell: export: `%s': not a valid identifier\n", tab);
		return (1);
	}
	if (tab[j] < 48 || (tab[j] > 57 && tab[j] < 65) || (tab[j] > 90
		&& tab[j] < 97) || tab[j] > 122)
		if (tab[j] != '=' && tab[j] != '_')
		{
			ft_printf("minishell: export: `%s': not a valid identifier\n", tab);
			return (1);
		}
	return (0);
}
