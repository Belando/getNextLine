/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelando <fbelando@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:45:50 by fbelando          #+#    #+#             */
/*   Updated: 2023/10/23 15:45:52 by fbelando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		s1 = malloc(sizeof(char));
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	s3 = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
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
