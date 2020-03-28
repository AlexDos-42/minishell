/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:19:00 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/15 11:42:00 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void		ft_type(char type, va_list *va, t_parsing *parsing)
{
	if (type == 'c')
		parsing->aff = ft_cdup(va_arg(*va, int));
	else if (type == '%')
		parsing->aff = ft_cdup('%');
	else if (type == 's')
		parsing->aff = ft_strdup(va_arg(*va, char*));
	else if (type == 'd' || type == 'i')
		parsing->aff = ft_itoa(va_arg(*va, int));
	else if (type == 'u')
		parsing->aff = ft_itoa_base(va_arg(*va, unsigned), "0123456789");
	else if (type == 'x')
		parsing->aff =
			ft_itoa_base(va_arg(*va, unsigned), "0123456789abcdef");
	else if (type == 'X')
		parsing->aff =
			ft_itoa_base(va_arg(*va, unsigned), "0123456789ABCDEF");
	else if (type == 'p')
		parsing->aff = ft_ptoa_base(va_arg(*va,
					unsigned long long int), "0123456789abcdef");
}

void		ft_init_parsing(t_parsing *parsing)
{
	parsing->flagstiret = 0;
	parsing->flags0 = 0;
	parsing->precision = -1;
	parsing->c = 0;
	parsing->aff = NULL;
	parsing->w = 0;
	parsing->z = 0;
	parsing->neg = 0;
}

int			ft_parsingpf(char *arg, va_list *va, t_parsing *parsing)
{
	int i;

	i = 0;
	i += ft_flags(&arg[i], parsing);
	if (*arg && !(ft_isdigit(arg[i])) && arg[i] != '*')
		parsing->w = 1;
	i += ft_width(&arg[i], va, parsing);
	i += ft_precision(&arg[i], va, parsing);
	if (arg[i] == 'c' || arg[i] == 'd' || arg[i] == 'i' || arg[i] == '%' ||
			arg[i] == 'x' || arg[i] == 'X' || arg[i] == 'u'
			|| arg[i] == 'p' || arg[i] == 's')
	{
		ft_type(arg[i], va, parsing);
		ft_app(arg[i], parsing);
		return (++i);
	}
	return (0);
}

int			ft_boucle(char *arg, va_list *va)
{
	t_parsing	parsing;
	int			len;

	len = 0;
	while (*arg)
	{
		ft_init_parsing(&parsing);
		if (*arg == '%')
		{
			arg++;
			arg += ft_parsingpf(arg, va, &parsing);
			if (parsing.aff || parsing.c)
				len = len + ft_putstr_pf(parsing.aff, parsing.c);
		}
		if (!parsing.aff && *arg)
		{
			ft_putchar_fd(*arg, 1);
			len++;
			arg++;
		}
		free(parsing.aff);
	}
	return (len);
}

int			ft_printf(const char *format, ...)
{
	char		*arg;
	va_list		va;
	int			len;

	va_start(va, format);
	arg = (char *)format;
	len = ft_boucle(arg, &va);
	va_end(va);
	return (len);
}
