/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <edouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:59:03 by edouvier          #+#    #+#             */
/*   Updated: 2020/09/08 17:59:04 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		ft_open(t_all *all, int j)
{
	if (all->fdin >= 0 && j == 1)
	{
		all->fdoutc = dup(1);
		close(1);
		dup2(all->fdin, 1);
	}
	if (all->fdout >= 0 && j == 2)
	{
		all->fdinc = dup(0);
		close(0);
		dup2(all->fdout, 0);
	}
}

void		ft_close(t_all *all, int i)
{
	if (all->fdin >= 0 && i == 1)
	{
		dup2(all->fdoutc, 1);
		close(all->fdoutc);
		all->fdin = -5;
	}
	if (all->fdout >= 0 && i == 2)
	{
		dup2(all->fdinc, 0);
		close(all->fdinc);
		all->fdout = -5;
	}
}

void	ft_create_file(t_all *all, char **tab, char **redir, int i)
{
	int		j;

	j = 0;
	if (redir[i][0] == '>' && redir[i][1] && redir[i][1] == '>' && (j = 1))
		all->fdin = open(tab[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (redir[i][0] == '>' && (j = 1))
		all->fdin = open(tab[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (redir[i][0] == '<' && (j = 2))
		all->fdout = open(tab[i + 1], O_RDONLY);
	ft_open(all, j);
	if (redir[i][0] == '>')
		if (redir[i + 1])
		{
			j = 0;
			while (redir[i + ++j])
				if (redir[i + j][0] == '>')
				{
					ft_close(all, 1);
					ft_create_file(all, tab, redir, i + j);
					break;
				}
		}
	if (redir[i][0] == '<')
		if (redir[i + 1])
		{
			j = 0;
			while (redir[i + ++j])
				if (redir[i + j][0] == '<')
				{
					ft_close(all, 2);
					ft_create_file(all, tab, redir, i + j);
					break;
				}
		}
}

char	**ft_allredir(char *tab)
{
	int		i;
	int		j;
	int		k;
	int		l;
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
	j = 0;
	i = 0;
	while (tab[i])
	{
		if (tab[i] == '>' || tab[i] == '<')
		{
			l = 0;
			k = 0;
			while (tab[i + k] && (tab[i + k] == '>' || tab[i + k] == '<'))
				k++;
			while (tab[i + k + l] && tab[i + k + l] == ' ')
				l++;
			if (tab[i + k + l] == '>' || tab[i + k + l] == '<')
				k += l + 1;
			new[j++] = ft_substr(tab, i, k);
			i = i + k;
			while (tab[i] && (tab[i] == ' ' || tab[i] == '>' || tab[i] == '<'))
				i++;
		}
		else
			i++;
	}
	new[j] = NULL;
	return (new);
}

char		**ft_addarg(char **tmp)
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

char		**ft_realsplit(char *tab, char **new, char **redir)
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

int			redirerror(char **tab, char **redir)
{
	int		i;
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
	i = -1;
	while (redir[++i])
		if (redir[i][1] && ((redir[i][0] == '<' && redir[i][1]) || redir[i][1] == '<' || redir[i][2]))
		{
			if (redir[i][0] && redir[i][1] && redir[i][2] && redir[i][3])
				ft_printf("minishell: syntax error near unexpected token `%c%c'\n", redir[i][0], redir[i][0]);
			else
				ft_printf("minishell: syntax error near unexpected token `%c'\n", redir[i][0]);
			g_ret = 2;
			return (0);	
		}
	return (1);
}

char		*ft_join(char **redir, char *tmp, char **new, t_all *all)
{
	int i;
	struct stat		stats;

	i = 0;
	while (redir[i])
		i++;
	while (redir[i] && redir[i][0] != '<')
		i--;
	if (new[i] && stat(new[i], &stats) == -1)
	{
		ft_printf("minishell: %s: %s\n", new[i], strerror(errno));
		if (all->fdout >= 0)
		{
			dup2(all->fdinc, 0);
			close(all->fdinc);
		}
		free(tmp);
		g_ret = 1;
		tmp = ft_calloc(1,1);
	}
	return (tmp);
	
}

int			redirspace(char **redir)
{
	int		i;
	int		j;

	i = -1;
	while (redir[++i])
	{
		j = -1;
		while (redir[i][++j])
		{
			if (redir[i][j] == ' ')
			{
				if (redir[i][0] && redir[i][1]&& redir[i][2] && redir[i][3])
					ft_printf("minishell: syntax error near unexpected token `%c%c'\n", redir[i][0], redir[i][0]);
				else
					ft_printf("minishell: syntax error near unexpected token `%c'\n", redir[i][0]);
				g_ret = 2;
				return(0);
			}
		}
	}
	return (1);
}

char		*ft_redirection(char *tab, t_all *all)
{
	int		i;
	char	**redir;
	char	**new;
	char	*tmp;

	i = 0;
	redir = ft_allredir(tab);
	all->fdin = -5;
	all->fdout = -5;
	if (redir != NULL && !redirspace(redir))
	{
		ft_freexec(redir);
		redir = NULL;
		tab = ft_strdup("");
	}
	else if (redir != NULL)
	{
		new = ft_splitslash(tab, "><");
		new = ft_realsplit(tab, new, redir);
		if (redirerror(new, redir))
		{
			ft_addarg(new);
			while (new[++i])
			{
				tmp = ft_strtrimslash(new[i], " ");
				free(new[i]);
				tmp = ft_suprguy(tmp);
				if (tmp[0] && tmp[ft_strlen(tmp) - 1] == '\n')	
					new[i] = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
				else
					new[i] = ft_strdup(tmp);
				free(tmp);
			}
			i = 0;
			tmp = new[0] ? ft_strdup(new[0]) : ft_calloc(1, 1);
			i = 0;
			while(redir[i] && redir[i][0] != '>')
				i++;
			if (redir[i] && redir[i][0] == '>')
				ft_create_file(all, new, redir, i);
			i = 0;
			while(redir[i] && redir[i][0] != '<')
				i++;
			if (redir[i] && redir[i][0] == '<')
				ft_create_file(all, new, redir, i);
			tmp = ft_join(redir, tmp, new, all);
		}
		else
			tmp = ft_calloc(1,1);
		ft_freexec(redir);
		ft_freexec(new);
		return (tmp);
	}
	else
		tab = ft_strdup(tab);
	return (tab);
}
