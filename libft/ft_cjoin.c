/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 17:00:30 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/29 22:47:22 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_cjoin(char const *s1, char c, int f)
{
	int		i;
	char	*str;

	i = 0;
	if (!c)
		return (NULL);
	if (!(str = malloc(sizeof(char) * (ft_strlen(s1) + 2))))
		return (NULL);
	while (s1 && *s1)
	{
		str[i] = *s1++;
		i++;
	}
	str[i++] = c;
	str[i] = '\0';
	if ((f == 1) && s1)
		free((char*)s1);
	return (str);
}
