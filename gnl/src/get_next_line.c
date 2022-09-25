/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 00:22:17 by fakouyat          #+#    #+#             */
/*   Updated: 2022/06/04 00:22:17 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strdup(char *s)
{
	int		i;
	char	*s_cpy;

	i = 0;
	while (s[i] != 0)
			i++;
	s_cpy = (char *)malloc(i + 1);
	if (!s_cpy)
		return (0);
	s_cpy[i] = '\0';
	while (i > 0)
	{
		s_cpy[i - 1] = s[i - 1];
		i--;
	}
	return (s_cpy);
}

static void	ft_bzero(void *s, int n)
{
	int		i;
	char	*s_int;

	s_int = (char *)s;
	i = 0;
	while (i < n)
	{
		*(s_int + i) = '\0';
		i++;
	}
}

int	ft_read_line(char **line, char str_kept[], int *count)
{
	char	*index;
	int		i;
	char	*tmp;

	index = ft_strchr_gnl(str_kept, '\n');
	i = 0;
	if (index != 0)
	{
		tmp = str_kept;
		*line = ft_substr_gnl(tmp, 0, (index - tmp) + 1);
		while (*(index + 1 + i) != 0)
		{
			str_kept[i] = *(index + 1 + i);
			i++;
		}
		ft_bzero(&str_kept[i], MAX_SIZE - i);
		return (1);
	}
	if (*count == 0)
	{
		*line = ft_strdup(str_kept);
		*count = -1;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char		*str_read;
	static char	str_kept[MAX_SIZE];
	int			count;
	char		*line;

	if (fd < 0 || fd > FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	str_read = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	ft_bzero(str_read, BUFFER_SIZE + 1);
	count = read(fd, str_read, BUFFER_SIZE);
	if (count < 0 || (count == 0 && str_kept[0] == 0))
	{
		free(str_read);
		return (NULL);
	}
	ft_strcat(str_kept, str_read);
	free(str_read);
	if (ft_read_line(&line, str_kept, &count) == 1)
		return (line);
	if (count == -1)
	{
		ft_bzero(str_kept, MAX_SIZE);
		return (line);
	}
	return (get_next_line(fd));
}
