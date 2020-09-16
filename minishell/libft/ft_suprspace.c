/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_suprspace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:55:02 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/29 22:50:41 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_suprspace(char *str)
{
	int		i;
	char	*tmp;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] != ' ')
			i++;
		j++;
	}
	if (!(tmp = ft_calloc(i, sizeof(char))))
		return (NULL);
	j = 0;
	k = -1;
	while (str[++k] && j <= k)
	{
		if (str[k] != ' ')
			tmp[j++] = str[k];
	}
	tmp[j] = '\0';
	free(str);
	return (tmp);
}
