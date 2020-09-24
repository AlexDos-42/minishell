#include "../include/minishell.h"

int					ft_utilguybis(const char *str, int j, int is)
{
	int k;

	k = 0;
	while (str[j] && str[j] == '\\' && j + k < is)
		k++;
	return (k);
}

int					ft_utilguy(const char *str, int j, int is)
{
	int k;

	k = 0;
	while (str[j + k] && str[j + k] == '\\' && j + k < is)
		k++;
	return (k);
}

int					ft_loopguy(int is, const char *str, int j, int k)
{
	while (++j < is)
	{
		j += (k = ft_utilguy(str, j, is));
		if (j == is && (str[j] == '\"' || str[j] == '\'') && k % 2 == 1)
			return (1);
		if (j < is && str[j] && str[j] == '\"' && k % 2 == 0)
		{
			k = 0;
			j++;
			while (j < is && (str[j] != '\"' || (str[j] == '\"' && k % 2 == 1)))
				j += (k = ft_utilguy(str, j, is)) ? k : 1;
			if (j == is && (str[j] != '\"' || (str[j] == '\"' && k % 2 == 1)))
				return (1);
		}
		else if (j < is && str[j] && str[j] == '\'' && k % 2 == 0)
		{
			while (j + 1 != is && str[j + 1] != '\'')
				j++;
			if (++j == is && str[j] != '\'')
				return (2);
		}
	}
	return (0);
}

int					isguillemet(int is, const char *str)
{
	int j;
	int i;
	int k;

	j = -1;
	i = 0;
	k = 0;
	i = ft_loopguy(is, str, j, k);
	return (i);
}
