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

int	found_newline(t_list *lst)
{
	int	i;

	while (lst)
	{
		i = 0;
		while (lst->str_buf[i] != '\0' && i < BUFFER_SIZE)
		{
			if (lst->str_buf[i] == '\n')
				return (1);
			i++;
		}
		lst = lst->next;
	}
	return (0);
}

t_list	*lst_last(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	str_cpy(t_list *lst, char *str)
{
	int		i;
	int		k;

	if (lst == NULL || str == NULL)
		return ;
	k = 0;
	while (lst)
	{
		i = 0;
		while (lst->str_buf[i] && lst->str_buf[i] != '\n')
			str[k++] = lst->str_buf[i++];
		if (lst->str_buf[i] == '\n')
		{
			str[k++] = '\n';
			return ;
		}
		lst = lst->next;
	}
	str[k] = '\0';
}

int	len_until_newline(t_list *lst)
{
	int	len;
	int	i;

	len = 0;
	while (lst)
	{
		i = 0;
		while (lst->str_buf[i] != '\0')
		{
			len++;
			if (lst->str_buf[i] == '\n')
				return (len);
			i++;
		}
		lst = lst->next;
	}
	return (len);
}

void	dealloc(t_list **lst, t_list *clean_node, char *buf)
{
	t_list	*actual;
	t_list	*next;

	if (lst == NULL)
		return ;
	actual = *lst;
	while (actual)
	{
		next = actual->next;
		free(actual->str_buf);
		free(actual);
		actual = next;
	}
	*lst = NULL;
	if (clean_node != NULL && clean_node->str_buf[0] == '\0')
	{
		free(clean_node);
		clean_node = NULL;
	}
	if (buf != NULL)
		free(buf);
}
