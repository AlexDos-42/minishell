/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:18:24 by alesanto          #+#    #+#             */
/*   Updated: 2019/11/07 16:29:51 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check(const char c, const char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			i++;
		else
			return (1);
	}
	return (0);
}

char			*ft_strtrim(char const *str, char const *set)
{
	int		i;
	int		j;
	char	*s;

	if (!str || !set)
		return (0);
	i = 0;
	j = ft_strlen(str) - 1;
	while (check(str[i], set) == 1)
		i++;
	if (i == (j + 1))
		return (ft_calloc(1, sizeof(char)));
	while (check(str[j], set) == 1)
	{
		if (j == 0)
			return (NULL);
		j--;
	}
	s = ft_substr(str, i, j - i + 1);
	return (s);
}
