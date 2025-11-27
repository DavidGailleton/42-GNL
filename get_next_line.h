/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:22:03 by dgaillet          #+#    #+#             */
/*   Updated: 2025/11/27 18:05:13 by dgaillet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>

char	*get_next_line(int fd);

size_t	ft_strlen(const char *s);
char	*ft_strjoin_new(char const *s1, char const *s2, size_t limit);
void	ft_bzero(void *s, size_t n);
int		index_of_nl(char *str, int limit);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
