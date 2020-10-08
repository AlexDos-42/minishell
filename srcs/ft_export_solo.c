#include "../include/minishell.h"

char		*beta_exp(t_all *all, char *new, int i)
{
	int			k;
	int			l;
	char		*tmp;

	while (!(l = 0) &&all->ext[++i])
	{
		k = 0;
		if (!new[l + k])
		{
			new = ft_strjoin(new, all->ext[i], 1);
			new = ft_strjoin(new, "\n", 1);
			break ;
		}
		while (new[l + k])
		{
			if (new[l + k] == '\n')
			{
            	l = l + 1 + k;
                k = 0;
            }
			if (new[l + k] && new[l + k] == all->ext[i][k])
				k++;
			else if (new[l + k] && new[l + k] < all->ext[i][k])
			{
				while (new[l + k] != '\n')
					k++;
				l = l + k;
				k = 0;
			}
			else if (new[l + k])
			{
				tmp = ft_strjoin(ft_substr(new, 0, l), all->ext[i], 1);
				tmp = ft_strjoin(tmp, "\n", 1);
				tmp = ft_strjoin(tmp, ft_substr(new, l, ft_strlen(&new[l])), 3);
				free(new);
				new = tmp;
				break ;
			}
			if (!new[l + k])
			{
				new = ft_strjoin(new, all->ext[i], 1);
				new = ft_strjoin(new, "\n", 1);
				break ;
			}
		}
	}
	return (new);
}

char		*alpha_beta(t_all *all, char *new, int i)
{
	int			k;
	int			l;
	char		*tmp;

	while (!(l = 0) && all->env[++i])
	{
		k = 0;
		while (new[l + k])
		{
			if (new[l + k] == '\n')
			{
            	l = l + 1 + k;
                k = 0;
            }
			if (new[l + k] == all->env[i][k])
				k++;
			else if (new[l + k] && new[l + k] < all->env[i][k])
			{
				while (new[l + k] != '\n')
					k++;
				l = l + k;
				k = 0;
			}
			else if (new[l + k])
			{
				tmp = ft_strjoin(ft_substr(new, 0, l), all->env[i], 1);
				tmp = ft_strjoin(tmp, "\n", 1);
				tmp = ft_strjoin(tmp, ft_substr(new, l, ft_strlen(&new[l])), 3);
				free(new);
				new = tmp;
				break ;
			}
			if (!new[l + k])
			{
				new = ft_strjoin(new, all->env[i], 1);
				new = ft_strjoin(new, "\n", 1);
				break ;
			}
		}
	}
	return (new);
}

void		export_solo(t_all *all, int i, int eg, char *tmp)
{
	if (all->nb_env)
	{
		tmp = ft_strjoin(ft_strdup(all->env[0]), "\n", 1);
		tmp = alpha_beta(all, tmp, 0);
	}
	else
		tmp = ft_calloc(1, 1);
	if (all->nb_ext > 0)
		tmp = beta_exp(all, tmp, -1);
	while (tmp[++i])
	{
		if (i == 0)
			ft_printf("export ");
		if (tmp[i] == '\n' && tmp[i + 1] && eg == 1 && !(eg = 0))
			ft_printf("\"\nexport ");
		else if (tmp[i] == '\n' && tmp[i + 1])
			ft_printf("\nexport ");
		else if (tmp[i] == '\n' && !tmp[i + 1] && eg == 1 && !(eg = 0))
			ft_printf("\"\n");
		else if (tmp[i] == '=' && (eg = 1))
			write(1, "=\"", 2);
		else
			write(1, &tmp[i], 1);
	}
	free(tmp);
}
