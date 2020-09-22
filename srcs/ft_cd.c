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

static void	ft_remplace(t_all *all)
{
	int		i;

	i = 0;
	while(all->env[i] && ft_strncmp(all->env[i], "PWD=", 4))
		i++;
	if (all->env[i] && !ft_strncmp(all->env[i], "PWD=", 4))
	{
		free(all->env[i]);
		all->env[i] = ft_strdup(all->pwd);
		all->env[i] = ft_strjoin("PWD=", all->env[i], 2);
	}
}

int	ft_cd(t_all *all)
{
	char	*tmp;
	char	**new;

	tmp = ft_strtrimslash(all->tab, " ");
	new = ft_splitspace(tmp, ' ');
	if (new[0])
		new[0] = ft_suprguy(new[0]);
	free(all->tab);
	free(tmp);
	ret = 1;
	if (!new[0])
		ft_printf("minishell: cd: HOME not set\n");
	else if (new[1])
		ft_printf("minishell: cd: too many arguments\n");
	else if (!new[0][0] || (new[0][0] == '~' && !new[0][1]))
	{
		chdir("/home/alesanto");
		free(all->pwd);
		all->pwd = getcwd(NULL, 0);
		ft_remplace(all);
		ret = 0;
	}
	else if (chdir(new[0]) == 0)
	{
		free(all->pwd);
		all->pwd = getcwd(NULL, 0);
		ft_remplace(all);
		ret = 0;
	}
	else
		ft_printf("minishell: cd: %s: %s\n", new[0], strerror(errno));
	ft_freexec(new);
	return (0);
}
