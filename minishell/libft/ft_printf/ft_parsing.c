/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:00:03 by alesanto          #+#    #+#             */
/*   Updated: 2019/12/17 16:41:36 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int			ft_flags(char *arg, t_parsing *parsing)
{
	int	i;

	i = 0;
	if (*arg)
	{
		while (arg[i] == '-' || arg[i] == '+'
				|| arg[i] == '0' || arg[i] == ' ' || arg[i] == '#')
		{
			if (arg[i] == '-')
				parsing->flagstiret = -1;
			if (arg[i] == '0' && parsing->flagstiret != -1)
			{
				parsing->flags0 = 1;
				parsing->z = 1;
			}
			if (parsing->flagstiret == -1)
			{
				parsing->flags0 = 0;
				parsing->z = 0;
			}
			i++;
		}
	}
	return (i);
}

int			ft_width2(char *arg, t_parsing *parsing, int i)
{
	parsing->flagstiret == 0 ?
		parsing->flagstiret = 1 : parsing->flagstiret;
	parsing->flagstiret *= ft_atoi(arg);
	parsing->flags0 *= parsing->flagstiret;
	parsing->z *= 2;
	while (ft_isdigit(arg[i]))
		i++;
	return (i);
}

int			ft_width(char *arg, va_list *va, t_parsing *parsing)
{
	int i;
	int j;

	i = 0;
	if (*arg && ft_isdigit(arg[i]))
		i = ft_width2(arg, parsing, i);
	else if (*arg && arg[i] == '*')
	{
		parsing->flagstiret == 0 ?
			parsing->flagstiret = 1 : parsing->flagstiret;
		j = va_arg(*va, unsigned int);
		if (j < 0)
		{
			parsing->z *= 2;
			parsing->flagstiret *= parsing->flagstiret < 0 ? -j : j;
		}
		else
			parsing->flagstiret *= j;
		parsing->flags0 *= parsing->flagstiret;
	}
	return (arg[i] == '*' ? i + 1 : i);
}

int			ft_precision(char *arg, va_list *va, t_parsing *parsing)
{
	int i;

	i = 0;
	if (*arg && arg[i] == '.')
	{
		arg++;
		parsing->precision = 0;
		parsing->z *= 2;
		if (*arg && ft_isdigit(arg[i]))
		{
			parsing->precision = ft_atoi(arg);
			while (ft_isdigit(arg[i]))
				i++;
		}
		else if (*arg && arg[i] == '*')
		{
			parsing->precision = va_arg(*va, unsigned int);
			if (parsing->precision < 0)
				parsing->precision = -1;
			i++;
		}
		i++;
	}
	return (i);
}
