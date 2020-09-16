/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:54:08 by alesanto          #+#    #+#             */
/*   Updated: 2019/12/07 13:15:44 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_read(int fd, char *buffer, char **stock)
{
	int		ret;

	while (!ft_strchr(stock[fd], '\n') &&
		(ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		stock[fd] = ft_strjoin(stock[fd], buffer, 1);
	}
	return (ret);
}

int					get_next_line(int fd, char **line)
{
	char		buffer[BUFFER_SIZE + 1];
	int			ret;
	int			i;
	static char	*stock[1024];
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	if (!stock[fd])
		stock[fd] = ft_calloc(0, 0);
	if ((ret = ft_read(fd, buffer, stock)) == -1)
		return (-1);
	i = 0;
	while (stock[fd][i] && stock[fd][i] != '\n')
		i++;
	*line = ft_substr(stock[fd], 0, i);
	tmp = stock[fd][i] ? ft_strdup(stock[fd] + i + 1) : NULL;
	free(stock[fd]);
	stock[fd] = tmp;
	if (ret != 0 || stock[fd])
		return (1);
	return (0);
}
