/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:23:35 by jpluta            #+#    #+#             */
/*   Updated: 2025/03/17 17:28:39 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*ft_strdup2(char *s1);
char	*ft_strjoin2(char *s1, char *s2);
char	*ft_strchr2(const char *s, int c);
char	*read_till_newline(int fd, char **remainder);
char	*get_remainder(char *buffer);
char	*extract_line(char *buffer, char *line);
void	*ft_memcpy2(void *dst, const void *src, size_t n);
char	*process_remainder(char **remainder);
char	*read_till_newline2(int fd, char *buffer, char *line, char **remainder);

#endif
