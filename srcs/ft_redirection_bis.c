/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 19:47:29 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/24 19:47:32 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_allredir(char *tab)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	while (tab[i])
	{
		if (tab[i] == '>' || tab[i] == '<')
		{
			while (tab[i] && (tab[i] == '>' || tab[i] == '<'))
				i++;
			j++;
		}
		else
			i++;
	}
	if (j == 0)
		return (NULL);
	new = ft_calloc(j + 1, sizeof(char *));
	return (ft_all_redir_bis(tab, new, 0, 0));
}

char	**ft_addarg(char **tmp)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	while (tmp[++i])
	{
		new = ft_splitspace(tmp[i], ' ');
		if (new[1])
		{
			j = 0;
			while (new[++j])
			{
				tmp[0] = ft_strjoin(tmp[0], " ", 1);
				tmp[0] = ft_strjoin(tmp[0], new[j], 1);
			}
			free(tmp[i]);
			tmp[i] = ft_strdup(new[0]);
		}
		ft_freexec(new);
	}
	return (tmp);
}

char	**ft_realsplit(char *tab, char **new, char **redir)
{
	char	**tmp;
	int		i;
	int		j;
	int		k;

	k = 0;
	j = 0;
	i = 0;
	while (redir[i])
		i++;
	tmp = ft_calloc(sizeof(char*), i + 2);
	i = 0;
	while (tab[i])
	{
		if (tab[i] && tab[i] != '<' && tab[i] != '>' && tab[i] != '\n')
			tmp[j++] = ft_strdup(new[k++]);
		else
			tmp[j++] = ft_calloc(1, 1);
		while (tab[i] && tab[i] != '<' && tab[i] != '>')
			i++;
		while (tab[i] && (tab[i] == '<' || tab[i] == '>'))
			i++;
	}
	ft_freexec(new);
	return (tmp);
}

int		redirerror_bis(char **redir)
{
	int		i;

	i = -1;
	while (redir[++i])
		if (redir[i][1] && ((redir[i][0] == '<' && redir[i][1])
		|| redir[i][1] == '<' || redir[i][2]))
		{
			if (redir[i][0] && redir[i][1] && redir[i][2] && redir[i][3])
			{
				ft_printf("minishell: syntax error near unexpected token");
				ft_printf("`%c%c'\n", redir[i][0], redir[i][0]);
			}
			else
			{
				ft_printf("minishell: syntax error near unexpected token");
				ft_printf("`%c'\n", redir[i][0]);
			}
			g_ret = 2;
			return (0);
		}
	return (1);
}

int		redirerror(char **tab, char **redir)
{
	char	*tmp;

	tmp = ft_strtrimslash(tab[1], " ");
	if (tmp && (!tmp[0] || tmp[0] == '\n'))
	{
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
		g_ret = 2;
		free(tmp);
		return (0);
	}
	free(tmp);
	return (redirerror_bis(redir));
}
