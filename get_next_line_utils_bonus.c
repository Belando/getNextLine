/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelando <fbelando@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:33:21 by fbelando          #+#    #+#             */
/*   Updated: 2023/11/08 18:33:23 by fbelando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	index_s1;
	size_t	index_s2;
	char	*s3;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	s3 = malloc(1 * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!s3)
		return (NULL);
	index_s1 = -1;
	while (s1[++index_s1])
		s3[index_s1] = s1[index_s1];
	index_s2 = 0;
	while (s2[index_s2])
		s3[index_s1++] = s2[index_s2++];
	s3[index_s1] = '\0';
	free(s1);
	return (s3);
}

/*
int	main(void)
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*line;
	int		lines;

	lines = 1;
	fd1 = open("test/test.txt", O_RDONLY);
	fd2 = open("test/test2.txt", O_RDONLY);
	fd3 = open("test/test3.txt", O_RDONLY);
	while (lines <= 5)
	{
		line = get_next_line(fd1);
		printf("%d->%s\n", lines, line);
		free(line);
		line = get_next_line(fd2);
		printf("%d->%s\n", lines, line);
		free(line);
		line = get_next_line(fd3);
		printf("%d->%s\n", lines, line);
		free(line);
		lines++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}*/
