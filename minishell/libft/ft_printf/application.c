/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   application.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:04:40 by alesanto          #+#    #+#             */
/*   Updated: 2019/12/17 16:19:17 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void		ft_s_precisionapp(char arg, t_parsing *parsing)
{
	char	*tmp;

	if ((arg == 's') && parsing->precision >= 0)
	{
		tmp = ft_substr(parsing->aff, 0, parsing->precision);
		free(parsing->aff);
		parsing->aff = tmp;
	}
}

void		ft_precisionappnbr(t_parsing *parsing)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = parsing->neg;
	if (parsing->precision > (ft_strlen(parsing->aff) - j))
	{
		tmp = ft_calloc(sizeof(char*), (parsing->precision + j + 1));
		if (j == 1)
			tmp[i++] = '-';
		while (parsing->precision-- > (ft_strlen(parsing->aff)) - j)
		{
			tmp[i++] = '0';
			parsing->z = 0;
		}
		tmp[i] = '\0';
		tmp = ft_strjoin(tmp, &(parsing->aff[j]), 1);
		free(parsing->aff);
		parsing->aff = tmp;
	}
}

void		ft_flagsapp(t_parsing *parsing, char arg)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	j = (parsing->flagstiret > 0) ? parsing->flagstiret : -parsing->flagstiret;
	if (parsing->flags0 > j)
		j = parsing->flags0;
	tmp = ft_calloc(sizeof(char), (j + 1));
	if (!ft_strlen(parsing->aff) && arg == 'c')
		j--;
	while (j-- > ((!ft_strlen(parsing->aff) ? 0 : ft_strlen(parsing->aff))))
		tmp[i++] = ' ';
	tmp[i] = '\0';
	if (parsing->flagstiret > 0)
		parsing->aff = ft_strjoin(tmp, parsing->aff, 3);
	else
		parsing->aff = ft_strjoin(parsing->aff, tmp, 3);
}

void		ft_exception(t_parsing *parsing, char arg)
{
	char	*tmp;

	if (arg == 'd' || arg == 'i' || arg == 'u' || arg == 'x'
			|| arg == 'X' || arg == 'p' || arg == '%')
	{
		if (parsing->precision == 0 && parsing->aff[0] == '0')
		{
			tmp = ft_strdup("");
			free(parsing->aff);
			parsing->aff = tmp;
		}
		if (parsing->precision == -1)
			parsing->precision = (parsing->aff[0] == '-') ?
				parsing->flags0 - 1 : parsing->flags0;
	}
}

void		ft_app(char arg, t_parsing *parsing)
{
	int i;

	i = 0;
	if (arg == 'c' && !ft_strlen(parsing->aff))
		i = 1;
	ft_exception(parsing, arg);
	ft_s_precisionapp(arg, parsing);
	if (arg == 'd' || arg == 'i'
			|| arg == 'u' || arg == 'x' || arg == 'X' || arg == 'p')
	{
		parsing->aff[0] == '-' ? parsing->neg = 1 : 0;
		ft_precisionappnbr(parsing);
	}
	if (arg == 'p')
		parsing->aff = ft_strjoin("0x", parsing->aff, 2);
	if (((parsing->z != 0 && (arg == '%' || arg == 's')) || (parsing->z == 1
			&& (arg == 'c' || arg == 'd' || arg == 'i' || arg == 'u'
			|| arg == 'x' || arg == 'X'))) && (parsing->flagstiret > 0))
		ft_flagsapp0(parsing, arg);
	else if (parsing->flagstiret != 0 && parsing->w != 1)
		ft_flagsapp(parsing, arg);
	if (arg == 'c' && i == 1 && parsing->flagstiret < 0)
		parsing->c = -1;
	else if (arg == 'c' && i == 1)
		parsing->c = 1;
}
