/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 22:22:59 by fakouyat          #+#    #+#             */
/*   Updated: 2022/05/22 22:22:59 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define MAX_SIZE 888888
# define FD_MAX 1024
# define BUFFER_SIZE 100

# include<fcntl.h> 
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

char	*ft_strchr_gnl(const char *s, int c);
void	ft_strcat(char *dst, const char *src);
char	*ft_substr_gnl(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);
int		ft_size_s(char *s);

#endif