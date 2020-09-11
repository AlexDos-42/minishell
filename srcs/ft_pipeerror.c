#include "../include/minishell.h"

void	istabpipe_suite3(char *tab, t_all *all, int i)
{	
	int j;
	int k;
	char *tmp;
	
	if (!ft_strncmp(&tab[i], "unset ", 6))
	{
		while(tab[i + 6])
		{
			k = 0;
			j = 0;
			while(tab[i + 6] == ' ')
				i++;
			while(tab[i + 6 + j] && tab[i + 6 + j] != ' ')
			{
				if (tab[i + 6 + j] == '=')
					k = 1;	
				j++;
			}
			if (k == 1)
			{
				tmp = ft_substr(tab, i + 6, j);
				ft_printf("minishell: unset: « %s » : identifiant non valable\n", tmp);
				free(tmp);
			}
			i += j;
		}		
	}
	(void)all;
}

void	istabpipe_suite2(char *tab, t_all *all, int i)
{	
	int j;
	int k;
	char *tmp;
	
	if (!ft_strncmp(&tab[i], "export ", 7))
	{
		while (tab[i + 7])
		{
			k = 0;
			j = 0;
			while(tab[i + 7] == ' ')
				i++;
			if (tab[i + 7] == '=')
				k = 1;
			while(tab[i + 7 + j] && tab[i + 7 + j] != ' ')	
				j++;
			if (k == 1)
			{
				tmp = ft_substr(tab, i + 7, j);
				ft_printf("minishell: export: « %s » : identifiant non valable\n", tmp);
				free(tmp);
			}
			i += j;
		}
	}
	else 
		istabpipe_suite3(tab, all, i);
}

void	istabpipe_suite(char *tab, t_all *all, int i)
{
	int j;
	char *tmp;
	int k;

	if (!ft_strncmp(&tab[i], "cd ", 3))
	{
		j = 0;
		k = 0;
		while (tab[i + 3] == ' ')
			i++;
		while (tab[i + 3 + j + k])
		{
			j += k;
			k = 0;
			j++;
			while (tab[i + 3 + j + k] == ' ')
				k++;
		}
		if (j)
		{
			tmp = ft_substr(tab, i + 3, j);
			if ((ft_strlen(tmp) == 1 && (tmp[0] != '.' || tmp[0] != '~')) ||
				(ft_strlen(tmp) == 2 && tmp[0] != '.' && tmp[1] != '.')
				|| chdir(tmp) != 0)
				ft_printf("cd: %s: %s\n", strerror(errno), tmp);
			free(tmp);
		}
	}
	else
		istabpipe_suite2(tab, all, i);
}

void	istabpipe(char *tab, t_all *all)
{
	int i;
	
	i = 0;
	while (tab[i] == ' ')
		i++;
	if (!ft_strncmp(&tab[i], "echo ", 5) || (!ft_strncmp(&tab[i], "exit", 4)))
		;
	else if (!ft_strncmp(&tab[i], "pwd ", 4))
	{
		while(tab[i + 4] == ' ')
			i++;
		if (tab[i + 4])
			ft_printf("pwd: too many arguments\n");
	}
	else if (!ft_strncmp(&tab[i], "env ", 4))
	{
		while(tab[i + 4] == ' ')
			i++;
		if (tab[i + 4])
			ft_printf("env: %s:\n", tab);
	}
	else
		istabpipe_suite(tab, all, i);
}