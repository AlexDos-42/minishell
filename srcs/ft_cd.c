/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <alesanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 09:58:32 by alesanto          #+#    #+#             */
/*   Updated: 2020/04/10 09:58:57 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cd(t_all *all)
{
	char	*tmp;

	tmp = ft_strtrim(all->tab, " ");
	free(all->tab);
	all->tab = tmp;
	if (!all->tab[0] || (all->tab[0] == '~' && !all->tab[1]))
	{
		chdir("/home/alesanto");
		free(all->pwd);
		all->pwd = getcwd(NULL, 0);
	}
	else if (chdir(all->tab) == 0)
	{
		free(all->pwd);
		all->pwd = getcwd(NULL, 0);
	}
	else
		ft_printf("cd: %s: %s\n", strerror(errno), all->tab);
	free(all->tab);
	return (ret = 0);
}
