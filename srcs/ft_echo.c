#include "../include/minishell.h"

int			isquote(char c, int q, int *i)
{
	if (c == '\"' && q != 2)
	{
		*i = *i + 1;
		q = q ? 0 : 1;
	}
	if (c == '\'' && q != 1)
	{
		*i = *i + 1;
		q = q ? 0 : 2;
	}
	return (q);
}

void		ft_putstr_echo(char *str, int fd)
{
	int i;
	int q;

	if (!str || !*str || fd < 0)
		return ;
	i = 0;
	q = 0;
	while (str[i])
	{
		if (i == 0 || (i != 0 && str[i - 1] != '\\'))
			q = isquote(str[i], q, &i);
		if (str[i] == '\\')
		{
			if (str[i + 1])
			{
				write(fd, &str[i + 1], 1);
				i += 2;
			}
			else
				i++;
		}
		else if ((str[i] && str[i] != '\"' && str[i] != '\'') || (str[i] &&
		((str[i] == '\"' && q == 2) || (str[i] == '\'' && q == 1))))
			write(fd, &str[i++], 1);
	}
}

int			ft_echo(t_all *all)
{
	char *tmp;

	if (!ft_strncmp(all->tab, "-n", 2))
	{
		tmp = ft_strtrim(all->tab + 2, " ");
		ft_putstr_echo(tmp, 1);
		free(tmp);
	}
	else
	{
		tmp = ft_strtrim(all->tab, " ");
		ft_putstr_echo(tmp, 1);
		write(1, "\n", 1);
		free(tmp);
	}
	free(all->tab);
	return (ret = 0);
}
