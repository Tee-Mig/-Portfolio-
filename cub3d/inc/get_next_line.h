/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:34:04 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/14 04:32:39 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		is_line_in_junk(char *junk);

char	*ft_end(char *junk, char *v);
char	*get_next_line(int fd);
char	*get_line_from_junk(char *junk);
char	*move_to_junk(char *tmp, char *junk);
char	*remove_line_from_junk(char *junk);

void	ft_bzero(void *s, size_t n);

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

#endif
