/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:44:13 by alesanto          #+#    #+#             */
/*   Updated: 2019/11/10 10:37:06 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		nb_len(int nb)
{
	int count;

	count = 0;
	while (nb)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

char			*ft_itoa(int n)
{
	int		i;
	int		signe;
	char	*dest;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	signe = (n < 0 ? 1 : 0);
	i = nb_len(n) + signe;
	if (!(dest = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	n = signe ? -n : n;
	dest[i] = '\0';
	while (n)
	{
		dest[--i] = n % 10 + '0';
		n = n / 10;
	}
	signe ?	dest[--i] = '-' : 0;
	return (dest);
}
