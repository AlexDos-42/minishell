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

int		ft_create_file(char *tab, int *fd, char *file, int *i)
{
		if (tab[*i] == '>' && tab[(*i) + 1] == '>')
		{
			ft_printf("%s\n", "test1");
			file = ft_get_file(&tab[(*i) + 2]);
			*fd = open(file, O_CREAT | O_WRONLY | O_APPEND);
			(*i)++;

		}
		else if (tab[*i] == '>')
		{
			ft_printf("%s\n", "test2");
			file = ft_get_file(&tab[(*i) + 1]);
			*fd = open(file, O_CREAT | O_WRONLY | O_TRUNC);

		}
		else if (tab[*i] == '<')
		{
			file = ft_get_file(&tab[(*i) + 1]);
			*fd = open(file, O_WRONLY);
		}
	if (file)
		free(file);
	return ((*fd != 0 || file) ? 1 : 0);
}

int		ft_redirection(char *tab, t_all *all)
{
	(void)all;
	char	*file;
	int		fd;
	int 	i;
	char	*tmp;

	fd = 0;
	file = 0;
	i = 0;
	while (tab[i])
	{
		if ((tmp = ft_strchr("><", tab[i])))
		{
			ft_create_file(tab, &fd, file, &i);
		}
		i++;
	}
	return (fd);
}

