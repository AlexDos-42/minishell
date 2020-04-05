# include "../include/minishell.h"
#include <signal.h>

void	ft_prompt(t_all *all, char *tmp, char *str)
{
	int		i;


	while (1)
	{
		i = read(0, tmp, 10);
		tmp[i] = '\0';
		str = ft_strjoin(str, tmp, 1);
		inter = 0;
		if (ft_strnstr(str, "\n", ft_strlen(str)))
		{
			if (ft_minishell(all, str) == 2)
			{
				i = -1;
				while(all->env[++i])
					free(all->env[i]);
				free(all->env);
				free(str);
				exit(0);
			}
			free(str);
			str = NULL;
			str = malloc(sizeof(char) * 1);
			str[0] = '\0';
			write(1, "minishell $>", 12);
		}
	}
}

void	ctrl(int signal)
{
	if (signal == SIGINT)
	{
		inter = 1;
		write(1, "\nminishell $>", 13);
	}
	else if (signal == SIGQUIT)
	{
		if (quit)
			write(1, "\n", 1);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_all		all;
	char		*tmp;
	char		*str;

	all.argv = argv;
//	ft_printf("PPPIIIDDDD=%i\n", getpid());
	ft_memset(&all, 0, sizeof(t_all));
	if (signal(SIGINT, &ctrl) == SIG_ERR || \
		signal(SIGQUIT, &ctrl) == SIG_ERR )
		return(1);
	if (argc == 1)
	{
		ft_initenv(&all, env);
		tmp = ft_calloc(sizeof(char), 11);
		str = ft_calloc(sizeof(char), 1);
		write(1, "minishell $>", 12);
		ft_prompt(&all, tmp, str);
	}
	return (0);
}
