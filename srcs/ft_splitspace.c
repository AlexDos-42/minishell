/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitspace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 16:41:05 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/16 16:41:07 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char			**ft_free(char **tab, int i)
{
	while (--i)
	{
		free(tab[i]);
		tab[i] = 0;
	}
	free(tab);
	tab = 0;
	return (NULL);
}

int					ischarsetspace(const char *str, int is, char c)
{
	int i;

	i = 0;
	if (is > 0 && (str[is] == c || str[is] == '\t') && str[is - 1] == '\\')
		while (is > i && str[is - 1 - i] == '\\')
			i++;
	if ((str[is] == c || str[is] == '\t') && !isguillemet(is, str) && i % 2 == 0)
		return (1);
	return (0);
}

static int			ft_taillem(const char *str, int i, char charset)
{
	int		j;

	j = 0;
	while (!ischarsetspace(str, i, charset) && str[i] != '\0')
	{
		i++;
		j++;
	}
	return (j);
}

static int			ft_nbr_mots(const char *str, char charset)
{
	int		i;
	int		nbr_mots;

	i = 0;
	nbr_mots = 0;
	while (str[i])
	{
		while (str[i] && ischarsetspace(str, i, charset))
			i++;
		if (str[i])
			nbr_mots++;
		while (str[i] && !ischarsetspace(str, i, charset) && str[i] != '\0')
			i++;
	}
	return (nbr_mots);
}

char				**ft_splitspace(const char *str, char c)
{
	int			is;
	int			i;
	int			j;
	char		**tab;

	if (!str)
		return (NULL);
	is = 0;
	if (!(tab = malloc(sizeof(char*) * (ft_nbr_mots(str, c) + 1))))
		return (0);
	i = 0;
	while (i < ft_nbr_mots(str, c))
	{
		j = 0;
		while ((str[is] == c || str[is] == '\t') && str[is])
			is++;
		if (!(tab[i] = malloc(sizeof(char) * (ft_taillem(str, is, c) + 1))))
			return (ft_free(tab, i));
		while (str[is] && !ischarsetspace(str, is, c))
			tab[i][j++] = str[is++];
		tab[i++][j] = '\0';
	}
	tab[i] = NULL;
	return (tab);
}
