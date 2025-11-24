/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:20:41 by dgaillet          #+#    #+#             */
/*   Updated: 2025/11/24 15:53:55 by dgaillet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static void	ft_bzero(void *s, size_t n)
{
	while (n > 0)
	{
		*((unsigned char *) s) = '\0';
		s++;
		n--;
	}
}

static char	*get_on_line(int fd, char buf[BUFFER_SIZE], char *nl, int res)
{
	char	*temp;

	while (1)
	{
		if (res <= 0)
			break ;
		nl = ft_strjoin_new(nl, buf, res);
		if (!nl)
			return (NULL);
		if (index_of_nl(nl, ft_strlen(nl)) >= 0)
		{
			temp = ft_substr(nl, 0, index_of_nl(nl, ft_strlen(nl)) + 1);
			free(nl);
			if (!temp)
				return (NULL);
			return (temp);
		}
		ft_bzero(buf, BUFFER_SIZE);
		res = read(fd, buf, BUFFER_SIZE);
		if (res <= 0)
			break ;
	}
	return (nl);
}

static char	*return_full_nl(int fd, char buf[BUFFER_SIZE],
					char *nl, char **last_nl)
{
	int		res;
	char	*temp;

	if (!nl)
		return (NULL);
	ft_bzero(buf, BUFFER_SIZE);
	res = read(fd, buf, BUFFER_SIZE);
	if (res == 0 && ft_strlen(nl) > 0)
	{
		*last_nl = NULL;
		return (nl);
	}
	if (res <= 0)
	{
		free(nl);
		*last_nl = NULL;
		return (NULL);
	}
	temp = get_on_line(fd, buf, nl, res);
	*last_nl = &buf[index_of_nl(buf, BUFFER_SIZE)];
	return (temp);
}

static char	*ft_ptr_match(void *to_search, void *to_match, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		if (to_search == to_match)
			return (to_search);
		i++;
		to_search++;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	static char	*last_nl;
	char		*temp;
	int			nl_i;

	nl_i = -1;
	if (last_nl)
	{
		temp = ft_ptr_match(buf, last_nl, BUFFER_SIZE);
		if (temp)
			nl_i = index_of_nl(temp + 1, &buf[BUFFER_SIZE] - temp);
		if (nl_i >= 0)
		{
			last_nl = &temp[nl_i + 1];
			temp = ft_substr(temp, 1, nl_i + 1);
			return (temp);
		}
		temp = ft_substr(temp, 1, BUFFER_SIZE);
		temp = return_full_nl(fd, buf, temp, &last_nl);
	}
	else
		temp = return_full_nl(fd, buf, ft_calloc(sizeof(char), 1), &last_nl);
	return (temp);
}
