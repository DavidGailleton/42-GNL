/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:55:25 by dgaillet          #+#    #+#             */
/*   Updated: 2025/11/24 17:22:10 by dgaillet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line_bonus.h"

static char	*get_lines(int fd, char *str)
{
	char	buf[BUFFER_SIZE];
	int		res;

	res = read(fd, buf, BUFFER_SIZE);
	while (res > 0)
	{
		if (!str)
			str = ft_strdup(buf);
		else
			str = ft_strjoin_new(str, buf, res);
		if (!str)
			return (NULL);
		ft_bzero(buf, BUFFER_SIZE);
		res = read(fd, buf, BUFFER_SIZE);
	}
	if (res < 0)
	{
		if (str)
			free(str);
		return (NULL);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*strs[1024];

	if (!strs[fd])
		strs[fd] = get_lines(fd, strs[fd]);

}
