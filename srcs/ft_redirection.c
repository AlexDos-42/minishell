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

void		ft_open(t_all *all)
{
	if (all->fdin >= 0)
	{	
		all->fdoutc = dup(1);
		close(1);
		dup2(all->fdin, 1);
	}
	if (all->fdout >= 0)
	{	
		all->fdinc = dup(0);
		close(0);
		dup2(all->fdout, 0);
	}
}

void		ft_close(t_all *all)
{
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
}

char	*ft_create_file(t_all *all, char **tab, char **redir, int i)
{
	// ft_printf("tab %s\n", tab[i]);
	// ft_printf("tab %s\n", tab[i + 1]);
	if (redir[i][0] == '>' && redir[1] && redir[i][1] == '>')
	 	all->fdin = open(tab[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (redir[i][0] == '>')
		all->fdin = open(tab[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (redir[i][0] == '<')
		all->fdout = open(tab[i + 1], O_RDONLY);
	ft_open(all);
	if (redir[i][0] == '>')
		if (redir[i + 1])
			if (redir[++i][0] == '>')
			{
				ft_close(all);
				ft_create_file(all, tab, redir, i);
			}
	return (NULL);
}

char	**ft_allredir(char *tab)
{
	int 	i;
	int		j;
	int		k;
	char	**new;

	i = 0;
	j = 0;
	while(tab[i])
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
	while(tab[i])
	{
		if (tab[i] == '>' || tab[i] == '<')
		{
			k = 0;
			while (tab[i + k] && (tab[i + k] == '>' || tab[i + k] == '<'))
				k++;
			new[j++] = ft_substr(tab, i, k);
			i = i + k;
		}
		else
			i++;
	}
	new[j] = NULL;
	return (new);
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
		while(tab[i] && tab[i] != '<' && tab[i] != '>')
			i++;
		while(tab[i] && (tab[i] == '<' || tab[i] == '>'))
			i++;
	}
	ft_freexec(new);
	return (tmp);	
}

int			redirerror(char **tab, char** redir)
{
	int		i;
	char	*tmp;

	tmp = ft_strtrimslash(tab[1], " ");
	if (tmp && (!tmp[0] || tmp[0] == '\n'))
	{
		ft_printf("minishell: line 0: syntax error near unexpected token `newline'\n");
		ret = 2;
		free(tmp);
		return (0);
	}
	free(tmp);
	i = -1;
	while (redir[++i])
		if (redir[i][1] && (redir[i][1] == '<' || redir[i][2]))
		{
			ft_printf("minishell: line 0: syntax error near unexpected token `%c'\n", redir[i][0]);
			ret = 2;
			return (0);	
		}
	return (1);
}

char		*ft_redirection(char *tab, t_all *all)
{
	int		i;
	char	**redir;
	char	**new;
	char	*tmp;

	i = -1;
	redir = ft_allredir(tab);
	all->fdin = -5;
	all->fdout = -5;
	if (redir != NULL)
	{
		new = ft_splitslash(tab, "><");
		new = ft_realsplit(tab, new, redir);
		if (redirerror(new, redir))
		{
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
			ft_create_file(all, new, redir, i);
			
		}
		else
			tmp = ft_calloc(1,1);
		ft_freexec(redir);
		ft_freexec(new);
		return (tmp);
	}
	return (ft_strdup(tab));
}
