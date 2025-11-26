/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:55:25 by dgaillet          #+#    #+#             */
/*   Updated: 2025/11/26 12:20:50 by dgaillet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line_bonus.h"

static int	del_before_nl(char buf[BUFFER_SIZE])
{
	int		nl_i;
	int		i;
	char	*temp;

	nl_i = index_of_nl(buf, BUFFER_SIZE);
	if (nl_i >= 0)
	{
		temp = ft_substr(buf, nl_i + 1, BUFFER_SIZE - nl_i);
		if (!temp)
			return (-1);
		ft_bzero(buf, BUFFER_SIZE);
		i = 0;
		while (temp[i])
		{
			buf[i] = temp[i];
			i++;
		}
		free(temp);
	}
	return (1);
}

static char	*extract_all_nl(char buf[BUFFER_SIZE], int fd, char *str, int nl_i)
{
	int	temp;

	str = ft_substr(buf, 0, BUFFER_SIZE);
	if (!str)
		return (NULL);
	while (nl_i < 0)
	{
		str = ft_strjoin_new(str, buf, temp);
		ft_bzero(buf, BUFFER_SIZE);
		temp = read(fd, buf, BUFFER_SIZE);
		if (temp < 0)
			return (free(str), NULL);
		if ((!str || ft_strlen(str) == 0) && temp == 0)
			return (free(str), NULL);
		if (temp == 0)
			return (str);
		nl_i = index_of_nl(buf, temp);
	}
	str = ft_strjoin_new(str, buf, nl_i);
	temp = del_before_nl(buf);
	if (temp < 0)
		return (free(str), NULL);
	return (str);
}

static char	*ft_gnl_extra(char buf[BUFFER_SIZE], int fd)
{
	int		nl_i;
	int		temp;
	char	*str;

	nl_i = index_of_nl(buf, BUFFER_SIZE);
	if (nl_i >= 0)
	{
		str = ft_substr(buf, 0, nl_i);
		temp = del_before_nl(buf);
		if (temp < 0)
			return (free(str), NULL);
	}
	else
		str = extract_all_nl(buf, fd, "", nl_i);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	strs[1024][BUFFER_SIZE];
	char		*to_return;

	to_return = ft_gnl_extra(strs[fd], fd);
	return (to_return);
}
/*
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	char	*str;
	int		fd1;
	int		fd2;
	int		fd3;

	fd1 = open("a.txt", O_RDONLY);
	fd2 = open("b.txt", O_RDONLY);
	fd3 = open("c.txt", O_RDONLY);
	str = get_next_line(fd1);
	printf("%s\n", str);
	free(str);
	str = get_next_line(fd2);
	printf("%s\n", str);
	free(str);
	str = get_next_line(fd3);
	printf("%s\n", str);
	free(str);
	str = get_next_line(fd1);
	printf("%s\n", str);
	free(str);
	str = get_next_line(fd2);
	printf("%s\n", str);
	free(str);
	str = get_next_line(fd3);
	printf("%s\n", str);
	free(str);
	str = get_next_line(fd1);
	printf("%s\n", str);
	free(str);
	str = get_next_line(fd2);
	printf("%s\n", str);
	free(str);
	str = get_next_line(fd3);
	printf("%s\n", str);
	free(str);
	str = get_next_line(fd1);
	printf("%s\n", str);
	free(str);
}
*/
