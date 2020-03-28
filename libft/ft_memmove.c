/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:56:15 by alesanto          #+#    #+#             */
/*   Updated: 2019/11/06 13:58:37 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	if (src < dst && src + n > dst)
	{
		while (n > 0)
		{
			n--;
			((char*)dst)[n] = ((char*)src)[n];
		}
		return (dst + n);
	}
	return (ft_memcpy(dst, src, n));
}
