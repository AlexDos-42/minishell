# include "../include/minishell.h"


int	ft_write(char c)
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
	else if (c == '\'')
		write(1, "\'", 1);
	else if (c == '\"')
		write(1, "\"", 1);
	else if (c == '$')
		write(1, "$", 1);
	else
		write(1, "\\", 1);
	return (2);
}

int	isquote(char c, int q, int *i)
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
	return(q);
}

void	ft_putstr_echo(char *str, int fd)
{
	int i;
	int q;
	int j;

	if (!str || !*str || fd < 0)
		return ;
	i = 0;
	q = 0;
	//ft_printf("str %s\n", str);
	while (str[i])
	{
		//ft_printf("q %d\n", q);
		if (i == 0 || (i != 0 && str[i - 1] != '\\'))
			q = isquote(str[i], q, &i);
		if (str[i] == '\\')
		{
			if (str[i] == '\\' && str[i + 1])
			{	
				i += ft_write(str[i + 1]);
				if (str[i] == '\\' && str[i - 1] == '\\')
				{
					j = 0;
					while (str[i + j] == '\\')
						j++;
	//				ft_printf("j %d\n", j);
					i += j % 2 ? j : j - 1;
				}
			}
			else
				i++;
		}	
		else if ((str[i] && str[i] != '\"' && str[i] != '\'') ||
			(str[i] && ((str[i] == '\"' && q == 2) || (str[i] == '\'' && q == 1))))
		{	
			write(fd, &str[i], 1);
			i++;
		}
	//	ft_printf("str[i] %c\n", str[i]);
	}
}

int	ft_echo(t_all *all)
{
	char *tmp;

	//ft_printf("all->tab %s\n", all->tab);ec
	if (!ft_strncmp(all->tab, "-n", 2))
	{
		tmp = ft_strtrim(all->tab + 2, " ");
	//	ft_printf("tmp 1 %s\n", tmp);
		ft_putstr_echo(tmp, 1);
		free(tmp);
	}
	else
	{
		tmp = ft_strtrim(all->tab, " ");
	//	ft_printf("tmp 2 %s\n", tmp);
		ft_putstr_echo(tmp, 1);
		write(1, "\n", 1);
		free(tmp);
	}
	free(all->tab);
	return(ret = 0);
}
