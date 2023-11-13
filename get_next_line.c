/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelando <fbelando@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:45:19 by fbelando          #+#    #+#             */
/*   Updated: 2023/10/23 15:45:26 by fbelando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_to_stash(int fd, char *stash)
{
	char	*buffer;
	int		read_bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		free (stash);
		return (NULL);
	}
	read_bytes = 1;
	while (!ft_strchr(stash, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(stash);
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		stash = ft_strjoin_gnl(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*ft_get_line(char *stash)
{
	int		index;
	char	*line;

	index = 0;
	if (stash[index] == '\0')
		return (NULL);
	while (stash[index] != '\0' && stash[index] != '\n')
		index++;
	if (stash[index] == '\n')
		line = malloc(sizeof(char) * (index + 2));
	else
		line = malloc(sizeof(char) * (index + 1));
	if (!line)
		return (NULL);
	index = 0;
	while (stash[index] != '\0' && stash[index] != '\n')
	{
		line[index] = stash[index];
		index++;
	}
	if (stash[index] == '\n')
		line[index++] = '\n';
	line[index] = '\0';
	return (line);
}

char	*ft_new_stash(char *stash)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	if (stash[i] == '\0')
	{
		free(stash);
		return (NULL);
	}
	str = malloc(sizeof(char) * ft_strlen(stash) - i + 1);
	if (!str)
	{
		free (stash);
		return (NULL);
	}
	i++;
	j = 0;
	while (stash[i] != '\0')
		str[j++] = stash[i++];
	str[j] = '\0';
	free(stash);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_get_line(stash);
	if (!line)
	{
		free (stash);
		stash = NULL;
		return (NULL);
	}
	stash = ft_new_stash(stash);
	return (line);
}

/*int	main(void)
{
	int		fd;
	char	*line;

	fd = open("./test.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("LINE-> %s", line);
		free (line);
	}
	close (fd);
	return (0);
}*/
