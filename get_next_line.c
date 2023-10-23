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

void	polish_list(t_list **lst)
{
	t_list	*last;
	t_list	*clean;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean = malloc(sizeof(t_list));
	if (buf == NULL || clean == NULL)
		return ;
	last = lst_last(*lst);
	i = 0;
	k = 0;
	while (last->str_buf[i] && last->str_buf[i] != '\n')
		i++;
	while (last->str_buf[i] && last->str_buf[i++])
		buf[k++] = last->str_buf[i];
	buf[k] = '\0';
	clean->str_buf = buf;
	clean->next = NULL;
	dealloc(lst, clean, buf);
}

char	*get_lines(t_list *lst)
{
	int		str_len;
	char	*next;

	if (lst == NULL)
		return (NULL);
	str_len = len_until_newline(lst);
	if (str_len == 0)
		return (NULL);
	next = malloc(str_len + 1);
	if (next == NULL)
		return (NULL);
	str_cpy(lst, next);
	return (next);
}

void	append(t_list **lst, char *buf, int fd)
{
	t_list	*new;
	t_list	*last;

	if (lst[fd] == NULL)
	{
		new = malloc(sizeof(t_list));
		if (new)
		{
			new->str_buf = buf;
			new->next = NULL;
			lst[fd] = new;
		}
	}
	else
	{
		last = lst_last(lst[fd]);
		new = malloc(sizeof(t_list));
		if (new)
		{
			new->str_buf = buf;
			new->next = NULL;
			last->next = new;
		}
	}
}

void	create_list(t_list **lst, int fd)
{
	int		char_read;
	char	*buf;

	while (!found_newline(lst[fd]))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (!char_read)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		append (lst, buf, fd);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*lst[4096];
	char			*next_line;

	if (fd < 0 || fd > 4095)
		return (NULL);
	create_list(&lst[fd], fd);
	if (lst[fd] == NULL)
		return (NULL);
	next_line = get_lines(lst[fd]);
	polish_list(&lst[fd]);
	return (next_line);
}
