# include "../include/minishell.h"

void ft_exporterreur(char *str, int k)
{
	if(!str[1])
	{
		if (k)
			write(1, "export: not valid in this context:\n", 36);
		else
			write(1, "minshell: bad assignment\n", 26);
	}
	else
	{
		str++;
		write(1, "minishell: ", 12);
		write(1, str, ft_strlen(str));
		write(1, " not found\n", 11);
	}
}

int	 ft_isenvexist(t_all *all, int i, int j, int k)
{
	unsigned int p;
	int o;

	p = 0;
	while(all->env[p] && p < all->nb_env -1)
	{	
		o = 0;
		while(all->env[p][o] && (all->env[p][o] == all->tab[j + o]))
		{
			if(all->env[p][o] == '=')
			{
				if(k == 1)
				{
					free(all->env[p]);
					all->env[p] = ft_substr(all->tab, j, i + 1 - j);
				}
				return(1);
			}
			o++;
		}
		p++;
	}
	return(0);
}

int	ft_nbnewenv(t_all *all)
{
	int i;
	int k;
	int eg;
	int j;

	i = -1;
	k = 0;
	eg = 0;
	j = 0;
	while(all->tab[++i])
	{
		if(all->tab[i] == '=')
		{
			eg = 1;
			if(all->tab[i - 1] == ' ' || !all->tab[i - 1])
			{
				ft_exporterreur(&all->tab[i], k);
				return(0);
			}
		}
		if ((all->tab[i + 1] == ' ' || !all->tab[i + 1]) && eg == 1)
		{
			if (!(ft_isenvexist(all, i, j, 1)))
				k++;
			j = i + 2;
			eg = 0;
		}
		
	}
	return(k);
}

char	**ft_newenv(t_all *all, int k)
{
	int i;
	int j;
	char **tabnewenv;
	int eg;

	i = -1;
	j = 0;
	tabnewenv = malloc(sizeof(char*) * (k + 1));
	k = 0;
	eg = 0;
	while(all->tab[++i])
	{
		if(all->tab[i] == '=')
			eg = 1;
		if ((all->tab[i + 1] == ' ' || !all->tab[i + 1]) && eg == 1)
		{
			if (!(ft_isenvexist(all, i, j, 0)))
			{
				tabnewenv[k] = ft_substr(all->tab, j, i + 1 - j);
				k++;
			}
			j = i + 2;
			eg = 0;
		}
	}
	return(tabnewenv);
}

int	ft_export(t_all *all)
{
	unsigned int i;
	char **tabnewenv;
	char **new_env;
	int nb_newenv;
	int j;
	
	if (!(nb_newenv = ft_nbnewenv(all)))
		return (0);
	tabnewenv = ft_newenv(all, nb_newenv);
	if (!(new_env = malloc((all->nb_env + nb_newenv + 1) * sizeof(char*))))
		return (0);
	i = 0;
	j = 0;
	while (i < all->nb_env)
	{
		new_env[i + j] = ft_strdup(all->env[i]);
		free(all->env[i]);
		i++;
		if (i == all->nb_env - 1)
		{
			while (j < nb_newenv)
			{
				new_env[i + j] = ft_strdup(tabnewenv[j]);
				j++;
			}
		}
	}
	all->nb_env += nb_newenv;
	free(all->env);
	all->env = new_env;
	return(0);
}
