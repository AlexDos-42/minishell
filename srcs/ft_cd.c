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

void			ft_remplaceold(t_all *all, char *tmp)
{
	int			i;

	i = 0;
	while (all->env[i] && ft_strncmp(all->env[i], "OLDPWD=", 7))
		i++;
	if (tmp && all->env[i] && !ft_strncmp(all->env[i], "OLDPWD=", 7))
	{
		free(all->env[i]);
		all->env[i] = ft_strdup(tmp + 4);
		all->env[i] = ft_strjoin("OLDPWD=", all->env[i], 2);
		free(tmp);
	}
	else if (tmp)
		free(tmp);
}

static void		ft_remplace(t_all *all, int i, char *tmp)
{
	char		**newenv;

	while (all->env[i] && ft_strncmp(all->env[i], "PWD=", 4))
		i++;
	if (all->env[i] && !ft_strncmp(all->env[i], "PWD=", 4)
	&& !(all->pwd[0] == '.' && all->pwd[1] == '.'))
	{
		tmp = ft_strdup(all->env[i]);
		free(all->env[i]);
		all->env[i] = ft_strdup(all->pwd);
		all->env[i] = ft_strjoin("PWD=", all->env[i], 2);
		ft_remplaceold(all, tmp);
	}
	else if ((i = -1) == -1 && !(all->pwd[0] == '.' && all->pwd[1] == '.'))
	{
		newenv = ft_calloc(all->nb_env + 2, sizeof(char*));
		while (all->env[++i])
			newenv[i] = ft_strdup(all->env[i]);
		newenv[i] = ft_strdup(all->pwd);
		newenv[i] = ft_strjoin("PWD=", newenv[i], 2);
		newenv[++i] = NULL;
		ft_freexec(all->env);
		all->env = newenv;
		all->nb_env++;
	}
}

void			cd_tiret(t_all *all)
{
	int i;

	i = 0;
	while (all->env[i] && ft_strncmp(all->env[i], "OLDPWD=", 7))
		i++;
	if (all->env[i])
	{
		if (chdir(&all->env[i][7]) == 0)
		{
			ft_printf("%s\n", &all->env[i][7]);
			free(all->pwd);
			all->pwd = getcwd(NULL, 0);
			g_ret = 0;
		}
		else
			ft_printf("minishell: cd: %s: %s\n", &all->env[i][7],
			strerror(errno));
	}
	else
	{
		ft_printf("minishell: cd: `OLDPWD' non défini\n");
		g_ret = 1;
	}
}

void			ft_cd_bis(t_all *all, char **new)
{
	if (new && new[0] && new[1])
		ft_printf("minishell: cd: too many arguments\n");
	else if (!new[0])
	{
		chdir("/home/user42");
		free(all->pwd);
		all->pwd = getcwd(NULL, 0);
		g_ret = 0;
	}
	else if (new[0][0] == '-' && !new[0][1])
		cd_tiret(all);
	else if (chdir(new[0]) == 0)
	{
		free(all->pwd);
		all->pwd = getcwd(NULL, 0);
		if (!all->pwd && errno == 2)
		{
			ft_printf("minishell: cd: %s\n", strerror(errno));
			all->pwd = ft_strdup("..");
			return ;
		}
		g_ret = 0;
	}
	else
		ft_printf("minishell: cd: %s: %s\n", new[0], strerror(errno));
}

int				ft_cd(t_all *all)
{
	char	*tmp;
	char	**new;

	tmp = ft_strtrimslash(all->tab, " ");
	new = ft_splitspace(tmp, ' ');
	if (new[0] && new[0][0] == '~' && !new[0][1])
	{
		free(new[0]);
		new[0] = ft_strdup("/home/user42");
	}
	if (new[0])
		new[0] = ft_suprguy(new[0]);
	free(all->tab);
	free(tmp);
	g_ret = 1;
	ft_cd_bis(all, new);
	ft_freexec(new);
	ft_remplace(all, 0, NULL);
	return (0);
}
