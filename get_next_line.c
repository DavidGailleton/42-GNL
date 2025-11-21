/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:20:41 by dgaillet          #+#    #+#             */
/*   Updated: 2025/11/21 19:06:31 by dgaillet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static char	*ft_read_line(int fd, char *dest, char buf[BUFFER_SIZE])
{
	int	readed;
	int	i;

	readed = 1;
	while (readed)
	{
		readed = read(fd, buf, BUFFER_SIZE);
		if (readed < 0)
			return (NULL);
		i = index_of_nl(buf, BUFFER_SIZE);
		if (i < 0)
			dest = ft_strjoin_new(dest, buf, readed);
		else
			dest = ft_strjoin_new(dest, buf, i);
		if (!dest)
			return (NULL);
		if (i >= 0)
			break ;
	}
	return (dest);
}

static char	*create_new_line(char buf[BUFFER_SIZE], char *base_str)
{
	char	*new_str;
	int		buf_len;
	int		nl_i;

	if (!buf)
		return (NULL);
	buf_len = ft_strlen(buf);
	nl_i = index_of_nl(buf, buf_len);
	if (nl_i >= 0)
	{
		new_str = ft_substr(buf, nl_i, buf_len - nl_i);
		free(base_str);
		return (new_str);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	char		*nl;
	char		*temp;

	nl = malloc(sizeof(char));
	if (!nl)
		return (NULL);
	temp = create_new_line(buf, nl);
	if (temp)
		nl = ft_read_line(fd, temp, buf);
	else
	{
		nl[0] = '\0';
		nl = ft_read_line(fd, nl, buf);
	}
	return (nl);
}

#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	char	*str;
	int		fd;

	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
		close(fd);
	}
}
