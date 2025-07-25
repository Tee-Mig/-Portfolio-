/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 23:51:10 by mfaucheu          #+#    #+#             */
/*   Updated: 2021/12/24 12:40:09 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

char	*ft_save(char *save);
char	*ft_line(char *save);
char	*ft_read(int fd, char *save);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);

size_t	ft_strlen(const char *str);

int		ft_verif_n(char *str);

#endif
