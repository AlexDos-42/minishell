#include "../include/minishell.h"

static int		check(const char c, const char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			i++;
		else
			return (1);
	}
	return (0);
}

char			*ft_strtrimslash(char const *str, char const *set)
{
	int		i;
	int		j;
	char	*s;
    int     k;
    
	if (!str || !set)
		return (0);
	i = 0;
	j = ft_strlen(str) - 1;
	while (check(str[i], set) == 1)
		i++;
	if (i == (j + 1))
		return (ft_calloc(1, sizeof(char)));
	while (check(str[j], set) == 1)
	{
        k = 0;
		if (j == 0)
			return (NULL);
        while(j > 0 && str[j - 1  - k] == '\\')
            k++;
        if (k % 2 == 1)
            break;
		j--;
	}
	s = ft_substr(str, i, j - i + 1);
	return (s);
}
