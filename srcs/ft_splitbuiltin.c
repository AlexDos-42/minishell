#include "../include/minishell.h"

static int					ischarsetspace(const char *str, int is, char c)
{
	int i;

	i = 0;
	if (is > 0 && str[is] == c && str[is - 1] == '\\')
		while(is > i && str[is - 1 - i] == '\\')
			i++;
	if (str[is] == c && !isguillemet(is, str) && i % 2 == 0)
		return (1);
	return (0);
}

static int			ft_taillem(const char *str, int i, char charset)
{
	int		j;

	j = 0;
	while (!ischarsetspace(str, i, charset) && str[i] != '\0')
	{
		i++;
		j++;
	}
	return (j);
}

char                *ft_splitbuiltin(const char *str, char c)
{
	int			is;
	int			j;
	char		*tab;

	if (!str)
		return (NULL);
	is = 0;
	j = 0;
	while (str[is] == c && str[is])
		is++;
	tab = malloc(sizeof(char) * (ft_taillem(str, is, c) + 1));
	while (str[is] && !ischarsetspace(str, is, c))
		tab[j++] = str[is++];
	tab[j] = '\0';
	return (tab);
}
