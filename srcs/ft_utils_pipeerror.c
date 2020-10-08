/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_pipeerror.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 16:01:31 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/24 16:01:33 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		istabpipe_next(char **new, int i)
{
	int			j;
	char		*tmp;

	tmp = "not a valid identifier";
	while (new[++i])
	{
		new[i] = ft_suprguy(new[i]);
		j = -1;
		if ((new[i][0] > 47 && new[i][0] < 58) || new[i][0] == '=')
		{
			if (g_pipe != 2)
				ft_printf("minishell: export: `%s': %s\n", new[i], tmp);
			g_quit = 1;
		}
		else
			while (new[i][++j] && new[i][j] != '=')
				if (new[i][j] < 48 || (new[i][j] > 58 && new[i][j] < 65) ||
				(new[i][j] > 90 && new[i][j] < 97) || new[i][j] > 122)
				{
					if (g_pipe != 2)
						ft_printf("minishell: export: `%s': %s\n", new[i], tmp);
					g_quit = 1;
					break ;
				}
	}
}

void		istabpipe_suite2(char **new, t_all *all, int i)
{
	if (!ft_strncmp(new[0], "export", 6) && !new[0][i + 6])
	{
		if (new[0])
			istabpipe_next(new, 0);
	}
	else
		istabpipe_suite3(new, all, i);
}

void		istabpipe_bis(char **new)
{
	new[1] = ft_suprguy(new[1]);
	if (new[2])
	{
		if (g_pipe != 2)
			ft_printf("mminishell: cd: too many arguments\n");
		g_quit = 1;
	}
	else if ((ft_strlen(new[1]) == 1 && (new[1][0] != '.' || new[1][0] != '~'))
	|| (ft_strlen(new[1]) == 2 && new[1][0] != '.' && new[1][1] != '.')
	|| chdir(new[1]) != 0)
	{
		if (g_pipe != 2)
			ft_printf("minishell: cd: `%s': No such file or directory\n",
			new[1]);
		g_quit = 1;
	}
}

void		istabpipe_suite(char **new, t_all *all, int i, char *tmp)
{
	if (!ft_strncmp(new[0], "env", 3) && !new[0][i + 3])
	{
		if (new[1])
		{
			new[1] = ft_suprguy(new[1]);
			if (g_pipe != 2 && (new[1][0] == '.' || new[1][0] == '/'))
				ft_printf("%s `%s': Permission non accordée\n", tmp, new[1]);
			else if (g_pipe != 2)
				ft_printf("%s `%s': No such file or directory\n", tmp, new[1]);
			g_quit = 1;
		}
	}
	else if (!ft_strncmp(new[0], "cd", 2) && (new[0][i + 2]))
	{
		if (new[1])
			istabpipe_bis(new);
		else
		{
			if (g_pipe != 2)
				ft_printf("minishell: cd: HOME not set\n");
			g_quit = 1;
		}
	}
	else
		istabpipe_suite2(new, all, i);
}

void		istabpipe(char *tab, t_all *all)
{
	int			i;
	char		*tmp;
	char		**new;

	i = 0;
	tmp = suprredir(ft_strtrimslash(tab, " "), 0, 0, ft_calloc(1, 1));
	new = ft_splitspace(tmp, ' ');
	free(tmp);
	new[0] = ft_suprguy(new[0]);
	if (((!ft_strncmp(new[0], "echo", 4) || !ft_strncmp(new[0], "exit", 4)) &&
	!new[0][4]) || (!ft_strncmp(new[0], "pwd", 3) && !new[0][i + 3]))
		;
	else
		istabpipe_suite(new, all, i, "minishell: env:");
	ft_freexec(new);
}
