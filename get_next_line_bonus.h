/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelando <fbelando@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:32:39 by fbelando          #+#    #+#             */
/*   Updated: 2023/11/08 18:32:41 by fbelando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>	
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

char	*get_next_line(int fd);
char	*ft_read_to_stash(int fd, char *stash);
char	*ft_get_line(char *stash);
char	*ft_new_stash(char *stash);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin_gnl(char *s1, char *s2);
size_t	ft_strlen(const char *str);
char	*ft_strcpy(char *dest, const char *src);

#endif