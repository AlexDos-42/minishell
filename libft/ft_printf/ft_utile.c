/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:58:26 by alesanto          #+#    #+#             */
/*   Updated: 2019/12/17 16:43:12 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char		*ft_cdup(int d)
{
	char	*str;
	int		i;
	char	c;

	c = (char)d;
	i = 0;
	if (!c)
	{
		if (!(str = malloc(1 * sizeof(char))))
			return (NULL);
	}
	else
	{
		if (!(str = malloc((2) * sizeof(char))))
			return (NULL);
	}
	if (c)
		str[i++] = c;
	str[i] = '\0';
	return (str);
}

char		*ft_strjoin_c(char const *s1, char c)
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
	return (str);
}

char		*ft_ptoa_base(unsigned long long int nbr, char *base)
{
	char						*str;
	int							i;
	unsigned long long int		n;
	int							basesize;

	i = 0;
	basesize = ft_strlen(base);
	n = nbr;
	while ((n /= basesize) >= 1)
		i++;
	i += 1;
	if (!(str = (char *)ft_calloc(sizeof(char), (i + 1))))
		return (NULL);
	while (i--)
	{
		str[i] = base[nbr % basesize];
		nbr /= basesize;
	}
	return (str);
}

char		*ft_itoa_base(unsigned nbr, char *base)
{
	char						*str;
	int							i;
	unsigned long long int		n;
	int							basesize;

	i = 0;
	basesize = ft_strlen(base);
	n = nbr;
	while ((n /= basesize) >= 1)
		i++;
	i += 1;
	if (!(str = (char *)ft_calloc(sizeof(char), (i + 1))))
		return (NULL);
	while (i--)
	{
		str[i] = base[nbr % basesize];
		nbr /= basesize;
	}
	return (str);
}

void		ft_flagsapp0(t_parsing *parsing, char arg)
{
	char	*tmp;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (parsing->flagstiret > 0)
		k = parsing->neg;
	j = (parsing->flagstiret > 0) ? parsing->flagstiret : -parsing->flagstiret;
	if (parsing->flags0 > j)
		j = parsing->flags0;
	tmp = ft_calloc(sizeof(char), (j + 1 + k));
	if (!ft_strlen(parsing->aff) && arg == 'c')
		j--;
	if (k == 1)
		tmp[i++] = '-';
	while (j-- > ((!ft_strlen(parsing->aff) ? 0 : ft_strlen(parsing->aff))))
		tmp[i++] = '0';
	tmp[i] = '\0';
	tmp = ft_strjoin(tmp, (&parsing->aff[k]), 1);
	free(parsing->aff);
	parsing->aff = tmp;
}
