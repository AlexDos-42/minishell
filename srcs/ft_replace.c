# include "../include/minishell.h"

char 	*ft_newtab(char *tab, char *env)
{	
	int i;
	int j;
	char *new;

	i = 0;
	j = 0;
	while(tab[i] != '$')
		i++;
	while(tab[i + j] && tab[i + j] != ' ' && tab[i + j] != '\n')
		j++;
	if (i || env)
		new = ft_substr(tab, 0, i);
	new = ft_strjoin(new, env, 1);
	new = ft_strjoin(new, &tab[i + j], 1);
	free(tab);
	if (env)
		free(env);
	return(new);
}

char	*ft_isinenv(char *tab, t_all *all)
{
	int k;
	int i;
	char *env;

	k = 0;
	while(all->env[k])
	{
		i = 0;
		while(all->env[k][i] && all->env[k][i] == tab[i + 1])
			i++;
		if (all->env[k][i] == '=' && (tab[i + 1] != '\0' || tab[i + 1] == ' ')) 
		{
			env = ft_substr(all->env[k], i + 1, ft_strlen(all->env[k]) - (i + 1));
			return(env);
		}
		k++;	
	}
	env = NULL;
	return (env);
}

char	*ft_replace(char *tab, t_all *all)
{
	int i;
	char *env;

	i = 0;
	while(tab[i])
	{
		if (tab[i + 1] && tab[i] =='$' && tab[i + 1] != ' ' && tab[i + 1] != '\n')
		{
			env = ft_isinenv(&tab[i], all);
			if (!(tab = ft_newtab(tab, env)))
					return(NULL);
		}
		i++;
	}
	return(tab);
}
