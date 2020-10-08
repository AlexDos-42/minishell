/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:56:34 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/08 17:56:37 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	write_env(t_all *all)
{
	int i;

	i = -1;
	while (++i < (int)all->nb_env)
	{
		ft_putstr_fd(all->env[i], 1);
		write(1, "\n", 1);
	}
	g_ret = 0;
}

int		ft_env(t_all *all)
{
	char			*tmp;
	char			**new;

	tmp = ft_strtrim(all->tab, " ");
	if (tmp[0])
	{
		new = ft_splitspace(tmp, ' ');
		new[0] = ft_suprguy(new[0]);
		if ((g_ret = 126) && (new[0][0] == '.' || new[0][0] == '/'))
			ft_printf("env: «%s»: Permission non accordée\n", new[0]);
		else if ((g_ret = 127))
			ft_printf("env: «%s»: Aucun fichier ou dossier de ce type\n",
			new[0]);
		ft_freexec(new);
	}
	else
		write_env(all);
	free(tmp);
	free(all->tab);
	return (0);
}

char	*suprredir(char *tab, int i, int j, char *tmp)
{
	while (tab[i])
	{
		while (tab[i] == ' ')
			i++;
		if (tab[i] == '>' || tab[i] == '<')
		{
			i += tab[i + 1] == '>' ? 2 : 1;
			while (tab[i] == ' ')
				i++;
			while (tab[i] && tab[i] != ' ')
				i++;
		}
		else if (!(j = 0) && (tab[i]))
		{
			while (tab[i + j] && tab[i + j] != '<'
			&& tab[i + j] != '>' && tab[i + j] != '\n')
				j++;
			if (tmp[0])
				tmp = ft_strjoin(tmp, " ", 1);
			tmp = ft_strjoin(tmp, ft_substr(tab, i, j), 3);
			i += j;
		}
	}
	free(tab);
	return (tmp);
}
