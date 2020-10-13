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
	char *tmp;
	tmp = getcwd(NULL, 0);
	if (!tmp && errno == 2)
	{
		ft_printf("pwd : erreur de détermination du répertoire actuel : getcwd");
		ft_printf(" : ne peut accéder aux répertoires parents : ");
		ft_printf("Aucun fichier ou dossier de ce type\n");
		g_ret = 1;
	}
	else
	{
		ft_putstr_fd(all->pwd, 1);
		write(1, "\n", 1);
		g_ret = 0;
		free(tmp);
	}
	free(all->tab);
	return (g_ret);
}
