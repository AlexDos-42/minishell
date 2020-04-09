# include "../include/minishell.h"


int	ft_write(char c, int i)
{
	if (c == 'n')
		write(1, "\n", 1);
	else if (c == 'r')
		write(1, "\r", 1);
	else if (c == 't')
		write(1, "\t", 1);
	else if (c == '0')
		write(1, "\0", 1);
	else if (c == 'a')
		write(1, "\a", 1);
	else if (c == 'b')
		write(1, "\b", 1);
	else if (c == 'f')
		write(1, "\f", 1);
	else
	{
		write(1, "\\", 1);
		return(i);
	}
	return (2);
}

int	isquote(char c, int q, int *i, int j)
{
	if (c == '\"' && q != 2)
	{
		if(j == 1)
			*i = *i + 1;
		q = q ? 0 : 1;
	}
	if (c == '\'' && q != 1)
	{
		if (j == 1)
			*i = *i + 1;
		q = q ? 0 : 2;	
	}
	return(q);
}

void	ft_putstr_echo(char *str, int fd)
{
	int i;
	int q;

	if (!str || !*str || fd < 0)
		return ;
	i = 0;
	q = 0;
	while (str[i])
	{
		q = isquote(str[i], q, &i, 1);
		if (str[i] == '\\')
		{
			i++;
			q = isquote(str[i], q, &i, 0);
			while (str[i + 1] == '\\')
				i++;
			if (q != 0 && str[i])
				i += ft_write(str[i], 0);
		   	else if (str[i] == '\\' && str[i + 1])
				i += ft_write(str[i + 1], 1);
		}	
		else if (str[i])
		{	
			write(fd, &str[i], 1);
			i++;
		}
	}
}

int	ft_echo(t_all *all)
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
	return(ret = 0);
}
