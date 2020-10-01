/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_pipeerror.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 16:01:31 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/24 16:01:33 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		istabpipe_next(char *tmp, int i, int j, char *tab)
{
	tmp = ft_substr(tab, i + 7, j);
	ft_printf("minishell: unset: « %s »");
	ft_printf("%s: identifiant non valable\n", tmp);
	free(tmp);
}

void		istabpipe_suite2(char *tab, t_all *all, int i)
{
	int			j;
	int			k;
	char		*tmp;

	tmp = 0;
	if (!ft_strncmp(&tab[i], "export ", 7))
	{
		while (tab[i + 7])
		{
			k = 0;
			j = 0;
			while (tab[i + 7] == ' ')
				i++;
			if (tab[i + 7] == '=')
				k = 1;
			while (tab[i + 7 + j] && tab[i + 7 + j] != ' ')
				j++;
			if (k == 1)
				istabpipe_next(tmp, i, j, tab);
			i += j;
		}
	}
	else
		istabpipe_suite3(tab, all, i);
}

void		istabpipe_bis(char *tmp, int i, int j, char *tab)
{
	tmp = ft_substr(tab, i + 3, j);
	if ((ft_strlen(tmp) == 1 && (tmp[0] != '.' || tmp[0] != '~')) ||
	(ft_strlen(tmp) == 2 && tmp[0] != '.' && tmp[1] != '.')
	|| chdir(tmp) != 0)
		ft_printf("cd: %s: %s\n", strerror(errno), tmp);
	free(tmp);
}

void		istabpipe_suite(char *tab, t_all *all, int i)
{
	int			j;
	char		*tmp;
	int			k;

	tmp = 0;
	if (!ft_strncmp(&tab[i], "cd ", 3))
	{
		j = 0;
		k = 0;
		while (tab[i + 3] == ' ')
			i++;
		while (tab[i + 3 + j + k])
		{
			j += k;
			k = 0;
			j++;
			while (tab[i + 3 + j + k] == ' ')
				k++;
		}
		if (j)
			istabpipe_bis(tmp, i, j, tab);
	}
	else
		istabpipe_suite2(tab, all, i);
}

void		istabpipe(char *tab, t_all *all)
{
	int			i;

	i = 0;
	while (tab[i] == ' ')
		i++;
	if (!ft_strncmp(&tab[i], "echo ", 5) || (!ft_strncmp(&tab[i], "exit", 4)))
		;
	else if (!ft_strncmp(&tab[i], "pwd ", 4))
	{
		while (tab[i + 4] == ' ')
			i++;
		if (tab[i + 4])
			ft_printf("pwd: too many arguments\n");
	}
	else if (!ft_strncmp(&tab[i], "env ", 4))
	{
		while (tab[i + 4] == ' ')
			i++;
		if (tab[i + 4])
			ft_printf("env: %s: Aucun fichier ou dossier de ce type\n", tab);
	}
	else
		istabpipe_suite(tab, all, i);
}
