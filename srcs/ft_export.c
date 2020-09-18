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

char		**ft_exporterreur(char **str, int j)
{
	int				i;
	char			*tmp;
	char			**new;
	int				k;

	i = 0;
	while (str[j][i] && str[j][i] != ' ')
		i++;
	tmp = ft_substr(str[j], 0, i);
	ft_printf("minishell: export: `%s': not a valid identifier\n", tmp);
	free(tmp);
	i = 0;
	k = 0;
	while (str[i])
		i++;
	if (i != 1)
	{
		new = ft_calloc(i - 1, sizeof(char *));
		i = 0;
		while (str[i])
		{
			if (i != j)
			{
				new[k] = ft_strdup(str[i]);
				k++;
			}
			free(str[i]);
			i++;
		}
	}
	else
		new = NULL;
	free(str[i]);
	ret = 1;
	return (new);
}

int			ft_isenvexist(t_all *all, int i, int j, int k)
{
	unsigned int	p;
	int				o;

	p = 0;
	while (all->env[p] && p < all->nb_env - 1)
	{
		o = 0;
		while (all->env[p][o] && (all->env[p][o] == all->tab[j + o]))
		{
			if (all->env[p][o] == '=')
			{
				if (k == 1)
				{
					free(all->env[p]);
					all->env[p] = ft_substr(all->tab, j, i + 1 - j);
				}
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
		if (tabnewenv[j] == '\\' && (tabnewenv[j + 1] && tabnewenv[j + 1] == '\\'))
		{
			j++;
			i++;	
		}
		else if (tabnewenv[j] == '\\' && isguillemet(j, tabnewenv))
			i++;
		j++;
	}
	tmp = ft_calloc(i, sizeof(char) + 1);
	i = 0;
	j = 0;
	while (tabnewenv[i])
	{
		if (tabnewenv[i] == '\\' && tabnewenv[i + 1] && tabnewenv[i + 1] == '\\')
			tmp[j++] = tabnewenv[i++];
		else if (tabnewenv[i] == '\\' && (isguillemet(i, tabnewenv)
		&& (!tabnewenv[i + 1] || (tabnewenv[i + 1] != '\"' && tabnewenv[i + 1] != '\''))))
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

int			ft_nbnewenv(char **tabnewenv, int j, int k, int i)
{
	int				eg;

	eg = 0;
	while (tabnewenv && tabnewenv[++i])
	{
		tabnewenv[i] = ft_suprguy(tabnewenv[i]);
		j = -1;
		eg = 0;
		while (tabnewenv && tabnewenv[i][++j])
		{
			if (eg == 0 && ((tabnewenv[i][j] == '=' && (j == 0 ||
			tabnewenv[i][j - 1] == ' ')) || (tabnewenv[i][j] == '\"'
			|| tabnewenv[i][j] == '\'')))
			{
				tabnewenv = ft_exporterreur(tabnewenv, i);
				i--;
				eg = 1;
			}
		}
	}
	ret = 0;
	while (tabnewenv && tabnewenv[k])
		k++;
	return (k);
}

char		**ft_newenv(t_all *all, int k, int j)
{
	int				i;
	char			**tabnewenv;
	int				eg;

	i = -1;
	k = 0;
	eg = 0;
	while (all->tab[++i])
	{
		if (all->tab[i] == '=')
			eg = 1;
		if ((!all->tab[i + 1] || (all->tab[i + 1] == ' ' &&
		(!isguillemet(i, (const char*)all->tab)))) && eg == 1)
		{
			if (!(ft_isenvexist(all, i, j, 1)))
				k++;
			j = i + 2;
			eg = 0;
		}
	}
	tabnewenv = malloc((sizeof(char*)) * (k + 1));
	i = -1;
	k = 0;
	eg = 0;
	j = 0;
	while (all->tab[++i])
	{
		if (all->tab[i] == '=')
			eg = 1;
		if ((!all->tab[i + 1] || (all->tab[i + 1] == ' ' &&
		(!isguillemet(i, (const char*)all->tab)))) && eg == 1)
		{
			if (!(ft_isenvexist(all, i, j, 0)))
			{
				tabnewenv[k] = ft_substr(all->tab, j, i + 1 - j);
				k++;
			}
			j = i + 2;
			eg = 0;
		}
	}
	tabnewenv[k] = '\0';
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

	j = 0;
	tabnewenv = ft_newenv(all, 0, j);
	if (!(nb_newenv = ft_nbnewenv(tabnewenv, 0, 0, -1)))
		return (ret = 127);
	if (!(new_env = malloc((all->nb_env + nb_newenv + 1) * sizeof(char*))))
		return (ret = 127);
	i = 0;
	while (i < all->nb_env)
	{
		new_env[i + j] = ft_strdup(all->env[i]);
		free(all->env[i]);
		i++;
		if (i == all->nb_env - 1)
			while (j < nb_newenv)
			{
				new_env[i + j] = ft_strdupfree(tabnewenv[j]);
				j++;
			}
	}
	new_env[i + j] = 0;
	free(all->tab);
	all->nb_env += nb_newenv;
	free(tabnewenv);
	free(all->env);
	all->env = new_env;
	return (0);
}
