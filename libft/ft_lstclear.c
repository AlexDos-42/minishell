/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:55:02 by alesanto          #+#    #+#             */
/*   Updated: 2019/11/07 18:05:03 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *tmp;
	t_list *pmt;

	pmt = *lst;
	while (pmt != NULL)
	{
		tmp = pmt->next;
		del(pmt->content);
		free(pmt);
		pmt = tmp;
	}
	*lst = NULL;
}
