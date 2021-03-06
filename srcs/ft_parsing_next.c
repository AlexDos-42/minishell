/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_next.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 16:12:53 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/24 16:12:54 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_minishell_again(char **tab, t_all *all, int k, int stop)
{
	while (tab && tab[++k])
	{
		if ((tab[k] = ft_replace(tab[k], all, -1, -1)))
		{
			if (ft_ispipe(tab[k]))
				ft_pipe(tab[k], all);
			else if ((stop = ft_loop(tab[k], all)))
			{
				while (tab && tab[k])
					free(tab[k++]);
				break ;
			}
		}
		free(tab[k]);
	}
	return (stop);
}

void	print_err(char c, char *str, int i)
{
	int		j;

	j = 0;
	while (str[++i] && (str[i] == ' ' || str[i] == '\t' || str[i] == c))
		if (str[i] == c)
			j++;
	if (c == ';')
		ft_printf("minishell: syntax error near unexpected token `;;'\n");
	else if (c == '|')
		if (j <= 1)
			ft_printf("minishell: syntax error near unexpected token `|'\n");
		else
			ft_printf("minishell: syntax error near unexpected token `||'\n");
	else if (c == '>')
		if (j == 0)
			ft_printf("minishell: syntax error near unexpected token `>'\n");
		else
			ft_printf("minishell: syntax error near unexpected token `>>'\n");
	else if (c == '<')
	{
		if (j <= 2)
			ft_printf("minishell: syntax error near unexpected token `<'\n");
		else
			ft_printf("minishell: syntax error near unexpected token `<<'\n");
	}
}

int		ififmini(char *str, int i)
{
	if (str[i] == ';')
		ft_printf("minishell: syntax error near unexpected token `;'\n");
	else
		ft_printf("minishell: syntax error near unexpected token `|'\n");
	g_ret = 2;
	return (1);
}

int		ifminichek(char *str, int i, int j, char c)
{
	while (str[i])
	{
		if ((str[i] == ';' || str[i] == '|' || str[i] == '<'
		|| str[i] == '>') && !isguillemet(i, str))
		{
			c = str[i];
			j = i;
			if (c == '>' && str[i + 1] && str[i + 1] == '>')
				i++;
			i++;
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (c == '|' && (!str[i] || str[i] == ';' || str[i] == '\n'))
				return (ififmini(str, i));
			if (str[i] == c)
			{
				print_err(c, str, i);
				g_ret = 2;
				return (1);
			}
			i = j;
		}
		i++;
	}
	return (0);
}

int		ft_minishell(t_all *all, char *str, int stop, int k)
{
	char	**tab;

	if (g_inter == 1 && !(g_inter = 0))
		g_ret = 131;
	if (g_inter == 2 && !(g_inter = 0))
		g_ret = 130;
	while (str[++k] && (str[k] == ';' || str[k] == ' '))
		if (str[k] == ';')
		{
			if (str[k + 1] && str[k + 1] == ';')
				ft_printf(
					"minishell: syntax error near unexpected token `;;'\n");
			else
				ft_printf(
					"minishell: syntax error near unexpected token `;'\n");
			g_ret = 1;
			return (stop);
		}
	if (ifminichek(str, 0, 0, 0))
		return (stop);
	tab = ft_splitslash(str, ";");
	stop = ft_minishell_again(tab, all, -1, stop);
	if (tab)
		free(tab);
	return (stop);
}
