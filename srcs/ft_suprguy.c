/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_suprguy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 16:28:15 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/24 16:28:17 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_suprguysuite(char *tab, int i)
{
	char	*tmp;
	int		j;

	j = 0;
	tmp = ft_calloc(i, sizeof(char) + 1);
	i = 0;
	while (tab[i])
	{
		if (tab[i] == '\\' && (tab[i + 1] && tab[i + 1] == '\\'
		&& (isguillemet(i, tab) == 1 || !isguillemet(j, tab))))
			tmp[j++] = tab[i++];
		else if (tab[i] == '\\' && ((isguillemet(i, tab) == 2)
			|| (isguillemet(i, tab) == 1 &&
			(tab[i + 1] != '\"' && tab[i + 1] != '$'))))
			tmp[j++] = tab[i];
		else if (((tab[i] != '\"' && tab[i] != '\'') ||
			isguillemet(i, tab)) && tab[i] != '\\')
			tmp[j++] = tab[i];
		i++;
	}
	tmp[j] = '\0';
	free(tab);
	return (tmp);
}

char	*ft_suprguy(char *tab)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tab[j])
	{
		if (((tab[j] != '\"' && tab[j] != '\'') ||
		isguillemet(j, tab)) && tab[j] != '\\')
			i++;
		else if (tab[j] == '\\' && (tab[j + 1] &&
		tab[j + 1] == '\\') && (isguillemet(j, tab) == 1
		|| !isguillemet(j, tab)))
		{
			i++;
			j++;
		}
		else if (tab[j] == '\\' && (isguillemet(j, tab) == 2
		|| (isguillemet(j, tab) == 1 &&
			(tab[j + 1] != '\"' && tab[j + 1] != '$'))))
			i++;
		j++;
	}
	return (ft_suprguysuite(tab, i));
}
