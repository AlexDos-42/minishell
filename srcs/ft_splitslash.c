/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitslash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:58:29 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/08 17:58:30 by edouvier         ###   ########.fr       */
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

int		ischarset(const char *str, int is, char *c)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (c[++j])
		while (str[is] == c[j])
		{
			if (isguillemet(is, str))
				i = 1;
			if (i == 0 && is != 0 && str[is] == c[j] && str[is - 1] == '\\')
				while (is >= i && str[is - 1 - i] && str[is - 1 - i] == '\\')
					i++;
			return (i % 2 == 0 ? 1 : 0);
		}
	return (0);
}

static int			ft_taillem(const char *str, int i, char *charset)
{
	int		j;

	j = 0;
	while (!ischarset(str, i, charset) && str[i] != '\0')
	{
		i++;
		j++;
	}
	return (j);
}

static int			ft_nbr_mots(const char *str, char *charset)
{
	int		i;
	int		nbr_mots;

	i = 0;
	nbr_mots = 0;
	while (str[i])
	{
		while (ischarset(str, i, charset))
			i++;
		if (str[i])
			nbr_mots++;
		while (!ischarset(str, i, charset) && str[i] != '\0')
			i++;
	}
	return (nbr_mots);
}

char				**ft_splitslash(const char *str, char *c)
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
		while (ischarset(str, is, c) && str[is])
			is++;
		if (!(tab[i] = malloc(sizeof(char) * (ft_taillem(str, is, c) + 1))))
			return (ft_free(tab, i));
		while (str[is] && !ischarset(str, is, c))
			tab[i][j++] = str[is++];
		tab[i++][j] = '\0';
	}
	tab[i] = NULL;
	return (tab);
}
