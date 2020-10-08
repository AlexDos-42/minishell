/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 18:08:14 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/08 18:08:16 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_pwd(t_all *all)
{
	ft_putstr_fd(all->pwd, 1);
	write(1, "\n", 1);
	g_ret = 0;
	free(all->tab);
	return (g_ret);
}
