# include "../include/minishell.h"

char	*ft_get_file(char *tmp)
{
	char 	*name;
	int		i;
	int		j;

	name = ft_strdup("");
	i = 0;
	j = 0;
	while (tmp[i] == ' ')
		i++;
	while (tmp[i + j] && (!(ft_strchr(" ><", tmp[i + j]))))
	{
		name = ft_realloc(name, (i + 2) * sizeof(char*));
		name[j] = tmp[i + j];
		j++;
	}
	if (!(*name))
	{
		free(name);
		return (0);
	}
	name[j] = '\0';
	return (name);
}

int		ft_create_file(char *tab)
{
	int 	i;
	int		fd;
	char 	*file;

	i = 0;
	fd = 0;
	file = 0;
	while (tab[i])
	{
		if (tab[i] == '>' && tab[i + 1] == '>')
		{
			file = ft_get_file(&tab[i + 2]);
			ft_printf("%s\n", file);

		}
		else if (tab[i] == '>' && tab[i + 1] != '>')
			ft_printf("%s\n", "test2");
		else if (tab[i] == '<')
			ft_printf("%s\n", "test3");
		i++;
	}
	return (i);
}

int		ft_redirection(char *tab, t_all *all)
{
	(void)all;

	ft_create_file(tab);
	return (0);
}

