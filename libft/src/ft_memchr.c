/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:37:23 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/25 15:35:41 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_char;
	size_t			i;

	s_char = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (s_char[i] == (unsigned char)c)
			return (&s_char[i]);
		i++;
	}
	return (NULL);
}
