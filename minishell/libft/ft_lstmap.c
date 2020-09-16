/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:58:13 by alesanto          #+#    #+#             */
/*   Updated: 2019/11/10 11:24:39 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_lstclear1(t_list **lst, void (*del)(void *))
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

static t_list	*ft_lstnew1(void *content)
{
	t_list *new;

	if (!(new = malloc(sizeof(t_list))))
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*begin;
	t_list	*tmp;

	if (!lst)
		return (0);
	if (!(tmp = ft_lstnew1((*f)(lst->content))))
		return (0);
	begin = tmp;
	while (lst->next)
	{
		lst = lst->next;
		if (!(tmp->next = ft_lstnew1((*f)(lst->content))))
		{
			ft_lstclear1(&begin, del);
			return (0);
		}
		tmp = tmp->next;
	}
	return (begin);
}
