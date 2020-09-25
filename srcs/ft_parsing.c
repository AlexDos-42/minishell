/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 16:42:20 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/16 16:42:21 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_fonc(int i, t_all *all)
{
	int		(*fonc[8])(t_all *);

	fonc[1] = ft_echo;
	fonc[2] = ft_pwd;
	fonc[3] = ft_cd;
	fonc[4] = ft_exit;
	fonc[5] = ft_env;
	fonc[6] = ft_export;
	fonc[7] = ft_unset;
	i = fonc[all->fct](all);
	return (i);
}

int		ft_ptrfct(t_all *all)
{
	int		i;

	i = 0;
	if (all->fct != 0)
	{
		i = ft_fonc(i, all);
		all->fct = 0;
	}
	else
		free(all->tab);
	if (all->fdin >= 0)
	{
		dup2(all->fdoutc, 1);
		close(all->fdoutc);
	}
	if (all->fdout >= 0)
	{
		dup2(all->fdinc, 0);
		close(all->fdinc);
	}
	return (i);
}

int		ft_realbuiltin(char *tab, char *str, int i)
{
	int		j;
	char	*new;

	j = 0;
	new = ft_splitbuiltin(tab, ' ');
	new = ft_suprguy(new);
	if (!ft_strncmp(new, str, i) && (!new[ft_strlen(str)] ||
	new[ft_strlen(str)] == '\n'))
		j = 1;
	free(new);
	return (j);
}

void	ft_nbfct(t_all *all, char *tab)
{
	int		i;

	i = 0;
	while (tab[i] && tab[i] != ' ' && tab[i] != '\n')
		i++;
	if (ft_realbuiltin(tab, "echo", 4))
		all->fct = 1;
	else if (ft_realbuiltin(tab, "pwd", 3))
		all->fct = 2;
	else if (ft_realbuiltin(tab, "cd", 2))
		all->fct = 3;
	else if (ft_realbuiltin(tab, "exit", 4))
		all->fct = 4;
	else if (ft_realbuiltin(tab, "env", 3))
		all->fct = 5;
	else if (ft_realbuiltin(tab, "export", 6))
		all->fct = 6;
	else if (ft_realbuiltin(tab, "unset", 5))
		all->fct = 7;
	else
		ft_exec(all, tab);
	while (tab[i] == ' ')
		i++;
	all->tab = ft_substr(tab, i, ft_strlen(&tab[i]));
}

int		ft_loop(char *tab, t_all *all)
{
	int		i;
	char	*new;

	i = 0;
	new = ft_redirection(tab, all);
	while (new && new[i] == ' ')
		i++;
	ft_nbfct(all, &new[i]);
	free(new);
	if (ft_strlen(all->tab) && all->tab[ft_strlen(all->tab) - 1] == '\n')
		all->tab[ft_strlen(all->tab) - 1] = '\0';
	return (ft_ptrfct(all));
}
