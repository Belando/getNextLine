/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelando <fbelando@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:46:06 by fbelando          #+#    #+#             */
/*   Updated: 2023/10/23 15:46:07 by fbelando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);
t_list	*lst_last(t_list *lst);
void	str_cpy(t_list *lst, char *str);
int		len_until_newline(t_list *lst);
void	dealloc(t_list **lst, t_list *clean_node, char *buf);
int		found_newline(t_list *lst);
void	polish_list(t_list **lst);
void	append(t_list **lst, char *buf, int fd);
char	*get_lines(t_list *lst);
void	create_list(t_list **lst, int fd);

#endif