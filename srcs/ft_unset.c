# include "../include/minishell.h"

int iserror;
char *messerror;

void	ft_error(t_all *all, int j)
{	

	int i;
	int k;

	k = 0;
	i = 0;
	while(all->tab[j + i] != '=')
		i++;
	if (!all->tab[j + i + 1] || all->tab[j + i + 1] == ' ')
	{
		if (iserror == 0)
		{
			iserror = 1;
			messerror = ft_substr(all->tab, j, i + 1);
			messerror = ft_strjoin("unset: ", messerror, 2);
			messerror = ft_strjoin(messerror, ": invalid parameter name\n", 1);
		}
	}
	else if (iserror != 2)
	{
		if (iserror == 1)
			free(messerror);
		iserror = 2;
		while (all->tab[j + k] && all->tab[j + k + 1] != ' ')
			k++;
		messerror = ft_substr(all->tab, j + 1, k);
		messerror = ft_strjoin("zsh: ", messerror, 2);
		messerror = ft_strjoin(messerror, " not found\n", 1);

	}	
}

void	ft_suprenv(t_all *all, int j)
{
	unsigned int p;
	int o;
	unsigned int i;
	unsigned int k;
	char **new_tab;

	p = 0;
	while(all->env[p] && p < all->nb_env -1)
	{	
		o = 0;
		while(all->env[p][o] && (all->env[p][o] == all->tab[j + o]))
		{
			if(all->env[p][o + 1] == '=')
			{
				i = 0;
				k = 0;
				new_tab = ft_calloc(sizeof(char*), all->nb_env--);
				while(k < all->nb_env)
				{
					if (i != p)
						new_tab[k++] = ft_strdup(all->env[i]);
					free(all->env[i]);
					i++;
				}
				free(all->env);
				all->env = new_tab;
				return ;	
			}
			o++;
		}
		p++;
	}
}

int	ft_unset(t_all *all)
{
	int i;
	int err;
	int j;

	iserror = 0;
	i = -1;
	err = 0;
	j = 0;
	while(all->tab && all->tab[++i])
	{
		if(all->tab[i] == '=')
			err = 1;
		if ((all->tab[i + 1] == ' ' || !all->tab[i + 1]))
		{
			if(err == 1)
			{
				err = 0;
				ft_error(all,j);
			}
			else	
				ft_suprenv(all, j);
			j = i + 2;
		}

	}
	if (iserror)
	{
		ft_putstr_fd(messerror, 1);
		free(messerror);
		return(1);
	}		
	return(0);
}
