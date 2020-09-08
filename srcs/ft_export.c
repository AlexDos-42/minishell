<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:57:07 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/08 17:57:09 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exporterreur(char *str, int k)
=======
#include "../include/minishell.h"

void		ft_exporterreur(char *str, int k)
>>>>>>> dc46c8f941bb473443947ffe858cd529065dd630
{
	if (!str[1])
	{
		if (k)
			write(1, "export: not valid in this context:\n", 36);
		else
			write(1, "minshell: bad assignment\n", 26);
	}
	else
	{
		str++;
		write(1, "minishell: ", 12);
		write(1, str, ft_strlen(str));
		write(1, " not found\n", 11);
		ret = 1;
	}
}

<<<<<<< HEAD
int		ft_isenvexist(t_all *all, int i, int j, int k)
{
	unsigned int	p;
	int		o;
=======
int			ft_isenvexist(t_all *all, int i, int j, int k)
{
	unsigned int	p;
	int				o;
>>>>>>> dc46c8f941bb473443947ffe858cd529065dd630

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

<<<<<<< HEAD
int		ft_nbnewenv(t_all *all)
{
	int		i;
	int		k;
	int		eg;
	int		j;
=======
int			ft_nbnewenv(t_all *all, int j, int k, int i)
{
	int				eg;
>>>>>>> dc46c8f941bb473443947ffe858cd529065dd630

	eg = 0;
<<<<<<< HEAD
	j = 0;
	while (all->tab[++i])
	{
		if (all->tab[i] == '=')
		{
			eg = 1;
=======
	while (all->tab[++i])
	{
		if (all->tab[i] == '=' && (eg = 1) == 1)
>>>>>>> dc46c8f941bb473443947ffe858cd529065dd630
			if (i == 0 || (all->tab[i - 1] == ' ' || !all->tab[i - 1]))
			{
				ft_exporterreur(&all->tab[i], k);
				free(all->tab);
				return (0);
			}
		if ((all->tab[i + 1] == ' ' || !all->tab[i + 1]) && eg == 1)
		{
			if (!(ft_isenvexist(all, i, j, 1)))
				k++;
			j = i + 2;
			eg = 0;
		}
	}
	if (k == 0)
		free(all->tab);
	return (k);
}

char		**ft_newenv(t_all *all, int k, int j)
{
<<<<<<< HEAD
	int		i;
	int		j;
	char	**tabnewenv;
	int		eg;
=======
	int				i;
	char			**tabnewenv;
	int				eg;
>>>>>>> dc46c8f941bb473443947ffe858cd529065dd630

	i = -1;
	tabnewenv = malloc(sizeof(char*) * (k + 1));
	k = 0;
	eg = 0;
	while (all->tab[++i])
	{
		if (all->tab[i] == '=')
			eg = 1;
		if ((all->tab[i + 1] == ' ' || !all->tab[i + 1]) && eg == 1)
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
	return (tabnewenv);
}

<<<<<<< HEAD
int		ft_export(t_all *all)
{
	unsigned int	i;
	char	**tabnewenv;
	char	**new_env;
	int		nb_newenv;
	int		j;

	ret = 0;
	if (!(nb_newenv = ft_nbnewenv(all)))
=======
char	*ft_strdupfree(char *src)
{
	int		i;
	char	*dest;

	i = 0;
	if (!(dest = (char *)malloc(ft_strlen(src) * sizeof(char) + 1)))
>>>>>>> dc46c8f941bb473443947ffe858cd529065dd630
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

	ret = 0;
	j = 0;
	if (!(nb_newenv = ft_nbnewenv(all, 0, 0, -1)))
		return (0);
	tabnewenv = ft_newenv(all, nb_newenv, j);
	if (!(new_env = malloc((all->nb_env + nb_newenv + 1) * sizeof(char*))))
		return (0);
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
	new_env[i + j] = '\0';
	free(all->tab);
	all->nb_env += nb_newenv;
	free(tabnewenv);
	free(all->env);
	all->env = new_env;
	return (0);
}
