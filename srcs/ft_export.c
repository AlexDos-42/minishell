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

void		export_solo(t_all *all)
{
	int		i;

	i = -1;
	while (all->env[++i])
	{
		ft_printf("export %s\n", all->env[i]);
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
		i = 0;
		while (str[i])
		{
			if (i != j)
			{
				new[k] = ft_strdup(str[i]);
				k++;
			}
			i++;
		}
		new[k] = '\0';
	}
	else
		new = NULL;
	ft_freexec(str);
	ret = 1;
	return (new);
}

int			ft_isenvexist(t_all *all, char *tab)
{
	unsigned int	p;
	int				o;

	p = 0;
	while (all->env[p] && p < all->nb_env - 1)
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

char	*ft_suprguy(char *tabnewenv)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tabnewenv[j])
	{
		if (((tabnewenv[j] != '\"' && tabnewenv[j] != '\'') ||
		isguillemet(j, tabnewenv)) && tabnewenv[j] != '\\')
			i++;
		if (tabnewenv[j] == '\\' && (tabnewenv[j + 1] && tabnewenv[j + 1] == '\\')
			&& (isguillemet(j, tabnewenv) == 1 || !isguillemet(j, tabnewenv)))
		{
			i++;
			j++;
		}
		else if (tabnewenv[j] == '\\' && (isguillemet(j, tabnewenv) == 2
		|| (isguillemet(i, tabnewenv) == 1 &&
			(tabnewenv[i + 1] != '\"' || tabnewenv[i + 1] != '$'))))
			i++;
		j++;
	}
	tmp = ft_calloc(i, sizeof(char) + 1);
	i = 0;
	j = 0;
	while (tabnewenv[i])
	{
		if (tabnewenv[i] == '\\' && (tabnewenv[i + 1] && tabnewenv[i + 1] == '\\'
			&& (isguillemet(i, tabnewenv) == 1 || !isguillemet(j, tabnewenv))))
			tmp[j++] = tabnewenv[i++];
		else if (tabnewenv[i] == '\\' && ((isguillemet(i, tabnewenv) == 2)
			|| (isguillemet(i, tabnewenv) == 1 &&
			(tabnewenv[i + 1] != '\"' && tabnewenv[i + 1] != '$'))))
			tmp[j++] = tabnewenv[i];
		else if (((tabnewenv[i] != '\"' && tabnewenv[i] != '\'') ||
			isguillemet(i, tabnewenv)) && tabnewenv[i] != '\\')
			tmp[j++] = tabnewenv[i];
		i++;
	}
	tmp[j] = '\0';
	free(tabnewenv);
	return (tmp);
}

int			isexporterror(char *tab, int j)
{
	if (tab[0] == '0' || tab[0] == '1' || tab[0] == '2'
			|| tab[0] == '3' || tab[0] == '4'
			|| tab[0] == '5' || tab[0] == '6'
			|| tab[0] == '7' || tab[0] == '8'
			|| tab[0] == '9')
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
	{
		if (tab[j] != '=' && tab[j] != '_')
		{
			ft_printf("minishell: export: `%s': not a valid identifier\n", tab);
			return (1);
		}
	}
	return (0);
	
}
int			ft_nbnewenv(char **tabnewenv, int j, int k)
{
	int i;

	i = 0;
	ret = 0;
	while (tabnewenv && tabnewenv[i])
	{
		j = -1;
		if (isexporterror(tabnewenv[i], 0))
				if ((tabnewenv = ft_exporterreur(tabnewenv, i)) == NULL)
					return(0);
		while (tabnewenv[i] && tabnewenv[i][++j])
		{
			if (isexporterror(tabnewenv[i], j))
			{
				if ((tabnewenv = ft_exporterreur(tabnewenv, i)) == NULL)
					return(0);
				j = -1;
			}
			else if (tabnewenv[i][j] == '=')
			{
				i++;
				j = -1;
			}
		}
	}
	while (tabnewenv && tabnewenv[k])
		k++;
	return (k);
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
	while(tabnewenv[++j])
	{
		if (j != i)
			new[k++] = ft_strdup(tabnewenv[j]);
		new[k] = NULL;
	}
	ft_freexec(tabnewenv);
	return (new);
}

char		**ft_newenv(t_all *all)
{
	int				i;
	char			**tabnewenv;
	int				eg;
	char			*tmp;
	int				j;

	tmp = ft_strtrimslash(all->tab, " ");
	free(all->tab);
	tabnewenv = ft_splitspace(tmp, ' ');
	free(tmp);
	i = 0;
	eg = 0;
	while (tabnewenv && tabnewenv[i])
	{
		tabnewenv[i] = ft_suprguy(tabnewenv[i]);
		if (!tabnewenv[i][0])
			ft_printf("minishell: export: `': not a valid identifier\n");
		j = -1;
		eg = 0;
		while (tabnewenv[i][++j])
			if (tabnewenv[i][j] == '=')
				eg = 1;
		if (eg == 0 || ft_isenvexist(all, tabnewenv[i]))
		{
			if (eg == 0)
			{
				j = -1;
				while(tabnewenv[i][++j] && eg == 0)
					eg = isexporterror(tabnewenv[i], j);
			}
			tabnewenv = ft_freetab(tabnewenv, i);
		}
		else	
			i++;
	}
	return (tabnewenv);
}

char	*ft_strdupfree(char *src)
{
	int		i;
	char	*dest;

	i = 0;
	if (!(dest = (char *)malloc(ft_strlen(src) * sizeof(char) + 1)))
		return (0);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	free(src);
	return (dest);
}

int			ft_export(t_all *all)
{
	unsigned int	i;
	char			**tabnewenv;
	char			**new_env;
	int				nb_newenv;
	int				j;


	if (!all->tab[0])
		export_solo(all);
	else
	{
		if ((tabnewenv = ft_newenv(all)) == NULL)
			return (0);
		if (!(nb_newenv = ft_nbnewenv(tabnewenv, 0, 0)))
			return (0);
		if (!(new_env = malloc((all->nb_env + nb_newenv + 1) * sizeof(char*))))
			return (ret = 127);
		i = 0;
		j = 0;
		while (i < all->nb_env)
		{
			new_env[i + j] = ft_strdup(all->env[i]);
			free(all->env[i]);
			i++;
			if (i == all->nb_env - 1)
				while (j < nb_newenv)
				{
					new_env[i + j] = ft_strdup(tabnewenv[j]);
					j++;
				}
		}
		new_env[i + j] = 0;
		all->nb_env += nb_newenv;
		ft_freexec(tabnewenv);
		free(all->env);
		all->env = new_env;
	}
	return (0);
}
