
char	**tab_env(char **env, size_t *nb_env)
{
	size_t	i;
	char	**env;

	i = 0;
	while (env[i])
		i++;
	if (!(env = ft_calloc(sizeof(char*), (i + 1))))
		return (NULL);
	env[i] = NULL;
	i = 0;
	while (env[i])
	{
		if (!(env[i] = ft_strdup(env[i])))
		{
			return (NULL);
		}
		i++;
	}
	*nb_env = i;
	return (env);
}

void	ft_initenv(t_all *all, char **env)
{
	all->pwd = getcwd(NULL, 0);
	all->env = tab_env(env, &all->nb_env);
//	int i = -1;
//	while(env[++i])
//		printf("%d env %s\n",i, env[i]);
}
